#ifndef EVENT_EMITTER_H
#define EVENT_EMITTER_H

#include <v8.h>

class EventEmitterJS
	{
	public:
	 static v8::Persistent<v8::FunctionTemplate> prototypeTemplate ;

	 static void init() ;
	
	static v8::Handle<v8::Value> New( const v8::Arguments& args ) ;
	} ;
	
	
#endif