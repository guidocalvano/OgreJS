
#include <string.h>
#include <v8.h>

class V8Toolkit
	{
	public:
	 static v8::Handle<v8::Function> setFunction( v8::Handle<v8::Object> obj,  const char* member, const char* functionAsString ) ;
	 static v8::Handle<v8::Function> setPrototypeTemplateFunction( v8::Handle<v8::ObjectTemplate> obj,  const char* member, const char* functionAsString ) ;
	
	} ;
	