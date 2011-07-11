#if !defined(CODE_GOOGLE_COM_P_V8_CONVERT_PROPERTIES_HPP_INCLUDED)
#define CODE_GOOGLE_COM_P_V8_CONVERT_PROPERTIES_HPP_INCLUDED 1
/** LICENSE

    This software's source code, including accompanying documentation and
    demonstration applications, are licensed under the following
    conditions...

    The author (Stephan G. Beal [http://wanderinghorse.net/home/stephan/])
    explicitly disclaims copyright in all jurisdictions which recognize
    such a disclaimer. In such jurisdictions, this software is released
    into the Public Domain.

    In jurisdictions which do not recognize Public Domain property
    (e.g. Germany as of 2011), this software is Copyright (c) 2011
    by Stephan G. Beal, and is released under the terms of the MIT License
    (see below).

    In jurisdictions which recognize Public Domain property, the user of
    this software may choose to accept it either as 1) Public Domain, 2)
    under the conditions of the MIT License (see below), or 3) under the
    terms of dual Public Domain/MIT License conditions described here, as
    they choose.

    The MIT License is about as close to Public Domain as a license can
    get, and is described in clear, concise terms at:

    http://en.wikipedia.org/wiki/MIT_License

    The full text of the MIT License follows:

    --
    Copyright (c) 2011 Stephan G. Beal (http://wanderinghorse.net/home/stephan/)

    Permission is hereby granted, free of charge, to any person
    obtaining a copy of this software and associated documentation
    files (the "Software"), to deal in the Software without
    restriction, including without limitation the rights to use,
    copy, modify, merge, publish, distribute, sublicense, and/or sell
    copies of the Software, and to permit persons to whom the
    Software is furnished to do so, subject to the following
    conditions:

    The above copyright notice and this permission notice shall be
    included in all copies or substantial portions of the Software.

    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
    EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
    OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
    NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
    HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
    WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
    FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
    OTHER DEALINGS IN THE SOFTWARE.

    --END OF MIT LICENSE--

    For purposes of the above license, the term "Software" includes
    documentation and demonstration source code which accompanies
    this software. ("Accompanies" = is contained in the Software's
    primary public source code repository.)

*/

#include "invocable.hpp"

namespace v8 { namespace convert {

    /**
       This class contains static methods which can be used to bind
       global/class-static/shared native variables to JS space.

       Note that it cannot bind file- or function-scope static
       variables because C++ does not allow pointers to them to be
       used as template parameters (for linking reasons).

       For binding member functions to accessors, see the
       MemberPropertyBinder class (which subclasses this one, for
       usage convenience).
    */
    class PropertyBinder
    {
    public:
        /**
           This template can be used as an argument to
           v8::ObjectTemplate::SetAccessor()'s Getter parameter to
           generically tie a static variable to a named JS property.

           SharedVar must be pointer to a static variable and must not
           be 0.

           CastToJS<PropertyType>() must be legal.
        */
        template <typename PropertyType, PropertyType const * SharedVar>
        static v8::Handle<v8::Value> AccessorGetterStaticVar(v8::Local<v8::String> property, const AccessorInfo &info)
        {
            return CastToJS<PropertyType>( *SharedVar );
        }
        /**
           The setter counterpart of AccessorGetterStaticVar().

           SharedVar must be pointer to a static variable and must not
           be 0.

           CastFromJS<PropertyType> must be legal.
        */
        template <typename PropertyType, PropertyType * SharedVar>
        static void AccessorSetterStaticVar(v8::Local<v8::String> property, v8::Local<v8::Value> value, const v8::AccessorInfo& info)
        {
            *SharedVar = CastFromJS<PropertyType>( value );
        }

