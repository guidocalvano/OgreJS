#include <ButtonBindJS.h>
#include <EventEmitterJS.h>
#include <string.h>
#include <MemoryManagerJS.h>

v8::Persistent<v8::FunctionTemplate> ButtonBindJS:: buttonPrototypeTemplate ;


    
void ButtonBindJS:: init( v8::Handle< v8::Object > target ) 
    {
     v8::Local<v8::FunctionTemplate> t = v8::FunctionTemplate::New(New);

	 // t-> GetFunction()-> Call( t->PrototypeTemplate(), 0, NULL   )
	 t-> Inherit( EventEmitterJS:: prototypeTemplate ) ;

   	 buttonPrototypeTemplate = v8::Persistent<v8::FunctionTemplate>::New(t);
   	 buttonPrototypeTemplate->InstanceTemplate()->SetInternalFieldCount(1);

   	 buttonPrototypeTemplate->SetClassName(v8::String::NewSymbol("Button"));
   	
     NODE_SET_PROTOTYPE_METHOD_BORROWED( buttonPrototypeTemplate, "destroy", destroy ) ;

     NODE_SET_PROTOTYPE_METHOD_BORROWED( buttonPrototypeTemplate, "setCaption", setCaption ) ;
     NODE_SET_PROTOTYPE_METHOD_BORROWED( buttonPrototypeTemplate, "setPosition", setPosition ) ;
     NODE_SET_PROTOTYPE_METHOD_BORROWED( buttonPrototypeTemplate, "setSize", setSize ) ;

    }


v8::Handle<v8::Value> ButtonBindJS:: New( const v8::Arguments& args ) 
    {
	 printf( "button new \n") ;
		
	 EventEmitterJS:: prototypeTemplate-> GetFunction()-> Call( args.This(), 0, NULL ) ;
		
     return args.This() ;
    }


v8::Handle<v8::Value> ButtonBindJS:: NewFromButtonCpp( MyGUI::Button* button ) 
    {
     v8::Local<v8::Function> function = ButtonBindJS::buttonPrototypeTemplate-> GetFunction();
     v8::Handle<v8::Object>   object   = function->NewInstance();

     ButtonBindJS* buttonBindJS = new ButtonBindJS() ;
     
     buttonBindJS-> button = button ;

	 buttonBindJS-> initMyGuiEventEmitterBindJS( button ) ;

	 // button-> eventMouseButtonPressed += MyGUI::newDelegate<ButtonBindJS>( buttonBindJS, &ButtonBindJS::mouseButtonPressed ) ;

     buttonBindJS-> Wrap( object ) ;

	 MemoryManagerJS:: singleton-> updateV8AllocatedMemory() ;

     return buttonBindJS-> handle_ ;
    }


v8::Handle<v8::Value> ButtonBindJS:: destroy( const v8::Arguments& args )
    {
	 ButtonBindJS* bound = node::ObjectWrap::Unwrap<ButtonBindJS>( args.This() ) ;

	 v8::Handle<v8::Value> val = WidgetConvertJS:: destroy( bound-> button, args ) ;
	
	 MemoryManagerJS:: singleton-> updateV8AllocatedMemory() ;
	
	 return val ;
	}
	
	

 v8::Handle<v8::Value> ButtonBindJS:: setCaption( const v8::Arguments& args ) 
	{
	 ButtonBindJS* bound = node::ObjectWrap::Unwrap<ButtonBindJS>( args.This() ) ;

	 return StaticTextBindJS:: setCaption( bound-> button, args ) ;
	}

 v8::Handle<v8::Value> ButtonBindJS:: setPosition( const v8::Arguments& args ) 
	{
	 ButtonBindJS* bound = node::ObjectWrap::Unwrap<ButtonBindJS>( args.This() ) ;

	 return WidgetConvertJS:: setPosition( bound-> button, args ) ;	
	}

 v8::Handle<v8::Value> ButtonBindJS:: setSize( const v8::Arguments& args ) 
	{
	 ButtonBindJS* bound = node::ObjectWrap::Unwrap<ButtonBindJS>( args.This() ) ;

	 return WidgetConvertJS:: setSize( bound-> button, args ) ;	
	}