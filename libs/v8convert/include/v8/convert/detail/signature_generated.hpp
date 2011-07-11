/* AUTO-GENERATED CODE! EDIT AT YOUR OWN RISK! */
#if !defined(DOXYGEN)

template <typename RV>
struct Signature< RV () >
{
    typedef RV ReturnType;
    enum { Arity = 0, IsConst = 0 };
    typedef void Context;
    //typedef RV (FunctionType)();
    typedef RV (*FunctionType)();
    typedef tmp::NilType Head;
    typedef Head Tail;
};
template <typename RV>
struct Signature< RV (*)() > : Signature<RV ()>
{};
template <typename RV>
struct Signature< RV () const > : Signature<RV ()>
{
    enum { IsConst = 1 };
};
//! Specialization for 1 arg(s).
template <typename RV, typename A1>
struct Signature< RV (A1) >
{
    typedef RV ReturnType;
    enum { Arity = 1, IsConst = 0 };
    typedef void Context;
    typedef RV (*FunctionType)(A1);
    typedef A1 Head;
    typedef tmp::NilType Tail;
};

//! Specialization for 1 arg(s).
template <typename RV, typename A1>
struct Signature< RV (A1) const > : Signature<RV (A1)>
{
    enum { IsConst = 1 };
};

//! Specialization for 1 arg(s).
template <typename RV, typename A1>
struct Signature< RV (*)(A1) > : Signature<RV (A1)>
{};

//! Specialization for T methods taking 1 arg(s).
template <typename T, typename RV, typename A1>
struct Signature< RV (T::*)(A1) > : Signature<RV (A1)>
{
    typedef T Context;
};

//! Specialization for T const methods taking 1 arg(s).
template <typename T, typename RV, typename A1>
struct Signature< RV (T::*)(A1) const > : Signature<RV (A1) const>
{
    typedef T Context;
    enum { IsConst = 1 };
};
//! Specialization for 2 arg(s).
template <typename RV, typename A1, typename A2>
struct Signature< RV (A1, A2) >
{
    typedef RV ReturnType;
    enum { Arity = 2, IsConst = 0 };
    typedef void Context;
    typedef RV (*FunctionType)(A1, A2);
    typedef A1 Head;
    typedef Signature<RV ( A2)> Tail;
};

//! Specialization for 2 arg(s).
template <typename RV, typename A1, typename A2>
struct Signature< RV (A1, A2) const > : Signature<RV (A1, A2)>
{
    enum { IsConst = 1 };
};

//! Specialization for 2 arg(s).
template <typename RV, typename A1, typename A2>
struct Signature< RV (*)(A1, A2) > : Signature<RV (A1, A2)>
{};

//! Specialization for T methods taking 2 arg(s).
template <typename T, typename RV, typename A1, typename A2>
struct Signature< RV (T::*)(A1, A2) > : Signature<RV (A1, A2)>
{
    typedef T Context;
};

//! Specialization for T const methods taking 2 arg(s).
template <typename T, typename RV, typename A1, typename A2>
struct Signature< RV (T::*)(A1, A2) const > : Signature<RV (A1, A2) const>
{
    typedef T Context;
    enum { IsConst = 1 };
};
//! Specialization for 3 arg(s).
template <typename RV, typename A1, typename A2, typename A3>
struct Signature< RV (A1, A2, A3) >
{
    typedef RV ReturnType;
    enum { Arity = 3, IsConst = 0 };
    typedef void Context;
    typedef RV (*FunctionType)(A1, A2, A3);
    typedef A1 Head;
    typedef Signature<RV ( A2, A3)> Tail;
};

//! Specialization for 3 arg(s).
template <typename RV, typename A1, typename A2, typename A3>
struct Signature< RV (A1, A2, A3) const > : Signature<RV (A1, A2, A3)>
{
    enum { IsConst = 1 };
};

//! Specialization for 3 arg(s).
template <typename RV, typename A1, typename A2, typename A3>
struct Signature< RV (*)(A1, A2, A3) > : Signature<RV (A1, A2, A3)>
{};

//! Specialization for T methods taking 3 arg(s).
template <typename T, typename RV, typename A1, typename A2, typename A3>
struct Signature< RV (T::*)(A1, A2, A3) > : Signature<RV (A1, A2, A3)>
{
    typedef T Context;
};

//! Specialization for T const methods taking 3 arg(s).
template <typename T, typename RV, typename A1, typename A2, typename A3>
struct Signature< RV (T::*)(A1, A2, A3) const > : Signature<RV (A1, A2, A3) const>
{
    typedef T Context;
    enum { IsConst = 1 };
};
//! Specialization for 4 arg(s).
template <typename RV, typename A1, typename A2, typename A3, typename A4>
struct Signature< RV (A1, A2, A3, A4) >
{
    typedef RV ReturnType;
    enum { Arity = 4, IsConst = 0 };
    typedef void Context;
    typedef RV (*FunctionType)(A1, A2, A3, A4);
    typedef A1 Head;
    typedef Signature<RV ( A2, A3, A4)> Tail;
};

//! Specialization for 4 arg(s).
template <typename RV, typename A1, typename A2, typename A3, typename A4>
struct Signature< RV (A1, A2, A3, A4) const > : Signature<RV (A1, A2, A3, A4)>
{
    enum { IsConst = 1 };
};

