
#ifndef MEMORY_MANAGER_JS_H
#define MEMORY_MANAGER_JS_H
#include <v8.h>



class MemoryManagerJS
	{
	public:
	 static MemoryManagerJS* singleton ;
	
	 static void init( v8::Handle<v8::Object> obj ) ;
	
	 MemoryManagerJS() ;
	
	 long nonV8Memory ;
	
	 long lastUpdatedMemory ;
	
	 long currentlyUsedMemory() ;
	
	 void updateV8AllocatedMemory() ;
	
	 static v8::Handle<v8::Value> allocateMemory( const v8::Arguments& args ) ;
	
	} ;
	
	
#endif