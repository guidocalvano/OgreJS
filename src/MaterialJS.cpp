#include <MaterialJS.h>



v8::Persistent<v8::FunctionTemplate> MaterialJS:: prototypeTemplate ;
unsigned int MaterialJS:: nextUniqueId ;


void MaterialJS:: init( v8::Handle< v8::Object > target) 
	{
		nextUniqueId = 1 ;
		
   	 v8::Local<v8::FunctionTemplate> t = v8::FunctionTemplate::New(New);

   	 prototypeTemplate = v8::Persistent<v8::FunctionTemplate>::New(t);
   	 prototypeTemplate->InstanceTemplate()->SetInternalFieldCount(1);
   	 prototypeTemplate->SetClassName(v8::String::NewSymbol("Material"));

	
	 addMaterialFunctionsToPrototype<MaterialJS>( prototypeTemplate ) ;

   	 target->Set(v8::String::NewSymbol("Material"),
                prototypeTemplate-> GetFunction() );	

	 // added resource manager loaded materials
	} 
	
void MaterialJS:: initMaterialResources( v8::Handle< v8::Object > target ) 
	{
	 v8::Handle<v8::Object> materialSet = v8::Object::New() ;
	
	 target-> Set( v8::String::NewSymbol("materialSet"), materialSet ) ;
     
	 Ogre:: MaterialManager:: ResourceMapIterator materialIterator = Ogre::MaterialManager::getSingletonPtr()-> getResourceIterator() ;
	
	 Ogre:: MaterialPtr next ;
	
	
	 while( materialIterator.hasMoreElements() )
		{
		 next = materialIterator.getNext() ;
		
		 materialSet-> Set( v8::String::New( next-> getName().c_str() ), MaterialJS:: NewFromMaterialPtr( next ) ) ;
		}
	
	}
	
v8::Handle<v8::Value> MaterialJS:: New( const v8::Arguments& args ) 
	{
	 Ogre::MaterialPtr material = Ogre::MaterialManager::getSingleton().create( getNextUniqueId(), Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME ) ;
		
	 new MaterialJS( args.This(), material ) ;
	
	 return args.This() ;
	}

std::string MaterialJS:: getNextUniqueId()
	{
	 std::string nextIdString = "ogreJS_" ;
	 
	 nextIdString += (char) ( MaterialJS:: nextUniqueId / 256 ) ;
	 nextIdString += (char) ( MaterialJS:: nextUniqueId % 256 ) ;
	
	return nextIdString ;
	}
	
MaterialJS::MaterialJS( v8::Handle< v8::Object > object, Ogre:: MaterialPtr material )
	{
	 this-> material = material ;
	
	 Wrap( object ) ;
	}

MaterialJS::~MaterialJS() {}
	
v8::Handle<v8::Value> MaterialJS:: NewFromMaterialPtr( Ogre::MaterialPtr material ) 
	{
	 v8::Local<v8::Function> function = MaterialJS::prototypeTemplate-> GetFunction() ;
	 v8::Local<v8::Object>   object   = function-> NewInstance() ;
	
	 new MaterialJS( object, material ) ;
	
	 return object ;
	}

	
v8::Handle<v8::Value> MaterialJS:: setDiffuseConvert( MaterialJS* materialJS, const v8::Arguments& args ) 
	{
	 Ogre::Real red 	= (Ogre::Real) v8::Local< v8::Number >::Cast( args[ 0 ] )-> Value() ;
	 Ogre::Real green	= (Ogre::Real) v8::Local< v8::Number >::Cast( args[ 1 ] )-> Value() ;
	 Ogre::Real blue	= (Ogre::Real) v8::Local< v8::Number >::Cast( args[ 2 ] )-> Value() ;

	 Ogre::Real alpha   =  args.Length() == 3 ? (Ogre::Real) 1.0 : (Ogre::Real) v8::Local< v8::Number >::Cast( args[ 3 ] )-> Value() ;
	
	 materialJS-> material-> setDiffuse( red, green, blue, alpha ) ;
	}
	