//! Specialization for 4 arg(s).
template <typename RV, typename A1, typename A2, typename A3, typename A4>
struct Signature< RV (*)(A1, A2, A3, A4) > : Signature<RV (A1, A2, A3, A4)>
{};

//! Specialization for T methods taking 4 arg(s).
template <typename T, typename RV, typename A1, typename A2, typename A3, typename A4>
struct Signature< RV (T::*)(A1, A2, A3, A4) > : Signature<RV (A1, A2, A3, A4)>
{
    typedef T Context;
};

//! Specialization for T const methods taking 4 arg(s).
template <typename T, typename RV, typename A1, typename A2, typename A3, typename A4>
struct Signature< RV (T::*)(A1, A2, A3, A4) const > : Signature<RV (A1, A2, A3, A4) const>
{
    typedef T Context;
    enum { IsConst = 1 };
};
//! Specialization for 5 arg(s).
template <typename RV, typename A1, typename A2, typename A3, typename A4, typename A5>
struct Signature< RV (A1, A2, A3, A4, A5) >
{
    typedef RV ReturnType;
    enum { Arity = 5, IsConst = 0 };
    typedef void Context;
    typedef RV (*FunctionType)(A1, A2, A3, A4, A5);
    typedef A1 Head;
    typedef Signature<RV ( A2, A3, A4, A5)> Tail;
};

//! Specialization for 5 arg(s).
template <typename RV, typename A1, typename A2, typename A3, typename A4, typename A5>
struct Signature< RV (A1, A2, A3, A4, A5) const > : Signature<RV (A1, A2, A3, A4, A5)>
{
    enum { IsConst = 1 };
};

//! Specialization for 5 arg(s).
template <typename RV, typename A1, typename A2, typename A3, typename A4, typename A5>
struct Signature< RV (*)(A1, A2, A3, A4, A5) > : Signature<RV (A1, A2, A3, A4, A5)>
{};

//! Specialization for T methods taking 5 arg(s).
template <typename T, typename RV, typename A1, typename A2, typename A3, typename A4, typename A5>
struct Signature< RV (T::*)(A1, A2, A3, A4, A5) > : Signature<RV (A1, A2, A3, A4, A5)>
{
    typedef T Context;
};

//! Specialization for T const methods taking 5 arg(s).
template <typename T, typename RV, typename A1, typename A2, typename A3, typename A4, typename A5>
struct Signature< RV (T::*)(A1, A2, A3, A4, A5) const > : Signature<RV (A1, A2, A3, A4, A5) const>
{
    typedef T Context;
    enum { IsConst = 1 };
};
//! Specialization for 6 arg(s).
template <typename RV, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6>
struct Signature< RV (A1, A2, A3, A4, A5, A6) >
{
    typedef RV ReturnType;
    enum { Arity = 6, IsConst = 0 };
    typedef void Context;
    typedef RV (*FunctionType)(A1, A2, A3, A4, A5, A6);
    typedef A1 Head;
    typedef Signature<RV ( A2, A3, A4, A5, A6)> Tail;
};

//! Specialization for 6 arg(s).
template <typename RV, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6>
struct Signature< RV (A1, A2, A3, A4, A5, A6) const > : Signature<RV (A1, A2, A3, A4, A5, A6)>
{
    enum { IsConst = 1 };
};

//! Specialization for 6 arg(s).
template <typename RV, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6>
struct Signature< RV (*)(A1, A2, A3, A4, A5, A6) > : Signature<RV (A1, A2, A3, A4, A5, A6)>
{};

//! Specialization for T methods taking 6 arg(s).
template <typename T, typename RV, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6>
struct Signature< RV (T::*)(A1, A2, A3, A4, A5, A6) > : Signature<RV (A1, A2, A3, A4, A5, A6)>
{
    typedef T Context;
};

//! Specialization for T const methods taking 6 arg(s).
template <typename T, typename RV, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6>
struct Signature< RV (T::*)(A1, A2, A3, A4, A5, A6) const > : Signature<RV (A1, A2, A3, A4, A5, A6) const>
{
    typedef T Context;
    enum { IsConst = 1 };
};
//! Specialization for 7 arg(s).
template <typename RV, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7>
struct Signature< RV (A1, A2, A3, A4, A5, A6, A7) >
{
    typedef RV ReturnType;
    enum { Arity = 7, IsConst = 0 };
    typedef void Context;
    typedef RV (*FunctionType)(A1, A2, A3, A4, A5, A6, A7);
    typedef A1 Head;
    typedef Signature<RV ( A2, A3, A4, A5, A6, A7)> Tail;
};

//! Specialization for 7 arg(s).
template <typename RV, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7>
struct Signature< RV (A1, A2, A3, A4, A5, A6, A7) const > : Signature<RV (A1, A2, A3, A4, A5, A6, A7)>
{
    enum { IsConst = 1 };
};

//! Specialization for 7 arg(s).
template <typename RV, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7>
struct Signature< RV (*)(A1, A2, A3, A4, A5, A6, A7) > : Signature<RV (A1, A2, A3, A4, A5, A6, A7)>
{};

