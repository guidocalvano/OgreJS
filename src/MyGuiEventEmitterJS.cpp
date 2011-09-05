#include <MyGuiEventEmitterJS.h>
/*
void MyGuiEventEmitterBindJS :: initMyGuiEventEmitterBindJS( MyGUI:: Widget* widget )
	{
		printf( "bound myguieventemitter\n") ;
	 widget-> eventMouseButtonPressed += MyGUI::newDelegate( this, &MyGuiEventEmitterBindJS::mouseButtonPressed ) ;

	// widget-> eventMouseMove += MyGUI::newDelegate( this, &MyGuiEventEmitterBindJS::mouseMove ) ;	
	}
	*/

void MyGuiEventEmitterJS:: emit( char* eventTypeCSTR, v8::Local<v8::Value> arg ) 
	{
	 v8::Local<v8::String> name = v8::String::New( "emit" ) ;

	 v8::Local< v8::Value > funcUncast = handle_->Get( name) ;

	 v8::Local<v8::Function> func = v8::Local<v8::Function>::Cast( funcUncast ) ;
	
	 v8::Local<v8::String> eventType 	= v8::String::New( eventTypeCSTR ) ;
	
	
	 v8::Local<v8::Value> args[2] ;
	 args[0] = eventType ;
	 args[1] = arg ;

	 func-> Call( handle_, 2, args ) ;
	
	}

	

void MyGuiEventEmitterJS:: mouseButtonPressed( MyGUI::Widget* _sender, int _left, int _top, MyGUI::MouseButton _id )
	{
		printf( "mouse pressed my gui\n");
 	 emit( "mousePressed", v8::String::New( "p" ) ) ;
	}

void MyGuiEventEmitterJS:: mouseMove( MyGUI::Widget* _sender, int _left, int _top ) 
	{
 	 // emit( "mouseMoved", v8::String::New( "mv" ) ) ;
	}
