// EXPERIMENTAL CODE. Don't use!
// Don't rely on any interfaces in this file until this notice goes away!
#if !defined(V8_CONVERT_ARGUMENTS_HPP_INCLUDED)
#define V8_CONVERT_ARGUMENTS_HPP_INCLUDED
#include "convert.hpp"
#include <limits>

namespace v8 { namespace convert {

    /**
        A functor which fetches an argument by index.
        
        I = the argument index to fetch.
        
        The class is intended mainly to be invoked via code paths 
        selected by template metaprograms, thus the hard-coding of 
        the argument parameter index at compile-time.
    */
    template <int I>
    struct ArgAt
    {
        typedef char AssertIndex[ (I>=0) ? 1 : -1];
        /**
            Returns argv[I] if argv.Length() is <= I, else v8::Undefined()
            is returned.
        */
        v8::Handle<v8::Value> operator()( v8::Arguments const & argv ) const
        {
            return (argv.Length() > I) ? argv[I] : v8::Undefined();
        }
    };

    /**
        Functor to fetch an argument and return its result
        as a native value.
        
        I = the argument index to fetch.
        
        T = the native type to convert to. CastFromJS<T>() must be legal.
    */
    template <int I, typename T>
    struct ArgAtCast
    {
        typedef JSToNative<T> J2N;
        typedef typename J2N::ReturnType ReturnType;
        typedef char AssertIndex[ (I>=0) ? 1 : -1];
        /**
            Returns CastFromJS<T>( ArtAt<I>(argv) ).
        */
        ReturnType operator()( v8::Arguments const & argv ) const
        {
            typedef ArgAt<I> Proxy;
            return CastFromJS<T>( Proxy()(argv) );
        }
    };

    /**
        Marker class, for documentation purposes.
    */
    struct ValuePredicateConcept
    {
        /**
            Must evaluate the handle and return true or false.
            The framework cannot guaranty that h.IsEmpty() is false,
            so implementations should be in the habit of checking it.
        */
        bool operator()( v8::Handle<v8::Value> const & h ) const;
    };

    /**
        A functor interface for determining if a JS value
        "is-a" value of a particular native type. The default
        implementation is useable for any type for which the
        following is legal:
        
        @code
        T * t = CastFromJS<T const *>( aV8Handle );
        @endcode
        
        Specializations are used for most data types, but this
        one is fine for client-bound types conformant with
        CastFromJS().

        Note that the default specializations treat T as a plain type,
        discarding const/pointer/reference qualifiers. Certain types may
        require that ValIs<T const &> (and similar) be specialized in order
        to behave properly.        
    */
    template <typename T>
    struct ValIs : ValuePredicateConcept
    {
        typedef T Type;
        /**
            Returns true if v appears to contain a (T*).
        */
        inline bool operator()( v8::Handle<v8::Value> const & v ) const
        {
            return NULL != CastFromJS<T const *>(v);
        }
    };
    
    template <typename T> struct ValIs<T const> : ValIs<T> {};
    template <typename T> struct ValIs<T const &> : ValIs<T> {};
    template <typename T> struct ValIs<T *> : ValIs<T> {};
    template <typename T> struct ValIs<T const *> : ValIs<T> {};

    /**
        Specialization which treats void as the v8::Undefined() value.
    */
    template <>
    struct ValIs<void>
    {
        typedef void Type;
        /**
            Returns true only if h is not empty and h->IsUndefined(). Note
            that an empty handle evaluates to false in this context because
            Undefined is a legal value whereas an empty handle is not.
            (Though Undefined might not be semantically legal in any given
            use case.)            
        */
        inline bool operator()( v8::Handle<v8::Value> const & h ) const
        {
            return h.IsEmpty() ? false : h->IsUndefined();
        }
    };

#if !defined(DOXYGEN)    
    namespace Detail {
        /**
            ValuePredicateConcept impl which returns retrue if
            Getter returns true for the given value.
        
            Getter must be a pointer to one of the v8::Value::IsXXX()
            functions. This functor returns true if the passed-in handle is
            not empty and it's IsXXX() function returns true.
        */
        template <bool (v8::Value::*Getter)() const>
        struct ValIs_X : ValuePredicateConcept
        {
            inline bool operator()( v8::Handle<v8::Value> const & v ) const
            {
                return v.IsEmpty() ? false : ((*v)->*Getter)();
            }  
        };

