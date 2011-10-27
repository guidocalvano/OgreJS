require( './src/js/ogre.js' 	) ;
require( './src/js/mygui.js' 	) ;
gui.input.linkToOgreInput( ogre.input ) ;



var ExampleCameraControl = require( './ExampleCameraControl.js' ) ;

var sn = ( new ogre.SceneNode() ).init() ;
var en = ( new ogre.Entity() 	).init( 'jaiqua.mesh' ) ;


en.setParent( 	sn ) ;
sn.setParent( 	ogre.root ) ;

en.animationStateSet[ 'Walk' ].setEnabled( true ) ;
en.animationStateSet[ 'Walk' ].setLoop( true ) ;


exports.t = setInterval( function() { en.animationStateSet[ 'Walk' ].addTime( 1.0 / 60.0 ) ; }, 1000 / 60 ) ;

var c = ( new ExampleCameraControl.ExampleCameraControl() ).init() ;

c.node.moveL3N( 0, 0, -200 ) ;
ogre.start( 60 ) ;

exports.sn = sn ;
exports.en = en ;
exports.c  = c  ;
