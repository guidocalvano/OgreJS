
#ifndef WINDOW_MYGUI_JS
#define WINDOW_MYGUI_JS

#include <WidgetJS.h>


class WindowMyGuiJS : public WidgetJS
	{
	public:
     static v8::Persistent<v8::FunctionTemplate> windowMyGuiPrototypeTemplate ;  

	
	 static	void init( v8::Handle< v8::Object > target ) ;
	
	
	 static v8::Handle<v8::Value> New( const v8::Arguments& args ) ;
	
     static v8::Handle<v8::Value> NewFromWindowCpp( MyGUI::Window* button ) ;
	 
	 static v8::Handle<v8::Value> destroy( const v8::Arguments& args ) ;

	 template< class ChildType >
	 static void addWindowMyGuiFunctionsToPrototype( v8::Handle<v8::FunctionTemplate> t )
		{	
		 addSpatialFunctions< ChildType >( t ) ;
		 addCreateFunctions< ChildType >( t ) ;
		
		}
	} ;
	
#endif