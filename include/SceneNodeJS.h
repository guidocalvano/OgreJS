#ifndef SCENE_NODE_H
#define SCENE_NODE_H

#include <OGRE/Ogre.h>
#include <v8.h>
#include <node.h>

#include <OgreManager.h>


class SceneNodeJS : public node::ObjectWrap
	{
	public:

	 SceneNodeJS( v8::Local<v8::Object> object ) ;
	 ~SceneNodeJS() ;

	 static void init( v8::Handle< v8::Object > target) ;

	 static v8::Handle<v8::Value> createRoot() ;

	 static v8::Handle<v8::Value> New( const v8::Arguments& args ) ;

	 static v8::Handle<v8::Value> setParent( const v8::Arguments& args ) ;

	 static v8::Handle<v8::Value> moveL3N( const v8::Arguments& args ) ;


	 static v8::Persistent<v8::FunctionTemplate> prototypeTemplate ;
	

	 Ogre::SceneNode* sceneNode ;

	 v8::Local<v8::Object> object ;


	 SceneNodeJS* parent ;

	} ;


#endif