


#include <v8.h>
#include <node_object_wrap.h>
#include <OGRE/Ogre.h>



class OgreJS
	{
	public:
	 static void require(  v8::Handle< v8::Object > target ) ;

	 static v8::Handle<v8::Value> setupDefault( const v8::Arguments& args) ;
	} ;