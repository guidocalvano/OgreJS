

var sys = require( 'sys' ) ;

ogre.input = {} ; // new extendable.Extendable() ;
system = ogre.system ;

function delegateFromAtoB( a, b )
	{
	 for( var i in b )
		{
	 	 if( typeof b[ i ] == 'function' )
			{
			
	 		 a[ i ] = (function(){ var func = b[i] ; var name = i ; return function() { return func.apply( b, arguments ) ;   } ; })() ;
			}
		
		}
	}



function delegateFromPrototypeAtoMemberMforPrototypeP( a, m, p )
	{
	 for( var i in p )
		{
	 	 if( typeof p[ i ] == 'function' )
			{
	 		 a[ i ] = (function(){ var func = p[i] ; var name = i ; return function() { return func.apply( this[ m ], arguments ) ;   } ; })() ;
			}

		}
	}

delegateFromAtoB( ogre.input, system.input ) ;

ogre.input.start = function( rateHz )
	{
	 ogre.input.captureProcess = setInterval( system.input.captureUI, 1000 / rateHz ) ;
	}

ogre.input.stop = function()
	{
	 clearInterval( ogre.input.captureProcess ) ;
	}

ogre.window = { width: system.window.width, height: system.window.height } ;

ogre.input.mouseMoved = function( mouseEvent ) {}
ogre.input.mousePressed = function( mouseEvent ) {}
ogre.input.mouseReleased = function( mouseEvent ) {}

ogre.input.keyIsPressed = {} ;


ogre.input.keyPressed = function( keyEvent ) 
    {
     ogre.input.keyIsPressed[ ogre.input.keyCodeToName( keyEvent.keyCode ) ] = true ;
    }
ogre.input.keyReleased = function( keyEvent ) 
    {
     ogre.input.keyIsPressed[ ogre.input.keyCodeToName( keyEvent.keyCode ) ] = false ;    
    }

ogre.input.on( 'mouseMoved', ogre.input.mouseMoved ) ;
ogre.input.on( 'mousePressed', ogre.input.mousePressed ) ;
ogre.input.on( 'mouseReleased', ogre.input.mouseReleased ) ;

ogre.input.on( 'keyPressed', ogre.input.keyPressed ) ;
ogre.input.on( 'keyReleased', ogre.input.keyReleased ) ;

var input = ogre.input ;



function SubEntity( cpp )
	{
	 this.cpp = cpp ;
	 this.material = ogre.materialSet[ cpp.getMaterialName() ] ;	
	}


SubEntity.prototype.setMaterialByName = function( name )
	{
	 this.cpp.setMaterialByName( name ) ;
	}


SubEntity.prototype.setMaterial = function( material )
	{
	 this.cpp.setMaterial( material.cpp ) ;
	
	 this.material = material ;
	}
	
	

SubEntity.prototype.getMaterial = function()
	{
	 return this.material ;
	}


function AnimationState() {}

AnimationState.prototype.init = function( systemAnimationState )
	{
	 this.cpp = systemAnimationState ;
	 return this ;
	}
	
AnimationState.prototype.setEnabled = function( enabled ) { return this.cpp.setEnabled( enabled ) ; } ;
AnimationState.prototype.setLoop	= function( loop 	) { return this.cpp.setLoop( 	loop	) ; } ;
AnimationState.prototype.addTime 	= function( time	) { return this.cpp.addTime( 	time 	) ; } ;

function Entity( meshname ) {}



Entity.prototype.init = function( meshname )
	{
	 this.cpp = new system.Entity( meshname ) ;

	 this.cpp.functionalEntity = this ;

	 this.parent = null ;

	 this.subEntitySet = [] ;

	 for( var i in this.cpp.subEntitySet )
		{
		 this.subEntitySet[ i ] = new SubEntity( this.cpp.subEntitySet[ i ] ) ;
		 // this.subEntitySet[ i ].functionalSubEntity = this ;
		}
		
	
	 this.animationStateSet = {} ;
	
	 for( var j in this.cpp.animationStateSet )
		{
		 this.animationStateSet[ j ] = ( new AnimationState() ).init( this.cpp.animationStateSet[ j ] ) ;
		
		}
	 return this ;
	} ;


