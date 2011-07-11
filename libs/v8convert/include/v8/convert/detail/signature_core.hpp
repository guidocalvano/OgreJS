#if !defined(CODE_GOOGLE_COM_V8_CONVERT_SIGNATURE_CORE_HPP_INCLUDED)
#define CODE_GOOGLE_COM_V8_CONVERT_SIGNATURE_CORE_HPP_INCLUDED 1
#include "tmp.hpp"
namespace v8 { namespace convert {
/** @file signature_core.hpp

This file houses the core-most templates related to handling
function/method signatures as full-fleged types.
*/



/** @class Signature

    Base (unimplemented) template for holding 
    function-signature-style argument lists in a type-rich manner. 
    Most implementations are script-generated. All specializations 
    implement a "type list" interface. The sl namespace contains 
    several different compile-time algorithms (sometimes called 
    template metafunctions) for querying the arity and types in a 
    signature.
    
    Sig must be a function-signature-style parameter list, e.g.:
    
    @code
    Signature< void (int, double) >
    Signature< void (MyType::*)( int double ) >
    Signature< void (MyType::*)( char const * ) const >
    @endcode

    This interface treates the "function parameter part" of its arguments as
    a "type list", and several algorithms in the sl namespace are available
    for fetching type information from a Signature type. This is an
    "extended" typelist, however, because it also remembers the return type
    optionally the class containing a member function described by the
    signature (neither of those are counted as part of the list, but are
    accessible separately).

    Require interface for specializations:

    @code
    typedef functionReturnType ReturnType;
    enum { Arity = FunctionArity, IsConst = True_Only_for_Const_Methods };
    typedef T Context; // void for non-member functions, non-cvp T for all T members
    typedef firstArgType Head; // head type of type-list.
    typedef Signature< RV (...)> Tail; // tail of type-list. (...)==arg types 2..N.
    // When Arity==1 or 0, Tail must be tmp::NilType. In theory, for Arity==1
    // Tail should be Signature<RV()>, but this interferes with some typelist
    // algorithms.
    @endcode

    The IsConst part is a bit of an ugly hack. It originates from the design
    decision that we separate const/non-const templates because MSVC
    reportedly cannot differentiate templates when the difference is only in
    const. i have since given up the policy of coddling to MSVC, so the
    IsConst bit might go away at some point (if i can get it back out
    without rewriting everything).

    Reminder to self: we no longer really need the Arity member (we can
    calculate it at compile-time) but lots of code uses it for legacy
    reasons and it saves a small bit if typing (keyboard typing, not C++
    typing). It's on the to-refactor list, though.

    The Arity value -1 is reserved for use with functions taking 
    exactly one v8::Arguments object (which makes them N-arity). 
    Other negative numbers may be used later on for other 
    special-case purposes.

    It is intended to be used like this:
    
    @code
    typedef Signature< int (char const *, double) > Sig;
    assert( Sig::Arity == 2 );
    assert( sl::Length<Sig>::Value == Sig::Arity )
    assert( (tmp::SameType< char const *, sl::At<0,Sig>::Type >::Value) );
    assert( (tmp::SameType< double, sl::At<1,Sig>::Type >::Value) );
    assert( 1 == sl::Index< double, Sig >::Value) );
    assert( !sl::Contains< int, Sig >::Value) ); // Sig::ReturnType doesn't count here!!!
    @endcode

    The IsConst bit is mildly unsettling but i needed it to implement ToInCa
    (i couldn't figure out how to figure that out with templates).
    
    Note that the length of the typelist does not include the return
    value type.
   
    Functions taking one (v8::Arguments const &) argument and 
    returning any type are considered to be 
    "InvocationCallback-like" and are treated specially. They have 
    an Arity value of -1, which is used as a hint by binding code 
    that the function can accept any number of arguments when called 
    from JS code (there is no way to create Arguments objects 
    directly from C++, only indirectly via Call()ing or Apply()ing a 
    v8::Function).
*/
template <typename Sig> struct Signature;


/**
    The sl namespace exclusively holds template metafunctions for working
    with Signature typelists.
*/
namespace sl {

    /**
        Metafunction whose Value member evaluates to the length of the
        given Signature.
    */
    template < typename ListT >
    struct Length : tmp::IntVal<
            tmp::IsNil<typename ListT::Head>::Value ? 0 : (1 + Length<typename ListT::Tail>::Value)
            > {};

    //! End-of-list specialization.
    template <>
    struct Length<tmp::nil> : tmp::IntVal<0> {};

    /**
        Metafunction whose Type member evaluates to the type of the
        I'th argument type in the given Signature. Fails to compile
        if I is out of range.
    */
    template < unsigned short I, typename ListT >
    struct At : At<I-1, typename ListT::Tail>
    {
        typedef char AssertIndex[ (I >= Length<ListT>::Value) ? -1 : 1 ];
    };

    //! Beginning-of-list specialization.
    template < typename ListT >
    struct At<0, ListT>
    {
         typedef typename ListT::Head Type;
    };

    /**
        End-of-list specialization. i don't think we need this, actually.
    */
    template <unsigned short I>
    struct At<I, tmp::nil> : tmp::Identity<tmp::nil>
    {};

