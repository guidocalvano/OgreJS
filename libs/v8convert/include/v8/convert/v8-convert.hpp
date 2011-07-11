#if !defined(CODE_GOOGLE_COM_P_V8_CONVERT_V8_CONVERT_HPP_INCLUDED)
#define CODE_GOOGLE_COM_P_V8_CONVERT_V8_CONVERT_HPP_INCLUDED 1

/** @mainpage v8::convert API

The v8::convert namespace houses APIs for handling the following:

- Converting between v8 Value handles and "native types" using generic
interface. This allows us to write generic algorithms which convert
between JS/C++ without having to know the exact types we're dealing
with.  The basic POD types and some STL types are supported out of the
box and plugging in one's own types is normally quite simple.

- Converting free- and member functions into v8::InvocationCallback
functions. These generated functions convert the JavaScript-originated
function arguments into native counterparts, forward the data to the
original native function, and convert the return values back to
something JS can use.

Those two core features give us all we need in order to be able to
bind near-arbitrary C/C++ functions with JavaScript (where calling
conventions and type conversions allow us to do so). For cases where
the "automatic" function-to-InvocationCallback conversions are not
suitable, the type-conversion API can simplify the implementation of
custom v8::InvocationCallback functions.

All of the conversions are compile-time typesafe where possible and
fail gracefully when such a determination can only be made at runtime.

This code originated as the core-most component of the v8-juice
library (http://code.google.com/p/v8-juice). After a couple years
i felt compelled to refactor it into a toolkit usable by arbitrary
v8-using clients, doing a bit of cleanup along the way. The eventuall
intention is that this code will replace the v8::juice::convert
code.

Author: Stephan Beal (http://wanderinghorse.net/home/stephan/)

License: Dual MIT/Public Domain

Project home page: http://code.google.com/p/v8-juice/wiki/V8Convert

The most important functions and types, from a user's perspective,
include:

Converting types:

- v8::convert::CastToJS()
- v8::convert::CastFromJS()

Implementing custom conversions:

- v8::convert::NativeToJS
- v8::convert::JSToNative

Converting functions to v8::InvocationCallback:

- v8::convert::FunctionToInCa
- v8::convert::MethodToInCa
- v8::convert::ConstMethodToInCa
- v8::convert::ToInCa

Other utilities:

- CtorForwarder and CtorForwarderDispatcher
- The tmp and sl namespaces hold template metaprogramming bits.

Most of the code in this library are internal template specializations
which take care of the dirty work. Typical clients won't typically need
more than what's listed above.

A core rule of this library is "if it ain't documented, don't use 
it." All public API members which are intended for client-side use 
are documented. Some one-line proxies whose purpose is either very 
obvious, exist only for template type resolution reasons, or 
are strictly internal are not necessarily documented.

*/
#include "convert.hpp"
#include "invocable.hpp"
#include "arguments.hpp"
#include "ClassCreator.hpp"
#include "properties.hpp"
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

#endif /* CODE_GOOGLE_COM_P_V8_CONVERT_V8_CONVERT_HPP_INCLUDED */
