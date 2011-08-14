
#include <CameraJS.h>
#include <OgreManager.h>

v8::Handle<v8::Value> CameraJS:: NewFromCamera( Ogre::Camera* camera )
	{

	 v8::Handle<v8::ObjectTemplate> objectTemplate = v8::ObjectTemplate::New();
	 objectTemplate->SetInternalFieldCount(1);

	 v8::Handle< v8::Object > cameraJSObject = objectTemplate->NewInstance() ;

	 v8::Handle< v8::FunctionTemplate > f = v8::FunctionTemplate::New( renderOneFrame ) ;
	 cameraJSObject-> Set( v8::String::New( "renderOneFrame" ), f->GetFunction()   ) ;

	 f = v8::FunctionTemplate::New( roll ) ;
	 cameraJSObject-> Set( v8::String::New( "roll" ), f->GetFunction()   ) ;

	 f = v8::FunctionTemplate::New( pitch ) ;
	 cameraJSObject-> Set( v8::String::New( "pitch" ), f->GetFunction()   ) ;

	 f = v8::FunctionTemplate::New( yaw ) ;
	 cameraJSObject-> Set( v8::String::New( "yaw" ), f->GetFunction()   ) ;

	 f = v8::FunctionTemplate::New( moveL3N ) ;
	 cameraJSObject-> Set( v8::String::New( "moveL3N" ), f->GetFunction()   ) ;


	 CameraJS* cameraJS = new CameraJS() ;

	 cameraJS-> camera = camera ;
	
	 cameraJS-> Wrap( cameraJSObject ) ;

	 return cameraJSObject ;
	}

 v8::Handle<v8::Value> CameraJS:: renderOneFrame( const v8::Arguments& args ) 
	{

	 OgreManager:: getSingletonPtr() -> m_pRoot->renderOneFrame() ;

	 return v8::Undefined() ;
	}



 v8::Handle<v8::Value> CameraJS:: roll( const v8::Arguments& args ) 
	{
	 printf( "Roll\n" ) ;

    	 CameraJS* cam = ObjectWrap::Unwrap<CameraJS>(args.This());

	 printf( "Unwrap\n" ) ;

	 v8::Local< v8::Number > num ; 

	 num = v8::Local< v8::Number >::Cast( args[ 0 ] ) ;

	 printf( "Cast\n" ) ;

	 double v = num-> Value() ;;
	
	 printf( "Roll%f\n", (float) v ) ;

	 cam-> camera-> roll( (Ogre::Radian) v ) ;

	 return v8::Undefined() ;
	}


 v8::Handle<v8::Value> CameraJS:: pitch( const v8::Arguments& args ) 
	{
    	 CameraJS* cam = ObjectWrap::Unwrap<CameraJS>(args.This());

	 v8::Local< v8::Number > num ; 

	 num = v8::Local< v8::Number >::Cast( args[ 0 ] ) ;

	 double v = num-> Value() ;;
	
	 cam-> camera-> pitch( (Ogre::Radian) v ) ;

	 return v8::Undefined() ;
	}


 v8::Handle<v8::Value> CameraJS:: yaw( const v8::Arguments& args ) 
	{
    	 CameraJS* cam = ObjectWrap::Unwrap<CameraJS>(args.This());

	 v8::Local< v8::Number > num ; 

	 num = v8::Local< v8::Number >::Cast( args[ 0 ] ) ;

	 double v = num-> Value() ;;
	
	 cam-> camera-> yaw( (Ogre::Radian) v ) ;

	 return v8::Undefined() ;
	}


 v8::Handle<v8::Value> CameraJS:: moveL3N( const v8::Arguments& args ) 
	{
    	 CameraJS* cam = ObjectWrap::Unwrap<CameraJS>(args.This());

	 double x = ( v8::Local< v8::Number >::Cast( args[ 0 ] ) )->Value() ;
	 double y = ( v8::Local< v8::Number >::Cast( args[ 1 ] ) )->Value() ;
	 double z = ( v8::Local< v8::Number >::Cast( args[ 2 ] ) )->Value() ;

	 cam-> camera-> moveRelative( Ogre::Vector3( x, y, z ) ) ;
	 
	 return v8::Undefined() ;
	}


