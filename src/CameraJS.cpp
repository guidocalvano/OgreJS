
#include <CameraJS.h>
#include <OgreManager.h>
#include <EntityJS.h>
#include <PickingManagerJS.h>
#include <OgreJS.h>

v8::Handle<v8::Value> CameraJS:: NewFromCamera( Ogre::Camera* camera )
	{

	 v8::Handle<v8::ObjectTemplate> objectTemplate = v8::ObjectTemplate::New();
	 objectTemplate->SetInternalFieldCount(1);

	 v8::Handle< v8::Object > cameraJSObject = objectTemplate->NewInstance() ;

	 v8::Handle< v8::FunctionTemplate > f = v8::FunctionTemplate::New( renderOneFrame ) ;
	 cameraJSObject-> Set( v8::String::New( "renderOneFrame" ), f->GetFunction()   ) ;

	 f = v8::FunctionTemplate::New( pick ) ;
	 cameraJSObject-> Set( v8::String::New( "pick" ), f->GetFunction()   ) ;

	 f = v8::FunctionTemplate::New( setParent ) ;
	 cameraJSObject-> Set( v8::String::New( "setParent" ), f->GetFunction()   ) ;
/*
	 f = v8::FunctionTemplate::New( roll ) ;
	 cameraJSObject-> Set( v8::String::New( "roll" ), f->GetFunction()   ) ;

	 f = v8::FunctionTemplate::New( pitch ) ;
	 cameraJSObject-> Set( v8::String::New( "pitch" ), f->GetFunction()   ) ;

	 f = v8::FunctionTemplate::New( yaw ) ;
	 cameraJSObject-> Set( v8::String::New( "yaw" ), f->GetFunction()   ) ;

	 f = v8::FunctionTemplate::New( moveL3N ) ;
	 cameraJSObject-> Set( v8::String::New( "moveL3N" ), f->GetFunction()   ) ;
*/

	 CameraJS* cameraJS = new CameraJS() ;

	 cameraJS-> camera = camera ;
	
	cameraJS-> parent = NULL ;
	
	cameraJS-> setParent( OgreJS:: singleton-> root ) ;
	 
	 cameraJS-> Wrap( cameraJSObject ) ;



	 return cameraJSObject ;
	}


 v8::Handle<v8::Value> CameraJS:: renderOneFrame( const v8::Arguments& args ) 
	{

	 OgreManager:: getSingletonPtr() -> m_pRoot->renderOneFrame() ;

	 return v8::Undefined() ;
	}


 v8::Handle<v8::Value> CameraJS:: pick( const v8::Arguments& args ) 
	{
   	 CameraJS* cam = ObjectWrap::Unwrap<CameraJS>(args.This());


	 int x = args[ 0 ]-> ToInteger()-> Value() ;
	 int y = args[ 1 ]-> ToInteger()-> Value() ;
	
	
	 double normalisedScreenX = ( (double) x ) / OgreManager:: getSingletonPtr()-> m_pViewport-> getActualWidth() ;
	 double normalisedScreenY = ( (double) y ) / OgreManager:: getSingletonPtr()-> m_pViewport-> getActualHeight() ;
		
	 // EntityJS* entityJS = OgreJS::singleton-> pickingManagerJS-> pick( x, y ) ;
	 Ogre::Ray mouseRay = cam-> camera-> getCameraToViewportRay( normalisedScreenX, normalisedScreenY ) ;
	 Ogre::Vector3 hitCoordinate ;
	
	 EntityJS* entityJS = OgreJS::singleton-> pickingManagerJS-> pick( mouseRay, hitCoordinate ) ;
	
	 if( entityJS != NULL )
		{ 
		 v8::Handle<v8::Object> entityHitTuple = v8::Object::New() ;

		 entityHitTuple-> Set( v8::String::New( "entity" ), entityJS-> handle_ ) ;

		 v8::Handle<v8::Object> hitVector = v8::Object::New() ;
		
		 hitVector-> Set( v8::String::New( "x" ), v8:: Number:: New( hitCoordinate.x ) ) ;
		 hitVector-> Set( v8::String::New( "y" ), v8:: Number:: New( hitCoordinate.y ) ) ;
		 hitVector-> Set( v8::String::New( "z" ), v8:: Number:: New( hitCoordinate.z ) ) ;
		 
		 entityHitTuple-> Set( v8::String::New( "point" ), hitVector ) ;

		 return entityHitTuple ;
		}
	 
	 return v8::Undefined() ;
	}
	
	
v8::Handle<v8::Value> CameraJS:: setParent( const v8::Arguments& args ) 
	{
	 CameraJS* cameraJS = node::ObjectWrap:: Unwrap<CameraJS>( args.This() ) ;
	
	 SceneNodeJS* newParent ;
	 if( !( args[ 0 ]-> IsNull() ) )	
		newParent 	  = node:: ObjectWrap::Unwrap<SceneNodeJS>( v8::Local<v8::Object>:: Cast( args[ 0 ] ) ) ;
	 else
		newParent = NULL ;
		
	 cameraJS-> setParent( newParent ) ;
	
	 return v8:: Undefined() ;
	}
	
	
void CameraJS:: setParent( SceneNodeJS* newParent )
	{
	 if( parent != NULL )
		{
		 parent-> sceneNode-> detachObject( camera ) ;
		}

	 if( newParent )
		{
		 parent = newParent ;
		
		 newParent-> sceneNode-> attachObject( camera ) ;
		}		
	}

/*
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
*/