        /**
           Binds the given static variable to a JS property, such that
           get/set access will go through
           AccessorGetterStaticVar<VarType,SharedVar> and
           AccessorSetterStaticVar<VarType,SharedVar>.
        */
        template <typename VarType, VarType * SharedVar>
        static void BindSharedVar( char const * name,
                                   v8::Handle<v8::ObjectTemplate> const & prototype,
                                   v8::AccessControl settings = v8::PROHIBITS_OVERWRITING,
                                   v8::PropertyAttribute attribute = v8::DontDelete
                         )
        {
            if( ! prototype.IsEmpty() )
            {
                prototype->SetAccessor( v8::String::New(name),
                                        AccessorGetterStaticVar<VarType,SharedVar>,
                                        AccessorSetterStaticVar<VarType,SharedVar>,
                                        v8::Handle< v8::Value >(),
                                        settings,
                                        attribute );
            }
        }

        /**
           A Setter implementation which always triggers a JS exception.
        */
        static void AccessorSetterThrow(v8::Local<v8::String> property, v8::Local<v8::Value> value, const v8::AccessorInfo& info)
        {
             ::v8::ThrowException(StringBuffer() <<
                                  "Native member property setter '"
                                  << property
                                  << "' is configured to throw an exception when modifying "
                                  << "this read-only member!");
        }

        /**
           Binds the given static variable to a JS property, such that
           read access will go through
           AccessorGetterStaticVar<VarType,SharedVar> and set access will be
           ignored (it will not change SharedVar).

           The throwOnSet parameter installs a custom setter which,
           when triggered, always throws a JS exception. If this value
           is false, no setter will be installed (and see the notes in
           MemberPropertyBinder::BindMemVarRO()). If you want
           v8-specified behaviours, pass false for this value.
        */
        template <typename VarType, VarType const * SharedVar>
        static void BindSharedVarRO( char const * name,
                                     v8::Handle<v8::ObjectTemplate> const & prototype,
                                     bool throwOnSet = false,
                                     v8::AccessControl settings = v8::PROHIBITS_OVERWRITING,
                                     v8::PropertyAttribute attribute = v8::DontDelete )
        {
            if( ! prototype.IsEmpty() )
            {
                prototype->SetAccessor( v8::String::New(name),
                                        AccessorGetterStaticVar<VarType,SharedVar>,
                                        throwOnSet ? AccessorSetterThrow : (v8::AccessorSetter)NULL,
                                        v8::Handle< v8::Value >(),
                                        v8::PROHIBITS_OVERWRITING,
                                        attribute );
            }
        }

        /**
           Implements the v8::AccessorGetter interface to bind a JS
           member property to a native getter function. This function
           can be used as the getter parameter to
           v8::ObjectTemplate::SetAccessor().

           Sig must be a function-signature-style type and Getter must
           capable of being called with no arguments and returning a
           value which can be CastToJS() to a JS value.

           If Getter() throws a native exception it is converted to a JS
           exception.
        */
        template <typename Sig, typename FunctionSignature<Sig>::FunctionType Getter>
        static v8::Handle<v8::Value> FunctionToAccesorGetter( Local< String > property, const AccessorInfo & info )
        {
            try
            {
                return CastToJS( (*Getter)() );
            }
            catch( std::exception const & ex )
            {
                return ::v8::ThrowException( ::v8::String::New(ex.what()) );
            }
            catch( ... )
            {
                return ::v8::ThrowException( StringBuffer() << "Native value property getter '"
                                             << property << "' threw an unknown native exception type!");
            }
        }