    /**
        Metafunction whose Type Value member evaluates to the 0-based
        index of the first occurrance of the the type T in the 
        given Signature's argument list. Evaluates to -1 if T is not 
        contained in the argument list. Signature::ReturnType and 
        Signature::Context are not evaluated.
    */
    template < typename T, typename ListT, unsigned short Internal = 0 >
    struct Index : tmp::IntVal< tmp::SameType<T, typename ListT::Head>::Value
                            ? Internal
                            : Index<T, typename ListT::Tail, Internal+1>::Value>
    {
    };

    //! End-of-list specialization.
    template < typename T, unsigned short Internal >
    struct Index<T,tmp::nil,Internal> : tmp::IntVal<-1> {};
    
    /**
        Convenience form of Index<T,ListT> which evaluates to true 
        if Index returns a non-negative value, else it evaluates
        to false.        
    */
    template < typename T, typename ListT>
    struct Contains : tmp::BoolVal< Index<T,ListT>::Value >= 0  > {};
    
    
    /**
        A metatype whos Value member evaluates to the number of arguments
        in the given typelist, but evaluates to -1 if the only argument
        is (v8::Arguments const &).

        Note that this calculates the length, as opposed to querying
        SigT::Arity (which i would like to get rid of).
    */
    template <typename SigT>
    struct Arity
    {
        enum {
            Value = ((1==Length<SigT>::Value)
                    && (0==Index<v8::Arguments const &,SigT>::Value))
                    ? -1
                    : Length<SigT>::Value
        };
    };
    
    /**
        This metafunction evaluates to true if SigT appears to be
        "InvocationCallback-like" (returns any type and takes one
        (v8::Arguments const &) parameter).
        
        We could implement this a number of different ways. The 
        current impl simply checks if the arity is -1.
    */
    template <typename SigT>
    struct IsInCaLike : tmp::BoolVal< -1 == Arity<SigT>::Value > {};
}

//! Highly arguably specialization.
template <typename RV> struct Signature< Signature<RV> > : Signature<RV> {};

/**
    Specialization to give "InvacationCallback-like" functions
    an Arity value of -1.

    Reminder: we can get rid of this if we factory out the Arity definition
    and use sl::Arity instead. (IsConst might be problematic, though.)
*/
template <typename RV>
struct Signature<RV (v8::Arguments const &)>
{
    typedef RV ReturnType;
    //typedef RV (Fingerprint)(v8::Arguments const &);
    enum { Arity = -1, IsConst = 0 };
    typedef void Context;
    typedef v8::Arguments const & Head;
    typedef Signature<RV ()> Tail;
};

template <typename RV>
struct Signature<RV (*)(v8::Arguments const &)> : Signature<RV (v8::Arguments const &)>
{};

template <typename T, typename RV>
struct Signature<RV (T::*)(v8::Arguments const &)> : Signature<RV (v8::Arguments const &)>
{
    typedef T Context;
};

template <typename T, typename RV>
struct Signature<RV (T::*)(v8::Arguments const &) const> : Signature<RV (v8::Arguments const &)>
{
    typedef T Context;
    enum { IsConst = 1 };
};


/**
   Base type for FunctionSignature, MethodSignature,
   and ConstMethodSignature.

    Sig must be a function-style parameter list in the form:
    
    ReturnType (args types...)
    
    e.g.
    
    double (int, double)

    Since some refactoring on 20110624 we don't really
    need this class - we could use Signature directly.
    However, i might later want to add another class-level detail
    or two which don't belong in that interface. We'll see.
*/
template <typename Sig>
struct SignatureBase : Signature<Sig>
{
    //typedef typename Signature<Sig>::ReturnType ReturnType;
    //enum { Arity = Signature<Sig>::Arity };
    //typedef Sig Signature;
    //typedef Sig FunctionType;
};

/** @class FunctionSignature
   Base (unimplemented) signature for FunctionSignature
   specializations. The type passed to it must be a function
   signature.

   All implementations must define the interface described for 
   Signature and its Context typedef must be void for this type.

   Examples:

   @code
   // void func_foo():
   typedef FunctionSignature< void () > NoArgsReturnsVoid;

   // int func_foo(double):
   typedef FunctionSignature< int (double) > OneArgReturnsInt;

   // double func_foo(int,int):
   typedef FunctionSignature< double (int,int) > TwoArgsReturnsDouble;
   @endcode
   
*/
template <typename FunctionSig>
struct FunctionSignature;

/** @class MethodSignature
   Base (unimplemented) signature for MethodSignature
   specializations. The Sig type passed to it must be a member method
   signature of a function from the class T.
   e.g. (void (T::*)(int))

   All implementations must have the interface called for by Signature
   and the Context typedef must be non-cvp-qualified T.

   Examples: 

   @code
   // void MyType::func():
   typedef MethodSignature< MyType, void () > NoArgsReturnsVoid;

   // int MyType::func(double):
   typedef MethodSignature< MyType, int (double) > OneArgReturnsInt;

   // double MyType::func(int,int):
   typedef MethodSignature< MyType, double (int,int) > TwoArgsReturnsDouble;
   @endcode

*/
template <typename T, typename Sig>
struct MethodSignature;

/** @class ConstMethodSignature
   Base (unimplemented) signature for ConstMethodSignature
   specializations. The Sig type passed to it must be a member
   method signature of a const function from the class T.
   e.g. (void (T::*)(int) const)

   All implementations must have the interface called for by Signature
   and the Context typedef must be non-cvp-qualified T. The IsConst
   member (enum or static/const boolean) must be a true value.

   Examples: 

   @code
   // void MyType::func() const:
   typedef ConstMethodSignature< MyType, void () > NoArgsReturnsVoid;

   // int MyType::func(double) const:
   typedef ConstMethodSignature< MyType, int (double) > OneArgReturnsInt;

   // double MyType::func(int,int) const:
   typedef ConstMethodSignature< MyType, double (int,int) > TwoArgsReturnsDouble;
   @endcode

*/
template <typename T, typename Sig>
struct ConstMethodSignature;

//template <typename T, typename Sig>
//struct ConstMethodSignature<const T,Sig> : ConstMethodSignature<T,Sig> {};

template <typename RV >
struct FunctionSignature< RV () > : SignatureBase< RV () >
{
    typedef RV (*FunctionType)();
};

template <typename RV >
struct FunctionSignature< RV (*)() > : FunctionSignature< RV () >
{
};

template <typename T, typename RV >
struct MethodSignature< T, RV () > : SignatureBase< RV () >
{
    typedef typename tmp::PlainType<T>::Type Context;
    typedef RV (T::*FunctionType)();
};

template <typename T, typename RV >
struct MethodSignature< T, RV (T::*)() > : MethodSignature<T, RV ()>
{
};

template <typename T, typename RV >
struct ConstMethodSignature< T, RV () > : SignatureBase< RV () >
{
    typedef typename tmp::PlainType<T>::Type Context;
    typedef RV (T::*FunctionType)() const;
    enum { IsConst = 1 };
};

template <typename T, typename RV >
struct ConstMethodSignature< T, RV () const > : ConstMethodSignature<T, RV () >
{
    typedef typename tmp::PlainType<T>::Type Context;
    typedef RV (T::*FunctionType)() const;
};


template <typename T, typename RV >
struct ConstMethodSignature< T, RV (T::*)() const > : ConstMethodSignature<T, RV ()>
{
};


/**
   A "type-rich" function pointer.

   Sig must be a function signature type usable in the construct
   FunctionSignature<Sig>. FuncPtr must be a function of that type.
*/
template <typename Sig, typename FunctionSignature<Sig>::FunctionType FuncPtr>
struct FunctionPtr : FunctionSignature<Sig>
{
    /**
       This type's full "signature" type.
    */
    typedef FunctionSignature<Sig> SignatureType;
    /**
       The return type of FuncPtr.
    */
    typedef typename SignatureType::ReturnType ReturnType;
    /**
       The data type of FuncPtr.
     */
    typedef typename SignatureType::FunctionType FunctionType;
    
