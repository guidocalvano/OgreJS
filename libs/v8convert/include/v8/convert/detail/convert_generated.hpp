/* AUTO-GENERATED CODE! EDIT AT YOUR OWN RISK! */
#if !defined(DOXYGEN)
namespace Detail {
template <>
struct CtorForwarderProxy<1> // todo: subclass Signature<Sig>
{
    enum { Arity = 1 };
    template <typename Sig>
    static typename Signature<Sig>::ReturnType Call( ::v8::Arguments const & argv )
    {
        if( argv.Length() < Arity )
        {
            throw std::range_error("CtorForwarder<T,1>::Ctor() expects at least 1 JS arguments!");
        }
        else
        {
            typedef typename Signature<Sig>::ReturnType Type_;
            typedef typename TypeInfo<Type_>::Type Type;
            typedef typename sl::At< 0, Signature<Sig> >::Type A0;
		
             typedef ArgCaster<A0> AC0;
		
             AC0 ac0; A0 arg0(ac0.ToNative(argv[0]));
		
            return new Type(  arg0 );
        }
    }
};
}
namespace Detail {
template <>
struct CtorForwarderProxy<2> // todo: subclass Signature<Sig>
{
    enum { Arity = 2 };
    template <typename Sig>
    static typename Signature<Sig>::ReturnType Call( ::v8::Arguments const & argv )
    {
        if( argv.Length() < Arity )
        {
            throw std::range_error("CtorForwarder<T,2>::Ctor() expects at least 2 JS arguments!");
        }
        else
        {
            typedef typename Signature<Sig>::ReturnType Type_;
            typedef typename TypeInfo<Type_>::Type Type;
            typedef typename sl::At< 0, Signature<Sig> >::Type A0;
		typedef typename sl::At< 1, Signature<Sig> >::Type A1;
		
             typedef ArgCaster<A0> AC0;
		 typedef ArgCaster<A1> AC1;
		
             AC0 ac0; A0 arg0(ac0.ToNative(argv[0]));
		 AC1 ac1; A1 arg1(ac1.ToNative(argv[1]));
		
            return new Type(  arg0,  arg1 );
        }
    }
};
}
namespace Detail {
template <>
struct CtorForwarderProxy<3> // todo: subclass Signature<Sig>
{
    enum { Arity = 3 };
    template <typename Sig>
    static typename Signature<Sig>::ReturnType Call( ::v8::Arguments const & argv )
    {
        if( argv.Length() < Arity )
        {
            throw std::range_error("CtorForwarder<T,3>::Ctor() expects at least 3 JS arguments!");
        }
        else
        {
            typedef typename Signature<Sig>::ReturnType Type_;
            typedef typename TypeInfo<Type_>::Type Type;
            typedef typename sl::At< 0, Signature<Sig> >::Type A0;
		typedef typename sl::At< 1, Signature<Sig> >::Type A1;
		typedef typename sl::At< 2, Signature<Sig> >::Type A2;
		
             typedef ArgCaster<A0> AC0;
		 typedef ArgCaster<A1> AC1;
		 typedef ArgCaster<A2> AC2;
		
             AC0 ac0; A0 arg0(ac0.ToNative(argv[0]));
		 AC1 ac1; A1 arg1(ac1.ToNative(argv[1]));
		 AC2 ac2; A2 arg2(ac2.ToNative(argv[2]));
		
            return new Type(  arg0,  arg1,  arg2 );
        }
    }
};
}
namespace Detail {
template <>
struct CtorForwarderProxy<4> // todo: subclass Signature<Sig>
{
    enum { Arity = 4 };
    template <typename Sig>
    static typename Signature<Sig>::ReturnType Call( ::v8::Arguments const & argv )
    {
        if( argv.Length() < Arity )
        {
            throw std::range_error("CtorForwarder<T,4>::Ctor() expects at least 4 JS arguments!");
        }
        else
        {
            typedef typename Signature<Sig>::ReturnType Type_;
            typedef typename TypeInfo<Type_>::Type Type;
            typedef typename sl::At< 0, Signature<Sig> >::Type A0;
		typedef typename sl::At< 1, Signature<Sig> >::Type A1;
		typedef typename sl::At< 2, Signature<Sig> >::Type A2;
		typedef typename sl::At< 3, Signature<Sig> >::Type A3;
		
             typedef ArgCaster<A0> AC0;
		 typedef ArgCaster<A1> AC1;
		 typedef ArgCaster<A2> AC2;
		 typedef ArgCaster<A3> AC3;
		
             AC0 ac0; A0 arg0(ac0.ToNative(argv[0]));
		 AC1 ac1; A1 arg1(ac1.ToNative(argv[1]));
		 AC2 ac2; A2 arg2(ac2.ToNative(argv[2]));
		 AC3 ac3; A3 arg3(ac3.ToNative(argv[3]));
		
            return new Type(  arg0,  arg1,  arg2,  arg3 );
        }
    }
};
}
namespace Detail {
template <>
struct CtorForwarderProxy<5> // todo: subclass Signature<Sig>
{
    enum { Arity = 5 };
    template <typename Sig>
    static typename Signature<Sig>::ReturnType Call( ::v8::Arguments const & argv )
    {
        if( argv.Length() < Arity )
        {
            throw std::range_error("CtorForwarder<T,5>::Ctor() expects at least 5 JS arguments!");
        }
        else
        {
            typedef typename Signature<Sig>::ReturnType Type_;
            typedef typename TypeInfo<Type_>::Type Type;
            typedef typename sl::At< 0, Signature<Sig> >::Type A0;
		typedef typename sl::At< 1, Signature<Sig> >::Type A1;
		typedef typename sl::At< 2, Signature<Sig> >::Type A2;
		typedef typename sl::At< 3, Signature<Sig> >::Type A3;
		typedef typename sl::At< 4, Signature<Sig> >::Type A4;
		
             typedef ArgCaster<A0> AC0;
		 typedef ArgCaster<A1> AC1;
		 typedef ArgCaster<A2> AC2;
		 typedef ArgCaster<A3> AC3;
		 typedef ArgCaster<A4> AC4;
		
             AC0 ac0; A0 arg0(ac0.ToNative(argv[0]));
		 AC1 ac1; A1 arg1(ac1.ToNative(argv[1]));
		 AC2 ac2; A2 arg2(ac2.ToNative(argv[2]));
		 AC3 ac3; A3 arg3(ac3.ToNative(argv[3]));
		 AC4 ac4; A4 arg4(ac4.ToNative(argv[4]));
		
            return new Type(  arg0,  arg1,  arg2,  arg3,  arg4 );
        }
    }
};
}
namespace Detail {
template <>
struct CtorForwarderProxy<6> // todo: subclass Signature<Sig>
{
    enum { Arity = 6 };
    template <typename Sig>
    static typename Signature<Sig>::ReturnType Call( ::v8::Arguments const & argv )
    {
        if( argv.Length() < Arity )
        {
            throw std::range_error("CtorForwarder<T,6>::Ctor() expects at least 6 JS arguments!");
        }
        else
        {
            typedef typename Signature<Sig>::ReturnType Type_;
            typedef typename TypeInfo<Type_>::Type Type;
            typedef typename sl::At< 0, Signature<Sig> >::Type A0;
		typedef typename sl::At< 1, Signature<Sig> >::Type A1;
		typedef typename sl::At< 2, Signature<Sig> >::Type A2;
		typedef typename sl::At< 3, Signature<Sig> >::Type A3;
		typedef typename sl::At< 4, Signature<Sig> >::Type A4;
		typedef typename sl::At< 5, Signature<Sig> >::Type A5;
		
             typedef ArgCaster<A0> AC0;
		 typedef ArgCaster<A1> AC1;
		 typedef ArgCaster<A2> AC2;
		 typedef ArgCaster<A3> AC3;
		 typedef ArgCaster<A4> AC4;
		 typedef ArgCaster<A5> AC5;
		
             AC0 ac0; A0 arg0(ac0.ToNative(argv[0]));
		 AC1 ac1; A1 arg1(ac1.ToNative(argv[1]));
		 AC2 ac2; A2 arg2(ac2.ToNative(argv[2]));
		 AC3 ac3; A3 arg3(ac3.ToNative(argv[3]));
		 AC4 ac4; A4 arg4(ac4.ToNative(argv[4]));
		 AC5 ac5; A5 arg5(ac5.ToNative(argv[5]));
		
            return new Type(  arg0,  arg1,  arg2,  arg3,  arg4,  arg5 );
        }
    }
};
}
namespace Detail {
template <>
struct CtorForwarderProxy<7> // todo: subclass Signature<Sig>
{
    enum { Arity = 7 };
    template <typename Sig>
    static typename Signature<Sig>::ReturnType Call( ::v8::Arguments const & argv )
    {
        if( argv.Length() < Arity )
        {
            throw std::range_error("CtorForwarder<T,7>::Ctor() expects at least 7 JS arguments!");
        }
        else
        {
            typedef typename Signature<Sig>::ReturnType Type_;
            typedef typename TypeInfo<Type_>::Type Type;
            typedef typename sl::At< 0, Signature<Sig> >::Type A0;
		typedef typename sl::At< 1, Signature<Sig> >::Type A1;
		typedef typename sl::At< 2, Signature<Sig> >::Type A2;
		typedef typename sl::At< 3, Signature<Sig> >::Type A3;
		typedef typename sl::At< 4, Signature<Sig> >::Type A4;
		typedef typename sl::At< 5, Signature<Sig> >::Type A5;
		typedef typename sl::At< 6, Signature<Sig> >::Type A6;
		
             typedef ArgCaster<A0> AC0;
		 typedef ArgCaster<A1> AC1;
		 typedef ArgCaster<A2> AC2;
		 typedef ArgCaster<A3> AC3;
		 typedef ArgCaster<A4> AC4;
		 typedef ArgCaster<A5> AC5;
		 typedef ArgCaster<A6> AC6;
		
             AC0 ac0; A0 arg0(ac0.ToNative(argv[0]));
		 AC1 ac1; A1 arg1(ac1.ToNative(argv[1]));
		 AC2 ac2; A2 arg2(ac2.ToNative(argv[2]));
		 AC3 ac3; A3 arg3(ac3.ToNative(argv[3]));
		 AC4 ac4; A4 arg4(ac4.ToNative(argv[4]));
		 AC5 ac5; A5 arg5(ac5.ToNative(argv[5]));
		 AC6 ac6; A6 arg6(ac6.ToNative(argv[6]));
		
            return new Type(  arg0,  arg1,  arg2,  arg3,  arg4,  arg5,  arg6 );
        }
    }
};
}
namespace Detail {
template <>
struct CtorForwarderProxy<8> // todo: subclass Signature<Sig>
{
    enum { Arity = 8 };
    template <typename Sig>
    static typename Signature<Sig>::ReturnType Call( ::v8::Arguments const & argv )
    {
        if( argv.Length() < Arity )
        {
            throw std::range_error("CtorForwarder<T,8>::Ctor() expects at least 8 JS arguments!");
        }
        else
        {
            typedef typename Signature<Sig>::ReturnType Type_;
            typedef typename TypeInfo<Type_>::Type Type;
            typedef typename sl::At< 0, Signature<Sig> >::Type A0;
		typedef typename sl::At< 1, Signature<Sig> >::Type A1;
		typedef typename sl::At< 2, Signature<Sig> >::Type A2;
		typedef typename sl::At< 3, Signature<Sig> >::Type A3;
		typedef typename sl::At< 4, Signature<Sig> >::Type A4;
		typedef typename sl::At< 5, Signature<Sig> >::Type A5;
		typedef typename sl::At< 6, Signature<Sig> >::Type A6;
		typedef typename sl::At< 7, Signature<Sig> >::Type A7;
		
             typedef ArgCaster<A0> AC0;
		 typedef ArgCaster<A1> AC1;
		 typedef ArgCaster<A2> AC2;
		 typedef ArgCaster<A3> AC3;
		 typedef ArgCaster<A4> AC4;
		 typedef ArgCaster<A5> AC5;
		 typedef ArgCaster<A6> AC6;
		 typedef ArgCaster<A7> AC7;
		
             AC0 ac0; A0 arg0(ac0.ToNative(argv[0]));
		 AC1 ac1; A1 arg1(ac1.ToNative(argv[1]));
		 AC2 ac2; A2 arg2(ac2.ToNative(argv[2]));
		 AC3 ac3; A3 arg3(ac3.ToNative(argv[3]));
		 AC4 ac4; A4 arg4(ac4.ToNative(argv[4]));
		 AC5 ac5; A5 arg5(ac5.ToNative(argv[5]));
		 AC6 ac6; A6 arg6(ac6.ToNative(argv[6]));
		 AC7 ac7; A7 arg7(ac7.ToNative(argv[7]));
		
            return new Type(  arg0,  arg1,  arg2,  arg3,  arg4,  arg5,  arg6,  arg7 );
        }
    }
};
}
namespace Detail {
template <>
struct CtorForwarderProxy<9> // todo: subclass Signature<Sig>
{
    enum { Arity = 9 };
    template <typename Sig>
    static typename Signature<Sig>::ReturnType Call( ::v8::Arguments const & argv )
    {
        if( argv.Length() < Arity )
        {
            throw std::range_error("CtorForwarder<T,9>::Ctor() expects at least 9 JS arguments!");
        }
        else
        {
            typedef typename Signature<Sig>::ReturnType Type_;
            typedef typename TypeInfo<Type_>::Type Type;
            typedef typename sl::At< 0, Signature<Sig> >::Type A0;
		typedef typename sl::At< 1, Signature<Sig> >::Type A1;
		typedef typename sl::At< 2, Signature<Sig> >::Type A2;
		typedef typename sl::At< 3, Signature<Sig> >::Type A3;
		typedef typename sl::At< 4, Signature<Sig> >::Type A4;
		typedef typename sl::At< 5, Signature<Sig> >::Type A5;
		typedef typename sl::At< 6, Signature<Sig> >::Type A6;
		typedef typename sl::At< 7, Signature<Sig> >::Type A7;
		typedef typename sl::At< 8, Signature<Sig> >::Type A8;
		
             typedef ArgCaster<A0> AC0;
		 typedef ArgCaster<A1> AC1;
		 typedef ArgCaster<A2> AC2;
		 typedef ArgCaster<A3> AC3;
		 typedef ArgCaster<A4> AC4;
		 typedef ArgCaster<A5> AC5;
		 typedef ArgCaster<A6> AC6;
		 typedef ArgCaster<A7> AC7;
		 typedef ArgCaster<A8> AC8;
		
             AC0 ac0; A0 arg0(ac0.ToNative(argv[0]));
		 AC1 ac1; A1 arg1(ac1.ToNative(argv[1]));
		 AC2 ac2; A2 arg2(ac2.ToNative(argv[2]));
		 AC3 ac3; A3 arg3(ac3.ToNative(argv[3]));
		 AC4 ac4; A4 arg4(ac4.ToNative(argv[4]));
		 AC5 ac5; A5 arg5(ac5.ToNative(argv[5]));
		 AC6 ac6; A6 arg6(ac6.ToNative(argv[6]));
		 AC7 ac7; A7 arg7(ac7.ToNative(argv[7]));
		 AC8 ac8; A8 arg8(ac8.ToNative(argv[8]));
		
            return new Type(  arg0,  arg1,  arg2,  arg3,  arg4,  arg5,  arg6,  arg7,  arg8 );
        }
    }
};
}
namespace Detail {
template <>
struct CtorForwarderProxy<10> // todo: subclass Signature<Sig>
{
    enum { Arity = 10 };
    template <typename Sig>
    static typename Signature<Sig>::ReturnType Call( ::v8::Arguments const & argv )
    {
        if( argv.Length() < Arity )
        {
            throw std::range_error("CtorForwarder<T,10>::Ctor() expects at least 10 JS arguments!");
        }
        else
        {
            typedef typename Signature<Sig>::ReturnType Type_;
            typedef typename TypeInfo<Type_>::Type Type;
            typedef typename sl::At< 0, Signature<Sig> >::Type A0;
		typedef typename sl::At< 1, Signature<Sig> >::Type A1;
		typedef typename sl::At< 2, Signature<Sig> >::Type A2;
		typedef typename sl::At< 3, Signature<Sig> >::Type A3;
		typedef typename sl::At< 4, Signature<Sig> >::Type A4;
		typedef typename sl::At< 5, Signature<Sig> >::Type A5;
		typedef typename sl::At< 6, Signature<Sig> >::Type A6;
		typedef typename sl::At< 7, Signature<Sig> >::Type A7;
		typedef typename sl::At< 8, Signature<Sig> >::Type A8;
		typedef typename sl::At< 9, Signature<Sig> >::Type A9;
		
             typedef ArgCaster<A0> AC0;
		 typedef ArgCaster<A1> AC1;
		 typedef ArgCaster<A2> AC2;
		 typedef ArgCaster<A3> AC3;
		 typedef ArgCaster<A4> AC4;
		 typedef ArgCaster<A5> AC5;
		 typedef ArgCaster<A6> AC6;
		 typedef ArgCaster<A7> AC7;
		 typedef ArgCaster<A8> AC8;
		 typedef ArgCaster<A9> AC9;
		
             AC0 ac0; A0 arg0(ac0.ToNative(argv[0]));
		 AC1 ac1; A1 arg1(ac1.ToNative(argv[1]));
		 AC2 ac2; A2 arg2(ac2.ToNative(argv[2]));
		 AC3 ac3; A3 arg3(ac3.ToNative(argv[3]));
		 AC4 ac4; A4 arg4(ac4.ToNative(argv[4]));
		 AC5 ac5; A5 arg5(ac5.ToNative(argv[5]));
		 AC6 ac6; A6 arg6(ac6.ToNative(argv[6]));
		 AC7 ac7; A7 arg7(ac7.ToNative(argv[7]));
		 AC8 ac8; A8 arg8(ac8.ToNative(argv[8]));
		 AC9 ac9; A9 arg9(ac9.ToNative(argv[9]));
		
            return new Type(  arg0,  arg1,  arg2,  arg3,  arg4,  arg5,  arg6,  arg7,  arg8,  arg9 );
        }
    }
};
}
#endif // if !defined(DOXYGEN)
