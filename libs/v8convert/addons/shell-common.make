#!/do/not/make -f
########################################################################
# To be included by add-on app which want to build a basic shell
# from shell-skel/shell.cpp which includes the addon's bindings.
########################################################################
ifeq (,$(SHELL_BINDINGS_FUNC))
$(error Define SHELL_BINDINGS_FUNC to a function _name_ before including this file.)
endif

ifeq (,$(SHELL_BINDINGS_HEADER))
$(error Define SHELL_BINDINGS_HEADER to a header file containing the function defined in SHELL_BINDINGS_FUNC.)
endif

ifeq (,$(SHELL_LDFLAGS))
$(warning You have not set SHELL_LDFLAGS, which means we are not linking the shell to the add-on code.)
endif

ifeq (1,1)
  SHELL.DIR ?= ../shell-skel
#  shell.cpp: $(SHELL.DIR)/shell.cpp
#	cp $< $@
  SHELL.NAME ?= shell
  SHELL.ORIG.CPP := $(SHELL.DIR)/shell.cpp
  SHELL.LOCAL.CPP := _shell-$(SHELL.NAME).cpp
  SHELL.LOCAL.O := $(subst .cpp,.o,$(SHELL.LOCAL.CPP))
  $(SHELL.ORIG.CPP):
  $(SHELL.LOCAL.CPP): $(SHELL.ORIG.CPP)
	cp $< $@
  $(SHELL.LOCAL.O): $(SHELL.LOCAL.CPP)
  $(SHELL.NAME).BIN.OBJECTS := $(SHELL.LOCAL.O)
  $(SHELL.NAME).BIN.LDFLAGS := $(LDFLAGS_V8) $(SHELL_LDFLAGS)
  $(eval $(call ShakeNMake.CALL.RULES.BINS,$(SHELL.NAME)))
  $(SHELL.LOCAL.O): CPPFLAGS+=-DSETUP_SHELL_BINDINGS=$(SHELL_BINDINGS_FUNC)
  $(SHELL.LOCAL.O): CPPFLAGS+=-DINCLUDE_SHELL_BINDINGS='"$(SHELL_BINDINGS_HEADER)"'
  $(SHELL.LOCAL.O): $(ALL_MAKEFILES)
  $($(SHELL.NAME).BIN): $(SHELL_DEPS)
  CLEAN_FILES += $(SHELL.LOCAL.CPP) $(SHELL.LOCAL.O) $($(SHELL.NAME).BIN)
  all: $($(SHELL.NAME).BIN)
endif
