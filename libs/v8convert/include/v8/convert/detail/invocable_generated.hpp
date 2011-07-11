/* AUTO-GENERATED CODE! EDIT AT YOUR OWN RISK! */
#if !defined(DOXYGEN)
namespace Detail {
    template <typename Sig, bool UnlockV8>
    struct ArgsToFunctionForwarder<1,Sig,UnlockV8> : FunctionSignature<Sig>
    {
        typedef FunctionSignature<Sig> SignatureType;
        typedef typename SignatureType::FunctionType FunctionType;
        typedef typename SignatureType::ReturnType ReturnType;
        static ReturnType CallNative( FunctionType func, v8::Arguments const & argv )
        {
            typedef char AssertArity[ sl::Arity<SignatureType>::Value == 1 ? 1 : -1];
            typedef typename sl::At< 0, Signature<Sig> >::Type A0;
		
             typedef ArgCaster<A0> AC0;
		
             AC0 ac0; A0 arg0(ac0.ToNative(argv[0]));
		
            typedef typename SignatureType::ReturnType RV;
            V8Unlocker<UnlockV8> const unlocker();
            return (ReturnType)(*func)(  arg0 );
        }
        static v8::Handle<v8::Value> Call( FunctionType func, v8::Arguments const & argv )
        {
            return CastToJS( CallNative( func, argv ) );
        }
    };

    template <typename Sig, bool UnlockV8>
    struct ArgsToFunctionForwarderVoid<1,Sig,UnlockV8> : FunctionSignature<Sig>
    {
        typedef FunctionSignature<Sig> SignatureType;
        typedef typename SignatureType::FunctionType FunctionType;
        typedef typename SignatureType::ReturnType ReturnType;
        static ReturnType CallNative( FunctionType func, v8::Arguments const & argv )
        {
            typedef char AssertArity[ sl::Arity<SignatureType>::Value == 1 ? 1 : -1];
            typedef typename sl::At< 0, Signature<Sig> >::Type A0;
		
             typedef ArgCaster<A0> AC0;
		
             AC0 ac0; A0 arg0(ac0.ToNative(argv[0]));
		
            V8Unlocker<UnlockV8> const unlocker();
            return (ReturnType)(*func)(  arg0 );
        }
        static v8::Handle<v8::Value> Call( FunctionType func, v8::Arguments const & argv )
        {
            CallNative( func, argv );
            return v8::Undefined();
        }
    };
}
namespace Detail {
    template <typename T, typename Sig, bool UnlockV8>
    struct ArgsToMethodForwarder<T, 1,Sig, UnlockV8> : MethodSignature<T,Sig>
    {
        typedef MethodSignature<T,Sig> SignatureType;
        typedef typename SignatureType::FunctionType FunctionType;
        typedef typename SignatureType::ReturnType ReturnType;
        static ReturnType CallNative( T  & self, FunctionType func, Arguments const & argv )
        {
            typedef typename sl::At< 0, Signature<Sig> >::Type A0;
		
             typedef ArgCaster<A0> AC0;
		
             AC0 ac0; A0 arg0(ac0.ToNative(argv[0]));
		
            typedef typename SignatureType::ReturnType RV;
            V8Unlocker<UnlockV8> const unlocker();
            return (ReturnType)(self.*func)(  arg0 );
        }
        static v8::Handle<v8::Value> Call( T  & self, FunctionType func, Arguments const & argv )
        {
            try { return CastToJS( CallNative( self, func, argv ) ); }
            HANDLE_PROPAGATE_EXCEPTION;
        }
        static ReturnType CallNative( FunctionType func, v8::Arguments const & argv )
        {
            T  * self = CastFromJS<T>(argv.This());
            if( ! self ) throw MissingThisExceptionT<T>();
            return (ReturnType)CallNative(*self, func, argv);
        }
        static v8::Handle<v8::Value> Call( FunctionType func, v8::Arguments const & argv )
        {
            try { return CastToJS( CallNative(func, argv) ); }
            HANDLE_PROPAGATE_EXCEPTION;
        }
    };

    template <typename T, typename Sig, bool UnlockV8>
    struct ArgsToMethodForwarderVoid<T, 1,Sig, UnlockV8> : MethodSignature<T,Sig>
    {
        typedef MethodSignature<T,Sig> SignatureType;
        typedef typename SignatureType::FunctionType FunctionType;
        typedef typename SignatureType::ReturnType ReturnType;
        static ReturnType CallNative( T  & self, FunctionType func, Arguments const & argv )
        {
            typedef typename sl::At< 0, Signature<Sig> >::Type A0;
		
             typedef ArgCaster<A0> AC0;
		
             AC0 ac0; A0 arg0(ac0.ToNative(argv[0]));
		
            V8Unlocker<UnlockV8> const unlocker();
            return (ReturnType)(self.*func)(  arg0 );
        }
        static v8::Handle<v8::Value> Call( T  & self, FunctionType func, Arguments const & argv )
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
            T  * self = CastFromJS<T>(argv.This());
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
}
namespace Detail {
    template <typename T, typename Sig, bool UnlockV8>
    struct ArgsToConstMethodForwarder<T, 1,Sig, UnlockV8> : ConstMethodSignature<T,Sig>
    {
        typedef ConstMethodSignature<T,Sig> SignatureType;
        typedef typename SignatureType::FunctionType FunctionType;
        typedef typename SignatureType::ReturnType ReturnType;
        static ReturnType CallNative( T const & self, FunctionType func, Arguments const & argv )
        {
            typedef typename sl::At< 0, Signature<Sig> >::Type A0;
		
             typedef ArgCaster<A0> AC0;
		
             AC0 ac0; A0 arg0(ac0.ToNative(argv[0]));
		
            typedef typename SignatureType::ReturnType RV;
            V8Unlocker<UnlockV8> const unlocker();
            return (ReturnType)(self.*func)(  arg0 );
        }
        static v8::Handle<v8::Value> Call( T const & self, FunctionType func, Arguments const & argv )
        {
            try { return CastToJS( CallNative( self, func, argv ) ); }
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
            try { return CastToJS( CallNative(func, argv) ); }
            HANDLE_PROPAGATE_EXCEPTION;
        }
    };

    template <typename T, typename Sig, bool UnlockV8>
    struct ArgsToConstMethodForwarderVoid<T, 1,Sig, UnlockV8> : ConstMethodSignature<T,Sig>
    {
        typedef ConstMethodSignature<T,Sig> SignatureType;
        typedef typename SignatureType::FunctionType FunctionType;
        typedef typename SignatureType::ReturnType ReturnType;
        static ReturnType CallNative( T const & self, FunctionType func, Arguments const & argv )
        {
            typedef typename sl::At< 0, Signature<Sig> >::Type A0;
		
             typedef ArgCaster<A0> AC0;
		
             AC0 ac0; A0 arg0(ac0.ToNative(argv[0]));
		
            V8Unlocker<UnlockV8> const unlocker();
            return (ReturnType)(self.*func)(  arg0 );
        }
        static v8::Handle<v8::Value> Call( T const & self, FunctionType func, Arguments const & argv )
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
    };
}
namespace Detail {
    template <typename Sig, bool UnlockV8>
    struct ArgsToFunctionForwarder<2,Sig,UnlockV8> : FunctionSignature<Sig>
    {
        typedef FunctionSignature<Sig> SignatureType;
        typedef typename SignatureType::FunctionType FunctionType;
        typedef typename SignatureType::ReturnType ReturnType;
        static ReturnType CallNative( FunctionType func, v8::Arguments const & argv )
        {
            typedef char AssertArity[ sl::Arity<SignatureType>::Value == 2 ? 1 : -1];
            typedef typename sl::At< 0, Signature<Sig> >::Type A0;
		typedef typename sl::At< 1, Signature<Sig> >::Type A1;
		
             typedef ArgCaster<A0> AC0;
		 typedef ArgCaster<A1> AC1;
		
             AC0 ac0; A0 arg0(ac0.ToNative(argv[0]));
		 AC1 ac1; A1 arg1(ac1.ToNative(argv[1]));
		
            typedef typename SignatureType::ReturnType RV;
            V8Unlocker<UnlockV8> const unlocker();
            return (ReturnType)(*func)(  arg0,  arg1 );
        }
        static v8::Handle<v8::Value> Call( FunctionType func, v8::Arguments const & argv )
        {
            return CastToJS( CallNative( func, argv ) );
        }
    };

