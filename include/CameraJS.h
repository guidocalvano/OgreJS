

#include <v8.h>
#include <node_object_wrap.h>
#include <OGRE/Ogre.h>



class CameraJS : node::ObjectWrap
	{
	public:

//	 static void init( v8::Handle< v8::Object > target) ;

//	 static v8::Handle<v8::Value> New( v8::Handle< v8::Object > target ) ;
	 static v8::Handle<v8::Value> NewFromCamera( Ogre::Camera* camera ) ;

	 static v8::Handle<v8::Value> renderOneFrame( const v8::Arguments& args ) ;



	 static v8::Handle<v8::Value> yaw( const v8::Arguments& args ) ;
	 static v8::Handle<v8::Value> pitch( const v8::Arguments& args ) ;
	 static v8::Handle<v8::Value> roll( const v8::Arguments& args ) ;

	 static v8::Handle<v8::Value> moveL3N( const v8::Arguments& args ) ;


	 Ogre:: Camera* camera ;

	} ;