        /**
           Binds the templatized getter function to the given JS property of the
           given prototype object, such that JS-side read access to the property
           will return the value of that member function.

           See FunctionToAccesorGetter() for the semantics of the Sig type.

           If Getter() throws a native exception it is converted to a JS
           exception.
           
           WEIRD: beware of this odd behaviour:

           @code
           BindGetterFunction<std::string // WEIRD: if i add () or (void) here,
                                  // the template doesn't resolve!
                      getSharedString>("sharedString", myProtoType);
           @endcode

        */
        template <typename Sig, typename FunctionSignature<Sig>::FunctionType Getter>
        static void BindGetterFunction( char const * propName, v8::Handle<v8::ObjectTemplate> const & prototype )
	{
	    prototype->SetAccessor( v8::String::New( propName ),
                                    FunctionToAccesorGetter<Sig,Getter> );
	}

        
        /**
           Implements the v8::AccessorSetter interface to bind a JS
           member property to a native getter function. This function
           can be used as the getter parameter to
           v8::ObjectTemplate::SetAccessor().

           SigSet must be function-signature-style pattern
           for the setter function. The native
           function must follow conventional mutator signature:

           ReturnType ( PropertyType )

           PropertyType may differ from the return type. PropertyType
           may not be void but the ReturnType may be. Any return value
           from the setter is ignored by the JS engine.
           
           Note that the v8 API appears to not allow us to just set
           a setter, but not a getter. We have to set a getter without
           a setter, a getter with a setter, or neither. At least that's
           been my experience.

           If Setter() throws a native exception it is converted to a JS
           exception.

        */
        template <typename Sig, typename FunctionSignature<Sig>::FunctionType Func>
        static void FunctionToAccesorSetter(v8::Local< v8::String > property, v8::Local< v8::Value > value, const v8::AccessorInfo &info)
        {
            try
            {
                typedef FunctionSignature<Sig> FT;
                typedef Signature<Sig> STL;
                (*Func)( CastFromJS<typename sl::At<0,STL>::Type>( value ) );
            }
            catch( std::exception const & ex )
            {
                ::v8::ThrowException( ::v8::String::New(ex.what()) );
            }
            catch( ... )
            {
                v8::ThrowException( StringBuffer() << "Native member property setter '"
                                    << property << "' threw an unknown native exception type!");
            }
            return;
        }

        /**
           Binds the given JS property to a pair of non-member
           functions, such that these functions will be called in
           place of get/set operations for the property.

           SigGet and SigSet must be function-signature-style patterns
           for the getter resp. setter functions. The native
           functions must follow conventional accessor signatures:

           - SigGet: PropertyType ()
           - SigSet: AnyType ( PropertyType )

           For the setter, PropertyType may differ from the return
           type. PropertyType may not be void but the AnyType may
           be. Any return value from the setter is ignored by the JS
           engine.

           If Getter() or Setter() throw a native exception it is
           converted to a JS exception.
           
           Example:

           @code
           std::string getSharedString();
           void setSharedString(std::string const &);
           ...
           PropertyBinder::BindGetterSetterFunctions<std::string (),
                                            getSharedString,
                                            void (std::string const &),
                                            setSharedString>
                                            ("sharedString", prototypeObject);
           @endcode
        */
        template <typename SigGet,
                  typename FunctionSignature<SigGet>::FunctionType Getter,
                  typename SigSet,
                  typename FunctionSignature<SigSet>::FunctionType Setter
            >
        static void BindGetterSetterFunctions( char const * propName, v8::Handle<v8::ObjectTemplate> const & prototype )
	{
            if( ! prototype.IsEmpty() )
            prototype->SetAccessor( v8::String::New( propName ),
                                    FunctionToAccesorGetter<SigGet,Getter>,
                                    FunctionToAccesorSetter<SigSet,Setter> );
	}
       
    };

    /**
       A helper class for binding JS properties to native code, in particular
       for when JS objects are bound to native T objects.

       It contains utility functions to simplify the process of binding
       JS properties to native member functions or native properties.
       
       Requirements:

       - T must be of class type.

       - JSToNative<T> must be implemented for T.

       - TypeInfo<T>::NativeHandle must be usable in a boolean context
       to determine whether the JS-to-Native converted object is null
       or not.

       - The JS class to which members are bound using this approach
       must be set up so that it is actually wrapping T objects.
       i.e. this class only works with "fully bound" native classes,
       and not with arbitrary JS objects.
    */
    template <typename T>
    class MemberPropertyBinder : public PropertyBinder
    {
    public:
        typedef typename TypeInfo<T>::Type Type;
        typedef typename JSToNative<T>::ResultType NativeHandle;

