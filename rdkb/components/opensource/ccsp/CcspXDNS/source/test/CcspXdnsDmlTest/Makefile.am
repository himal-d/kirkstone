##########################################################################
# If not stated otherwise in this file or this component's LICENSE
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

AM_CFLAGS = -D_ANSC_LINUX
AM_CFLAGS += -D_ANSC_USER
AM_CFLAGS += -fPIC -fno-exceptions -Os -Wall -Wextra

AM_CXXFLAGS = -std=c++11

ACLOCAL_AMFLAGS = -I m4

AUTOMAKE_OPTIONS = subdir-objects

bin_PROGRAMS = CcspXdnsDmlTest_gtest.bin

CcspXdnsDmlTest_gtest_bin_CPPFLAGS = \
    -I$(PKG_CONFIG_SYSROOT_DIR)$(includedir)/gtest \
    -I${top_srcdir}/gtest/include \
    -I${top_srcdir}/include \
    -I${top_srcdir}/source \
    -I$(top_srcdir)/source/dmlxdns

CcspXdnsDmlTest_gtest_bin_CPPFLAGS += \
    -DWAN_FAILOVER_SUPPORTED \
    -D_CBR_PRODUCT_REQ_ \
    -DFEATURE_IPV6

CcspXdnsDmlTest_gtest_bin_SOURCES = \
    CcspXdnsMock.cpp \
    CcspXdnsCosaDmlTest.cpp \
    CcspXdnsCosaApisTest.cpp \
    CcspXdnsCosaWebconfigApiTest.cpp \
    CcspXdnsCosaApiUtilPrivTest.cpp \
    CcspXdnsCosaApiUtilTest.cpp \
    CcspXdnsPluginMainApisTest.cpp \
    ${top_builddir}/source/dmlxdns/cosa_apis_util.c \
    ${top_builddir}/source/dmlxdns/cosa_xdns_webconfig_api.c \
    ${top_builddir}/source/dmlxdns/xdns_param.c \
    ${top_builddir}/source/dmlxdns/xdns_comp_helpers.c \
    ${top_builddir}/source/dmlxdns/cosa_apis_util_priv.c \
    ${top_builddir}/source/dmlxdns/cosa_apis_busutil.c \
    ${top_builddir}/source/dmlxdns/plugin_main_apis.c \
    ${top_builddir}/source/dmlxdns/cosa_xdns_apis.c \
    ${top_builddir}/source/dmlxdns/cosa_xdns_dml.c \
    gtest_main.cpp

CcspXdnsDmlTest_gtest_bin_LDADD = \
    $(HOME)/usr/local/lib/libmock_ccsp_common.la \
    $(HOME)/usr/local/lib/libmock_secure_wrapper.la \
    $(HOME)/usr/local/lib/libmock_safec_lib.la \
    $(HOME)/usr/local/lib/libmock_syscfg.la \
    $(HOME)/usr/local/lib/libmock_base64.la \
    $(HOME)/usr/local/lib/libmock_webconfigframework.la \
    $(HOME)/usr/local/lib/libmock_msgpack.la \
    $(HOME)/usr/local/lib/libmock_sysevent.la \
    $(HOME)/usr/local/lib/libmock_utopia.la \
    $(HOME)/usr/local/lib/libmock_rbus.la \
    $(HOME)/usr/local/lib/libmock_file_io.la \
    $(HOME)/usr/local/lib/libmock_socket.la \
    $(HOME)/usr/local/lib/libmock_fd.la

CcspXdnsDmlTest_gtest_bin_LDFLAGS = -lgtest -lgmock -lgcov -pthread

#code coverage flags
AM_CFLAGS += -fprofile-arcs -ftest-coverage
AM_CXXFLAGS += -fprofile-arcs -ftest-coverage
CcspXdnsDmlTest_gtest_bin_LDFLAGS += --coverage