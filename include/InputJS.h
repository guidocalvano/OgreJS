


#include <v8.h>
#include <node_object_wrap.h>
#include <OGRE/Ogre.h>

#include <OIS/OISEvents.h>
#include <OIS/OISInputManager.h>
#include <OIS/OISKeyboard.h>
#include <OIS/OISMouse.h>

class InputJS : public node::ObjectWrap, OIS::KeyListener, OIS::MouseListener
	{
	public:

//	 static void init( v8::Handle< v8::Object > target) ;

	 static v8::Handle<v8::Value> NewFromOgreManager() ;

	 static v8::Handle<v8::Value> captureUI( const v8::Arguments& args ) ;

	 bool keyPressed(const OIS::KeyEvent &keyEventRef);
	 bool keyReleased(const OIS::KeyEvent &keyEventRef);

	 bool mouseMoved(const OIS::MouseEvent &evt);
	 bool mousePressed(const OIS::MouseEvent &evt, OIS::MouseButtonID id); 
	 bool mouseReleased(const OIS::MouseEvent &evt, OIS::MouseButtonID id);

	 v8::Local<v8::Object> mouseEventToObject( const OIS::MouseEvent &evt) ;
	 v8::Local<v8::Object> keyEventToObject( const OIS::KeyEvent &keyEventRef ) ;


	 v8::Handle<v8::Object> inputJSObject ;

	} ;