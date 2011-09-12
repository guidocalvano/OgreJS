

// exports.system = system ; exports.system.Camera = system.Camera ; exports.Input = Input ; 

exports.init = function( exports ) {

var 
var sys = require( 'sys' ) ;

exports.input = {} ;
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


exports.input.start = function( rateHz )
	{
	 exports.input.captureProcess = setInterval( system.input.captureUI, 1000 / rateHz ) ;
	}

exports.input.stop = function()
	{
	 clearInterval( exports.input.captureProcess ) ;
	}


var input = exports.input ;

delegateFromAtoB( exports.input, system.input ) ;
	
function Entity( meshname )
	{
	 this.cpp = new system.Entity( meshname ) ;

	 this.parent = null ;
	}


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



function SceneNode()
	{
	 this.cpp = new system.SceneNode() ;

	 this.parent = null ;

	 this.children = [] ;
	}


SceneNode.prototype.setParent = function( newParent ) 
	{
	 console.log( 'a') ;
	 if( newParent != null )
		 this.cpp.setParent( newParent.cpp ) ;
	 else
		 this.cpp.setParent( null ) ;
	 console.log( 'b') ;
	 if( this.parent != null )
		{
		 var removeFromOldParent = this.parent.children.indexOf( this ) ;
		 if( removeFromOldParent >= 0 ) this.parent.children.splice( removeFromOldParent, 1 ) ;
		}
	 console.log( 'c') ;
	 this.parent = newParent ;

	 if( newParent != null )
		 newParent.children.push( this ) ;
		 console.log( 'd') ;
	} 

SceneNode.prototype.moveL3N = function( x, y, z ) { this.cpp.moveL3N( x, y, z ) ; } 

SceneNode.prototype.roll  = function( r ) { this.cpp.roll(  r ) ; } 
SceneNode.prototype.pitch = function( r ) { this.cpp.pitch( r ) ; } 
SceneNode.prototype.yaw   = function( r ) { this.cpp.yaw(   r ) ; } 

SceneNode.prototype.convertLocalOXYZToWorldOXYZ = function( x, y, z ) { return this.cpp.convertLocalOXYZToWorldOXYZ( x, y, z ) ; } 
SceneNode.prototype.convertWorldOXYZToLocalOXYZ = function( x, y, z ) { return this.cpp.convertWorldOXYZToLocalOXYZ( x, y, z ) ; } 


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
	
	
Camera.prototype.initDefault = function()
	{
		
	 this.cpp 	= system.Camera ;
	 this.node 	= new SceneNode() ;	
	
	 this.setParent( this.node ) ;

	 this.node.setParent( root ) ;	

	 this.node.moveL3N( 0, 0, 200 ) ;
	
	 this.node.yaw( 3.145 ) ;

	 this.movementProcesses = {} ;
	 this.activeHandlers = {} ;
	
	
	 this.setDefaultInputHandlers() ;
	
	 return this ;
	}
	

Camera.prototype.pick = function( x, y )
	{
	 return this.cpp.pick( x, y ) ;
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
	 var entity = this.pick( input.x, input.y ) ;
	 if( entity != null )
		entity.emit( 'mousePressed', input ) ;
	} ;


Camera.prototype.defaultMouseReleasedHandler = function( input )
	{
	 var entity = this.pick( input.x, input.y ) ;
	 if( entity != null )
		entity.emit( 'mouseReleased', input ) ;
	} ;

Camera.prototype.defaultMouseMovedHandler = function( input )
	{
	 var entity = this.pick( input.x, input.y ) ;
	 if( entity != null )
		entity.emit( 'mouseMoved', input ) ;	
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
