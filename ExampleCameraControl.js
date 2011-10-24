
function ExampleCameraControl() {}
	{

	} ;

ExampleCameraControl.prototype.init = function()
	{
	 this.camera = ogre.camera ;
	
	 this.node   = ( new ogre.SceneNode() ).init() ;
	
	 this.node.setParent( ogre.root ) ;	

	 this.camera.setParent( this.node ) ;
	
	 this.movementProcesses = {} ;
	 this.activeHandlers = {} ;
	
	 this.setDefaultInputHandlers() ;
	
	 return this ;
	} ;


ExampleCameraControl.prototype.defaultKeyPressedHandler = function( input )
	{
	 var self = this ;

	 switch( input.keyChar )
		{
		 case 'w' :
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

ExampleCameraControl.prototype.defaultMousePressedHandler = function( input )
	{
	 var hit = this.camera.pick( input.x, input.y ) ;
	 if( hit )
		hit.entity.emit( 'mousePressed', input ) ;
	} ;


ExampleCameraControl.prototype.defaultMouseReleasedHandler = function( input )
	{
	 var hit = this.camera.pick( input.x, input.y ) ;
	 if( hit )
		hit.entity.emit( 'mouseReleased', input ) ;
	} ;

ExampleCameraControl.prototype.defaultMouseMovedHandler = function( input )
	{
	 var hit = this.camera.pick( input.x, input.y ) ;
	 if( hit )
		hit.entity.emit( 'mouseMoved', input ) ;	
	} ;

ExampleCameraControl.prototype.defaultKeyReleasedHandler = function( input )
	{
	 if( typeof this.movementProcesses[ input.keyCode ] == undefined ) return ;

	 clearInterval( this.movementProcesses[ input.keyCode ] ) ;	

	 this.movementProcesses[ input.keyCode ] = undefined ;	
	} ;

ExampleCameraControl.prototype.setDefaultInputHandlers = function()
	{
	 var self = this ;

	 this.activeHandlers[ 'keyPressed' ] 		= function( input ) { self.defaultKeyPressedHandler( 		input ) ; } ;
	 this.activeHandlers[ 'keyReleased' ] 	= function( input ) { self.defaultKeyReleasedHandler( 	input ) ; } ;

	 this.activeHandlers[ 'mousePressed' ] 	= function( input ) { self.defaultMousePressedHandler( 	input ) ; } ;
	 this.activeHandlers[ 'mouseReleased' ] 	= function( input ) { self.defaultMouseReleasedHandler(  input ) ; } ;	
	 this.activeHandlers[ 'mouseMoved' ] 	= function( input ) { self.defaultMouseMovedHandler( 	input ) ; } ;	

 	 for( var i in this.activeHandlers )
		ogre.input.on( i, this.activeHandlers[ i ] ) ;

	}


ExampleCameraControl.prototype.removeDefaultInputHandlers = function()
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



exports.ExampleCameraControl = ExampleCameraControl ;