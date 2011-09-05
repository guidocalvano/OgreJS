
#ifndef LAYER_JS_H
#define LAYER_JS_H


#include <node_object_wrap.h>
#include <v8.h>



class LayerJS : public node::ObjectWrap
	{
	public:
	 char* layerName ;
	
	 LayerJS( const char* layerName ) ;
	
		
     static v8::Persistent<v8::FunctionTemplate> layerPrototypeTemplate ;  


	 static void init( v8::Handle< v8::Object > target ) ;
    
     static v8::Handle<v8::Value> NewFromLayerName( const char* layerName ) ;
	
	 static v8::Handle<v8::Value> New( const v8::Arguments& args ) ;
    

     static v8::Handle<v8::Value> createPanel( const v8::Arguments& args ) ;
	
     static v8::Handle<v8::Value> createStaticText( const v8::Arguments& args ) ;

     static v8::Handle<v8::Value> createButton( const v8::Arguments& args ) ;

     static v8::Handle<v8::Value> createEdit( const v8::Arguments& args ) ;

     static v8::Handle<v8::Value> createWindow( const v8::Arguments& args ) ;


/*
     static v8::Handle<v8::Value> createEditBox( const v8::Arguments& args ) ;

     static v8::Handle<v8::Value> createEditStretch( const v8::Arguments& args ) ;

     static v8::Handle<v8::Value> createPanel( const v8::Arguments& args ) ;
*/
	
	} ;
	
#endif