#if !defined(CODE_GOOGLE_COM_V8_CONVERT_INVOCABLE_V8_HPP_INCLUDED)
#define CODE_GOOGLE_COM_V8_CONVERT_INVOCABLE_V8_HPP_INCLUDED 1

/** @file invocable_core.hpp

This file houses the core-most "invocation-related" parts of the
v8-convert API. These types and functions are for converting
free and member functions to v8::InvocationCallback functions
so that they can be tied to JS objects. It relies on the
CastToJS() and CastFromJS() functions to do non-function type
conversion.
   
*/

#include "convert_core.hpp"
#include "signature_core.hpp"
#include "TypeList.hpp"

namespace v8 { namespace convert {

/**
    A marker class, primarily for documentation purposes.
*/
struct Callable
{
    /**
        Matches the v8::InvocationCallback interface. All function 
        bindings created by this framework use this function as 
        their class-level InvocationCallback interface.
    */
    static v8::Handle<v8::Value> Call( v8::Arguments const & );
};

/**
   Partial specialization for v8::InvocationCallback-like functions
   (differing only in their return type) with an Arity value of -1.
*/
template <typename RV>
struct FunctionSignature< RV (v8::Arguments const &) > : SignatureBase<RV (v8::Arguments const &)>
{
    typedef RV (*FunctionType)(v8::Arguments const &);
};

/**
   Partial specialization for v8::InvocationCallback-like non-const
   member functions (differing only in their return type) with an
   Arity value of -1.
*/
template <typename T, typename RV >
struct MethodSignature< T, RV (Arguments const &) > : SignatureBase< RV (v8::Arguments const &) >
{
    typedef T Type;
    typedef RV (T::*FunctionType)(Arguments const &);
};

/**
   Partial specialization for v8::InvocationCallback-like const member
   functions (differing only in their return type) with an Arity value
   of -1.
*/
template <typename T, typename RV >
struct ConstMethodSignature< T, RV (Arguments const &) > : SignatureBase< RV (v8::Arguments const &) >
{
    typedef T Type;
    typedef RV (T::*FunctionType)(Arguments const &) const;
};

/**
   Full specialization for InvocationCallback and
   InvocationCallback-like functions (differing only by their return
   type), which uses an Arity value of -1.
*/
template <typename RV, RV (*FuncPtr)(v8::Arguments const &) >
struct FunctionPtr<RV (v8::Arguments const &),FuncPtr>
    : FunctionSignature<RV (v8::Arguments const &)>
{
    public:
    typedef FunctionSignature<RV (v8::Arguments const &)> SignatureType;
    typedef typename SignatureType::ReturnType ReturnType;
    typedef typename SignatureType::FunctionType FunctionType;
    static FunctionType GetFunction()
     {
         return FuncPtr;
     }
};

/**
   Full specialization for InvocationCallback and
   InvocationCallback-like functions (differing only by their return
   type), which uses an Arity value of -1.
*/
template <typename T,typename RV, RV (T::*FuncPtr)(v8::Arguments const &) >
struct MethodPtr<T, RV (T::*)(v8::Arguments const &),FuncPtr>
    : MethodSignature<T, RV (T::*)(v8::Arguments const &)>
{
    typedef MethodSignature<T, RV (T::*)(v8::Arguments const &)> SignatureType;
    typedef typename SignatureType::ReturnType ReturnType;
    typedef typename SignatureType::FunctionType FunctionType;
    static FunctionType GetFunction()
     {
         return FuncPtr;
     }
};

/**
   Full specialization for InvocationCallback and
   InvocationCallback-like functions (differing only by their return
   type), which uses an Arity value of -1.
*/
template <typename T,typename RV, RV (T::*FuncPtr)(v8::Arguments const &) const >
struct ConstMethodPtr<T, RV (T::*)(v8::Arguments const &) const,FuncPtr>
    : ConstMethodSignature<T, RV (T::*)(v8::Arguments const &) const>
{
    typedef ConstMethodSignature<T, RV (T::*)(v8::Arguments const &) const> SignatureType;
    typedef typename SignatureType::ReturnType ReturnType;
    typedef typename SignatureType::FunctionType FunctionType;
    static FunctionType GetFunction()
     {
         return FuncPtr;
     }
};

#if !defined(DOXYGEN)
namespace Detail {
    /**
        A sentry class which instantiates a v8::Unlocker
        if the boolean value is true or is a no-op if it is false.
    */
    template <bool> struct V8Unlocker;
    
    /**
        Equivalent to v8::Unlocker.
    */
    template <>
    struct V8Unlocker<true> : v8::Unlocker
    {
    };
    /**
        A no-op specialization.
    */
    template <>
    struct V8Unlocker<false>
    {
    };
    
    

}
#endif

/**
    A metatemplate which we can use to determine if a given type
    is "safe" to use in conjunction with v8::Unlock.
    
    We optimistically assume that most types are safe and
    add specializations for types we know are not safe, e.g.
    v8::Handle<Anything> and v8::Arguments.
    
    Specializations of this type basically make up a collective 
    "blacklist" of types which we know are not legal to use unless 
    v8 is locked by our current thread. As new problematic types are 
    discovered, they can be added to the blacklist by introducing a 
    specialization of this class.
*/
template <typename T>
struct IsUnlockable : tmp::BoolVal<true> {};
template <typename T>
struct IsUnlockable<T const> : IsUnlockable<T> {};
template <typename T>
struct IsUnlockable<T const &> : IsUnlockable<T> {};
template <typename T>
struct IsUnlockable<T *> : IsUnlockable<T> {};
template <typename T>
struct IsUnlockable<T const *> : IsUnlockable<T> {};

/**
    Explicit instantiation to make damned sure that nobody
    re-sets this one. We rely on these semantics for 
    handling FunctionSignature like Const/MethodSignature
    in some cases.
*/
template <>
struct IsUnlockable<void> : tmp::BoolVal<true> {};

/*
    Todo?: find a mechanism to cause certain highly illegal types to 
    always trigger an assertion... We could probably do it by 
    declaring but not definiting JSToNative/NativeToJS 
    specialializations.
*/
template <>
struct IsUnlockable<void *> : tmp::BoolVal<false> {};

template <>
struct IsUnlockable<void const *> : tmp::BoolVal<false> {};

template <typename T>
struct IsUnlockable< v8::Handle<T> > : tmp::BoolVal<false> {};

template <typename T>
struct IsUnlockable< v8::Persistent<T> > : tmp::BoolVal<false> {};

template <typename T>
struct IsUnlockable< v8::Local<T> > : tmp::BoolVal<false> {};

template <>
struct IsUnlockable<v8::Arguments> : tmp::BoolVal<false> {};

/**
    Given a tmp::TypeList-compatible type list, this metafunction's
    Value member evalues to true if IsUnlockable<T>::Value is
    true for all types in TList, else Value evaluates to false.
    As a special case, an empty list evaluates to true because in this
    API an empty list will refer to a function taking no arguments.
*/
template <typename TList>
struct TypeListIsUnlockable;

#if !defined(DOXYGEN)
namespace Detail
{
    template <typename ListType>
    struct TypeListIsUnlockableImpl : tmp::BoolVal<
        IsUnlockable<typename ListType::Head>::Value && TypeListIsUnlockableImpl<typename ListType::Tail>::Value
        >
    {
    };

    template <>
    struct TypeListIsUnlockableImpl< tmp::NilType > : tmp::BoolVal<true>
    {};
   
}
#endif

/**
    Given a TypeList, this metatypeplate's Value member evaluates
    to true if IsUnlockable<T>::Value is true for every type
    in the typelist.
*/
template <typename TList>
struct TypeListIsUnlockable : Detail::TypeListIsUnlockableImpl<TList>
{
};

/**
    Given a Signature, this metafunction's Value member
    evaluates to true if:
    
    - IsUnlockable<SigTList::ReturnType>::Value is true and...
    
    - IsUnlockable<SigTList::Context>::Value is true (only relavent
    for Const/MethodSignature, not FunctionSignature) and...
    
    - TypeListIsUnlockable< SigTList >::Value is true.
    
    If the value is true, the function signature has passed the most 
    basic check for whether or not it is legal to use v8::Unlocker 
    to unlock v8 before calling a function with this signature. Note 
    that this is a best guess, but this code cannot know 
    app-specific conditions which might make this guess invalid. 
    e.g. if a bound function itself uses v8 and does not explicitly 
    acquire a lock then the results are undefined (and will very 
    possibly trigger an assertion in v8, killing the app). Such 
    things can and do happen. If you're lucky, you're building 
    against a debug version of libv8 and its assertion text will 
    point you directly to the JS code which caused the assertion, 
    then you can disable unlocking support for that binding.    

    If you want to disable unlocking for all bound members of a given
    class, create an IsUnlockable<T> specialization whos Value 
    member evaluates to false. Then no functions/methods using that 
    class will cause this metafunction to evaluate to true.
    
    Note that FunctionToInCa, Const/MethodToInCa, etc., are all
    Signature subclasses, and can be used directly with
    this template.
    
    Example:
    
    @code
    // This one can be unlocked:
    typedef FunctionSignature< int (int) > F1;
    // SignatureIsUnlockable<F1>::Value == true
    
    // This one cannot because it contains a v8 type in the arguments:
    typedef FunctionSignature< int (v8::Handle<v8::Value>) > F2;
    // SignatureIsUnlockable<F2>::Value == false
    @endcode
    
    For Const/MethodToInCa types, this check will also fail if
    IsUnlockable< SigTList::Context >::Value is false.
*/
template <typename SigTList>
struct SignatureIsUnlockable : tmp::BoolVal<
        IsUnlockable<typename SigTList::Context>::Value &&
        IsUnlockable<typename SigTList::ReturnType>::Value &&
        IsUnlockable<typename SigTList::Head>::Value &&
        SignatureIsUnlockable<typename SigTList::Tail>::Value
        > {};
//! End-of-list specialization.
template <>
struct SignatureIsUnlockable<tmp::NilType> : tmp::BoolVal<true> {};

/**
    Internal exception type to allow us to differentiate
    "no native 'this' pointer found" errors from all other
    exceptions. It is thrown by the CallNative() functions
    of various JS-to-Native function forwarders.
*/
struct MissingThisException
{
protected:
    StringBuffer msg;
    template <typename T>
    void init()
    {
        this->msg << "CastFromJS<"<< TypeName<T>::Value
        << ">() returned NULL. Throwing to avoid "
        << "dereferencing a NULL pointer!";
    }
    MissingThisException() {}
public:
    /**
        Returns the exception message text, which does not change
        after construction.
    */
    StringBuffer const & Buffer() const { return msg; }
};


#if !defined(DOXYGEN)
namespace Detail {
/** Temporary internal macro. Undef'd at the end of this file. */
#define HANDLE_PROPAGATE_EXCEPTION catch( MissingThisException const & ex ){ return TossMissingThis<T>(); } \
            catch(...){ throw; } (void)0
   