        /**
            A ValuePredicateConcept impl which returns true only if 
            the given handle is-a number and the number is in the 
            inclusive range std::numeric_limits<NumT>::min .. 
            max().
        */
        template <typename NumT>
        struct ValIs_NumberStrictRange : ValuePredicateConcept
        {
            typedef NumT Type;
            inline bool operator()( v8::Handle<v8::Value> const & h ) const
            {
                if( h.IsEmpty() || ! h->IsNumber() ) return false;
                else
                {
                    double const dv( h->NumberValue() );
                    return (dv >= std::numeric_limits<NumT>::min())
                        && (dv <= std::numeric_limits<NumT>::max());
                }
            }
        };
        /** Special-case specialization which returns true if the given
            handle is-a Number (without checking the range, which is 
            not necessary for this specific type in this context.
        */
        template <>
        struct ValIs_NumberStrictRange<double>
        {
            typedef double Type;
            inline bool operator()( v8::Handle<v8::Value> const & h ) const
            {
                return !h.IsEmpty() && h->IsNumber();
            }
        };
    }
#endif // DOXYGEN

    struct ValIs_Array :  Detail::ValIs_X<&v8::Value::IsArray> {};
    struct ValIs_Object : Detail::ValIs_X<&v8::Value::IsObject> {};
    struct ValIs_Boolean : Detail::ValIs_X<&v8::Value::IsBoolean> {};
    struct ValIs_Date : Detail::ValIs_X<&v8::Value::IsDate> {};
    struct ValIs_External : Detail::ValIs_X<&v8::Value::IsExternal> {};
    struct ValIs_False : Detail::ValIs_X<&v8::Value::IsFalse> {};
    struct ValIs_Function : Detail::ValIs_X<&v8::Value::IsFunction> {};
    struct ValIs_Int32 : Detail::ValIs_X<&v8::Value::IsInt32> {};
    struct ValIs_UInt32 : Detail::ValIs_X<&v8::Value::IsUint32 /* Note the "UInt" vs "Uint" descrepancy. i consider Uint to be wrong.*/ > {};
    struct ValIs_Null : Detail::ValIs_X<&v8::Value::IsNull> {};
    struct ValIs_Undefined : Detail::ValIs_X<&v8::Value::IsUndefined> {};
    struct ValIs_Number : Detail::ValIs_X<&v8::Value::IsNumber> {};
    struct ValIs_RegExp : Detail::ValIs_X<&v8::Value::IsRegExp> {};
    struct ValIs_String : Detail::ValIs_X<&v8::Value::IsString> {};
    struct ValIs_True : Detail::ValIs_X<&v8::Value::IsTrue> {};

    // FIXME: reverse the parent relationships between e.g. ValIs<v8::Array> and ValIs_Array.
    template <> struct ValIs<int8_t> : Detail::ValIs_NumberStrictRange<int8_t> {};
    template <> struct ValIs<uint8_t> : Detail::ValIs_NumberStrictRange<uint8_t> {};
    template <> struct ValIs<int16_t> : Detail::ValIs_NumberStrictRange<int16_t> {};
    template <> struct ValIs<uint16_t> : Detail::ValIs_NumberStrictRange<uint16_t> {};
    template <> struct ValIs<int32_t> : Detail::ValIs_NumberStrictRange<int32_t> {};
    template <> struct ValIs<uint32_t> : Detail::ValIs_NumberStrictRange<uint32_t> {};
    template <> struct ValIs<int64_t> : Detail::ValIs_NumberStrictRange<int64_t> {};
    template <> struct ValIs<uint64_t> : Detail::ValIs_NumberStrictRange<uint64_t> {};
    template <> struct ValIs<double> : ValIs_Number {};
    template <> struct ValIs<char const *> : ValIs_String {};
    template <> struct ValIs<std::string> : ValIs_String {};
    template <> struct ValIs<v8::Array> : ValIs_Array {};
    template <> struct ValIs<v8::Object> : ValIs_Object {};
    template <> struct ValIs<v8::Boolean> : ValIs_Boolean {};
    template <> struct ValIs<v8::Date> : ValIs_Date {};
    template <> struct ValIs<v8::External> : ValIs_External {};
    template <> struct ValIs<v8::Function> : ValIs_Function {};
    template <> struct ValIs<v8::Int32> : ValIs_Int32 {};
    template <> struct ValIs<v8::Uint32> : ValIs_UInt32 {};
    template <> struct ValIs<v8::Number> : ValIs_Number {};
    template <> struct ValIs<v8::RegExp> : ValIs_RegExp {};
    template <> struct ValIs<v8::String> : ValIs_String {};
    template <typename T> struct ValIs< v8::Handle<T> > : ValIs< T > {};
    template <typename T> struct ValIs< v8::Local<T> > : ValIs< T > {};
    template <typename T> struct ValIs< v8::Persistent<T> > : ValIs< T > {};