    template <typename Sig, bool UnlockV8>
    struct ArgsToFunctionForwarderVoid<2,Sig,UnlockV8> : FunctionSignature<Sig>
    {
        typedef FunctionSignature<Sig> SignatureType;
        typedef typename SignatureType::FunctionType FunctionType;
        typedef typename SignatureType::ReturnType ReturnType;
        static ReturnType CallNative( FunctionType func, v8::Arguments const & argv )
        {
            typedef char AssertArity[ sl::Arity<SignatureType>::Value == 2 ? 1 : -1];
            typedef typename sl::At< 0, Signature<Sig> >::Type A0;
		typedef typename sl::At< 1, Signature<Sig> >::Type A1;
		
             typedef ArgCaster<A0> AC0;
		 typedef ArgCaster<A1> AC1;
		
             AC0 ac0; A0 arg0(ac0.ToNative(argv[0]));
		 AC1 ac1; A1 arg1(ac1.ToNative(argv[1]));
		
            V8Unlocker<UnlockV8> const unlocker();
            return (ReturnType)(*func)(  arg0,  arg1 );
        }
        static v8::Handle<v8::Value> Call( FunctionType func, v8::Arguments const & argv )
        {
            CallNative( func, argv );
            return v8::Undefined();
        }
    };
}
namespace Detail {
    template <typename T, typename Sig, bool UnlockV8>
    struct ArgsToMethodForwarder<T, 2,Sig, UnlockV8> : MethodSignature<T,Sig>
    {
        typedef MethodSignature<T,Sig> SignatureType;
        typedef typename SignatureType::FunctionType FunctionType;
        typedef typename SignatureType::ReturnType ReturnType;
        static ReturnType CallNative( T  & self, FunctionType func, Arguments const & argv )
        {
            typedef typename sl::At< 0, Signature<Sig> >::Type A0;
		typedef typename sl::At< 1, Signature<Sig> >::Type A1;
		
             typedef ArgCaster<A0> AC0;
		 typedef ArgCaster<A1> AC1;
		
             AC0 ac0; A0 arg0(ac0.ToNative(argv[0]));
		 AC1 ac1; A1 arg1(ac1.ToNative(argv[1]));
		
            typedef typename SignatureType::ReturnType RV;
            V8Unlocker<UnlockV8> const unlocker();
            return (ReturnType)(self.*func)(  arg0,  arg1 );
        }
        static v8::Handle<v8::Value> Call( T  & self, FunctionType func, Arguments const & argv )
        {
            try { return CastToJS( CallNative( self, func, argv ) ); }
            HANDLE_PROPAGATE_EXCEPTION;
        }
        static ReturnType CallNative( FunctionType func, v8::Arguments const & argv )
        {
            T  * self = CastFromJS<T>(argv.This());
            if( ! self ) throw MissingThisExceptionT<T>();
            return (ReturnType)CallNative(*self, func, argv);
        }
        static v8::Handle<v8::Value> Call( FunctionType func, v8::Arguments const & argv )
        {
            try { return CastToJS( CallNative(func, argv) ); }
            HANDLE_PROPAGATE_EXCEPTION;
        }
    };

    template <typename T, typename Sig, bool UnlockV8>
    struct ArgsToMethodForwarderVoid<T, 2,Sig, UnlockV8> : MethodSignature<T,Sig>
    {
        typedef MethodSignature<T,Sig> SignatureType;
        typedef typename SignatureType::FunctionType FunctionType;
        typedef typename SignatureType::ReturnType ReturnType;
        static ReturnType CallNative( T  & self, FunctionType func, Arguments const & argv )
        {
            typedef typename sl::At< 0, Signature<Sig> >::Type A0;
		typedef typename sl::At< 1, Signature<Sig> >::Type A1;
		
             typedef ArgCaster<A0> AC0;
		 typedef ArgCaster<A1> AC1;
		
             AC0 ac0; A0 arg0(ac0.ToNative(argv[0]));
		 AC1 ac1; A1 arg1(ac1.ToNative(argv[1]));
		
            V8Unlocker<UnlockV8> const unlocker();
            return (ReturnType)(self.*func)(  arg0,  arg1 );
        }
        static v8::Handle<v8::Value> Call( T  & self, FunctionType func, Arguments const & argv )
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
            T  * self = CastFromJS<T>(argv.This());
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
}
namespace Detail {
    template <typename T, typename Sig, bool UnlockV8>
    struct ArgsToConstMethodForwarder<T, 2,Sig, UnlockV8> : ConstMethodSignature<T,Sig>
    {
        typedef ConstMethodSignature<T,Sig> SignatureType;
        typedef typename SignatureType::FunctionType FunctionType;
        typedef typename SignatureType::ReturnType ReturnType;
        static ReturnType CallNative( T const & self, FunctionType func, Arguments const & argv )
        {
            typedef typename sl::At< 0, Signature<Sig> >::Type A0;
		typedef typename sl::At< 1, Signature<Sig> >::Type A1;
		
             typedef ArgCaster<A0> AC0;
		 typedef ArgCaster<A1> AC1;
		
             AC0 ac0; A0 arg0(ac0.ToNative(argv[0]));
		 AC1 ac1; A1 arg1(ac1.ToNative(argv[1]));
		
            typedef typename SignatureType::ReturnType RV;
            V8Unlocker<UnlockV8> const unlocker();
            return (ReturnType)(self.*func)(  arg0,  arg1 );
        }
        static v8::Handle<v8::Value> Call( T const & self, FunctionType func, Arguments const & argv )
        {
            try { return CastToJS( CallNative( self, func, argv ) ); }
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
            try { return CastToJS( CallNative(func, argv) ); }
            HANDLE_PROPAGATE_EXCEPTION;
        }
    };

    template <typename T, typename Sig, bool UnlockV8>
    struct ArgsToConstMethodForwarderVoid<T, 2,Sig, UnlockV8> : ConstMethodSignature<T,Sig>
    {
        typedef ConstMethodSignature<T,Sig> SignatureType;
        typedef typename SignatureType::FunctionType FunctionType;
        typedef typename SignatureType::ReturnType ReturnType;
        static ReturnType CallNative( T const & self, FunctionType func, Arguments const & argv )
        {
            typedef typename sl::At< 0, Signature<Sig> >::Type A0;
		typedef typename sl::At< 1, Signature<Sig> >::Type A1;
		
             typedef ArgCaster<A0> AC0;
		 typedef ArgCaster<A1> AC1;
		
             AC0 ac0; A0 arg0(ac0.ToNative(argv[0]));
		 AC1 ac1; A1 arg1(ac1.ToNative(argv[1]));
		
            V8Unlocker<UnlockV8> const unlocker();
            return (ReturnType)(self.*func)(  arg0,  arg1 );
        }
        static v8::Handle<v8::Value> Call( T const & self, FunctionType func, Arguments const & argv )
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
    };
}
namespace Detail {
    template <typename Sig, bool UnlockV8>
    struct ArgsToFunctionForwarder<3,Sig,UnlockV8> : FunctionSignature<Sig>
    {
        typedef FunctionSignature<Sig> SignatureType;
        typedef typename SignatureType::FunctionType FunctionType;
        typedef typename SignatureType::ReturnType ReturnType;
        static ReturnType CallNative( FunctionType func, v8::Arguments const & argv )
        {
            typedef char AssertArity[ sl::Arity<SignatureType>::Value == 3 ? 1 : -1];
            typedef typename sl::At< 0, Signature<Sig> >::Type A0;
		typedef typename sl::At< 1, Signature<Sig> >::Type A1;
		typedef typename sl::At< 2, Signature<Sig> >::Type A2;
		
             typedef ArgCaster<A0> AC0;
		 typedef ArgCaster<A1> AC1;
		 typedef ArgCaster<A2> AC2;
		
             AC0 ac0; A0 arg0(ac0.ToNative(argv[0]));
		 AC1 ac1; A1 arg1(ac1.ToNative(argv[1]));
		 AC2 ac2; A2 arg2(ac2.ToNative(argv[2]));
		
            typedef typename SignatureType::ReturnType RV;
            V8Unlocker<UnlockV8> const unlocker();
            return (ReturnType)(*func)(  arg0,  arg1,  arg2 );
        }
        static v8::Handle<v8::Value> Call( FunctionType func, v8::Arguments const & argv )
        {
            return CastToJS( CallNative( func, argv ) );
        }
    };