// Entity.prototype = new extendable.Extendable() ;

delegateFromPrototypeAtoMemberMforPrototypeP( Entity.prototype, 'cpp', ogre.EventEmitter.prototype ) ;

Entity.prototype.setParent = function( newParent ) 
	{
	 if( newParent != null )
		 this.cpp.setParent( newParent.cpp ) ;
	 else
		 this.cpp.setParent( null ) ;

	 if( this.parent != null )
		{
		 var removeFromOldParent = this.parent.children.indexOf( this ) ;
		 if( removeFromOldParent >= 0 ) this.parent.children.splice( removeFromOldParent, 1 ) ;
		}

	 this.parent = newParent ;

	 if( newParent != null )
		 newParent.children.push( this ) ;
	} 


Entity.prototype.setMaterial = function( material )
	{
	 for( var i in this.subEntitySet ) this.subEntitySet[ i ].setMaterial( material ) ;	
	} ;


Entity.prototype.setAmbient = function( r, g, b )
    {
  	 for( var i in this.subEntitySet ) this.subEntitySet[ i ].getMaterial().setAmbient( r, g, b ) ;  
    
    } ;

Entity.prototype.setDiffuse = function( r, g, b, a )
    {
  	 for( var i in this.subEntitySet ) this.subEntitySet[ i ].getMaterial().setDiffuse( r, g, b, a ) ;  
    
    } ;

Entity.prototype.setSpecular = function( r, g, b, a )
    {
  	 for( var i in this.subEntitySet ) this.subEntitySet[ i ].getMaterial().setSpecular( r, g, b, a ) ;  
    
    } ;


Entity.prototype.setSelfIllumination = function( r, g, b, a )
    {
  	 for( var i in this.subEntitySet ) this.subEntitySet[ i ].getMaterial().setSelfIllumination( r, g, b, a ) ;  
    
    } ;
    
ogre.Entity = Entity ;



function SceneNode() {}

SceneNode.prototype.init = function()
	{
	 this.cpp = new system.SceneNode() ;

	 this.parent = null ;

	 this.children = [] ;
     
     this.isRooted = false ;
     
     this.visibilityListenerSet = {} ;
     
     this.nextVisibilityId = 0 ;
	
	 return this ;
	}
	

SceneNode.prototype.getIsRooted = function() { return this.isRooted ; } ;


// SceneNode.prototype = new extendable.Extendable() ;

SceneNode.prototype.setParent = function( newParent ) 
	{
	 if( newParent != null )
		 this.cpp.setParent( newParent.cpp ) ;
	 else
		  this.cpp.setParent( null ) ;
          
         
         
	 if( this.parent != null )
		{
		 var removeFromOldParent = this.parent.children.indexOf( this ) ;
		 if( removeFromOldParent >= 0 ) this.parent.children.splice( removeFromOldParent, 1 ) ;
		}
	 this.parent = newParent ;

	 if( newParent != null )
		 newParent.children.push( this ) ;
         
         
     if(  this.isRooted && ( !this.parent || !this.parent.isRooted )  )
        { 
         this.unroot() ;

        }
        
     if( !this.isRooted && this.parent && this.parent.isRooted )
        {
         this.root() ;
        }
	} ;


SceneNode.prototype.root = function()
    {
     this.isRooted = true ;
     this.triggerBecomeVisible() ;
     
     for( var i in this.children )
        if( this.children[ i ].root )
            this.children[ i ].root() ;
    } ;


SceneNode.prototype.unroot = function()
    {
     this.isRooted = false ;
     this.triggerBecomeInvisible() ;
     
     for( var i in this.children )
        if( this.children[ i ].unroot )
            this.children[ i ].unroot() ;
    } ;

SceneNode.prototype.addVisibilityListener = function( visibilityListener )
    {
     this.visibilityListenerSet[ this.nextVisibilityId++ ] = visibilityListener ;
    } ;
    
    
SceneNode.prototype.removeVisibilityListener = function( id )
    {
     delete this.visibilityListenerSet[ id ] ;
    } ;
    
    
SceneNode.prototype.triggerBecomeVisible = function()
    {
     for( var i in this.visibilityListenerSet )
        this.visibilityListenerSet[ i ].onBecomeVisible( this ) ;
    
    } ;