    /**
        Marker class, for documentation purposes.
        
        Classes matching this concept "evaluate" a v8::Arguments 
        object for validity without actually performing any 
        "application logic." These are inended to be used as 
        functors, primarily triggered via code paths selected by 
        template metaprograms.
        
        They must be default-construcable and should have no
        private state. Their public API consists of only operator().

        This Concept's operator() is intended only to be used for 
        decision-making purposes ("are there enough arguments?" or 
        "are the arguments of the proper types?"), and not 
        higher-level application logic.
    */
    struct ArgumentsPredicateConcept
    {
        /**
            Must "evaluate" the arguments and return true or false. 
        */
        bool operator()( v8::Arguments const & ) const;
    };

    /**
        Functor to evaluate whether an Arguments list
        has a certain range of argument count.
        
        Min is the minimum number. Max is the maximum. The range is 
        inclusive. Use (Max<Min) to mean (at least MIN). Use 
        (Min==Max) to mean only that many arguments.
    */
    template <int Min_, int Max_ = Min_>
    struct ArgPred_Length : ArgumentsPredicateConcept
    {
        enum { Min = Min_, Max = Max_ };
        /**
            Returns true if av meets the argument count
            requirements defined by the Min and Max
            values.
        */
        bool operator()( v8::Arguments const & av ) const
        {
            
            int const argc = av.Length();
            return (Max < Min)
                ? argc >= Min
                : (argc>=Min) && (argc<=Max);
        }
    };

    /**
        Arguments predicate functor.
    
        Index = arg index to check.
        
        ValIsType must match the ValuePredicateConcept interface.
    */
    template <unsigned short Index, typename ValIsType >
    struct ArgAt_Is : ArgumentsPredicateConcept
    {
        /**
            Returns true if ValType()( av[Index] ) is true.
        */
        bool operator()( v8::Arguments const & av ) const
        {
            return (Index >= av.Length())
                ? false
                : ValIsType()( av[Index] );
        }
    };

    /**
        Arguments predicate functor.
    
        Index = arg index to check.
        
        T is a type for which ValIs<T> is legal. The functor
        returns true if ValIs<T> returns true the argument
        at the given index.
    */
    template <unsigned short Index, typename T>
    struct ArgAt_IsA : ArgAt_Is< Index, ValIs<T> > {};

#if !defined(DOXYGEN)   
    namespace Detail {
        /**
            Functor which proxies the v8::Value "is-a" functions.
            
            Index is the argument index to check. Getter is the 
            member to be used to perform the is-a evaluation.
        */
        template <unsigned short Index, bool (v8::Value::*Getter)() const>
        struct ArgAt_IsX : ArgumentsPredicateConcept
        {
            /**
                Returns true only if (Index < av.Length())
                and av->Getter() returns true.
            */
            bool operator()( v8::Arguments const & av ) const
            {
                return ( av.Length() <= Index )
                    ? false
                    : ((*av[Index])->*Getter)();
            }  
        };
    }
#endif // DOXYGEN
    template <unsigned short Index>
    struct ArgAt_IsArray : Detail::ArgAt_IsX<Index, &v8::Value::IsArray> {};

    template <unsigned short Index>
    struct ArgAt_IsObject : Detail::ArgAt_IsX<Index, &v8::Value::IsObject> {};

    template <unsigned short Index>
    struct ArgAt_IsBoolean : Detail::ArgAt_IsX<Index, &v8::Value::IsBoolean> {};

