
#include <MyGuiRootBindJS.h>


v8::Persistent<v8::FunctionTemplate> MyGuiRootBindJS:: myGuiRootPrototypeTemplate ;


MyGuiRootBindJS :: MyGuiRootBindJS()
    {
    }

MyGuiRootBindJS :: ~MyGuiRootBindJS()
    {
    }



v8::Handle<v8::Value> MyGuiRootBindJS:: New( const v8::Arguments& args ) 
    {
    
    
      MyGuiRootBindJS* rootJS = new MyGuiRootBindJS() ;
    
      rootJS-> mPlatform = new MyGUI::OgrePlatform();
      rootJS-> mPlatform->initialise( OgreManager:: getSingletonPtr()-> m_pRenderWnd, OgreManager:: getSingletonPtr()-> m_pSceneMgr ) ; 
	 
      rootJS-> mGui = new MyGUI::Gui();
	  rootJS-> mGui-> initialise();

	  rootJS-> mInputManager = MyGUI::InputManager::getInstancePtr();
//	rootJS-> mInputManager-> initialise() ;
	
      rootJS-> Wrap( args.This() ) ;

      return args.This() ;  

      /* del
 	 button = mGUI->createWidget<MyGUI::Button>("Button", 10, 10, 300, 26, MyGUI::Align::Default, "Main");
	 button->setCaption("exit");
	 */
    }

    
  
void MyGuiRootBindJS:: init( v8::Handle< v8::Object > target ) 
    {
     v8::Local<v8::FunctionTemplate> t = v8::FunctionTemplate::New(New);

   	myGuiRootPrototypeTemplate = v8::Persistent<v8::FunctionTemplate>::New(t);
   	myGuiRootPrototypeTemplate->InstanceTemplate()->SetInternalFieldCount(1);
   	myGuiRootPrototypeTemplate->SetClassName(v8::String::NewSymbol("Gui"));
   	
     NODE_SET_PROTOTYPE_METHOD_BORROWED( myGuiRootPrototypeTemplate, "createButton", createButton ) ;
     NODE_SET_PROTOTYPE_METHOD_BORROWED( myGuiRootPrototypeTemplate, "createWidget", createWidget ) ;
   
     NODE_SET_PROTOTYPE_METHOD_BORROWED( myGuiRootPrototypeTemplate, "injectMouseMove", injectMouseMove ) ;
     NODE_SET_PROTOTYPE_METHOD_BORROWED( myGuiRootPrototypeTemplate, "injectMousePress", injectMousePress ) ;
     NODE_SET_PROTOTYPE_METHOD_BORROWED( myGuiRootPrototypeTemplate, "injectMouseRelease", injectMouseRelease ) ;

     NODE_SET_PROTOTYPE_METHOD_BORROWED( myGuiRootPrototypeTemplate, "injectKeyPress", injectKeyPress ) ;
     NODE_SET_PROTOTYPE_METHOD_BORROWED( myGuiRootPrototypeTemplate, "injectKeyRelease", injectKeyRelease ) ;


     WidgetBindJS::init( target ) ;
     ButtonBindJS::init( target ) ;
   
     target-> Set( v8::String::NewSymbol("root"), NewFromOgreManager() );
    }

v8::Handle<v8::Value> MyGuiRootBindJS:: NewFromOgreManager() 
    {
     v8::Local<v8::Function> function = MyGuiRootBindJS::myGuiRootPrototypeTemplate-> GetFunction();
     v8::Local<v8::Object>   object   = function->NewInstance();

     return object ;
    }
    
    

  
v8::Handle<v8::Value> MyGuiRootBindJS:: createButton( const v8::Arguments& args )
    {
     MyGuiRootBindJS* guiRootJs = node::ObjectWrap::Unwrap<MyGuiRootBindJS>( args.This() ) ;

     MyGUI::Gui* creator = guiRootJs-> mGui ;


     MyGUI::ButtonPtr buttonPtr = creator-> createWidget<MyGUI::Button>("Button", 10, 10, 300, 26, MyGUI::Align::Default, "Main") ;

     v8::Handle< v8::Value> buttonObject = ButtonBindJS::NewFromButtonCpp( buttonPtr ) ;

     return buttonObject ;
    }