    template <typename Sig, bool UnlockV8>
    struct ArgsToFunctionForwarderVoid<3,Sig,UnlockV8> : FunctionSignature<Sig>
    {
        typedef FunctionSignature<Sig> SignatureType;
        typedef typename SignatureType::FunctionType FunctionType;
        typedef typename SignatureType::ReturnType ReturnType;
        static ReturnType CallNative( FunctionType func, v8::Arguments const & argv )
        {
            typedef char AssertArity[ sl::Arity<SignatureType>::Value == 3 ? 1 : -1];
            typedef typename sl::At< 0, Signature<Sig> >::Type A0;
		typedef typename sl::At< 1, Signature<Sig> >::Type A1;
		typedef typename sl::At< 2, Signature<Sig> >::Type A2;
		
             typedef ArgCaster<A0> AC0;
		 typedef ArgCaster<A1> AC1;
		 typedef ArgCaster<A2> AC2;
		
             AC0 ac0; A0 arg0(ac0.ToNative(argv[0]));
		 AC1 ac1; A1 arg1(ac1.ToNative(argv[1]));
		 AC2 ac2; A2 arg2(ac2.ToNative(argv[2]));
		
            V8Unlocker<UnlockV8> const unlocker();
            return (ReturnType)(*func)(  arg0,  arg1,  arg2 );
        }
        static v8::Handle<v8::Value> Call( FunctionType func, v8::Arguments const & argv )
        {
            CallNative( func, argv );
            return v8::Undefined();
        }
    };
}
namespace Detail {
    template <typename T, typename Sig, bool UnlockV8>
    struct ArgsToMethodForwarder<T, 3,Sig, UnlockV8> : MethodSignature<T,Sig>
    {
        typedef MethodSignature<T,Sig> SignatureType;
        typedef typename SignatureType::FunctionType FunctionType;
        typedef typename SignatureType::ReturnType ReturnType;
        static ReturnType CallNative( T  & self, FunctionType func, Arguments const & argv )
        {
            typedef typename sl::At< 0, Signature<Sig> >::Type A0;
		typedef typename sl::At< 1, Signature<Sig> >::Type A1;
		typedef typename sl::At< 2, Signature<Sig> >::Type A2;
		
             typedef ArgCaster<A0> AC0;
		 typedef ArgCaster<A1> AC1;
		 typedef ArgCaster<A2> AC2;
		
             AC0 ac0; A0 arg0(ac0.ToNative(argv[0]));
		 AC1 ac1; A1 arg1(ac1.ToNative(argv[1]));
		 AC2 ac2; A2 arg2(ac2.ToNative(argv[2]));
		
            typedef typename SignatureType::ReturnType RV;
            V8Unlocker<UnlockV8> const unlocker();
            return (ReturnType)(self.*func)(  arg0,  arg1,  arg2 );
        }
        static v8::Handle<v8::Value> Call( T  & self, FunctionType func, Arguments const & argv )
        {
            try { return CastToJS( CallNative( self, func, argv ) ); }
            HANDLE_PROPAGATE_EXCEPTION;
        }
        static ReturnType CallNative( FunctionType func, v8::Arguments const & argv )
        {
            T  * self = CastFromJS<T>(argv.This());
            if( ! self ) throw MissingThisExceptionT<T>();
            return (ReturnType)CallNative(*self, func, argv);
        }
        static v8::Handle<v8::Value> Call( FunctionType func, v8::Arguments const & argv )
        {
            try { return CastToJS( CallNative(func, argv) ); }
            HANDLE_PROPAGATE_EXCEPTION;
        }
    };

    template <typename T, typename Sig, bool UnlockV8>
    struct ArgsToMethodForwarderVoid<T, 3,Sig, UnlockV8> : MethodSignature<T,Sig>
    {
        typedef MethodSignature<T,Sig> SignatureType;
        typedef typename SignatureType::FunctionType FunctionType;
        typedef typename SignatureType::ReturnType ReturnType;
        static ReturnType CallNative( T  & self, FunctionType func, Arguments const & argv )
        {
            typedef typename sl::At< 0, Signature<Sig> >::Type A0;
		typedef typename sl::At< 1, Signature<Sig> >::Type A1;
		typedef typename sl::At< 2, Signature<Sig> >::Type A2;
		
             typedef ArgCaster<A0> AC0;
		 typedef ArgCaster<A1> AC1;
		 typedef ArgCaster<A2> AC2;
		
             AC0 ac0; A0 arg0(ac0.ToNative(argv[0]));
		 AC1 ac1; A1 arg1(ac1.ToNative(argv[1]));
		 AC2 ac2; A2 arg2(ac2.ToNative(argv[2]));
		
            V8Unlocker<UnlockV8> const unlocker();
            return (ReturnType)(self.*func)(  arg0,  arg1,  arg2 );
        }
        static v8::Handle<v8::Value> Call( T  & self, FunctionType func, Arguments const & argv )
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
            T  * self = CastFromJS<T>(argv.This());
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
}
namespace Detail {
    template <typename T, typename Sig, bool UnlockV8>
    struct ArgsToConstMethodForwarder<T, 3,Sig, UnlockV8> : ConstMethodSignature<T,Sig>
    {
        typedef ConstMethodSignature<T,Sig> SignatureType;
        typedef typename SignatureType::FunctionType FunctionType;
        typedef typename SignatureType::ReturnType ReturnType;
        static ReturnType CallNative( T const & self, FunctionType func, Arguments const & argv )
        {
            typedef typename sl::At< 0, Signature<Sig> >::Type A0;
		typedef typename sl::At< 1, Signature<Sig> >::Type A1;
		typedef typename sl::At< 2, Signature<Sig> >::Type A2;
		
             typedef ArgCaster<A0> AC0;
		 typedef ArgCaster<A1> AC1;
		 typedef ArgCaster<A2> AC2;
		
             AC0 ac0; A0 arg0(ac0.ToNative(argv[0]));
		 AC1 ac1; A1 arg1(ac1.ToNative(argv[1]));
		 AC2 ac2; A2 arg2(ac2.ToNative(argv[2]));
		
            typedef typename SignatureType::ReturnType RV;
            V8Unlocker<UnlockV8> const unlocker();
            return (ReturnType)(self.*func)(  arg0,  arg1,  arg2 );
        }
        static v8::Handle<v8::Value> Call( T const & self, FunctionType func, Arguments const & argv )
        {
            try { return CastToJS( CallNative( self, func, argv ) ); }
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
            try { return CastToJS( CallNative(func, argv) ); }
            HANDLE_PROPAGATE_EXCEPTION;
        }
    };

    template <typename T, typename Sig, bool UnlockV8>
    struct ArgsToConstMethodForwarderVoid<T, 3,Sig, UnlockV8> : ConstMethodSignature<T,Sig>
    {
        typedef ConstMethodSignature<T,Sig> SignatureType;
        typedef typename SignatureType::FunctionType FunctionType;
        typedef typename SignatureType::ReturnType ReturnType;
        static ReturnType CallNative( T const & self, FunctionType func, Arguments const & argv )
        {
            typedef typename sl::At< 0, Signature<Sig> >::Type A0;
		typedef typename sl::At< 1, Signature<Sig> >::Type A1;
		typedef typename sl::At< 2, Signature<Sig> >::Type A2;
		
             typedef ArgCaster<A0> AC0;
		 typedef ArgCaster<A1> AC1;
		 typedef ArgCaster<A2> AC2;
		
             AC0 ac0; A0 arg0(ac0.ToNative(argv[0]));
		 AC1 ac1; A1 arg1(ac1.ToNative(argv[1]));
		 AC2 ac2; A2 arg2(ac2.ToNative(argv[2]));
		
            V8Unlocker<UnlockV8> const unlocker();
            return (ReturnType)(self.*func)(  arg0,  arg1,  arg2 );
        }
        static v8::Handle<v8::Value> Call( T const & self, FunctionType func, Arguments const & argv )
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
    };
}
namespace Detail {
    template <typename Sig, bool UnlockV8>
    struct ArgsToFunctionForwarder<4,Sig,UnlockV8> : FunctionSignature<Sig>
    {
        typedef FunctionSignature<Sig> SignatureType;
        typedef typename SignatureType::FunctionType FunctionType;
        typedef typename SignatureType::ReturnType ReturnType;
        static ReturnType CallNative( FunctionType func, v8::Arguments const & argv )
        {
            typedef char AssertArity[ sl::Arity<SignatureType>::Value == 4 ? 1 : -1];
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
		
            typedef typename SignatureType::ReturnType RV;
            V8Unlocker<UnlockV8> const unlocker();
            return (ReturnType)(*func)(  arg0,  arg1,  arg2,  arg3 );
        }
        static v8::Handle<v8::Value> Call( FunctionType func, v8::Arguments const & argv )
        {
            return CastToJS( CallNative( func, argv ) );
        }
    };

