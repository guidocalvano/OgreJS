
#ifndef WIDGET_CONVERT_H
#define WIDGET_CONVERT_H
#include <v8.h>
#include <MyGUI.h>
class WidgetConvertJS
	{
	public:
	 static v8::Handle<v8::Value> destroy( MyGUI::Widget* widget, const v8::Arguments& args ) ;	
	
		
	 static v8::Handle<v8::Value> setPosition( MyGUI::Widget* widget, const v8::Arguments& args ) ;

	 static v8::Handle<v8::Value> setSize( MyGUI::Widget* widget, const v8::Arguments& args ) ;	
	} ;
	
#endif