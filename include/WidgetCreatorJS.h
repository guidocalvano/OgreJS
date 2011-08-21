


#ifndef WIDGET_CREATOR_JS_H
#define WIDGET_CREATOR_JS_H

class WidgetJS ;

#include <MyGUI.h>
#include <MyGUI_OgrePlatform.h>
#include <v8.h>
#include <node_object_wrap.h>
#include <ButtonJS.h>
// #include <WidgetJS.h>


class WidgetCreatorJS
    {
    public:

     MyGUI::Widget* widgetCreator ;


   //  static v8::Handle<v8::Value> New( const v8::Arguments& args ) ;

     static void addMethodsToPrototypeTemplate( v8::Persistent<v8::FunctionTemplate> prototypeTemplate ) ;

     static v8::Handle<v8::Value> createButton( const v8::Arguments& args ) ;

     static v8::Handle<v8::Value> createWidget( const v8::Arguments& args ) ;

/*

     static v8::Handle<v8::Value> createStaticText( const v8::Arguments& args ) ;
     
     static v8::Handle<v8::Value> createEdit( const v8::Arguments& args ) ;  

     static v8::Handle<v8::Value> createEditStretch( const v8::Arguments& args ) ;  

     static v8::Handle<v8::Value> createWindow( const v8::Arguments& args ) ;  

*/
    } ;
    
#endif