    template <typename Sig, bool UnlockV8>
    struct ArgsToFunctionForwarderVoid<4,Sig,UnlockV8> : FunctionSignature<Sig>
    {
        typedef FunctionSignature<Sig> SignatureType;
        typedef typename SignatureType::FunctionType FunctionType;
        typedef typename SignatureType::ReturnType ReturnType;
        static ReturnType CallNative( FunctionType func, v8::Arguments const & argv )
        {
            typedef char AssertArity[ sl::Arity<SignatureType>::Value == 4 ? 1 : -1];
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
		
            V8Unlocker<UnlockV8> const unlocker();
            return (ReturnType)(*func)(  arg0,  arg1,  arg2,  arg3 );
        }
        static v8::Handle<v8::Value> Call( FunctionType func, v8::Arguments const & argv )
        {
            CallNative( func, argv );
            return v8::Undefined();
        }
    };
}
namespace Detail {
    template <typename T, typename Sig, bool UnlockV8>
    struct ArgsToMethodForwarder<T, 4,Sig, UnlockV8> : MethodSignature<T,Sig>
    {
        typedef MethodSignature<T,Sig> SignatureType;
        typedef typename SignatureType::FunctionType FunctionType;
        typedef typename SignatureType::ReturnType ReturnType;
        static ReturnType CallNative( T  & self, FunctionType func, Arguments const & argv )
        {
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
		
            typedef typename SignatureType::ReturnType RV;
            V8Unlocker<UnlockV8> const unlocker();
            return (ReturnType)(self.*func)(  arg0,  arg1,  arg2,  arg3 );
        }
        static v8::Handle<v8::Value> Call( T  & self, FunctionType func, Arguments const & argv )
        {
            try { return CastToJS( CallNative( self, func, argv ) ); }
            HANDLE_PROPAGATE_EXCEPTION;
        }
        static ReturnType CallNative( FunctionType func, v8::Arguments const & argv )
        {
            T  * self = CastFromJS<T>(argv.This());
            if( ! self ) throw MissingThisExceptionT<T>();
            return (ReturnType)CallNative(*self, func, argv);
        }
        static v8::Handle<v8::Value> Call( FunctionType func, v8::Arguments const & argv )
        {
            try { return CastToJS( CallNative(func, argv) ); }
            HANDLE_PROPAGATE_EXCEPTION;
        }
    };

    template <typename T, typename Sig, bool UnlockV8>
    struct ArgsToMethodForwarderVoid<T, 4,Sig, UnlockV8> : MethodSignature<T,Sig>
    {
        typedef MethodSignature<T,Sig> SignatureType;
        typedef typename SignatureType::FunctionType FunctionType;
        typedef typename SignatureType::ReturnType ReturnType;
        static ReturnType CallNative( T  & self, FunctionType func, Arguments const & argv )
        {
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
		
            V8Unlocker<UnlockV8> const unlocker();
            return (ReturnType)(self.*func)(  arg0,  arg1,  arg2,  arg3 );
        }
        static v8::Handle<v8::Value> Call( T  & self, FunctionType func, Arguments const & argv )
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
            T  * self = CastFromJS<T>(argv.This());
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
}
namespace Detail {
    template <typename T, typename Sig, bool UnlockV8>
    struct ArgsToConstMethodForwarder<T, 4,Sig, UnlockV8> : ConstMethodSignature<T,Sig>
    {
        typedef ConstMethodSignature<T,Sig> SignatureType;
        typedef typename SignatureType::FunctionType FunctionType;
        typedef typename SignatureType::ReturnType ReturnType;
        static ReturnType CallNative( T const & self, FunctionType func, Arguments const & argv )
        {
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
		
            typedef typename SignatureType::ReturnType RV;
            V8Unlocker<UnlockV8> const unlocker();
            return (ReturnType)(self.*func)(  arg0,  arg1,  arg2,  arg3 );
        }
        static v8::Handle<v8::Value> Call( T const & self, FunctionType func, Arguments const & argv )
        {
            try { return CastToJS( CallNative( self, func, argv ) ); }
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
            try { return CastToJS( CallNative(func, argv) ); }
            HANDLE_PROPAGATE_EXCEPTION;
        }
    };

    template <typename T, typename Sig, bool UnlockV8>
    struct ArgsToConstMethodForwarderVoid<T, 4,Sig, UnlockV8> : ConstMethodSignature<T,Sig>
    {
        typedef ConstMethodSignature<T,Sig> SignatureType;
        typedef typename SignatureType::FunctionType FunctionType;
        typedef typename SignatureType::ReturnType ReturnType;
        static ReturnType CallNative( T const & self, FunctionType func, Arguments const & argv )
        {
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
		
            V8Unlocker<UnlockV8> const unlocker();
            return (ReturnType)(self.*func)(  arg0,  arg1,  arg2,  arg3 );
        }
        static v8::Handle<v8::Value> Call( T const & self, FunctionType func, Arguments const & argv )
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
    };
}
namespace Detail {
    template <typename Sig, bool UnlockV8>
    struct ArgsToFunctionForwarder<5,Sig,UnlockV8> : FunctionSignature<Sig>
    {
        typedef FunctionSignature<Sig> SignatureType;
        typedef typename SignatureType::FunctionType FunctionType;
        typedef typename SignatureType::ReturnType ReturnType;
        static ReturnType CallNative( FunctionType func, v8::Arguments const & argv )
        {
            typedef char AssertArity[ sl::Arity<SignatureType>::Value == 5 ? 1 : -1];
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
		
            typedef typename SignatureType::ReturnType RV;
            V8Unlocker<UnlockV8> const unlocker();
            return (ReturnType)(*func)(  arg0,  arg1,  arg2,  arg3,  arg4 );
        }
        static v8::Handle<v8::Value> Call( FunctionType func, v8::Arguments const & argv )
        {
            return CastToJS( CallNative( func, argv ) );
        }
    };

    template <typename Sig, bool UnlockV8>
    struct ArgsToFunctionForwarderVoid<5,Sig,UnlockV8> : FunctionSignature<Sig>
    {
        typedef FunctionSignature<Sig> SignatureType;
        typedef typename SignatureType::FunctionType FunctionType;
        typedef typename SignatureType::ReturnType ReturnType;
        static ReturnType CallNative( FunctionType func, v8::Arguments const & argv )
        {
            typedef char AssertArity[ sl::Arity<SignatureType>::Value == 5 ? 1 : -1];
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
		
            V8Unlocker<UnlockV8> const unlocker();
            return (ReturnType)(*func)(  arg0,  arg1,  arg2,  arg3,  arg4 );
        }
        static v8::Handle<v8::Value> Call( FunctionType func, v8::Arguments const & argv )
        {
            CallNative( func, argv );
            return v8::Undefined();
        }
    };
}
namespace Detail {
    template <typename T, typename Sig, bool UnlockV8>
    struct ArgsToMethodForwarder<T, 5,Sig, UnlockV8> : MethodSignature<T,Sig>
    {
        typedef MethodSignature<T,Sig> SignatureType;
        typedef typename SignatureType::FunctionType FunctionType;
        typedef typename SignatureType::ReturnType ReturnType;
        static ReturnType CallNative( T  & self, FunctionType func, Arguments const & argv )
        {
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
		
            typedef typename SignatureType::ReturnType RV;
            V8Unlocker<UnlockV8> const unlocker();
            return (ReturnType)(self.*func)(  arg0,  arg1,  arg2,  arg3,  arg4 );
        }
        static v8::Handle<v8::Value> Call( T  & self, FunctionType func, Arguments const & argv )
        {
            try { return CastToJS( CallNative( self, func, argv ) ); }
            HANDLE_PROPAGATE_EXCEPTION;
        }
        static ReturnType CallNative( FunctionType func, v8::Arguments const & argv )
        {
            T  * self = CastFromJS<T>(argv.This());
            if( ! self ) throw MissingThisExceptionT<T>();
            return (ReturnType)CallNative(*self, func, argv);
        }
        static v8::Handle<v8::Value> Call( FunctionType func, v8::Arguments const & argv )
        {
            try { return CastToJS( CallNative(func, argv) ); }
            HANDLE_PROPAGATE_EXCEPTION;
        }
    };

