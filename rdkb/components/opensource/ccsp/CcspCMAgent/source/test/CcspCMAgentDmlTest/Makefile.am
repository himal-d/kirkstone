####################################################################################
# If not stated otherwise in this file or this component's Licenses.txt file the
# following copyright and licenses apply:
#
# Copyright 2024 RDK Management
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
####################################################################################

AM_CFLAGS = -D_ANSC_LINUX
AM_CFLAGS += -D_ANSC_USER
AM_CFLAGS += -fPIC -fno-exceptions -Os -Wall -Wextra

AM_CXXFLAGS = -std=c++11

ACLOCAL_AMFLAGS = -I m4

AUTOMAKE_OPTIONS = subdir-objects

bin_PROGRAMS = CcspCMAgentDmlTest_gtest.bin

CcspCMAgentDmlTest_gtest_bin_CPPFLAGS = \
    -I$(PKG_CONFIG_SYSROOT_DIR)$(includedir)/gtest \
    -I${top_srcdir}/gtest/include \
    -I${top_srcdir}/source \
    -I$(top_srcdir)/source/TR-181/board_sbapi \
    -I${top_srcdir}/source/TR-181/middle_layer_src \
    -I${top_srcdir}/source/TR-181/integration_src.shared \
    -I${top_srcdir}/source/TR-181/include \
    -I${top_srcdir}/source/Custom

CcspCMAgentDmlTest_gtest_bin_CPPFLAGS += \
    -DRBUS_BUILD_FLAG_ENABLE \
    -DENABLE_LLD_SUPPORT \
    -DWAN_FAILOVER_SUPPORTED \
    -DFEATURE_RDKB_WAN_MANAGER \
    -D_CM_HIGHSPLIT_SUPPORTED_

CcspCMAgentDmlTest_gtest_bin_SOURCES = \
    CcspCMAgentMock.cpp \
    CcspCMAgentDeviceInfoDmlTest.cpp \
    CcspCMAgentDeviceInfoInternalTest.cpp \
    CcspCMAgentRdkCentralCableModemDmlTest.cpp \
    CcspCMAgentRdkCentralCableModemInternalTest.cpp \
    CcspCMAgentXCiscoComCableModemDmlFirstTest.cpp \
    CcspCMAgentXCiscoComCableModemDmlSecondTest.cpp \
    CcspCMAgentWebconfigApi.cpp \
    CcspCMAgentRbusHandlerApisTest.cpp \
    ${top_srcdir}/source/TR-181/middle_layer_src/plugin_main.c \
    ${top_srcdir}/source/TR-181/middle_layer_src/plugin_main_apis.c \
    ${top_srcdir}/source/TR-181/middle_layer_src/cosa_cm_common.c \
    ${top_srcdir}/source/TR-181/middle_layer_src/cosa_x_cisco_com_cablemodem_dml.c \
    ${top_srcdir}/source/TR-181/middle_layer_src/cosa_x_cisco_com_cablemodem_internal.c \
    ${top_srcdir}/source/TR-181/middle_layer_src/cosa_device_info_dml.c \
    ${top_srcdir}/source/TR-181/middle_layer_src/cosa_device_info_internal.c \
    ${top_srcdir}/source/TR-181/middle_layer_src/cosa_x_rdkcentral_com_cablemodem_dml.c \
    ${top_srcdir}/source/TR-181/middle_layer_src/cosa_x_rdkcentral_com_cablemodem_internal.c \
    ${top_srcdir}/source/TR-181/middle_layer_src/cm_agent_webconfig_api.c \
    ${top_srcdir}/source/TR-181/middle_layer_src/cmagent_helpers.c \
    ${top_srcdir}/source/TR-181/middle_layer_src/cmagent_param.c \
    ${top_srcdir}/source/TR-181/middle_layer_src/cosa_rbus_handler_apis.c \
    ${top_srcdir}/source/TR-181/integration_src.shared/cosa_x_cisco_com_cablemodem_apis.c \
    ${top_srcdir}/source/TR-181/integration_src.shared/cosa_device_info_apis.c \
    ${top_srcdir}/source/TR-181/integration_src.shared/cosa_x_rdkcentral_com_cablemodem_apis.c \
    gtest_main.cpp

CcspCMAgentDmlTest_gtest_bin_LDFLAGS = -lgtest -lgmock -lgcov -pthread --coverage

CcspCMAgentDmlTest_gtest_bin_LDADD = \
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
    $(HOME)/usr/local/lib/libmock_ccsp_common.la \
    $(HOME)/usr/local/lib/libmock_util.la \
    $(HOME)/usr/local/lib/libmock_utopia.la
    
AM_CFLAGS += -fprofile-arcs -ftest-coverage
AM_CXXFLAGS += -fprofile-arcs -ftest-coverage
CcspCMAgentDmlTest_gtest_bin_LDFLAGS += --coverage