SceneNode.prototype.triggerBecomeInvisible = function()
    {
     for( var i in this.visibilityListenerSet )
        this.visibilityListenerSet[ i ].onBecomeInvisible( this ) ;
    
    } ;    
    
    

SceneNode.prototype.setScale3N = function( x, y, z ) { this.cpp.setScale3N( x, y, z ) ; } 

SceneNode.prototype.scaleL3N = function( x, y, z ) { this.cpp.scaleL3N( x, y, z ) ; } 

SceneNode.prototype.setPosition3N = function( x, y, z ) { this.cpp.setPosition3N( x, y, z ) ; } 

SceneNode.prototype.moveL3N = function( x, y, z ) { this.cpp.moveL3N( x, y, z ) ; } 

SceneNode.prototype.rotateLAngleAroundAxis3N  = function( a, x, y, z ) { this.cpp.rotateLAngleAroundAxis3N( a, x, y, z ) ; } 

SceneNode.prototype.resetOrientation  = function() { this.cpp.resetOrientation() ; } 
SceneNode.prototype.setOrientationM9N  = function( x0, x1, x2, y0, y1, y2, z0, z1, z2 ) { this.cpp.setOrientationM9N( x0, x1, x2, y0, y1, y2, z0, z1, z2 ) ; } 
SceneNode.prototype.setOrientationByAngleAndAxis4N  = function( angle, x, y, z ) { this.cpp.setOrientationByAngleAndAxis4N( angle, x, y, z ) ; } 



SceneNode.prototype.roll  = function( r ) { this.cpp.roll(  r ) ; } 
SceneNode.prototype.pitch = function( r ) { this.cpp.pitch( r ) ; } 
SceneNode.prototype.yaw   = function( r ) { this.cpp.yaw(   r ) ; } 

SceneNode.prototype.convertLocal3NToWorldV = function( x, y, z ) { return this.cpp.convertLocal3NToWorldV( x, y, z ) ; } 
SceneNode.prototype.convertWorld3NToLocalV = function( x, y, z ) { return this.cpp.convertWorld3NToLocalV( x, y, z ) ; } 

SceneNode.prototype.convertLocal3NToParentV = function( x, y, z ) 
	{
	 return this.parent.convertWorld3NToLocalV.apply( this.parent, this.convertLocal3NToWorldV( x, y, z ) ) ; 
  	} ;

SceneNode.prototype.convertParent3NToLocalV = function( x, y, z  ) 
	{
	 return this.convertWorld3NToLocalV.apply( this, this.parent.convertLocal3NToWorldV( x, y, z ) ) ;   
	} ;


ogre.SceneNode = SceneNode ;


function RootNode()
	{
	 this.cpp = system.root ;
	 this.parent = null ;

	 this.children = [] ;

     this.isRooted = true ;
	}

RootNode.prototype = SceneNode ;

var root = new RootNode() ;

function Camera()
	{
	}

// Camera.prototype = new extendable.Extendable() ;
	
Camera.prototype.init = function()
	{
		
	 this.cpp 	= system.Camera ;
	
	 this.setParent( root ) ;

	 this.movementProcesses = {} ;
	 this.activeHandlers = {} ;
		
	 return this ;
	}


Camera.prototype.initDefault = function()
	{

	 this.cpp 	= system.Camera ;
//	 this.node 	= new SceneNode() ;	

	 this.setParent( root ) ;

	 // this.node.setParent( root ) ;	

	 // this.node.moveL3N( 0, 0, 200 ) ;

//	 this.node.yaw( 3.145 ) ;

	 this.movementProcesses = {} ;
	 this.activeHandlers = {} ;


	// this.setDefaultInputHandlers() ;

	 return this ;
	}


Camera.prototype.pick = function( x, y )
	{
	 var hit = this.cpp.pick( x, y ) ;
	
	 if( hit )
		{
		 return { entity: hit.entity.functionalEntity, point: hit.point } ;
		}
	
	 // if( systemEntity ) return systemEntity.functionalEntity ;
	}



Camera.prototype.renderOneFrame = function()
	{
	 return this.cpp.renderOneFrame() ;
	}