    /**
        Internal helper to create an exception when we require
        a native (T*) pointer and don't find one. Returns the result
        of v8::ThrowException(...).
    */  
    template <typename T>
    v8::Handle<v8::Value> TossMissingThis()
    {
        return Toss(StringBuffer()<<"CastFromJS<"<<TypeName<T>::Value<<">() returned NULL! Cannot find 'this' pointer!");
    }

    /**
        A MissingThisException type holding generic
        message text which references TypeName<T>::Value
        as being the problematic class.
    */
    template <typename T>
    struct MissingThisExceptionT : MissingThisException
    {
        MissingThisExceptionT()
        {
            this->init<T>();
        }
    };

/**
    Temporary internal macro to trigger a static assertion if unlocking
    support is requested but cannot be implemented for the given
    wrapper due to constraints on our use of v8 when it is unlocked.
*/
#define ASSERT_UNLOCKV8_IS_FALSE typedef char ThisSpecializationCannotUseV8Unlocker[!UnlockV8 ? 1 : -1]
/**
    Temporary internal macro to trigger a static assertion if: 
    UnlockV8 is true and SignatureIsUnlockable<Sig>::Value is false. 
    This is to prohibit that someone accidentally enables locking 
    when using a function type which we know (based on its 
    signature's types) cannot obey the locking rules.
*/
#define ASSERT_UNLOCK_SANITY_CHECK typedef char AssertCanEnableUnlock[ \
    !UnlockV8 ? 1 : (cv::SignatureIsUnlockable< SignatureType >::Value ?  1 : -1) \
    ]

    /*
        FIXME: ArgsToFunctionForwarder doesn't really need the Arity
        template parameter anymore.
    */

    template <int Arity_, typename Sig,
            bool UnlockV8 = cv::SignatureIsUnlockable< cv::Signature<Sig> >::Value >
    struct ArgsToFunctionForwarder;
    
    template <int Arity, typename RV, bool UnlockV8>
    struct ArgsToFunctionForwarder<Arity,RV (v8::Arguments const &), UnlockV8>
        : FunctionSignature<RV (v8::Arguments const &)>
    {
    public:
        typedef FunctionSignature<RV (v8::Arguments const &)> SignatureType;
        typedef typename SignatureType::FunctionType FunctionType;
        typedef typename SignatureType::ReturnType ReturnType;
        static ReturnType CallNative( FunctionType func, Arguments const & argv )
        {
            return (RV) func(argv);
        }

        static v8::Handle<v8::Value> Call( FunctionType func, Arguments const & argv )
        {
            return cv::CastToJS( CallNative( func, argv ) );
        }

        ASSERT_UNLOCKV8_IS_FALSE;
        typedef char AssertArity[ sl::Arity<SignatureType>::Value == -1 ? 1 : -1];
    };

    //! Reminder to self: we really do need this specialization for some cases.
    template <int Arity, typename RV, bool UnlockV8>
    struct ArgsToFunctionForwarder<Arity,RV (*)(v8::Arguments const &), UnlockV8>
        : ArgsToFunctionForwarder<Arity,RV (v8::Arguments const &), UnlockV8>
    {};

    template <typename Sig, bool UnlockV8>
    struct ArgsToFunctionForwarder<0,Sig, UnlockV8> : FunctionSignature<Sig>
    {
        typedef FunctionSignature<Sig> SignatureType;
        typedef typename SignatureType::ReturnType ReturnType;
        typedef typename SignatureType::FunctionType FunctionType;
        static ReturnType CallNative( FunctionType func, Arguments const & argv )
        {
            V8Unlocker<UnlockV8> unlocker;
            return func();
        }
        static v8::Handle<v8::Value> Call( FunctionType func, Arguments const & argv )
        {
            return CastToJS( CallNative( func, argv ) );
        }
        ASSERT_UNLOCK_SANITY_CHECK;
        typedef char AssertArity[ sl::Arity<SignatureType>::Value == 0 ? 1 : -1];
    };

    template <int Arity_, typename Sig,
                bool UnlockV8 = SignatureIsUnlockable< Signature<Sig> >::Value>
    struct ArgsToFunctionForwarderVoid;

    template <typename Sig, bool UnlockV8>
    struct ArgsToFunctionForwarderVoid<0,Sig, UnlockV8> : FunctionSignature<Sig>
    {
        typedef FunctionSignature<Sig> SignatureType;
        typedef typename SignatureType::ReturnType ReturnType;
        typedef Sig FunctionType;
        static ReturnType CallNative( FunctionType func, Arguments const & argv )
        {
            V8Unlocker<UnlockV8> const unlocker();
            return (ReturnType)func()
            /* the explicit cast there is a workaround for the RV==void
               case. It is a no-op for other cases, since the return value
               is already RV. Some compilers (MSVC) don't allow an explicit
               return of a void expression without the cast.
            */;
        }
        static v8::Handle<v8::Value> Call( FunctionType func, Arguments const & argv )
        {
            CallNative( func, argv );
            return v8::Undefined();
        }
        ASSERT_UNLOCK_SANITY_CHECK;
        typedef char AssertArity[ sl::Arity<SignatureType>::Value == 0 ? 1 : -1];
    };
    
    template <int Arity, typename RV, bool UnlockV8>
    struct ArgsToFunctionForwarderVoid<Arity,RV (v8::Arguments const &), UnlockV8>
        : FunctionSignature<RV (v8::Arguments const &)>
    {
    public:
        typedef FunctionSignature<RV (v8::Arguments const &)> SignatureType;
        typedef typename SignatureType::FunctionType FunctionType;
        typedef typename SignatureType::ReturnType ReturnType;
        static ReturnType CallNative( FunctionType func, Arguments const & argv )
        {
            V8Unlocker<UnlockV8> const unlocker();
            return (ReturnType)func(argv);
        }
        static v8::Handle<v8::Value> Call( FunctionType func, Arguments const & argv )
        {
            CallNative( func, argv );
            return v8::Undefined();
        }
        ASSERT_UNLOCKV8_IS_FALSE;
        typedef char AssertArity[ sl::Arity<SignatureType>::Value == -1 ? 1 : -1];
    };

    /**
        Internal impl for v8::convert::ArgsToConstMethodForwarder.
    */
    template <typename T, int Arity_, typename Sig,
             bool UnlockV8 = cv::SignatureIsUnlockable< MethodSignature<T, Sig> >::Value
     >
    struct ArgsToMethodForwarder;


    template <typename T, typename Sig, bool UnlockV8>
    struct ArgsToMethodForwarder<T, 0, Sig, UnlockV8> : MethodSignature<T,Sig>
    {
    public:
        typedef MethodSignature<T,Sig> SignatureType;
        typedef typename SignatureType::ReturnType ReturnType;
        typedef typename SignatureType::FunctionType FunctionType;
        typedef typename TypeInfo<T>::Type Type;
        static ReturnType CallNative( T & self, FunctionType func, v8::Arguments const & argv )
        {
            V8Unlocker<UnlockV8> const unlocker();
            return (self.*func)();
        }
        static v8::Handle<v8::Value> Call( T & self, FunctionType func, v8::Arguments const & argv )
        {
            try
            {
                return CastToJS( CallNative( self, func, argv ) );
            }
            HANDLE_PROPAGATE_EXCEPTION;
        }
        static ReturnType CallNative( FunctionType func, v8::Arguments const & argv )
        {
            T * self = CastFromJS<T>(argv.This());
            if( ! self ) throw MissingThisExceptionT<T>();
            return (ReturnType)CallNative(*self, func, argv);
        }
        static v8::Handle<v8::Value> Call( FunctionType func, v8::Arguments const & argv )
        {
            try
            {
                return CastToJS( CallNative( func, argv ) );
            }
            HANDLE_PROPAGATE_EXCEPTION;
        }
        
        ASSERT_UNLOCK_SANITY_CHECK;
    };

    template <typename T, int Arity, typename RV, bool UnlockV8>
    struct ArgsToMethodForwarder<T, Arity, RV (v8::Arguments const &), UnlockV8>
        : MethodSignature<T, RV (v8::Arguments const &)>
    {
    public:
        typedef MethodSignature<T, RV (v8::Arguments const &)> SignatureType;
        typedef char AssertArity[ sl::Arity<SignatureType>::Value == -1 ? 1 : -1];
        typedef typename SignatureType::FunctionType FunctionType;
        typedef typename SignatureType::ReturnType ReturnType;
        static ReturnType CallNative( T & self, FunctionType func, v8::Arguments const & argv )
        {
            return (self.*func)(argv);
        }
        static v8::Handle<v8::Value> Call( T & self, FunctionType func, v8::Arguments const & argv )
        {
            try
            {
                return CastToJS( CallNative( self, func, argv ) );
            }
            HANDLE_PROPAGATE_EXCEPTION;
        }
        static ReturnType CallNative( FunctionType func, v8::Arguments const & argv )
        {
            T * self = CastFromJS<T>(argv.This());
            if( ! self ) throw MissingThisExceptionT<T>();
            return (ReturnType)CallNative(*self, func, argv);
        }
        static v8::Handle<v8::Value> Call( FunctionType func, v8::Arguments const & argv )
        {
            try
            {
                return CastToJS( CallNative(func, argv) );
            }
            HANDLE_PROPAGATE_EXCEPTION;
        }
        ASSERT_UNLOCKV8_IS_FALSE;
    };