    template <typename T, typename Sig, bool UnlockV8>
    struct ArgsToMethodForwarderVoid<T, 5,Sig, UnlockV8> : MethodSignature<T,Sig>
    {
        typedef MethodSignature<T,Sig> SignatureType;
        typedef typename SignatureType::FunctionType FunctionType;
        typedef typename SignatureType::ReturnType ReturnType;
        static ReturnType CallNative( T  & self, FunctionType func, Arguments const & argv )
        {
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
		
            V8Unlocker<UnlockV8> const unlocker();
            return (ReturnType)(self.*func)(  arg0,  arg1,  arg2,  arg3,  arg4 );
        }
        static v8::Handle<v8::Value> Call( T  & self, FunctionType func, Arguments const & argv )
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
            T  * self = CastFromJS<T>(argv.This());
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
}
namespace Detail {
    template <typename T, typename Sig, bool UnlockV8>
    struct ArgsToConstMethodForwarder<T, 5,Sig, UnlockV8> : ConstMethodSignature<T,Sig>
    {
        typedef ConstMethodSignature<T,Sig> SignatureType;
        typedef typename SignatureType::FunctionType FunctionType;
        typedef typename SignatureType::ReturnType ReturnType;
        static ReturnType CallNative( T const & self, FunctionType func, Arguments const & argv )
        {
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
		
            typedef typename SignatureType::ReturnType RV;
            V8Unlocker<UnlockV8> const unlocker();
            return (ReturnType)(self.*func)(  arg0,  arg1,  arg2,  arg3,  arg4 );
        }
        static v8::Handle<v8::Value> Call( T const & self, FunctionType func, Arguments const & argv )
        {
            try { return CastToJS( CallNative( self, func, argv ) ); }
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
            try { return CastToJS( CallNative(func, argv) ); }
            HANDLE_PROPAGATE_EXCEPTION;
        }
    };

    template <typename T, typename Sig, bool UnlockV8>
    struct ArgsToConstMethodForwarderVoid<T, 5,Sig, UnlockV8> : ConstMethodSignature<T,Sig>
    {
        typedef ConstMethodSignature<T,Sig> SignatureType;
        typedef typename SignatureType::FunctionType FunctionType;
        typedef typename SignatureType::ReturnType ReturnType;
        static ReturnType CallNative( T const & self, FunctionType func, Arguments const & argv )
        {
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
		
            V8Unlocker<UnlockV8> const unlocker();
            return (ReturnType)(self.*func)(  arg0,  arg1,  arg2,  arg3,  arg4 );
        }
        static v8::Handle<v8::Value> Call( T const & self, FunctionType func, Arguments const & argv )
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
    };
}
namespace Detail {
    template <typename Sig, bool UnlockV8>
    struct ArgsToFunctionForwarder<6,Sig,UnlockV8> : FunctionSignature<Sig>
    {
        typedef FunctionSignature<Sig> SignatureType;
        typedef typename SignatureType::FunctionType FunctionType;
        typedef typename SignatureType::ReturnType ReturnType;
        static ReturnType CallNative( FunctionType func, v8::Arguments const & argv )
        {
            typedef char AssertArity[ sl::Arity<SignatureType>::Value == 6 ? 1 : -1];
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
		
            typedef typename SignatureType::ReturnType RV;
            V8Unlocker<UnlockV8> const unlocker();
            return (ReturnType)(*func)(  arg0,  arg1,  arg2,  arg3,  arg4,  arg5 );
        }
        static v8::Handle<v8::Value> Call( FunctionType func, v8::Arguments const & argv )
        {
            return CastToJS( CallNative( func, argv ) );
        }
    };

    template <typename Sig, bool UnlockV8>
    struct ArgsToFunctionForwarderVoid<6,Sig,UnlockV8> : FunctionSignature<Sig>
    {
        typedef FunctionSignature<Sig> SignatureType;
        typedef typename SignatureType::FunctionType FunctionType;
        typedef typename SignatureType::ReturnType ReturnType;
        static ReturnType CallNative( FunctionType func, v8::Arguments const & argv )
        {
            typedef char AssertArity[ sl::Arity<SignatureType>::Value == 6 ? 1 : -1];
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
		
            V8Unlocker<UnlockV8> const unlocker();
            return (ReturnType)(*func)(  arg0,  arg1,  arg2,  arg3,  arg4,  arg5 );
        }
        static v8::Handle<v8::Value> Call( FunctionType func, v8::Arguments const & argv )
        {
            CallNative( func, argv );
            return v8::Undefined();
        }
    };
}
namespace Detail {
    template <typename T, typename Sig, bool UnlockV8>
    struct ArgsToMethodForwarder<T, 6,Sig, UnlockV8> : MethodSignature<T,Sig>
    {
        typedef MethodSignature<T,Sig> SignatureType;
        typedef typename SignatureType::FunctionType FunctionType;
        typedef typename SignatureType::ReturnType ReturnType;
        static ReturnType CallNative( T  & self, FunctionType func, Arguments const & argv )
        {
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
		
            typedef typename SignatureType::ReturnType RV;
            V8Unlocker<UnlockV8> const unlocker();
            return (ReturnType)(self.*func)(  arg0,  arg1,  arg2,  arg3,  arg4,  arg5 );
        }
        static v8::Handle<v8::Value> Call( T  & self, FunctionType func, Arguments const & argv )
        {
            try { return CastToJS( CallNative( self, func, argv ) ); }
            HANDLE_PROPAGATE_EXCEPTION;
        }
        static ReturnType CallNative( FunctionType func, v8::Arguments const & argv )
        {
            T  * self = CastFromJS<T>(argv.This());
            if( ! self ) throw MissingThisExceptionT<T>();
            return (ReturnType)CallNative(*self, func, argv);
        }
        static v8::Handle<v8::Value> Call( FunctionType func, v8::Arguments const & argv )
        {
            try { return CastToJS( CallNative(func, argv) ); }
            HANDLE_PROPAGATE_EXCEPTION;
        }
    };

    template <typename T, typename Sig, bool UnlockV8>
    struct ArgsToMethodForwarderVoid<T, 6,Sig, UnlockV8> : MethodSignature<T,Sig>
    {
        typedef MethodSignature<T,Sig> SignatureType;
        typedef typename SignatureType::FunctionType FunctionType;
        typedef typename SignatureType::ReturnType ReturnType;
        static ReturnType CallNative( T  & self, FunctionType func, Arguments const & argv )
        {
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
		
            V8Unlocker<UnlockV8> const unlocker();
            return (ReturnType)(self.*func)(  arg0,  arg1,  arg2,  arg3,  arg4,  arg5 );
        }
        static v8::Handle<v8::Value> Call( T  & self, FunctionType func, Arguments const & argv )
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
            T  * self = CastFromJS<T>(argv.This());
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
}
namespace Detail {
    template <typename T, typename Sig, bool UnlockV8>
    struct ArgsToConstMethodForwarder<T, 6,Sig, UnlockV8> : ConstMethodSignature<T,Sig>
    {
        typedef ConstMethodSignature<T,Sig> SignatureType;
        typedef typename SignatureType::FunctionType FunctionType;
        typedef typename SignatureType::ReturnType ReturnType;
        static ReturnType CallNative( T const & self, FunctionType func, Arguments const & argv )
        {
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
		
            typedef typename SignatureType::ReturnType RV;
            V8Unlocker<UnlockV8> const unlocker();
            return (ReturnType)(self.*func)(  arg0,  arg1,  arg2,  arg3,  arg4,  arg5 );
        }
        static v8::Handle<v8::Value> Call( T const & self, FunctionType func, Arguments const & argv )
        {
            try { return CastToJS( CallNative( self, func, argv ) ); }
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
            try { return CastToJS( CallNative(func, argv) ); }
            HANDLE_PROPAGATE_EXCEPTION;
        }
    };