        /**
           This template can be used as an argument to
           v8::ObjectTemplate::SetAccessor()'s Getter parameter to
           generically tie a native member variable to a named JS
           property.

           Requirements:

           - Type must be convertible to NativeHandle via CastFromJS<NativeHandle>().

           - PropertyType must be convertible via CastToJS<PropertyType>().

           If the underlying native This object cannot be found (that
           is, if CastFromJS<NativeHandle>() fails) then this routine will
           trigger a JS exception.

           Example:

           Assume we have a native type Foo with a std::string member
           called str. We can bind the member variable with:

           \code
           myObjectTemplate.SetAccessor(String::New("foo"),
           MemberToAccessorGetter<Foo,std::string,&Foo::str>,
           MemberToAccessorSetter<Foo,std::string,&Foo::str> );
           \endcode

           In 10 years of C++ coding, this is the first time i've ever
           had a use for a pointer-to-member.
        */
        template <typename PropertyType, PropertyType Type::*MemVar>
        static v8::Handle<v8::Value> MemberToAccessorGetter(v8::Local<v8::String> property, const v8::AccessorInfo &info)
        {
            NativeHandle self = CastFromJS<NativeHandle>( info.This() );
            if( ! self ) return v8::ThrowException( StringBuffer() << "Native member property getter '"
                                                    << property << "' could not access native This object!" );
            try
            {
                return CastToJS( (self->*MemVar) );
            }
            catch( std::exception const & ex )
            {
                return CastToJS( ex );
            }
            catch( ... )
            {
                return ::v8::ThrowException( StringBuffer() << "Native member property getter '"
                                             << property << "' threw an unknown native exception type!");
            }
        }

        /**
           This is the Setter counterpart of MemberToAccessorGetter(). See
           that function for most of the details.

           Requirements:

           - MemVar must be an accessible member of Type.
           - PropertyType must be convertible via CastFromJS<PropertyType>().

           If the underlying native This object cannot be found then this
           routine will trigger a JS exception, though it is currently
           unclear whether this is actually legal in v8 (and difficult to
           test, since the native bindings work so well ;).
        */
        template <typename PropertyType, PropertyType Type::*MemVar>
        static void MemberToAccessorSetter(v8::Local<v8::String> property, v8::Local<v8::Value> value, const v8::AccessorInfo& info)
        {
            NativeHandle self = CastFromJS<NativeHandle>( info.This() );
            if( self )
            {
                self->*MemVar = CastFromJS<PropertyType>( value );
            }
            else
            {
                v8::ThrowException( StringBuffer() << "Native member property setter '"
                                    << property << "' could not access native This object!" );
            }
        }

        
        /**
           Binds automatically-generated getter/setter functions to the given
           member variable. See MemberToAccessorGetter() and MemberToAccessorSetter()
           for the requirements of the templatized types.

           If you only want to bind one of the getter OR the setter then
           use the 5-argument variant of Set() instead and pass MemberToAccessorGetter<>
           or MemberToAccessorGetter<>, as appropriate, to that function.
        */
        template <typename VarType, VarType Type::*MemVar>
        static void BindMemVar( char const * name,
                                v8::Handle<v8::ObjectTemplate> const & prototype,
                                v8::AccessControl settings = v8::PROHIBITS_OVERWRITING,
                                v8::PropertyAttribute attribute = v8::DontDelete
                         )
        {
            if( ! prototype.IsEmpty() )
            {
                prototype->SetAccessor( v8::String::New(name),
                                        MemberToAccessorGetter<VarType,MemVar>,
                                        MemberToAccessorSetter<VarType,MemVar>,
                                        v8::Handle< v8::Value >(),
                                        settings,
                                        attribute );
            }
        }

