#include <AnimationStateJS.h>



v8::Persistent<v8::FunctionTemplate> AnimationStateJS:: prototypeTemplate ;


void AnimationStateJS:: init( v8::Handle< v8::Object > target) 
	{		
   	 v8::Local<v8::FunctionTemplate> t = v8::FunctionTemplate::New(New);

   	 prototypeTemplate = v8::Persistent<v8::FunctionTemplate>::New(t);
   	 prototypeTemplate->InstanceTemplate()->SetInternalFieldCount(1);
   	 prototypeTemplate->SetClassName(v8::String::NewSymbol("AnimationState"));

	
	 addAnimationStateFunctionsToPrototype<AnimationStateJS>( prototypeTemplate ) ;
	}
	
	

v8::Handle<v8::Value> AnimationStateJS:: New( const v8::Arguments& args ) 
	{
	 printf( "AnimationStateJS:: New \n" ) ;
		
	 return args.This() ;
	}
	
	

v8::Handle<v8::Value> AnimationStateJS:: NewFromAnimationStatePtr( Ogre::AnimationState* animationState ) 
	{
	 printf( "AnimationStateJS:: NewFromAnimationStatePtr \n" ) ;
	
	 v8::Local<v8::Function> function = AnimationStateJS::prototypeTemplate-> GetFunction() ;
	 v8::Local<v8::Object>   object   = function-> NewInstance() ;

	 new AnimationStateJS( object, animationState ) ;

	 return object ;
	}
	
AnimationStateJS::AnimationStateJS( v8::Handle< v8::Object > object, Ogre:: AnimationState* animationState )
	{
	 this-> animationState = animationState ;

	 Wrap( object ) ;
	}
	


v8::Handle<v8::Value> AnimationStateJS:: addTimeConvert( AnimationStateJS* animationStateJS, const v8::Arguments& args ) 
	{
	 Ogre::Real dT 	= (Ogre::Real) v8::Local< v8::Number >::Cast( args[ 0 ] )-> Value() ;
	
	 animationStateJS-> animationState-> addTime( dT ) ;
	
	 return v8:: Undefined() ;
	}


v8::Handle<v8::Value> AnimationStateJS:: setEnabledConvert( AnimationStateJS* animationStateJS, const v8::Arguments& args ) 
	{
	 bool enabled = args[ 0 ]-> ToBoolean()-> Value() ;
	
	 animationStateJS-> animationState-> setEnabled( enabled ) ;
	
	 return v8:: Undefined() ;
	}



v8::Handle<v8::Value> AnimationStateJS:: setLoopConvert( AnimationStateJS* animationStateJS, const v8::Arguments& args ) 
	{
	 bool loop = args[ 0 ]-> ToBoolean()-> Value() ;
		
	 animationStateJS-> animationState-> setLoop( loop ) ;
	 
	 return v8:: Undefined() ;
	}

	

