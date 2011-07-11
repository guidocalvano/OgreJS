/**
   Test/demo code for the v8-convert API.
*/
#if defined(NDEBUG)
#  undef NDEBUG  // force assert() to work
#endif

#include <cassert>
#include <iostream>
#include <fstream>
#include <iterator>
#include <algorithm>

#ifndef CERR
#define CERR std::cerr << __FILE__ << ":" << std::dec << __LINE__ << ":" <<__FUNCTION__ << "(): "
#endif

#ifndef COUT
#define COUT std::cout << __FILE__ << ":" << std::dec << __LINE__ << " : "
#endif

#include <iostream>

#include "v8/convert/v8-convert.hpp"
#include "v8/convert/V8Shell.hpp"
namespace cv = ::v8::convert;
//typedef v8::Handle<v8::Value> ValueHandle;
#define ValueHandle v8::Handle<v8::Value>

#include "ConvertDemo.hpp"
#define JSTR(X) v8::String::New(X)

#include <cstdio> /* puts() */

#if !defined(_WIN32)
#  include <unistd.h> /* only for sleep() */
#  define do_sleep ::sleep
#else
#  include <windows.h> /* only for Sleep() */
#  define do_sleep(N) ::Sleep((N)*1000)
#endif


ValueHandle test1_callback( v8::Arguments const & argv )
{
    using namespace v8;
    Local<Value> myref /* to keep v8 from prematurly cleaning my object. */;
    Local<Function> jf;
    BoundNative * fooPtr;
    Local<Object> myobj;
    {
        BoundNative::SetupBindings( v8::Context::GetCurrent()->Global() );
        //v8::HandleScope scope;
        Handle<Function> const & ctor( cv::ClassCreator<BoundSubNative>::Instance().CtorFunction() );
        CERR << "Calling NewInstance()\n";
        myref = ctor->NewInstance(0, NULL);
        CERR << "Called NewInstance()\n";
        fooPtr = cv::CastFromJS<BoundNative>(myref);
        CERR << "NewInstance() == @"<<(void const *)fooPtr<<'\n';
        assert( 0 != fooPtr );
        myobj = Object::Cast(*myref);
        ValueHandle varg[] = {
          JSTR("Example of binding functions taking (char const *) arguments.")
        };
        int const argc = 1;
        jf = Function::Cast( *(myobj->Get(JSTR("puts"))) );
        jf->Call( myobj, argc, varg );
        jf = Function::Cast( *(myobj->Get(JSTR("bogo"))) );
        jf->Call( myobj, argc, varg );
        jf = Function::Cast( *(myobj->Get(JSTR("bogo2"))) );
        jf->Call( myobj, argc, varg );
        jf = Function::Cast( *(myobj->Get(JSTR("nativeParam"))) );
        varg[0] = myobj;
        jf->Call( myobj, argc, varg );
#if 1
        jf = Function::Cast( *(myobj->Get(JSTR("runGC"))) );
        CERR << "runGC handle isEmpty?=="<<jf.IsEmpty()<<'\n';
        jf->Call( myobj, 0, varg );
#endif
    }

    typedef cv::FunctionPtr< int (char const *), ::puts > PUTS;
    PUTS::FunctionType putstr = PUTS::Function;
    putstr("roundabout use of puts()");
    
    typedef cv::FunctionPtr< void (), doNothing > DoNothingFP;
    DoNothingFP::Function();
    typedef cv::FunctionPtr< void (), doNothing > DoNothingFP2;
    DoNothingFP2::Function();
    typedef cv::FunctionPtr< int (int), doSomething > DoSomething;
    DoSomething::Function(13);

    
    typedef cv::MethodPtr< BoundNative, void (void), &BoundNative::doFoo > DoFoo;
    typedef cv::MethodPtr< BoundNative, double (int,double), &BoundNative::doFoo2 > DoFoo2;

    typedef cv::ConstMethodPtr< BoundNative, double (int,double), &BoundNative::operator() > DoFooOp2;

    v8::InvocationCallback cb;
    CERR << "Calling doNothing():\n";
    cb = cv::FunctionToInvocationCallback< void (), doNothing >;
    cb(argv);

  
    CERR << "Calling doSomething():\n";
    cb = cv::FunctionToInvocationCallback< int (int), doSomething >;
    cb(argv);
    BoundNative & foo = *fooPtr;
    CERR << "Calling foo.doFoo2():\n";
    cv::MethodToInCa< BoundNative, double (int, double), &BoundNative::doFoo2 >::Call(foo, argv);

    
    CERR << "Calling foo.operator():\n";
    cv::ConstMethodToInCa< BoundNative, double (int, double), &BoundNative::operator() >::Call(foo, argv);

    CERR << "Calling foo.invo() (non-const):\n";
    cv::MethodToInCa< BoundNative, ValueHandle(v8::Arguments const &), &BoundNative::invo >::Call(foo, argv);


    CERR << "Calling foo.invo() (const):\n";
    cv::ConstMethodToInCa< BoundNative, ValueHandle(v8::Arguments const &), &BoundNative::invo >::Call(foo, argv);


    CERR << "Calling sampleCallback():\n";
    cb = cv::FunctionToInCa< ValueHandle(v8::Arguments const &), sampleCallback >::Call;
    cb(argv);


    CERR << "Calling foo.invo() (static):\n";
    cb = cv::FunctionToInCa< ValueHandle(v8::Arguments const &), BoundNative::invoStatic >::Call;
    cb(argv);

    CERR << "argv-forwarder (void):\n";
    cv::ArgsToFunctionForwarder< void () >::Call( doNothing, argv );
    CERR << "argv-forwarder (int):\n";
    cv::ArgsToFunctionForwarder< int (int) >::Call( doSomething, argv );

    CERR << "argv-forwarder (int) via forwardFunction():\n";
    cv::forwardFunction( doSomething, argv );
    CERR << "argv-forwarder (void) via forwardFunction():\n";
    cv::forwardFunction( doNothing, argv );

    CERR << "argv-method-forwarder (void):\n";
    cv::ArgsToMethodForwarder< BoundNative, void () >::Call( foo, &BoundNative::doFoo, argv );

     CERR << "argv-method-forwarder (int,double):\n";
     cv::ArgsToMethodForwarder< BoundNative, double (int,double) >::Call( foo, &BoundNative::doFoo2, argv );
     CERR << "same thing using forwardMethod(T, MemFunc, Arguments):\n";
     cv::forwardMethod( foo, &BoundNative::doFoo2, argv );
     cv::forwardMethod( foo, &BoundNative::doFoo, argv );
     try
     {
         cv::forwardMethod<BoundNative>( &BoundNative::doFoo, argv )
             /* won't actually work b/c argv.This() is-not-a BoundNative */
             ;
     }
     catch(cv::MissingThisException const & ex )
     {
         CERR << "Got expected exception: " << ex.Buffer() << '\n';
     }
     catch(...) { throw; }

     CERR << "argv-const-method-forwarder (void):\n";
     cv::ArgsToConstMethodForwarder< BoundNative, void () >::Call( foo, &BoundNative::doFooConst, argv );

     CERR << "Calling forwardConstMethod(T, MemFunc, Arguments):\n";
     cv::forwardConstMethod( foo, &BoundNative::doFooConst, argv );
     cv::forwardConstMethod( foo, &BoundNative::doFooConstInt, argv );
     try
     {
         cv::forwardConstMethod<BoundNative>( &BoundNative::doFooConstInt, argv )
             /* won't actually work b/c argv.This() is-not-a BoundNative */
             ;
     }
     catch(cv::MissingThisException const & ex )
     {
         CERR << "Got expected exception: " << ex.Buffer() << '\n';
     }
     catch(...) { throw; }
#if 0
     jf = Function::Cast( *(myobj->Get(JSTR("destroy"))) );
     CERR << "Calling myObject.destroy()...\n";
     jf->Call( Local<Object>(Object::Cast(*myref)), 0, NULL );
#endif

     
     CERR << "Done\n";
     CERR << "NOTE: you may see an exception message directly before or after this "
          << "function returns regarding a missing native 'this' pointer. Don't "
          << "panic - it is _expected_ here.\n"
         ;
     return v8::Undefined();
}

