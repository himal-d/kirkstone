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
SUBDIRS =
DIST_SUBDIRS =

SRCDIR = $(top_srcdir)/src

# the list of header files that belong to the library (to be installed later)
AM_CXXFLAGS = -DPLATFORM_LINUX -O2 -fPIC \
	-I$(top_srcdir)/include \
	-I${PKG_CONFIG_SYSROOT_DIR}/usr/include

AM_CFLAGS = -DPLATFORM_LINUX -O2 -fPIC \
	-I$(top_srcdir)/include \
	-I${PKG_CONFIG_SYSROOT_DIR}/usr/include

#CXX = $(CC)

bin_PROGRAMS = testSysResource
lib_LTLIBRARIES = libsysResource.la

libsysResource_la_SOURCES = $(SRCDIR)/sysResource.c \
	$(SRCDIR)/procInfo.c \
	$(SRCDIR)/simpleStats.cpp \
	$(SRCDIR)/tdiff.c
testSysResource_SOURCES = $(SRCDIR)/testSysResource.cpp
libsysResource_la_LIBADD = -lpthread
testSysResource_LDADD = libsysResource.la $(LIBS)

if ENABLE_SYS_RESOURCE_MLT
AM_CXXFLAGS += -DUSE_AVLINT -DMLT_INCREASE_THRESHOLD=5
libsysResource_la_SOURCES += $(SRCDIR)/avlTree.cpp \
        $(SRCDIR)/avlNode.cpp \
        $(SRCDIR)/mlt_malloc.cpp \
	$(SRCDIR)/rpl_new.cpp \
	$(SRCDIR)/rpl_malloc.c \
	$(SRCDIR)/zmalloc.cpp \
        $(SRCDIR)/cmaNode.cpp \
        $(SRCDIR)/sysresLogger.cpp \
        $(SRCDIR)/mltAnalyzer.cpp \
        $(SRCDIR)/cmadHandler.cpp \
        $(SRCDIR)/LinkedList.cpp \
        $(SRCDIR)/cmadLogger.cpp \
        $(SRCDIR)/backtraceHandler.cpp
testSysResource_SOURCES += $(SRCDIR)/testnew.cpp \
	$(SRCDIR)/testmalloc.c \
	$(SRCDIR)/testmalloc2.c \
	$(SRCDIR)/testcalloc.c \
	$(SRCDIR)/testcalloc2.c \
        $(SRCDIR)/testmemalign.c \
        $(SRCDIR)/testavlint.cpp \
        $(SRCDIR)/testavlint2.cpp
endif

if ENABLE_SYSMON_POLLINT
AM_CXXFLAGS +=-DSYSMON_POLLINT=$(ENABLE_SYSMON_POLLINT)
else
AM_CXXFLAGS +=-DSYSMON_POLLINT=1
endif

if ENABLE_SYS_RESOURCE_MLT
AM_CXXFLAGS +=-DUSE_SYSRES_MLT=1 -DUSE_FILE_LINE_INFO=1 -DRETURN_ADDRESS_LEVEL=0

if ENABLE_ANALYZE_IDLE_MLT
AM_CXXFLAGS += -DANALYZE_IDLE_MLT=1
else
AM_CXXFLAGS += -DANALYZE_IDLE_MLT=0
endif

if ENABLE_LNK_MLT
AM_CXXFLAGS += -DUSE_LNK_MALLOC=1
libsysResource_la_SOURCES += $(SRCDIR)/lnk_malloc.cpp
LIBS += -ldl
endif

endif

if ENABLE_FILE_WDR
AM_CXXFLAGS += -DUSE_FILE_WDR=1
libsysResource_la_SOURCES += $(SRCDIR)/debugRecord.cpp
endif

if ENABLE_CMAS
AM_CXXFLAGS += -DUSE_CMAS
if ENABLE_CMAS_CP
AM_CXXFLAGS += -DUSE_CMAS_CP
endif
if ENABLE_CMAS_IT
AM_CXXFLAGS += -DUSE_CMAS_IT -DUSE_SSTATS_FLINT
libsysResource_la_SOURCES += $(SRCDIR)/simpleStats.cpp \
	$(SRCDIR)/tdiff.c
endif
AM_CXXFLAGS += -DUSE_AVLINT
libsysResource_la_SOURCES += $(SRCDIR)/cmastats.cpp
testSysResource_SOURCES += $(SRCDIR)/testavlcmas.cpp $(SRCDIR)/testavlint.cpp
endif

if ENABLE_MLT_BACKTRACE
AM_CXXFLAGS += -DUSE_MLT_BACKTRACE -DUSE_AVLBT
libsysResource_la_SOURCES += $(SRCDIR)/backtrace.cpp
testSysResource_SOURCES += $(SRCDIR)/testavlbt.cpp
endif

if ENABLE_CMAT_SSTATS
AM_CXXFLAGS += -DUSE_CMAT_SSTATS -DUSE_SSTATS_FLINT
endif

AM_CFLAGS = $(AM_CXXFLAGS)
libsysResource_la_includedir = ${includedir}/mlt
libsysResource_la_include_HEADERS = $(top_srcdir)/include/rpl_malloc.h $(top_srcdir)/include/mlt_malloc.h $(top_srcdir)/include/sysResource.h
