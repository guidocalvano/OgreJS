#ifndef WIDGET_JS_H
#define WIDGET_JS_H




#include <MyGUI.h>
#include <MyGUI_OgrePlatform.h>
#include <node_object_wrap.h>
#include <WidgetCreatorJS.h>



class WidgetJS : public  WidgetCreatorJS, node::ObjectWrap
    {
    public:
     static void init( v8::Handle< v8::Object > target ) ;
        
     static v8::Handle<v8::Value> New( const v8::Arguments& args )  ;
     
     static v8::Handle<v8::Value> NewFromWidgetCpp( MyGUI::Widget* widget ) ;

     static v8::Persistent<v8::FunctionTemplate> widgetPrototypeTemplate ;  
     
     MyGUI::Widget* widget ;
    } ;
    
#endif