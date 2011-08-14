

exports.system = system ; exports.Camera = Camera ; exports.Input = Input ; 



function Entity( meshname )
	{
	 this.cpp = new system.Entity( meshname ) ;

	 this.parent = null ;
	}


Entity.prototype.setParent = function( newParent ) 
	{
	 if( newParent == null ) 
		 this.cpp.setParent( newParent.cpp ) ;

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
	 if( newParent == null ) 
		this.cpp.setParent( null ) ;
	 else
		this.cpp.setParent( newParent.cpp ) ;

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

exports.SceneNode = SceneNode ;


function RootNode()
	{
	 this.cpp = system.root ;
	 this.parent = null ;

	 this.children = [] ;

	}

RootNode.prototype = SceneNode ;

exports.RootNode = RootNode ;

exports.root = new RootNode() ;

