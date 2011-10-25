
#include <OgreJS.h>
#include <OgreManager.h>
#include <CameraJS.h>
#include <InputJS.h>

#include <MaterialJS.h>

#include <SceneNodeJS.h>
#include <EntityJS.h>
#include <SubEntityJS.h>
#include <AnimationStateJS.h>


#include <EventEmitterJS.h>

#include <fstream>
#include <sstream>
#include <string>

#include <iostream>

using namespace std;

OgreJS* OgreJS:: singleton = NULL ;


OgreJS:: OgreJS()
	{
	 pickingManagerJS = new PickingManagerJS() ;
	}



void OgreJS :: require(  v8::Handle< v8::Object > target ) 
	{
	 singleton = new OgreJS() ;
	 /*
 	 v8::HandleScope handle_scope;

	 v8::Persistent<v8::Context> context = v8::Context::New();

 	 v8::Context::Scope context_scope(context);
	*/
	 EventEmitterJS::init() ;


	 new OgreManager() ;

	 OgreManager:: getSingletonPtr()-> initDefault() ;
	 OgreManager:: getSingletonPtr()-> setupDemoScene() ;



	 v8::Local<v8::Object> system = v8::Object::New() ;

	 MaterialJS:: init( system ) ;

	 SceneNodeJS:: init( system ) ;
	 EntityJS:: init( system ) ;
	 SubEntityJS:: init( system ) ;
	 AnimationStateJS:: init( system ) ;


	 v8::Handle<v8::Value> cameraJS = CameraJS:: NewFromCamera( OgreManager:: getSingletonPtr()-> m_pCamera ) ;

	 v8::Handle<v8::Value> inputJS = InputJS:: NewFromOgreManager() ;
	
	 // context-> Global()-> Set( v8::String::New("system"), system ) ;

	 system-> Set( v8::String::New("Camera"), cameraJS ) ;
	 system-> Set( v8::String::New("input"), inputJS ) ;
	
	 v8::Local<v8::Object> windowObj = v8::Object::New() ;
	
	 windowObj-> Set( v8::String::New("width"),  v8::Number::New( OgreManager:: getSingletonPtr()-> m_pViewport->getActualWidth()) ) ;
	 windowObj-> Set( v8::String::New("height"), v8::Number::New( OgreManager:: getSingletonPtr()-> m_pViewport->getActualHeight() ) ) ;

	 system-> Set( v8::String::New("window"), windowObj ) ;

	// context-> Global()-> Set( v8::String::New("exports"), target ) ;

/*
  	 ifstream file ;

  	 file.open ("src/js/ogre.js" ) ;

	 stringstream buf ;

	 buf << file.rdbuf() ;

	 string sourceString = buf.str() ;

	 printf( sourceString.c_str() ) ;	 

	 

 	 v8::Handle<v8::String> source = v8::String::New( sourceString.c_str() );
	 
 	 v8::Handle<v8::Script> script = v8::Script::Compile(source);
  
 	 v8::Handle<v8::Value> result = script->Run();
 	 
 	*/
 	 

	target-> Set( v8::String::New( "system" ), system ) ;
	 target-> Set( v8::String::New( "EventEmitter" ), EventEmitterJS:: prototypeTemplate-> GetFunction() ) ;
 	 
 	 
 	 
 	 
 	 
 	 
  
 	// context.Dispose();


/*
	 target-> Set( v8::String::New("system"), system ) ;

	 target-> Set( v8::String::New("Camera"), cameraJS ) ;
	 target-> Set( v8::String::New("Input"), inputJS ) ;

*/
	}
