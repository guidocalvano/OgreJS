#include <ButtonJS.h>
#include <EventEmitterJS.h>
#include <MemoryManagerJs.h>


v8::Persistent<v8::FunctionTemplate> ButtonJS:: buttonPrototypeTemplate ;

    
void ButtonJS:: init( v8::Handle< v8::Object > target ) 
    {
     v8::Local<v8::FunctionTemplate> t = v8::FunctionTemplate::New(New);

	 t-> Inherit( EventEmitterJS:: prototypeTemplate ) ;

   	 buttonPrototypeTemplate = v8::Persistent<v8::FunctionTemplate>::New(t);
   	 buttonPrototypeTemplate->InstanceTemplate()->SetInternalFieldCount(1);
   	 buttonPrototypeTemplate->SetClassName(v8::String::NewSymbol("Button"));

     NODE_SET_PROTOTYPE_METHOD_BORROWED( buttonPrototypeTemplate, "destroy", destroy ) ;

	addButtonFunctionsToPrototype<ButtonJS>( buttonPrototypeTemplate ) ;
    }


v8::Handle<v8::Value> ButtonJS:: New( const v8::Arguments& args ) 
    {
	 EventEmitterJS:: prototypeTemplate-> GetFunction()-> Call( args.This(), 0, NULL ) ;	
	
     return args.This() ;
    }


v8::Handle<v8::Value> ButtonJS:: NewFromButtonCpp( MyGUI::Button* w ) 
    {
     v8::Local<v8::Function> function = ButtonJS::buttonPrototypeTemplate-> GetFunction();
     v8::Local<v8::Object>   object   = function->NewInstance();

     ButtonJS* bindJS = new ButtonJS() ;
     
     bindJS-> widget = w ;

	 bindJS-> initMyGuiEventEmitterJS( w ) ;

     bindJS-> Wrap( object ) ;

	 MemoryManagerJS:: singleton-> updateV8AllocatedMemory() ;


     return object ;
    }




v8::Handle<v8::Value> ButtonJS:: destroy( const v8::Arguments& args )
    {
	 ButtonJS* bound = node::ObjectWrap::Unwrap<ButtonJS>( args.This() ) ;

	 MyGUI::Gui::getInstance().destroyWidget( bound-> widget ) ;

	 MemoryManagerJS:: singleton-> updateV8AllocatedMemory() ;

	 return v8::Undefined() ;
	}