//! Specialization for T methods taking 7 arg(s).
template <typename T, typename RV, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7>
struct Signature< RV (T::*)(A1, A2, A3, A4, A5, A6, A7) > : Signature<RV (A1, A2, A3, A4, A5, A6, A7)>
{
    typedef T Context;
};

//! Specialization for T const methods taking 7 arg(s).
template <typename T, typename RV, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7>
struct Signature< RV (T::*)(A1, A2, A3, A4, A5, A6, A7) const > : Signature<RV (A1, A2, A3, A4, A5, A6, A7) const>
{
    typedef T Context;
    enum { IsConst = 1 };
};
//! Specialization for 8 arg(s).
template <typename RV, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8>
struct Signature< RV (A1, A2, A3, A4, A5, A6, A7, A8) >
{
    typedef RV ReturnType;
    enum { Arity = 8, IsConst = 0 };
    typedef void Context;
    typedef RV (*FunctionType)(A1, A2, A3, A4, A5, A6, A7, A8);
    typedef A1 Head;
    typedef Signature<RV ( A2, A3, A4, A5, A6, A7, A8)> Tail;
};

//! Specialization for 8 arg(s).
template <typename RV, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8>
struct Signature< RV (A1, A2, A3, A4, A5, A6, A7, A8) const > : Signature<RV (A1, A2, A3, A4, A5, A6, A7, A8)>
{
    enum { IsConst = 1 };
};

//! Specialization for 8 arg(s).
template <typename RV, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8>
struct Signature< RV (*)(A1, A2, A3, A4, A5, A6, A7, A8) > : Signature<RV (A1, A2, A3, A4, A5, A6, A7, A8)>
{};

//! Specialization for T methods taking 8 arg(s).
template <typename T, typename RV, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8>
struct Signature< RV (T::*)(A1, A2, A3, A4, A5, A6, A7, A8) > : Signature<RV (A1, A2, A3, A4, A5, A6, A7, A8)>
{
    typedef T Context;
};

//! Specialization for T const methods taking 8 arg(s).
template <typename T, typename RV, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8>
struct Signature< RV (T::*)(A1, A2, A3, A4, A5, A6, A7, A8) const > : Signature<RV (A1, A2, A3, A4, A5, A6, A7, A8) const>
{
    typedef T Context;
    enum { IsConst = 1 };
};
//! Specialization for 9 arg(s).
template <typename RV, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8, typename A9>
struct Signature< RV (A1, A2, A3, A4, A5, A6, A7, A8, A9) >
{
    typedef RV ReturnType;
    enum { Arity = 9, IsConst = 0 };
    typedef void Context;
    typedef RV (*FunctionType)(A1, A2, A3, A4, A5, A6, A7, A8, A9);
    typedef A1 Head;
    typedef Signature<RV ( A2, A3, A4, A5, A6, A7, A8, A9)> Tail;
};

//! Specialization for 9 arg(s).
template <typename RV, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8, typename A9>
struct Signature< RV (A1, A2, A3, A4, A5, A6, A7, A8, A9) const > : Signature<RV (A1, A2, A3, A4, A5, A6, A7, A8, A9)>
{
    enum { IsConst = 1 };
};

//! Specialization for 9 arg(s).
template <typename RV, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8, typename A9>
struct Signature< RV (*)(A1, A2, A3, A4, A5, A6, A7, A8, A9) > : Signature<RV (A1, A2, A3, A4, A5, A6, A7, A8, A9)>
{};

//! Specialization for T methods taking 9 arg(s).
template <typename T, typename RV, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8, typename A9>
struct Signature< RV (T::*)(A1, A2, A3, A4, A5, A6, A7, A8, A9) > : Signature<RV (A1, A2, A3, A4, A5, A6, A7, A8, A9)>
{
    typedef T Context;
};

//! Specialization for T const methods taking 9 arg(s).
template <typename T, typename RV, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8, typename A9>
struct Signature< RV (T::*)(A1, A2, A3, A4, A5, A6, A7, A8, A9) const > : Signature<RV (A1, A2, A3, A4, A5, A6, A7, A8, A9) const>
{
    typedef T Context;
    enum { IsConst = 1 };
};
//! Specialization for 10 arg(s).
template <typename RV, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8, typename A9, typename A10>
struct Signature< RV (A1, A2, A3, A4, A5, A6, A7, A8, A9, A10) >
{
    typedef RV ReturnType;
    enum { Arity = 10, IsConst = 0 };
    typedef void Context;
    typedef RV (*FunctionType)(A1, A2, A3, A4, A5, A6, A7, A8, A9, A10);
    typedef A1 Head;
    typedef Signature<RV ( A2, A3, A4, A5, A6, A7, A8, A9, A10)> Tail;
};

//! Specialization for 10 arg(s).
template <typename RV, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8, typename A9, typename A10>
struct Signature< RV (A1, A2, A3, A4, A5, A6, A7, A8, A9, A10) const > : Signature<RV (A1, A2, A3, A4, A5, A6, A7, A8, A9, A10)>
{
    enum { IsConst = 1 };
};

//! Specialization for 10 arg(s).
template <typename RV, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8, typename A9, typename A10>
struct Signature< RV (*)(A1, A2, A3, A4, A5, A6, A7, A8, A9, A10) > : Signature<RV (A1, A2, A3, A4, A5, A6, A7, A8, A9, A10)>
{};