    template <typename T, typename RV, bool UnlockV8, int _Arity>
    struct ArgsToMethodForwarder<T,_Arity, RV (T::*)(v8::Arguments const &), UnlockV8> :
            ArgsToMethodForwarder<T, _Arity, RV (v8::Arguments const &), UnlockV8>
    {};

    template <typename T, int Arity_, typename Sig,
        bool UnlockV8 = cv::SignatureIsUnlockable< cv::MethodSignature<T, Sig> >::Value
    >
    struct ArgsToMethodForwarderVoid;

    template <typename T, typename Sig, bool UnlockV8>
    struct ArgsToMethodForwarderVoid<T,0,Sig, UnlockV8>
        : MethodSignature<T,Sig>
    {
    public:
        typedef MethodSignature<T,Sig> SignatureType;
        typedef typename SignatureType::FunctionType FunctionType;
        typedef typename TypeInfo<T>::Type Type;
        typedef typename SignatureType::ReturnType ReturnType;
        static ReturnType CallNative( Type & self, FunctionType func, v8::Arguments const & argv )
        {
            V8Unlocker<UnlockV8> const unlocker();
            return (ReturnType)(self.*func)();
        }
        static v8::Handle<v8::Value> Call( Type & self, FunctionType func, v8::Arguments const & argv )
        {
            try
            {
                CallNative( self, func, argv );
                return v8::Undefined();
            }
            HANDLE_PROPAGATE_EXCEPTION;
        }
        static ReturnType CallNative( FunctionType func, v8::Arguments const & argv )
        {
            T * self = CastFromJS<T>(argv.This());
            if( ! self ) throw MissingThisExceptionT<T>();
            return (ReturnType)CallNative(*self, func, argv);
        }
        static v8::Handle<v8::Value> Call( FunctionType func, v8::Arguments const & argv )
        {
            try
            {
                CallNative(func, argv);
                return v8::Undefined();
            }
            HANDLE_PROPAGATE_EXCEPTION;
        }
    };

    template <typename T, int Arity, typename RV, bool UnlockV8>
    struct ArgsToMethodForwarderVoid<T,Arity, RV (v8::Arguments const &), UnlockV8>
        : MethodSignature<T,RV (v8::Arguments const &)>
    {
    public:
        typedef MethodSignature<T,RV (v8::Arguments const &)> SignatureType;
        typedef typename SignatureType::FunctionType FunctionType;
        typedef typename TypeInfo<T>::Type Type;
        typedef typename SignatureType::ReturnType ReturnType;
        static ReturnType CallNative( Type & self, FunctionType func, v8::Arguments const & argv )
        {
            return (ReturnType)(self.*func)(argv);
        }
        static v8::Handle<v8::Value> Call( Type & self, FunctionType func, v8::Arguments const & argv )
        {
            try
            {
                CallNative( self, func, argv );
                return v8::Undefined();
            }
            HANDLE_PROPAGATE_EXCEPTION;

        }
        static ReturnType CallNative( FunctionType func, v8::Arguments const & argv )
        {
            T * self = CastFromJS<T>(argv.This());
            if( ! self ) throw MissingThisExceptionT<T>();
            return (ReturnType)CallNative(*self, func, argv);
        }
        static v8::Handle<v8::Value> Call( FunctionType func, v8::Arguments const & argv )
        {
            try
            {
                CallNative(func, argv);
                return v8::Undefined();
            }
            HANDLE_PROPAGATE_EXCEPTION;
        }
        ASSERT_UNLOCKV8_IS_FALSE;
    };

    template <typename T, int Arity, typename RV, bool UnlockV8>
    struct ArgsToMethodForwarderVoid<T,Arity, RV (T::*)(v8::Arguments const &), UnlockV8>
        : ArgsToMethodForwarderVoid<T,Arity, RV (v8::Arguments const &), UnlockV8>
    {};
    
    /**
        Internal impl for v8::convert::ArgsToConstMethodForwarder.
    */
    template <typename T, int Arity_, typename Sig,
            bool UnlockV8 = cv::SignatureIsUnlockable< cv::ConstMethodSignature<T, Sig> >::Value
    >
    struct ArgsToConstMethodForwarder;

    template <typename T, typename Sig, bool UnlockV8>
    struct ArgsToConstMethodForwarder<T,0,Sig, UnlockV8> : ConstMethodSignature<T,Sig>
    {
    public:
        typedef ConstMethodSignature<T,Sig> SignatureType;
        typedef typename SignatureType::FunctionType FunctionType;
        typedef typename SignatureType::ReturnType ReturnType;
        static ReturnType CallNative( T const & self, FunctionType func, v8::Arguments const & argv )
        {
            V8Unlocker<UnlockV8> const unlocker();
            return (self.*func)();
        }
        
        static v8::Handle<v8::Value> Call( T const & self, FunctionType func, v8::Arguments const & argv )
        {
            try
            {
                return cv::CastToJS( CallNative( self, func, argv ) );
            }
            HANDLE_PROPAGATE_EXCEPTION;
        }
        static ReturnType CallNative( FunctionType func, v8::Arguments const & argv )
        {
            T const * self = CastFromJS<T>(argv.This());
            if( ! self ) throw MissingThisExceptionT<T>();
            return (ReturnType)CallNative(*self, func, argv);
        }
        static v8::Handle<v8::Value> Call( FunctionType func, v8::Arguments const & argv )
        {
            try
            {
                return CastToJS( CallNative(func, argv) );
            }
            HANDLE_PROPAGATE_EXCEPTION;
        }
    };

    template <typename T, int Arity, typename RV, bool UnlockV8>
    struct ArgsToConstMethodForwarder<T, Arity, RV (v8::Arguments const &), UnlockV8>
        : ConstMethodSignature<T, RV (v8::Arguments const &)>
    {
    public:
        typedef ConstMethodSignature<T, RV (v8::Arguments const &)> SignatureType;
        typedef char AssertArity[ sl::Arity<SignatureType>::Value == -1 ? 1 : -1];
        typedef typename SignatureType::FunctionType FunctionType;
        typedef typename SignatureType::ReturnType ReturnType;
        static ReturnType CallNative( T const & self, FunctionType func, v8::Arguments const & argv )
        {
            return (ReturnType)(self.*func)(argv);
        }
        static v8::Handle<v8::Value> Call( T const & self, FunctionType func, v8::Arguments const & argv )
        {
            try
            {
                return cv::CastToJS( CallNative( self, func, argv ) );
            }
            HANDLE_PROPAGATE_EXCEPTION;
        }
        static ReturnType CallNative( FunctionType func, v8::Arguments const & argv )
        {
            T const * self = CastFromJS<T>(argv.This());
            if( ! self ) throw MissingThisExceptionT<T>();
            return (ReturnType)CallNative(*self, func, argv);
        }
        static v8::Handle<v8::Value> Call( FunctionType func, v8::Arguments const & argv )
        {
            try
            {
                return CastToJS( CallNative(func, argv) );
            }
            HANDLE_PROPAGATE_EXCEPTION;
        }
        ASSERT_UNLOCKV8_IS_FALSE;
    };

    template <typename T, int Arity, typename RV, bool UnlockV8>
    struct ArgsToConstMethodForwarder<T, Arity, RV (T::*)(v8::Arguments const &) const, UnlockV8>
        : ArgsToConstMethodForwarder<T, Arity, RV (v8::Arguments const &), UnlockV8>
    {};

    template <typename T, int Arity_, typename Sig,
            bool UnlockV8 = cv::SignatureIsUnlockable< cv::ConstMethodSignature<T, Sig> >::Value
    >
    struct ArgsToConstMethodForwarderVoid;

    template <typename T, typename Sig, bool UnlockV8>
    struct ArgsToConstMethodForwarderVoid<T,0,Sig, UnlockV8> : ConstMethodSignature<T,Sig>
    {
    public:
        typedef ConstMethodSignature<T,Sig> SignatureType;
        typedef typename SignatureType::FunctionType FunctionType;
        typedef typename SignatureType::ReturnType ReturnType;
        typedef typename TypeInfo<T>::Type Type;
        static ReturnType CallNative( Type const & self, FunctionType func, v8::Arguments const & argv )
        {
            V8Unlocker<UnlockV8> const unlocker();
            return (ReturnType)(self.*func)();
        }
        
        static v8::Handle<v8::Value> Call( Type const & self, FunctionType func, v8::Arguments const & argv )
        {
            try
            {
                CallNative( self, func, argv );
                return v8::Undefined();
            }
            HANDLE_PROPAGATE_EXCEPTION;
        }
        static ReturnType CallNative( FunctionType func, v8::Arguments const & argv )
        {
            T const * self = CastFromJS<T>(argv.This());
            if( ! self ) throw MissingThisExceptionT<T>();
            return (ReturnType)CallNative(*self, func, argv);
        }
        static v8::Handle<v8::Value> Call( FunctionType func, v8::Arguments const & argv )
        {
            try
            {
                CallNative(func, argv);
                return v8::Undefined();
            }
            HANDLE_PROPAGATE_EXCEPTION;
        }
        ASSERT_UNLOCK_SANITY_CHECK;
    };
    
