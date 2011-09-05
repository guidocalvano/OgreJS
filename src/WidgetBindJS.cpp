#include <WidgetBindJS.h>
#include <MemoryManagerJS.h>
v8::Persistent<v8::FunctionTemplate> WidgetBindJS:: widgetPrototypeTemplate ;

    
void WidgetBindJS:: init( v8::Handle< v8::Object > target ) 
    {
     v8::Local<v8::FunctionTemplate> t = v8::FunctionTemplate::New(New);

   	 widgetPrototypeTemplate = v8::Persistent<v8::FunctionTemplate>::New( t ) 	;
   	 widgetPrototypeTemplate-> InstanceTemplate()->SetInternalFieldCount( 1 ) 	;
   	 widgetPrototypeTemplate-> SetClassName(v8::String::NewSymbol( "Widget" ) ) ;
   	
     NODE_SET_PROTOTYPE_METHOD_BORROWED( widgetPrototypeTemplate, "destroy", destroy ) ;

     NODE_SET_PROTOTYPE_METHOD_BORROWED( widgetPrototypeTemplate, "createStaticText", createStaticText ) ;
     NODE_SET_PROTOTYPE_METHOD_BORROWED( widgetPrototypeTemplate, "createButton", createButton ) ;
     NODE_SET_PROTOTYPE_METHOD_BORROWED( widgetPrototypeTemplate, "createPanel", createPanel ) ;
    
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

	 MemoryManagerJS:: singleton-> updateV8AllocatedMemory() ;

     return object ;
    }



v8::Handle<v8::Value> WidgetBindJS:: createStaticText( const v8::Arguments& args )
    {
	 WidgetBindJS* bound = node::ObjectWrap::Unwrap<WidgetBindJS>( args.This() ) ;

	 return WidgetCreatorConvertJS:: createStaticText( bound-> widget, args ) ;
	}




v8::Handle<v8::Value> WidgetBindJS:: createButton( const v8::Arguments& args )
    {
	 WidgetBindJS* bound = node::ObjectWrap::Unwrap<WidgetBindJS>( args.This() ) ;
    
	 return WidgetCreatorConvertJS:: createButton( bound-> widget, args ) ;
	}
	

v8::Handle<v8::Value> WidgetBindJS:: createPanel( const v8::Arguments& args )
    {
	 WidgetBindJS* bound = node::ObjectWrap::Unwrap<WidgetBindJS>( args.This() ) ;

	 return WidgetCreatorConvertJS:: createPanel( bound-> widget, args ) ;
	}


v8::Handle<v8::Value> WidgetBindJS:: destroy( const v8::Arguments& args )
    {
	 WidgetBindJS* bound = node::ObjectWrap::Unwrap<WidgetBindJS>( args.This() ) ;

	 v8::Handle<v8::Value> val = WidgetConvertJS:: destroy( bound-> widget, args ) ;
	
	 MemoryManagerJS:: singleton-> updateV8AllocatedMemory() ;
	
	 return val ;
	}
	
	
	

v8::Handle<v8::Value> WidgetBindJS:: setPosition( const v8::Arguments& args )
    {
	 WidgetBindJS* bound = node::ObjectWrap::Unwrap<WidgetBindJS>( args.This() ) ;

	 return WidgetConvertJS:: setPosition( bound-> widget, args ) ;
	}


v8::Handle<v8::Value> WidgetBindJS:: setSize( const v8::Arguments& args )
    {
	 WidgetBindJS* bound = node::ObjectWrap::Unwrap<WidgetBindJS>( args.This() ) ;

	 return WidgetConvertJS:: setSize( bound-> widget, args ) ;
	}
