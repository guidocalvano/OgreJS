#include <WidgetJS.h>

class WidgetCreatorJS ;

    
void WidgetJS:: init( v8::Handle< v8::Object > target ) 
    {
     v8::Local<v8::FunctionTemplate> t = v8::FunctionTemplate::New(New);

   	widgetPrototypeTemplate = v8::Persistent<v8::FunctionTemplate>::New(t);
   	widgetPrototypeTemplate-> InstanceTemplate()->SetInternalFieldCount(1);
   	widgetPrototypeTemplate-> SetClassName(v8::String::NewSymbol("Gui"));
   	
   	 // WidgetCreatorJS<MyGUI::Widget>:: addMethodsToPrototypeTemplate( widgetPrototypeTemplate ) ;
    
     // target-> Set( v8::String::NewSymbol("root"), NewFromOgreManager() );
    }


v8::Handle<v8::Value> WidgetJS:: New( const v8::Arguments& args ) 
    {
     return args.This() ;
    }


v8::Handle<v8::Value> WidgetJS:: NewFromWidgetCpp( MyGUI::Widget* widget ) 
    {
     v8::Local<v8::Function> function = WidgetJS::widgetPrototypeTemplate-> GetFunction();
     v8::Local<v8::Object>   object   = function->NewInstance();

     WidgetJS* widgetJS = new WidgetJS() ;
     
     widgetJS-> widget = widget ;

     widgetJS-> Wrap( object ) ;

     return object ;
    }