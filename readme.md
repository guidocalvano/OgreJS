**Do you want to Help out?** go here-> https://github.com/guidocalvano/OgreJS/wiki/Help-out


Provided an initial example api for Vector, and a test. This can be used as boilerplate for all the classes needing to be bound.

Completed:

* Wrapped Ogre::Vector3 in juice::ogre::Vector
* Bound juice::ogre::Vector
* Bound Ogre::Real


## Dependencies

* v8
* v8convert (already in the repo)
* Ogre
* boost (for Ogre threading, if compiled with threading, and for boost::bind, which is header-only)

## To build test

<pre>
make &lt;VARS&gt; test
</pre>


Look in common.mk for what vars to set.

What I run:
<pre>
make  \
  OGRE_HOME=/d/super/dump/foundations/repo2/foundations/trunk/libs/ogre             \
  BOOST_HOME=/d/super/dump/foundations/repo2/foundations/trunk/libs/boost_1_44_0    \
  V8_HOME=/d/super/dump/foundations/libs/v8/tag.3.3.6.1                             \
  LIBV8=/d/super/dump/foundations/libs/build/lib/libv8_ia32.a test
</pre>

## To run the test
<pre>
./build/debug/bin/test/main.exe ./src/test/test.js
</pre>

## Understanding

* Take a look at /src/test/test.js, see what I am printing out. I exposed a log() function that prints to stdout.
* To see the Vector class, take a look at the header /include/juice/ogre/Vector.hpp, I left detailed docs there.
* Notice how Ogre::Real is being passed in .. no worries. This is because I define how to convert back and forth to and from JS to Ogre::Real in Real.hpp.
* Real.hpp shows how easy it is to bind POD (plain old data) that has an easy way to translate it to JS.
* Then take a look at the implementation file at /src/juice/ogre/Vector.cpp, I how the more complex class binding actually works there as well.
* Take a look at main.cpp, I explain the normal operation of v8, and show how simple it is to bind the classes to any object.
* To fully understand v8 itself, use v8.h as a reference (in the v8 project distrobution's include directory)



