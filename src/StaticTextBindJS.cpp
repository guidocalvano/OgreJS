
#include <StaticTextBindJS.h>
#include <EventEmitterJS.h>
#include <string.h>
#include <MemoryManagerJS.h>

v8::Persistent<v8::FunctionTemplate> StaticTextBindJS:: prototypeTemplate ;


    
void StaticTextBindJS:: init( v8::Handle< v8::Object > target ) 
    {
     v8::Local<v8::FunctionTemplate> t = v8::FunctionTemplate::New(New);

	 // t-> GetFunction()-> Call( t->PrototypeTemplate(), 0, NULL   )
	 t-> Inherit( EventEmitterJS:: prototypeTemplate ) ;

   	 prototypeTemplate = v8::Persistent<v8::FunctionTemplate>::New(t);
   	 prototypeTemplate->InstanceTemplate()->SetInternalFieldCount(1);

   	 prototypeTemplate->SetClassName(v8::String::NewSymbol("StaticText"));
   	
     NODE_SET_PROTOTYPE_METHOD_BORROWED( prototypeTemplate, "destroy", 		destroy ) ;

     NODE_SET_PROTOTYPE_METHOD_BORROWED( prototypeTemplate, "setCaption", 	setCaption ) ;
     NODE_SET_PROTOTYPE_METHOD_BORROWED( prototypeTemplate, "setPosition", 	setPosition ) ;
     NODE_SET_PROTOTYPE_METHOD_BORROWED( prototypeTemplate, "setSize", 		setSize ) ;
    }


v8::Handle<v8::Value> StaticTextBindJS:: New( const v8::Arguments& args ) 
    {
	 printf( "static text new \n") ;
		
	 EventEmitterJS:: prototypeTemplate-> GetFunction()-> Call( args.This(), 0, NULL ) ;
		
     return args.This() ;
    }


v8::Handle<v8::Value> StaticTextBindJS:: NewFromStaticTextCpp( MyGUI::StaticText* w ) 
    {
     v8::Local<v8::Function> function = StaticTextBindJS::prototypeTemplate-> GetFunction();
     v8::Handle<v8::Object>   object   = function->NewInstance();

     StaticTextBindJS* bindJS = new StaticTextBindJS() ;
     
     bindJS-> staticText = w ;

	 bindJS-> initMyGuiEventEmitterBindJS( w ) ;


     bindJS-> Wrap( object ) ;

	 MemoryManagerJS:: singleton-> updateV8AllocatedMemory() ;

     return bindJS-> handle_ ;
    }


v8::Handle<v8::Value> StaticTextBindJS:: destroy( const v8::Arguments& args )
    {
	 StaticTextBindJS* bound = node::ObjectWrap::Unwrap<StaticTextBindJS>( args.This() ) ;

	 v8::Handle<v8::Value> val = WidgetConvertJS:: destroy( bound-> staticText, args ) ;
	
	 MemoryManagerJS:: singleton-> updateV8AllocatedMemory() ;
	
	 return val ;
	}
	
	
	
	
v8::Handle<v8::Value> StaticTextBindJS::setCaption( const v8::Arguments& args ) 
	{
	 StaticTextBindJS* bound = node::ObjectWrap::Unwrap<StaticTextBindJS>( args.This() ) ;

	 return StaticTextBindJS:: setCaption( bound-> staticText, args ) ;
	}
	
	
v8::Handle<v8::Value> StaticTextBindJS::setCaption( MyGUI::StaticText* staticText, const v8::Arguments& args ) 
	{
	 v8::String::AsciiValue ascii( args[ 0 ] ) ;
		
	 staticText-> setCaption( *ascii ) ;

	 return v8::Undefined() ;
	}
	
v8::Handle<v8::Value> StaticTextBindJS::setPosition( const v8::Arguments& args ) 
	{
	 StaticTextBindJS* bound = node::ObjectWrap::Unwrap<StaticTextBindJS>( args.This() ) ;

	 return WidgetConvertJS:: setPosition( bound-> staticText, args ) ;	
	}

v8::Handle<v8::Value> StaticTextBindJS::setSize( const v8::Arguments& args ) 
	{
	 StaticTextBindJS* bound = node::ObjectWrap::Unwrap<StaticTextBindJS>( args.This() ) ;

	 return WidgetConvertJS:: setSize( bound-> staticText, args ) ;	
	}