Camera.prototype.setParent = function( newParent ) 
	{
	 if( newParent != null )
		 this.cpp.setParent( newParent.cpp ) ;
	 else
		 this.cpp.setParent( null ) ;

	 if( this.parent != null )
		{
		 var removeFromOldParent = this.parent.children.indexOf( this ) ;
		 if( removeFromOldParent >= 0 ) this.parent.children.splice( removeFromOldParent, 1 ) ;
		}

	 this.parent = newParent ;

	 if( newParent != null )
		 newParent.children.push( this ) ;
	}


Camera.prototype.start = function( rateHz )
	{
	 var self = this ;
		
	 this.renderProcess = setInterval( function() { self.renderOneFrame() ; }, 1000 / rateHz ) ;		
	}



Camera.prototype.stop = function()
	{
	 clearInterval( this.renderProcess ) ;
	}
	


/*
ogre.rotatingHead = function( rateHz )
	{
	 var head = new Entity( 'ogrehead.mesh' ) ;
	 var node = new SceneNode() ;
	
	 head.setParent( node ) ;
	
	 node.setParent( root ) ;
	
	 ogre.rotatingHead.entity = head ; ogre.rotatingHead.node = node ;
	
	 ogre.rotatingHead.process = setInterval( function() { node.yaw( 1.0 / rateHz ) ; }, 1000 / rateHz ) ;
	}

*/
ogre.RootNode = RootNode ;

ogre.root = root ;

var cam =  new Camera() ;


function Material() {}

Material.prototype.init = function()
	{
	 this.cpp = new ogre.system.Material() ;
	 this.cpp.init() ;
	
	 return this ;
	} ;


Material.prototype.initSystemMaterial = function( name, systemMaterial )
	{
	 this.name	= name 				;
	 this.cpp 	= systemMaterial 	;
	
	 return this ;
	} ;	

Material.prototype.clone			= function() 
	{
	 var systemMaterial = this.cpp.clone() ; 
	
	 return ( new Material() ).initSystemMaterial( "anonymous", systemMaterial ) ;
	} ;


Material.prototype.setAmbient 			= function( r, g, b ) { this.cpp.setAmbient( r, g, b ) ; } ;

Material.prototype.setDiffuse 			= function( r, g, b, a ) { this.cpp.setDiffuse( r, g, b, a ) ; } ;

Material.prototype.setSpecular 			= function( r, g, b, a ) { this.cpp.setSpecular( r, g, b, a ) ; } ;

Material.prototype.setSelfIllumination 	= function( r, g, b ) { this.cpp.setSelfIllumination( r, g, b ) ; } ;




Material.prototype.getAmbient 			= function() { return this.cpp.getAmbient() ; } ;

Material.prototype.getDiffuse 			= function() { return this.cpp.getDiffuse() ; } ;

Material.prototype.getSpecular 			= function() { return this.cpp.getSpecular() ; } ;

Material.prototype.getSelfIllumination 	= function() { return this.cpp.getSelfIllumination() ; } ;



Material.prototype.setTexture 		= function( textureName ) { this.cpp.setTexture( textureName ) ; } ;

Material.prototype.setTextureScroll = function( u, v ) { this.cpp.setTextureScroll( u, v ) ; } ;

Material.prototype.setTextureScale	= function( w, h ) { this.cpp.setTextureScale( w, h  ) ; } ;


ogre.Material = Material ;

ogre.materialSet = {} ;

for( var materialName in ogre.system.materialSet )
	{
	 ogre.materialSet[ materialName ] = ( new Material() ).initSystemMaterial( materialName, ogre.system.materialSet[ materialName ] ) ;
	}


cam.initDefault() ;

ogre.Camera = Camera ;

ogre.camera = cam  ;//cam.initDefault() ;


function Projection() {}

Projection.prototype.init = function( parent, target )
	{
	 this.target = target ;
	
	 this.sceneNode = ( new SceneNode() ).init() ;
	
	 this.sceneNode.setParent( parent ) ;
	} ;

