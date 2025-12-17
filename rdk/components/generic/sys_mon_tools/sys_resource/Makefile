##########################################################################
# If not stated otherwise in this file or this component's Licenses.txt
# file the following copyright and licenses apply:
#
# Copyright 2016 RDK Management
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
# http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
##########################################################################

# You must define CANMORE_SDK

# If an application links against an .so (SO1) which is in turn linked against a
# 2nd .so (SO2), the link will fail if SO2 can't be found at link time.  This
# can be fixed by making sure SO2 can be found in either:
#    - the current LD_LIBRARY_PATH, or 
#    - a path in a linker -rpath option
# But it's unreasonable to expect the app writer to know all the dependencies
# of SO1 and where those files are at compile time.  The following option will
# cause the linker to ignore unresolved references from SO1 rather than failing.
SO_WORKAROUND ?= --unresolved-symbols=ignore-in-shared-libs

INCLUDES =-I. -I include/
LIBOBJLIST=
EXEOBJLIST=

ifeq ($(USE_SYSRES_PLATFORM), BROADCOM)
# Broadcom build
$(warning THIS IS A BROADCOM BUILD)
PLATFORM = broadcom
CFLAGS+=-DPLATFORM_BROADCOM -Wall -O2 -fPIC
INCLUDES+=-I${BCM_TOOLCHAIN}/include -I${BCM_TOOLCHAIN}/mipsel-linux-uclibc/sys-root/usr/include
LINK     = ${BCM_TOOLCHAIN}/bin/mipsel-linux-uclibc-g++
LIBS     = -L${BCM_TOOLCHAIN}/usr/lib -L${BCM_TOOLCHAIN}/mipsel-linux-uclibc/lib -L${BCM_TOOLCHAIN}/mipsel-linux-uclibc/sys-root/usr/lib -lpthread
TARGETCC = ${BCM_TOOLCHAIN}/bin/mipsel-linux-uclibc-gcc
AR       = ${BCM_TOOLCHAIN}/bin/mipsel-linux-uclibc-ar
OBJDUMP  = ${BCM_TOOLCHAIN}/bin/mipsel-linux-uclibc-objdump
endif

ifeq ($(USE_SYSRES_PLATFORM), CANMORE)
# Canmore build
$(warning THIS IS A CANMORE BUILD)
PLATFORM = canmore
INCLUDES+=-I${CANMORE_SDK}/include -I${CANMORE_SDK}/include/linux_user
LINK     = ${CANMORE_SDK}/bin/i686-cm-linux-g++
LIBS     = -L${CANMORE_SDK}/usr/lib -L${CANMORE_SDK}/usr/local/lib -L${CANMORE_SDK}/lib -lpthread -losal
TARGETCC = ${CANMORE_SDK}/bin/i686-cm-linux-gcc
CFLAGS+=-DPLATFORM_CANMORE -m32 -O2
CFLAGS+=-DFORMAT_ELF -D_INTERNAL_PCI_
CFLAGS+=-fno-builtin-memcpy -fno-strict-aliasing
CFLAGS+=-MD
endif

ODFFLAGS = -tC
ODFFILTER = | grep "F \.text\|O \.bss\|O \.data" | tr '\t' ' ' | tr -s ' ' | cut -d ' ' -f5- | awk '{if($$1 != 0) printf "%s %s\n", $$2, $$1}' | sort

ifeq ($(TARGETCC),)
$(error Error: Target platform is not set!)
endif
ifeq ($(BCM_TOOLCHAIN),)
$(error Error: Target platform is not set!)
endif

ifneq ($(USE_SYSMON_POLLINT),)
CFLAGS+=-DSYSMON_POLLINT=$(USE_SYSMON_POLLINT)
else
CFLAGS+=-DSYSMON_POLLINT=10
endif

