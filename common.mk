

DEBUGMODE=debug
RM = rm
AR = ar


################################################################
##OgreJS vars
################################################################
OGREJS_HOME = .
SRCPATH = $(OGREJS_HOME)/src
BINPATH = $(OGREJS_HOME)/build/$(DEBUGMODE)/bin
OBJPATH = $(OGREJS_HOME)/build/$(DEBUGMODE)/obj
LIBPATH = $(OGREJS_HOME)/build/$(DEBUGMODE)/lib
LIBSPATH = $(OGREJS_HOME)/libs


OGREJS_OBJPATH = $(OBJPATH)/ogrejs
OGREJS_SRCPATH = $(SRCPATH)
LIBOGREJS = $(LIBPATH)/libogrejs.a

################################################################


################################################################
##Boost common vars
################################################################
BOOST_HOME = $(LIBSPATH)/boost_1_44_0
BOOST_CXXFLAGS = -I"$(BOOST_HOME)"
################################################################


################################################################
##Ogre common vars
################################################################
OGRE_HOME = $(LIBSPATH)/ogre
OGRE_CXXFLAGS = -I"$(OGRE_HOME)/include/OGRE" $(BOOST_CXXFLAGS)
################################################################




################################################################
##V8Convert common vars
################################################################
V8CONVERT_HOME = $(LIBSPATH)/v8convert
V8CONVERT_CXXFLAGS = -I"$(V8CONVERT_HOME)/include"
################################################################



################################################################
##V8 common vars
################################################################
V8_HOME = $(LIBSPATH)/v8
V8_SRCPATH = $(V8_HOME)/src
V8_ARCH = IA32
V8_arch = ia32
V8_CXXFLAGS = -I"$(V8_HOME)/include" \
  -DENABLE_LOGGING_AND_PROFILING -DENABLE_VMSTATE_TRACKING -DV8_TARGET_ARCH_$(V8_ARCH) \
  -DENABLE_DISASSEMBLER -DV8_ENABLE_CHECKS -DOBJECT_PRINT \
  -DENABLE_DEBUGGER_SUPPORT -DINSPECTOR -DDEBUG\
  -DWIN32 -m32 -O0 -DSTRUNCATE=80 -D__MINGW32__
V8_LDFLAGS = -m32 -lwinmm -lws2_32
V8_OBJPATH = $(OBJPATH)/v8
LIBV8 = $(LIBPATH)/libv8_$(V8_arch).a

################################################################

