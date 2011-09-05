#ifndef WIDGET_JS_H
#define WIDGET_JS_H




#include <MyGUI.h>
#include <MyGUI_OgrePlatform.h>
#include <node_object_wrap.h>
#include <WidgetCreatorConvertJS.h>

#include <WidgetConvertJS.h>

class WidgetBindJS : public node::ObjectWrap
    {
	public:	
	 static v8::Persistent<v8::FunctionTemplate> widgetPrototypeTemplate ;  

     MyGUI::Widget* widget ;
	
     static void init( v8::Handle< v8::Object > target ) ;
        
     static v8::Handle<v8::Value> New( const v8::Arguments& args )  ;
     
     static v8::Handle<v8::Value> NewFromWidgetCpp( MyGUI::Widget* widget ) ;


     static v8::Handle<v8::Value> createStaticText( const v8::Arguments& args ) ;

     static v8::Handle<v8::Value> createButton( const v8::Arguments& args ) ;

     static v8::Handle<v8::Value> createPanel( const v8::Arguments& args ) ;

	 static v8::Handle<v8::Value> destroy( const v8::Arguments& args ) ;
	
	
	 static v8::Handle<v8::Value> setPosition( const v8::Arguments& args ) ;

     static v8::Handle<v8::Value> setSize( const v8::Arguments& args ) ;
    } ;
    
#endif