Projection.prototype.project = function()
	{
	 var unprojectedWorld = this.target.convertLocal3NToWorldV( 0, 0, 0 ) ;
	
	 var unprojectedParent = this.sceneNode.parent.convertWorld3NToLocalV( unprojectedWorld[ 0 ], unprojectedWorld[ 1 ], unprojectedWorld[ 2 ] ) ;
	
	 this.sceneNode.setPosition3N( unprojectedParent[ 0 ] / unprojectedParent[ 2 ], unprojectedParent[ 1 ] / unprojectedParent[ 2 ], 1  ) ;
	} ;


ogre.system.animationProcessSet = {} ;

ogre.system.updateAnimations = function( elapsedTime ) { for( var i in ogre.system.animationProcessSet ) ogre.system.animationProcessSet[ i ]( elapsedTime ) ; } ;

ogre.system.nextAnimationId = 0 ;

ogre.system.reusableAnimationIdSet = [] ;

ogre.system.startAnimation = function( rateHz ) 
	{
	 var previousTime = ( new Date() ).getTime() ;
	 
	 ogre.system.animationInterval = setInterval( 
		function() 
			{ 
			 var currentTime = ( new Date() ).getTime() ;
			
			 ogre.system.updateAnimations( currentTime - previousTime ) ;
			
			 previousTime = currentTime ;
			}, 
		1000 / rateHz ) 
	} ;

ogre.system.getNextAnimationId = function() 
	{
	 if( ogre.system.reusableAnimationIdSet.length == 0 )
		{
		 var returnThis = ogre.system.nextAnimationId ;
		 ogre.system.nextAnimationId++ ;
		
		 return returnThis ;
		}
		
	 return ogre.system.reusableAnimationIdSet.pop() ;
	} ;

ogre.addAnimationProcess = function( animationFunction )
	{
	 var animationId = ogre.system.getNextAnimationId() ;
	
	 ogre.system.animationProcessSet[ animationId  ] = animationFunction ;	
	
	 return animationId ;
	} ;
	
	
ogre.removeAnimationProcess = function( animationId )
	{
	 ogre.system.reusableAnimationIdSet.push( animationId ) ;
		
	 delete ogre.system.animationProcessSet[ animationId  ] ;	
	} ;

ogre.start = function( rateHz ) { cam.start( rateHz ) ; input.start( rateHz ) ; ogre.system.startAnimation( rateHz ) ; /* ogre.rotatingHead( rateHz ) ; */ } ;
ogre.stop  = function() { cam.stop() 	 ; input.stop() ;  }


