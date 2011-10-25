

#include <InputJS.h>
#include <OgreManager.h>
#include <V8Toolkit.h>


v8::Handle<v8::Value> InputJS:: NewFromOgreManager() 
	{
	 v8::Handle<v8::ObjectTemplate> objectTemplate = v8::ObjectTemplate::New();
	 objectTemplate->SetInternalFieldCount(1);
	 v8::Handle<v8::Object> inputJSObject = objectTemplate-> NewInstance() ;

	 inputJSObject-> Set( v8::String::New( "event" ), v8::Object::New() ) ;
	 inputJSObject-> Set( v8::String::New( "onceFunc" ), v8::Object::New() ) ;


	 V8Toolkit:: setFunction( inputJSObject, "on", "function( event, func )		\
		{									\
		 this.emit( 'newListener', event, func ) ; 				\
											\
		 if( this.event[ event ] == undefined ) 				\
			this.event[ event ] = [ func ] ; 				\
		 else 									\
			this.event[ event ].push( func ) ; 				\
		}" ) ;
	 V8Toolkit:: setFunction( inputJSObject, "addListener", "function( event, func ){ return this.on( event, func ) ; }" ) ;

	 V8Toolkit:: setFunction( inputJSObject, "removeListener", 
		"function( event, func )					\
			{							\
			 for( var i in this.event[ event ] )			\
				{						\
				 if( this.event[event][ i ] == func )		\
					{					\
					 this.event[event].splice( i, 1 ) ;	\
					 return true ;				\
					}					\
				} 						\
			 return false ;						\
			}" 
		) ;

	 V8Toolkit:: setFunction( inputJSObject, "once", "function( event, func )	\
		{									\
		 if( this.onceFunc[event] == undefined ) this.onceFunc[event]=[] ;	\
											\
		 this.onceFunc[event][ func ] = true ;					\
											\
		 this.on( event, func ) ;						\
		}" ) ;


	 V8Toolkit:: setFunction( inputJSObject, "removeAllListeners", "function( event ){ this.event[ event ] = [] ; }" ) ;

	 V8Toolkit:: setFunction( inputJSObject, "listeners", "function( event ){ if( this.event[ event ] == undefined ) return [] ; else return this.event[ event ] ; }" ) ;


	 V8Toolkit:: setFunction( inputJSObject, "emit", 
		"function( event )								\
			{ 									\
			 var removeThese = [] ;							\
												\
			 if( this.event[ event ] == undefined ) 				\
				return ; 							\
			 else 									\
				{								\
				 var args = Array.prototype.slice.call(arguments);		\
				 var eventArgs = args.slice( 1 ) ;				\
				 for( var i in this.event[ event ] )				\
					{							\
					 this.event[ event ][ i ].apply( null, eventArgs ) ;	\
												\
				 	 if( this.onceFunc[event] != undefined && this.onceFunc[ event ][ this.event[ event ][ i ] ] == 1) \
						{						\
						 removeThese.push( this.event[ event ][ i ] ) ;	\
						 this.onceFunc[event].splice(  this.event[ event ][ i ], 1 ) ;\
						}						\
					}							\
			 	}								\
			 var removeThis ;  							\
			 while( removeThese.length > 0 )					\
				{								\
				 removeThis = removeThese.pop() ;				\
												\
				 this.removeListener( event, removeThis ) ;			\
				}								\
			}" 

	) ;


	// del V8Toolkit:: setFunction( inputJSObject, "mouseMoved", "function(){ ogre.Camera.pitch( 1.4 ) ; ogre.Camera.renderOneFrame() ; }" ) ;

	// del V8Toolkit:: setFunction( inputJSObject, "mousePressed", "function(){ ogre.Camera.roll( 1.4 ) ; ogre.Camera.renderOneFrame() ; }" ) ;

	 printf( "after setFunction\n" ) ;

	 InputJS* inputJS = new InputJS() ;

	 OgreManager::getSingletonPtr()-> m_pKeyboard-> setEventCallback( inputJS ) ;
	 OgreManager::getSingletonPtr()-> m_pMouse->    setEventCallback( inputJS ) ;

	 inputJS-> Wrap( inputJSObject ) ;
	 inputJS-> inputJSObject = inputJSObject ;


	 v8::Handle< v8::FunctionTemplate > f = v8::FunctionTemplate::New( captureUI ) ;
	 inputJSObject-> Set( v8::String::New( "captureUI" ), f->GetFunction()   ) ;

	 return inputJSObject ;
	}


v8::Handle<v8::Value> InputJS:: captureUI( const v8::Arguments& args ) 
	{
//	 printf( "capture ui \n" ) ;


	 OgreManager::getSingletonPtr()-> pumpGUIEventQueue() ;


	 OgreManager::getSingletonPtr()-> m_pKeyboard-> capture() ;

	 OgreManager::getSingletonPtr()-> m_pMouse-> 	capture() ;


//	 InputJS* inputJS = ObjectWrap.unwrap

	 return v8::Undefined() ;
	}

v8::Local<v8::Object> InputJS::keyEventToObject( const OIS::KeyEvent &keyEventRef )
	{
	  v8::Local<v8::Object> object = v8::Object::New() ;

	  char key[2] ; key[0]=keyEventRef.text ; key[1]=0 ;

	  v8::Local<v8::String> 	keyChar = v8::String::New( key ) ;

	  v8::Local<v8::Integer> 	keyCode = v8::Integer::New( keyEventRef.key ) ;

	  

	  object-> Set( v8::String::New( "keyChar" ), keyChar ) ;
	  object-> Set( v8::String::New( "keyCode" ), keyCode ) ;

	 return object ;
	}


