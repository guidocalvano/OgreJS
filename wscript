def set_options(opt):
  opt.tool_options("compiler_cxx")

def configure(conf):
  conf.check_tool("compiler_cxx")
  conf.check_tool("node_addon")
  conf.env.append_value('CXXFLAGS', '-arch i386'.split() )
#  conf.env.append_value('CXXFLAGS', '-arch i386')

def build(bld):
  obj = bld.new_task_gen("cxx", "shlib", "node_addon")
  obj.cxxflags = ["-g", "-D_FILE_OFFSET_BITS=64", "-D_LARGEFILE_SOURCE", "-Wall"]
  obj.env.append_value('LDFLAGS', 'ogre.o')
  obj.target = "ogre"
  obj.source = [ "ogrejsnode.cpp" ]
  obj.includes= '. ..'