ogre.input.keyCodeToName = function( keyCode )
    {
     switch( keyCode )
        {
        case 0 :
            return "unassigned" ;
        case 1 :
            return "escape" ;
        case 2 :
            return "1" ;
        case 3 :
            return "2" ;
        case 4 :
            return "3" ;
        case 5 :
            return "4" ;
        case 6 :
            return "5" ;
        case 7 :
            return "6" ;
        case 8 :
            return "7" ;
        case 9 :
            return "8" ;
            
        case 10 :
            return "9" ;
        case 11 :
            return "0" ;
        case 12 :
            return "minus" ;
        case 13 :
            return "equal" ;
        case 14 :
            return "back" ;
        case 15 :
            return "tab" ;
        case 16 :
            return "q" ;
        case 17 :
            return "w" ;
        case 18 :
            return "e" ;
        case 19 :
            return "r" ;
        
        case 20 :
            return "t" ;
        case 21 :
            return "y" ;
        case 22 :
            return "u" ;
        case 23 :
            return "i" ;
        case 24 :
            return "o" ;
        case 25 :
            return "p" ;
        case 26 :
            return "[" ;
        case 27 :
            return "]" ;
        case 28 :
            return "\n" ;
        case 29 :
            return "leftControl" ;

        case 30 :
            return "a" ;
        case 31 :
            return "s" ;
        case 32 :
            return "d" ;
        case 33 :
            return "f" ;
        case 34 :
            return "g" ;
        case 35 :
            return "h" ;
        case 36 :
            return "j" ;
        case 37 :
            return "k" ;
        case 38 :
            return "l" ;
        case 39 :
            return ";" ;
            
        case 40 :
            return "'" ;
        case 41 :
            return "leftShift" ;
        case 42 :
            return "\\" ;
        case 43 :
            return "z" ;
        case 44 :
            return "x" ;
        case 45 :
            return "c" ;
        case 46 :
            return "v" ;
        case 47 :
            return "b" ;
        case 48 :
            return "n" ;
        case 49 :
            return "m" ;

        case 50 :
            return "," ;
        case 51 :
            return "." ;
        case 52 :
            return "/" ;
        case 53 :
            return "rightShift" ;
        case 54 :
            return "*" ;
        case 55 :
            return "command" ;
        case 56 :
            return " " ;
        case 57 :
            return "capsLock" ;
        case 58 :
            return "f1" ;
        case 59 :
            return "f2" ;

        case 60 :
            return "f3" ;
        case 61 :
            return "f4" ;
        case 62 :
            return "f5" ;
        case 63 :
            return "f6" ;
        case 64 :
            return "f7" ;
        case 65 :
            return "f8" ;
        case 66 :
            return "f9" ;
        case 67 :
            return "f10" ;
        case 68 :
            return "numLock" ;
        case 69 :
            return "scroll" ;
            
        case 70 :
            return "numpad7" ;
        case 71 :
            return "numpad8" ;
        case 72 :
            return "numpad9" ;
        case 73 :
            return "subtract" ;
        case 74 :
            return "numpad4" ;
        case 75 :
            return "numpad5" ;
        case 76 :
            return "numpad6" ;
        case 77 :
            return "add" ;
        case 78 :
            return "numpad1" ;
        case 79 :
            return "numpad2" ;
            
        case 80 :
            return "numpad3" ;
        case 81 :
            return "numpad0" ;
        case 82 :
            return "decimal" ;
        case 83 :
            return "oem_102" ;
        case 84 :
            return "f11" ;
        case 85 :
            return "f12" ;
        case 86 :
            return "f12" ;
        case 87 :
            return "f14" ;
        case 88 :
            return "f15" ;
        case 89 :
            return "kana" ;

        case 90 :
            return "abnt_c1" ;
        case 91 :
            return "convert" ;
        case 92 :
            return "noConvert" ;
        case 93 :
            return "yen" ;

        case 94 :
            return "abnt_c2" ;
        case 95 :
            return "numpadEquals" ;
        case 96 :
            return "previousTrack" ;
        case 97 :
            return "at" ;
        case 98 :
            return "colon" ;
        case 99 :
            return "underline" ;

        case 100 :
            return "kanji" ;
        case 101 :
            return "stop" ;
        case 102 :
            return "ax" ;
        case 103 :
            return "unLabeled" ;
        case 104 :
            return "nextTrack" ;
        case 105 :
            return "numpadEnter" ;
        case 106 :
            return "rightControl" ;
        case 107 :
            return "mute" ;
        case 108 :
            return "calculator" ;
        case 109 :
            return "playPause" ;            

        case 110 :
            return "mediaStop" ;
        case 111 :
            return "volumeDown" ;
        case 112 :
            return "volumeUp" ;
        case 113 :
            return "webHome" ;
        case 114 :
            return "humpadComma" ;
        case 115 :
            return "divide" ;
        case 116 :
            return "sysRQ" ;
        case 117 :
            return "rightCommand" ;
        case 118 :
            return "pause" ;
        case 119 :
            return "home" ;           


        case 120 :
            return "up" ;
        case 121 :
            return "pageUp" ;
        case 122 :
            return "left" ;
        case 123 :
            return "right" ;
        case 124 :
            return "end" ;
        case 125 :
            return "down" ;
        case 126 :
            return "pageDown" ;
        case 127 :
            return "insert" ;
        case 128 :
            return "delete" ;
        case 129 :
            return "leftWindow" ;   

        case 130 :
            return "rightWindows" ;
        case 131 :
            return "apps" ;
        case 132 :
            return "power" ;
        case 133 :
            return "sleep" ;
        case 134 :
            return "wake" ;
        case 135 :
            return "webSearch" ;
        case 136 :
            return "webFavorites" ;
        case 137 :
            return "webRefresh" ;
        case 138 :
            return "webStop" ;
        case 139 :
            return "webForward" ;   	

        case 140 :
            return "webBack" ;
        case 141 :
            return "myComputer" ;
        case 142 :
            return "mail" ;
        case 143 :
            return "mediaSelect" ;
        } ;
    
     return undefined ;
    } ;


return ogre ;
// }


// exports.init = init ;