    template <typename T, int Arity, typename RV, bool UnlockV8>
    struct ArgsToConstMethodForwarderVoid<T, Arity, RV (v8::Arguments const &), UnlockV8>
        : ConstMethodSignature<T, RV (v8::Arguments const &)>
    {
    public:
        typedef ConstMethodSignature<T, RV (v8::Arguments const &)> SignatureType;
        typedef char AssertArity[ sl::Arity<SignatureType>::Value == -1 ? 1 : -1];
        typedef typename SignatureType::FunctionType FunctionType;
        typedef typename SignatureType::ReturnType ReturnType;
        typedef typename TypeInfo<T>::Type Type;
        static ReturnType CallNative( Type const & self, FunctionType func, v8::Arguments const & argv )
        {
            V8Unlocker<UnlockV8> const unlocker();
            return (ReturnType)(self.*func)();
        }
        static v8::Handle<v8::Value> Call( Type const & self, FunctionType func, v8::Arguments const & argv )
        {
            try
            {
                CallNative( self, func, argv );
            }
            HANDLE_PROPAGATE_EXCEPTION;
        }
        static ReturnType CallNative( FunctionType func, v8::Arguments const & argv )
        {
            T const * self = CastFromJS<T>(argv.This());
            if( ! self ) throw MissingThisExceptionT<T>();
            return CallNative(*self, func, argv);
        }
        static v8::Handle<v8::Value> Call( FunctionType func, v8::Arguments const & argv )
        {
            try
            {
                return CastToJS( CallNative( func, argv ) );
            }
            HANDLE_PROPAGATE_EXCEPTION;
        }
        ASSERT_UNLOCKV8_IS_FALSE;
    };

    template <typename T, int Arity, typename RV, bool UnlockV8>
    struct ArgsToConstMethodForwarderVoid<T, Arity, RV (T::*)(v8::Arguments const &) const, UnlockV8>
    : ArgsToConstMethodForwarderVoid<T, Arity, RV (v8::Arguments const &), UnlockV8>
    {};

}
#endif // DOXYGEN

/**
    A helper type for passing v8::Arguments lists to native non-member
    functions.

    Sig must be a function-signature-like argument. e.g. <double (int,double)>,
    and the members of this class expect functions matching that signature.

    If UnlockV8 is true then v8::Unlocker will be used to unlock v8 
    for the duration of the call to Func(). HOWEVER... (the rest of 
    these docs are about the caveats)...

    A UnlockV8 value of SignatureIsUnlockable<Sig>::Value uses a
    reasonably sound heuristic but it cannot predict certain 
    app-dependent conditions which render its guess semantically 
    invalid. See SignatureIsUnlockable for more information.

    It is illegal for UnlockV8 to be true if ANY of the following 
    applies:

    - The callback itself will "use" v8 but does not explicitly use 
    v8::Locker. If it uses v8::Locker then it may safely enable 
    unlocking support. We cannot determine via templates  whether 
    or not a function "uses" v8 except by guessing based on the 
    return and arguments types.

    - Any of the return or argument types for the function are v8 
    types, e.g. v8::Handle<Anything> or v8::Arguments. 
    SignatureIsUnlockable<Sig>::Value will evaluate to false 
    if any of the "known bad" types is contained in the function's 
    signature. If this function is given a true value but
    SignatureIsUnlockable<Sig>::Value is false then
    a compile-time assertion will be triggered.

    - Certain callback signatures cannot have unlocking support
    enabled because if we unlock then we cannot legally access the data
    we need to convert. These will cause a compile-time assertion
    if UnlockV8 is true. All such bits are incidentally covered by
    SignatureIsUnlockable's check, so this assertion can
    only happen if the client explicitly sets UnlockV8 to true for
    those few cases.

    - There might be other, as yet unknown/undocumented, corner cases 
    where unlocking v8 is semantically illegal at this level of the 
    API.

    Violating any of these leads to undefined behaviour. The library 
    tries to fail at compile time for invalid combinations when it 
    can, but (as described aboved) it can be fooled into thinking that
    unlocking is safe.

*/
template <typename Sig,
        bool UnlockV8 = SignatureIsUnlockable< FunctionSignature<Sig> >::Value
>
struct ArgsToFunctionForwarder : Callable
{
private:
    typedef typename tmp::IfElse< tmp::SameType<void ,typename FunctionSignature<Sig>::ReturnType>::Value,
                                Detail::ArgsToFunctionForwarderVoid< sl::Arity< Signature<Sig> >::Value, Sig, UnlockV8 >,
                                Detail::ArgsToFunctionForwarder< sl::Arity< Signature<Sig> >::Value, Sig, UnlockV8 >
        >::Type
    ProxyType;
public:
    typedef typename ProxyType::SignatureType SignatureType;
    typedef typename ProxyType::ReturnType ReturnType;
    typedef typename ProxyType::FunctionType FunctionType;
    /**
       Passes the given arguments to func(), converting them to the appropriate
       types. If argv.Length() is less than sl::Arity< SignatureType >::Value then
       a JS exception is thrown, with one exception: if the function has "-1 arity"
       (i.e. it is InvocationCallback-like) then argv is passed on to it regardless
       of the value of argv.Length().
       
       The native return value of the call is returned to the caller.
    */
    static ReturnType CallNative( FunctionType func, v8::Arguments const & argv )
    {
        return ProxyType::CallNative( func, argv );
    }
    /**
        Equivalent to CastToJS( CallNative(func,argv) ) unless ReturnType
        is void, in which case CastToJS() is not invoked and v8::Undefined()
        will be returned.
    */
    static v8::Handle<v8::Value> Call( FunctionType func, v8::Arguments const & argv )
    {
        return ProxyType::Call( func, argv );
    }
};

#if !defined(DOXYGEN)
namespace Detail {

    template <typename Sig,
              typename FunctionSignature<Sig>::FunctionType Func,
              bool UnlockV8 = SignatureIsUnlockable< FunctionSignature<Sig> >::Value >
    struct FunctionToInCa : FunctionPtr<Sig,Func>, Callable
    {
        
        typedef FunctionSignature<Sig> SignatureType;
        typedef ArgsToFunctionForwarder< sl::Arity<SignatureType>::Value, Sig, UnlockV8 > Proxy;
        typedef typename SignatureType::ReturnType ReturnType;
        static ReturnType CallNative( v8::Arguments const & argv )
        {
            return (ReturnType)Proxy::CallNative( Func, argv );
        }
        static v8::Handle<v8::Value> Call( v8::Arguments const & argv )
        {
            return Proxy::Call( Func, argv );
        }
        ASSERT_UNLOCK_SANITY_CHECK;
    };

    template <typename Sig,
              typename FunctionSignature<Sig>::FunctionType Func,
              bool UnlockV8 = SignatureIsUnlockable< FunctionSignature<Sig> >::Value >
    struct FunctionToInCaVoid : FunctionPtr<Sig,Func>, Callable
    {
        typedef FunctionSignature<Sig> SignatureType;
        typedef ArgsToFunctionForwarderVoid< sl::Arity<SignatureType>::Value, Sig, UnlockV8 > Proxy;
        typedef typename SignatureType::ReturnType ReturnType;
        static ReturnType CallNative( v8::Arguments const & argv )
        {
            return (ReturnType)Proxy::CallNative( Func, argv );
        }
        static v8::Handle<v8::Value> Call( v8::Arguments const & argv )
        {
            return Proxy::Call( Func, argv );
        }
        ASSERT_UNLOCK_SANITY_CHECK;
    };


    template <typename T,
              typename Sig,
              typename MethodSignature<T,Sig>::FunctionType Func,
              bool UnlockV8 = SignatureIsUnlockable< MethodSignature<T,Sig> >::Value
              >
    struct MethodToInCa : MethodPtr<T,Sig, Func>, Callable
    {
        typedef MethodPtr<T, Sig, Func> SignatureType;
        typedef ArgsToMethodForwarder< T, sl::Arity<SignatureType>::Value, Sig, UnlockV8 > Proxy;
        typedef typename SignatureType::ReturnType ReturnType;
        static ReturnType CallNative( T & self, v8::Arguments const & argv )
        {
            return Proxy::CallNative( self, Func, argv );
        }
        static ReturnType CallNative( v8::Arguments const & argv )
        {
            return Proxy::Call( Func, argv );
        }
        static v8::Handle<v8::Value> Call( v8::Arguments const & argv )
        {
            return Proxy::Call( Func, argv );
        }
        static v8::Handle<v8::Value> Call( T & self, v8::Arguments const & argv )
        {
            return Proxy::Call( self, Func, argv );
        }
        ASSERT_UNLOCK_SANITY_CHECK;
    };

    template <typename T,
              typename Sig,
              typename MethodSignature<T,Sig>::FunctionType Func,
              bool UnlockV8 = SignatureIsUnlockable< MethodSignature<T,Sig> >::Value
              >
    struct MethodToInCaVoid : MethodPtr<T,Sig,Func>, Callable
    {
        typedef MethodPtr<T, Sig, Func> SignatureType;
        typedef ArgsToMethodForwarderVoid< T, sl::Arity<SignatureType>::Value, Sig, UnlockV8 > Proxy;
        typedef typename SignatureType::ReturnType ReturnType;
        static ReturnType CallNative( T & self, v8::Arguments const & argv )
        {
            return Proxy::CallNative( self, Func, argv );
        }
        static ReturnType CallNative( v8::Arguments const & argv )
        {
            return Proxy::Call( Func, argv );
        }
        static v8::Handle<v8::Value> Call( v8::Arguments const & argv )
        {
            return Proxy::Call( Func, argv );
        }
        static v8::Handle<v8::Value> Call( T & self, v8::Arguments const & argv )
        {
            return Proxy::Call( self, Func, argv );
        }
        ASSERT_UNLOCK_SANITY_CHECK;
    };

    template <typename T,
              typename Sig,
              typename ConstMethodSignature<T,Sig>::FunctionType Func,
              bool UnlockV8 = SignatureIsUnlockable< ConstMethodSignature<T,Sig> >::Value
              >
    struct ConstMethodToInCa : ConstMethodPtr<T,Sig, Func>, Callable
    {
        typedef ConstMethodPtr<T, Sig, Func> SignatureType;
        typedef ArgsToConstMethodForwarder< T, sl::Arity<SignatureType>::Value, Sig, UnlockV8 > Proxy;
        typedef typename SignatureType::ReturnType ReturnType;
        static ReturnType CallNative( T const & self, v8::Arguments const & argv )
        {
            return Proxy::CallNative( self, Func, argv );
        }
        static ReturnType CallNative( v8::Arguments const & argv )
        {
            return Proxy::Call( Func, argv );
        }
        static v8::Handle<v8::Value> Call( v8::Arguments const & argv )
        {
            return Proxy::Call( Func, argv );
        }
        static v8::Handle<v8::Value> Call( T const & self, v8::Arguments const & argv )
        {
            return Proxy::Call( self, Func, argv );
        }
    };

