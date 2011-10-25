#ifndef ANIMATION_STATE_JS_H
#define ANIMATION_STATE_JS_H

#include <OGRE/Ogre.h>
#include <v8.h>
#include <node_object_wrap.h>

#include <string>


class AnimationStateJS : public node::ObjectWrap
	{
	public:
		
	 static v8::Persistent<v8::FunctionTemplate> prototypeTemplate ;
	
	 Ogre::AnimationState* animationState ;
	
	 static void init( v8::Handle< v8::Object > target) ;
	
	 template< class ChildType >
	 static void addAnimationStateFunctionsToPrototype( v8::Handle<v8::FunctionTemplate> t )
		{
		 NODE_SET_PROTOTYPE_METHOD_BORROWED( t, "addTime", addTimeBind<ChildType> ) ;	
		
		 NODE_SET_PROTOTYPE_METHOD_BORROWED( t, "setEnabled", setEnabledBind<ChildType> ) ;	
	     NODE_SET_PROTOTYPE_METHOD_BORROWED( t, "setLoop", setLoopBind<ChildType> ) ;	
		}
	
	 AnimationStateJS( v8::Handle< v8::Object > object, Ogre::AnimationState* animationState ) ;

	 static v8::Handle<v8::Value> New( const v8::Arguments& args ) ;	
	 
	
	 static v8::Handle<v8::Value> NewFromAnimationStatePtr( Ogre::AnimationState* animationState ) ;
	 
	
	
	 static v8::Handle<v8::Value> addTimeConvert(AnimationStateJS* animationStateJS, const v8::Arguments& args ) ;	

	 template< class ChildType >
	 static v8::Handle<v8::Value> addTimeBind( const v8::Arguments& args )
	 	{
		 AnimationStateJS* animationStateJS = (AnimationStateJS*) node::ObjectWrap:: Unwrap<ChildType>( args.This() ) ; 

		 return addTimeConvert( animationStateJS, args ) ;
		} ;
		
		
	 static v8::Handle<v8::Value> setEnabledConvert( AnimationStateJS* animationStateJS, const v8::Arguments& args ) ;	

	 template< class ChildType >
	 static v8::Handle<v8::Value> setEnabledBind( const v8::Arguments& args )
	 	{
		 AnimationStateJS* animationStateJS = (AnimationStateJS*) node::ObjectWrap:: Unwrap<ChildType>( args.This() ) ; 

		 return setEnabledConvert( animationStateJS, args ) ;
		} ;
	
	
	 static v8::Handle<v8::Value> setLoopConvert( AnimationStateJS* animationStateJS, const v8::Arguments& args ) ;	

	 template< class ChildType >
	 static v8::Handle<v8::Value> setLoopBind( const v8::Arguments& args )
	 	{
		 AnimationStateJS* animationStateJS = (AnimationStateJS*) node::ObjectWrap:: Unwrap<ChildType>( args.This() ) ; 

		 return setLoopConvert( animationStateJS, args ) ;
		} ;
	} ;
	
#endif