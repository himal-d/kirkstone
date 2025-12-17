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
dnl                                               -*- Autoconf -*-
dnl Process this file with autoconf to produce a configure script.

dnl AC_PREREQ([2.69])
AC_PREREQ([2.68])
AC_INIT([sysResource], [1.0], [ridish.ra@lntteschservices.com])
AC_CONFIG_SRCDIR([src/mlt_malloc.cpp])

AC_CONFIG_MACRO_DIR([m4])
AC_CONFIG_AUX_DIR([cfg])
AM_INIT_AUTOMAKE([foreign no-dist-gzip dist-bzip2 1.9])
AC_CONFIG_HEADERS([cfg/config.h])

LT_INIT

m4_ifdef([AM_SILENT_RULES],[AM_SILENT_RULES([yes])],
[AM_DEFAULT_VERBOSITY=1
AC_SUBST(AM_DEFAULT_VERBOSITY)])

# Checks for programs.
AC_PROG_CC
AC_PROG_CXX


# Checks for libraries.

# Checks for header files.
AC_CHECK_HEADERS([locale.h stdlib.h unistd.h])
#PKG_CHECK_MODULES([GLIB], [glib-2.0 >= 2.24.0])
#PKG_CHECK_MODULES([GTHREAD], [gthread-2.0 >= 2.24.0])

AC_CHECK_LIB(gthread-2.0, g_thread_init)

# Checks for typedefs, structures, and compiler characteristics.
AC_TYPE_PID_T
AC_TYPE_SIZE_T

ENABLE_SYS_RESOURCE_MLT=" "
ENABLE_SYSMON_POLLINT=" "
ENABLE_ANALYZE_IDLE_MLT=" "
ENABLE_LNK_MLT=" "
ENABLE_FILE_WDR=" "
ENABLE_CMAS_CP=" "
ENABLE_CMAS_IT=" "
ENABLE_MLT_BACKTRACE=" "
ENABLE_CMAT_SSTATS=" "

AC_ARG_ENABLE([sys-resource-mlt],
              AS_HELP_STRING([--enable-sys-resource-mlt],[enable sys-resource-mlt (default is no)]),
              [
                case "${enableval}" in
                 yes) ENABLE_SYS_RESOURCE_MLT=true;;
                 no)  ENABLE_SYS_RESOURCE_MLT=false
		      AC_MSG_NOTICE([sys-resource-mlt is disabled]) ;;
                 *) AC_MSG_ERROR([bad value ${enableval} for --enable-sys-resource-mlt]) ;;
                esac
              ],
              [echo "sys-resource-mlt is disabled"])
AM_CONDITIONAL([ENABLE_SYS_RESOURCE_MLT],[test x$ENABLE_SYS_RESOURCE_MLT = xtrue])

AC_ARG_ENABLE([sysmon-pollint],
              AS_HELP_STRING([--enable-sysmon-pollint],[enable sysmon-pollint (default is no)]),
              [
                case "${enableval}" in
                 yes) ENABLE_SYSMON_POLLINT=true;;
                 no)  ENABLE_SYSMON_POLLINT=false
		      AC_MSG_NOTICE([sysmon-pollint is disabled]) ;;
                 *) AC_MSG_ERROR([bad value ${enableval} for --enable-sysmon-pollint]) ;;
                esac
              ],
              [echo "sysmon-pollint is disabled"])
AM_CONDITIONAL([ENABLE_SYSMON_POLLINT],[test x$ENABLE_SYSMON_POLLINT = xtrue])

AC_ARG_ENABLE([analyze-idle-mlt],
              AS_HELP_STRING([--enable-analyze-idle-mlt],[enable analyze-idle-mlt (default is no)]),
              [
                case "${enableval}" in
                 yes) ENABLE_ANALYZE_IDLE_MLT=true;;
                 no)  ENABLE_ANALYZE_IDLE_MLT=false
		      AC_MSG_NOTICE([analyze-idle-mlt is disabled]) ;;
                 *) AC_MSG_ERROR([bad value ${enableval} for --enable-analyze-idle-mlt]) ;;
                esac
              ],
              [echo "analyze-idle-mlt is disabled"])
AM_CONDITIONAL([ENABLE_ANALYZE_IDLE_MLT],[test x$ENABLE_ANALYZE_IDLE_MLT = xtrue])

AC_ARG_ENABLE([lnk-mlt],
              AS_HELP_STRING([--enable-lnk-mlt],[enable lnk-mlt (default is no)]),
              [
                case "${enableval}" in
                 yes) ENABLE_LNK_MLT=true;;
                 no)  ENABLE_LNK_MLT=false
		      AC_MSG_NOTICE([lnk-mlt is disabled]) ;;
                 *) AC_MSG_ERROR([bad value ${enableval} for --enable-lnk-mlt]) ;;
                esac
              ],
              [echo "lnk-mlt is disabled"])
