
#include "juice/ogre/Vector.hpp"

#include "v8/convert/properties.hpp"

namespace juice{ namespace ogre{

  void Vector::bind( v8::Handle<v8::Object> dest )
  {
    //Obtain the singleton that holds the JS definitions for this class.
    CC & cc(CC::Instance());
    
    //If the definition has already been defined,
    if( cc.IsSealed() )
    {
      //Just add the definitions to the object.
      cc.AddClassTo( "Vector", dest );
      return;
    }
    
    //--------------------------------------------------------------
    //-- Bind functions
    //--------------------------------------------------------------
    
    //Bind the normalise() function
    cc("normalise",
                 //The first argument is the class type
                 //The second argument is the function signature
                 //The third argument is the member function pointer
                 cv::ToInCa<self_type, Ogre::Real (),&self_type::normalise>::Call);
    //--------------------------------------------------------------
    
    //--------------------------------------------------------------
    //-- Bind accessors/mutators
    //--------------------------------------------------------------
    //Shortcut typedef
    typedef cv::MemberPropertyBinder<self_type> PB;

    //We can bind accessors/mutators directly to the prototype.
    v8::Handle<v8::ObjectTemplate> const & proto( cc.Prototype() );
    
    //Bind getX()/setX()
    //The first template parameter is the getter signature
    //The second template paramter is the getter member function pointer
    //The third template paramter is the setter signature
    //The fourth template paramter is the setter member function pointer
    //The first argument is the name of the accessor/mutator
    //The second paramter is the prototype to add it to
    PB::BindGetterSetterMethods<Ogre::Real() , &self_type::getX,
                void (Ogre::Real), &self_type::setX
                >("x", proto);

    //Ditto
    PB::BindGetterSetterMethods<Ogre::Real (), &self_type::getY,
                void (Ogre::Real), &self_type::setY
                >("y", proto);

    //Ditto
    PB::BindGetterSetterMethods<Ogre::Real (), &self_type::getZ,
                void (Ogre::Real), &self_type::setZ
                >("z", proto);
    //--------------------------------------------------------------
    
    //Add the JS definitions to the object passed in
    cc.AddClassTo( "Vector", dest );
  }
  
  
}}//namespaces juice::ogre

//-----------------------------------
// Policies used by cv::ClassCreator (it also has others)
namespace v8 { namespace convert {
  // This is to "name" the class; used in some error reporting. This is the definition; the declaration is in the header file.
  template <>
  char const * TypeName< juice::ogre::Vector >::Value = "ogre.Vector";
}}// namespaces v8::convert

