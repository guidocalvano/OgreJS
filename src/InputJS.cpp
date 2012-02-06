

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
	  object-> Set( v8::String::New( "keyName" ), keyName ) ;

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
        case OIS:: KC_UNASSIGNED :
            val = "unassigned" ; return val ;
        case OIS:: KC_ESCAPE :
            val = "escape" ; return val ;
        case OIS:: KC_1 :
            val = "1" ; return val ;
        case OIS:: KC_2 :
            val = "2" ; return val ;
        case OIS:: KC_3 :
            val = "3" ; return val ;
        case OIS:: KC_4 :
            val = "4" ; return val ;
        case OIS:: KC_5 :
            val = "5" ; return val ;
        case OIS:: KC_6 :
            val = "6" ; return val ;
        case OIS:: KC_7 :
            val = "7" ; return val ;
        case OIS:: KC_8 :
            val = "8" ; return val ;
            
        case OIS:: KC_9 :
            val = "9" ; return val ;
        case OIS:: KC_0 :
            val = "0" ; return val ;
        case OIS:: KC_MINUS :
            val = "minus" ; return val ;
        case OIS:: KC_EQUALS :
            val = "equal" ; return val ;
        case OIS:: KC_BACK :
            val = "back" ; return val ;
        case OIS:: KC_TAB :
            val = "tab" ; return val ;
        case OIS:: KC_Q :
            val = "q" ; return val ;
        case OIS:: KC_W :
            val = "w" ; return val ;
        case OIS:: KC_E :
            val = "e" ; return val ;
        case OIS:: KC_R :
            val = "r" ; return val ;
        
        case OIS:: KC_T :
            val = "t" ; return val ;
        case OIS:: KC_Y :
            val = "y" ; return val ;
        case OIS:: KC_U :
            val = "u" ; return val ;
        case OIS:: KC_I :
            val = "i" ; return val ;
        case OIS:: KC_O :
            val = "o" ; return val ;
        case OIS:: KC_P :
            val = "p" ; return val ;
        case OIS:: KC_LBRACKET :
            val = "[" ; return val ;
        case OIS:: KC_RBRACKET :
            val = "]" ; return val ;
        case OIS:: KC_RETURN :
            val = "\n" ; return val ;
        case OIS:: KC_LCONTROL :
            val = "leftControl" ; return val ;

        case OIS:: KC_A :
            val = "a" ; return val ;
        case OIS:: KC_S :
            val = "s" ; return val ;
        case OIS:: KC_D :
            val = "d" ; return val ;
        case OIS:: KC_F :
            val = "f" ; return val ;
        case OIS:: KC_G :
            val = "g" ; return val ;
        case OIS:: KC_H :
            val = "h" ; return val ;
        case OIS:: KC_J :
            val = "j" ; return val ;
        case OIS:: KC_K :
            val = "k" ; return val ;
        case OIS:: KC_L :
            val = "l" ; return val ;
        case OIS:: KC_SEMICOLON :
            val = ";" ; return val ;
            
        case OIS:: KC_APOSTROPHE :
            val = "'" ; return val ;
        case OIS:: KC_GRAVE :
            val = "`" ; return val ;
            
        case OIS:: KC_LSHIFT :
            val = "leftShift" ; return val ;
        case OIS:: KC_BACKSLASH :
            val = "\\" ; return val ;
        case OIS:: KC_Z :
            val = "z" ; return val ;
        case OIS:: KC_X :
            val = "x" ; return val ;
        case OIS:: KC_C :
            val = "c" ; return val ;
        case OIS:: KC_V :
            val = "v" ; return val ;
        case OIS:: KC_B :
            val = "b" ; return val ;
        case OIS:: KC_N :
            val = "n" ; return val ;
        case OIS:: KC_M :
            val = "m" ; return val ;

        case OIS:: KC_COMMA :
            val = "," ; return val ;
        case OIS:: KC_PERIOD :
            val = "." ; return val ;
        case OIS:: KC_SLASH :
            val = "/" ; return val ;
        case OIS:: KC_RSHIFT :
            val = "rightShift" ; return val ;
        case OIS:: KC_MULTIPLY :
            val = "*" ; return val ;
        case OIS:: KC_LMENU :
            val = "command" ; return val ;
        case OIS:: KC_SPACE :
            val = " " ; return val ;
        case OIS:: KC_CAPITAL :
            val = "capsLock" ; return val ;
        case OIS:: KC_F1 :
            val = "f1" ; return val ;
        case OIS:: KC_F2 :
            val = "f2" ; return val ;

        case OIS:: KC_F3 :
            val = "f3" ; return val ;
        case OIS:: KC_F4 :
            val = "f4" ; return val ;
        case OIS:: KC_F5 :
            val = "f5" ; return val ;
        case OIS:: KC_F6 :
            val = "f6" ; return val ;
        case OIS:: KC_F7 :
            val = "f7" ; return val ;
        case OIS:: KC_F8 :
            val = "f8" ; return val ;
        case OIS:: KC_F9 :
            val = "f9" ; return val ;
        case OIS:: KC_F10 :
            val = "f10" ; return val ;
        case OIS:: KC_NUMLOCK :
            val = "numLock" ; return val ;
        case OIS:: KC_SCROLL :
            val = "scroll" ; return val ;
            
        case OIS:: KC_NUMPAD7 :
            val = "numpad7" ; return val ;
        case OIS:: KC_NUMPAD8 :
            val = "numpad8" ; return val ;
        case OIS:: KC_NUMPAD9 :
            val = "numpad9" ; return val ;
        case OIS:: KC_SUBTRACT :
            val = "subtract" ; return val ;
        case OIS:: KC_NUMPAD4 :
            val = "numpad4" ; return val ;
        case OIS:: KC_NUMPAD5 :
            val = "numpad5" ; return val ;
        case OIS:: KC_NUMPAD6 :
            val = "numpad6" ; return val ;
        case OIS:: KC_ADD :
            val = "add" ; return val ;
        case OIS:: KC_NUMPAD1 :
            val = "numpad1" ; return val ;
        case OIS:: KC_NUMPAD2 :
            val = "numpad2" ; return val ;
            
        case OIS:: KC_NUMPAD3 :
            val = "numpad3" ; return val ;
        case OIS:: KC_NUMPAD0 :
            val = "numpad0" ; return val ;
        case OIS:: KC_DECIMAL :
            val = "decimal" ; return val ;
        case OIS:: KC_OEM_102 :
            val = "oem_102" ; return val ;
        case OIS:: KC_F11 :
            val = "f11" ; return val ;
        case OIS:: KC_F12 :
            val = "f12" ; return val ;
        case OIS:: KC_F13 :
            val = "f13" ; return val ;
        case OIS:: KC_F14 :
            val = "f14" ; return val ;
        case OIS:: KC_F15 :
            val = "f15" ; return val ;
        case OIS:: KC_KANA :
            val = "kana" ; return val ;

        case OIS:: KC_ABNT_C1 :
            val = "abnt_c1" ; return val ;
        case OIS:: KC_CONVERT :
            val = "convert" ; return val ;
        case OIS:: KC_NOCONVERT :
            val = "noConvert" ; return val ;
        case OIS:: KC_YEN :
            val = "yen" ; return val ;

        case OIS:: KC_ABNT_C2 :
            val = "abnt_c2" ; return val ;
        case OIS:: KC_NUMPADEQUALS :
            val = "numpadEquals" ; return val ;
        case OIS:: KC_PREVTRACK :
            val = "previousTrack" ; return val ;
        case OIS:: KC_AT :
            val = "at" ; return val ;
        case OIS:: KC_COLON :
            val = "colon" ; return val ;
        case OIS:: KC_UNDERLINE :
            val = "underline" ; return val ;

        case OIS:: KC_KANJI :
            val = "kanji" ; return val ;
        case OIS:: KC_STOP :
            val = "stop" ; return val ;
        case OIS:: KC_AX :
            val = "ax" ; return val ;
        case OIS:: KC_UNLABELED :
            val = "unLabeled" ; return val ;
        case OIS:: KC_NEXTTRACK :
            val = "nextTrack" ; return val ;
        case OIS:: KC_NUMPADENTER :
            val = "numpadEnter" ; return val ;
        case OIS:: KC_RCONTROL :
            val = "rightControl" ; return val ;
        case OIS:: KC_MUTE :
            val = "mute" ; return val ;
        case OIS:: KC_CALCULATOR :
            val = "calculator" ; return val ;
        case OIS:: KC_PLAYPAUSE :
            val = "playPause" ; return val ;            

        case OIS:: KC_MEDIASTOP :
            val = "mediaStop" ; return val ;
        case OIS:: KC_VOLUMEDOWN :
            val = "volumeDown" ; return val ;
        case OIS:: KC_VOLUMEUP :
            val = "volumeUp" ; return val ;
        case OIS:: KC_WEBHOME :
            val = "webHome" ; return val ;
        case OIS:: KC_NUMPADCOMMA :
            val = "numpadComma" ; return val ;
        case OIS:: KC_DIVIDE :
            val = "divide" ; return val ;
        case OIS:: KC_SYSRQ :
            val = "sysRQ" ; return val ;
        case OIS:: KC_RMENU :
            val = "rightCommand" ; return val ;
        case OIS:: KC_PAUSE :
            val = "pause" ; return val ;
        case OIS:: KC_HOME :
            val = "home" ; return val ;           


        case OIS:: KC_UP :
            val = "up" ; return val ;
        case OIS:: KC_PGUP :
            val = "pageUp" ; return val ;
        case OIS:: KC_LEFT :
            val = "left" ; return val ;
        case OIS:: KC_RIGHT :
            val = "right" ; return val ;
        case OIS:: KC_END :
            val = "end" ; return val ;
        case OIS:: KC_DOWN :
            val = "down" ; return val ;
        case OIS:: KC_PGDOWN :
            val = "pageDown" ; return val ;
        case OIS:: KC_INSERT :
            val = "insert" ; return val ;
        case OIS:: KC_DELETE :
            val = "delete" ; return val ;
        case OIS:: KC_LWIN :
            val = "leftWindow" ; return val ;   

        case OIS:: KC_RWIN :
            val = "rightWindows" ; return val ;
        case OIS:: KC_APPS :
            val = "apps" ; return val ;
        case OIS:: KC_POWER :
            val = "power" ; return val ;
        case OIS:: KC_SLEEP :
            val = "sleep" ; return val ;
        case OIS:: KC_WAKE :
            val = "wake" ; return val ;
        case OIS:: KC_WEBSEARCH :
            val = "webSearch" ; return val ;
        case OIS:: KC_WEBFAVORITES :
            val = "webFavorites" ; return val ;
        case OIS:: KC_WEBREFRESH :
            val = "webRefresh" ; return val ;
        case OIS:: KC_WEBSTOP :
            val = "webStop" ; return val ;
        case OIS:: KC_WEBFORWARD :
            val = "webForward" ; return val ;   	

        case OIS:: KC_WEBBACK :
            val = "webBack" ; return val ;
        case OIS:: KC_MYCOMPUTER :
            val = "myComputer" ; return val ;
        case OIS:: KC_MAIL :
            val = "mail" ; return val ;
        case OIS:: KC_MEDIASELECT :
            val = "mediaSelect" ; return val ;
/*        
        case 200 :
            val = "upArrowPad" ; return val ;
        case 203 :
            val = "leftArrowPad" ; return val ;
        case 205 :
            val = "rightArrowPad" ; return val ;
        case 208 :
            val = "downArrowPad" ; return val ;                    
*/
        } ;
    
     val = "undefined" ; return val ;
    } 




