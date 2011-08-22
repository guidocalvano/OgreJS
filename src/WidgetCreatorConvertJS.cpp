
#include <WidgetCreatorConvertJS.h>

#include <WidgetBindJS.h>




        
v8::Handle<v8::Value> WidgetCreatorConvertJS:: createButton( MyGUI::Widget* creator, const v8::Arguments& args )
     {
      printf( "WidgetCreatorConvertJS::createButton()\n" ) ;       

      MyGUI::ButtonPtr buttonPtr = creator-> createWidget<MyGUI::Button>("Button", 10, 10, 300, 26, MyGUI::Align::Default, "Main") ;
      
      v8::Handle< v8::Value> buttonObject = ButtonBindJS::NewFromButtonCpp( buttonPtr ) ;
      
      return buttonObject ;
     }

v8::Handle<v8::Value> WidgetCreatorConvertJS:: createWidget( MyGUI::Widget* creator, const v8::Arguments& args )
     {
      MyGUI::WidgetPtr widgetPtr = creator-> createWidget<MyGUI::Widget>("Widget", 10, 10, 300, 26, MyGUI::Align::Default, "Main") ;
          
      v8::Handle< v8::Value> widgetObject = WidgetBindJS::NewFromWidgetCpp( widgetPtr ) ;
          
      return widgetObject ;
     }
