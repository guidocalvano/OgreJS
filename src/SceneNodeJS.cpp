#include <SceneNodeJS.h>

v8::Persistent<v8::FunctionTemplate> SceneNodeJS:: prototypeTemplate ;

SceneNodeJS:: SceneNodeJS( v8::Local<v8::Object> object )
	{
	 this-> object = object ;
	 parent = NULL ;

	 sceneNode = OgreManager:: getSingletonPtr()-> m_pSceneMgr-> createSceneNode() ;

	 
	 Wrap( this-> object ) ;
	}


SceneNodeJS:: ~SceneNodeJS()
	{
	 delete sceneNode ;
	}

void SceneNodeJS:: init( v8::Handle< v8::Object > target)
	{
   	 v8::Local<v8::FunctionTemplate> t = v8::FunctionTemplate::New(New);

   	 prototypeTemplate = v8::Persistent<v8::FunctionTemplate>::New(t);
   	 prototypeTemplate->InstanceTemplate()->SetInternalFieldCount(1);
   	 prototypeTemplate->SetClassName(v8::String::NewSymbol("SceneNode"));

   	 NODE_SET_PROTOTYPE_METHOD_BORROWED(prototypeTemplate, "setParent", setParent ) ;
   	 NODE_SET_PROTOTYPE_METHOD_BORROWED(prototypeTemplate, "moveL3N", moveL3N ) ;

   	 target-> Set( v8::String::NewSymbol("SceneNode"),
                prototypeTemplate-> GetFunction() );

	 target-> Set( v8::String::NewSymbol("root"), createRoot() ) ;
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



