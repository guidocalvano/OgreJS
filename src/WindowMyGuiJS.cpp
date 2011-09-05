


#include <WindowMyGuiJS.h>
#include <MemoryManagerJS.h>
#include <EventEmitterJS.h>

v8::Persistent<v8::FunctionTemplate> WindowMyGuiJS:: windowMyGuiPrototypeTemplate ; 


void WindowMyGuiJS:: init( v8::Handle< v8::Object > target ) 
    {
     v8::Local<v8::FunctionTemplate> t = v8::FunctionTemplate::New(New);

	 // t-> GetFunction()-> Call( t->PrototypeTemplate(), 0, NULL   )
	 t-> Inherit( EventEmitterJS:: prototypeTemplate ) ;

   	 windowMyGuiPrototypeTemplate = v8::Persistent<v8::FunctionTemplate>::New(t);
   	 windowMyGuiPrototypeTemplate->InstanceTemplate()->SetInternalFieldCount(1);

   	 windowMyGuiPrototypeTemplate->SetClassName(v8::String::NewSymbol("StaticText"));

	 addWindowMyGuiFunctionsToPrototype<WindowMyGuiJS>( windowMyGuiPrototypeTemplate ) ;
	}

v8::Handle<v8::Value> WindowMyGuiJS:: New( const v8::Arguments& args ) 
    {
	
	 printf( "static text new \n") ;
		
	 EventEmitterJS:: prototypeTemplate-> GetFunction()-> Call( args.This(), 0, NULL ) ;
		
     return args.This() ;
    }


v8::Handle<v8::Value> WindowMyGuiJS:: NewFromWindowCpp( MyGUI::Window* w ) 
    {
     v8::Local<v8::Function> function = WindowMyGuiJS:: windowMyGuiPrototypeTemplate-> GetFunction();
     v8::Handle<v8::Object>   object   = function->NewInstance();

     WindowMyGuiJS* bindJS = new WindowMyGuiJS() ;
     
     bindJS-> widget = w ;

	 bindJS-> initMyGuiEventEmitterJS( w ) ;


     bindJS-> Wrap( object ) ;

	 MemoryManagerJS:: singleton-> updateV8AllocatedMemory() ;

     return bindJS-> handle_ ;
    }



v8::Handle<v8::Value> WindowMyGuiJS:: destroy( const v8::Arguments& args )
    {
	 WindowMyGuiJS* bound = node::ObjectWrap::Unwrap<WindowMyGuiJS>( args.This() ) ;

	 MyGUI::Gui::getInstance().destroyWidget( bound-> widget ) ;

	 MemoryManagerJS:: singleton-> updateV8AllocatedMemory() ;

	 return v8::Undefined() ;
	}