    template <unsigned short Index>
    struct ArgAt_IsDate : Detail::ArgAt_IsX<Index, &v8::Value::IsDate> {};

    template <unsigned short Index>
    struct ArgAt_IsExternal : Detail::ArgAt_IsX<Index, &v8::Value::IsExternal> {};

    template <unsigned short Index>
    struct ArgAt_IsFalse : Detail::ArgAt_IsX<Index, &v8::Value::IsFalse> {};

    template <unsigned short Index>
    struct ArgAt_IsFunction : Detail::ArgAt_IsX<Index, &v8::Value::IsFunction> {};

    template <unsigned short Index>
    struct ArgAt_IsInt32 : Detail::ArgAt_IsX<Index, &v8::Value::IsInt32> {};

    template <unsigned short Index>
    struct ArgAt_IsUInt32 : Detail::ArgAt_IsX<Index, &v8::Value::IsUint32> {};

    template <unsigned short Index>
    struct ArgAt_IsNull : Detail::ArgAt_IsX<Index, &v8::Value::IsNull> {};
    
    template <unsigned short Index>
    struct ArgAt_IsUndefined : Detail::ArgAt_IsX<Index, &v8::Value::IsUndefined> {};

    template <unsigned short Index>
    struct ArgAt_IsNumber : Detail::ArgAt_IsX<Index, &v8::Value::IsNumber> {};

    template <unsigned short Index>
    struct ArgAt_IsRegExp : Detail::ArgAt_IsX<Index, &v8::Value::IsRegExp> {};

    template <unsigned short Index>
    struct ArgAt_IsString : Detail::ArgAt_IsX<Index, &v8::Value::IsString> {};

    template <unsigned short Index>
    struct ArgAt_IsTrue : Detail::ArgAt_IsX<Index, &v8::Value::IsTrue> {};



#if 0 // i don't think i like this stuff...
    template <typename T>
    struct ValCanBe : ValuePredicateConcept
    {
        inline bool operator()( v8::Handle<v8::Value> const & v ) const
        {
            return NULL != CastFromJS<T const *>(v);
        }
    };
    template <>
    struct ValCanBe<void>
    {
        inline bool operator()( v8::Handle<v8::Value> const & v ) const
        {
            return v.IsEmpty() || v->IsUndefined();
        }
    };
    
    template <typename T>
    struct ValCanBe_AnyNonEmpty
    {
        typedef T Type;
        inline bool operator()( v8::Handle<v8::Value> const & h ) const
        {
            return !h.IsEmpty();
        }
    };
    
#if 0
    struct ValCanBe_Number
    {
        inline bool operator()( v8::Handle<v8::Value> const & h ) const
        {
            return ( h.IsEmpty() )
                ? false
                : h->IsNumber();
        }
    };
#endif

    template <typename NumT>
    struct ValCanBe_NumberStrictRange : ValIs_NumberStrictRange<NumT> {};

    template <>
    struct ValCanBe<bool> : ValCanBe_AnyNonEmpty<bool> {};
    template <>
    struct ValCanBe<int8_t> : ValCanBe_NumberStrictRange<int8_t> {};
    template <>
    struct ValCanBe<uint8_t> : ValCanBe_NumberStrictRange<uint8_t> {};
    template <>
    struct ValCanBe<int16_t> : ValCanBe_NumberStrictRange<int16_t> {};
    template <>
    struct ValCanBe<uint16_t> : ValCanBe_NumberStrictRange<uint16_t> {};
    template <>
    struct ValCanBe<int32_t> : ValCanBe_NumberStrictRange<int32_t> {};
    template <>
    struct ValCanBe<uint32_t> : ValCanBe_NumberStrictRange<uint32_t> {};
    template <>
    struct ValCanBe<int64_t> : ValCanBe_NumberStrictRange<int64_t> {};
    template <>
    struct ValCanBe<uint64_t> : ValCanBe_NumberStrictRange<uint64_t> {};
    template <>
    struct ValCanBe<double> : ValCanBe_NumberStrictRange<double> {};
    template <>
    struct ValCanBe<char const *> : ValCanBe_AnyNonEmpty<char const *> {};
    template <>
    struct ValCanBe<std::string> : ValCanBe_AnyNonEmpty<std::string> {};

#endif
} }

#endif
