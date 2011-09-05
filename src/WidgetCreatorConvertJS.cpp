
#include <WidgetCreatorConvertJS.h>

#include <WidgetBindJS.h>
#include <StaticTextBindJS.h>

v8::Handle<v8::Value> WidgetCreatorConvertJS:: createStaticText( MyGUI::Widget* creator, const v8::Arguments& args )
	{
	  printf( "WidgetCreatorConvertJS::createStaticText()\n" ) ;      

	  int x 		= args[0]-> ToInteger()-> Value() ;
	  int y 		= args[1]-> ToInteger()-> Value() ;
	  int width  	= args[2]-> ToInteger()-> Value() ;
	  int height 	= args[3]-> ToInteger()-> Value() ;

      MyGUI::StaticTextPtr staticTextPtr = creator-> createWidget<MyGUI::StaticText>("Button", x, y, width, height, MyGUI::Align::Default, creator-> getLayer()-> getName() ) ;

      v8::Handle< v8::Value> object = StaticTextBindJS::NewFromStaticTextCpp( staticTextPtr ) ;

      return object ;	
	}

        
v8::Handle<v8::Value> WidgetCreatorConvertJS:: createButton( MyGUI::Widget* creator, const v8::Arguments& args )
     {
	  int x 		= args[0]-> ToInteger()-> Value() ;
	  int y 		= args[1]-> ToInteger()-> Value() ;
	  int width  	= args[2]-> ToInteger()-> Value() ;
	  int height 	= args[3]-> ToInteger()-> Value() ;
	
      MyGUI::ButtonPtr buttonPtr = creator-> createWidget<MyGUI::Button>("Button", x, y, width, height, MyGUI::Align::Default, creator-> getLayer()-> getName () ) ;
      
      v8::Handle< v8::Value> buttonObject = ButtonBindJS::NewFromButtonCpp( buttonPtr ) ;
      
      return buttonObject ;
     }


v8::Handle<v8::Value> WidgetCreatorConvertJS:: createPanel( MyGUI::Widget* creator, const v8::Arguments& args )
     {
	  int x 		= args[0]-> ToInteger()-> Value() ;
	  int y 		= args[1]-> ToInteger()-> Value() ;
	  int width  	= args[2]-> ToInteger()-> Value() ;
	  int height 	= args[3]-> ToInteger()-> Value() ;


      MyGUI::WidgetPtr widgetPtr = creator-> createWidget<MyGUI::Widget>("Panel", x, y, width, height, MyGUI::Align::Default, creator-> getLayer()-> getName () ) ;

      v8::Handle< v8::Value> widgetObject = WidgetBindJS::NewFromWidgetCpp( widgetPtr ) ;

      return widgetObject ;
     }