    /** The function specifies in the template arguments. */
    static const FunctionType Function;
};
template <typename Sig, typename FunctionSignature<Sig>::FunctionType FuncPtr>
typename FunctionPtr<Sig,FuncPtr>::FunctionType const FunctionPtr<Sig,FuncPtr>::Function = FuncPtr;

/**
   Used like FunctionPtr, but in conjunction with non-const
   member functions ("methods") of the T class. See FunctionPtr
   for the requirements of the Sig type.
*/
template <typename T, typename Sig, typename MethodSignature<T,Sig>::FunctionType FuncPtr>
struct MethodPtr : MethodSignature<T,Sig>
{
    typedef MethodSignature<T,Sig> SignatureType;
    typedef typename SignatureType::ReturnType ReturnType;
    typedef typename SignatureType::FunctionType FunctionType;
    static const FunctionType Function;
};
template <typename T, typename Sig, typename MethodSignature<T,Sig>::FunctionType FuncPtr>
typename MethodPtr<T,Sig,FuncPtr>::FunctionType const MethodPtr<T,Sig,FuncPtr>::Function = FuncPtr;

/**
   Used like MethodPtr, but in conjunction with const methods of the T
   class.
*/
template <typename T, typename Sig, typename ConstMethodSignature<T,Sig>::FunctionType FuncPtr>
struct ConstMethodPtr : ConstMethodSignature<T,Sig>
{
    typedef ConstMethodSignature<T,Sig> SignatureType;
    typedef typename SignatureType::ReturnType ReturnType;
    typedef typename SignatureType::FunctionType FunctionType;
    static const FunctionType Function;
};
template <typename T, typename Sig, typename ConstMethodSignature<T,Sig>::FunctionType FuncPtr>
typename ConstMethodPtr<T,Sig,FuncPtr>::FunctionType const ConstMethodPtr<T,Sig,FuncPtr>::Function = FuncPtr;

#include "signature_generated.hpp"
}} // namespaces

#endif /* CODE_GOOGLE_COM_V8_CONVERT_SIGNATURE_CORE_HPP_INCLUDED */
