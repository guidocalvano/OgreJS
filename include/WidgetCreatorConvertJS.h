


#ifndef WIDGET_CREATOR_CONVERT_JS_H
#define WIDGET_CREATOR_CONVERT_JS_H

// class WidgetJS ;

#include <MyGUI.h>
#include <MyGUI_OgrePlatform.h>
#include <v8.h>
#include <node_object_wrap.h>
#include <ButtonBindJS.h>
// #include <WidgetJS.h>


class WidgetCreatorConvertJS
    {
    public:

     MyGUI::Widget* widgetCreator ;


   //  static v8::Handle<v8::Value> New( const v8::Arguments& args ) ;


     static v8::Handle<v8::Value> createButton( MyGUI::Widget* creator, const v8::Arguments& args ) ;

     static v8::Handle<v8::Value> createWidget( MyGUI::Widget* creator, const v8::Arguments& args ) ;

/*

     static v8::Handle<v8::Value> createStaticText( const v8::Arguments& args ) ;
     
     static v8::Handle<v8::Value> createEdit( const v8::Arguments& args ) ;  

     static v8::Handle<v8::Value> createEditStretch( const v8::Arguments& args ) ;  

     static v8::Handle<v8::Value> createWindow( const v8::Arguments& args ) ;  

*/
    } ;
    
#endif