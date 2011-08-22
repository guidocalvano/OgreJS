#include <WidgetBindJS.h>

v8::Persistent<v8::FunctionTemplate> WidgetBindJS:: widgetPrototypeTemplate ;

    
void WidgetBindJS:: init( v8::Handle< v8::Object > target ) 
    {
     v8::Local<v8::FunctionTemplate> t = v8::FunctionTemplate::New(New);

   	 widgetPrototypeTemplate = v8::Persistent<v8::FunctionTemplate>::New( t ) 	;
   	 widgetPrototypeTemplate-> InstanceTemplate()->SetInternalFieldCount( 1 ) 	;
   	 widgetPrototypeTemplate-> SetClassName(v8::String::NewSymbol( "Widget" ) ) ;
   	
     NODE_SET_PROTOTYPE_METHOD_BORROWED( widgetPrototypeTemplate, "createButton", createButton ) ;
     NODE_SET_PROTOTYPE_METHOD_BORROWED( widgetPrototypeTemplate, "createWidget", createWidget ) ;
    
     // target-> Set( v8::String::NewSymbol("root"), NewFromOgreManager() );
    }


v8::Handle<v8::Value> WidgetBindJS:: New( const v8::Arguments& args ) 
    {
     return args.This() ;
    }


v8::Handle<v8::Value> WidgetBindJS:: NewFromWidgetCpp( MyGUI::Widget* widget ) 
    {
     v8::Local<v8::Function> function = WidgetBindJS::widgetPrototypeTemplate-> GetFunction();
     v8::Local<v8::Object>   object   = function->NewInstance();

     WidgetBindJS* widgetJS = new WidgetBindJS() ;
     
     printf( "widgets assigned \n" ) ;
     widgetJS-> widget = widget ;

     widgetJS-> Wrap( object ) ;

     return object ;
    }


v8::Handle<v8::Value> WidgetBindJS:: createButton( const v8::Arguments& args )
    {
	 WidgetBindJS* bound = node::ObjectWrap::Unwrap<WidgetBindJS>( args.This() ) ;
    
	 return WidgetCreatorConvertJS:: createButton( bound-> widget, args ) ;
	}
	

v8::Handle<v8::Value> WidgetBindJS:: createWidget( const v8::Arguments& args )
    {
	 WidgetBindJS* bound = node::ObjectWrap::Unwrap<WidgetBindJS>( args.This() ) ;

	 return WidgetCreatorConvertJS:: createWidget( bound-> widget, args ) ;
	}

