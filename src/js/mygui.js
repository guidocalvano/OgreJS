// var extendable = require( 'Extendable' ) ;

// exports.init = function( gui ) {

var system = gui.system ;

var sys = require( 'sys' ) ;

function Component()
	{	
	}
	
// Component.prototype = new extendable.Extendable() ;


Component.prototype = new ogre.EventEmitter() ;


Component.prototype.init = function( parent, x, y, width, height )
	{	
	 this.x = x ;
	 this.y = y ;

	 this.width  = width  ;
	 this.height = height ;

	 this.children = [] ;

	 this.setParent( parent ) ;
	
	 for( var i in this.EVENT_LIST )
		{
		 var eventName = this.EVENT_LIST[ i ] ;
		 this.on( eventName, this[ eventName ] ) ;
	 	}
	
	 return this ;
	}

Component.prototype.mouseMoved    = function( mouseEvent ) {} ;
Component.prototype.mousePressed  = function( mouseEvent ) {} ;
Component.prototype.mouseReleased = function( mouseEvent ) {} ;

Component.prototype.keyPressed    = function( mouseEvent ) {} ;
Component.prototype.keyReleased   = function( mouseEvent ) {} ;

Component.prototype.setParent = function( parent )
	{
	 this.destroySystemComponentsOfBranch() ;
	
	 if( typeof this.parent !== 'undefined' && this.parent != null )
		{
		 var removeFromOldParent = this.parent.children.indexOf( this ) ;
		 if( removeFromOldParent >= 0 ) this.parent.children.splice( removeFromOldParent, 1 ) ;
		}
	
	 this.parent = parent ;
	
	 if( typeof this.parent  !== 'undefined' && this.parent != null )
		{			
		 this.parent.children.push( this ) ;
		
		 this.createSystemComponentsOfBranch() ;
		}

	}

Component.prototype.EVENT_LIST = [ "mousePressed", "mouseReleased", "mouseMoved", "keyPressed", "keyReleased" ] ;


Component.prototype.linkEventHandlers = function()
	{
	 var self = this ;
	
	
	 for( var i in this.EVENT_LIST )
		{
		 
		 var eventName = this.EVENT_LIST[ i ] ;
		 console.log( "sys comp" + this.systemComponent ) ;
                 
                 
		 this.systemComponent.on( eventName, 
			( function() 
				{
				 var name = eventName ;
				return function() 
					{
					 Array.prototype.unshift.call( arguments, name ) ;  
					 self.emit( arguments ) ;
					} 
				})() 
			) ; 
		}
	}


Component.prototype.createSystemComponentsOfBranch = function()
	{
	 this.createSystemComponent() ;
	
	 for( var i in this.children )
		this.children[ i ].createSystemComponentsOfBranch() ;	
	}

	
Component.prototype.createSystemComponent = function()
	{
	 
	} ;


Component.prototype.resetComponentProperties = function()
    {
     if( typeof this.text != 'undefined' ) this.setText( this.text ) ;

    } ;


Component.prototype.destroySystemComponentsOfBranch = function()
	{
	 for( var i in this.children )
		this.children[ i ].destroySystemComponentsOfBranch() ;
		
	 this.destroySystemComponent() ;
	} ;


Component.prototype.destroySystemComponent = function()
	{
	 if( typeof this.systemComponent  == 'undefined' ) return ;
	
	 this.systemComponent.destroy() ;
	
	 this.systemComponent = undefined ;
	} ;


Component.prototype.setText = function( text )
	{
     this.text = text ; 

     if( typeof this.systemComponent  == 'undefined' ) return ;

	 this.systemComponent.setCaption( text ) ;
	}


Component.prototype.setPosition = function( x, y )
	{
     this.x = x ;
     this.y = y ;

     if( typeof this.systemComponent  == 'undefined' ) return ;

	 this.systemComponent.setPosition( x, y ) ;
	}


Component.prototype.setSize = function( w, h )
	{
     this.width  = w ;
     this.height = h ;

     if( typeof this.systemComponent  == 'undefined' ) return ;

	 this.systemComponent.setSize( w, h ) ;
	}


function Text()
	{
	}
	

Text.prototype.init = function( parent, x, y, width, height )
	{
	 Component.prototype.init.call( this, parent, x, y, width, height ) ;
	
	 return this ;
	}

Text.prototype = Object.create( Component.prototype ) ;	


Text.prototype.createSystemComponent = function()
	{
	 if( typeof this.parent !== 'undefined' )
		{
	 	 this.systemComponent = this.parent.systemComponent.createStaticText( this.x, this.y, this.width, this.height ) ;
	
	 	 this.linkEventHandlers() ;

         this.resetComponentProperties() ;
		}
	}



	
	
function Button() {}

Button.prototype.init = function( parent, x, y, width, height )
	{
	 Component.prototype.init.call( this, parent, x, y, width, height ) ;
	
	 return this ;
	}

Button.prototype = new Component() ;	
	

Button.prototype.createSystemComponent = function()
	{	
	 if( typeof this.parent !== 'undefined' )
		{
	 	 this.systemComponent = this.parent.systemComponent.createButton( this.x, this.y, this.width, this.height ) ;
		 this.linkEventHandlers() ;
		}
	}
	



function TextEdit() {}

TextEdit.prototype.init = function( parent, x, y, width, height )
	{
	 Component.prototype.init.call( this, parent, x, y, width, height ) ;

	 return this ;
	}

TextEdit.prototype = new Component() ;	


TextEdit.prototype.createSystemComponent = function()
	{	
	 if( typeof this.parent !== 'undefined' )
		{
	 	 this.systemComponent = this.parent.systemComponent.createEdit( this.x, this.y, this.width, this.height ) ;
		 this.linkEventHandlers() ;
		}
	}


	
