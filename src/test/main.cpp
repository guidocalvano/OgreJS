
#include "juice/ogre/Vector.hpp"
#include <v8.h>
#include <ostream>
#include <boost/bind.hpp>


//A callback to print stuff out, from javascript. Meant for debugging.
v8::Handle<v8::Value> LogCallback(const v8::Arguments& args) {
  if (args.Length() < 1) return v8::Undefined();
  v8::HandleScope scope;
  v8::Handle<v8::Value> arg = args[0];
  v8::String::Utf8Value value(arg);
  std::cout << std::string(*value, value.length()) << std::endl;
  return v8::Undefined();
}



// Reads a file into a v8 string.
v8::Handle<v8::String> ReadFile(const char* name) {
  FILE* file = fopen(name, "rb");
  if (file == NULL) return v8::Handle<v8::String>();

  fseek(file, 0, SEEK_END);
  int size = ftell(file);
  rewind(file);

  char* chars = new char[size + 1];
  chars[size] = '\0';
  for (int i = 0; i < size;) {
    int read = fread(&chars[i], 1, size - i, file);
    i += read;
  }
  fclose(file);
  v8::Handle<v8::String> result = v8::String::New(chars, size);
  delete[] chars;
  return result;
}

//This utility function will compile a v8 string into a script.
// It also takes a second paramter, which is a function
// object that reports v8 exceptions.
template<typename HandleTryCatch>
v8::Handle<v8::Script>
compile(const v8::Handle<v8::String> script_source,
  const v8::Handle<v8::String> script_name,
  HandleTryCatch handleTryCatch)
{
  assert(!script_source.IsEmpty());
  assert(v8::Context::InContext());
  
  v8::HandleScope handle_scope;
  
  // Compile script in try/catch context.
  v8::TryCatch try_catch;
  
  v8::Handle<v8::Script> script = v8::Script::Compile(script_source, script_name);
  
  
  if (script.IsEmpty()) {
    handleTryCatch(try_catch);
  }
  
  return handle_scope.Close(script);
}


//This utlity function will run a script that has already been
// compiled. It also takes a second paramter, which is a function
// object that reports v8 exceptions.
template<typename HandleTryCatch>
v8::Handle<v8::Value>
run(v8::Handle<v8::Script> script, HandleTryCatch handleTryCatch)
{
  assert(!script.IsEmpty());
  assert(v8::Context::InContext());
  
  v8::HandleScope handle_scope;

  v8::TryCatch try_catch;
  v8::Handle<v8::Value> result = script->Run();
  
  if (try_catch.HasCaught()) {
    handleTryCatch(try_catch);
  }
  
  return handle_scope.Close(result);
}


// Utility function to get a v8 utf8 string's in as a const char* 
const char* ToCString(const v8::String::Utf8Value& value) {
  return *value ? *value : "<string conversion failed>";
}


//This is a function that will take an exception and report the errors
// through the specified stream out. Use boost::bind to turn this
// into a unary function object, taking only the exception as an
// argument, while predefining the output stream, the type of which
// is specified with the template parameter.
template<typename OutT>
void
ReportException(const v8::TryCatch& try_catch, OutT& out) {

  v8::HandleScope handle_scope;
  
  v8::String::Utf8Value exception(try_catch.Exception());
  const char* exception_string = ToCString(exception);
  v8::Handle<v8::Message> message = try_catch.Message();
  if (message.IsEmpty()) {
    // V8 didn't provide any extra information about this error; just
    // print the exception.
    out << exception_string << std::endl;
  } else {
    // Print (filename):(line number): (message).
    v8::String::Utf8Value filename(message->GetScriptResourceName());
    const char* filename_string = ToCString(filename);
    int linenum = message->GetLineNumber();
    out
      << filename_string
      << ":" << linenum
      << ": " << exception_string
      << std::endl;
    // Print line of source code.
    v8::String::Utf8Value sourceline(message->GetSourceLine());
    const char* sourceline_string = ToCString(sourceline);
    out << sourceline_string << std::endl;
    // Print wavy underline (GetUnderline is deprecated).
    int start = message->GetStartColumn();
    for (int i = 0; i < start; i++) {
      out << (" ");
    }
    int end = message->GetEndColumn();
    for (int i = start; i < end; i++) {
      out << ("^");
    }
    out << std::endl;
  }
}