    template <typename T,
              typename Sig,
              typename ConstMethodSignature<T,Sig>::FunctionType Func,
              bool UnlockV8 = SignatureIsUnlockable< ConstMethodSignature<T,Sig> >::Value
              >
    struct ConstMethodToInCaVoid : ConstMethodPtr<T,Sig,Func>, Callable
    {
        typedef ConstMethodPtr<T, Sig, Func> SignatureType;
        typedef ArgsToConstMethodForwarderVoid< T, sl::Arity<SignatureType>::Value, Sig, UnlockV8 > Proxy;
        typedef typename SignatureType::ReturnType ReturnType;
        static ReturnType CallNative( T const & self, v8::Arguments const & argv )
        {
            return Proxy::CallNative( self, Func, argv );
        }
        static ReturnType CallNative( v8::Arguments const & argv )
        {
            return Proxy::Call( Func, argv );
        }
        static v8::Handle<v8::Value> Call( v8::Arguments const & argv )
        {
            return Proxy::Call( Func, argv );
        }
        static v8::Handle<v8::Value> Call( T const & self, v8::Arguments const & argv )
        {
            return Proxy::Call( self, Func, argv );
        }
        ASSERT_UNLOCK_SANITY_CHECK;
    };

} // Detail namespace
#endif // DOXYGEN
#undef ASSERT_UNLOCK_SANITY_CHECK
#undef ASSERT_UNLOCKV8_IS_FALSE


/**
   A template for converting free (non-member) function pointers
   to v8::InvocationCallback.

   Sig must be a function signature. Func must be a pointer to a function
   with that signature.

   If UnlockV8 is true then v8::Unlocker will be used to unlock v8 
   for the duration of the call to Func(). HOWEVER... see 
   ArgsToFunctionForwarder for the details/caveats regarding that 
   parameter.
   
       Example:
    @code
    v8::InvocationCallback cb = 
       FunctionToInCa< int (int), ::putchar>::Call;
    @endcode
*/
template <typename Sig,
          typename FunctionSignature<Sig>::FunctionType Func,
          bool UnlockV8 = SignatureIsUnlockable< Signature<Sig> >::Value
          >
struct FunctionToInCa
    : tmp::IfElse< tmp::SameType<void ,typename FunctionSignature<Sig>::ReturnType>::Value,
                 Detail::FunctionToInCaVoid< Sig, Func, UnlockV8>,
                 Detail::FunctionToInCa< Sig, Func, UnlockV8>
        >::Type
{};

/**
    A variant of FunctionToInCa which the property of not invoking
    the conversion of the function's return type from native to JS
    form. This is useful when such a conversion is not legal
    because CastToJS() won't work on it or, more generally,
    when you want the JS interface to always get the undefined
    return value.
    
    Call() always returns v8::Undefined(). CallNative(), however,
    returns the real return type specified by Sig (which may be void).

    Example:

    @code
    v8::InvocationCallback cb = 
       FunctionToInCaVoid< int (int), ::putchar>::Call;
    @endcode
*/
template <typename Sig,
          typename FunctionSignature<Sig>::FunctionType Func,
          bool UnlockV8 = SignatureIsUnlockable< Signature<Sig> >::Value
          >
struct FunctionToInCaVoid : Detail::FunctionToInCaVoid< Sig, Func, UnlockV8>
{};


/**
   A template for converting non-const member function pointers to
   v8::InvocationCallback. For const member functions use
   ConstMethodToInCa instead.

   To convert JS objects to native 'this' pointers this API uses
   CastFromJS<T>(arguments.This()), where arguments is the
   v8::Arguments instance passed to the generated InvocationCallback
   implementation. If that conversion fails then the generated
   functions will throw a JS-side exception when called.

   T must be some client-specified type which is presumably bound (or
   at least bindable) to JS-side Objects. Sig must be a member
   function signature for T. Func must be a pointer to a function with
   that signature.
   
   See ArgsToFunctionForwarder for details about the UnlockV8 parameter.
   
    Example:

    @code
    v8::InvocationCallback cb = 
       MethodToInCa< T, int (int), &T::myFunc>::Call;
    @endcode
*/
template <typename T, typename Sig,
          typename MethodSignature<T,Sig>::FunctionType Func,
          bool UnlockV8 = SignatureIsUnlockable< MethodSignature<T,Sig> >::Value
          >
struct MethodToInCa
    : tmp::IfElse< tmp::SameType<void ,typename MethodSignature<T,Sig>::ReturnType>::Value,
                 Detail::MethodToInCaVoid<T, Sig, Func, UnlockV8>,
                 Detail::MethodToInCa<T, Sig, Func, UnlockV8>
        >::Type
{
};

/**
    See FunctionToInCaVoid - this is identical exception that it
    works on member functions of T.
    
    Example:

    @code
    v8::InvocationCallback cb = 
       MethodToInCaVoid< T, int (int), &T::myFunc>::Call;
    @endcode

*/
template <typename T, typename Sig,
          typename MethodSignature<T,Sig>::FunctionType Func,
          bool UnlockV8 = SignatureIsUnlockable< MethodSignature<T,Sig> >::Value
          >
struct MethodToInCaVoid
    : Detail::MethodToInCaVoid<T, Sig, Func, UnlockV8>
{
};

/**
   Functionally identical to MethodToInCa, but for const member functions.
   
   See ArgsToFunctionForwarder for details about the UnlockV8 parameter.
   
   Note that the Sig signature must be suffixed with a const qualifier!
   
    Example:

    @code
    v8::InvocationCallback cb = 
       ConstMethodToInCa< T, int (int) const, &T::myFunc>::Call;
    @endcode

*/
template <typename T, typename Sig, typename ConstMethodSignature<T,Sig>::FunctionType Func,
          bool UnlockV8 = SignatureIsUnlockable< ConstMethodSignature<T,Sig> >::Value
          >
struct ConstMethodToInCa
    : tmp::IfElse< tmp::SameType<void ,typename ConstMethodSignature<T, Sig>::ReturnType>::Value,
                 Detail::ConstMethodToInCaVoid<T, Sig, Func, UnlockV8>,
                 Detail::ConstMethodToInCa<T, Sig, Func, UnlockV8>
        >::Type
{};

/**
    See FunctionToInCaVoid - this is identical exception that it
    works on const member functions of T.
   
    Note that the Sig signature must be suffixed with a const qualifier!
    
    Example:

    @code
    v8::InvocationCallback cb = 
       ConstMethodToInCaVoid< T, int (int) const, &T::myFunc>::Call;
    @endcode

*/
template <typename T, typename Sig, typename ConstMethodSignature<T,Sig>::FunctionType Func,
          bool UnlockV8 = SignatureIsUnlockable< ConstMethodSignature<T,Sig> >::Value
          >
struct ConstMethodToInCaVoid : Detail::ConstMethodToInCaVoid<T, Sig, Func, UnlockV8>
{};


/** @deprecated Use FunctionToInCa::Call() instead.

   A v8::InvocationCallback implementation which forwards the arguments from argv
   to the template-specified function. If Func returns void then the return
   value will be v8::Undefined().

   Example usage:

   @code
   v8::InvocationCallback cb = FunctionToInvocationCallback<int (char const *), ::puts>;
   @endcode
*/
template <typename Sig,
          typename FunctionSignature<Sig>::FunctionType Func>
v8::Handle<v8::Value> FunctionToInvocationCallback( v8::Arguments const & argv )
{
    return FunctionToInCa<Sig,Func>::Call(argv);
}

/** @deprecated Use MethodToInCa::Call() instead.

   A v8::InvocationCallback implementation which forwards the arguments from argv
   to the template-specified member of "a" T object. This function uses
   CastFromJS<T>( argv.This() ) to fetch the native 'this' object, and will
   fail (with a JS-side exception) if that conversion fails.

   If Func returns void then the return value will be v8::Undefined().

   Example usage:

   @code
   v8::InvocationCallback cb = MethodToInvocationCallback<MyType, int (double), &MyType::doSomething >;
   @endcode

*/
template <typename T,typename Sig,
          typename MethodSignature<T,Sig>::FunctionType Func>
v8::Handle<v8::Value> MethodToInvocationCallback( v8::Arguments const & argv )
{
    return MethodToInCa<T,Sig,Func>::Call(argv);
}


/** @deprecated Use ConstMethodToInCa::Call() instead.

   Identical to MethodToInvocationCallback(), but is for const member functions.

   @code
   v8::InvocationCallback cb = ConstMethodToInvocationCallback<MyType, int (double), &MyType::doSomethingConst >;
   @endcode

*/
template <typename T,typename Sig,
          typename ConstMethodSignature<T,Sig>::FunctionType Func>
v8::Handle<v8::Value> ConstMethodToInvocationCallback( v8::Arguments const & argv )
{
    return ConstMethodToInCa<T,Sig,Func>::Call(argv);
}

/**
   Identicial to ArgsToFunctionForwarder, but works on non-const
   member methods of type T.

   Sig must be a function-signature-like argument. e.g. <double
   (int,double)>, and the members of this class expect T member
   functions matching that signature.
*/
template <typename T, typename Sig, bool UnlockV8 = SignatureIsUnlockable< MethodSignature<T,Sig> >::Value>
struct ArgsToMethodForwarder
{
private:
    typedef typename
    tmp::IfElse< tmp::SameType<void ,typename MethodSignature<T,Sig>::ReturnType>::Value,
                 Detail::ArgsToMethodForwarderVoid< T, sl::Arity< Signature<Sig> >::Value, Sig, UnlockV8 >,
                 Detail::ArgsToMethodForwarder< T, sl::Arity< Signature<Sig> >::Value, Sig, UnlockV8 >
    >::Type
    Proxy;
public:
    typedef typename Proxy::SignatureType SignatureType;
    typedef typename Proxy::FunctionType FunctionType;
    typedef typename Proxy::ReturnType ReturnType;
    /**
       Passes the given arguments to (self.*func)(), converting them 
       to the appropriate types. If argv.Length() is less than 
       sl::Arity<SignatureType>::Value then a JS exception is 
       thrown, with one exception: if the function has "-1 arity" 
       (i.e. it is InvocationCallback-like) then argv is passed on 
       to it regardless of the value of argv.Length().
    */
    static v8::Handle<v8::Value> Call( T & self, FunctionType func, v8::Arguments const & argv )
    {
        return Proxy::Call( self, func, argv );
    }