ifeq ($(USE_SYS_RESOURCE_MLT), y)
CFLAGS+=-DUSE_SYSRES_MLT=1 -DUSE_FILE_LINE_INFO=1 -DRETURN_ADDRESS_LEVEL=0 -DMLT_INCREASE_THRESHOLD=5

ifeq ($(USE_ANALYZE_IDLE_MLT), y)
CFLAGS+=-DANALYZE_IDLE_MLT=1
else
CFLAGS+=-DANALYZE_IDLE_MLT=0
ifneq ($(MLT_SKIP_ITERATIONS),)
CFLAGS+=-DMLT_SKIP_ITERATIONS=$(MLT_SKIP_ITERATIONS)
else
CFLAGS+=-DMLT_SKIP_ITERATIONS=0
endif
endif

ifeq ($(USE_LNK_MLT), y)
CFLAGS+=-DUSE_LNK_MALLOC=1
LIBS+= -L${BCM_TOOLCHAIN}/mipsel-linux-uclibc/sys-root/usr/lib -ldl
endif

endif

ifeq ($(USE_CMAS), y)
CFLAGS+=-DUSE_CMAS
ifeq ($(USE_CMAS_CP), y)
CFLAGS+=-DUSE_CMAS_CP
endif
ifeq ($(USE_CMAS_IT), y)
CFLAGS+=-DUSE_CMAS_IT -DUSE_SSTATS_FLINT
LIBOBJLIST+=simpleStats.o tdiff.o eltAnalyzer.o
endif
LIBOBJLIST+=cmastats.o cmasAnalyzer.o sysresLogger.o
EXEOBJLIST+=testavlcmas.o
ifeq ($(USE_CMAS_BACKTRACE), y)
LIBOBJLIST+=avlTree.o avlNode.o
ifneq ($(USE_CMAS_BACKTRACE_COUNT),)
CFLAGS+=-DUSE_CMAS_BACKTRACE_COUNT=$(USE_CMAS_BACKTRACE_COUNT)
else
CFLAGS+=-DUSE_CMAS_BACKTRACE_COUNT=30
endif
endif
endif

ifeq ($(findstring y, $(USE_SYS_RESOURCE_MLT) $(USE_CMAS) $(USE_MLT_BACKTRACE) $(USE_CMAS_BACKTRACE)), y)
USE_AVLINT=y
LIBOBJLIST+=avlTree.o avlNode.o sysresLogger.o
endif

ifeq ($(USE_AVLINT), y)
CFLAGS+=-DUSE_AVLINT
EXEOBJLIST+=testavlint.o testavlint2.o
endif

ifeq ($(USE_MLT_BACKTRACE), y)
CFLAGS+=-DUSE_MLT_BACKTRACE -DUSE_AVLBT
endif
ifeq ($(USE_CMAS_BACKTRACE), y)
CFLAGS+=-DUSE_CMAS_BACKTRACE -DUSE_AVLBT
LIBOBJLIST+=cmasmfcHandler.o
endif
ifeq ($(findstring y, $(USE_MLT_BACKTRACE) $(USE_CMAS_BACKTRACE)), y)
LIBOBJLIST+=backtrace.o backtraceHandler.o
EXEOBJLIST+=testavlbt.o
endif

ifeq ($(USE_CMAT_SSTATS), y)
CFLAGS+=-DUSE_CMAT_SSTATS -DUSE_SSTATS_FLINT
LIBOBJLIST+=simpleStats.o tdiff.o eltAnalyzer.o sysresLogger.o
endif

ifeq ($(USE_FILE_WDR), y)
CFLAGS+=-DUSE_FILE_WDR=1
endif

ifeq ($(DEBUG), y)
$(warning THIS IS A DEBUG BUILD)
CFLAGS+=-g -ggdb -DDEBUG=1
OBJDIR=bin/dbg
else
$(warning THIS IS A RELEASE BUILD)
OBJDIR=bin/rel
endif