    template <typename T, typename Sig, bool UnlockV8>
    struct ArgsToConstMethodForwarderVoid<T, 6,Sig, UnlockV8> : ConstMethodSignature<T,Sig>
    {
        typedef ConstMethodSignature<T,Sig> SignatureType;
        typedef typename SignatureType::FunctionType FunctionType;
        typedef typename SignatureType::ReturnType ReturnType;
        static ReturnType CallNative( T const & self, FunctionType func, Arguments const & argv )
        {
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
		
            V8Unlocker<UnlockV8> const unlocker();
            return (ReturnType)(self.*func)(  arg0,  arg1,  arg2,  arg3,  arg4,  arg5 );
        }
        static v8::Handle<v8::Value> Call( T const & self, FunctionType func, Arguments const & argv )
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
    };
}
namespace Detail {
    template <typename Sig, bool UnlockV8>
    struct ArgsToFunctionForwarder<7,Sig,UnlockV8> : FunctionSignature<Sig>
    {
        typedef FunctionSignature<Sig> SignatureType;
        typedef typename SignatureType::FunctionType FunctionType;
        typedef typename SignatureType::ReturnType ReturnType;
        static ReturnType CallNative( FunctionType func, v8::Arguments const & argv )
        {
            typedef char AssertArity[ sl::Arity<SignatureType>::Value == 7 ? 1 : -1];
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
		
            typedef typename SignatureType::ReturnType RV;
            V8Unlocker<UnlockV8> const unlocker();
            return (ReturnType)(*func)(  arg0,  arg1,  arg2,  arg3,  arg4,  arg5,  arg6 );
        }
        static v8::Handle<v8::Value> Call( FunctionType func, v8::Arguments const & argv )
        {
            return CastToJS( CallNative( func, argv ) );
        }
    };

    template <typename Sig, bool UnlockV8>
    struct ArgsToFunctionForwarderVoid<7,Sig,UnlockV8> : FunctionSignature<Sig>
    {
        typedef FunctionSignature<Sig> SignatureType;
        typedef typename SignatureType::FunctionType FunctionType;
        typedef typename SignatureType::ReturnType ReturnType;
        static ReturnType CallNative( FunctionType func, v8::Arguments const & argv )
        {
            typedef char AssertArity[ sl::Arity<SignatureType>::Value == 7 ? 1 : -1];
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
		
            V8Unlocker<UnlockV8> const unlocker();
            return (ReturnType)(*func)(  arg0,  arg1,  arg2,  arg3,  arg4,  arg5,  arg6 );
        }
        static v8::Handle<v8::Value> Call( FunctionType func, v8::Arguments const & argv )
        {
            CallNative( func, argv );
            return v8::Undefined();
        }
    };
}
namespace Detail {
    template <typename T, typename Sig, bool UnlockV8>
    struct ArgsToMethodForwarder<T, 7,Sig, UnlockV8> : MethodSignature<T,Sig>
    {
        typedef MethodSignature<T,Sig> SignatureType;
        typedef typename SignatureType::FunctionType FunctionType;
        typedef typename SignatureType::ReturnType ReturnType;
        static ReturnType CallNative( T  & self, FunctionType func, Arguments const & argv )
        {
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
		
            typedef typename SignatureType::ReturnType RV;
            V8Unlocker<UnlockV8> const unlocker();
            return (ReturnType)(self.*func)(  arg0,  arg1,  arg2,  arg3,  arg4,  arg5,  arg6 );
        }
        static v8::Handle<v8::Value> Call( T  & self, FunctionType func, Arguments const & argv )
        {
            try { return CastToJS( CallNative( self, func, argv ) ); }
            HANDLE_PROPAGATE_EXCEPTION;
        }
        static ReturnType CallNative( FunctionType func, v8::Arguments const & argv )
        {
            T  * self = CastFromJS<T>(argv.This());
            if( ! self ) throw MissingThisExceptionT<T>();
            return (ReturnType)CallNative(*self, func, argv);
        }
        static v8::Handle<v8::Value> Call( FunctionType func, v8::Arguments const & argv )
        {
            try { return CastToJS( CallNative(func, argv) ); }
            HANDLE_PROPAGATE_EXCEPTION;
        }
    };

    template <typename T, typename Sig, bool UnlockV8>
    struct ArgsToMethodForwarderVoid<T, 7,Sig, UnlockV8> : MethodSignature<T,Sig>
    {
        typedef MethodSignature<T,Sig> SignatureType;
        typedef typename SignatureType::FunctionType FunctionType;
        typedef typename SignatureType::ReturnType ReturnType;
        static ReturnType CallNative( T  & self, FunctionType func, Arguments const & argv )
        {
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
		
            V8Unlocker<UnlockV8> const unlocker();
            return (ReturnType)(self.*func)(  arg0,  arg1,  arg2,  arg3,  arg4,  arg5,  arg6 );
        }
        static v8::Handle<v8::Value> Call( T  & self, FunctionType func, Arguments const & argv )
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
            T  * self = CastFromJS<T>(argv.This());
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
}
namespace Detail {
    template <typename T, typename Sig, bool UnlockV8>
    struct ArgsToConstMethodForwarder<T, 7,Sig, UnlockV8> : ConstMethodSignature<T,Sig>
    {
        typedef ConstMethodSignature<T,Sig> SignatureType;
        typedef typename SignatureType::FunctionType FunctionType;
        typedef typename SignatureType::ReturnType ReturnType;
        static ReturnType CallNative( T const & self, FunctionType func, Arguments const & argv )
        {
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
		
            typedef typename SignatureType::ReturnType RV;
            V8Unlocker<UnlockV8> const unlocker();
            return (ReturnType)(self.*func)(  arg0,  arg1,  arg2,  arg3,  arg4,  arg5,  arg6 );
        }
        static v8::Handle<v8::Value> Call( T const & self, FunctionType func, Arguments const & argv )
        {
            try { return CastToJS( CallNative( self, func, argv ) ); }
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
            try { return CastToJS( CallNative(func, argv) ); }
            HANDLE_PROPAGATE_EXCEPTION;
        }
    };

    template <typename T, typename Sig, bool UnlockV8>
    struct ArgsToConstMethodForwarderVoid<T, 7,Sig, UnlockV8> : ConstMethodSignature<T,Sig>
    {
        typedef ConstMethodSignature<T,Sig> SignatureType;
        typedef typename SignatureType::FunctionType FunctionType;
        typedef typename SignatureType::ReturnType ReturnType;
        static ReturnType CallNative( T const & self, FunctionType func, Arguments const & argv )
        {
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
		
            V8Unlocker<UnlockV8> const unlocker();
            return (ReturnType)(self.*func)(  arg0,  arg1,  arg2,  arg3,  arg4,  arg5,  arg6 );
        }
        static v8::Handle<v8::Value> Call( T const & self, FunctionType func, Arguments const & argv )
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
    };
}
namespace Detail {
    template <typename Sig, bool UnlockV8>
    struct ArgsToFunctionForwarder<8,Sig,UnlockV8> : FunctionSignature<Sig>
    {
        typedef FunctionSignature<Sig> SignatureType;
        typedef typename SignatureType::FunctionType FunctionType;
        typedef typename SignatureType::ReturnType ReturnType;
        static ReturnType CallNative( FunctionType func, v8::Arguments const & argv )
        {
            typedef char AssertArity[ sl::Arity<SignatureType>::Value == 8 ? 1 : -1];
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
		
            typedef typename SignatureType::ReturnType RV;
            V8Unlocker<UnlockV8> const unlocker();
            return (ReturnType)(*func)(  arg0,  arg1,  arg2,  arg3,  arg4,  arg5,  arg6,  arg7 );
        }
        static v8::Handle<v8::Value> Call( FunctionType func, v8::Arguments const & argv )
        {
            return CastToJS( CallNative( func, argv ) );
        }
    };

