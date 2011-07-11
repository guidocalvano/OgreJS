#error "Obsoleted code. Don't include this."

// utility code for test/demo apps. Mostly taken from the v8 sample shell

void ReportException(v8::TryCatch* try_catch) {
    // code taken from v8 sample shell
  v8::HandleScope handle_scope;
  //v8::String::Utf8Value exception();
  std::string exception_string( cv::CastFromJS<std::string>(try_catch->Exception()) ) ;
  v8::Handle<v8::Message> message = try_catch->Message();
  std::ostream & out( std::cerr );
  if (message.IsEmpty()) {
      // V8 didn't provide any extra information about this error; just
      // print the exception.
      out << exception_string << '\n';
  } else {
    // Print (filename):(line number): (message).
    std::string filename_string = cv::JSToStdString(message->GetScriptResourceName());
    int linenum = message->GetLineNumber();
    out << filename_string << ':' << linenum
         << ": "<< exception_string
         << '\n';
    // Print line of source code.
    std::string sourceline_string = cv::JSToStdString(message->GetSourceLine());
    out << sourceline_string << '\n';
    // Print wavy underline (GetUnderline is deprecated).
    int start = message->GetStartColumn();
    for (int i = 0; i < start; i++) {
        out << ' ';
    }
    int end = message->GetEndColumn();
    for (int i = start; i < end; i++) {
        out << '^';
    }
    out << std::endl;
    v8::String::Utf8Value stack_trace(try_catch->StackTrace());
    if (stack_trace.length() > 0) {
        std::string stack_trace_string = cv::JSToStdString(try_catch->StackTrace());
        out << stack_trace_string << '\n';
    }
  }
}

// Executes a string within the current v8 context.
bool ExecuteString(v8::Handle<v8::String> source,
                   v8::Handle<v8::Value> name,
                   bool print_result,
                   bool report_exceptions) {
    // code taken from v8 sample shell
    v8::HandleScope handle_scope;
    v8::TryCatch try_catch;
    v8::Handle<v8::Script> script = v8::Script::Compile(source, name);
    std::ostream & out = std::cout;
    if (script.IsEmpty()) {
        // Print errors that happened during compilation.
        if (report_exceptions)
            ReportException(&try_catch);
        return false;
    } else {
        v8::Handle<v8::Value> result = script->Run();
        if (result.IsEmpty()) {
            // Print errors that happened during execution.
            if (report_exceptions)
                ReportException(&try_catch);
            return false;
        } else {
            if (print_result && !result->IsUndefined()) {
                // If all went well and the result wasn't undefined then print
                // the returned value.
                out << cv::JSToStdString(result) << '\n';
            }
            return true;
        }
    }
}

v8::Handle<v8::Value> Load(const v8::Arguments& args)
{
    // code taken from v8 sample shell
    //CERR << "load(...)ing...\n";
    for (int i = 0; i < args.Length(); i++) {
        v8::HandleScope handle_scope;
        v8::String::Utf8Value file(args[i]);
        if (*file == NULL) {
            return v8::ThrowException(v8::String::New("Error loading file"));
        }
        std::ifstream istr(*file);
        istr >> std::noskipws;
        std::ostringstream os;
        std::copy( std::istream_iterator<char>(istr),
                   std::istream_iterator<char>(),
                   std::ostream_iterator<char>(os) );
        v8::Handle<v8::String> source =
            JSTR(os.str().c_str());
        os.clear();
        if (source.IsEmpty()) {
            return v8::ThrowException(v8::String::New("Error loading file"));
        }
        if (!ExecuteString(source, v8::String::New(*file), false, true)) {
            return v8::ThrowException(v8::String::New("Error executing file"));
        }
    }
    return v8::Undefined();
}

// The callback that is invoked by v8 whenever the JavaScript 'print'
// function is called.  Prints its arguments on stdout separated by
// spaces and ending with a newline.
v8::Handle<v8::Value> Print(const v8::Arguments& args) {
  bool first = true;
  for (int i = 0; i < args.Length(); i++) {
    v8::HandleScope handle_scope;
    if (first) {
      first = false;
    } else {
        std::cout << ' ';
    }
    std::cout << cv::JSToStdString(args[i]);
  }
  std::cout << std::endl;
  return v8::Undefined();
}


/**
   Implements the v8::InvocationCallback interface and has the
   following JS interface:

   @code
   Array stracktrace([unsigned int limit = some reasonable default])
   @endcode

   Each element in the returned array represents a stack frame and
   is a plain object with the following properties:

   column = 1-based column number (note that this is different from most editors,
   but this is how v8 returns this value.)
       
   line = 1-based line number

   scriptName = name of the script

   functionName = name of the function

   isConstructor = true if this is a constructor call

   isEval = true if this is part of an eval()

   TODO:

   - Add a toString() member to the returned array which creates a
   conventional-looking stacktrace string.
*/
v8::Handle<v8::Value> GetV8StackTrace( v8::Arguments const & argv )
{
    using namespace v8;
    // Lame hack to distinguish between v8::juice::convert and v8::convert APIs:
#if defined(CODE_GOOGLE_COM_V8_CONVERT_SIGNATURE_CORE_V8_HPP_INCLUDED)
    namespace cv = v8::convert;
#else
    namespace cv = v8::juice::convert;
#endif
    uint32_t limit = (argv.Length() > 0) ? cv::CastFromJS<uint32_t>(argv[0]) : 0;
    if( limit == 0 ) limit = 8;
    else if( limit > 100 ) limit = 100;

    Local<StackTrace> const st = StackTrace::CurrentStackTrace( limit, StackTrace::kDetailed );
    int const fcountI = st->GetFrameCount();
    // Who the hell designed the StackTrace API to return an int in GetFrameCount() but take
    // an unsigned int in GetFrame()???
    uint32_t const fcount = static_cast<uint32_t>(fcountI);
    Local<Array> jst = Array::New(fcount);
#define STR(X) v8::String::New(X)
    for( uint32_t i = 0; (i < fcount) && (i<limit); ++i )
    {
        Local<StackFrame> const & sf( st->GetFrame(i) );
        Local<Object> jsf = Object::New();
        jsf->Set(STR("column"), cv::CastToJS(sf->GetColumn()));
        jsf->Set(STR("functionName"), sf->GetFunctionName());
        jsf->Set(STR("line"), cv::CastToJS(sf->GetLineNumber()));
        jsf->Set(STR("scriptName"), sf->GetScriptName());
        jsf->Set(STR("isConstructor"), cv::CastToJS(sf->IsConstructor()));
        jsf->Set(STR("isEval"), cv::CastToJS(sf->IsEval()));
        jst->Set(i,jsf);
    }
    return jst;
#undef STR
}

#if !defined(_WIN32)
#  include <unistd.h> /* only for sleep() */
#  define do_sleep sleep
#else
#  include <windows.h>
#  define do_sleep(N) Sleep((N)*1000)
#endif
v8::Handle<v8::Value> JsSleep( v8::Arguments const & argv )
{
#if defined(CODE_GOOGLE_COM_V8_CONVERT_SIGNATURE_CORE_V8_HPP_INCLUDED)
    namespace cv = v8::convert;
#else
    namespace cv = v8::juice::convert;
#endif
    unsigned int n = (argv.Length()>1) ? cv::CastFromJS<uint32_t>(argv[0]) : 0;
    if( ! n ) return v8::Undefined();
    else
    {
        return cv::CastToJS(do_sleep(n));
    }
}
