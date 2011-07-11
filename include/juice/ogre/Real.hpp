#ifndef OGREJS_JUICE_OGRE_REAL_HPP
#define OGREJS_JUICE_OGRE_REAL_HPP

#include <v8.h>
#include "v8/convert/v8-convert.hpp"

#include <OgrePrerequisites.h>

namespace v8 { namespace convert {

  template <>
  struct NativeToJS<Ogre::Real>
  {
    v8::Handle<v8::Value> operator()( Ogre::Real const & Number ) const
    {
      return v8::Number::New(Number);
    }
  };
  
  template <>
  struct JSToNative<Ogre::Real>
  {
      typedef Ogre::Real ResultType;
      ResultType operator()( v8::Handle<v8::Value> const & h ) const
      {
        return h->IsNumber()
                ? h->NumberValue()
                : 0;
      }
  };
  
}}//namespaces v8::convert

#endif
