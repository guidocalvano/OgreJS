


#include <v8.h>
#include <node_object_wrap.h>
#include <OGRE/Ogre.h>
#include <MyGuiJS.h>
#include <PickingManagerJS.h>

class OgreJS
	{
	public:
		
	 static OgreJS* singleton ;
	
	 PickingManagerJS*  pickingManagerJS ;
	 SceneNodeJS* 		root ;
	
	 OgreJS() ;
	
		
	 static void require(  v8::Handle< v8::Object > target ) ;

	 static v8::Handle<v8::Value> setupDefault( const v8::Arguments& args) ;	 
	} ;