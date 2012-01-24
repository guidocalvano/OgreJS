

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

	  v8::Local<v8::String> 	keyName = v8::String::New( keyCodeToKeyName( keyEventRef.key ).c_str() ) ;


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


std::string InputJS:: keyCodeToKeyName( int keyCode )
    {
     std::string val ;
    
     switch( keyCode )
        {
        case 0 :
            val = "unassigned" ; return val ;
        case 1 :
            val = "escape" ; return val ;
        case 2 :
            val = "1" ; return val ;
        case 3 :
            val = "2" ; return val ;
        case 4 :
            val = "3" ; return val ;
        case 5 :
            val = "4" ; return val ;
        case 6 :
            val = "5" ; return val ;
        case 7 :
            val = "6" ; return val ;
        case 8 :
            val = "7" ; return val ;
        case 9 :
            val = "8" ; return val ;
            
        case 10 :
            val = "9" ; return val ;
        case 11 :
            val = "0" ; return val ;
        case 12 :
            val = "minus" ; return val ;
        case 13 :
            val = "equal" ; return val ;
        case 14 :
            val = "back" ; return val ;
        case 15 :
            val = "tab" ; return val ;
        case 16 :
            val = "q" ; return val ;
        case 17 :
            val = "w" ; return val ;
        case 18 :
            val = "e" ; return val ;
        case 19 :
            val = "r" ; return val ;
        
        case 20 :
            val = "t" ; return val ;
        case 21 :
            val = "y" ; return val ;
        case 22 :
            val = "u" ; return val ;
        case 23 :
            val = "i" ; return val ;
        case 24 :
            val = "o" ; return val ;
        case 25 :
            val = "p" ; return val ;
        case 26 :
            val = "[" ; return val ;
        case 27 :
            val = "]" ; return val ;
        case 28 :
            val = "\n" ; return val ;
        case 29 :
            val = "leftControl" ; return val ;

        case 30 :
            val = "a" ; return val ;
        case 31 :
            val = "s" ; return val ;
        case 32 :
            val = "d" ; return val ;
        case 33 :
            val = "f" ; return val ;
        case 34 :
            val = "g" ; return val ;
        case 35 :
            val = "h" ; return val ;
        case 36 :
            val = "j" ; return val ;
        case 37 :
            val = "k" ; return val ;
        case 38 :
            val = "l" ; return val ;
        case 39 :
            val = ";" ; return val ;
            
        case 40 :
            val = "'" ; return val ;
        case 41 :
            val = "leftShift" ; return val ;
        case 42 :
            val = "\\" ; return val ;
        case 43 :
            val = "z" ; return val ;
        case 44 :
            val = "x" ; return val ;
        case 45 :
            val = "c" ; return val ;
        case 46 :
            val = "v" ; return val ;
        case 47 :
            val = "b" ; return val ;
        case 48 :
            val = "n" ; return val ;
        case 49 :
            val = "m" ; return val ;

        case 50 :
            val = "," ; return val ;
        case 51 :
            val = "." ; return val ;
        case 52 :
            val = "/" ; return val ;
        case 53 :
            val = "rightShift" ; return val ;
        case 54 :
            val = "*" ; return val ;
        case 55 :
            val = "command" ; return val ;
        case 56 :
            val = " " ; return val ;
        case 57 :
            val = "capsLock" ; return val ;
        case 58 :
            val = "f1" ; return val ;
        case 59 :
            val = "f2" ; return val ;

        case 60 :
            val = "f3" ; return val ;
        case 61 :
            val = "f4" ; return val ;
        case 62 :
            val = "f5" ; return val ;
        case 63 :
            val = "f6" ; return val ;
        case 64 :
            val = "f7" ; return val ;
        case 65 :
            val = "f8" ; return val ;
        case 66 :
            val = "f9" ; return val ;
        case 67 :
            val = "f10" ; return val ;
        case 68 :
            val = "numLock" ; return val ;
        case 69 :
            val = "scroll" ; return val ;
            
        case 70 :
            val = "numpad7" ; return val ;
        case 71 :
            val = "numpad8" ; return val ;
        case 72 :
            val = "numpad9" ; return val ;
        case 73 :
            val = "subtract" ; return val ;
        case 74 :
            val = "numpad4" ; return val ;
        case 75 :
            val = "numpad5" ; return val ;
        case 76 :
            val = "numpad6" ; return val ;
        case 77 :
            val = "add" ; return val ;
        case 78 :
            val = "numpad1" ; return val ;
        case 79 :
            val = "numpad2" ; return val ;
            
        case 80 :
            val = "numpad3" ; return val ;
        case 81 :
            val = "numpad0" ; return val ;
        case 82 :
            val = "decimal" ; return val ;
        case 83 :
            val = "oem_102" ; return val ;
        case 84 :
            val = "f11" ; return val ;
        case 85 :
            val = "f12" ; return val ;
        case 86 :
            val = "f12" ; return val ;
        case 87 :
            val = "f14" ; return val ;
        case 88 :
            val = "f15" ; return val ;
        case 89 :
            val = "kana" ; return val ;

        case 90 :
            val = "abnt_c1" ; return val ;
        case 91 :
            val = "convert" ; return val ;
        case 92 :
            val = "noConvert" ; return val ;
        case 93 :
            val = "yen" ; return val ;

        case 94 :
            val = "abnt_c2" ; return val ;
        case 95 :
            val = "numpadEquals" ; return val ;
        case 96 :
            val = "previousTrack" ; return val ;
        case 97 :
            val = "at" ; return val ;
        case 98 :
            val = "colon" ; return val ;
        case 99 :
            val = "underline" ; return val ;

        case 100 :
            val = "kanji" ; return val ;
        case 101 :
            val = "stop" ; return val ;
        case 102 :
            val = "ax" ; return val ;
        case 103 :
            val = "unLabeled" ; return val ;
        case 104 :
            val = "nextTrack" ; return val ;
        case 105 :
            val = "numpadEnter" ; return val ;
        case 106 :
            val = "rightControl" ; return val ;
        case 107 :
            val = "mute" ; return val ;
        case 108 :
            val = "calculator" ; return val ;
        case 109 :
            val = "playPause" ; return val ;            

        case 110 :
            val = "mediaStop" ; return val ;
        case 111 :
            val = "volumeDown" ; return val ;
        case 112 :
            val = "volumeUp" ; return val ;
        case 113 :
            val = "webHome" ; return val ;
        case 114 :
            val = "humpadComma" ; return val ;
        case 115 :
            val = "divide" ; return val ;
        case 116 :
            val = "sysRQ" ; return val ;
        case 117 :
            val = "rightCommand" ; return val ;
        case 118 :
            val = "pause" ; return val ;
        case 119 :
            val = "home" ; return val ;           


        case 120 :
            val = "up" ; return val ;
        case 121 :
            val = "pageUp" ; return val ;
        case 122 :
            val = "left" ; return val ;
        case 123 :
            val = "right" ; return val ;
        case 124 :
            val = "end" ; return val ;
        case 125 :
            val = "down" ; return val ;
        case 126 :
            val = "pageDown" ; return val ;
        case 127 :
            val = "insert" ; return val ;
        case 128 :
            val = "delete" ; return val ;
        case 129 :
            val = "leftWindow" ; return val ;   

        case 130 :
            val = "rightWindows" ; return val ;
        case 131 :
            val = "apps" ; return val ;
        case 132 :
            val = "power" ; return val ;
        case 133 :
            val = "sleep" ; return val ;
        case 134 :
            val = "wake" ; return val ;
        case 135 :
            val = "webSearch" ; return val ;
        case 136 :
            val = "webFavorites" ; return val ;
        case 137 :
            val = "webRefresh" ; return val ;
        case 138 :
            val = "webStop" ; return val ;
        case 139 :
            val = "webForward" ; return val ;   	

        case 140 :
            val = "webBack" ; return val ;
        case 141 :
            val = "myComputer" ; return val ;
        case 142 :
            val = "mail" ; return val ;
        case 143 :
            val = "mediaSelect" ; return val ;
        } ;
    
     val = "undefined" ; return val ;
    } 




