


#include <StaticTextJS.h>
#include <MemoryManagerJS.h>
#include <EventEmitterJS.h>

v8::Persistent<v8::FunctionTemplate> StaticTextJS:: staticTextPrototypeTemplate ; 


void StaticTextJS:: init( v8::Handle< v8::Object > target ) 
    {
     v8::Local<v8::FunctionTemplate> t = v8::FunctionTemplate::New(New);

	 // t-> GetFunction()-> Call( t->PrototypeTemplate(), 0, NULL   )
	 t-> Inherit( EventEmitterJS:: prototypeTemplate ) ;

   	 staticTextPrototypeTemplate = v8::Persistent<v8::FunctionTemplate>::New(t);
   	 staticTextPrototypeTemplate->InstanceTemplate()->SetInternalFieldCount(1);

   	 staticTextPrototypeTemplate->SetClassName(v8::String::NewSymbol("StaticText"));

         NODE_SET_PROTOTYPE_METHOD_BORROWED( staticTextPrototypeTemplate, "destroy", destroy ) ;


	 addStaticTextFunctionsToPrototype<StaticTextJS>( staticTextPrototypeTemplate ) ;
	}

v8::Handle<v8::Value> StaticTextJS:: New( const v8::Arguments& args ) 
    {
	
	 printf( "static text new \n") ;
		
	 EventEmitterJS:: prototypeTemplate-> GetFunction()-> Call( args.This(), 0, NULL ) ;
		
     return args.This() ;
    }


v8::Handle<v8::Value> StaticTextJS:: NewFromStaticTextCpp( MyGUI::StaticText* w ) 
    {
     v8::Local<v8::Function> function = StaticTextJS:: staticTextPrototypeTemplate-> GetFunction();
     v8::Handle<v8::Object>   object   = function->NewInstance();

     StaticTextJS* bindJS = new StaticTextJS() ;
     
     bindJS-> widget = w ;

	 bindJS-> initMyGuiEventEmitterJS( w ) ;


     bindJS-> Wrap( object ) ;

	 MemoryManagerJS:: singleton-> updateV8AllocatedMemory() ;

     return bindJS-> handle_ ;
    }



v8::Handle<v8::Value> StaticTextJS:: destroy( const v8::Arguments& args )
    {
	 StaticTextJS* bound = node::ObjectWrap::Unwrap<StaticTextJS>( args.This() ) ;

	 MyGUI::Gui::getInstance().destroyWidget( bound-> widget ) ;

	 MemoryManagerJS:: singleton-> updateV8AllocatedMemory() ;

	 return v8::Undefined() ;
	}



v8::Handle<v8::Value> StaticTextJS::setCaptionConvert( StaticTextJS* bound, const v8::Arguments& args ) 
	{
	 v8::String::AsciiValue ascii( args[ 0 ] ) ;
	
	 printf( "setCaptionConvert %s", *ascii ) ;

	 ( (MyGUI::StaticTextPtr) bound-> widget )-> setCaption( *ascii ) ;

	 return v8::Undefined() ;
	}