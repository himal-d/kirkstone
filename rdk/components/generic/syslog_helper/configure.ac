##########################################################################
# If not stated otherwise in this file or this component's Licenses.txt
# file the following copyright and licenses apply:
#
# Copyright 2018 RDK Management
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
#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

dnl AC_PREREQ([2.69])
AC_INIT([syslog-helper], [1.0], [mani_selvaraj@comcast.com])
AC_CONFIG_SRCDIR([syslog_helper.cpp])
dnl AC_CONFIG_HEADERS([config.h])
AM_INIT_AUTOMAKE([foreign no-dist-gzip dist-bzip2 1.9])

LT_INIT
	
# Checks for programs.
AC_PROG_CXX
AC_PROG_CC
AC_PROG_INSTALL
AC_PROG_MAKE_SET
# Checks for libraries.

# Checks for header files.
AC_CHECK_HEADERS([sys/socket.h sys/time.h unistd.h])

# Checks for typedefs, structures, and compiler characteristics.

# Checks for library functions.
AC_CHECK_FUNCS([gethostname gettimeofday localtime_r memset socket])

AC_CONFIG_FILES([Makefile])
AC_OUTPUT
