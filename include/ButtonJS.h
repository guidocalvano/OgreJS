
#ifndef BUTTON_JS_H
#define BUTTON_JS_H

#include <MyGUI.h>
#include <StaticTextJS.h>



class ButtonJS : public StaticTextJS
    {
    public:
     static void init( v8::Handle< v8::Object > target ) ;
        
     static v8::Handle<v8::Value> New( const v8::Arguments& args )  ;
     
     static v8::Handle<v8::Value> NewFromButtonCpp( MyGUI::Button* button ) ;

     static v8::Handle<v8::Value> destroy( const v8::Arguments& args )  ;


     static v8::Persistent<v8::FunctionTemplate> buttonPrototypeTemplate ;  

	 template< class ChildType >
	 static void addButtonFunctionsToPrototype( v8::Handle<v8::FunctionTemplate> t )
	    {
			addStaticTextFunctionsToPrototype<ChildType>( t ) ;
		}
    } ;
    
#endif