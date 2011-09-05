
#include <MyGUI.h>
#include <MyGUI_OgrePlatform.h>
#include <OgreManager.h>
#include <WidgetCreatorJS.h>
#include <node_object_wrap.h>
#include <WidgetJS.h>
#include <ButtonJS.h>


class MyGuiRootJS : public node::ObjectWrap
    {
    public:
	 MyGUI::OgrePlatform* mPlatform ;
    	 MyGUI::Gui*          mGui      ;
  
     static void init( v8::Handle< v8::Object > target ) ;

     static v8::Handle<v8::Value> New( const v8::Arguments& args ) ;

     static v8::Handle<v8::Value> NewFromOgreManager() ;

     static v8::Persistent<v8::FunctionTemplate> myGuiRootPrototypeTemplate ;  


     static v8::Handle<v8::Value> createButton( const v8::Arguments& args ) ;

     static v8::Handle<v8::Value> createWidget( const v8::Arguments& args ) ;
     
     MyGuiRootJS() ;
     
     ~MyGuiRootJS() ;
     

    
    } ;