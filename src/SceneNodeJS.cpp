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


	 addSceneNodeFunctionsToPrototype<SceneNodeJS>( prototypeTemplate ) ;


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

v8::Handle<v8::Value> SceneNodeJS:: setParentConvert( SceneNodeJS* sceneNodeJS, const v8::Arguments& args ) 
	{
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


v8::Handle<v8::Value> SceneNodeJS:: setScale3NConvert( SceneNodeJS* sceneNodeJS, const v8::Arguments& args )
	{
	 double x = ( v8::Local< v8::Number >::Cast( args[ 0 ] ) )-> Value() ;
	 double y = ( v8::Local< v8::Number >::Cast( args[ 1 ] ) )-> Value() ;
	 double z = ( v8::Local< v8::Number >::Cast( args[ 2 ] ) )-> Value() ;

	 sceneNodeJS-> sceneNode-> setScale(  x, y, z  ) ;

	 return v8:: Undefined() ;
	}


v8::Handle<v8::Value> SceneNodeJS:: scaleL3NConvert( SceneNodeJS* sceneNodeJS, const v8::Arguments& args )
	{
	 double x = ( v8::Local< v8::Number >::Cast( args[ 0 ] ) )-> Value() ;
	 double y = ( v8::Local< v8::Number >::Cast( args[ 1 ] ) )-> Value() ;
	 double z = ( v8::Local< v8::Number >::Cast( args[ 2 ] ) )-> Value() ;

	 sceneNodeJS-> sceneNode-> scale(  x, y, z  ) ;

	 return v8:: Undefined() ;
	}


v8::Handle<v8::Value> SceneNodeJS:: setPosition3NConvert( SceneNodeJS* sceneNodeJS, const v8::Arguments& args )
	{
	 double x = ( v8::Local< v8::Number >::Cast( args[ 0 ] ) )-> Value() ;
	 double y = ( v8::Local< v8::Number >::Cast( args[ 1 ] ) )-> Value() ;
	 double z = ( v8::Local< v8::Number >::Cast( args[ 2 ] ) )-> Value() ;

	 sceneNodeJS-> sceneNode-> setPosition(  x, y, z ) ;

	 return v8:: Undefined() ;
	}

v8::Handle<v8::Value> SceneNodeJS:: moveL3NConvert( SceneNodeJS* sceneNodeJS, const v8::Arguments& args )
	{
	 double x = ( v8::Local< v8::Number >::Cast( args[ 0 ] ) )-> Value() ;
	 double y = ( v8::Local< v8::Number >::Cast( args[ 1 ] ) )-> Value() ;
	 double z = ( v8::Local< v8::Number >::Cast( args[ 2 ] ) )-> Value() ;

	 sceneNodeJS-> sceneNode-> translate(  x, y, z, Ogre:: Node:: TS_LOCAL ) ;

	 return v8:: Undefined() ;
	}



v8::Handle<v8::Value> SceneNodeJS:: convertLocal3NToWorldVConvert( SceneNodeJS* sceneNodeJS, const v8::Arguments& args )
	{
	 v8::Local<v8::Object> localOXYZ = args[ 0 ]-> ToObject() ;

	 double x = ( v8::Local< v8::Number >::Cast( args[ 0 ] ) )-> Value() ;
	 double y = ( v8::Local< v8::Number >::Cast( args[ 1 ] ) )-> Value() ;
	 double z = ( v8::Local< v8::Number >::Cast( args[ 2 ] ) )-> Value() ;

	 Ogre::Vector3 localV3( x, y, z ) ;

	 Ogre::Vector3 worldV3 = sceneNodeJS-> sceneNode-> convertLocalToWorldPosition( localV3 ) ;

	 v8::Local<v8::Array> worldA = v8::Array::New(3) ;

	 worldA-> Set( v8::Number::New( 0 ), v8::Number::New( worldV3.x ) ) ;
	 worldA-> Set( v8::Number::New( 1 ), v8::Number::New( worldV3.y ) ) ;
	 worldA-> Set( v8::Number::New( 2 ), v8::Number::New( worldV3.z ) ) ;
	
	 return worldA ;
	}


v8::Handle<v8::Value> SceneNodeJS:: convertWorld3NToLocalVConvert( SceneNodeJS* sceneNodeJS, const v8::Arguments& args )
	{
//	 v8::Local<v8::Object> worldOXYZ = args[ 0 ]-> ToObject() ;

	 double x = ( v8::Local< v8::Number >::Cast( args[ 0 ] ) )-> Value() ;
	 double y = ( v8::Local< v8::Number >::Cast( args[ 1 ] ) )-> Value() ;
	 double z = ( v8::Local< v8::Number >::Cast( args[ 2 ] ) )-> Value() ;

	 Ogre::Vector3 worldV3( x, y, z ) ;

	 Ogre::Vector3 localV3 = sceneNodeJS-> sceneNode-> convertWorldToLocalPosition( worldV3 ) ;

	 v8::Local<v8::Array> localA = v8::Array::New( 3 ) ;

	 localA-> Set( v8::Number::New( 0 ), v8::Number::New( localV3.x ) ) ;
	 localA-> Set( v8::Number::New( 1 ), v8::Number::New( localV3.y ) ) ;
	 localA-> Set( v8::Number::New( 2 ), v8::Number::New( localV3.z ) ) ;

	 return localA ;
	}



 v8::Handle<v8::Value> SceneNodeJS:: setOrientationByAngleAndAxis4NConvert( SceneNodeJS* sn, const v8::Arguments& args ) 
	{

	 double angle = ( v8::Local< v8::Number >::Cast( args[ 0 ] ) )-> Value() ;
	
	 double x = ( v8::Local< v8::Number >::Cast( args[ 1 ] ) )-> Value() ;
	 double y = ( v8::Local< v8::Number >::Cast( args[ 2 ] ) )-> Value() ;
	 double z = ( v8::Local< v8::Number >::Cast( args[ 3 ] ) )-> Value() ;


	 sn-> sceneNode-> rotate( Ogre:: Quaternion( Ogre:: Radian( angle ), Ogre:: Vector3( x, y, z ) ) ) ;

	 return v8::Undefined() ;		
	}



 v8::Handle<v8::Value> SceneNodeJS:: setOrientationM9NConvert( SceneNodeJS* sn, const v8::Arguments& args ) 
	{

	 double x0 = ( v8::Local< v8::Number >::Cast( args[ 0 ] ) )-> Value() ;
	 double x1 = ( v8::Local< v8::Number >::Cast( args[ 1 ] ) )-> Value() ;
	 double x2 = ( v8::Local< v8::Number >::Cast( args[ 2 ] ) )-> Value() ;
	
	 double y0 = ( v8::Local< v8::Number >::Cast( args[ 3 ] ) )-> Value() ;
	 double y1 = ( v8::Local< v8::Number >::Cast( args[ 4 ] ) )-> Value() ;
	 double y2 = ( v8::Local< v8::Number >::Cast( args[ 5 ] ) )-> Value() ;
	
	 double z0 = ( v8::Local< v8::Number >::Cast( args[ 6 ] ) )-> Value() ;
	 double z1 = ( v8::Local< v8::Number >::Cast( args[ 7 ] ) )-> Value() ;
	 double z2 = ( v8::Local< v8::Number >::Cast( args[ 8 ] ) )-> Value() ;	

	 sn-> sceneNode-> rotate( Ogre:: Quaternion( Ogre:: Vector3( x0, x1, x2 ), Ogre:: Vector3( y0, y1, y2 ), Ogre:: Vector3( z0, z1, z2 ) ) ) ;

	 return v8::Undefined() ;		
	}


 v8::Handle<v8::Value> SceneNodeJS:: rotateLAngleAroundAxis3NConvert( SceneNodeJS* sn, const v8::Arguments& args ) 
	{
	 double angle = ( v8::Local< v8::Number >::Cast( args[ 0 ] ) )-> Value() ;		
		
	 double x = ( v8::Local< v8::Number >::Cast( args[ 1 ] ) )-> Value() ;
	 double y = ( v8::Local< v8::Number >::Cast( args[ 2 ] ) )-> Value() ;
	 double z = ( v8::Local< v8::Number >::Cast( args[ 3 ] ) )-> Value() ;
	
	 sn-> sceneNode-> rotate( Ogre:: Quaternion( Ogre::Radian( angle ), Ogre:: Vector3( x, y, z ) ) ) ;


	 return v8::Undefined() ;		
	}

 v8::Handle<v8::Value> SceneNodeJS:: rollConvert( SceneNodeJS* sn, const v8::Arguments& args ) 
	{
	 v8::Local< v8::Number > num ; 

	 num = v8::Local< v8::Number >::Cast( args[ 0 ] ) ;

	 double v = num-> Value() ;;

	 sn-> sceneNode-> roll( (Ogre::Radian) v ) ;

	 return v8::Undefined() ;
	}


 v8::Handle<v8::Value> SceneNodeJS:: pitchConvert( SceneNodeJS* sn, const v8::Arguments& args ) 
	{
	 v8::Local< v8::Number > num ; 

	 num = v8::Local< v8::Number >::Cast( args[ 0 ] ) ;

	 double v = num-> Value() ;;

	 sn-> sceneNode-> pitch( (Ogre::Radian) v ) ;

	 return v8::Undefined() ;
	}


 v8::Handle<v8::Value> SceneNodeJS:: yawConvert( SceneNodeJS* sn, const v8::Arguments& args ) 
	{
	 v8::Local< v8::Number > num ; 

	 num = v8::Local< v8::Number >::Cast( args[ 0 ] ) ;

	 double v = num-> Value() ;;

	 sn-> sceneNode-> yaw( (Ogre::Radian) v ) ;

	 return v8::Undefined() ;
	}

