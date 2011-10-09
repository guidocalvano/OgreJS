#ifndef SCENE_NODE_H
#define SCENE_NODE_H

#include <OGRE/Ogre.h>
#include <v8.h>
#include <node_object_wrap.h>



class SceneNodeJS : public node::ObjectWrap
	{
	public:

	 SceneNodeJS( v8::Local<v8::Object> object ) ;
	 ~SceneNodeJS() ;

	 static void init( v8::Handle< v8::Object > target) ;

	 static v8::Handle<v8::Value> createRoot() ;

	 static v8::Handle<v8::Value> New( const v8::Arguments& args ) ;


	 static v8::Handle<v8::Value> setParentConvert( SceneNodeJS* sn, const v8::Arguments& args ) ;

	 static v8::Handle<v8::Value> moveL3NConvert( SceneNodeJS* sn, const v8::Arguments& args ) ;

	 static v8::Handle<v8::Value> convertLocalOXYZToWorldOXYZConvert( SceneNodeJS* sn, const v8::Arguments& args ) ;	
	 static v8::Handle<v8::Value> convertWorldOXYZToLocalOXYZConvert( SceneNodeJS* sn,const v8::Arguments& args ) ;
	
	
	 static v8::Handle<v8::Value> yawConvert( SceneNodeJS* sn, const v8::Arguments& args ) ;
	 static v8::Handle<v8::Value> pitchConvert( SceneNodeJS* sn, const v8::Arguments& args ) ;
	 static v8::Handle<v8::Value> rollConvert( SceneNodeJS* sn, const v8::Arguments& args ) ;
	
	 template< class ChildType >
	 static void addSceneNodeFunctionsToPrototype( v8::Handle<v8::FunctionTemplate> t )
		{
	     NODE_SET_PROTOTYPE_METHOD_BORROWED( t, "setParent", setParentBind<ChildType> ) ;	
	
	   	 NODE_SET_PROTOTYPE_METHOD_BORROWED( t, "moveL3N", moveL3NBind<ChildType> ) ;

	   	 NODE_SET_PROTOTYPE_METHOD_BORROWED( t, "convertLocalOXYZToWorldOXYZ", convertLocalOXYZToWorldOXYZBind<ChildType> ) ;
	   	 NODE_SET_PROTOTYPE_METHOD_BORROWED( t, "convertWorldOXYZToLocalOXYZ", convertWorldOXYZToLocalOXYZBind<ChildType> ) ;

	   	 NODE_SET_PROTOTYPE_METHOD_BORROWED( t, "roll", rollBind<ChildType> ) ;
	   	 NODE_SET_PROTOTYPE_METHOD_BORROWED( t, "pitch", pitchBind<ChildType> ) ;
	   	 NODE_SET_PROTOTYPE_METHOD_BORROWED( t, "yaw", yawBind<ChildType> ) ;
		}
	 

	 template< class ChildType >
	 static v8::Handle<v8::Value> setParentBind( const v8::Arguments& args )
		{
		     SceneNodeJS* sn = (SceneNodeJS*) ObjectWrap::Unwrap<ChildType>(args.This());
			
		 return setParentConvert( sn, args ) ;
		}

	 template< class ChildType >
	 static v8::Handle<v8::Value> moveL3NBind( const v8::Arguments& args ) 
		{
	     SceneNodeJS* sn = (SceneNodeJS*) ObjectWrap::Unwrap<ChildType>(args.This());

		 return moveL3NConvert( sn, args ) ;
		}

	 template< class ChildType >
	 static v8::Handle<v8::Value> convertLocalOXYZToWorldOXYZBind( const v8::Arguments& args ) 
		{
	     SceneNodeJS* sn = (SceneNodeJS*) ObjectWrap::Unwrap<ChildType>(args.This());

 		 return convertLocalOXYZToWorldOXYZConvert( sn, args ) ;
		}	
			
	 template< class ChildType >
	 static v8::Handle<v8::Value> convertWorldOXYZToLocalOXYZBind( const v8::Arguments& args ) 
		{
	     SceneNodeJS* sn = (SceneNodeJS*) ObjectWrap::Unwrap<ChildType>(args.This());

		 return convertWorldOXYZToLocalOXYZConvert( sn, args ) ;
		}

	 template< class ChildType >	
	 static v8::Handle<v8::Value> yawBind( const v8::Arguments& args ) 
		{
	     SceneNodeJS* sn = (SceneNodeJS*) ObjectWrap::Unwrap<ChildType>(args.This());

		 return yawConvert( sn, args ) ;
		}
		
	 template< class ChildType >
	 static v8::Handle<v8::Value> pitchBind( const v8::Arguments& args ) 
		{
	     SceneNodeJS* sn = (SceneNodeJS*) ObjectWrap::Unwrap<ChildType>(args.This());

		 return pitchConvert( sn, args ) ;
		}
			
	 template< class ChildType >			
	 static v8::Handle<v8::Value> rollBind( const v8::Arguments& args ) 
		{
	     SceneNodeJS* sn = (SceneNodeJS*) ObjectWrap::Unwrap<ChildType>(args.This());

		 return rollConvert( sn, args ) ;
		}



	 static v8::Persistent<v8::FunctionTemplate> prototypeTemplate ;
	

	 Ogre::SceneNode* sceneNode ;

	 v8::Local<v8::Object> object ;


	 SceneNodeJS* parent ;

	} ;


#endif