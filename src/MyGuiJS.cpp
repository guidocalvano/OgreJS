#include <MyGuiJS.h>

#include <OgreManager.h>

#include <LayerJS.h>
#include <WidgetJS.h>
#include <StaticTextJS.h>
#include <ButtonJS.h>
#include <EditJS.h>
#include <WindowMyGuiJS.h>

#include <InputMyGuiJS.h>


#include <fstream>
#include <sstream>
#include <string>

#include <iostream>


using namespace std;

MyGuiJS* MyGuiJS::singleton = NULL ;

MyGuiJS :: MyGuiJS() 	
	{
	 mPlatform	= new MyGUI::OgrePlatform();
	 mPlatform-> initialise( OgreManager:: getSingletonPtr()-> m_pRenderWnd, OgreManager:: getSingletonPtr()-> m_pSceneMgr ) ; 
	 mGui		= new MyGUI::Gui();
	 mGui-> initialise();
		
	// pickingManagerJS = new PickingManagerJS() ;
	}

void MyGuiJS:: require( v8::Handle< v8::Object > target ) 
    {	
	 singleton = new MyGuiJS() ;
/*
 	 v8::HandleScope handle_scope;

	 v8::Persistent<v8::Context> context = v8::Context::New();

 	 v8::Context::Scope context_scope(context);
*/
 	 v8::Handle<v8::Object> system = v8::Object::New() ;
 	 v8::Handle<v8::Object> layerSet = v8::Object::New() ;

     system-> Set( v8::String::NewSymbol("layerSet"), layerSet ) ;

 	 LayerJS::init( 		system ) ;


     WidgetJS::init( 		system ) ;
     ButtonJS::init( 		system ) ;
     StaticTextJS::init( 	system ) ;

     EditJS::init( 			system ) ;
     WindowMyGuiJS::init( 	system ) ;

/*
     WidgetBindJS::init( system ) ;
     ButtonBindJS::init( system ) ;
     StaticTextBindJS::init( system ) ;
*/
	 MyGUI::Enumerator<std::vector<MyGUI::ILayer*, std::allocator<MyGUI::ILayer*> > > layerEnumerator = MyGUI::LayerManager::getInstancePtr()-> getEnumerator() ;

	 while( layerEnumerator.next() )
		{
		 const std::string layerName = layerEnumerator.current()-> getName() ;
		 layerSet-> Set( v8::String::NewSymbol( layerName.c_str() ), LayerJS:: NewFromLayerName ( layerName.c_str() ) ) ; 
		}


//		 layerSet-> Set( v8::String::NewSymbol( "Main" ), createRoot( "Main" ) ) ; 


     // system-> Set( v8::String::NewSymbol("root"), createRoot() ) ;
     system-> Set( v8::String::NewSymbol("input"), InputMyGuiJS:: createInput() ) ;

	 target-> Set( v8::String::New("system"), system ) ;
//	 target-> Set( v8::String::New("exports"), target ) ;
/*
 	 ifstream file ;

  	 file.open ("src/js/mygui.js" ) ;
	 stringstream buf ;

	 buf << file.rdbuf() ;

	 string sourceString = buf.str() ;

 	 v8::Handle<v8::String> source = v8::String::New( sourceString.c_str() );
	 
 	 v8::Handle<v8::Script> script = v8::Script::Compile(source);
  
 	 v8::Handle<v8::Value> result = script->Run();

*/

// 	 context.Dispose();
    }

/*
v8::Handle< v8::Value > MyGuiJS:: createRoot( const std::string layerName )
 	{
	 int width = OgreManager:: getSingletonPtr()-> m_pViewport-> getActualWidth() ;
	 int height = OgreManager:: getSingletonPtr()-> m_pViewport-> getActualHeight() ;
			
	 MyGUI::WidgetPtr widgetPtr = singleton-> mGui-> createWidget<MyGUI::Widget>("", 0, 0, width, height, MyGUI::Align::Default, layerName ) ;

	 // widgetPtr-> setMaskPick( "blackPixel.png" ) ;

	 // widgetPtr-> setNeedMouseFocus( false ) ;
	
     v8::Handle< v8::Value> widgetObject = WidgetBindJS::NewFromWidgetCpp( widgetPtr ) ;

	 widgetObject-> ToObject()-> Set( v8::String::New( "width" ), v8::Number::New( width ) ) ;
	 widgetObject-> ToObject()-> Set( v8::String::New( "height"), v8::Number::New( height ) ) ;


     return widgetObject ;
	}
*/	