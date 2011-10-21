
// #include <OgreManager.h>
#include <v8.h>
#include <node.h>
#include <OgreJS.h>
#include <MemoryManagerJS.h>
// #include <MyGuiJS.h>

int main( int argc, char** argv )
	{
	 printf( "START\n" ) ;
	  // This needs to run *before* V8::Initialize()
	  argv = node::Init(argc, argv);

	 printf( "node::Init\n" ) ;
	  v8::V8::Initialize();
	  v8::HandleScope handle_scope;

	  // Create the one and only Context.
	  v8::Persistent<v8::Context> context = v8::Context::New();
	  v8::Context::Scope context_scope(context);

	 printf( "v8 init stuff\n" ) ;
	  v8::Handle<v8::Object> process = node::SetupProcessObject(argc, argv);


	 printf( "new object \n" ) ;

	  v8::Local<v8::Object> mem = v8::Object::New() ;

	 MemoryManagerJS::init( mem ) ;

	  v8::Local<v8::Object> ogre = v8::Object::New() ;

	 // init( ogre ) ;
	 printf( "ogreman init \n" ) ;
	 // OgreManager:: getSingletonPtr()-> initDefault() ;

	 OgreJS:: require( ogre ) ;

	 printf( "ogreman setup \n" ) ;

//	 OgreManager:: getSingletonPtr()-> setupDemoScene() 	;
	 printf( "global init \n" ) ;

	  context->Global()->Set( v8::String::New("mem"), mem ) ;


	  context->Global()->Set( v8::String::New("ogre"), ogre ) ;
	
	
/*	 
 	 v8::Local<v8::Object> myGui = v8::Object::New() ;
 	 
 	 MyGuiJS::require( myGui ) ;

 	 context->Global()->Set( v8::String::New( "gui" ), myGui ) ;
*/ 	

	 printf( "load \n" ) ;

  // Create all the objects, load modules, do everything.
  // so your next reading stop should be node::Load()!
	  node::Load(process);



  // All our arguments are loaded. We've evaluated all of the scripts. We
  // might even have created TCP servers. Now we enter the main eventloop. If
  // there are no watchers on the loop (except for the ones that were
  // uv_unref'd) then this function exits. As long as there are active
  // watchers, it blocks.
//  uv_run();
	 printf( "run \n" ) ;

	  node::Run() ;

	 printf( "exit \n" ) ;

	  node::EmitExit(process);

	#ifndef NDEBUG
	  // Clean up.
	  context.Dispose();
	  // v8::V8::Dispose();
	#endif  // NDEBUG

	 // initOgre( argc, args ) ;
	}

