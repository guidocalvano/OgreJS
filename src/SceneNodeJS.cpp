#include <SceneNodeJS.h>
#include <OgreManager.h>
#include <OgreJS.h>
#include <MemoryManagerJS.h>
v8::Persistent<v8::FunctionTemplate> SceneNodeJS:: prototypeTemplate ;

SceneNodeJS:: SceneNodeJS( v8::Local<v8::Object> object )
	{
	 this-> object = object ;
	 parent = NULL ;

	 sceneNode = OgreManager:: getSingletonPtr()-> m_pSceneMgr-> createSceneNode() ;

	 
	 Wrap( this-> object ) ;
	
	 MemoryManagerJS:: singleton-> updateV8AllocatedMemory() ;
	
	}


SceneNodeJS:: ~SceneNodeJS()
	{
	 sceneNode-> removeAllChildren() ;
	
	 Ogre::SceneNode* parent = sceneNode-> getParentSceneNode() ;
	
	 if( parent != NULL )
		{
			parent-> removeChild( sceneNode ) ;
		}
	
	 OgreManager:: getSingletonPtr()-> m_pSceneMgr-> destroySceneNode(  sceneNode ) ;
	
	printf( "destroyed scenenode\n" ) ;
	
	 MemoryManagerJS:: singleton-> updateV8AllocatedMemory() ;
	
	}

void SceneNodeJS:: init( v8::Handle< v8::Object > target)
	{
   	 v8::Local<v8::FunctionTemplate> t = v8::FunctionTemplate::New(New);

   	 prototypeTemplate = v8::Persistent<v8::FunctionTemplate>::New(t);
   	 prototypeTemplate->InstanceTemplate()->SetInternalFieldCount(1);
   	 prototypeTemplate->SetClassName(v8::String::NewSymbol("SceneNode"));

   	 NODE_SET_PROTOTYPE_METHOD_BORROWED(prototypeTemplate, "setParent", setParent ) ;
   	 NODE_SET_PROTOTYPE_METHOD_BORROWED(prototypeTemplate, "moveL3N", moveL3N ) ;

   	 NODE_SET_PROTOTYPE_METHOD_BORROWED(prototypeTemplate, "convertLocalOXYZToWorldOXYZ", convertLocalOXYZToWorldOXYZ ) ;
   	 NODE_SET_PROTOTYPE_METHOD_BORROWED(prototypeTemplate, "convertWorldOXYZToLocalOXYZ", convertWorldOXYZToLocalOXYZ ) ;

   	 NODE_SET_PROTOTYPE_METHOD_BORROWED(prototypeTemplate, "roll", roll ) ;
   	 NODE_SET_PROTOTYPE_METHOD_BORROWED(prototypeTemplate, "pitch", pitch ) ;
   	 NODE_SET_PROTOTYPE_METHOD_BORROWED(prototypeTemplate, "yaw", yaw ) ;


   	 target-> Set( v8::String::NewSymbol("SceneNode"),
                prototypeTemplate-> GetFunction() );

	 v8::Handle<v8::Value> rootObject = createRoot() ;

	 OgreJS:: singleton-> root = ObjectWrap:: Unwrap<SceneNodeJS>( rootObject-> ToObject() ) ;

	 target-> Set( v8::String::NewSymbol("root"),  rootObject ) ;
	}


v8::Handle<v8::Value> SceneNodeJS:: createRoot() 
	{
	 v8::Local<v8::Function> function = prototypeTemplate-> GetFunction();
    	 v8::Local<v8::Object> object = function->NewInstance();

	 SceneNodeJS* sceneNodeJS = node::ObjectWrap::Unwrap<SceneNodeJS>( object ) ;

	 OgreManager:: getSingletonPtr()-> m_pSceneMgr->getRootSceneNode()-> addChild( sceneNodeJS-> sceneNode ) ;

	 return object ;
	}

v8::Handle<v8::Value> SceneNodeJS:: New( const v8::Arguments& args ) 
	{
	 new SceneNodeJS( args.This() ) ;

	 return args.This() ;
	}

v8::Handle<v8::Value> SceneNodeJS:: setParent( const v8::Arguments& args ) 
	{
	 SceneNodeJS* sceneNodeJS = node::ObjectWrap::Unwrap<SceneNodeJS>( args.This() ) ;

	 if( sceneNodeJS-> parent != NULL )
		{
		 sceneNodeJS-> parent-> sceneNode-> removeChild( sceneNodeJS-> sceneNode ) ;
		}
	 if( !( args[ 0 ]-> IsNull() ) )
		{
		 SceneNodeJS* newParent 	  = node::ObjectWrap::Unwrap<SceneNodeJS>( v8::Local<v8::Object>:: Cast( args[ 0 ] ) ) ;
	
		 sceneNodeJS-> parent = newParent ;

		 newParent-> sceneNode-> addChild( sceneNodeJS-> sceneNode ) ;
		}

	 return v8:: Undefined() ;
	}

