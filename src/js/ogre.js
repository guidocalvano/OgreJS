// exports.system = system ; exports.system.Camera = system.Camera ; exports.Input = Input ; 

// var extend = require( 'extend' ) ;

exports.init = function( exports ) {


var sys = require( 'sys' ) ;

exports.input = {} ; // new extendable.Extendable() ;
system = exports.system ;

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

delegateFromAtoB( exports.input, system.input ) ;

exports.input.start = function( rateHz )
	{
	 exports.input.captureProcess = setInterval( system.input.captureUI, 1000 / rateHz ) ;
	}

exports.input.stop = function()
	{
	 clearInterval( exports.input.captureProcess ) ;
	}

exports.window = { width: system.window.width, height: system.window.height } ;

exports.input.mouseMoved = function( mouseEvent ) {}
exports.input.mousePressed = function( mouseEvent ) {}
exports.input.mouseReleased = function( mouseEvent ) {}

exports.input.keyPressed = function( mouseEvent ) {}
exports.input.keyReleased = function( mouseEvent ) {}

exports.input.on( 'mouseMoved', exports.input.mouseMoved ) ;
exports.input.on( 'mousePressed', exports.input.mousePressed ) ;
exports.input.on( 'mouseReleased', exports.input.mouseReleased ) ;

exports.input.on( 'keyPressed', exports.input.keyPressed ) ;
exports.input.on( 'keyReleased', exports.input.keyReleased ) ;

var input = exports.input ;



function SubEntity( cpp )
	{
	 this.cpp = cpp ;	
	}


SubEntity.prototype.setMaterialByName = function( name )
	{
	 this.cpp.setMaterialByName( name ) ;
	}


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
		 this.subEntitySet[ i ].functionalSubEntity = this ;
		}
		
	 return this ;
	} ;


// Entity.prototype = new extendable.Extendable() ;

delegateFromPrototypeAtoMemberMforPrototypeP( Entity.prototype, 'cpp', exports.EventEmitter.prototype ) ;

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


exports.Entity = Entity ;



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

SceneNode.prototype.moveL3N = function( x, y, z ) { this.cpp.moveL3N( x, y, z ) ; } 

SceneNode.prototype.roll  = function( r ) { this.cpp.roll(  r ) ; } 
SceneNode.prototype.pitch = function( r ) { this.cpp.pitch( r ) ; } 
SceneNode.prototype.yaw   = function( r ) { this.cpp.yaw(   r ) ; } 

SceneNode.prototype.convertLocalOXYZToWorldOXYZ = function( oXYZ ) { return this.cpp.convertLocalOXYZToWorldOXYZ( oXYZ ) ; } 
SceneNode.prototype.convertWorldOXYZToLocalOXYZ = function( oXYZ ) { return this.cpp.convertWorldOXYZToLocalOXYZ( oXYZ ) ; } 

SceneNode.prototype.convertLocalOXYZToParentOXYZ = function( oXYZ ) 
	{ return this.parent.convertWorldOXYZToLocalOXYZ( this.convertLocalOXYZToWorldOXYZ( oXYZ ) ) ;   } ;

SceneNode.prototype.convertParentOXYZToLocalOXYZ = function( oXYZ ) 
	{ return this.convertWorldOXYZToLocalOXYZ( this.parent.convertLocalOXYZToWorldOXYZ( oXYZ ) ) ;   } ;


exports.SceneNode = SceneNode ;


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

