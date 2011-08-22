#include <ButtonBindJS.h>

v8::Persistent<v8::FunctionTemplate> ButtonBindJS:: buttonPrototypeTemplate ;

    
void ButtonBindJS:: init( v8::Handle< v8::Object > target ) 
    {
     v8::Local<v8::FunctionTemplate> t = v8::FunctionTemplate::New(New);

   	buttonPrototypeTemplate = v8::Persistent<v8::FunctionTemplate>::New(t);
   	buttonPrototypeTemplate->InstanceTemplate()->SetInternalFieldCount(1);
   	buttonPrototypeTemplate->SetClassName(v8::String::NewSymbol("Gui"));
   	
   	// WidgetCreatorJS:: addMethodsToPrototypeTemplate( buttonPrototypeTemplate ) ;
    
     // target-> Set( v8::String::NewSymbol("root"), NewFromOgreManager() );
    }


v8::Handle<v8::Value> ButtonBindJS:: New( const v8::Arguments& args ) 
    {
     return args.This() ;
    }


v8::Handle<v8::Value> ButtonBindJS:: NewFromButtonCpp( MyGUI::Button* button ) 
    {
     v8::Local<v8::Function> function = ButtonBindJS::buttonPrototypeTemplate-> GetFunction();
     v8::Local<v8::Object>   object   = function->NewInstance();

     ButtonBindJS* buttonBindJS = new ButtonBindJS() ;
     
     buttonBindJS-> button = button ;

     buttonBindJS-> Wrap( object ) ;

     return object ;
    }