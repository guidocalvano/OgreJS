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

	 static v8::Handle<v8::Value> setScale3NConvert( SceneNodeJS* sn, const v8::Arguments& args ) ;
	 static v8::Handle<v8::Value> scaleL3NConvert( SceneNodeJS* sn, const v8::Arguments& args ) ;

	 static v8::Handle<v8::Value> setPosition3NConvert( SceneNodeJS* sn, const v8::Arguments& args ) ;
	 static v8::Handle<v8::Value> moveL3NConvert( SceneNodeJS* sn, const v8::Arguments& args ) ;

	 static v8::Handle<v8::Value> convertLocal3NToWorldVConvert( SceneNodeJS* sn, const v8::Arguments& args ) ;	
	 static v8::Handle<v8::Value> convertWorld3NToLocalVConvert( SceneNodeJS* sn,const v8::Arguments& args ) ;
	
	 static v8::Handle<v8::Value> setOrientationM9NConvert( SceneNodeJS* sn, const v8::Arguments& args ) ;
	 static v8::Handle<v8::Value> setOrientationByAngleAndAxis4NConvert( SceneNodeJS* sn, const v8::Arguments& args ) ;
		
	 static v8::Handle<v8::Value> rotateLAngleAroundAxis3NConvert( SceneNodeJS* sn, const v8::Arguments& args ) ;
	
	 static v8::Handle<v8::Value> yawConvert( SceneNodeJS* sn, const v8::Arguments& args ) ;
	 static v8::Handle<v8::Value> pitchConvert( SceneNodeJS* sn, const v8::Arguments& args ) ;
	 static v8::Handle<v8::Value> rollConvert( SceneNodeJS* sn, const v8::Arguments& args ) ;
	
	 template< class ChildType >
	 static void addSceneNodeFunctionsToPrototype( v8::Handle<v8::FunctionTemplate> t )
		{
	     NODE_SET_PROTOTYPE_METHOD_BORROWED( t, "setParent", setParentBind<ChildType> ) ;	

	   	 NODE_SET_PROTOTYPE_METHOD_BORROWED( t, "setScale3N", setScale3NBind<ChildType> ) ;
	   	 NODE_SET_PROTOTYPE_METHOD_BORROWED( t, "scaleL3N", scaleL3NBind<ChildType> ) ;

	   	 NODE_SET_PROTOTYPE_METHOD_BORROWED( t, "setOrientationM9N", setOrientationM9NBind<ChildType> ) ;	
	   	 NODE_SET_PROTOTYPE_METHOD_BORROWED( t, "setOrientationByAngleAndAxis4N", setOrientationByAngleAndAxis4NBind<ChildType> ) ;	

	   	 NODE_SET_PROTOTYPE_METHOD_BORROWED( t, "setPosition3N", setPosition3NBind<ChildType> ) ;	
	   	 NODE_SET_PROTOTYPE_METHOD_BORROWED( t, "moveL3N", moveL3NBind<ChildType> ) ;

	   	 NODE_SET_PROTOTYPE_METHOD_BORROWED( t, "convertLocal3NToWorldV", convertLocal3NToWorldVBind<ChildType> ) ;
	   	 NODE_SET_PROTOTYPE_METHOD_BORROWED( t, "convertWorld3NToLocalV", convertWorld3NToLocalVBind<ChildType> ) ;

	   	 NODE_SET_PROTOTYPE_METHOD_BORROWED( t, "roll", rollBind<ChildType> ) ;
	   	 NODE_SET_PROTOTYPE_METHOD_BORROWED( t, "pitch", pitchBind<ChildType> ) ;
	   	 NODE_SET_PROTOTYPE_METHOD_BORROWED( t, "yaw", yawBind<ChildType> ) ;
	
	   	 NODE_SET_PROTOTYPE_METHOD_BORROWED( t, "rotateLAngleAroundAxis3N", rotateLAngleAroundAxis3NBind<ChildType> ) ;
		}
	 

	 template< class ChildType >
	 static v8::Handle<v8::Value> setParentBind( const v8::Arguments& args )
		{
		     SceneNodeJS* sn = (SceneNodeJS*) ObjectWrap::Unwrap<ChildType>(args.This());
			
		 return setParentConvert( sn, args ) ;
		}


	 template< class ChildType >
	 static v8::Handle<v8::Value> setOrientationByAngleAndAxis4NBind( const v8::Arguments& args ) 
		{
	     SceneNodeJS* sn = (SceneNodeJS*) ObjectWrap::Unwrap<ChildType>(args.This());

		 return setOrientationByAngleAndAxis4NConvert( sn, args ) ;
		}


	 template< class ChildType >
	 static v8::Handle<v8::Value> setOrientationM9NBind( const v8::Arguments& args ) 
		{
	     SceneNodeJS* sn = (SceneNodeJS*) ObjectWrap::Unwrap<ChildType>(args.This());

		 return setOrientationM9NConvert( sn, args ) ;
		}



	 template< class ChildType >
	 static v8::Handle<v8::Value> setScale3NBind( const v8::Arguments& args ) 
		{
	     SceneNodeJS* sn = (SceneNodeJS*) ObjectWrap::Unwrap<ChildType>(args.This());

		 return setScale3NConvert( sn, args ) ;
		}

	 template< class ChildType >
	 static v8::Handle<v8::Value> scaleL3NBind( const v8::Arguments& args ) 
		{
	     SceneNodeJS* sn = (SceneNodeJS*) ObjectWrap::Unwrap<ChildType>(args.This());

		 return scaleL3NConvert( sn, args ) ;
		}

	 template< class ChildType >
	 static v8::Handle<v8::Value> setPosition3NBind( const v8::Arguments& args ) 
		{
	     SceneNodeJS* sn = (SceneNodeJS*) ObjectWrap::Unwrap<ChildType>(args.This());

		 return setPosition3NConvert( sn, args ) ;
		}

	 template< class ChildType >
	 static v8::Handle<v8::Value> moveL3NBind( const v8::Arguments& args ) 
		{
	     SceneNodeJS* sn = (SceneNodeJS*) ObjectWrap::Unwrap<ChildType>(args.This());

		 return moveL3NConvert( sn, args ) ;
		}

	 template< class ChildType >
	 static v8::Handle<v8::Value> convertLocal3NToWorldVBind( const v8::Arguments& args ) 
		{
	     SceneNodeJS* sn = (SceneNodeJS*) ObjectWrap::Unwrap<ChildType>(args.This());

 		 return convertLocal3NToWorldVConvert( sn, args ) ;
		}	
			
	 template< class ChildType >
	 static v8::Handle<v8::Value> convertWorld3NToLocalVBind( const v8::Arguments& args ) 
		{
	     SceneNodeJS* sn = (SceneNodeJS*) ObjectWrap::Unwrap<ChildType>(args.This());

		 return convertWorld3NToLocalVConvert( sn, args ) ;
		}
		
		
	 template< class ChildType >	
	 static v8::Handle<v8::Value> rotateLAngleAroundAxis3NBind( const v8::Arguments& args ) 
		{
	     SceneNodeJS* sn = (SceneNodeJS*) ObjectWrap::Unwrap<ChildType>(args.This());

		 return rotateLAngleAroundAxis3NConvert( sn, args ) ;
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