//! Specialization for T methods taking 10 arg(s).
template <typename T, typename RV, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8, typename A9, typename A10>
struct Signature< RV (T::*)(A1, A2, A3, A4, A5, A6, A7, A8, A9, A10) > : Signature<RV (A1, A2, A3, A4, A5, A6, A7, A8, A9, A10)>
{
    typedef T Context;
};

//! Specialization for T const methods taking 10 arg(s).
template <typename T, typename RV, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8, typename A9, typename A10>
struct Signature< RV (T::*)(A1, A2, A3, A4, A5, A6, A7, A8, A9, A10) const > : Signature<RV (A1, A2, A3, A4, A5, A6, A7, A8, A9, A10) const>
{
    typedef T Context;
    enum { IsConst = 1 };
};
template <typename RV,  typename A0 >
struct FunctionSignature< RV ( A0) > : SignatureBase< RV ( A0) >
{
    typedef RV (*FunctionType)( A0);
};

template <typename RV,  typename A0 >
struct FunctionSignature< RV (*)( A0) >
  : FunctionSignature< RV ( A0) >
{};


template <typename T, typename RV,  typename A0 >
struct MethodSignature< T, RV ( A0) > : SignatureBase< RV ( A0) >
{
    typedef T ClassType;
    typedef RV (T::*FunctionType)( A0);
};
template <typename T, typename RV,  typename A0 >
struct MethodSignature< T, RV (T::*)( A0) > :
    MethodSignature< T, RV ( A0) >
{};


template <typename T, typename RV,  typename A0 >
struct ConstMethodSignature< T, RV ( A0) > : SignatureBase< RV ( A0) >
{
    typedef T ClassType;
    typedef RV (T::*FunctionType)( A0) const;
};

template <typename T, typename RV,  typename A0 >
struct ConstMethodSignature< T, RV ( A0) const > :
    ConstMethodSignature< T, RV ( A0) >
{};


template <typename T, typename RV,  typename A0 >
struct ConstMethodSignature< T, RV (T::*)( A0) const > :
    ConstMethodSignature< T, RV ( A0) >
{};
template <typename RV,  typename A0,  typename A1 >
struct FunctionSignature< RV ( A0,  A1) > : SignatureBase< RV ( A0,  A1) >
{
    typedef RV (*FunctionType)( A0,  A1);
};

template <typename RV,  typename A0,  typename A1 >
struct FunctionSignature< RV (*)( A0,  A1) >
  : FunctionSignature< RV ( A0,  A1) >
{};


template <typename T, typename RV,  typename A0,  typename A1 >
struct MethodSignature< T, RV ( A0,  A1) > : SignatureBase< RV ( A0,  A1) >
{
    typedef T ClassType;
    typedef RV (T::*FunctionType)( A0,  A1);
};
template <typename T, typename RV,  typename A0,  typename A1 >
struct MethodSignature< T, RV (T::*)( A0,  A1) > :
    MethodSignature< T, RV ( A0,  A1) >
{};


template <typename T, typename RV,  typename A0,  typename A1 >
struct ConstMethodSignature< T, RV ( A0,  A1) > : SignatureBase< RV ( A0,  A1) >
{
    typedef T ClassType;
    typedef RV (T::*FunctionType)( A0,  A1) const;
};

template <typename T, typename RV,  typename A0,  typename A1 >
struct ConstMethodSignature< T, RV ( A0,  A1) const > :
    ConstMethodSignature< T, RV ( A0,  A1) >
{};


template <typename T, typename RV,  typename A0,  typename A1 >
struct ConstMethodSignature< T, RV (T::*)( A0,  A1) const > :
    ConstMethodSignature< T, RV ( A0,  A1) >
{};
template <typename RV,  typename A0,  typename A1,  typename A2 >
struct FunctionSignature< RV ( A0,  A1,  A2) > : SignatureBase< RV ( A0,  A1,  A2) >
{
    typedef RV (*FunctionType)( A0,  A1,  A2);
};

template <typename RV,  typename A0,  typename A1,  typename A2 >
struct FunctionSignature< RV (*)( A0,  A1,  A2) >
  : FunctionSignature< RV ( A0,  A1,  A2) >
{};


template <typename T, typename RV,  typename A0,  typename A1,  typename A2 >
struct MethodSignature< T, RV ( A0,  A1,  A2) > : SignatureBase< RV ( A0,  A1,  A2) >
{
    typedef T ClassType;
    typedef RV (T::*FunctionType)( A0,  A1,  A2);
};
template <typename T, typename RV,  typename A0,  typename A1,  typename A2 >
struct MethodSignature< T, RV (T::*)( A0,  A1,  A2) > :
    MethodSignature< T, RV ( A0,  A1,  A2) >
{};


template <typename T, typename RV,  typename A0,  typename A1,  typename A2 >
struct ConstMethodSignature< T, RV ( A0,  A1,  A2) > : SignatureBase< RV ( A0,  A1,  A2) >
{
    typedef T ClassType;
    typedef RV (T::*FunctionType)( A0,  A1,  A2) const;
};

template <typename T, typename RV,  typename A0,  typename A1,  typename A2 >
struct ConstMethodSignature< T, RV ( A0,  A1,  A2) const > :
    ConstMethodSignature< T, RV ( A0,  A1,  A2) >
{};


