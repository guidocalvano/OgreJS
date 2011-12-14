#ifndef STATIC_TEXT_JS
#define STATIC_TEXT_JS

#include <WidgetJS.h>


class StaticTextJS : public WidgetJS
	{
	public:
     static v8::Persistent<v8::FunctionTemplate> staticTextPrototypeTemplate ;  

	
	 static	void init( v8::Handle< v8::Object > target ) ;
	
	
	 static v8::Handle<v8::Value> New( const v8::Arguments& args ) ;
	
     static v8::Handle<v8::Value> NewFromStaticTextCpp( MyGUI::StaticText* button ) ;
	 
	 static v8::Handle<v8::Value> destroy( const v8::Arguments& args ) ;

	 template< class ChildType >
	 static void addStaticTextFunctionsToPrototype( v8::Handle<v8::FunctionTemplate> t )
		{
	     	 NODE_SET_PROTOTYPE_METHOD_BORROWED( t, "setCaption", setCaptionBind<ChildType> ) ;	
	
		 addSpatialFunctions< ChildType >( t ) ;
		}

	 static v8::Handle<v8::Value> setCaptionConvert( StaticTextJS* bound, const v8::Arguments& args ) ;

	 template< class ChildType >
	 static v8::Handle<v8::Value> setCaptionBind( const v8::Arguments& args )
		{
		 StaticTextJS* bound = (StaticTextJS*) ( node::ObjectWrap::Unwrap<ChildType>( args.This() ) ) ;
		
		 setCaptionConvert( bound, args ) ;	
		}

	
	
	
	
	
	
	} ;
	
#endif