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
AM_CFLAGS =
AM_LDFLAGS = -lccsp_common -lwebconfig_framework -lmsgpackc -ltrower-base64

AM_CPPFLAGS = -Wall -Werror
ACLOCAL_AMFLAGS = -I m4
hardware_platform = i686-linux-gnu

lib_LTLIBRARIES = libdmlxdns.la
libdmlxdns_la_CPPFLAGS = -I$(top_srcdir)/include -I$(top_srcdir)/source/dmlxdns -I$(top_srcdir)/source/XdnsSsp -I${PKG_CONFIG_SYSROOT_DIR}$(includedir)/rbus $(CPPFLAGS)
libdmlxdns_la_SOURCES = cosa_apis_util.c cosa_xdns_webconfig_api.c xdns_param.c xdns_comp_helpers.c plugin_main.c cosa_apis_util_priv.c cosa_apis_busutil.c plugin_main_apis.c cosa_xdns_apis.c cosa_xdns_dml.c
libdmlxdns_la_LDFLAGS = -lccsp_common -lsyscfg -lsysevent -lutapi -lutctx -lwebconfig_framework -lmsgpackc -ltrower-base64 -lrbus -lsecure_wrapper