        /**
           Binds the given JS property to MemVar, such that read/get
           operations will work but write/set operations will be
           ignored (that is, will not affect the value returned by the
           getter).

           The throwOnSet parameter installs a custom setter which,
           when triggered, always throws a JS exception. If this value
           is false, no setter will be installed (and see the notes
           below). If you want v8-specified behaviours, pass false
           for this value.
           
           Achtung: the JS engine exhibits the following, slightly
           unintuitive behaviour, for values bound in this way. Assume
           that we have bound an integer member to JS with the name
           "roVar" and we do the following in JS:

           @code
           ++myobj.roVar;
           @endcode

           The return value of that statement is actually the
           incremented value, but myobj.roVar is not actually modified
           and its accessor-setter is not called. Since the exact
           semantics of things like how native accessor proxies work
           are an unspecified part of the ECMAScript standard, we
           cannot complain that what v8 does here is "wrong" (it could
           arguably throw a JS exception in that case).
        */
        template <typename VarType, VarType Type::*MemVar>
        static void BindMemVarRO( char const * name,
                                  v8::Handle<v8::ObjectTemplate> const & prototype,
                                  bool throwOnSet = false,
                                  v8::AccessControl settings = v8::PROHIBITS_OVERWRITING,
                                  v8::PropertyAttribute attribute = v8::DontDelete )
        {
            if( ! prototype.IsEmpty() )
            {
                prototype->SetAccessor( v8::String::New(name),
                                        MemberToAccessorGetter<VarType,MemVar>,
                                        throwOnSet ? AccessorSetterThrow : (v8::AccessorSetter)NULL,
                                        v8::Handle< v8::Value >(),
                                        settings,
                                        attribute );
            }
        }
        /**
           Implements the v8::AccessorGetter interface to bind a JS
           member property to a native getter function. This function
           can be used as the getter parameter to
           v8::ObjectTemplate::SetAccessor().

           Sig must be a function-pointer-style argument with a
           non-void return type convertible to v8 via CastToJS(), and
           Getter must be function capable of being called with 0
           arguments (either because it has none or they have
           defaults).
        */
        template <typename Sig, typename MethodSignature<T,Sig>::FunctionType Getter>
        static v8::Handle<v8::Value> MethodToAccessorGetter( Local< String > property, const AccessorInfo & info )
        {
            NativeHandle self = CastFromJS<NativeHandle>( info.This() );
            if( ! self ) return v8::ThrowException( StringBuffer() << "Native member property getter '"
                                                    << property << "' could not access native This object!" );
            try
            {
                return convert::CastToJS( (self->*Getter)() );
            }
            catch( std::exception const & ex )
            {
                return CastToJS(ex);
            }
            catch( ... )
            {
                return ::v8::ThrowException( StringBuffer() << "Native member property getter '"
                                             << property << "' threw an unknown native exception type!");
            }
        }

        /**
           Overload for const native getter functions.
        */
        template <typename Sig, typename ConstMethodSignature<T,Sig>::FunctionType Getter>
        static v8::Handle<v8::Value> ConstMethodToAccessorGetter( v8::Local< v8::String > property, const v8::AccessorInfo & info )
        {
            NativeHandle const self = CastFromJS<NativeHandle>( info.This() );
            if( ! self ) return v8::ThrowException( StringBuffer() << "Native member property getter '"
                                                    << property << "' could not access native This object!" );
            try
            {
                return convert::CastToJS( (self->*Getter)() );
            }
            catch( std::exception const & ex )
            {
                return CastToJS(ex);
            }
            catch( ... )
            {
                return ::v8::ThrowException( StringBuffer() << "Native member property getter '"
                                             << property << "' threw an unknown native exception type!");
            }
        }

