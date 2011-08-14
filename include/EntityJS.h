
#ifndef ENTITY_JS_H
#define ENTITY_JS_H

#include <OGRE/Ogre.h>
#include <v8.h>
#include <node_object_wrap.h>

#include <SceneNodeJS.h>
#include <OgreManager.h>

class EntityJS : public node::ObjectWrap
	{
	public:

	 EntityJS( v8::Local<v8::Object> object, const char* mesh  ) ;

	 static void init( v8::Handle< v8::Object > target) ;

	 static v8::Handle<v8::Value> New( const v8::Arguments& args ) ;

	 static v8::Handle<v8::Value> setParent( const v8::Arguments& args ) ;


	 static v8::Persistent<v8::FunctionTemplate> prototypeTemplate ;


	 v8::Local<v8::Object> object ;

	 Ogre::Entity* entity ;


	 SceneNodeJS* parent ;
	} ;


#endif
