var sys = require( 'sys' ) ;
require( './src/js/ogre.js' ).init( ogre ).start( 100 ) ;
require( './src/js/mygui.js' ).init( gui ) ;
gui.input.linkToOgreInput( ogre.input ) ;

var w = (new gui.Window()).init( gui.layerSet.Main, 300, 300, 100, 100 ) ;
// w.setParent( gui.layerSet.Main ) ;


var ed = (new gui.TextEdit()).init( gui.layerSet.Main, 200, 200, 100, 100 ) ;
// ed.setParent( gui.layerSet.Main ) ;

ogre.input.on( 'mouseMoved', function( f ) { sys.puts( '( ' + f.x + ', ' + f.y + ' )' ) } ) ;