
#include <EntityJS.h>

v8::Persistent<v8::FunctionTemplate> EntityJS:: prototypeTemplate ;


 EntityJS:: EntityJS( v8::Local<v8::Object> object, const char* mesh )
	{
	 this-> object = object ;
	 parent = NULL ;

	 entity = OgreManager:: getSingletonPtr()-> m_pSceneMgr-> createEntity( mesh ) ;

	 
	 Wrap( this-> object ) ;
	}


 void EntityJS:: init( v8::Handle< v8::Object > target) 
	{
   	 v8::Local<v8::FunctionTemplate> t = v8::FunctionTemplate::New(New);

   	 prototypeTemplate = v8::Persistent<v8::FunctionTemplate>::New(t);
   	 prototypeTemplate->InstanceTemplate()->SetInternalFieldCount(1);
   	 prototypeTemplate->SetClassName(v8::String::NewSymbol("Entity"));

   	 NODE_SET_PROTOTYPE_METHOD(prototypeTemplate, "setParent", setParent ) ;

   	 target->Set(v8::String::NewSymbol("Entity"),
                prototypeTemplate-> GetFunction() );

	}

 v8::Handle<v8::Value> EntityJS:: New( const v8::Arguments& args ) 
	{
	 v8::String::AsciiValue ascii( args[ 0 ] ) ;

	 new EntityJS( args.This(), *ascii ) ;

	 return args.This() ;
	}

 v8::Handle<v8::Value> EntityJS:: setParent( const v8::Arguments& args ) 
	{
	 EntityJS* entityJS = node::ObjectWrap:: Unwrap<EntityJS>( args.This() ) ;

	 if( entityJS-> parent != NULL )
		{
		 entityJS-> parent-> sceneNode-> detachObject( entityJS-> entity ) ;
		}
	
	 if( !( args[ 0 ]-> IsNull() ) )
		{

		 SceneNodeJS* newParent 	  = node:: ObjectWrap::Unwrap<SceneNodeJS>( v8::Local<v8::Object>:: Cast( args[ 0 ] ) ) ;

		 entityJS-> parent = newParent ;

		 newParent-> sceneNode-> attachObject( entityJS-> entity ) ;
		}
	 return v8:: Undefined() ;
	}