        /**
            Implements v8::AccessorSetter interface to proxy a JS
            member property through a native member setter function.

            This function can be used as the setter parameter to
            v8::ObjectTemplate::SetAccessor().

            Sig must be a function-pointer-style type and Getter must
            be a T member function of that type. The function must be
            capable of being called with only 1 argument (either
            because it only accepts 1 or has defaults for the others),
            and its return value is discarded (not converted to v8)
            because that's how v8's native setters work.

            Exceptions thrown by the underlying function are
            translated to JS exceptions.
        */
        template <typename Sig, typename MethodSignature<T,Sig>::FunctionType Setter>
        static void MethodToAccessorSetter(v8::Local< v8::String > property, v8::Local< v8::Value > value, const v8::AccessorInfo &info)
        {
            NativeHandle self = CastFromJS<NativeHandle>( info.This() );
            if( ! self )
            {
                v8::ThrowException( StringBuffer() << "Native member property setter '"
                                    << property << "' could not access native This object!" );
                return;
            }
            else try
            {

                typedef typename sl::At< 0, Signature<Sig> >::Type ArgT;
                (self->*Setter)( CastFromJS<ArgT>( value ) );
            }
            catch( std::exception const & ex )
            {
                CastToJS(ex);
            }
            catch( ... )
            {
                ::v8::ThrowException( StringBuffer() << "Native member property setter '"
                                      << property << "' threw an unknown native exception type!");
            }
            return;
        }

        /**
           Binds the given JS property to a pair of T member
           functions, such that these functions will be called in
           place of get/set operations for the property.

           See the inherited BindGetterSetterFunctions() for the full
           details. This function is identical except that it maps
           member functions.
        */
        template <typename SigGet,
                  typename ConstMethodSignature<T,SigGet>::FunctionType Getter,
                  typename SigSet,
                  typename MethodSignature<T,SigSet>::FunctionType Setter
            >
        static void BindGetterSetterMethods( char const * propName, v8::Handle<v8::ObjectTemplate> const & prototype )
	{
            if( ! prototype.IsEmpty() )
                prototype->SetAccessor( v8::String::New( propName ),
                                        ConstMethodToAccessorGetter<SigGet,Getter>,
                                        MethodToAccessorSetter<SigSet,Setter>
                                        );
	}

        /**
           Equivalent to BindGetterSetterMethods() but takes a
           non-const getter. Member setter functions are not, by
           nature, const. This function has a different name than
           BindGetterSetterMethods() because MSVC cannot distinguish
           between templates which differ only in constness.
        */
        template <typename SigGet,
                  typename MethodSignature<T,SigGet>::FunctionType Getter,
                  typename SigSet,
                  typename MethodSignature<T,SigSet>::FunctionType Setter
            >
        static void BindNonConstGetterSetterMethods( char const * propName, v8::Handle<v8::ObjectTemplate> const & prototype )
	{
            if( ! prototype.IsEmpty() )
                prototype->SetAccessor( v8::String::New( propName ),
                                        MethodToAccessorGetter<SigGet,Getter>,
                                        MethodToAccessorSetter<SigSet,Setter>
                                        );
	}

        

        /**
           Binds the templatized getter function to the given JS property of the
           given prototype object, such that JS-side read access to the property
           will return the value of that member function.

           Sig must be a function-pointer-style function signature and Getter must be
           a non-const T member function matching that signature.
         */
        template <typename Sig, typename MethodSignature<T,Sig>::FunctionType Getter>
        static void BindGetterMethod( char const * propName, v8::Handle<v8::ObjectTemplate> const & prototype )
	{
	    prototype->SetAccessor( v8::String::New( propName ),
                                    MethodToAccessorGetter<Sig,Getter> );
	}
        /**
           Overload too support const getters.
        */
        template <typename Sig, typename ConstMethodSignature<T,Sig>::FunctionType Getter>
        static void BindGetterConstMethod( char const * propName, v8::Handle<v8::ObjectTemplate> const & prototype )
	{
	    prototype->SetAccessor( v8::String::New( propName ),
                                    MethodToAccessorGetter<Sig,Getter> );
	}

    };

}} // namespaces

#endif /* CODE_GOOGLE_COM_P_V8_CONVERT_PROPERTIES_HPP_INCLUDED */
