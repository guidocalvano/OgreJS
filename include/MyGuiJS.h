#ifndef MY_GUI_JS_H
#define MY_GUI_JS_H

#include <MyGUI.h>
#include <MyGUI_OgrePlatform.h>
/*
#include <WidgetBindJS.h>
#include <StaticTextBindJS.h>
#include <ButtonBindJS.h>
*/

#include <v8.h>

class MyGuiJS
	{
	public:
	 static MyGuiJS* singleton ;
		
	 MyGUI::OgrePlatform* mPlatform 		;
     MyGUI::Gui*          mGui      		;

		
     static void require( v8::Handle< v8::Object > target ) ;
		
//	 static v8::Handle< v8::Value > createRoot( const std::string layerName ) ; 
		
	 static v8::Handle< v8::Object > createInput() ;
	
	 MyGuiJS() ;		
	} ;
	
#endif