struct MyType
{
    MyType() {
        CERR << "MyType::MyType() @ "<<this<<'\n';
    }
    MyType( int i, double d ) {
        CERR << "MyType::MyType("<<i<<", "<<d<<") @ "<<this<<'\n';
    }
    MyType( char const * str ) {
        CERR << "MyType::MyType("<<str<<") @ "<<this<<'\n';
    }
    MyType( v8::Arguments const & argv ) {
        CERR << "MyType::MyType("<<argv.Length()<<" arg(s)) @ "<<this<<'\n';
    }
    ~MyType() {
        CERR << "MyType::~MyType() @ "<<this<<'\n';
    }
    
    // Ctors we want to bind to v8 (there are several other ways to do this):
    typedef cv::Signature<MyType (
        cv::CtorForwarder<MyType *()>,
        cv::CtorForwarder<MyType *(char const *)>,
        cv::CtorForwarder<MyType *( int, double )>,
        cv::CtorForwarder<MyType *( v8::Arguments const &)>
    )> Ctors;
};

//-----------------------------------
// Policies used by cv::ClassCreator
namespace v8 { namespace convert {

    template <>
    class ClassCreator_Factory<MyType>
     : public ClassCreator_Factory_CtorArityDispatcher< MyType, MyType::Ctors >
    {};
    template <>
    struct JSToNative< MyType > : JSToNative_ClassCreator< MyType >
    {};
    