ifeq ($(USE_DEADCODESTRIP), y)
CFLAGS+=-fdata-sections -ffunction-sections
LFLAGS+=-Wl,--gc-sections
endif
ifeq ($(TEST_DEADCODESTRIP), y)
CFLAGS+=-DTEST_DEADCODESTRIP
LIBOBJLIST+=deadCodeAndDataFile.o deadCodeRefedDataFile.o deadCodeLibRefedDataFile.o
endif

SOURCEDIR=src
LIBOBJLIST+=sysResource.o procInfo.o
EXEOBJLIST+=testSysResource.o
ifeq ($(USE_SYS_RESOURCE_MLT), y)
LIBOBJLIST+=mlt_malloc.o rpl_new.o rpl_malloc.o mltAnalyzer.o cmaNode.o LinkedList.o cmadHandler.o cmadLogger.o zmalloc.o
EXEOBJLIST+=testnew.o testmalloc.o testmalloc2.o testcalloc.o testcalloc2.o testmemalign.o
ifeq ($(USE_LNK_MLT), y)
LIBOBJLIST+= lnk_malloc.o
endif
endif
ifeq ($(USE_FILE_WDR), y)
LIBOBJLIST+= debugRecord.o
endif

ifeq ($(TEST_FMP), y)
USE_FMP=y
CFLAGS+=-DTEST_FMP -DSIMPLE_FMP_TEST
EXEOBJLIST+= testfixedSizePartition.o procStatmS.o
endif

ifeq ($(USE_FMP), y)
CFLAGS+=-DUSE_CUSTOM_MM=1 -DUSE_FIXED_SIZE_PARTITION=1
LIBOBJLIST+= fixedSizePartition.o cnew.o
endif

ifeq ($(TEST_LL), y)
CFLAGS+=-DTEST_LL
EXEOBJLIST+=testHLL.o testSLL.o
endif

LIBDIR = lib/platform/$(PLATFORM)
STATICLIB = $(LIBDIR)/libsysResource.a
SHAREDLIB = $(LIBDIR)/libsysResource.so
RDFSHAREDLIB=$(LIBDIR)/libsysResource.rdf.so
USHAREDLIB = $(LIBDIR)/libsysResource.u.so
EXETARGET = $(OBJDIR)/testSysResource
EXETARGETU = $(OBJDIR)/testSysResource.u
ODFTARGET = $(EXETARGET).odf

LIBOBJECTS=$(addprefix $(OBJDIR)/,$(LIBOBJLIST))
EXEOBJECTS=$(addprefix $(OBJDIR)/,$(EXEOBJLIST))
ODFOBJECTS=$(addsuffix .odf,$(LIBOBJECTS)) ##$(addsuffix .odf,$(EXEOBJECTS))
ODFUNUSED=$(addsuffix .unused,$(ODFOBJECTS))
ODFUSED=$(addsuffix .used,$(ODFOBJECTS))

RDFUNMOBJECTS=$(shell [ -e $(SHAREDLIB).edfa.used-unmodified ] && cat $(SHAREDLIB).edfa.used-unmodified)
RDFSRCOBJECTS=$(shell [ -e $(SHAREDLIB).edfa.used.rdfsrc ] && cat $(SHAREDLIB).edfa.used.rdfsrc)
RDFTBBOBJECTS=$(patsubst %.cpp, %.o, $(filter %.cpp, $(addprefix $(OBJDIR)/,$(notdir $(RDFSRCOBJECTS))))) $(patsubst %.c, %.o, $(filter %.c, $(addprefix $(OBJDIR)/,$(notdir $(RDFSRCOBJECTS)))))
RDFLIBOBJECTS=$(shell test -e $(SHAREDLIB).edfa.used.rdfsrc && echo $(RDFTBBOBJECTS) $(RDFUNMOBJECTS) || cat $(SHAREDLIB).edfa.used)