v8::Local<v8::Object> InputJS::mouseEventToObject( const OIS::MouseEvent &evt)
	{
	  v8::Local<v8::Object> object = v8::Object::New() ;

	 v8::Local<v8::Number> dX 	 = v8::Number::New( evt.state.X.rel ) ;
	 v8::Local<v8::Number> dY 	 = v8::Number::New( evt.state.Y.rel ) ;

	 v8::Local<v8::Number> x 	 = v8::Number::New( evt.state.X.abs ) ;
	 v8::Local<v8::Number> y 	 = v8::Number::New( evt.state.Y.abs ) ;


	 v8::Handle<v8::Boolean> leftIsDown 	 = v8::Boolean::New( evt.state.buttonDown( OIS::MB_Left ) == true ) ;
	 v8::Handle<v8::Boolean> rightIsDown 	 = v8::Boolean::New( evt.state.buttonDown( OIS::MB_Right ) == true ) ;
	 v8::Handle<v8::Boolean> middleIsDown 	 = v8::Boolean::New( evt.state.buttonDown( OIS::MB_Middle ) == true ) ;

	 v8::Handle<v8::Array> place = v8::Array::New( 2 ) ;
	 v8::Handle<v8::Array> speed = v8::Array::New( 2 ) ;
	
	 place-> Set( v8::Number::New( 0 ), x ) ;
	 place-> Set( v8::Number::New( 1 ), y ) ;
	
 	 object-> Set( v8:: String:: New( "place" ), place ) ;
	
	
	 speed-> Set( v8::Number::New( 0 ), dX ) ;
	 speed-> Set( v8::Number::New( 1 ), dY ) ;
	
 	 object-> Set( v8:: String:: New( "speed" ), speed ) ;

/*
	  object-> Set( v8::String::New( "dX" ), dX ) ;
	  object-> Set( v8::String::New( "dY" ), dY ) ;

	  object-> Set( v8::String::New( "x" ), x ) ;
	  object-> Set( v8::String::New( "y" ), y ) ;
*/
	  object-> Set( v8::String::New( "leftIsDown" ), leftIsDown ) ;
	  object-> Set( v8::String::New( "rightIsDown" ), rightIsDown ) ;
	  object-> Set( v8::String::New( "middleIsDown" ), middleIsDown ) ;


	 return object ;
	}



bool InputJS::keyPressed(const OIS::KeyEvent &keyEventRef)
	{



	 v8::Local<v8::Function> func = v8::Local<v8::Function>::Cast( inputJSObject->Get( v8::String::New( "emit" ) ) ) ;
	 v8::Local<v8::Value> args[2] ;
	 v8::Local<v8::String> eventType = v8::String::New( "keyPressed" ) ;

	 args[0] = eventType ;
	 args[1] = keyEventToObject( keyEventRef ) ;
	 func-> Call( inputJSObject, 2, args ) ;


	 return true ;
	}


bool InputJS::keyReleased(const OIS::KeyEvent &keyEventRef)
	{
	 v8::Local<v8::Function> func = v8::Local<v8::Function>::Cast( inputJSObject->Get( v8::String::New( "emit" ) ) ) ;
	 v8::Local<v8::Value> args[2] ;
	 v8::Local<v8::String> eventType = v8::String::New( "keyReleased" ) ;

	 args[0] = eventType ;
	 args[1] = keyEventToObject( keyEventRef ) ;
	 func-> Call( inputJSObject, 2, args ) ;
	 return true ;
	}


bool InputJS::mouseMoved(const OIS::MouseEvent &evt)
	{
	 v8::Local<v8::Function> func = v8::Local<v8::Function>::Cast( inputJSObject->Get( v8::String::New( "emit" ) ) ) ;

	 v8::Local<v8::String> eventType = v8::String::New( "mouseMoved" ) ;

	 v8::Local<v8::Value> args[2] ;
	 args[0] = eventType ;
	 args[1] = mouseEventToObject( evt ) ;


	 func-> Call( inputJSObject, 2, args ) ;

	 return true ;

	}


bool InputJS::mousePressed(const OIS::MouseEvent &evt, OIS::MouseButtonID id)
	{
//	 printf( "mouse pressed\n" ) ;
	 v8::Local<v8::Function> func = v8::Local<v8::Function>::Cast( inputJSObject->Get( v8::String::New( "emit" ) ) ) ;

	 v8::Local<v8::String> eventType = v8::String::New( "mousePressed" ) ;


	 v8::Local<v8::Value> args[1] ;
	 args[0] = eventType ;
	 args[1] = mouseEventToObject( evt ) ;

	 func-> Call( inputJSObject, 2, args ) ;

	 return true ;
	}


bool InputJS::mouseReleased(const OIS::MouseEvent &evt, OIS::MouseButtonID id)
	{
//	 printf( "mouse released\n" ) ;
	 v8::Local<v8::Function> func = v8::Local<v8::Function>::Cast( inputJSObject->Get( v8::String::New( "emit" ) ) ) ;

	 v8::Local<v8::String> eventType = v8::String::New( "mouseReleased" ) ;


	 v8::Local<v8::Value> args[2] ;
	 args[0] = eventType ;
	 args[1] = mouseEventToObject( evt ) ;

	 func-> Call( inputJSObject, 2, args ) ;

	 return true ;

	}

