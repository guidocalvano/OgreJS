
#include <MyGUI.h>
#include <v8.h>
#ifndef INPUT_MY_GUI_JS
#define INPUT_MY_GUI_JS
class InputMyGuiJS
	{
	public:
		
	 static v8::Handle< v8::Object > createInput() ;	
		
     static v8::Handle<v8::Value> injectMouseMove( const v8::Arguments& args ) ;

     static v8::Handle<v8::Value> injectMousePress( const v8::Arguments& args ) ;

     static v8::Handle<v8::Value> injectMouseRelease( const v8::Arguments& args ) ;

     static v8::Handle<v8::Value> injectKeyPress( const v8::Arguments& args ) ;

     static v8::Handle<v8::Value> injectKeyRelease( const v8::Arguments& args ) ;	
	} ;
	
#endif