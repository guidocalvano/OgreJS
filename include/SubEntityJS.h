

#ifndef SUB_ENTITY_JS_H
#define SUB_ENTITY_JS_H

#include <OGRE/Ogre.h>
#include <v8.h>
#include <node_object_wrap.h>

#include <SceneNodeJS.h>
#include <OgreManager.h>

class SubEntityJS : public node::ObjectWrap
	{
	public:
		
	 static v8::Persistent<v8::FunctionTemplate> prototypeTemplate ;
		
	 Ogre::SubEntity* subEntity ;
	
	 
	 SubEntityJS() ;
	 

	 static void init( v8::Handle< v8::Object > target) ;

	 static v8::Handle<v8::Value> New( const v8::Arguments& args  ) ;	 
	
	 static v8::Handle<v8::Value> NewFromSubEntity( Ogre::SubEntity* subEntity ) ;	 


	 template< class ChildType >
	 static void addSubEntityFunctionsToPrototype( v8::Handle<v8::FunctionTemplate> t )
		{
	     NODE_SET_PROTOTYPE_METHOD_BORROWED( t, "setMaterialByName", setMaterialByNameBind<ChildType> 	) ;	
	     NODE_SET_PROTOTYPE_METHOD_BORROWED( t, "setMaterial", 		 setMaterialBind<ChildType> 		) ;	
	     NODE_SET_PROTOTYPE_METHOD_BORROWED( t, "getMaterialName", 	 getMaterialNameBind<ChildType> 	) ;	
		}

	 static v8::Handle<v8::Value> setMaterialByNameConvert( SubEntityJS* ,const v8::Arguments& args ) ;	 
	
	 template< class ChildType >
	 static v8::Handle<v8::Value> setMaterialByNameBind( const v8::Arguments& args ) 
	 	{
		 SubEntityJS* subEntityJS = (SubEntityJS*) node::ObjectWrap:: Unwrap<ChildType>( args.This() ) ;
		 return setMaterialByNameConvert( subEntityJS, args ) ;
		}


	 static v8::Handle<v8::Value> getMaterialNameConvert( SubEntityJS* ,const v8::Arguments& args ) ;	 

	 template< class ChildType >
	 static v8::Handle<v8::Value> getMaterialNameBind( const v8::Arguments& args ) 
	 	{
		 SubEntityJS* subEntityJS = (SubEntityJS*) node::ObjectWrap:: Unwrap<ChildType>( args.This() ) ;
		 return getMaterialNameConvert( subEntityJS, args ) ;
		}

	 static v8::Handle<v8::Value> setMaterialConvert( SubEntityJS* ,const v8::Arguments& args ) ;	 		
		
	 template< class ChildType >
	 static v8::Handle<v8::Value> setMaterialBind( const v8::Arguments& args ) 
	 	{
		 SubEntityJS* subEntityJS = (SubEntityJS*) node::ObjectWrap:: Unwrap<ChildType>( args.This() ) ;
		 return setMaterialConvert( subEntityJS, args ) ;
		}
	} ;
	
	
#endif