import platform
import re
import sys
import os



env = Environment()

if platform == 'darwin':
    env.AppendUnique( SHCCFLAGS =['-arch', 'i386'])
    env.AppendUnique( SHLINKFLAGS = ['-arch', 'i386'])
    env.AppendUnique( CCFLAGS = ['-arch', 'i386'])
    env.AppendUnique( CXXFLAGS = ['-arch', 'i386'])
    env.AppendUnique( LINKFLAGS = ['-arch', 'i386'])


OBS = []


if platform == 'darwin':

    env[ 'FRAMEWORKS' ].append( '-framework Foundation' ) 

    env[ 'FRAMEWORKS' ].append( '-framework IOKit' ) 

    env[ 'FRAMEWORKS' ].append( '-framework Carbon' ) 

    env[ 'FRAMEWORKS' ].append( '-framework Cocoa' ) 

    env[ 'FRAMEWORKS' ].append( '-framework SDL' ) 


# boost


boost_incdir = os.path.abspath('../boost_1_46_1')
boost_libdir = os.path.abspath('../boost_1_46_1/lib/')

env[ 'CPPPATH' ].append( os.path.abspath('../boost_1_46_1') ) 

env[ 'LIBPATH' ].append( os.path.abspath('../boost_1_46_1/lib/') ) 

OBS.append( 'boost_date_time-xgcc42-mt-1_46_1' ) ;
OBS.append( 'boost_thread-xgcc42-mt-1_46_1' ) ;


# free type

env[ 'LIBS' ].append( 'freetype' )

# free image

env[ 'LIBS' ].append( 'freeimage' )

# zzip

env[ 'LIBS' ].append( 'zzip' )


# gcc

env[ 'LIBS' ].append( 'gcc' )

# ogre

env[ 'CPPPATH' ].append( os.path.abspath( '../OgreSDK/include/' ) )
OBS.append( '../OgreSDK/lib/release/Ogre.framework/Ogre' )



# v8

env[ 'CPPPATH' ].append( os.path.abspath('../node/deps/v8include') )
env[ 'LIBPATH' ].append( os.path.abspath('../node/build/default')  )
env[ 'LIBS' ].append( 'v8' ) 


# juice

env[ 'CPPPATH' ].append( os.path.abspath( '../libv8-juice-20101126' ) )
env[ 'LIBPATH' ].append( os.path.abspath( '../libv8-juice-20101126/src/include' ) )
env[ 'LIBS' ].append( 'v8-juice' ) 


env.StaticLibrary( 'ogrejs.cpp', OBS ) 

# node

env[ 'CPPPATH' ].append( os.path.abspath( '../node/src' ) )
env[ 'LIBPATH' ].append( os.path.abspath( '../node/build/default' ) )
env[ 'LIBS' ].append( 'node' ) 

env.SharedLibrary( 'ogrejsnode.cpp', OBS ) 
