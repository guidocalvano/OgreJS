#ifndef MATERIAL_JS_H
#define MATERIAL_JS_H

#include <OGRE/Ogre.h>
#include <v8.h>
#include <node_object_wrap.h>

#include <string>

class MaterialJS : public node::ObjectWrap
	{
	public:
	
	 static v8::Persistent<v8::FunctionTemplate> prototypeTemplate ;

	 Ogre::MaterialPtr material ;

	 static unsigned int nextUniqueId ;
	
	 static void init( v8::Handle< v8::Object > target) ;

	 static void initMaterialResources( v8::Handle< v8::Object > target ) ;

	 template< class ChildType >
	 static void addMaterialFunctionsToPrototype( v8::Handle<v8::FunctionTemplate> t )
		{
		 NODE_SET_PROTOTYPE_METHOD_BORROWED( t, "clone", cloneBind<ChildType> ) ;	
		
		 NODE_SET_PROTOTYPE_METHOD_BORROWED( t, "setAmbient", setAmbientBind<ChildType> ) ;	
	     NODE_SET_PROTOTYPE_METHOD_BORROWED( t, "setDiffuse", setDiffuseBind<ChildType> ) ;	
	     NODE_SET_PROTOTYPE_METHOD_BORROWED( t, "setSpecular", setSpecularBind<ChildType> ) ;	

		 NODE_SET_PROTOTYPE_METHOD_BORROWED( t, "setSelfIllumination", setSelfIlluminationBind<ChildType> ) ;	


	     NODE_SET_PROTOTYPE_METHOD_BORROWED( t, "setTexture", 		setTextureBind<ChildType> ) ;	
	     NODE_SET_PROTOTYPE_METHOD_BORROWED( t, "setTextureScroll", setTextureScrollBind<ChildType> ) ;	
	     NODE_SET_PROTOTYPE_METHOD_BORROWED( t, "setTextureScale", 	setTextureScaleBind<ChildType> ) ;	
		}
	
	 static v8::Handle<v8::Value> New( const v8::Arguments& args ) ;
	
	 static v8::Handle<v8::Value> NewFromMaterialPtr( Ogre::MaterialPtr material ) ;
	
	
	 MaterialJS( v8::Handle< v8::Object > object, Ogre::MaterialPtr material ) ;

	 ~MaterialJS() ;
	
	 static v8::Handle<v8::Value> Init( const v8::Arguments& args ) ;		
	
	 static std::string getNextUniqueId() ;
	
	
	 static v8::Handle<v8::Value> setDiffuseConvert( MaterialJS* materialJS, const v8::Arguments& args ) ;	
	
	 template< class ChildType >
	 static v8::Handle<v8::Value> setDiffuseBind( const v8::Arguments& args )
	 	{
		 MaterialJS* materialJS = (MaterialJS*) node::ObjectWrap:: Unwrap<ChildType>( args.This() ) ; 
		
		 return setDiffuseConvert( materialJS, args ) ;
		} ;
		
		
	 static v8::Handle<v8::Value> setSpecularConvert( MaterialJS* materialJS, const v8::Arguments& args ) ;	

	 template< class ChildType >
	 static v8::Handle<v8::Value> setSpecularBind( const v8::Arguments& args )
	 	{
		 MaterialJS* materialJS = (MaterialJS*) node::ObjectWrap:: Unwrap<ChildType>( args.This() ) ; 

		 return setSpecularConvert( materialJS, args ) ;
		} ;
	
	

	 static v8::Handle<v8::Value> setAmbientConvert( MaterialJS* materialJS, const v8::Arguments& args ) ;	

	 template< class ChildType >
	 static v8::Handle<v8::Value> setAmbientBind( const v8::Arguments& args )
	 	{
		 MaterialJS* materialJS = (MaterialJS*) node::ObjectWrap:: Unwrap<ChildType>( args.This() ) ; 

		 return setAmbientConvert( materialJS, args ) ;
		} ;

	
	 
	 static v8::Handle<v8::Value> setSelfIlluminationConvert( MaterialJS* materialJS, const v8::Arguments& args ) ;	

	 template< class ChildType >
	 static v8::Handle<v8::Value> setSelfIlluminationBind( const v8::Arguments& args )
	 	{
		 MaterialJS* materialJS = (MaterialJS*) node::ObjectWrap:: Unwrap<ChildType>( args.This() ) ; 

		 return setSelfIlluminationConvert( materialJS, args ) ;
		} ;

	
	 static v8::Handle<v8::Value> setTextureConvert( MaterialJS* materialJS, const v8::Arguments& args ) ;	

	 template< class ChildType >
	 static v8::Handle<v8::Value> setTextureBind( const v8::Arguments& args )
	 	{
		 MaterialJS* materialJS = (MaterialJS*) node::ObjectWrap:: Unwrap<ChildType>( args.This() ) ; 

		 return setTextureConvert( materialJS, args ) ;
		} ;
	
	
	 static v8::Handle<v8::Value> setTextureScrollConvert( MaterialJS* materialJS, const v8::Arguments& args ) ;	

	 template< class ChildType >
	 static v8::Handle<v8::Value> setTextureScrollBind( const v8::Arguments& args )
	 	{
		 MaterialJS* materialJS = (MaterialJS*) node::ObjectWrap:: Unwrap<ChildType>( args.This() ) ; 

		 return setTextureScrollConvert( materialJS, args ) ;
		} ;
	
	
	 static v8::Handle<v8::Value> setTextureScaleConvert( MaterialJS* materialJS, const v8::Arguments& args ) ;	

	 template< class ChildType >
	 static v8::Handle<v8::Value> setTextureScaleBind( const v8::Arguments& args )
	 	{
		 MaterialJS* materialJS = (MaterialJS*) node::ObjectWrap:: Unwrap<ChildType>( args.This() ) ; 

		 return setTextureScaleConvert( materialJS, args ) ;
		} ;
		
	
	 static v8::Handle<v8::Value> cloneConvert( MaterialJS* materialJS, const v8::Arguments& args ) ;	

	 template< class ChildType >
	 static v8::Handle<v8::Value> cloneBind( const v8::Arguments& args )
	 	{
		 MaterialJS* materialJS = (MaterialJS*) node::ObjectWrap:: Unwrap<ChildType>( args.This() ) ; 

		 return cloneConvert( materialJS, args ) ;
		} ;
	
	} ;
	
	
	
#endif