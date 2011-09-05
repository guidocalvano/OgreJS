#include <v8.h>
#include <string.h>
#include <V8Toolkit.h>


v8::Handle<v8::Function> V8Toolkit :: setFunction( v8::Handle<v8::Object> obj,  const char* member, const char* functionAsString )
	{
/* del
	 v8::Handle<v8::ObjectTemplate> objectTemplate = v8::ObjectTemplate::New() ;


	 v8::Handle<v8::Object> inputJSObject = objectTemplate-> NewInstance() ;
*/
	 int len =  strlen( "var _____ = " ) + strlen( functionAsString ) + strlen( ";  _____;" ) ;

	 char str[ len+1 ] ;

	 strcpy( str, "var _____ = " ) ; strcat( str, functionAsString ) ; strcat( str, ";  _____;" ) ;


	 v8::Local<v8::String> source = v8::String::New( str ) ;
 	 v8::Local<v8::Script> script = v8::Script::Compile( source ) ;


 	 v8::Handle<v8::Function> result = v8::Handle<v8::Function>::Cast( script->Run() ) ;


 	 v8::Script::Compile( v8::String::New( "delete _____ ;" )  )-> Run() ;

 	 obj-> Set( v8::String::New( member ), result ) ;

	 return result ;
	}




v8::Handle<v8::Function> V8Toolkit :: setPrototypeTemplateFunction( v8::Handle<v8::ObjectTemplate> obj,  const char* member, const char* functionAsString )
	{
	 int len =  strlen( "var _____ = " ) + strlen( functionAsString ) + strlen( ";  _____;" ) ;

	 char str[ len+1 ] ;

	 strcpy( str, "var _____ = " ) ; strcat( str, functionAsString ) ; strcat( str, ";  _____;" ) ;


	 v8::Local<v8::String> source = v8::String::New( str ) ;
 	 v8::Local<v8::Script> script = v8::Script::Compile( source ) ;


 	 v8::Handle<v8::Function> result = v8::Handle<v8::Function>::Cast( script->Run() ) ;


 	 v8::Script::Compile( v8::String::New( "delete _____ ;" )  )-> Run() ;

 	 obj-> Set( v8::String::New( member ), result ) ;

	 return result ;
	}