.PHONY: all
all: $(LIBDIR) $(OBJDIR) $(SHAREDLIB) ##$(EXETARGET)
	@echo "Env   options: USE_SYSRES_PLATFORM=$(USE_SYSRES_PLATFORM) USE_SYS_RESOURCE_MLT=$(USE_SYS_RESOURCE_MLT) USE_ANALYZE_IDLE_MLT=$(USE_ANALYZE_IDLE_MLT) USE_CMAS/CP/IT=$(USE_CMAS)/$(USE_CMAS_CP)/$(USE_CMAS_IT) USE_CMAT_SSTATS=$(USE_CMAT_SSTATS) USE_SYSMON_POLLINT=$(USE_SYSMON_POLLINT) USE_LNK_MLT=$(USE_LNK_MLT) USE_MLT_BACKTRACE=$(USE_MLT_BACKTRACE) USE_CMAS_BACKTRACE=$(USE_CMAS_BACKTRACE) USE_CMAS_BACKTRACE_COUNT=$(USE_CMAS_BACKTRACE_COUNT) USE_AVLINT=$(USE_AVLINT) USE_FILE_WDR=$(USE_FILE_WDR) DEBUG=$(DEBUG) USE_DEADCODESTRIP=$(USE_DEADCODESTRIP)"
	@echo "Build options: CFLAGS = " $(CFLAGS)
	@echo "Build options: LFLAGS = " $(LFLAGS)

all.nodf: $(LIBDIR) $(OBJDIR) $(STATICLIB) $(ODFOBJECTS) $(EXETARGET) $(ODFTARGET) $(ODFUNUSED) $(ODFUSED) $(USHAREDLIB) $(EXETARGETU)
	@echo "Env   options: USE_SYSRES_PLATFORM=$(USE_SYSRES_PLATFORM) USE_SYS_RESOURCE_MLT=$(USE_SYS_RESOURCE_MLT) USE_ANALYZE_IDLE_MLT=$(USE_ANALYZE_IDLE_MLT) USE_CMAS/CP/IT=$(USE_CMAS)/$(USE_CMAS_CP)/$(USE_CMAS_IT) USE_CMAT_SSTATS=$(USE_CMAT_SSTATS) USE_SYSMON_POLLINT=$(USE_SYSMON_POLLINT) USE_LNK_MLT=$(USE_LNK_MLT) USE_MLT_BACKTRACE=$(USE_MLT_BACKTRACE) USE_CMAS_BACKTRACE=$(USE_CMAS_BACKTRACE) USE_CMAS_BACKTRACE_COUNT=$(USE_CMAS_BACKTRACE_COUNT) USE_AVLINT=$(USE_AVLINT) USE_FILE_WDR=$(USE_FILE_WDR) DEBUG=$(DEBUG) USE_DEADCODESTRIP=$(USE_DEADCODESTRIP)"
	@echo "Build options: CFLAGS = " $(CFLAGS)
	@echo "Build options: LFLAGS = " $(LFLAGS)

all.rdf: $(LIBDIR) $(OBJDIR) $(STATICLIB) $(EXETARGET) $(EXETARGET).libs $(SHAREDLIB).edfa.used rdflibobjs
	@echo "Env   options: USE_SYSRES_PLATFORM=$(USE_SYSRES_PLATFORM) USE_SYS_RESOURCE_MLT=$(USE_SYS_RESOURCE_MLT) USE_ANALYZE_IDLE_MLT=$(USE_ANALYZE_IDLE_MLT) USE_CMAS/CP/IT=$(USE_CMAS)/$(USE_CMAS_CP)/$(USE_CMAS_IT) USE_CMAT_SSTATS=$(USE_CMAT_SSTATS) USE_SYSMON_POLLINT=$(USE_SYSMON_POLLINT) USE_LNK_MLT=$(USE_LNK_MLT) USE_MLT_BACKTRACE=$(USE_MLT_BACKTRACE) USE_CMAS_BACKTRACE=$(USE_CMAS_BACKTRACE) USE_CMAS_BACKTRACE_COUNT=$(USE_CMAS_BACKTRACE_COUNT) USE_AVLINT=$(USE_AVLINT) USE_FILE_WDR=$(USE_FILE_WDR) DEBUG=$(DEBUG) USE_DEADCODESTRIP=$(USE_DEADCODESTRIP)"
	@echo "Build options: CFLAGS = " $(CFLAGS)
	@echo "Build options: LFLAGS = " $(LFLAGS)
	@echo "Building rdf shared lib $(RDFSHAREDLIB) from RDFLIBOBJECTS ..."
	@echo "RDFLIBOBJECTS: " $(RDFLIBOBJECTS)
	$(LINK) $(CFLAGS) -shared -o $(RDFSHAREDLIB) $(RDFLIBOBJECTS)
	@echo "Rebuilding executable with rdf shared lib..."
	$(LINK) $(LFLAGS) -o $(EXETARGET).rdf $(EXEOBJECTS) $(RDFSHAREDLIB) $(LIBS)

