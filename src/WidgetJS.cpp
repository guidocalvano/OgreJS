#include <WidgetJS.h>
#include <MemoryManagerJS.h>
#include <EventEmitterJS.h>

#include <ButtonJS.h>
#include <StaticTextJS.h>
#include <EditJS.h>
#include <WindowMyGuiJS.h>

v8::Persistent<v8::FunctionTemplate> WidgetJS:: widgetPrototypeTemplate ;

    
void WidgetJS:: init( v8::Handle< v8::Object > target ) 
    {
     v8::Local<v8::FunctionTemplate> t = v8::FunctionTemplate::New(New);

	 t-> Inherit( EventEmitterJS:: prototypeTemplate ) ;

   	 widgetPrototypeTemplate = v8::Persistent<v8::FunctionTemplate>::New( t ) 	;
   	 widgetPrototypeTemplate-> InstanceTemplate()->SetInternalFieldCount( 1 ) 	;
   	 widgetPrototypeTemplate-> SetClassName(v8::String::NewSymbol( "Widget" ) ) ;

         NODE_SET_PROTOTYPE_METHOD_BORROWED( widgetPrototypeTemplate, "destroy", destroy ) ;

	 addSpatialFunctions<WidgetJS>( widgetPrototypeTemplate ) ;
	 addCreateFunctions<WidgetJS>(  widgetPrototypeTemplate ) ;    
     // target-> Set( v8::String::NewSymbol("root"), NewFromOgreManager() );
    }


v8::Handle<v8::Value> WidgetJS:: New( const v8::Arguments& args ) 
    {
     return args.This() ;
    }


v8::Handle<v8::Value> WidgetJS:: NewFromWidgetCpp( MyGUI::Widget* w ) 
    {
     v8::Local<v8::Function> function = WidgetJS::widgetPrototypeTemplate-> GetFunction();
     v8::Local<v8::Object>   object   = function->NewInstance();

     WidgetJS* bindJS = new WidgetJS() ;
     
     printf( "widgets assigned \n" ) ;
     bindJS-> widget = w ;

     EventEmitterJS:: prototypeTemplate-> GetFunction()-> Call( object, 0, NULL ) ;

	// bindJS-> initMyGuiEventEmitterJS( w ) ;

     bindJS-> Wrap( object ) ;
	 MemoryManagerJS:: singleton-> updateV8AllocatedMemory() ;

     return object ;
    }


v8::Handle<v8::Value> WidgetJS:: destroy( const v8::Arguments& args )
    {
	 WidgetJS* bound = node::ObjectWrap::Unwrap<WidgetJS>( args.This() ) ;

	 MyGUI::Gui::getInstance().destroyWidget( bound-> widget ) ;
	
	 MemoryManagerJS:: singleton-> updateV8AllocatedMemory() ;

	 return v8::Undefined() ;
	}



v8::Handle<v8::Value> WidgetJS:: focusConvert( WidgetJS* bound, const v8::Arguments& args ) 
	{
	 MyGUI::InputManager::getInstancePtr()-> setKeyFocusWidget( bound-> widget ) ;
	 return v8::Undefined() ;
	}



v8::Handle<v8::Value> WidgetJS:: blurConvert( WidgetJS* bound, const v8::Arguments& args ) 
	{
	 MyGUI::InputManager::getInstancePtr()-> resetKeyFocusWidget( bound-> widget ) ;
	 return v8::Undefined() ;
	}


v8::Handle<v8::Value> WidgetJS:: setPositionConvert( WidgetJS* bound, const v8::Arguments& args ) 
	{
	 int x = args[ 0 ]-> ToInteger()-> Value() ;
	 int y = args[ 1 ]-> ToInteger()-> Value() ;

	 bound-> widget-> setPosition( x, y ) ;
	 return v8::Undefined() ;
	}



v8::Handle<v8::Value> WidgetJS:: setSizeConvert( WidgetJS* bound, const v8::Arguments& args ) 
	{
	 int width  = args[ 0 ]-> ToInteger()-> Value() ;
	 int height = args[ 1 ]-> ToInteger()-> Value() ;

	 bound-> widget-> setSize( width, height ) ;

	 return v8::Undefined() ;
	}





