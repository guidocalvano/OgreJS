#include <EditJS.h>
#include <EventEmitterJS.h>
#include <MemoryManagerJs.h>


v8::Persistent<v8::FunctionTemplate> EditJS:: editPrototypeTemplate ;

    
void EditJS:: init( v8::Handle< v8::Object > target ) 
    {
     v8::Local<v8::FunctionTemplate> t = v8::FunctionTemplate::New(New);

	 t-> Inherit( EventEmitterJS:: prototypeTemplate ) ;

   	 editPrototypeTemplate = v8::Persistent<v8::FunctionTemplate>::New(t);
   	 editPrototypeTemplate->InstanceTemplate()->SetInternalFieldCount(1);
   	 editPrototypeTemplate->SetClassName(v8::String::NewSymbol("Edit"));

     NODE_SET_PROTOTYPE_METHOD_BORROWED( editPrototypeTemplate, "destroy", destroy ) ;

	addEditFunctionsToPrototype<EditJS>( editPrototypeTemplate ) ;
    }


v8::Handle<v8::Value> EditJS:: New( const v8::Arguments& args ) 
    {
	 EventEmitterJS:: prototypeTemplate-> GetFunction()-> Call( args.This(), 0, NULL ) ;	
	
     return args.This() ;
    }


v8::Handle<v8::Value> EditJS:: NewFromEditCpp( MyGUI::Edit* w ) 
    {
     v8::Local<v8::Function> function = EditJS::editPrototypeTemplate-> GetFunction();
     v8::Local<v8::Object>   object   = function->NewInstance();

     EditJS* bindJS = new EditJS() ;
     
     bindJS-> widget = w ;

	 bindJS-> initMyGuiEventEmitterJS( w ) ;

     bindJS-> Wrap( object ) ;

	 MemoryManagerJS:: singleton-> updateV8AllocatedMemory() ;


     return object ;
    }




v8::Handle<v8::Value> EditJS:: destroy( const v8::Arguments& args )
    {
	 EditJS* bound = node::ObjectWrap::Unwrap<EditJS>( args.This() ) ;

	 MyGUI::Gui::getInstance().destroyWidget( bound-> widget ) ;

	 MemoryManagerJS:: singleton-> updateV8AllocatedMemory() ;

	 return v8::Undefined() ;
	}
