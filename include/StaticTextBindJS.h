#ifndef STATIC_TEXT_JS_H
#define STATIC_TEXT_JS_H




#include <MyGUI.h>
#include <MyGUI_OgrePlatform.h>
#include <node_object_wrap.h>
#include <WidgetConvertJS.h>
#include <MyGuiEventEmitterBindJS.h>


class StaticTextBindJS : public MyGuiEventEmitterBindJS
	{
	public:
	
	 static	void init( v8::Handle< v8::Object > target ) ;
	
	
	 static v8::Handle<v8::Value> New( const v8::Arguments& args ) ;
	
     static v8::Handle<v8::Value> NewFromStaticTextCpp( MyGUI::StaticText* button ) ;
	 
	 static v8::Handle<v8::Value> destroy( const v8::Arguments& args ) ;


	 static v8::Handle<v8::Value> setCaption( const v8::Arguments& args ) ;

	 static v8::Handle<v8::Value> setCaption( MyGUI::StaticText* staticText, const v8::Arguments& args ) ;
	
	
	 static v8::Handle<v8::Value> setPosition( const v8::Arguments& args ) ;

     static v8::Handle<v8::Value> setSize( const v8::Arguments& args ) ;


     static v8::Persistent<v8::FunctionTemplate> prototypeTemplate ;  

     MyGUI::StaticText* staticText ;	
	} ;
	
	
#endif