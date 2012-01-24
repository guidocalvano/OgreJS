#include <InputMyGuiJS.h>

#include <OIS/OISEvents.h>
#include <OIS/OISInputManager.h>
#include <OIS/OISKeyboard.h>
#include <OIS/OISMouse.h>

v8::Handle< v8::Object > InputMyGuiJS:: createInput() 
	{
	 v8::Handle< v8::Object > object = v8::Object::New() ;
		
	 v8::Handle< v8::FunctionTemplate > f = v8::FunctionTemplate::New( injectMouseMove ) ;
	 object-> Set( v8::String::New( "injectMouseMoved" ), f->GetFunction()   ) ;		
	
	 f = v8::FunctionTemplate::New( injectMousePress ) ;
	 object-> Set( v8::String::New( "injectMousePressed" ), f->GetFunction()   ) ;
	
	 f = v8::FunctionTemplate::New( injectMouseRelease ) ;
	 object-> Set( v8::String::New( "injectMouseReleased" ), f->GetFunction()   ) ;
	
	 f = v8::FunctionTemplate::New( injectKeyPress ) ;
	 object-> Set( v8::String::New( "injectKeyPressed" ), f->GetFunction()   ) ;
	
	 f = v8::FunctionTemplate::New( injectKeyRelease ) ;
	 object-> Set( v8::String::New( "injectKeyReleased" ), f->GetFunction()   ) ;
	
	return object ;
	}




v8::Handle<v8::Value> InputMyGuiJS:: injectMouseMove( const v8::Arguments& args )
	{	
	 v8::Handle<v8::Object> place = args[ 0 ]-> ToObject()-> Get( v8::String::New( "place" ) )-> ToObject() ;

	 int x = place-> Get( v8::Number::New( 0 ) )-> ToInteger()-> Value() ;
	 int y = place-> Get( v8::Number::New( 1 ) )-> ToInteger()-> Value() ;

	 MyGUI::InputManager::getInstancePtr()-> injectMouseMove( x, y, 0 ) ;
	
	 return v8:: Undefined() ;
	}


v8::Handle<v8::Value> InputMyGuiJS:: injectMousePress( const v8::Arguments& args )
	{	
	 printf( "mygui injectmousepress...\n");

	 v8::Handle<v8::Object> place = args[ 0 ]-> ToObject()-> Get( v8::String::New( "place" ) )-> ToObject() ;

	 int x = place-> Get( v8::Number::New( 0 ) )-> ToInteger()-> Value() ;
	 int y = place-> Get( v8::Number::New( 1 ) )-> ToInteger()-> Value() ;

	 return v8:: Boolean:: New( MyGUI::InputManager::getInstancePtr()->  injectMousePress( x, y, MyGUI::MouseButton::Enum( OIS::MB_Left ) ) ) ;
	
	//  return v8:: Undefined() ;
	}


v8::Handle<v8::Value> InputMyGuiJS:: injectMouseRelease( const v8::Arguments& args )
	{
	 v8::Handle<v8::Object> place = args[ 0 ]-> ToObject()-> Get( v8::String::New( "place" ) )-> ToObject() ;

	 int x = place-> Get( v8::Number::New( 0 ) )-> ToInteger()-> Value() ;
	 int y = place-> Get( v8::Number::New( 1 ) )-> ToInteger()-> Value() ;

	 MyGUI::InputManager::getInstancePtr()->  injectMouseRelease( x, y, MyGUI::MouseButton::Enum( OIS::MB_Left ) ) ;

	 return v8:: Undefined() ;
	}





v8::Handle<v8::Value> InputMyGuiJS:: injectKeyPress( const v8::Arguments& args )
	{
	 v8::Handle<v8::Object> obj = args[ 0 ]-> ToObject() ;
	
	 int 		  code =  obj-> Get( v8::String::New( "keyCode" ) )-> ToInteger()-> Value() ;
	 v8::String::AsciiValue ascii( obj-> Get( v8::String::New( "keyChar" ) ) ) ;	
		
	 printf( "keycode %i keychar %c \n", code, (*ascii)[0] ) ;

	 MyGUI::InputManager::getInstancePtr()->  injectKeyPress( (MyGUI::KeyCode::Enum) code, (*ascii)[0]  ) ;

	 return v8:: Undefined() ;
	}


v8::Handle<v8::Value> InputMyGuiJS:: injectKeyRelease( const v8::Arguments& args )
	{
	 v8::Handle<v8::Object> obj = args[ 0 ]-> ToObject() ;

	 int code = obj-> Get( v8::String::New( "keyCode" ) )-> ToInteger()-> Value() ;
		
	 MyGUI::InputManager::getInstancePtr()->  injectKeyRelease( (MyGUI::KeyCode::Enum) code ) ;

	 return v8:: Undefined() ;
	}