//Just print the usage of this test program.
void usage(){
  printf("Usage:\n" "test <script>\n");
}

int main(int argc, const char** argv){
  if ( argc < 2 ) {
    usage();
    return -1;
  }
  
  //Script file name
  const char* filename = argv[1];
  
  //Intro on v8 Handles:
  //There are two types of Handles: Persistent, and Local. Local goes onto a "stack" which is always the last 
  // v8::HandleScope to be created. When each HandleScope goes out of scope, it reaps the references of all the local
  // variables on its "stack".
  // There are two ways to pass a JS reference outside of a v8::HandleScope. One is usually used when returning from a function
  // like so: return handle_scope.Close(local);. This passes the reference up to the next v8::HandleScope.
  // The second way is to use another type of Handle: the Persistent Handle. This reference will not be reaped with RIIA, but will
  // instead only be reaped when Dispose is called on the handle.
  // v8::Handle is a superclass to both Persistent, and to Local, and can refere to either.
  
  
  //This will hold the v8 context, all execution in v8 happens in such a "context"
  //Note: this is a Persistent handle, which means that once initialized, its reference will not be
  // reaped until we explicitly call Persistent::Dispose(). However, for now it is empty.
  v8::Persistent<v8::Context> m_v8Context;
  
  {
    //All execution in v8 must happen while one of these is on the stack somewhere
    v8::Locker locker;
    
    //When this destructs, it will collect any scoped (non-persistent) Handles created from now until the end of the scope,
    // reaping the Handles' references.
    v8::HandleScope handle_scope;
    
    //Greate a object tempalte, which will be a template for the global object.
    v8::Handle<v8::ObjectTemplate> globt = v8::ObjectTemplate::New();
      
    //Global template
    {
      //This object template will have a .log() function
      //Very simple to bind simple global functions that take JS type arguments
      globt->Set( v8::String::New("log"), v8::FunctionTemplate::New(LogCallback));
    }

    //Create the new context. v8::Context::New() returns a persistent handle. Remember to call Dispose() when we are done with it.
    // We create the new context with the global template object, thus the global object of the context will not
    // be copied from the global template object.
    m_v8Context = v8::Context::New(NULL, globt);
    
    //In order to do any execution within a context, we must lock it sort of.
    v8::Context::Scope context_scope(m_v8Context);
    
    //Setup the v8 context for execution
    {
      //Get the global object
      v8::Handle<v8::Object> global = m_v8Context->Global();
      
      //inform v8 of these classes
      {
        //Vector
        juice::ogre::Vector::bind(global);
      }
    }
  } //Leave the setup scope
  
  
  //Compile and run a script
  //This can be anywhere, we left all the scopes.
  {
    //We are about to do some v8 stuff ... lock it.
    v8::Locker locker;
    
    //Create a stack for Local handles.
    v8::HandleScope handle_scope;
    
    //Lock the context for execution
    v8::Context::Scope context_scope(m_v8Context);

    //Simply use this utility function to read in the file to a strings.
    v8::Handle<v8::String> script_source = ReadFile(filename);
    
    //Sanity
    if (script_source.IsEmpty()) {
      printf("Failed to load file.\n");
      return -1;
    }
    
    //Use the compile function above to return a compiled script.
    v8::Handle<v8::Script> script = compile(script_source,
      v8::String::New(filename),
      //Report errors with the utility function object above
      // std::bind simply creates a stl function object out of a function.
      // The function object will take one argument, the exception, and we predefine
      // its second argument, which is a stream out for error messages, as going to
      // std::cout.
      boost::bind(ReportException<std::ostream>, _1, boost::ref(std::cout)));
    
    //Sanity
    if ( script.IsEmpty() ) 
    {
      printf("Failed to compile script.\n");
      return -1;
    }
    
    //Use the utility run function to run the script.
    v8::Handle<v8::Value> result = run(script,
      //See explanation by complile() above, this function object
      // will report exception errors to std::cout.
      boost::bind(ReportException<std::ostream>, _1, boost::ref(std::cout)) );
  }// leave locks, scopes etc.
  
  // We are no longer going to use the context. Dispose of it.
  m_v8Context.Dispose();
  
  return 0;
};