function Panel(){}

	
Panel.prototype = new Component() ;

Panel.prototype.init = function( parent, x, y, width, height )
	{
	 Component.prototype.init.call( this, parent, x, y, width, height ) ;
	
	 return this ;
	}

Panel.prototype.createSystemComponent = function()
	{
         console.log( 'CREATED PANEL SYSTEM COMPONENT' ) ;
	 if( typeof this.parent !== 'undefined' )
		{
	 	 this.systemComponent = this.parent.systemComponent.createPanel( this.x, this.y, this.width, this.height ) ;
	 	 this.linkEventHandlers() ;
		}
	}




function Window(){}


Window.prototype = new Component() ;

Window.prototype.init = function( parent, x, y, width, height )
	{
	 Component.prototype.init.call( this, parent, x, y, width, height ) ;

	 return this ;
	}

Window.prototype.createSystemComponent = function()
	{
	 if( typeof this.parent !== 'undefined' )
		{
		 this.systemComponent = this.parent.systemComponent.createWindow( this.x, this.y, this.width, this.height ) ;
	 	 this.linkEventHandlers() ;		
		}
	}




function Root() {}

Root.prototype.init = function( layer )
	{
	 this.systemComponent = layer ;
	
	 Component.prototype.init.call( this, undefined, 0, 0, layer.width, layer.height ) ;
	
	 return this ;
	}


Root.prototype = new Panel() ;

Root.prototype.setParent = function() {} ;

Root.prototype.createSystemComponent = function() {} ;
Root.prototype.destroySystemComponent = function() {} ;




var input = {} ;// new extendable.Extendable() ; 

var sys = require( 'sys' ) ;

function delegateFromAtoB( a, b )
	{
	 for( var i in b )
		{
	 	 if( typeof b[ i ] == 'function' )
			{
			
	 		 a[ i ] = (function(){ var func = b[i] ; var name = i ; sys.puts( name ) ; return function() { return func.apply( b, arguments ) ;   } ; })() ;
			}
		
		}
	}

delegateFromAtoB( input, system.input ) ;




function Layer() {}

Layer.prototype = new Panel() ;


Layer.prototype.init = function( layer )
	{
	 this.systemComponent = layer ;
	
	 Panel.prototype.init.call( this, undefined, 0, 0, layer.width, layer.height ) ;
	 return this ;
	}


Layer.prototype.setParent = function() {} ;

Layer.prototype.createSystemComponent = function() {} ;
Layer.prototype.destroySystemComponent = function() {} ;




input.linkToOgreInput = function( ogreInput ) 
	{
	 ogreInput.on( 'mouseMoved', input.injectMouseMoved ) ;
	 ogreInput.on( 'mousePressed', input.injectMousePressed ) ;
	 ogreInput.on( 'mouseReleased', input.injectMouseReleased ) ;
			
	 ogreInput.on( 'keyPressed', input.injectKeyPressed ) ;
	 ogreInput.on( 'keyReleased', input.injectKeyReleased ) ;
	}


gui.input = input ;

gui.system = system ;
gui.Component = Component ;
gui.Text = Text ;
gui.Button = Button ;
gui.Panel  = Panel  ;
gui.Window = Window ;
gui.TextEdit = TextEdit ;

gui.layerSet = {} ;

for( var i in system.layerSet )
	{ 
	 gui.layerSet[ i ]   = new Layer() ;
	 gui.layerSet[ i ].init( system.layerSet[ i ] )   ;
	}


function Overlay() {} ;

Overlay.prototype = new Panel() ;


Overlay.prototype.init = function( width, height, sceneNode, cameraNode )
    {
     this.sceneNode  = sceneNode  ;
     this.cameraNode = cameraNode ;

     this.reposition() ;

	 Panel.prototype.init.call( this, gui.layerSet.Back, 0, 0, width, height ) ;
	
	 var self = this ;
	
	 this.process = setInterval( function() { self.reposition() ; }, 20 ) ;

     return this ;
    } ;

Overlay.prototype.reposition = function()
    {
    
     var worldV   = this.sceneNode.convertLocal3NToWorldV( 0, 0, 0 ) ;

	 console.log( "worldV " + worldV[ 0 ] + ', ' + worldV[ 1 ] + ', ' + worldV[ 2 ] ) ;

     var cameraV  = this.cameraNode.convertWorld3NToLocalV( worldV[ 0 ], worldV[ 1 ], worldV[ 2 ] ) ;

	 console.log( "cameraV " + cameraV[ 0 ] + ', ' + cameraV[ 1 ] + ', ' + cameraV[ 2 ] ) ;

     if( cameraV[ 2 ] < 0 ) this.setParent( null ) ;  
     else                   this.setParent( gui.layerSet.Back ) ;
     
	 console.log( "w " + ogre.window.width ) ;
	 console.log( "h " + ogre.window.height ) ;
	
	 console.log( "oww / 2 " + ogre.window.width / 2 ) ;
	
	 console.log( "cx /cz " + cameraV[ 0 ] / cameraV[ 2 ] ) ;
	
	 var x = ogre.window.width / 2  - ogre.window.width  * ( cameraV[ 0 ] / cameraV[ 2 ] ) ;
	 var y = ogre.window.height / 2 - ogre.window.height * ( cameraV[ 1 ] / cameraV[ 2 ] ) ;
		
	 console.log( ' NEW POSITION = ' + x + ', ' + y )

     this.setPosition( x, y ) ;
     
    } ;

gui.Overlay = Overlay ;

// gui.b = ( new Button() ).init( gui.layerSet.Main, 100, 100,100,100 ) ;
// gui.b.systemComponent.on( 'mousePressed', sys.puts ) ;
// }
