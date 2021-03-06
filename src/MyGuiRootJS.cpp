
#include <MyGuiRootJS.h>


v8::Persistent<v8::FunctionTemplate> MyGuiRootJS:: myGuiRootPrototypeTemplate ;


MyGuiRootJS :: MyGuiRootJS()
    {
    }

MyGuiRootJS :: ~MyGuiRootJS()
    {
    }



v8::Handle<v8::Value> MyGuiRootJS:: New( const v8::Arguments& args ) 
    {
    
    
      MyGuiRootJS* rootJS = new MyGuiRootJS() ;
    
      rootJS-> mPlatform = new MyGUI::OgrePlatform();
      rootJS-> mPlatform->initialise( OgreManager:: getSingletonPtr()-> m_pRenderWnd, OgreManager:: getSingletonPtr()-> m_pSceneMgr ) ; 
	 
      rootJS-> mGui = new MyGUI::Gui();
	 rootJS-> mGui-> initialise();
	 
      rootJS-> Wrap( args.This() ) ;

      return args.This() ;  

      /* del
 	 button = mGUI->createWidget<MyGUI::Button>("Button", 10, 10, 300, 26, MyGUI::Align::Default, "Main");
	 button->setCaption("exit");
	 */
    }

    
  
void MyGuiRootJS:: init( v8::Handle< v8::Object > target ) 
    {
     v8::Local<v8::FunctionTemplate> t = v8::FunctionTemplate::New(New);

   	myGuiRootPrototypeTemplate = v8::Persistent<v8::FunctionTemplate>::New(t);
   	myGuiRootPrototypeTemplate->InstanceTemplate()->SetInternalFieldCount(1);
   	myGuiRootPrototypeTemplate->SetClassName(v8::String::NewSymbol("Gui"));
   	
     NODE_SET_PROTOTYPE_METHOD_BORROWED( myGuiRootPrototypeTemplate, "createButton", createButton ) ;
     NODE_SET_PROTOTYPE_METHOD_BORROWED( myGuiRootPrototypeTemplate, "createWidget", createWidget ) ;
   
     WidgetJS::init( target ) ;
     ButtonJS::init( target ) ;
   
     target-> Set( v8::String::NewSymbol("root"), NewFromOgreManager() );
    }

v8::Handle<v8::Value> MyGuiRootJS:: NewFromOgreManager() 
    {
     v8::Local<v8::Function> function = MyGuiRootJS::myGuiRootPrototypeTemplate-> GetFunction();
     v8::Local<v8::Object>   object   = function->NewInstance();

     return object ;
    }
    
    

  
v8::Handle<v8::Value> MyGuiRootJS:: createButton( const v8::Arguments& args )
    {
     MyGuiRootJS* guiRootJs = node::ObjectWrap::Unwrap<MyGuiRootJS>( args.This() ) ;

     MyGUI::Gui* creator = guiRootJs-> mGui ;


     MyGUI::ButtonPtr buttonPtr = creator-> createWidget<MyGUI::Button>("Button", 10, 10, 300, 26, MyGUI::Align::Default, "Main") ;

     v8::Handle< v8::Value> buttonObject = ButtonJS::NewFromButtonCpp( buttonPtr ) ;

     return buttonObject ;
    }

v8::Handle<v8::Value> MyGuiRootJS:: createWidget( const v8::Arguments& args )
    {
     MyGuiRootJS* guiRootJs = node::ObjectWrap::Unwrap<MyGuiRootJS >( args.This() ) ;

     MyGUI::WidgetPtr widgetPtr = guiRootJs-> mGui-> createWidget<MyGUI::Widget>("Widget", 10, 10, 300, 26, MyGUI::Align::Default, "Main") ;
    
     v8::Handle< v8::Value> widgetObject = WidgetJS::NewFromWidgetCpp( widgetPtr ) ;
    
     return widgetObject ;
    }