template <typename T, typename RV,  typename A0,  typename A1,  typename A2 >
struct ConstMethodSignature< T, RV (T::*)( A0,  A1,  A2) const > :
    ConstMethodSignature< T, RV ( A0,  A1,  A2) >
{};
template <typename RV,  typename A0,  typename A1,  typename A2,  typename A3 >
struct FunctionSignature< RV ( A0,  A1,  A2,  A3) > : SignatureBase< RV ( A0,  A1,  A2,  A3) >
{
    typedef RV (*FunctionType)( A0,  A1,  A2,  A3);
};

template <typename RV,  typename A0,  typename A1,  typename A2,  typename A3 >
struct FunctionSignature< RV (*)( A0,  A1,  A2,  A3) >
  : FunctionSignature< RV ( A0,  A1,  A2,  A3) >
{};


template <typename T, typename RV,  typename A0,  typename A1,  typename A2,  typename A3 >
struct MethodSignature< T, RV ( A0,  A1,  A2,  A3) > : SignatureBase< RV ( A0,  A1,  A2,  A3) >
{
    typedef T ClassType;
    typedef RV (T::*FunctionType)( A0,  A1,  A2,  A3);
};
template <typename T, typename RV,  typename A0,  typename A1,  typename A2,  typename A3 >
struct MethodSignature< T, RV (T::*)( A0,  A1,  A2,  A3) > :
    MethodSignature< T, RV ( A0,  A1,  A2,  A3) >
{};


template <typename T, typename RV,  typename A0,  typename A1,  typename A2,  typename A3 >
struct ConstMethodSignature< T, RV ( A0,  A1,  A2,  A3) > : SignatureBase< RV ( A0,  A1,  A2,  A3) >
{
    typedef T ClassType;
    typedef RV (T::*FunctionType)( A0,  A1,  A2,  A3) const;
};

template <typename T, typename RV,  typename A0,  typename A1,  typename A2,  typename A3 >
struct ConstMethodSignature< T, RV ( A0,  A1,  A2,  A3) const > :
    ConstMethodSignature< T, RV ( A0,  A1,  A2,  A3) >
{};


template <typename T, typename RV,  typename A0,  typename A1,  typename A2,  typename A3 >
struct ConstMethodSignature< T, RV (T::*)( A0,  A1,  A2,  A3) const > :
    ConstMethodSignature< T, RV ( A0,  A1,  A2,  A3) >
{};
template <typename RV,  typename A0,  typename A1,  typename A2,  typename A3,  typename A4 >
struct FunctionSignature< RV ( A0,  A1,  A2,  A3,  A4) > : SignatureBase< RV ( A0,  A1,  A2,  A3,  A4) >
{
    typedef RV (*FunctionType)( A0,  A1,  A2,  A3,  A4);
};

template <typename RV,  typename A0,  typename A1,  typename A2,  typename A3,  typename A4 >
struct FunctionSignature< RV (*)( A0,  A1,  A2,  A3,  A4) >
  : FunctionSignature< RV ( A0,  A1,  A2,  A3,  A4) >
{};


template <typename T, typename RV,  typename A0,  typename A1,  typename A2,  typename A3,  typename A4 >
struct MethodSignature< T, RV ( A0,  A1,  A2,  A3,  A4) > : SignatureBase< RV ( A0,  A1,  A2,  A3,  A4) >
{
    typedef T ClassType;
    typedef RV (T::*FunctionType)( A0,  A1,  A2,  A3,  A4);
};
template <typename T, typename RV,  typename A0,  typename A1,  typename A2,  typename A3,  typename A4 >
struct MethodSignature< T, RV (T::*)( A0,  A1,  A2,  A3,  A4) > :
    MethodSignature< T, RV ( A0,  A1,  A2,  A3,  A4) >
{};


template <typename T, typename RV,  typename A0,  typename A1,  typename A2,  typename A3,  typename A4 >
struct ConstMethodSignature< T, RV ( A0,  A1,  A2,  A3,  A4) > : SignatureBase< RV ( A0,  A1,  A2,  A3,  A4) >
{
    typedef T ClassType;
    typedef RV (T::*FunctionType)( A0,  A1,  A2,  A3,  A4) const;
};

template <typename T, typename RV,  typename A0,  typename A1,  typename A2,  typename A3,  typename A4 >
struct ConstMethodSignature< T, RV ( A0,  A1,  A2,  A3,  A4) const > :
    ConstMethodSignature< T, RV ( A0,  A1,  A2,  A3,  A4) >
{};


template <typename T, typename RV,  typename A0,  typename A1,  typename A2,  typename A3,  typename A4 >
struct ConstMethodSignature< T, RV (T::*)( A0,  A1,  A2,  A3,  A4) const > :
    ConstMethodSignature< T, RV ( A0,  A1,  A2,  A3,  A4) >
{};
template <typename RV,  typename A0,  typename A1,  typename A2,  typename A3,  typename A4,  typename A5 >
struct FunctionSignature< RV ( A0,  A1,  A2,  A3,  A4,  A5) > : SignatureBase< RV ( A0,  A1,  A2,  A3,  A4,  A5) >
{
    typedef RV (*FunctionType)( A0,  A1,  A2,  A3,  A4,  A5);
};

