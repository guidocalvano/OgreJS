
#include <SubEntityJS.h>
#include <OgreJS.h>
#include <EventEmitterJS.h>
#include <MemoryManagerJS.h>

v8::Persistent<v8::FunctionTemplate> SubEntityJS:: prototypeTemplate ;

SubEntityJS :: SubEntityJS()
	{}

void SubEntityJS:: init( v8::Handle< v8::Object > target) 
	{
	 v8::Local<v8::FunctionTemplate> t = v8::FunctionTemplate::New( New ) ;
   
   	 prototypeTemplate = v8::Persistent<v8::FunctionTemplate>::New(t);
   	 prototypeTemplate->InstanceTemplate()->SetInternalFieldCount(1);
   	 prototypeTemplate->SetClassName(v8::String::NewSymbol("SubEntity"));

	 addSubEntityFunctionsToPrototype<SubEntityJS>( prototypeTemplate ) ;
	
	} 



 v8::Handle<v8::Value> SubEntityJS:: New( const v8::Arguments& args ) 
	{
	 return args.This() ;
	}
	
	

 v8::Handle<v8::Value> SubEntityJS:: NewFromSubEntity( Ogre::SubEntity* subEntity ) 
    {
     v8::Local<v8::Function> function = SubEntityJS::prototypeTemplate-> GetFunction();
     v8::Local<v8::Object>   object   = function->NewInstance();

     SubEntityJS* bindJS = new SubEntityJS() ;

     bindJS-> subEntity = subEntity ;

     bindJS-> Wrap( object ) ;

	 MemoryManagerJS:: singleton-> updateV8AllocatedMemory() ;

     return object ;
    }


 v8::Handle<v8::Value> SubEntityJS:: setMaterialByNameConvert( SubEntityJS* subEntityJS, const v8::Arguments& args ) 
 	{
	 v8::String::AsciiValue ascii( args[ 0 ] ) ;
	 
	 subEntityJS-> subEntity-> setMaterialName( *ascii ) ;
	 
	 return v8::Undefined() ;
	}