$(EXETARGET).libs: $(SHAREDLIB)
	@echo "Build " $(EXETARGET).libs
	@echo "$(SHAREDLIB)" > $(EXETARGET).libs

$(SHAREDLIB).edfa.used: $(LIBOBJECTS)
	@echo "$(LIBOBJECTS)" | tr ' ' '\n' > $(STATICLIB).obj
	scripts/host/edfAnalyzer.sh -e $(EXETARGET) -f $(STATICLIB).obj -l $(EXETARGET).libs -V -s -r2 #-x libsysResource.so.ods.excs

config:
	@echo "SOURCEDIR    :" $(SOURCEDIR)
	@echo "OBJDIR       :" $(OBJDIR)
	@echo "LIBOBJECTS   :" $(LIBOBJECTS)
	@echo "EXEOBJECTS   :" $(EXEOBJECTS)
	@echo "SHAREDLIB    :" $(SHAREDLIB)
	@echo "EXETARGET    :" $(EXETARGET)
	@echo "RDFSRCOBJECTS:" $(RDFSRCOBJECTS)
	@echo "RDFTBBOBJECTS:" $(RDFTBBOBJECTS)
	@echo "RDFUNMOBJECTS:" $(RDFUNMOBJECTS)
	@echo "RDFLIBOBJECTS:" $(RDFLIBOBJECTS)
##	@echo "RDFLIBOBJECTS:" $$(test -e $(SHAREDLIB).ods.lib-unused.src && echo $(RDFTBBOBJECTS) $(RDFUNMOBJECTS) || cat $(SHAREDLIB).edfa.used )
##	@echo "ODFOBJECTS   :" $(ODFOBJECTS)
##	@echo "ODFTARGET    :" $(ODFTARGET)
##	@echo "ODFUNUSED    :" $(ODFUNUSED)
##	@echo "ODFUSED      :" $(ODFUSED)
	@echo "Env   options: USE_SYSRES_PLATFORM=$(USE_SYSRES_PLATFORM) USE_SYS_RESOURCE_MLT=$(USE_SYS_RESOURCE_MLT) USE_ANALYZE_IDLE_MLT=$(USE_ANALYZE_IDLE_MLT) USE_CMAS/CP/IT=$(USE_CMAS)/$(USE_CMAS_CP)/$(USE_CMAS_IT) USE_CMAT_SSTATS=$(USE_CMAT_SSTATS) USE_SYSMON_POLLINT=$(USE_SYSMON_POLLINT) USE_LNK_MLT=$(USE_LNK_MLT) USE_MLT_BACKTRACE=$(USE_MLT_BACKTRACE) USE_CMAS_BACKTRACE=$(USE_CMAS_BACKTRACE) USE_CMAS_BACKTRACE_COUNT=$(USE_CMAS_BACKTRACE_COUNT) USE_AVLINT=$(USE_AVLINT) USE_FILE_WDR=$(USE_FILE_WDR) DEBUG=$(DEBUG) USE_DEADCODESTRIP=$(USE_DEADCODESTRIP)"
	@echo "Build options: CFLAGS = " $(CFLAGS)
	@echo "Build options: LFLAGS = " $(LFLAGS)

