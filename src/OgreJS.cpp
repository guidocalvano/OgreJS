
#include <OgreJS.h>
#include <OgreManager.h>
#include <CameraJS.h>
#include <InputJS.h>

#include <SceneNodeJS.h>
#include <EntityJS.h>

#include <fstream>
#include <sstream>
#include <string>

#include <iostream>

using namespace std;

void OgreJS :: require(  v8::Handle< v8::Object > target ) 
	{
 	 v8::HandleScope handle_scope;

	 v8::Persistent<v8::Context> context = v8::Context::New();

 	 v8::Context::Scope context_scope(context);


	 new OgreManager() ;

	 OgreManager:: getSingletonPtr()-> initDefault() ;
	 OgreManager:: getSingletonPtr()-> setupDemoScene() ;

	 v8::Handle<v8::Value> cameraJS = CameraJS:: NewFromCamera( OgreManager:: getSingletonPtr()-> m_pCamera ) ;

	 v8::Handle<v8::Value> inputJS = InputJS:: NewFromOgreManager() ;

	 v8::Local<v8::Object> system = v8::Object::New() ;

	 SceneNodeJS:: init( system ) ;
	 EntityJS:: init( system ) ;

	 context-> Global()-> Set( v8::String::New("system"), system ) ;

	 context-> Global()-> Set( v8::String::New("Camera"), cameraJS ) ;
	 context-> Global()-> Set( v8::String::New("Input"), inputJS ) ;

	 context-> Global()-> Set( v8::String::New("exports"), target ) ;


  	 ifstream file ;

  	 file.open ("src/js/ogre.js" ) ;

	 stringstream buf ;

	 buf << file.rdbuf() ;

	 string sourceString = buf.str() ;

	 printf( sourceString.c_str() ) ;	 

	 

 	 v8::Handle<v8::String> source = v8::String::New( sourceString.c_str() );
	 
 	 v8::Handle<v8::Script> script = v8::Script::Compile(source);
  
 	 v8::Handle<v8::Value> result = script->Run();
 	 
 	 
 	 
 	 
 	 v8::Handle<v8::Object> myGui = v8::Object::New() ;
 	 
 	 MyGuiRootJS::init( myGui ) ;
 	 
 	 target-> Set( v8::String::New( "gui" ), myGui ) ;
 	 
 	 
 	 
 	 
 	 
  
 	 context.Dispose();

/*
	 target-> Set( v8::String::New("system"), system ) ;

	 target-> Set( v8::String::New("Camera"), cameraJS ) ;
	 target-> Set( v8::String::New("Input"), inputJS ) ;

*/
	}