Camera.prototype.defaultKeyPressedHandler = function( input )
	{
	 var self = this ;
	
	 switch( input.keyChar )
		{
		 case 'w' :
			sys.puts( typeof this.movementProcesses[ input.keyCode ] ) ;
			if( typeof this.movementProcesses[ input.keyCode ] == 'undefined' )
				this.movementProcesses[ input.keyCode ] = setInterval( function() { self.node.moveL3N( 0, 0, 10 ) ; }, 20 ) ;
				
			break ;
		
		 case 's' :
			if( typeof this.movementProcesses[ input.keyCode ] == 'undefined' )
				this.movementProcesses[ input.keyCode ] = setInterval( function() { self.node.moveL3N( 0, 0, -10 ) ; }, 20 ) ;
			break ;
		
		 case 'd' :
			if( typeof this.movementProcesses[ input.keyCode ] == 'undefined' )
				this.movementProcesses[ input.keyCode ] = setInterval( function() { self.node.moveL3N( -10, 0, 0 ) ; }, 20 ) ;

			break ;

		 case 'a' :
			if( typeof this.movementProcesses[ input.keyCode ] == 'undefined' )
				this.movementProcesses[ input.keyCode ] = setInterval( function() { self.node.moveL3N(  10, 0, 0 ) ; }, 20 ) ;
		
		 break ;
		}
	 
	} ;

Camera.prototype.defaultMousePressedHandler = function( input )
	{
	 var hit = this.pick( input.x, input.y ) ;
	 if( hit )
		hit.entity.emit( 'mousePressed', input ) ;
	} ;


Camera.prototype.defaultMouseReleasedHandler = function( input )
	{
	 var hit = this.pick( input.x, input.y ) ;
	 if( hit )
		hit.entity.emit( 'mouseReleased', input ) ;
	} ;

Camera.prototype.defaultMouseMovedHandler = function( input )
	{
	 var hit = this.pick( input.x, input.y ) ;
	 if( hit )
		hit.entity.emit( 'mouseMoved', input ) ;	
	} ;

Camera.prototype.defaultKeyReleasedHandler = function( input )
	{
	 if( typeof this.movementProcesses[ input.keyCode ] == undefined ) return ;
		
	 clearInterval( this.movementProcesses[ input.keyCode ] ) ;	
	
	 this.movementProcesses[ input.keyCode ] = undefined ;	
	} ;

Camera.prototype.setDefaultInputHandlers = function()
	{
	 var self = this ;
	
	
	
	 this.activeHandlers[ 'keyPressed' ] 		= function( input ) { self.defaultKeyPressedHandler( 		input ) ; } ;
	 this.activeHandlers[ 'keyReleased' ] 	= function( input ) { self.defaultKeyReleasedHandler( 	input ) ; } ;
	
	 this.activeHandlers[ 'mousePressed' ] 	= function( input ) { self.defaultMousePressedHandler( 	input ) ; } ;
	 this.activeHandlers[ 'mouseReleased' ] 	= function( input ) { self.defaultMouseReleasedHandler(  input ) ; } ;	
	 this.activeHandlers[ 'mouseMoved' ] 	= function( input ) { self.defaultMouseMovedHandler( 	input ) ; } ;	

 	 for( var i in this.activeHandlers )
		input.on( i, this.activeHandlers[ i ] ) ;

	}


Camera.prototype.removeDefaultInputHandlers = function()
	{
	 for( var handlerType in this.activeHandlers )
		{
		 if( typeof this.activeHandlers[ handlerType ] == undefined )
			{
		 	 Input.removeListener( handlerType, this.activeHandlers[ handlerType ]  ) ;
		 	 this.activeHandlers[ handlerType ] = undefined ;
			}
		}
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
exports.rotatingHead = function( rateHz )
	{
	 var head = new Entity( 'ogrehead.mesh' ) ;
	 var node = new SceneNode() ;
	
	 head.setParent( node ) ;
	
	 node.setParent( root ) ;
	
	 exports.rotatingHead.entity = head ; exports.rotatingHead.node = node ;
	
	 exports.rotatingHead.process = setInterval( function() { node.yaw( 1.0 / rateHz ) ; }, 1000 / rateHz ) ;
	}

*/
exports.RootNode = RootNode ;

exports.root = root ;

var cam =  new Camera() ;




cam.initDefault() ;

exports.Camera = Camera ;

exports.camera = cam  ;//cam.initDefault() ;

exports.start = function( rateHz ) { cam.start( rateHz ) ; input.start( rateHz ) ; /* exports.rotatingHead( rateHz ) ; */ } ;
exports.stop  = function() { cam.stop() 	 ; input.stop() ;  }


return exports ;
}