AM_CONDITIONAL([ENABLE_LNK_MLT],[test x$ENABLE_LNK_MLT = xtrue])

AC_ARG_ENABLE([file-wdr],
              AS_HELP_STRING([--enable-file-wdr],[enable file-wdr (default is no)]),
              [
                case "${enableval}" in
                 yes) ENABLE_FILE_WDR=true;;
                 no)  ENABLE_FILE_WDR=false
		      AC_MSG_NOTICE([file-wdr is disabled]) ;;
                 *) AC_MSG_ERROR([bad value ${enableval} for --enable-file-wdr]) ;;
                esac
              ],
              [echo "file-wdr is disabled"])
AM_CONDITIONAL([ENABLE_FILE_WDR],[test x$ENABLE_FILE_WDR = xtrue])

AC_ARG_ENABLE([cmas-cp],
              AS_HELP_STRING([--enable-],[enable cmas-cp (default is no)]),
              [
                case "${enableval}" in
                 yes) ENABLE_CMAS_CP=true;;
                 no)  ENABLE_CMAS_CP=false
		      AC_MSG_NOTICE([cmas-cp is disabled]) ;;
                 *) AC_MSG_ERROR([bad value ${enableval} for --enable-cmas-cp]) ;;
                esac
              ],
              [echo "cmas-cp is disabled"])
AM_CONDITIONAL([ENABLE_CMAS],[test x$ENABLE_CMAS_CP = xtrue])
AM_CONDITIONAL([ENABLE_CMAS_CP],[test x$ENABLE_CMAS_CP = xtrue])

AC_ARG_ENABLE([cmas-it],
              AS_HELP_STRING([--enable-cmas-it],[enable cmas-it (default is no)]),
              [
                case "${enableval}" in
                 yes) ENABLE_CMAS_IT=true;;
                 no)  ENABLE_CMAS_IT=false
		      AC_MSG_ERROR([cmas-it is disabled]) ;;
                 *) AC_MSG_ERROR([bad value ${enableval} for --enable-cmas-it]) ;;
                esac
              ],
              [echo "cmas-it is disabled"])
AM_CONDITIONAL([ENABLE_CMAS],[test x$ENABLE_CMAS_IT = xtrue])
AM_CONDITIONAL([ENABLE_CMAS_IT],[test x$ENABLE_CMAS_IT = xtrue])

AC_ARG_ENABLE([mlt-bt],
              AS_HELP_STRING([--enable-mlt-bt],[enable mlt-bt (default is no)]),
              [
                case "${enableval}" in
                 yes) ENABLE_MLT_BACKTRACE=true;;
                 no)  ENABLE_MLT_BACKTRACE=false
		      AC_MSG_NOTICE([mlt-bt is disabled]) ;;
                 *) AC_MSG_ERROR([bad value ${enableval} for --enable-mlt-bt]) ;;
                esac
              ],
              [echo "mlt-bt is disabled"])
AM_CONDITIONAL([ENABLE_MLT_BACKTRACE],[test x$ENABLE_MLT_BACKTRACE = xtrue])

AC_ARG_ENABLE([cmat-sstats],
              AS_HELP_STRING([--enable-cmat-sstats],[enable cmat-sstats (default is no)]),
              [
                case "${enableval}" in
                 yes) ENABLE_CMAT_SSTATS=true;;
                 no)  ENABLE_CMAT_SSTATS=false
		      AC_MSG_NOTICE([cmat-sstats is disabled]) ;;
                 *) AC_MSG_ERROR([bad value ${enableval} for --enable-cmat-sstats]) ;;
                esac
              ],
              [echo "cmat-sstats is disabled"])
AM_CONDITIONAL([ENABLE_CMAT_SSTATS],[test x$ENABLE_CMAT_SSTATS = xtrue])

AC_SUBST(ENABLE_SYS_RESOURCE_MLT)
AC_SUBST(ENABLE_SYSMON_POLLINT)
AC_SUBST(ENABLE_ANALYZE_IDLE_MLT)
AC_SUBST(ENABLE_LNK_MLT)
AC_SUBST(ENABLE_FILE_WDR)
AC_SUBST(ENABLE_CMAS_CP)
AC_SUBST(ENABLE_CMAS_IT)
AC_SUBST(ENABLE_MLT_BACKTRACE)
AC_SUBST(ENABLE_CMAT_SSTATS)

AC_CONFIG_FILES([Makefile])
AC_OUTPUT
