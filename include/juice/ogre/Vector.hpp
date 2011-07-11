#ifndef OGREJS_JUICE_OGRE_VECTOR_HPP
#define OGREJS_JUICE_OGRE_VECTOR_HPP

#include <cassert>
#include <v8.h>
#include "v8/convert/v8-convert.hpp"
#include "v8/convert/NativeToJSMap.hpp"

#include <OgreVector3.h>

//We need the Ogre::Real conversion templates first
#include "juice/ogre/Real.hpp"

namespace juice{ namespace ogre{

// Convenience typedef:
namespace cv = v8::convert;

//-----------------------------------
// The type we want to bind to v8.
struct Vector
{
public:
//A typedef to itself
  typedef Vector self_type;
  
public:
//constructors
  //FIXME: v8convert seems to require a default ctor even if it isn't specified in the
  // list of constructors
  Vector()
    : m_vector(0.0, 0.0, 0.0)
  {}

  Vector(Ogre::Real fX, Ogre::Real fY, Ogre::Real fZ)
    : m_vector(fX, fY, fZ)
  {
    
  }
  
public:
//methods
  Ogre::Real normalise() {
    return m_vector.normalise();
  }
public:
//Accessors/Mutators
  Ogre::Real getX() const{
    return m_vector.x;
  }
  
  void setX(Ogre::Real x){
    m_vector.x = x;
  }
  
  Ogre::Real getY() const{
    return m_vector.y;
  }
  
  void setY(Ogre::Real y){
    m_vector.y = y;
  }
  
  Ogre::Real getZ() const{
    return m_vector.z;
  }
  
  void setZ(Ogre::Real z){
    m_vector.z = z;
  }
public:
//This is binding stuff
  // Ctors we want to bind to v8 (there are several other ways to do this):
  typedef cv::Signature<self_type (
      cv::CtorForwarder<self_type *(Ogre::Real fX, Ogre::Real fY, Ogre::Real fZ)>
  )> Ctors;

  //This is the class creator singleton for this class
  typedef cv::ClassCreator<self_type> CC;
  
  //Add this class's constructors to the JS object passed in as an argument
  static void bind( v8::Handle<v8::Object> dest );
private:
//Vector encapsulates Ogre::Vector3
  Ogre::Vector3 m_vector;
};

}}//namespaces juice::ogre

//-----------------------------------
// Policies used by cv::ClassCreator (it also has others)
namespace v8 { namespace convert {

  //This specialization defines how the class can be instantiated in Javascript, ie. which constructors exist.
  //The actual definition is inside the class.
  template <>
  class ClassCreator_Factory<juice::ogre::Vector>
   : public ClassCreator_Factory_CtorArityDispatcher< juice::ogre::Vector, juice::ogre::Vector::Ctors >
  {};
  
  //This tells v8convert how to convert from a JS ref to native type.
  //Since we are using ClassCreator, we will inherit and use its automated conversion function.
  template <>
  struct JSToNative< juice::ogre::Vector > : JSToNative_ClassCreator< juice::ogre::Vector >
  {};
  
  // This is to "name" the class; used in some error reporting. This is the declaration; the definition is in the implementation file.
  template <>
  char const * TypeName< juice::ogre::Vector >::Value;
}}// namespaces v8::convert


#endif