$(LIBDIR):
	@[ -d $(LIBDIR) ] || mkdir -p $(LIBDIR)

$(OBJDIR):
	@[ -d $(OBJDIR) ] || mkdir -p $(OBJDIR)

$(SHAREDLIB) : $(LIBOBJECTS)
	@echo "Building shared lib..."
	$(LINK) $(CFLAGS) -shared -o $(SHAREDLIB) $^
	@$(OBJDUMP) $(ODFFLAGS) $(SHAREDLIB) $(ODFFILTER) > $(SHAREDLIB).odf

$(EXETARGET): $(EXEOBJECTS) $(LIBOBJECTS)
	@echo "Building executable..."
	$(LINK) $(LFLAGS) -o $(EXETARGET) $(EXEOBJECTS) -L$(LIBDIR) -lsysResource $(LIBS)

$(EXETARGETU): $(EXEOBJECTS) $(USHAREDLIB)
	@echo "Rebuilding executable with nodf shared lib..."
	$(LINK) $(LFLAGS) -o $(EXETARGET) $(EXEOBJECTS) -L$(LIBDIR) -lsysResource $(LIBS)

$(STATICLIB) : $(LIBOBJECTS)
	$(AR) rcs $(STATICLIB) $^

$(USHAREDLIB) : $(ODFUSED)
	@echo "Building nodf shared lib..."
	$(LINK) $(CFLAGS) -shared -o $(SHAREDLIB) $(shell ls -la bin/dbg/*.odf.used | awk '{if ($$5 != 0) { gsub (/.odf.used/,""); print $$9}}' | tr '\n' ' ')
	@$(OBJDUMP) $(ODFFLAGS) $(SHAREDLIB) $(ODFFILTER) > $(SHAREDLIB).odf

$(ODFTARGET): $(EXETARGET)
	@$(OBJDUMP) $(ODFFLAGS) $(EXETARGET) $(ODFFILTER) > $(EXETARGET).odf

$(OBJDIR)/%.o.odf.used: $(OBJDIR)/%.o.odf
	@comm -12 $(ODFTARGET) $< > $(@D)/$(@F)

$(OBJDIR)/%.o.odf.unused: $(OBJDIR)/%.o.odf
	@comm -13 $(ODFTARGET) $< > $(@D)/$(@F)

$(OBJDIR)/%.o: $(SOURCEDIR)/%.c
	$(TARGETCC) -c $(CFLAGS) $(INCLUDES) $< -o $(@D)/$(@F)

$(OBJDIR)/%.o: $(SOURCEDIR)/%.cpp
	$(TARGETCC) -c $(CFLAGS) $(INCLUDES) $< -o $(@D)/$(@F)

rdflibobjs:
	@echo "Building rdf r2 lib objects : $(RDFTBBOBJECTS) ..."
	make $(RDFTBBOBJECTS)

$(OBJDIR)/%.rdf.o: $(SOURCEDIR)/%.rdf.cpp
	$(TARGETCC) -c $(CFLAGS) $(INCLUDES) $< -o $(@D)/$(@F)

$(OBJDIR)/%.rdf.o: $(SOURCEDIR)/%.rdf.c
	$(TARGETCC) -c $(CFLAGS) $(INCLUDES) $< -o $(@D)/$(@F)

$(OBJDIR)/%.o.odf: $(OBJDIR)/%.o
	@$(OBJDUMP) $(ODFFLAGS) $< $(ODFFILTER) > $(@D)/$(@F)

clean:
	$(RM) -rf bin $(SHAREDLIB)* $(RDFSHAREDLIB) $(STATICLIB)* $(EXETARGET)* $(SOURCEDIR)/*.cpp.* $(SOURCEDIR)/*.c.* $(SOURCEDIR)/*.rdf.*

