#include <v8.h>
#include <string.h>
#include <V8Toolkit.h>


v8::Handle<v8::Function> V8Toolkit :: setFunction( v8::Handle<v8::Object> obj,  const char* member, const char* functionAsString )
	{
	 printf( "staart\n" ) ;

	 v8::Handle<v8::ObjectTemplate> objectTemplate = v8::ObjectTemplate::New() ;

	 printf( "new\n" ) ;

	 v8::Handle<v8::Object> inputJSObject = objectTemplate-> NewInstance() ;
	 printf( "asdf\n" ) ;

	 int len =  strlen( "var _____ = " ) + strlen( functionAsString ) + strlen( ";  _____;" ) ;

	 char str[ len+1 ] ;

	 strcpy( str, "var _____ = " ) ; strcat( str, functionAsString ) ; strcat( str, ";  _____;" ) ;


	 printf( str ) ;
	 printf( "assign hack string\n" ) ;

	 v8::Local<v8::String> source = v8::String::New( str ) ;
 	 v8::Local<v8::Script> script = v8::Script::Compile( source ) ;

	 printf( "compile\n" ) ;

 	 v8::Handle<v8::Function> result = v8::Handle<v8::Function>::Cast( script->Run() ) ;

	 printf( "run\n" );

 	 v8::Script::Compile( v8::String::New( "delete _____ ;" )  )-> Run() ;

 	 obj-> Set( v8::String::New( member ), result ) ;

	 return result ;
	}
