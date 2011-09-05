
#ifndef BUTTON_BIND_JS_H
#define BUTTON_BIND_JS_H

#include <MyGUI.h>
#include <MyGUI_OgrePlatform.h>
#include <node_object_wrap.h>
#include <MyGuiEventEmitterBindJS.h>
#include <WidgetConvertJS.h>
#include <StaticTextBindJS.h>

class ButtonBindJS : public MyGuiEventEmitterBindJS
    {
    public:
     static void init( v8::Handle< v8::Object > target ) ;
        
     static v8::Handle<v8::Value> New( const v8::Arguments& args )  ;
     
     static v8::Handle<v8::Value> NewFromButtonCpp( MyGUI::Button* button ) ;

	 static v8::Handle<v8::Value> destroy( const v8::Arguments& args ) ;


	 static v8::Handle<v8::Value> setCaption( const v8::Arguments& args ) ;
	
	
	 static v8::Handle<v8::Value> setPosition( const v8::Arguments& args ) ;

     static v8::Handle<v8::Value> setSize( const v8::Arguments& args ) ;


	// virtual void mouseButtonPressed( MyGUI::Widget* _sender, int _left, int _top, MyGUI::MouseButton _id ) { MyGuiEventEmitterBindJS:: mouseButtonPressed( _sender, _left, _top, _id ) ; }

     static v8::Persistent<v8::FunctionTemplate> buttonPrototypeTemplate ;  


     MyGUI::Button* button ;	
    } ;
    
#endif