v8::Handle<v8::Value> MyGuiRootBindJS:: createWidget( const v8::Arguments& args )
    {
     MyGuiRootBindJS* guiRootJs = node::ObjectWrap::Unwrap<MyGuiRootBindJS >( args.This() ) ;

     MyGUI::WidgetPtr widgetPtr = guiRootJs-> mGui-> createWidget<MyGUI::Widget>("Widget", 10, 10, 300, 26, MyGUI::Align::Default, "Main") ;
    
     v8::Handle< v8::Value> widgetObject = WidgetBindJS::NewFromWidgetCpp( widgetPtr ) ;
    
     return widgetObject ;
    }

v8::Handle<v8::Value> MyGuiRootBindJS:: injectMouseMove( const v8::Arguments& args )
	{
     MyGuiRootBindJS* guiRootJs = node::ObjectWrap::Unwrap<MyGuiRootBindJS >( args.This() ) ;

	 int x = ( v8::Local< v8::Number >::Cast( args[ 0 ] ) )-> Value() ;
	 int y = ( v8::Local< v8::Number >::Cast( args[ 1 ] ) )-> Value() ;
	 int z = ( v8::Local< v8::Number >::Cast( args[ 2 ] ) )-> Value() ;

	 MyGUI::InputManager::getInstancePtr()-> injectMouseMove( x, y, z ) ;
	
	 return v8:: Undefined() ;
	}


v8::Handle<v8::Value> MyGuiRootBindJS:: injectMousePress( const v8::Arguments& args )
	{
     MyGuiRootBindJS* guiRootJs = node::ObjectWrap::Unwrap<MyGuiRootBindJS >( args.This() ) ;

	 int x = ( v8::Local< v8::Number >::Cast( args[ 0 ] ) )-> Value() ;
	 int y = ( v8::Local< v8::Number >::Cast( args[ 1 ] ) )-> Value() ;

	 MyGUI::InputManager::getInstancePtr()->  injectMousePress( x, y, MyGUI::MouseButton::Enum( OIS::MB_Left ) ) ;
	
	 return v8:: Undefined() ;
	}


v8::Handle<v8::Value> MyGuiRootBindJS:: injectMouseRelease( const v8::Arguments& args )
	{
     MyGuiRootBindJS* guiRootJs = node::ObjectWrap::Unwrap<MyGuiRootBindJS >( args.This() ) ;

	 int x = ( v8::Local< v8::Number >::Cast( args[ 0 ] ) )-> Value() ;
	 int y = ( v8::Local< v8::Number >::Cast( args[ 1 ] ) )-> Value() ;

	 MyGUI::InputManager::getInstancePtr()->  injectMouseRelease( x, y, MyGUI::MouseButton::Enum( OIS::MB_Left ) ) ;

	 return v8:: Undefined() ;
	}





v8::Handle<v8::Value> MyGuiRootBindJS:: injectKeyPress( const v8::Arguments& args )
	{
     MyGuiRootBindJS* guiRootJs = node::ObjectWrap::Unwrap<MyGuiRootBindJS >( args.This() ) ;

	 int 			code 	= (int) 			( v8::Local< v8::Integer >::Cast( args[ 0 ] ) )-> Value() ;
	 unsigned int 	chr 	= (unsigned int) 	( v8::Local< v8::Integer >::Cast( args[ 1 ] ) )-> Value() ;

	 MyGUI::InputManager::getInstancePtr()->  injectKeyPress( (MyGUI::KeyCode::Enum) code, chr ) ;

	 return v8:: Undefined() ;
	}


v8::Handle<v8::Value> MyGuiRootBindJS:: injectKeyRelease( const v8::Arguments& args )
	{
     MyGuiRootBindJS* guiRootJs = node::ObjectWrap::Unwrap<MyGuiRootBindJS >( args.This() ) ;

	 int code = (int) ( v8::Local< v8::Integer >::Cast( args[ 0 ] ) )-> Value() ;

	 MyGUI::InputManager::getInstancePtr()->  injectKeyRelease( (MyGUI::KeyCode::Enum) code ) ;

	 return v8:: Undefined() ;
	}