    /**
       Like the 3-arg overload, but tries to extract the (T*) object using
       CastFromJS<T>(argv.This()).
    */
    static v8::Handle<v8::Value> Call( FunctionType func, v8::Arguments const & argv )
    {
        return Proxy::Call( func, argv );
    }
};


/**
   Identical to ArgsToMethodForwarder, but works on const member methods.
*/
template <typename T, typename Sig,
        bool UnlockV8 = SignatureIsUnlockable< ConstMethodSignature<T,Sig> >::Value
        >
struct ArgsToConstMethodForwarder
{
private:
    typedef typename
    tmp::IfElse< tmp::SameType<void ,typename ConstMethodSignature<T,Sig>::ReturnType>::Value,
                 Detail::ArgsToConstMethodForwarderVoid< T, sl::Arity< Signature<Sig> >::Value, Sig, UnlockV8 >,
                 Detail::ArgsToConstMethodForwarder< T, sl::Arity< Signature<Sig> >::Value, Sig, UnlockV8 >
    >::Type
    Proxy;
public:
    typedef typename Proxy::SignatureType SignatureType;
    typedef typename Proxy::FunctionType FunctionType;

    /**
       Passes the given arguments to (self.*func)(), converting them 
       to the appropriate types. If argv.Length() is less than 
       sl::Arity< Signature<Sig> >::Value then a JS exception is thrown, with one 
       exception: if the function has "-1 arity" (i.e. it is 
       InvocationCallback-like) then argv is passed on to it 
       regardless of the value of argv.Length().
    */
    static v8::Handle<v8::Value> Call( T const & self, FunctionType func, v8::Arguments const & argv )
    {
        return Proxy::Call( self, func, argv );
    }

    /**
       Like the 3-arg overload, but tries to extract the (T const *)
       object using CastFromJS<T>(argv.This()).
    */
    static v8::Handle<v8::Value> Call( FunctionType func, v8::Arguments const & argv )
    {
        return Proxy::Call( func, argv );
    }
};

/**
   Tries to forward the given arguments to the given native 
   function. Will fail if argv.Lengt() is not at least 
   sl::Arity<Signature<Sig>>::Value, throwing a JS exception in that 
   case _unless_ the function is InvocationCallback-like, in which 
   case argv is passed directly to it regardless of the value of 
   argv.Length().
*/
template <typename Sig>
inline typename FunctionSignature<Sig>::ReturnType
forwardFunction( Sig func, Arguments const & argv )
{
    typedef FunctionSignature<Sig> MSIG;
    typedef typename MSIG::ReturnType RV;
    enum { Arity = sl::Arity< Signature<Sig> >::Value };
    typedef typename
        tmp::IfElse< tmp::SameType<void ,RV>::Value,
        Detail::ArgsToFunctionForwarderVoid< Arity, Sig >,
        Detail::ArgsToFunctionForwarder< Arity, Sig >
        >::Type Proxy;
    return (RV)Proxy::CallNative( func, argv );
}

/**
   Works like forwardFunction(), but forwards to the
   given non-const member function and treats the given object
   as the 'this' pointer.
*/
template <typename T, typename Sig>
inline typename MethodSignature<T,Sig>::ReturnType
forwardMethod( T & self,
               Sig func,
               /* if i do: typename MethodSignature<T,Sig>::FunctionType
                  then this template is never selected. */
               Arguments const & argv )
{
    typedef MethodSignature<T,Sig> MSIG;
    typedef typename MSIG::ReturnType RV;
    enum { Arity = sl::Arity< MSIG >::Value };
    typedef typename
        tmp::IfElse< tmp::SameType<void ,RV>::Value,
                 Detail::ArgsToMethodForwarderVoid< T, Arity, Sig >,
                 Detail::ArgsToMethodForwarder< T, Arity, Sig >
    >::Type Proxy;
    return (RV)Proxy::CallNative( self, func, argv );
}

/**
   Like the 3-arg forwardMethod() overload, but
   extracts the native T 'this' object from argv.This().

   Note that this function requires that the caller specify
   the T template parameter - it cannot deduce it.
*/
template <typename T, typename Sig>
typename MethodSignature<T,Sig>::ReturnType
forwardMethod(Sig func, v8::Arguments const & argv )
{
    typedef MethodSignature<T,Sig> MSIG;
    typedef typename MSIG::ReturnType RV;
    enum { Arity = sl::Arity< MSIG >::Value };
    typedef typename
        tmp::IfElse< tmp::SameType<void ,RV>::Value,
                 Detail::ArgsToMethodForwarderVoid< T, Arity, Sig >,
                 Detail::ArgsToMethodForwarder< T, Arity, Sig >
    >::Type Proxy;
    return (RV)Proxy::CallNative( func, argv );
}

    
/**
   Works like forwardMethod(), but forwards to the given const member
   function and treats the given object as the 'this' pointer.

*/
template <typename T, typename Sig>
inline typename ConstMethodSignature<T,Sig>::ReturnType
forwardConstMethod( T const & self,
                    //typename ConstMethodSignature<T,Sig>::FunctionType func,
                    Sig func,
                    v8::Arguments const & argv )
{
    typedef ConstMethodSignature<T,Sig> MSIG;
    typedef typename MSIG::ReturnType RV;
    enum { Arity = sl::Arity< MSIG >::Value };
    typedef typename
        tmp::IfElse< tmp::SameType<void ,RV>::Value,
                 Detail::ArgsToConstMethodForwarderVoid< T, Arity, Sig >,
                 Detail::ArgsToConstMethodForwarder< T, Arity, Sig >
    >::Type Proxy;
    return (RV)Proxy::CallNative( self, func, argv );
}

/**
   Like the 3-arg forwardConstMethod() overload, but
   extracts the native T 'this' object from argv.This().

   Note that this function requires that the caller specify
   the T template parameter - it cannot deduce it.
*/
template <typename T, typename Sig>
typename ConstMethodSignature<T,Sig>::ReturnType
forwardConstMethod(Sig func, v8::Arguments const & argv )
{
    typedef ConstMethodSignature<T,Sig> MSIG;
    typedef typename MSIG::ReturnType RV;
    enum { Arity = sl::Arity< MSIG >::Value };
    typedef typename
        tmp::IfElse< tmp::SameType<void ,RV>::Value,
                 Detail::ArgsToConstMethodForwarderVoid< T, Arity, Sig >,
                 Detail::ArgsToConstMethodForwarder< T, Arity, Sig >
    >::Type Proxy;
    return (RV)Proxy::CallNative( func, argv );
}

/**
   A structified/functorified form of v8::InvocationCallback.  It is
   sometimes convenient to be able to use a typedef to create an alias
   for a given InvocationCallback. Since we cannot typedef function
   templates this way, this class can fill that gap.
*/
template <v8::InvocationCallback ICB>
struct InCa : FunctionToInCa< v8::Handle<v8::Value> (v8::Arguments const &), ICB>
{
};


#if 1
/**
   "Converts" an InCa<ICB> instance to JS by treating it as an
   InvocationCallback function. This is primarily useful in
   conjunction with ClassCreator::Set() to add function bindings.
*/
template <v8::InvocationCallback ICB>
struct NativeToJS< InCa<ICB> >
{
    /**
       Returns a JS handle to InCa<ICB>::Call().
    */
    v8::Handle<v8::Value> operator()( InCa<ICB> const & )
    {
        return v8::FunctionTemplate::New(InCa<ICB>::Call)->GetFunction();
    }
};
#endif

#if !defined(DOXYGEN)
namespace Detail {
    /** Internal code duplication reducer. */
    template <int ExpectingArity>
    v8::Handle<v8::Value> TossArgCountError( v8::Arguments const & args )
    {
        using v8::convert::StringBuffer;
        return v8::ThrowException(v8::Exception::Error(StringBuffer()
                                                       <<"Incorrect argument count ("<<args.Length()
                                                       <<") for function - expecting "
                                                       <<ExpectingArity<<" arguments."));
    }
}
#endif

/**
   A utility template to assist in the creation of InvocationCallbacks
   overloadable based on the number of arguments passed to them at
   runtime.

   See Call() for more details.
   
   Using this class almost always requires more code than
   doing the equivalent with InCaOverload. The exception to that
   guideline is when we have only two overloads.
*/
template < int Arity,
           v8::InvocationCallback ICB,
           v8::InvocationCallback Fallback = Detail::TossArgCountError<Arity>
>
struct InCaOverloader : Callable
{
    /**
       When called, if (Artity==-1) or if (Arity==args.Length()) then
       ICB(args) is returned, else Fallback(args) is returned.

       The default Fallback implementation triggers a JS-side
       exception when called, its error string indicating the argument
       count mismatch.

       Implements the InvocationCallback interface.
    */
    static v8::Handle<v8::Value> Call( v8::Arguments const & args )
    {
        return ( (-1==Arity) || (Arity == args.Length()) )
            ? ICB(args)
            : Fallback(args);
    }
};


/**
   InvocationCallback wrapper which calls another InvocationCallback
   and translates any native ExceptionT exceptions thrown by that
   function into JS exceptions.

   ExceptionT must be an exception type which is thrown by const 
   reference (e.g. STL-style) as opposed to by pointer (MFC-style).

   SigGetMsg must be a function-signature-style argument describing
   a method within ExceptionT which can be used to fetch the message
   reported by the exception. It must meet these requirements:

   a) Be const
   b) Take no arguments
   c) Return a type convertible to JS via CastToJS()

   Getter must be a pointer to a function matching that signature.

   ICB must be a v8::InvocationCallback. When this function is called
   by v8, it will pass on the call to ICB and catch exceptions.

   Exceptions of type ExceptionT which are thrown by ICB get
   translated into a JS exception with an error message fetched using
   ExceptionT::Getter().

   If PropagateOtherExceptions is true then exception of types other
   than ExceptionT are re-thrown (which can be fatal to v8, so be
   careful). If it is false then they are not propagated but the error
   message in the generated JS exception is unspecified (because we
   have no generic way to get such a message). If a client needs to
   catch multiple exception types, enable propagation and chain the
   callbacks together. In such a case, the outer-most (last) callback
   in the chain should not propagate unknown exceptions (to avoid
   killing v8).


   This type can be used to implement "chaining" of exception
   catching, such that we can use the InCaCatcher
   to catch various distinct exception types in the context
   of one v8::InvocationCallback call.

   Example:

   @code
   // Here we want to catch MyExceptionType, std::runtime_error, and
   // std::exception (the base class of std::runtime_error, by the
   // way) separately:

   // When catching within an exception hierarchy, start with the most
   // specific (most-derived) exceptions.

   // Client-specified exception type:
   typedef InCaCatcher<
      MyExceptionType,
      std::string (),
      &MyExceptionType::getMessage,
      MyCallbackWhichThrows, // the "real" InvocationCallback
      true // make sure propagation is turned on!
      > Catch_MyEx;

  // std::runtime_error:
  typedef InCaCatcher<
      std::runtime_error,
      char const * (),
      &std::runtime_error::what,
      Catch_MyEx::Catch, // next Callback in the chain
      true // make sure propagation is turned on!
      > Catch_RTE;

   // std::exception:
   typedef InCaCatcher_std<
       Catch_RTE::Call,
       false // Often we want no propagation at the top-most level,
             // to avoid killing v8.
       > MyCatcher;

   // Now MyCatcher::Call is-a InvocationCallback which will handle
   // MyExceptionType, std::runtime_error, and std::exception via
   // different catch blocks. Note, however, that the visible
   // behaviour for runtime_error and std::exception (its base class)
   // will be identical here, though they actually have different
   // code.
   @endcode
*/
template < typename ExceptionT,
           typename SigGetMsg,
           typename v8::convert::ConstMethodSignature<ExceptionT,SigGetMsg>::FunctionType Getter,
           // how to do something like this: ???
           // template <class ET, class SGM> class SigT::FunctionType Getter,
           v8::InvocationCallback ICB,
           bool PropagateOtherExceptions = false
    >
struct InCaCatcher : Callable
{
    static v8::Handle<v8::Value> Call( v8::Arguments const & args )
    {
        try
        {
            return ICB( args );
        }
        catch( ExceptionT const & e2 )
        {
            return Toss(CastToJS((e2.*Getter)())->ToString());
        }
        catch( ExceptionT const * e2 )
        {
            return Toss(CastToJS((e2->*Getter)())->ToString());
        }
        catch(...)
        {
            if( PropagateOtherExceptions ) throw;
            else return Toss("Unknown native exception thrown!");
        }
    }
};

/**
   Convenience form of InCaCatcher which catches
   std::exception and uses their what() method to
   fetch the error message.
   
   The ConcreteException parameter may be std::exception (the 
   default) or (in theory) any publically derived subclass.
   When using a non-default value, one can chain exception catchers
   to catch most-derived types first.
   
   PropagateOtherExceptions defaults to false if ConcreteException is
   std::exception (exactly, not a subtype), else it defaults to 
   true. The reasoning is: when chaining these handlers we need to 
   catch the most-derived first. Those handlers need to propagate 
   other exceptions so that we can catch the lesser-derived ones (or 
   those from completely different hierarchies) in subsequent 
   catchers. The final catcher "should" (arguably) swallow unknown 
   exceptions, converting them to JS exceptions with an unspecified 
   message string (propagating them is technically legal but will 
   most likely crash v8).

   Here is an example of chaining:

   @code
    typedef InCaCatcher_std< MyThrowingCallback, std::logic_error > LECatch;
    typedef cv::InCaCatcher_std< LECatch::Call, std::runtime_error > RECatch;
    typedef cv::InCaCatcher_std< RECatch::Call, std::bad_cast > BCCatch;
    typedef cv::InCaCatcher_std< BCCatch::Call > BaseCatch;
    v8::InvocationCallback cb = BaseCatch::Call;
   @endcode
   
   In the above example any exceptions would be processed in the order:
   logic_error, runtime_error, bad_cast, std::exception, anything else.
*/
template <v8::InvocationCallback ICB,
        typename ConcreteException = std::exception,
        bool PropagateOtherExceptions = !tmp::SameType< std::exception, ConcreteException >::Value
>
struct InCaCatcher_std :
    InCaCatcher<ConcreteException,
                char const * (),
                &ConcreteException::what,
                ICB,
                PropagateOtherExceptions
                >
{};


#if !defined(DOXYGEN)
namespace Detail
{
    namespace cv = v8::convert;
    namespace tmp = cv::tmp;
    template <typename FWD>
    struct ArityOverloaderOne : Callable
    {
        static v8::Handle<v8::Value> Call( v8::Arguments const & argv )
        {
            enum { Arity = sl::Arity< FWD >::Value };
            if( (Arity<0) || (Arity == argv.Length()) )
            {
                return FWD::Call( argv );
            }
            else
            {
                cv::StringBuffer msg;
                msg << "ArityOverloaderOne<>::Call(): "
                    //<< argv.Callee()->GetName()
                    << "called with "<<argv.Length()<<" arguments, "
                    << "but requires "<<(int)Arity<<"!\n";
                return v8::ThrowException(msg.toError());
            }
        }
    };
    /**
       Internal dispatch end-of-list routine.
    */
    template <>
    struct ArityOverloaderOne<tmp::NilType> : private Callable
    {
        static v8::Handle<v8::Value> Call( v8::Arguments const & argv )
        {
            return v8::ThrowException(v8::Exception::Error(v8::String::New("ArityOverloaderOne<> end-of-list specialization should not have been called!")));
        }
    };
    /**
       FwdList must be-a TypeList of classes with Call() and Arity members.
    */
    template <typename List>
    struct ArityOverloaderList : Callable
    {
        static v8::Handle<v8::Value> Call( v8::Arguments const & argv )
        {
            typedef typename List::Head FWD;
            typedef typename List::Tail Tail;
            enum { Arity = sl::Arity< FWD >::Value };
            if( (Arity == argv.Length()) || (Arity<0) )
            {
                return ArityOverloaderOne< FWD >::Call( argv );
            }
            {
                return ArityOverloaderList< Tail >::Call(argv);
            }
            return v8::Undefined(); // can't get this far.
        }
    };