    template <typename Sig, bool UnlockV8>
    struct ArgsToFunctionForwarderVoid<8,Sig,UnlockV8> : FunctionSignature<Sig>
    {
        typedef FunctionSignature<Sig> SignatureType;
        typedef typename SignatureType::FunctionType FunctionType;
        typedef typename SignatureType::ReturnType ReturnType;
        static ReturnType CallNative( FunctionType func, v8::Arguments const & argv )
        {
            typedef char AssertArity[ sl::Arity<SignatureType>::Value == 8 ? 1 : -1];
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
		
            V8Unlocker<UnlockV8> const unlocker();
            return (ReturnType)(*func)(  arg0,  arg1,  arg2,  arg3,  arg4,  arg5,  arg6,  arg7 );
        }
        static v8::Handle<v8::Value> Call( FunctionType func, v8::Arguments const & argv )
        {
            CallNative( func, argv );
            return v8::Undefined();
        }
    };
}
namespace Detail {
    template <typename T, typename Sig, bool UnlockV8>
    struct ArgsToMethodForwarder<T, 8,Sig, UnlockV8> : MethodSignature<T,Sig>
    {
        typedef MethodSignature<T,Sig> SignatureType;
        typedef typename SignatureType::FunctionType FunctionType;
        typedef typename SignatureType::ReturnType ReturnType;
        static ReturnType CallNative( T  & self, FunctionType func, Arguments const & argv )
        {
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
		
            typedef typename SignatureType::ReturnType RV;
            V8Unlocker<UnlockV8> const unlocker();
            return (ReturnType)(self.*func)(  arg0,  arg1,  arg2,  arg3,  arg4,  arg5,  arg6,  arg7 );
        }
        static v8::Handle<v8::Value> Call( T  & self, FunctionType func, Arguments const & argv )
        {
            try { return CastToJS( CallNative( self, func, argv ) ); }
            HANDLE_PROPAGATE_EXCEPTION;
        }
        static ReturnType CallNative( FunctionType func, v8::Arguments const & argv )
        {
            T  * self = CastFromJS<T>(argv.This());
            if( ! self ) throw MissingThisExceptionT<T>();
            return (ReturnType)CallNative(*self, func, argv);
        }
        static v8::Handle<v8::Value> Call( FunctionType func, v8::Arguments const & argv )
        {
            try { return CastToJS( CallNative(func, argv) ); }
            HANDLE_PROPAGATE_EXCEPTION;
        }
    };

    template <typename T, typename Sig, bool UnlockV8>
    struct ArgsToMethodForwarderVoid<T, 8,Sig, UnlockV8> : MethodSignature<T,Sig>
    {
        typedef MethodSignature<T,Sig> SignatureType;
        typedef typename SignatureType::FunctionType FunctionType;
        typedef typename SignatureType::ReturnType ReturnType;
        static ReturnType CallNative( T  & self, FunctionType func, Arguments const & argv )
        {
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
		
            V8Unlocker<UnlockV8> const unlocker();
            return (ReturnType)(self.*func)(  arg0,  arg1,  arg2,  arg3,  arg4,  arg5,  arg6,  arg7 );
        }
        static v8::Handle<v8::Value> Call( T  & self, FunctionType func, Arguments const & argv )
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
            T  * self = CastFromJS<T>(argv.This());
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
}
namespace Detail {
    template <typename T, typename Sig, bool UnlockV8>
    struct ArgsToConstMethodForwarder<T, 8,Sig, UnlockV8> : ConstMethodSignature<T,Sig>
    {
        typedef ConstMethodSignature<T,Sig> SignatureType;
        typedef typename SignatureType::FunctionType FunctionType;
        typedef typename SignatureType::ReturnType ReturnType;
        static ReturnType CallNative( T const & self, FunctionType func, Arguments const & argv )
        {
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
		
            typedef typename SignatureType::ReturnType RV;
            V8Unlocker<UnlockV8> const unlocker();
            return (ReturnType)(self.*func)(  arg0,  arg1,  arg2,  arg3,  arg4,  arg5,  arg6,  arg7 );
        }
        static v8::Handle<v8::Value> Call( T const & self, FunctionType func, Arguments const & argv )
        {
            try { return CastToJS( CallNative( self, func, argv ) ); }
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
            try { return CastToJS( CallNative(func, argv) ); }
            HANDLE_PROPAGATE_EXCEPTION;
        }
    };

    template <typename T, typename Sig, bool UnlockV8>
    struct ArgsToConstMethodForwarderVoid<T, 8,Sig, UnlockV8> : ConstMethodSignature<T,Sig>
    {
        typedef ConstMethodSignature<T,Sig> SignatureType;
        typedef typename SignatureType::FunctionType FunctionType;
        typedef typename SignatureType::ReturnType ReturnType;
        static ReturnType CallNative( T const & self, FunctionType func, Arguments const & argv )
        {
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
		
            V8Unlocker<UnlockV8> const unlocker();
            return (ReturnType)(self.*func)(  arg0,  arg1,  arg2,  arg3,  arg4,  arg5,  arg6,  arg7 );
        }
        static v8::Handle<v8::Value> Call( T const & self, FunctionType func, Arguments const & argv )
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
    };
}
namespace Detail {
    template <typename Sig, bool UnlockV8>
    struct ArgsToFunctionForwarder<9,Sig,UnlockV8> : FunctionSignature<Sig>
    {
        typedef FunctionSignature<Sig> SignatureType;
        typedef typename SignatureType::FunctionType FunctionType;
        typedef typename SignatureType::ReturnType ReturnType;
        static ReturnType CallNative( FunctionType func, v8::Arguments const & argv )
        {
            typedef char AssertArity[ sl::Arity<SignatureType>::Value == 9 ? 1 : -1];
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
		
            typedef typename SignatureType::ReturnType RV;
            V8Unlocker<UnlockV8> const unlocker();
            return (ReturnType)(*func)(  arg0,  arg1,  arg2,  arg3,  arg4,  arg5,  arg6,  arg7,  arg8 );
        }
        static v8::Handle<v8::Value> Call( FunctionType func, v8::Arguments const & argv )
        {
            return CastToJS( CallNative( func, argv ) );
        }
    };

    template <typename Sig, bool UnlockV8>
    struct ArgsToFunctionForwarderVoid<9,Sig,UnlockV8> : FunctionSignature<Sig>
    {
        typedef FunctionSignature<Sig> SignatureType;
        typedef typename SignatureType::FunctionType FunctionType;
        typedef typename SignatureType::ReturnType ReturnType;
        static ReturnType CallNative( FunctionType func, v8::Arguments const & argv )
        {
            typedef char AssertArity[ sl::Arity<SignatureType>::Value == 9 ? 1 : -1];
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
		
            V8Unlocker<UnlockV8> const unlocker();
            return (ReturnType)(*func)(  arg0,  arg1,  arg2,  arg3,  arg4,  arg5,  arg6,  arg7,  arg8 );
        }
        static v8::Handle<v8::Value> Call( FunctionType func, v8::Arguments const & argv )
        {
            CallNative( func, argv );
            return v8::Undefined();
        }
    };
}
namespace Detail {
    template <typename T, typename Sig, bool UnlockV8>
    struct ArgsToMethodForwarder<T, 9,Sig, UnlockV8> : MethodSignature<T,Sig>
    {
        typedef MethodSignature<T,Sig> SignatureType;
        typedef typename SignatureType::FunctionType FunctionType;
        typedef typename SignatureType::ReturnType ReturnType;
        static ReturnType CallNative( T  & self, FunctionType func, Arguments const & argv )
        {
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
		
            typedef typename SignatureType::ReturnType RV;
            V8Unlocker<UnlockV8> const unlocker();
            return (ReturnType)(self.*func)(  arg0,  arg1,  arg2,  arg3,  arg4,  arg5,  arg6,  arg7,  arg8 );
        }
        static v8::Handle<v8::Value> Call( T  & self, FunctionType func, Arguments const & argv )
        {
            try { return CastToJS( CallNative( self, func, argv ) ); }
            HANDLE_PROPAGATE_EXCEPTION;
        }
        static ReturnType CallNative( FunctionType func, v8::Arguments const & argv )
        {
            T  * self = CastFromJS<T>(argv.This());
            if( ! self ) throw MissingThisExceptionT<T>();
            return (ReturnType)CallNative(*self, func, argv);
        }
        static v8::Handle<v8::Value> Call( FunctionType func, v8::Arguments const & argv )
        {
            try { return CastToJS( CallNative(func, argv) ); }
            HANDLE_PROPAGATE_EXCEPTION;
        }
    };