template <typename RV,  typename A0,  typename A1,  typename A2,  typename A3,  typename A4,  typename A5 >
struct FunctionSignature< RV (*)( A0,  A1,  A2,  A3,  A4,  A5) >
  : FunctionSignature< RV ( A0,  A1,  A2,  A3,  A4,  A5) >
{};


template <typename T, typename RV,  typename A0,  typename A1,  typename A2,  typename A3,  typename A4,  typename A5 >
struct MethodSignature< T, RV ( A0,  A1,  A2,  A3,  A4,  A5) > : SignatureBase< RV ( A0,  A1,  A2,  A3,  A4,  A5) >
{
    typedef T ClassType;
    typedef RV (T::*FunctionType)( A0,  A1,  A2,  A3,  A4,  A5);
};
template <typename T, typename RV,  typename A0,  typename A1,  typename A2,  typename A3,  typename A4,  typename A5 >
struct MethodSignature< T, RV (T::*)( A0,  A1,  A2,  A3,  A4,  A5) > :
    MethodSignature< T, RV ( A0,  A1,  A2,  A3,  A4,  A5) >
{};


template <typename T, typename RV,  typename A0,  typename A1,  typename A2,  typename A3,  typename A4,  typename A5 >
struct ConstMethodSignature< T, RV ( A0,  A1,  A2,  A3,  A4,  A5) > : SignatureBase< RV ( A0,  A1,  A2,  A3,  A4,  A5) >
{
    typedef T ClassType;
    typedef RV (T::*FunctionType)( A0,  A1,  A2,  A3,  A4,  A5) const;
};

template <typename T, typename RV,  typename A0,  typename A1,  typename A2,  typename A3,  typename A4,  typename A5 >
struct ConstMethodSignature< T, RV ( A0,  A1,  A2,  A3,  A4,  A5) const > :
    ConstMethodSignature< T, RV ( A0,  A1,  A2,  A3,  A4,  A5) >
{};


template <typename T, typename RV,  typename A0,  typename A1,  typename A2,  typename A3,  typename A4,  typename A5 >
struct ConstMethodSignature< T, RV (T::*)( A0,  A1,  A2,  A3,  A4,  A5) const > :
    ConstMethodSignature< T, RV ( A0,  A1,  A2,  A3,  A4,  A5) >
{};
template <typename RV,  typename A0,  typename A1,  typename A2,  typename A3,  typename A4,  typename A5,  typename A6 >
struct FunctionSignature< RV ( A0,  A1,  A2,  A3,  A4,  A5,  A6) > : SignatureBase< RV ( A0,  A1,  A2,  A3,  A4,  A5,  A6) >
{
    typedef RV (*FunctionType)( A0,  A1,  A2,  A3,  A4,  A5,  A6);
};

template <typename RV,  typename A0,  typename A1,  typename A2,  typename A3,  typename A4,  typename A5,  typename A6 >
struct FunctionSignature< RV (*)( A0,  A1,  A2,  A3,  A4,  A5,  A6) >
  : FunctionSignature< RV ( A0,  A1,  A2,  A3,  A4,  A5,  A6) >
{};


template <typename T, typename RV,  typename A0,  typename A1,  typename A2,  typename A3,  typename A4,  typename A5,  typename A6 >
struct MethodSignature< T, RV ( A0,  A1,  A2,  A3,  A4,  A5,  A6) > : SignatureBase< RV ( A0,  A1,  A2,  A3,  A4,  A5,  A6) >
{
    typedef T ClassType;
    typedef RV (T::*FunctionType)( A0,  A1,  A2,  A3,  A4,  A5,  A6);
};
template <typename T, typename RV,  typename A0,  typename A1,  typename A2,  typename A3,  typename A4,  typename A5,  typename A6 >
struct MethodSignature< T, RV (T::*)( A0,  A1,  A2,  A3,  A4,  A5,  A6) > :
    MethodSignature< T, RV ( A0,  A1,  A2,  A3,  A4,  A5,  A6) >
{};


template <typename T, typename RV,  typename A0,  typename A1,  typename A2,  typename A3,  typename A4,  typename A5,  typename A6 >
struct ConstMethodSignature< T, RV ( A0,  A1,  A2,  A3,  A4,  A5,  A6) > : SignatureBase< RV ( A0,  A1,  A2,  A3,  A4,  A5,  A6) >
{
    typedef T ClassType;
    typedef RV (T::*FunctionType)( A0,  A1,  A2,  A3,  A4,  A5,  A6) const;
};

template <typename T, typename RV,  typename A0,  typename A1,  typename A2,  typename A3,  typename A4,  typename A5,  typename A6 >
struct ConstMethodSignature< T, RV ( A0,  A1,  A2,  A3,  A4,  A5,  A6) const > :
    ConstMethodSignature< T, RV ( A0,  A1,  A2,  A3,  A4,  A5,  A6) >
{};


template <typename T, typename RV,  typename A0,  typename A1,  typename A2,  typename A3,  typename A4,  typename A5,  typename A6 >
struct ConstMethodSignature< T, RV (T::*)( A0,  A1,  A2,  A3,  A4,  A5,  A6) const > :
    ConstMethodSignature< T, RV ( A0,  A1,  A2,  A3,  A4,  A5,  A6) >
{};
template <typename RV,  typename A0,  typename A1,  typename A2,  typename A3,  typename A4,  typename A5,  typename A6,  typename A7 >
struct FunctionSignature< RV ( A0,  A1,  A2,  A3,  A4,  A5,  A6,  A7) > : SignatureBase< RV ( A0,  A1,  A2,  A3,  A4,  A5,  A6,  A7) >
{
    typedef RV (*FunctionType)( A0,  A1,  A2,  A3,  A4,  A5,  A6,  A7);
};