    /**
       End-of-list specialization.
    */
    template <>
    struct ArityOverloaderList<tmp::NilType> : Callable
    {
        static v8::Handle<v8::Value> Call( v8::Arguments const & argv )
        {
            cv::StringBuffer msg;
            msg << "ArityOverloaderList<>::Call() there is no overload "
                //<< argv.Callee()->GetName() // name is normally empty
                << "taking "<<argv.Length()<<" arguments!\n";
            return v8::ThrowException( msg.toError() );
        }
    };       
} // namespace Detail
#endif // DOXYGEN

/**
   A helper class which allows us to dispatch to multiple
   overloaded native functions from JS, depending on the argument
   count.

   FwdList must be-a TypeList (or interface-compatible type list) 
   containing types which have the following function:

   static v8::Handle<v8::Value> Call( v8::Arguments const & argv );

   And a static const integer (or enum) value called Arity, 
   which must specify the expected number of arguments, or be 
   negative specify that the function accepts any number of 
   arguments.

   In other words, all entries in FwdList must implement the
   interface used by most of the InCa-related API.
   
   Example:
   
   @code
   // Overload 3 variants of a member function:
   namespace cv = v8::convert;
   typedef cv::Signature< void (
            cv::MethodToInCa<BoundNative, void (), &BoundNative::overload0>,
            cv::MethodToInCa<BoundNative, void (int), &BoundNative::overload1>,
            cv::MethodToInCa<BoundNative, void (int,int), &BoundNative::overload2>
        )> OverloadList;
   typedef cv::InCaOverloadList< OverloadList > MyOverloads;
   v8::InvocationCallback cb = MyOverloads::Call;     
   @endcode

   Note that only one line of that code is evaluated at runtime - the rest
   is all done at compile-time.
*/
template < typename FwdList >
struct InCaOverloadList : Callable
{
    /**
       Tries to dispatch argv to one of the bound functions defined
       in FwdList, based on the number of arguments in argv and
       the Arity 

       Implements the v8::InvocationCallback interface.
    */
    static v8::Handle<v8::Value> Call( v8::Arguments const & argv )
    {
        typedef Detail::ArityOverloaderList<FwdList> X;
        return X::Call( argv );
    }
};

#include "invocable_generated.hpp"

#if !defined(DOXYGEN)
namespace Detail {
    namespace cv = v8::convert;

    //! Internal helper for ToInCa impl.
    template <typename T, typename Sig, bool IsConst = cv::Signature<Sig>::IsConst >
    struct ToInCaSigSelector : cv::ConstMethodSignature<T,Sig>
    {
        template < typename cv::ConstMethodSignature<T,Sig>::FunctionType Func, bool UnlockV8 >
        struct Base : cv::ConstMethodToInCa<T, Sig, Func, UnlockV8 >
        {
        };
    };
    
    //! Internal helper for ToInCa impl.
    template <typename T, typename Sig>
    struct ToInCaSigSelector<T,Sig,false> : MethodSignature<T,Sig>
    {
        template < typename cv::MethodSignature<T,Sig>::FunctionType Func, bool UnlockV8 >
        struct Base : cv::MethodToInCa<T, Sig, Func, UnlockV8 >
        {
        };
    };
    
