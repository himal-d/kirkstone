#
# Copyright 2020 Comcast Cable Communications Management, LLC
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#     http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
#
# SPDX-License-Identifier: Apache-2.0
#

AM_CFLAGS = -D_ANSC_LINUX
AM_CFLAGS += -D_ANSC_USER
AM_CFLAGS += -fPIC -fno-exceptions -Os -Wall -Wextra

AM_CXXFLAGS = -std=c++11

ACLOCAL_AMFLAGS = -I m4

AUTOMAKE_OPTIONS = subdir-objects

bin_PROGRAMS = CcspAdvSecurityDmlTest_gtest.bin

CcspAdvSecurityDmlTest_gtest_bin_CPPFLAGS = -I$(PKG_CONFIG_SYSROOT_DIR)$(includedir)/gtest \
                                            -I${top_srcdir}/gtest/include \
                                            -I${top_srcdir}/source \
                                            -I${top_srcdir}/source/AdvSecurityDml \
                                            -I${top_srcdir}/source/include

CcspAdvSecurityDmlTest_gtest_bin_SOURCES = CcspAdvSecurityMock.cpp \
                                           CcspAdvSecurityDmlTest.cpp \
                                           CcspAdvSecurityInternalTest.cpp \
                                           CcspAdvSecurityWebconfigTest.cpp \
                                           ${top_builddir}/source/AdvSecurityDml/cosa_adv_security_dml.c \
                                           ${top_builddir}/source/AdvSecurityDml/cosa_adv_security_internal.c \
                                           ${top_builddir}/source/AdvSecurityDml/advsecurity_helpers.c \
                                           ${top_builddir}/source/AdvSecurityDml/advsecurity_param.c \
                                           ${top_builddir}/source/AdvSecurityDml/cosa_adv_security_webconfig.c \
                                           ${top_builddir}/source/AdvSecurityDml/plugin_main.c \
                                           gtest_main.cpp

CcspAdvSecurityDmlTest_gtest_bin_LDFLAGS = -lgtest -lgmock -lgcov -pthread

CcspAdvSecurityDmlTest_gtest_bin_LDADD = \
    $(HOME)/usr/local/lib/libmock_syscfg.la \
    $(HOME)/usr/local/lib/libmock_secure_wrapper.la \
    $(HOME)/usr/local/lib/libmock_msgpack.la \
    $(HOME)/usr/local/lib/libmock_safec_lib.la \
    $(HOME)/usr/local/lib/libmock_webconfigframework.la \
    $(HOME)/usr/local/lib/libmock_base64.la \
    $(HOME)/usr/local/lib/libmock_rbus.la \
    $(HOME)/usr/local/lib/libmock_cm_hal.la \
    $(HOME)/usr/local/lib/libmock_platform_hal.la \
    $(HOME)/usr/local/lib/libmock_cjson.la \
    $(HOME)/usr/local/lib/libmock_sysevent.la \
    $(HOME)/usr/local/lib/libmock_ccsp_common.la

AM_CFLAGS += -fprofile-arcs -ftest-coverage
AM_CXXFLAGS += -fprofile-arcs -ftest-coverage
CcspAdvSecurityDmlTest_gtest_bin_LDFLAGS += --coverage