template <typename RV,  typename A0,  typename A1,  typename A2,  typename A3,  typename A4,  typename A5,  typename A6,  typename A7 >
struct FunctionSignature< RV (*)( A0,  A1,  A2,  A3,  A4,  A5,  A6,  A7) >
  : FunctionSignature< RV ( A0,  A1,  A2,  A3,  A4,  A5,  A6,  A7) >
{};


template <typename T, typename RV,  typename A0,  typename A1,  typename A2,  typename A3,  typename A4,  typename A5,  typename A6,  typename A7 >
struct MethodSignature< T, RV ( A0,  A1,  A2,  A3,  A4,  A5,  A6,  A7) > : SignatureBase< RV ( A0,  A1,  A2,  A3,  A4,  A5,  A6,  A7) >
{
    typedef T ClassType;
    typedef RV (T::*FunctionType)( A0,  A1,  A2,  A3,  A4,  A5,  A6,  A7);
};
template <typename T, typename RV,  typename A0,  typename A1,  typename A2,  typename A3,  typename A4,  typename A5,  typename A6,  typename A7 >
struct MethodSignature< T, RV (T::*)( A0,  A1,  A2,  A3,  A4,  A5,  A6,  A7) > :
    MethodSignature< T, RV ( A0,  A1,  A2,  A3,  A4,  A5,  A6,  A7) >
{};


template <typename T, typename RV,  typename A0,  typename A1,  typename A2,  typename A3,  typename A4,  typename A5,  typename A6,  typename A7 >
struct ConstMethodSignature< T, RV ( A0,  A1,  A2,  A3,  A4,  A5,  A6,  A7) > : SignatureBase< RV ( A0,  A1,  A2,  A3,  A4,  A5,  A6,  A7) >
{
    typedef T ClassType;
    typedef RV (T::*FunctionType)( A0,  A1,  A2,  A3,  A4,  A5,  A6,  A7) const;
};

template <typename T, typename RV,  typename A0,  typename A1,  typename A2,  typename A3,  typename A4,  typename A5,  typename A6,  typename A7 >
struct ConstMethodSignature< T, RV ( A0,  A1,  A2,  A3,  A4,  A5,  A6,  A7) const > :
    ConstMethodSignature< T, RV ( A0,  A1,  A2,  A3,  A4,  A5,  A6,  A7) >
{};


template <typename T, typename RV,  typename A0,  typename A1,  typename A2,  typename A3,  typename A4,  typename A5,  typename A6,  typename A7 >
struct ConstMethodSignature< T, RV (T::*)( A0,  A1,  A2,  A3,  A4,  A5,  A6,  A7) const > :
    ConstMethodSignature< T, RV ( A0,  A1,  A2,  A3,  A4,  A5,  A6,  A7) >
{};
template <typename RV,  typename A0,  typename A1,  typename A2,  typename A3,  typename A4,  typename A5,  typename A6,  typename A7,  typename A8 >
struct FunctionSignature< RV ( A0,  A1,  A2,  A3,  A4,  A5,  A6,  A7,  A8) > : SignatureBase< RV ( A0,  A1,  A2,  A3,  A4,  A5,  A6,  A7,  A8) >
{
    typedef RV (*FunctionType)( A0,  A1,  A2,  A3,  A4,  A5,  A6,  A7,  A8);
};

template <typename RV,  typename A0,  typename A1,  typename A2,  typename A3,  typename A4,  typename A5,  typename A6,  typename A7,  typename A8 >
struct FunctionSignature< RV (*)( A0,  A1,  A2,  A3,  A4,  A5,  A6,  A7,  A8) >
  : FunctionSignature< RV ( A0,  A1,  A2,  A3,  A4,  A5,  A6,  A7,  A8) >
{};


template <typename T, typename RV,  typename A0,  typename A1,  typename A2,  typename A3,  typename A4,  typename A5,  typename A6,  typename A7,  typename A8 >
struct MethodSignature< T, RV ( A0,  A1,  A2,  A3,  A4,  A5,  A6,  A7,  A8) > : SignatureBase< RV ( A0,  A1,  A2,  A3,  A4,  A5,  A6,  A7,  A8) >
{
    typedef T ClassType;
    typedef RV (T::*FunctionType)( A0,  A1,  A2,  A3,  A4,  A5,  A6,  A7,  A8);
};
template <typename T, typename RV,  typename A0,  typename A1,  typename A2,  typename A3,  typename A4,  typename A5,  typename A6,  typename A7,  typename A8 >
struct MethodSignature< T, RV (T::*)( A0,  A1,  A2,  A3,  A4,  A5,  A6,  A7,  A8) > :
    MethodSignature< T, RV ( A0,  A1,  A2,  A3,  A4,  A5,  A6,  A7,  A8) >
{};


