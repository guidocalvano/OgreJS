
// to run, compile OgreJS, and in the folder containing this example type 
// ../build/ogrenode ./example.js 

require( '../src/js/ogre.js'  ) ; 
require( '../src/js/mygui.js' ) ;
gui.input.linkToOgreInput( ogre.input ) ;


var sceneNode = ( new ogre.SceneNode() ).init() ;

var entity = ( new ogre.Entity() ).init( 'ogrehead.mesh' ) ;

sceneNode.setParent( ogre.root ) ;

entity.setParent( sceneNode ) ;

var camNode = ( new ogre.SceneNode() ).init() ;

camNode.setParent( ogre.root ) ;


ogre.camera.setParent( camNode ) ;



camNode.moveL3N( 0, 0, 300 ) ;
camNode.yaw( 3.14 ) ;


ogre.addAnimationProcess( function( elapsedTime ) { sceneNode.yaw(  ( elapsedTime / 1000 ) * Math.PI / 5 ) ; } ) ;

var camProcesses = {} ;
var camSpeed = 50 ; // units per second

ogre.input.on( 'keyPressed', 

    function( keyEvent ) 
        {
        
        switch( keyEvent.keyName )
            {
             case 'left' :
                if( !camProcesses.left )
                    camProcesses.left = ogre.addAnimationProcess( function( elapsedTime )
                        {
                         camNode.moveL3N( ( elapsedTime / 1000 ) * camSpeed, 0, 0 ) ;
                        } ) ;
             
                break ;
                
             case 'right' :
             
                if( !camProcesses.right )
                 camProcesses.right = ogre.addAnimationProcess( function( elapsedTime )
                    {
                     camNode.moveL3N(  -( elapsedTime / 1000 ) * camSpeed, 0, 0 ) ;
                    } ) ;
                 
                break ;
            
             case 'up' :
                
                if( !camProcesses.up )
                camProcesses.up = ogre.addAnimationProcess( function( elapsedTime )
                    {
                     camNode.moveL3N( 0, ( elapsedTime / 1000 ) * camSpeed, 0 ) ;
                    } ) ;
                
                break ;
                
             case 'down' :
                
                if( !camProcesses.down )
                camProcesses.down = ogre.addAnimationProcess( function( elapsedTime )
                    {
                     camNode.moveL3N( 0, -( elapsedTime / 1000 ) * camSpeed, 0 ) ;
                    } ) ;             
                
                break ;
                    
            } 
            
        } ) ;
        
ogre.input.on( 'keyReleased', 

    function( keyEvent ) 
        {
        switch( keyEvent.keyName )
            {
             case 'left' :
                ogre.removeAnimationProcess( camProcesses.left ) ;  
                camProcesses.left = null ;       
                break ;
                
             case 'right' :
                ogre.removeAnimationProcess( camProcesses.right ) ;         
                camProcesses.right = null ;                 
                break ;
            
             case 'up' :
                
                 ogre.removeAnimationProcess( camProcesses.up ) ;         
                camProcesses.up = null ;
                
                break ;
                
             case 'down' :
                
                ogre.removeAnimationProcess( camProcesses.down ) ;                      
                camProcesses.down = null ;
                break ;
                    
            } 
        } ) ;


ogre.start( 100 ) ;