    //! Internal helper for ToInCa impl.
    template <typename Sig>
    struct ToInCaSigSelector<void,Sig,false> : cv::FunctionSignature<Sig>
    {
        template < typename cv::FunctionSignature<Sig>::FunctionType Func, bool UnlockV8 >
        struct Base : cv::FunctionToInCa<Sig, Func, UnlockV8 >
        {
        };
    };

    /** Internal helper for ToInCa impl.
        We need both true and false specializations here to avoid an ambiguity
        with (T,Sig,true) resp. (T,Sig,false).
    */
    template <typename Sig>
    struct ToInCaSigSelector<void,Sig,true> : ToInCaSigSelector<void,Sig,false> {};

    //! Internal helper for ToInCaVoid impl.
    template <typename T, typename Sig, bool IsConst = cv::Signature<Sig>::IsConst >
    struct ToInCaSigSelectorVoid : cv::ConstMethodSignature<T,Sig>
    {
        template < typename cv::ConstMethodSignature<T,Sig>::FunctionType Func, bool UnlockV8 >
        struct Base : cv::ConstMethodToInCaVoid<T, Sig, Func, UnlockV8 >
        {
        };
    };

    //! Internal helper for ToInCaVoid impl.
    template <typename T, typename Sig>
    struct ToInCaSigSelectorVoid<T,Sig,false> : MethodSignature<T,Sig>
    {
        template < typename cv::MethodSignature<T,Sig>::FunctionType Func, bool UnlockV8 >
        struct Base : cv::MethodToInCaVoid<T, Sig, Func, UnlockV8 >
        {
        };
    };

    //! Internal helper for ToInCaVoid impl.
    template <typename Sig>
    struct ToInCaSigSelectorVoid<void,Sig,false> : cv::FunctionSignature<Sig>
    {
        template < typename cv::FunctionSignature<Sig>::FunctionType Func, bool UnlockV8 >
        struct Base : cv::FunctionToInCaVoid<Sig, Func, UnlockV8 >
        {
        };
    };

    /** Internal helper for ToInCaVoid impl.
        We need both true and false specializations here to avoid an ambiguity
        with (T,Sig,true) resp. (T,Sig,false).
    */
    template <typename Sig>
    struct ToInCaSigSelectorVoid<void,Sig,true> : ToInCaSigSelectorVoid<void,Sig,false> {};

}
#endif // DOXYGEN

/**
    A wrapper for MethodToInCa, ConstMethodToInCa, and 
    FunctionToInCa, which determines which one of those to use based 
    on the type of T and the constness of the method signature Sig.

    For non-member functions, T must be void.

    See ArgsToFunctionForwarder for the meaning of the UnlockV8 parameter.

    Examples:

    @code
    typedef ToInCa<MyT, int (int), &MyT::nonConstFunc> NonConstMethod;
    typedef ToInCa<MyT, void (int) const, &MyT::constFunc> ConstMethod;
    typedef ToInCa<void, int (char const *), ::puts, true> Func;
    
    v8::InvocationCallback cb;
    cb = NonConstMethod::Call;
    cb = ConstMethod::Call;
    cb = Func::Call;
    @endcode

    Note the extra 'const' qualification for const method. This is
    unfortunately neccessary (or at least i haven't found a way around
    it yet). Also note that 'void' 1st parameter for non-member
    functions (another minor hack).

    It is unknown whether or not this template will work in Microsoft
    compilers which reportedly have trouble differentiating 
    constness in templates. The whole reason why (Const)MethodToInCa 
    is split into const- and non-const forms is to be able to 
    work around that shortcoming :/.

    Maintenance reminder: we need the extra level of indirection 
    (the classes in the Detail namespace) to avoid instantiating 
    both ConstMethodToInCa and MethodToInCa with the given 
    singature/function combination (which won't compile). That said, 
    the indirection is purely compile-time - no extra Call() 
    wrappers are injected because of this.
*/
template <typename T, typename Sig,
        typename Detail::ToInCaSigSelector<T,Sig>::FunctionType Func,
        bool UnlockV8 = SignatureIsUnlockable< Detail::ToInCaSigSelector<T,Sig> >::Value
        >
struct ToInCa : Detail::ToInCaSigSelector<T,Sig>::template Base<Func,UnlockV8>
{
};

/**
    Specialization for FunctionToInCa behaviour.
*/
template <typename Sig,
    typename FunctionSignature<Sig>::FunctionType Func,
    bool UnlockV8
>
struct ToInCa<void,Sig,Func,UnlockV8> : FunctionToInCa<Sig,Func,UnlockV8>
{
};

/**
    A slightly simplified form of FunctionToInCa which is only
    useful for "InvocationCallback-like" functions and requires
    only two arguments:
    
    @code
    // int my_func( v8::Arguments const & );
    typedef InCaLikeFunc< int, my_func > F;
    @endcode
*/ 
template <typename RV, RV (*Func)(v8::Arguments const &)>
struct InCaLikeFunc : FunctionToInCa< RV (v8::Arguments const &), Func>
{
};

/**
    A slightly simplified form of MethodToInCa which is only
    useful for non-const "InvocationCallback-like" methods:
    
    @code
    // Method: int MyType::func( v8::Arguments const & )
    typedef InCaLikeMethod<MyType, int, &MyType::func > F;
    @endcode
*/
template <typename T, typename RV, RV (T::*Func)(v8::Arguments const &)>
struct InCaLikeMethod : ToInCa< T, RV (v8::Arguments const &), Func>
{};

/**
    A slightly simplified form of ConstMethodToInCa which is only 
    useful for const "InvocationCallback-like" methods:
    
    @code
    // Method: int MyType::func( v8::Arguments const & ) const
    typedef InCaLikeConstMethod<MyType, int, &MyType::func > F;
    @endcode
*/
template <typename T, typename RV, RV (T::*Func)(v8::Arguments const &) const>
struct InCaLikeConstMethod : ConstMethodToInCa< T, RV (v8::Arguments const &), Func>
{};


/**
    This works just like ToInCa but instead of behaving like
    FunctionToInCa or Const/MethoToInCa it behaves like
    FunctionToInCaVoid or Const/MethoToInCaVoid.
*/
template <typename T, typename Sig,
        typename Detail::ToInCaSigSelectorVoid<T,Sig>::FunctionType Func,
        bool UnlockV8 = SignatureIsUnlockable< Detail::ToInCaSigSelector<T,Sig> >::Value
        >
struct ToInCaVoid : Detail::ToInCaSigSelectorVoid<T,Sig>::template Base<Func,UnlockV8>
{
};

/**
    Specialization for FunctionToInCaVoid behaviour.
*/
template <typename Sig,
    typename FunctionSignature<Sig>::FunctionType Func,
    bool UnlockV8
>
struct ToInCaVoid<void,Sig,Func,UnlockV8> : FunctionToInCaVoid<Sig,Func,UnlockV8>
{
};

/**
    Don't use this yet - it's an experiment.
*/
template <typename ArgPred, typename InCaT>
struct PredicatedInCa : InCaT
{
    bool operator()( v8::Arguments const & argv ) const
    {
        return ArgPred()( argv );
    }
};

/**
    Don't use this yet - it's an experiment.
*/
template <typename TList>
struct PredicatedInCaOverloader;

#if !defined(DOXYGEN)
namespace Detail
{
    template <typename ListType>
    struct PredicatedInCaOverloader : Callable
    {
        static v8::Handle<v8::Value> Call( v8::Arguments const & argv )
        {
            typedef typename ListType::Head Head;
            typedef typename ListType::Tail Tail;
            if( Head()( argv ) )
            {
                return Head::Call( argv );
            }
            else
            {
                return PredicatedInCaOverloader<Tail>::Call(argv);
            }
        }
    };
    template <>
    struct PredicatedInCaOverloader< tmp::NilType > : Callable
    {
        static v8::Handle<v8::Value> Call( v8::Arguments const & argv )
        {
            return cv::Toss(cv::StringBuffer()<<"No predicates in the "
                            << "argument dispatcher matched the given "
                            << "arguments (arg count="<<argv.Length()
                            << ").");
        }
    };
}
#endif // DOXYGEN

/**
    Don't use this yet - it's an experiment.
*/
template <typename TList>
struct PredicatedInCaOverloader : Detail::PredicatedInCaOverloader<TList>
{};

/**
    This class acts as a proxy for another InCa-compatible class,
    running client-defined intialization code the _first_ time
    its callback is called from JS. This could be used to run
    library-dependent intialization routines such as lt_dlinit().
    
    InCaT must conform to the InCa interface (i.e., have a static Call()
    function which implements the v8::InvocationCallback interface).
    
    InitFunctor must be default-constructable and have an operator()
    taking no args and returning any type which can be ignored (i.e.
    not dynamically-allocated resources).
*/
template <typename InCaT, typename InitFunctor>
struct OneTimeInitInCa : Callable
{
    /**
        The first time this function is called it runs 
        InitFunctor()() to execute any client-dependent setup. If 
        that throws a native exception it is propagated back to the 
        caller and initialization is considered NOT to have 
        occurred, meaning the next call to this function will also 
        run InitFunctor()().

        If initialization does not throw, InCaT::Call(argv) is 
        called and its value is returned. Once initialization 
        succeeds, it is _not_ triggered on subsequent calls to this 
        function.

        Pedantic note: if this class is used in code which is linked
        in from multiple DLLs, the init routine might be called
        more than once, depending on the platform.
    */
    static v8::Handle<v8::Value> Call( v8::Arguments const & argv )
    {
        static bool bob = false;
        if( ! bob )
        {
            InitFunctor()();
            /* Reminder: if it throws we do not set bob=true.
               This is part of the interface, not an accident.
            */
            bob = true;
        }
        return InCaT::Call( argv );
    }
};

}} // namespaces

#undef HANDLE_PROPAGATE_EXCEPTION

#endif /* CODE_GOOGLE_COM_V8_CONVERT_INVOCABLE_V8_HPP_INCLUDED */
