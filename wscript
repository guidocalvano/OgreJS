def set_options(opt):
  opt.tool_options("compiler_cxx")

def configure(conf):
  conf.check_tool("compiler_cxx")
  conf.check_tool("node_addon")
  conf.env.append_unique('LDFLAGS', ['-flat_namespace', '-undefined', 'warning', '-arch', 'i386' ] )
  conf.env.append_value('LDFLAGS', '-arch i386'.split())
  conf.env.append_value('CXXFLAGS', '-arch i386'.split() )
  conf.env.append_value('CFLAGS', '-arch i386'.split() )
  conf.env.append_value('CCFLAGS', '-arch i386'.split() )
  conf.env.append_value('CXXFLAGS', '-arch i386'.split() )
  conf.env.append_value( 'SHCCFLAGS', ['-arch', 'i386'])
  conf.env.append_value( 'SHLINKFLAGS', ['-arch', 'i386'])
  conf.env.append_value( 'SHCCFLAGS', ['-arch', 'i386'])
  conf.env.append_value( 'LINKFLAGS', ['-arch', 'i386'])
  conf.env.append_value( 'SHCFLAGS', ['-arch', 'i386'])
  conf.env.append_value( 'SHCCFLAGS', ['-arch', 'i386'])
  conf.env.append_value( 'SHCXXFLAGS', ['-arch', 'i386'])
  conf.env.append_value( 'SHLIBFLAGS', ['-arch', 'i386'])
  conf.env.append_value( 'TARGET_ARCH', ['-arch', 'i386'])

def build(bld):
  bld.env.append_value('LDFLAGS', '-arch i386'.split())
  bld.env.append_value('CXXFLAGS', '-arch i386'.split() )
  bld.env.append_value('CFLAGS', '-arch i386'.split() )
  bld.env.append_value('CCFLAGS', '-arch i386'.split() )
  obj = bld.new_task_gen("cxx", "shlib", "node_addon")
  obj.cxxflags = ["-g", "-D_FILE_OFFSET_BITS=64", "-D_LARGEFILE_SOURCE", "-Wall"]
  # obj.env.append_value('LDFLAGS', 'ogre.o')
  obj.env.append_value('CXXFLAGS', '-arch i386'.split() )
  obj.env.append_value('CFLAGS', '-arch i386'.split() )
  obj.target = "ogre"
  obj.source = [ "ogrejsnode.cpp" ]
  obj.includes= '. ..'
  obj.env.append_value('CXXFLAGS', '-arch i386'.split() )
  obj.inputs = 'ogre.o'
  obj.uselib_local = 'ogre.o'
  obj.add_objects = 'ogre.o'
  
  # obj.add_objects = 'ogre.o' 