template <typename T, typename RV,  typename A0,  typename A1,  typename A2,  typename A3,  typename A4,  typename A5,  typename A6,  typename A7,  typename A8 >
struct ConstMethodSignature< T, RV ( A0,  A1,  A2,  A3,  A4,  A5,  A6,  A7,  A8) > : SignatureBase< RV ( A0,  A1,  A2,  A3,  A4,  A5,  A6,  A7,  A8) >
{
    typedef T ClassType;
    typedef RV (T::*FunctionType)( A0,  A1,  A2,  A3,  A4,  A5,  A6,  A7,  A8) const;
};

template <typename T, typename RV,  typename A0,  typename A1,  typename A2,  typename A3,  typename A4,  typename A5,  typename A6,  typename A7,  typename A8 >
struct ConstMethodSignature< T, RV ( A0,  A1,  A2,  A3,  A4,  A5,  A6,  A7,  A8) const > :
    ConstMethodSignature< T, RV ( A0,  A1,  A2,  A3,  A4,  A5,  A6,  A7,  A8) >
{};


template <typename T, typename RV,  typename A0,  typename A1,  typename A2,  typename A3,  typename A4,  typename A5,  typename A6,  typename A7,  typename A8 >
struct ConstMethodSignature< T, RV (T::*)( A0,  A1,  A2,  A3,  A4,  A5,  A6,  A7,  A8) const > :
    ConstMethodSignature< T, RV ( A0,  A1,  A2,  A3,  A4,  A5,  A6,  A7,  A8) >
{};
template <typename RV,  typename A0,  typename A1,  typename A2,  typename A3,  typename A4,  typename A5,  typename A6,  typename A7,  typename A8,  typename A9 >
struct FunctionSignature< RV ( A0,  A1,  A2,  A3,  A4,  A5,  A6,  A7,  A8,  A9) > : SignatureBase< RV ( A0,  A1,  A2,  A3,  A4,  A5,  A6,  A7,  A8,  A9) >
{
    typedef RV (*FunctionType)( A0,  A1,  A2,  A3,  A4,  A5,  A6,  A7,  A8,  A9);
};

template <typename RV,  typename A0,  typename A1,  typename A2,  typename A3,  typename A4,  typename A5,  typename A6,  typename A7,  typename A8,  typename A9 >
struct FunctionSignature< RV (*)( A0,  A1,  A2,  A3,  A4,  A5,  A6,  A7,  A8,  A9) >
  : FunctionSignature< RV ( A0,  A1,  A2,  A3,  A4,  A5,  A6,  A7,  A8,  A9) >
{};


template <typename T, typename RV,  typename A0,  typename A1,  typename A2,  typename A3,  typename A4,  typename A5,  typename A6,  typename A7,  typename A8,  typename A9 >
struct MethodSignature< T, RV ( A0,  A1,  A2,  A3,  A4,  A5,  A6,  A7,  A8,  A9) > : SignatureBase< RV ( A0,  A1,  A2,  A3,  A4,  A5,  A6,  A7,  A8,  A9) >
{
    typedef T ClassType;
    typedef RV (T::*FunctionType)( A0,  A1,  A2,  A3,  A4,  A5,  A6,  A7,  A8,  A9);
};
template <typename T, typename RV,  typename A0,  typename A1,  typename A2,  typename A3,  typename A4,  typename A5,  typename A6,  typename A7,  typename A8,  typename A9 >
struct MethodSignature< T, RV (T::*)( A0,  A1,  A2,  A3,  A4,  A5,  A6,  A7,  A8,  A9) > :
    MethodSignature< T, RV ( A0,  A1,  A2,  A3,  A4,  A5,  A6,  A7,  A8,  A9) >
{};


template <typename T, typename RV,  typename A0,  typename A1,  typename A2,  typename A3,  typename A4,  typename A5,  typename A6,  typename A7,  typename A8,  typename A9 >
struct ConstMethodSignature< T, RV ( A0,  A1,  A2,  A3,  A4,  A5,  A6,  A7,  A8,  A9) > : SignatureBase< RV ( A0,  A1,  A2,  A3,  A4,  A5,  A6,  A7,  A8,  A9) >
{
    typedef T ClassType;
    typedef RV (T::*FunctionType)( A0,  A1,  A2,  A3,  A4,  A5,  A6,  A7,  A8,  A9) const;
};

template <typename T, typename RV,  typename A0,  typename A1,  typename A2,  typename A3,  typename A4,  typename A5,  typename A6,  typename A7,  typename A8,  typename A9 >
struct ConstMethodSignature< T, RV ( A0,  A1,  A2,  A3,  A4,  A5,  A6,  A7,  A8,  A9) const > :
    ConstMethodSignature< T, RV ( A0,  A1,  A2,  A3,  A4,  A5,  A6,  A7,  A8,  A9) >
{};


template <typename T, typename RV,  typename A0,  typename A1,  typename A2,  typename A3,  typename A4,  typename A5,  typename A6,  typename A7,  typename A8,  typename A9 >
struct ConstMethodSignature< T, RV (T::*)( A0,  A1,  A2,  A3,  A4,  A5,  A6,  A7,  A8,  A9) const > :
    ConstMethodSignature< T, RV ( A0,  A1,  A2,  A3,  A4,  A5,  A6,  A7,  A8,  A9) >
{};
#endif // if !defined(DOXYGEN)
