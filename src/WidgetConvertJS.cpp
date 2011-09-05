
#include <WidgetConvertJS.h>
v8::Handle<v8::Value> WidgetConvertJS:: destroy( MyGUI::Widget* widget, const v8::Arguments& args )
	{
	 MyGUI::Gui::getInstance().destroyWidget(widget);
	
	 return v8::Undefined() ;
	}





v8::Handle<v8::Value> WidgetConvertJS:: setPosition( MyGUI::Widget* widget, const v8::Arguments& args )
	{
	 int x = args[ 0 ]-> ToInteger()-> Value() ;
	 int y = args[ 1 ]-> ToInteger()-> Value() ;
	
	 widget-> setPosition( x, y ) ;
	 return v8::Undefined() ;
	}



v8::Handle<v8::Value> WidgetConvertJS:: setSize( MyGUI::Widget* widget, const v8::Arguments& args )
	{
	 int width  = args[ 0 ]-> ToInteger()-> Value() ;
	 int height = args[ 1 ]-> ToInteger()-> Value() ;

	 widget-> setSize( width, height ) ;

	 return v8::Undefined() ;
	}
