
#ifndef EDIT_JS_H
#define EDIT_JS_H

#include <MyGUI.h>
#include <StaticTextJS.h>



class EditJS : public StaticTextJS
    {
    public:
     static void init( v8::Handle< v8::Object > target ) ;
        
     static v8::Handle<v8::Value> New( const v8::Arguments& args )  ;
     
     static v8::Handle<v8::Value> NewFromEditCpp( MyGUI::Edit* edit ) ;

     static v8::Handle<v8::Value> destroy( const v8::Arguments& args )  ;


     static v8::Persistent<v8::FunctionTemplate> editPrototypeTemplate ;  

	 template< class ChildType >
	 static void addEditFunctionsToPrototype( v8::Handle<v8::FunctionTemplate> t )
	    {
			addStaticTextFunctionsToPrototype<ChildType>( t ) ;
		}
    } ;
    
#endif