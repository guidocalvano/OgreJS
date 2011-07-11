#!/usr/bin/make -f
########################################################################
# Main makefile for v8-convert.
#
# Important targets for users not hacking this source tree:
#
#  all: do everything
#  amal: build the amalgamation build
#  run: run tests (it's not called 'test' because we have a binary with
#       that name)
########################################################################
include config.make # see that file for certain configuration options.

V8_PREFIX := $(HOME)
CPPFLAGS += -I$(V8_PREFIX)/include

TMPL_GENERATOR_COUNT := 10# max number of arguments generate template specializations can handle
INCDIR_DETAIL := $(TOP_INCDIR)/v8/convert/detail
sig_gen_h := $(INCDIR_DETAIL)/signature_generated.hpp
invo_gen_h := $(INCDIR_DETAIL)/invocable_generated.hpp
conv_gen_h := $(INCDIR_DETAIL)/convert_generated.hpp
TMPL_GENERATOR := $(TOP_SRCDIR_REL)/createForwarders.sh
MAKEFILE_DEPS_LIST = $(filter-out $(ShakeNMake.CISH_DEPS_FILE),$(MAKEFILE_LIST))
createSignatureTypeList.sh:
$(sig_gen_h): $(TMPL_GENERATOR) createSignatureTypeList.sh $(MAKEFILE_DEPS_LIST)
	@echo "Creating $@ for functions taking 1 to $(TMPL_GENERATOR_COUNT) arguments..."; \
	echo "/* AUTO-GENERATED CODE! EDIT AT YOUR OWN RISK! */" > $@; \
	echo "#if !defined(DOXYGEN)" >> $@;
	@bash ./createSignatureTypeList.sh 0 $(TMPL_GENERATOR_COUNT) >> $@
	@i=1; while [ $$i -le $(TMPL_GENERATOR_COUNT) ]; do \
		bash $(TMPL_GENERATOR) $$i FunctionSignature MethodSignature ConstMethodSignature  || exit $$?; \
		i=$$((i + 1)); \
	done >> $@
	@echo "#endif // if !defined(DOXYGEN)" >> $@
gen: $(sig_gen_h)
all: $(sig_gen_h)
$(invo_gen_h): $(TMPL_GENERATOR) $(MAKEFILE_DEPS_LIST)
	@echo "Creating $@ for functions taking 1 to $(TMPL_GENERATOR_COUNT) arguments..."; \
	echo "/* AUTO-GENERATED CODE! EDIT AT YOUR OWN RISK! */" > $@; \
	echo "#if !defined(DOXYGEN)" >> $@; \
	i=1; while [ $$i -le $(TMPL_GENERATOR_COUNT) ]; do \
		bash $(TMPL_GENERATOR) $$i \
			ArgsToFunctionForwarder \
			ArgsToMethodForwarder \
		  || exit $$?; \
		i=$$((i + 1)); \
	done >> $@
	@echo "#endif // if !defined(DOXYGEN)" >> $@;
gen: $(invo_gen_h)
all: $(invo_gen_h)

$(conv_gen_h): $(TMPL_GENERATOR) $(MAKEFILE_DEPS_LIST)
	@echo "Creating $@ for functions taking 1 to $(TMPL_GENERATOR_COUNT) arguments..."; \
	echo "/* AUTO-GENERATED CODE! EDIT AT YOUR OWN RISK! */" > $@; \
	echo "#if !defined(DOXYGEN)" >> $@; \
	i=1; while [ $$i -le $(TMPL_GENERATOR_COUNT) ]; do \
		bash $(TMPL_GENERATOR) $$i \
			CtorForwarder \
		  || exit $$?; \
		i=$$((i + 1)); \
	done >> $@
	@echo "#endif // if !defined(DOXYGEN)" >> $@;
gen: $(conv_gen_h)
all: $(conv_gen_h)

V8_LDFLAGS := -L$(V8_PREFIX)/lib -lv8_g

ConvertDemo.o: ConvertDemo.cpp
demo.BIN.OBJECTS := demo.o ConvertDemo.o
demo.BIN.LDFLAGS := $(V8_LDFLAGS)
$(eval $(call ShakeNMake.EVAL.RULES.BIN,demo))
demo.o: $(sig_gen_h)

all: $(demo.BIN)


########################################################################
# Defines a target for creating TypeList_$(1).hpp
TYPELIST_GENR := $(TOP_SRCDIR_REL)/maketypelist.pl
define GEN_TYPELIST
# $1 = count
$(INCDIR_DETAIL)/TypeList_$(1).hpp: $(MAKEFILE_DEPS_LIST)
	@echo "Creating $$@"; \
		echo "#if !defined(DOXYGEN)" > $$@; \
		perl $$(TYPELIST_GENR) $(1) >> $$@ || exit $$$$?; \
		echo "#endif // if !defined(DOXYGEN)" >> $$@;
gen: $(INCDIR_DETAIL)/TypeList_$(1).hpp
endef

$(eval $(call GEN_TYPELIST,05))
$(eval $(call GEN_TYPELIST,10))
$(eval $(call GEN_TYPELIST,15))


########################################################################
# shell app...
SHELL.DIR := addons/shell-skel
SHELL_LDFLAGS := ConvertDemo.o
SHELL_BINDINGS_HEADER := ConvertDemo.hpp
SHELL_BINDINGS_FUNC := BoundNative::SetupBindings
include addons/shell-common.make