v8::Handle<v8::Value> SceneNodeJS:: moveL3N( const v8::Arguments& args )
	{
	 SceneNodeJS* sceneNodeJS = node::ObjectWrap::Unwrap<SceneNodeJS>( args.This() ) ;

	 double x = ( v8::Local< v8::Number >::Cast( args[ 0 ] ) )-> Value() ;
	 double y = ( v8::Local< v8::Number >::Cast( args[ 1 ] ) )-> Value() ;
	 double z = ( v8::Local< v8::Number >::Cast( args[ 2 ] ) )-> Value() ;

	 sceneNodeJS-> sceneNode-> translate(  x, y, z, Ogre:: Node:: TS_LOCAL ) ;

	 return v8:: Undefined() ;
	}



v8::Handle<v8::Value> SceneNodeJS:: convertLocalOXYZToWorldOXYZ( const v8::Arguments& args )
	{
	 SceneNodeJS* sceneNodeJS = node::ObjectWrap::Unwrap<SceneNodeJS>( args.This() ) ;

	 v8::Local<v8::Object> localOXYZ = args[ 0 ]-> ToObject() ;

	 double x = localOXYZ-> Get( v8::String::New( "x" ) )-> NumberValue() ;
	 double y = localOXYZ-> Get( v8::String::New( "y" ) )-> NumberValue() ;
	 double z = localOXYZ-> Get( v8::String::New( "z" ) )-> NumberValue() ;

	 Ogre::Vector3 localV3( x, y, z ) ;

	 Ogre::Vector3 worldV3 = sceneNodeJS-> sceneNode-> convertLocalToWorldPosition( localV3 ) ;

	 v8::Local<v8::Object> worldOXYZ = v8::Object::New() ;

	 worldOXYZ-> Set( v8::String::New( "x" ), v8::Number::New( worldV3.x ) ) ;
	 worldOXYZ-> Set( v8::String::New( "y" ), v8::Number::New( worldV3.y ) ) ;
	 worldOXYZ-> Set( v8::String::New( "z" ), v8::Number::New( worldV3.z ) ) ;
	
	 return worldOXYZ ;
	}


v8::Handle<v8::Value> SceneNodeJS:: convertWorldOXYZToLocalOXYZ( const v8::Arguments& args )
	{
	 SceneNodeJS* sceneNodeJS = node::ObjectWrap::Unwrap<SceneNodeJS>( args.This() ) ;

	 v8::Local<v8::Object> worldOXYZ = args[ 0 ]-> ToObject() ;

	 double x = worldOXYZ-> Get( v8::String::New( "x" ) )-> NumberValue() ;
	 double y = worldOXYZ-> Get( v8::String::New( "y" ) )-> NumberValue() ;
	 double z = worldOXYZ-> Get( v8::String::New( "z" ) )-> NumberValue() ;

	 Ogre::Vector3 worldV3( x, y, z ) ;

	 Ogre::Vector3 localV3 = sceneNodeJS-> sceneNode-> convertWorldToLocalPosition( worldV3 ) ;

	 v8::Local<v8::Object> localOXYZ = v8::Object::New() ;

	 localOXYZ-> Set( v8::String::New( "x" ), v8::Number::New( localV3.x ) ) ;
	 localOXYZ-> Set( v8::String::New( "y" ), v8::Number::New( localV3.y ) ) ;
	 localOXYZ-> Set( v8::String::New( "z" ), v8::Number::New( localV3.z ) ) ;

	 return localOXYZ ;
	}



 v8::Handle<v8::Value> SceneNodeJS:: roll( const v8::Arguments& args ) 
	{
	 printf( "Roll\n" ) ;

    	 SceneNodeJS* sn = ObjectWrap::Unwrap<SceneNodeJS>(args.This());

	 printf( "Unwrap\n" ) ;

	 v8::Local< v8::Number > num ; 

	 num = v8::Local< v8::Number >::Cast( args[ 0 ] ) ;

	 printf( "Cast\n" ) ;

	 double v = num-> Value() ;;

	 printf( "Roll%f\n", (float) v ) ;

	 sn-> sceneNode-> roll( (Ogre::Radian) v ) ;

	 return v8::Undefined() ;
	}


 v8::Handle<v8::Value> SceneNodeJS:: pitch( const v8::Arguments& args ) 
	{
   	 SceneNodeJS* sn = ObjectWrap::Unwrap<SceneNodeJS>(args.This());

	 v8::Local< v8::Number > num ; 

	 num = v8::Local< v8::Number >::Cast( args[ 0 ] ) ;

	 double v = num-> Value() ;;

	 sn-> sceneNode-> pitch( (Ogre::Radian) v ) ;

	 return v8::Undefined() ;
	}


 v8::Handle<v8::Value> SceneNodeJS:: yaw( const v8::Arguments& args ) 
	{
   	 SceneNodeJS* sn = ObjectWrap::Unwrap<SceneNodeJS>(args.This());

	 v8::Local< v8::Number > num ; 

	 num = v8::Local< v8::Number >::Cast( args[ 0 ] ) ;

	 double v = num-> Value() ;;

	 sn-> sceneNode-> yaw( (Ogre::Radian) v ) ;

	 return v8::Undefined() ;
	}