    template <typename T, typename Sig, bool UnlockV8>
    struct ArgsToMethodForwarderVoid<T, 9,Sig, UnlockV8> : MethodSignature<T,Sig>
    {
        typedef MethodSignature<T,Sig> SignatureType;
        typedef typename SignatureType::FunctionType FunctionType;
        typedef typename SignatureType::ReturnType ReturnType;
        static ReturnType CallNative( T  & self, FunctionType func, Arguments const & argv )
        {
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
		
            V8Unlocker<UnlockV8> const unlocker();
            return (ReturnType)(self.*func)(  arg0,  arg1,  arg2,  arg3,  arg4,  arg5,  arg6,  arg7,  arg8 );
        }
        static v8::Handle<v8::Value> Call( T  & self, FunctionType func, Arguments const & argv )
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
            T  * self = CastFromJS<T>(argv.This());
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
}
namespace Detail {
    template <typename T, typename Sig, bool UnlockV8>
    struct ArgsToConstMethodForwarder<T, 9,Sig, UnlockV8> : ConstMethodSignature<T,Sig>
    {
        typedef ConstMethodSignature<T,Sig> SignatureType;
        typedef typename SignatureType::FunctionType FunctionType;
        typedef typename SignatureType::ReturnType ReturnType;
        static ReturnType CallNative( T const & self, FunctionType func, Arguments const & argv )
        {
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
		
            typedef typename SignatureType::ReturnType RV;
            V8Unlocker<UnlockV8> const unlocker();
            return (ReturnType)(self.*func)(  arg0,  arg1,  arg2,  arg3,  arg4,  arg5,  arg6,  arg7,  arg8 );
        }
        static v8::Handle<v8::Value> Call( T const & self, FunctionType func, Arguments const & argv )
        {
            try { return CastToJS( CallNative( self, func, argv ) ); }
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
            try { return CastToJS( CallNative(func, argv) ); }
            HANDLE_PROPAGATE_EXCEPTION;
        }
    };

    template <typename T, typename Sig, bool UnlockV8>
    struct ArgsToConstMethodForwarderVoid<T, 9,Sig, UnlockV8> : ConstMethodSignature<T,Sig>
    {
        typedef ConstMethodSignature<T,Sig> SignatureType;
        typedef typename SignatureType::FunctionType FunctionType;
        typedef typename SignatureType::ReturnType ReturnType;
        static ReturnType CallNative( T const & self, FunctionType func, Arguments const & argv )
        {
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
		
            V8Unlocker<UnlockV8> const unlocker();
            return (ReturnType)(self.*func)(  arg0,  arg1,  arg2,  arg3,  arg4,  arg5,  arg6,  arg7,  arg8 );
        }
        static v8::Handle<v8::Value> Call( T const & self, FunctionType func, Arguments const & argv )
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
    };
}
namespace Detail {
    template <typename Sig, bool UnlockV8>
    struct ArgsToFunctionForwarder<10,Sig,UnlockV8> : FunctionSignature<Sig>
    {
        typedef FunctionSignature<Sig> SignatureType;
        typedef typename SignatureType::FunctionType FunctionType;
        typedef typename SignatureType::ReturnType ReturnType;
        static ReturnType CallNative( FunctionType func, v8::Arguments const & argv )
        {
            typedef char AssertArity[ sl::Arity<SignatureType>::Value == 10 ? 1 : -1];
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
		
            typedef typename SignatureType::ReturnType RV;
            V8Unlocker<UnlockV8> const unlocker();
            return (ReturnType)(*func)(  arg0,  arg1,  arg2,  arg3,  arg4,  arg5,  arg6,  arg7,  arg8,  arg9 );
        }
        static v8::Handle<v8::Value> Call( FunctionType func, v8::Arguments const & argv )
        {
            return CastToJS( CallNative( func, argv ) );
        }
    };

    template <typename Sig, bool UnlockV8>
    struct ArgsToFunctionForwarderVoid<10,Sig,UnlockV8> : FunctionSignature<Sig>
    {
        typedef FunctionSignature<Sig> SignatureType;
        typedef typename SignatureType::FunctionType FunctionType;
        typedef typename SignatureType::ReturnType ReturnType;
        static ReturnType CallNative( FunctionType func, v8::Arguments const & argv )
        {
            typedef char AssertArity[ sl::Arity<SignatureType>::Value == 10 ? 1 : -1];
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
		
            V8Unlocker<UnlockV8> const unlocker();
            return (ReturnType)(*func)(  arg0,  arg1,  arg2,  arg3,  arg4,  arg5,  arg6,  arg7,  arg8,  arg9 );
        }
        static v8::Handle<v8::Value> Call( FunctionType func, v8::Arguments const & argv )
        {
            CallNative( func, argv );
            return v8::Undefined();
        }
    };
}
namespace Detail {
    template <typename T, typename Sig, bool UnlockV8>
    struct ArgsToMethodForwarder<T, 10,Sig, UnlockV8> : MethodSignature<T,Sig>
    {
        typedef MethodSignature<T,Sig> SignatureType;
        typedef typename SignatureType::FunctionType FunctionType;
        typedef typename SignatureType::ReturnType ReturnType;
        static ReturnType CallNative( T  & self, FunctionType func, Arguments const & argv )
        {
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
		
            typedef typename SignatureType::ReturnType RV;
            V8Unlocker<UnlockV8> const unlocker();
            return (ReturnType)(self.*func)(  arg0,  arg1,  arg2,  arg3,  arg4,  arg5,  arg6,  arg7,  arg8,  arg9 );
        }
        static v8::Handle<v8::Value> Call( T  & self, FunctionType func, Arguments const & argv )
        {
            try { return CastToJS( CallNative( self, func, argv ) ); }
            HANDLE_PROPAGATE_EXCEPTION;
        }
        static ReturnType CallNative( FunctionType func, v8::Arguments const & argv )
        {
            T  * self = CastFromJS<T>(argv.This());
            if( ! self ) throw MissingThisExceptionT<T>();
            return (ReturnType)CallNative(*self, func, argv);
        }
        static v8::Handle<v8::Value> Call( FunctionType func, v8::Arguments const & argv )
        {
            try { return CastToJS( CallNative(func, argv) ); }
            HANDLE_PROPAGATE_EXCEPTION;
        }
    };

    template <typename T, typename Sig, bool UnlockV8>
    struct ArgsToMethodForwarderVoid<T, 10,Sig, UnlockV8> : MethodSignature<T,Sig>
    {
        typedef MethodSignature<T,Sig> SignatureType;
        typedef typename SignatureType::FunctionType FunctionType;
        typedef typename SignatureType::ReturnType ReturnType;
        static ReturnType CallNative( T  & self, FunctionType func, Arguments const & argv )
        {
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
		
            V8Unlocker<UnlockV8> const unlocker();
            return (ReturnType)(self.*func)(  arg0,  arg1,  arg2,  arg3,  arg4,  arg5,  arg6,  arg7,  arg8,  arg9 );
        }
        static v8::Handle<v8::Value> Call( T  & self, FunctionType func, Arguments const & argv )
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
            T  * self = CastFromJS<T>(argv.This());
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
}
namespace Detail {
    template <typename T, typename Sig, bool UnlockV8>
    struct ArgsToConstMethodForwarder<T, 10,Sig, UnlockV8> : ConstMethodSignature<T,Sig>
    {
        typedef ConstMethodSignature<T,Sig> SignatureType;
        typedef typename SignatureType::FunctionType FunctionType;
        typedef typename SignatureType::ReturnType ReturnType;
        static ReturnType CallNative( T const & self, FunctionType func, Arguments const & argv )
        {
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
		
            typedef typename SignatureType::ReturnType RV;
            V8Unlocker<UnlockV8> const unlocker();
            return (ReturnType)(self.*func)(  arg0,  arg1,  arg2,  arg3,  arg4,  arg5,  arg6,  arg7,  arg8,  arg9 );
        }
        static v8::Handle<v8::Value> Call( T const & self, FunctionType func, Arguments const & argv )
        {
            try { return CastToJS( CallNative( self, func, argv ) ); }
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
            try { return CastToJS( CallNative(func, argv) ); }
            HANDLE_PROPAGATE_EXCEPTION;
        }
    };

    template <typename T, typename Sig, bool UnlockV8>
    struct ArgsToConstMethodForwarderVoid<T, 10,Sig, UnlockV8> : ConstMethodSignature<T,Sig>
    {
        typedef ConstMethodSignature<T,Sig> SignatureType;
        typedef typename SignatureType::FunctionType FunctionType;
        typedef typename SignatureType::ReturnType ReturnType;
        static ReturnType CallNative( T const & self, FunctionType func, Arguments const & argv )
        {
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
		
            V8Unlocker<UnlockV8> const unlocker();
            return (ReturnType)(self.*func)(  arg0,  arg1,  arg2,  arg3,  arg4,  arg5,  arg6,  arg7,  arg8,  arg9 );
        }
        static v8::Handle<v8::Value> Call( T const & self, FunctionType func, Arguments const & argv )
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
    };
}
#endif // if !defined(DOXYGEN)
