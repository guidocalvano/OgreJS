
#ifndef BUTTON_BIND_JS_H
#define BUTTON_BIND_JS_H

#include <MyGUI.h>
#include <MyGUI_OgrePlatform.h>
#include <node_object_wrap.h>


class ButtonBindJS : public node::ObjectWrap
    {
    public:
     static void init( v8::Handle< v8::Object > target ) ;
        
     static v8::Handle<v8::Value> New( const v8::Arguments& args )  ;
     
     static v8::Handle<v8::Value> NewFromButtonCpp( MyGUI::Button* button ) ;

     static v8::Persistent<v8::FunctionTemplate> buttonPrototypeTemplate ;  

     MyGUI::Button* button ;
    
    } ;
    
#endif