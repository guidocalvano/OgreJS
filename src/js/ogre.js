// exports.system = system ; exports.system.Camera = system.Camera ; exports.Input = Input ; 

// var extend = require( 'extend' ) ;

// var init = function( ogre ) {


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

ogre.input.keyPressed = function( mouseEvent ) {}
ogre.input.keyReleased = function( mouseEvent ) {}

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


ogre.Entity = Entity ;



function SceneNode() {}

SceneNode.prototype.init = function()
	{
	 this.cpp = new system.SceneNode() ;

	 this.parent = null ;

	 this.children = [] ;
	
	 return this ;
	}
	
	
	
	

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
	} 

SceneNode.prototype.setScale3N = function( x, y, z ) { this.cpp.setScale3N( x, y, z ) ; } 

SceneNode.prototype.scaleL3N = function( x, y, z ) { this.cpp.scaleL3N( x, y, z ) ; } 

SceneNode.prototype.setPosition3N = function( x, y, z ) { this.cpp.setPosition3N( x, y, z ) ; } 

SceneNode.prototype.moveL3N = function( x, y, z ) { this.cpp.moveL3N( x, y, z ) ; } 

SceneNode.prototype.rotateLAngleAroundAxis3N  = function( a, x, y, z ) { this.cpp.rotateLAngleAroundAxis3N( a, x, y, z ) ; } 
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
	 animationFunction.____animationId = ogre.system.getNextAnimationId() ;
	
	 ogre.system.animationProcessSet[ animationFunction.____animationId  ] = animationFunction ;	
	} ;
	
	
ogre.removeAnimationProcess = function( animationFunction )
	{
	 ogre.system.reusableAnimationIdSet.push( animationFunction.____animationId ) ;
		
	 delete ogre.system.animationProcessSet[ animationFunction.____animationId  ] ;	
	} ;

ogre.start = function( rateHz ) { cam.start( rateHz ) ; input.start( rateHz ) ; ogre.system.startAnimation( rateHz ) ; /* ogre.rotatingHead( rateHz ) ; */ } ;
ogre.stop  = function() { cam.stop() 	 ; input.stop() ;  }


return ogre ;
// }


// exports.init = init ;