    // used in some error reporting:
    template <>
    char const * TypeName< MyType >::Value = "MyType";
}}
//-----------------------------------
// Ultra-brief ClassCreator demo. See ConvertDemo.?pp for MUCH more.
void bind_MyType( v8::Handle<v8::Object> dest )
{
    typedef cv::ClassCreator<MyType> CC;
    CC & cc(CC::Instance());
    cc
        ("destroy", CC::DestroyObjectCallback)
        .AddClassTo( "MyType", dest );
}

void test1(cv::Shell & shell)
{
    using namespace v8;
    HandleScope scope;
    bind_MyType( shell.Global() );

    if(1)
    {
        Handle<Function> hf = FunctionTemplate::New(test1_callback)->GetFunction();
        Handle<Value> args[] = {
            Integer::New(3),
            Number::New(5.1),
            Undefined()
        };
        CERR << "Calling binding function...\n";
        TryCatch catcher;
        hf->Call( shell.Context()->Global(), 3, args );
        catcher.Reset();
        CERR << "Returned from binding function.\n";
    }
    else
    {
        BoundNative::SetupBindings( shell.Global() );
    }

    char const * extScr = "./test.js";
    CERR << "Calling external script ["<<extScr<<"]...\n";
    if(1)
    {
        Local<Object> global( shell.Context()->Global() );
        assert( ! global.IsEmpty() );
        Local<Function> jf( Function::Cast( *(global->Get(JSTR("load"))) ) );
        assert( ! jf.IsEmpty() );
        ValueHandle varg[] = { v8::String::New(extScr), cv::CastToJS(extScr) };
        jf->Call( global, 1, varg );
    }
    else if(1)
    {
        shell.ExecuteFile( extScr );
    }
    CERR << "Returned from external script\n";
}

static int v8_main(int argc, char const * const * argv)
{
    cv::Shell shell(NULL,argc,argv);
    //v8::Handle<v8::Object> global = shell.Global();
    shell.SetupDefaultBindings()
        ("gc", cv::FunctionToInCa<bool (),v8::V8::IdleNotification>::Call )
    ;
    try
    {
        test1(shell);
    }
    catch(std::exception const & ex)
    {
        CERR << "EXCEPTION: " << ex.what() << '\n';
        return 1;
    }
    catch(...)
    {
        CERR << "UNKNOWN EXCEPTION!\n";
        return 1;
    }
    if(0)
    {
        CERR << "Trying to force GC... This will likely take 5-10 seconds... "
             << "wait for it to see the weak pointer callbacks in action...\n"
#if 0 // this appears to have been fixed...
             << "ON SOME MACHINES THIS IS CRASHING ON ME IN V8 at some point "
             << "on 64-bit builds, but not on 32-bit...\n"
#endif
            ;
        while( !v8::V8::IdleNotification() )
        {
            CERR << "sleeping briefly before trying again...\n";
            do_sleep(1);
        }
        CERR << "v8 says GC is done.\n";
    }
    return 0;
}

int main(int argc, char const * const * argv)
{

    int const rc = v8_main(argc, argv);
    CERR << "Done! rc="<<rc<<'\n';
    return rc;
}

