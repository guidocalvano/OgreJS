
#include <LayerJS.h>
/*
#include <ButtonBindJS.h>
#include <WidgetBindJS.h>
#include <StaticTextBindJS.h>
*/

#include <ButtonJS.h>
#include <EditJS.h>
#include <WidgetJS.h>
#include <StaticTextJS.h>
#include <WindowMyGuiJS.h>

#include <MemoryManagerJS.h>

#include <string.h>
#include <MyGuiJS.h>

v8::Persistent<v8::FunctionTemplate> LayerJS:: layerPrototypeTemplate ;




LayerJS:: LayerJS( const char* layerName ) 
	{
	 this-> layerName = new char[ std::strlen( layerName ) + 1 ] ;
	
	 std::strcpy( this-> layerName, layerName ) ;
	}




void LayerJS:: init( v8::Handle< v8::Object > target ) 
	{
	 v8::Local<v8::FunctionTemplate> t = v8::FunctionTemplate::New(New);

	 layerPrototypeTemplate = v8::Persistent<v8::FunctionTemplate>::New( t ) 	;
	 layerPrototypeTemplate-> InstanceTemplate()->SetInternalFieldCount( 1 ) 	;
	 layerPrototypeTemplate-> SetClassName(v8::String::NewSymbol( "Layer" ) ) ;


	 NODE_SET_PROTOTYPE_METHOD_BORROWED( layerPrototypeTemplate, "createStaticText", createStaticText ) ;
	 NODE_SET_PROTOTYPE_METHOD_BORROWED( layerPrototypeTemplate, "createButton", createButton ) ;
	 NODE_SET_PROTOTYPE_METHOD_BORROWED( layerPrototypeTemplate, "createPanel", createPanel ) ;
	 NODE_SET_PROTOTYPE_METHOD_BORROWED( layerPrototypeTemplate, "createEdit", createEdit ) ;
	 NODE_SET_PROTOTYPE_METHOD_BORROWED( layerPrototypeTemplate, "createWindow", createWindow ) ;
	
	}
	
	

v8::Handle<v8::Value> LayerJS:: New( const v8::Arguments& args ) 
    {
     return args.This() ;
    }


v8::Handle<v8::Value> LayerJS:: NewFromLayerName( const char* layerName ) 
    {
     v8::Local<v8::Function> function = LayerJS::layerPrototypeTemplate-> GetFunction();
     v8::Local<v8::Object>   object   = function->NewInstance();

     LayerJS* layerJS = new LayerJS( layerName) ;

     layerJS-> Wrap( object ) ;

	 MemoryManagerJS:: singleton-> updateV8AllocatedMemory() ;

     return object ;
    }


v8::Handle<v8::Value> LayerJS:: createStaticText( const v8::Arguments& args )
    {
	 LayerJS* bound = node::ObjectWrap::Unwrap<LayerJS>( args.This() ) ;


	 int x 		= args[0]-> ToInteger()-> Value() ;
	 int y 		= args[1]-> ToInteger()-> Value() ;
	 int width  = args[2]-> ToInteger()-> Value() ;
	 int height = args[3]-> ToInteger()-> Value() ;

     MyGUI::StaticTextPtr staticTextPtr = MyGuiJS:: singleton-> mGui-> createWidget<MyGUI::StaticText>("Button", x, y, width, height, MyGUI::Align::Default, bound-> layerName ) ;

     v8::Handle< v8::Value> object = StaticTextJS::NewFromStaticTextCpp( staticTextPtr ) ;

     return object ;
	}




v8::Handle<v8::Value> LayerJS:: createButton( const v8::Arguments& args )
    {
	 LayerJS* bound = node::ObjectWrap::Unwrap<LayerJS>( args.This() ) ;


	 int x 		= args[0]-> ToInteger()-> Value() ;
	 int y 		= args[1]-> ToInteger()-> Value() ;
	 int width  = args[2]-> ToInteger()-> Value() ;
	 int height = args[3]-> ToInteger()-> Value() ;

     MyGUI::ButtonPtr buttonPtr = MyGuiJS:: singleton-> mGui-> createWidget<MyGUI::Button>("Button", x, y, width, height, MyGUI::Align::Default, bound-> layerName ) ;

     v8::Handle< v8::Value> object = ButtonJS::NewFromButtonCpp( buttonPtr ) ;

     return object ;	 
	}




v8::Handle<v8::Value> LayerJS:: createEdit( const v8::Arguments& args )
    {
	 LayerJS* bound = node::ObjectWrap::Unwrap<LayerJS>( args.This() ) ;


	 int x 		= args[0]-> ToInteger()-> Value() ;
	 int y 		= args[1]-> ToInteger()-> Value() ;
	 int width  = args[2]-> ToInteger()-> Value() ;
	 int height = args[3]-> ToInteger()-> Value() ;

     MyGUI::EditPtr widgetPtr = MyGuiJS:: singleton-> mGui-> createWidget<MyGUI::Edit>("EditBox", x, y, width, height, MyGUI::Align::Default, bound-> layerName ) ;

     v8::Handle< v8::Value> object = EditJS::NewFromEditCpp( widgetPtr ) ;

     return object ;	 
	}


v8::Handle<v8::Value> LayerJS:: createPanel( const v8::Arguments& args )
    {
	 LayerJS* bound = node::ObjectWrap::Unwrap<LayerJS>( args.This() ) ;


	 int x 		= args[0]-> ToInteger()-> Value() ;
	 int y 		= args[1]-> ToInteger()-> Value() ;
	 int width  = args[2]-> ToInteger()-> Value() ;
	 int height = args[3]-> ToInteger()-> Value() ;

     MyGUI::WidgetPtr widgetPtr = MyGuiJS:: singleton-> mGui-> createWidget<MyGUI::Widget>("Panel", x, y, width, height, MyGUI::Align::Default, bound-> layerName ) ;

     v8::Handle< v8::Value> object = WidgetJS::NewFromWidgetCpp( widgetPtr ) ;

     return object ;
	}


v8::Handle<v8::Value> LayerJS:: createWindow( const v8::Arguments& args )
    {
	 LayerJS* bound = node::ObjectWrap::Unwrap<LayerJS>( args.This() ) ;


	 int x 		= args[0]-> ToInteger()-> Value() ;
	 int y 		= args[1]-> ToInteger()-> Value() ;
	 int width  = args[2]-> ToInteger()-> Value() ;
	 int height = args[3]-> ToInteger()-> Value() ;

     MyGUI::WindowPtr widgetPtr = MyGuiJS:: singleton-> mGui-> createWidget<MyGUI::Window>("Window", x, y, width, height, MyGUI::Align::Default, bound-> layerName ) ;

     v8::Handle< v8::Value> object = WindowMyGuiJS::NewFromWindowCpp( widgetPtr ) ;

     return object ;
	}
