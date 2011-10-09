
#include <EntityJS.h>
#include <OgreJS.h>
#include <EventEmitterJS.h>
#include <MemoryManagerJS.h>
#include <SubEntityJS.h>


v8::Persistent<v8::FunctionTemplate> EntityJS:: prototypeTemplate ;


 EntityJS:: EntityJS( v8::Local<v8::Object> object, const char* mesh )
	{
	 // this-> object = object ;
	 parent = NULL ;

	 entity = OgreManager:: getSingletonPtr()-> m_pSceneMgr-> createEntity( mesh ) ;

	 //
 	 int subEntityCount = entity-> getNumSubEntities() ;
	 Ogre:: SubEntity* nextSubEntity ;

	 v8::Handle<v8::Value> nextSubEntityObject ; 

	 v8::Handle<v8::Array> subEntitySet = v8::Array::New( subEntityCount ) ;

	 for( int i = 0 ; i < subEntityCount ; i++ )
		{
		 nextSubEntity = entity-> getSubEntity( i ) ;
		
		 nextSubEntityObject = SubEntityJS:: NewFromSubEntity( nextSubEntity ) ;
		
		 subEntitySet-> Set( i, nextSubEntityObject ) ; 
		}


	 object-> Set( v8::String::New( "subEntitySet" ), subEntitySet ) ;
	 //
	 Wrap( object ) ;	
	
	 MemoryManagerJS:: singleton-> updateV8AllocatedMemory() ;
	}
	
 EntityJS:: ~EntityJS()
	{
	 entity-> detachFromParent() ;
		
	 OgreManager:: getSingletonPtr()-> m_pSceneMgr-> destroyEntity( entity ) ;
	
		printf( "destroyed entity\n" ) ;
	
	 MemoryManagerJS:: singleton-> updateV8AllocatedMemory() ;
	}

 void EntityJS:: init( v8::Handle< v8::Object > target) 
	{
   	 v8::Local<v8::FunctionTemplate> t = v8::FunctionTemplate::New(New);

	 t-> Inherit( EventEmitterJS:: prototypeTemplate ) ;

   	 prototypeTemplate = v8::Persistent<v8::FunctionTemplate>::New(t);
   	 prototypeTemplate->InstanceTemplate()->SetInternalFieldCount(1);
   	 prototypeTemplate->SetClassName(v8::String::NewSymbol("Entity"));

   	 // NODE_SET_PROTOTYPE_METHOD_BORROWED(prototypeTemplate, "setParent", setParent ) ;

	 addEntityFunctionsToPrototype<EntityJS>( prototypeTemplate ) ;

   	 target->Set(v8::String::NewSymbol("Entity"),
                prototypeTemplate-> GetFunction() );

	}

 v8::Handle<v8::Value> EntityJS:: New( const v8::Arguments& args ) 
	{
	 v8::String::AsciiValue ascii( args[ 0 ] ) ;
	
	 EventEmitterJS:: prototypeTemplate-> GetFunction()-> Call( args.This(), 0, NULL ) ;

	 new EntityJS( args.This(), *ascii ) ;

	 return args.This() ;
	}

 v8::Handle<v8::Value> EntityJS:: setParentConvert( EntityJS* entityJS, const v8::Arguments& args ) 
	{
	 if( entityJS-> parent != NULL )
		{
		 entityJS-> parent-> sceneNode-> detachObject( entityJS-> entity ) ;
		 OgreJS:: singleton-> pickingManagerJS-> remove( entityJS-> entity ) ;
		}
	
	 if( !( args[ 0 ]-> IsNull() ) )
		{

		 SceneNodeJS* newParent 	  = node:: ObjectWrap::Unwrap<SceneNodeJS>( v8::Local<v8::Object>:: Cast( args[ 0 ] ) ) ;

		 entityJS-> parent = newParent ;

		 newParent-> sceneNode-> attachObject( entityJS-> entity ) ;
		 OgreJS:: singleton-> pickingManagerJS-> add( entityJS-> entity, entityJS ) ;
		}
	 return v8:: Undefined() ;
	}