v8::Handle<v8::Value> WidgetJS:: createStaticTextConvert( WidgetJS* bound, const v8::Arguments& args ) 
	{
	  int x 		= args[0]-> ToInteger()-> Value() ;
	  int y 		= args[1]-> ToInteger()-> Value() ;
	  int width  	= args[2]-> ToInteger()-> Value() ;
	  int height 	= args[3]-> ToInteger()-> Value() ;

      MyGUI::StaticTextPtr widgetPtr = bound-> widget-> createWidget<MyGUI::StaticText>("Button", x, y, width, height, MyGUI::Align::Default, bound-> widget-> getLayer()-> getName() ) ;

      v8::Handle< v8::Value> object = StaticTextJS::NewFromStaticTextCpp( widgetPtr ) ;

      return object ;		
	}


v8::Handle<v8::Value> WidgetJS:: createButtonConvert( WidgetJS* bound, const v8::Arguments& args ) 
	{
	  int x 		= args[0]-> ToInteger()-> Value() ;
	  int y 		= args[1]-> ToInteger()-> Value() ;
	  int width  	= args[2]-> ToInteger()-> Value() ;
	  int height 	= args[3]-> ToInteger()-> Value() ;

      MyGUI::ButtonPtr widgetPtr = bound-> widget-> createWidget<MyGUI::Button>("Button", x, y, width, height, MyGUI::Align::Default, bound-> widget-> getLayer()-> getName() ) ;

      v8::Handle< v8::Value> object = ButtonJS::NewFromButtonCpp( widgetPtr ) ;

      return object ;
	}


v8::Handle<v8::Value> WidgetJS:: createEditConvert( WidgetJS* bound, const v8::Arguments& args ) 
	{
	  int x 		= args[0]-> ToInteger()-> Value() ;
	  int y 		= args[1]-> ToInteger()-> Value() ;
	  int width  	= args[2]-> ToInteger()-> Value() ;
	  int height 	= args[3]-> ToInteger()-> Value() ;

      MyGUI::EditPtr widgetPtr = bound-> widget-> createWidget<MyGUI::Edit>("Edit", x, y, width, height, MyGUI::Align::Default, bound-> widget-> getLayer()-> getName() ) ;

      v8::Handle< v8::Value> object = EditJS::NewFromEditCpp( widgetPtr ) ;

      return object ;
	}



v8::Handle<v8::Value> WidgetJS:: createPanelConvert( WidgetJS* bound, const v8::Arguments& args ) 
	{
	  int x 		= args[0]-> ToInteger()-> Value() ;
	  int y 		= args[1]-> ToInteger()-> Value() ;
	  int width  	= args[2]-> ToInteger()-> Value() ;
	  int height 	= args[3]-> ToInteger()-> Value() ;

      MyGUI::WidgetPtr widgetPtr = bound-> widget-> createWidget<MyGUI::Widget>("Panel", x, y, width, height, MyGUI::Align::Default, bound-> widget-> getLayer()-> getName() ) ;

      v8::Handle< v8::Value> object = WidgetJS::NewFromWidgetCpp( widgetPtr ) ;

      return object ;
	}


v8::Handle<v8::Value> WidgetJS:: createWindowConvert( WidgetJS* bound, const v8::Arguments& args ) 
	{
	  int x 		= args[0]-> ToInteger()-> Value() ;
	  int y 		= args[1]-> ToInteger()-> Value() ;
	  int width  	= args[2]-> ToInteger()-> Value() ;
	  int height 	= args[3]-> ToInteger()-> Value() ;

      MyGUI::WindowPtr widgetPtr = bound-> widget-> createWidget<MyGUI::Window>("Window", x, y, width, height, MyGUI::Align::Default, bound-> widget-> getLayer()-> getName() ) ;

      v8::Handle< v8::Value> object = WindowMyGuiJS::NewFromWindowCpp( widgetPtr ) ;

      return object ;
	}

