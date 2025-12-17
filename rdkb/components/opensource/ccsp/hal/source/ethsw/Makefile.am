##########################################################################
# If not stated otherwise in this file or this component's Licenses.txt
# file the following copyright and licenses apply:
#
# Copyright 2015 RDK Management
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

ACLOCAL_AMFLAGS = -I m4

lib_LTLIBRARIES = libhal_ethsw.la

libhal_ethsw_la_CPPFLAGS =
libhal_ethsw_la_SOURCES = ccsp_hal_ethsw.c
libhal_ethsw_la_LDFLAGS =

bin_PROGRAMS = eth_api

eth_api_CPPFLAGS =
eth_api_SOURCES = eth_api.c
eth_api_LDFLAGS = -lhal_ethsw
eth_api_LDADD = libhal_ethsw.la
