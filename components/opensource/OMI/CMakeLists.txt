#
# If not stated otherwise in this file or this component's LICENSE file the
# following copyright and licenses apply:
#
# Copyright 2018 Liberty Global B.V.
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
#
# Author: Lindsay Rea <lrea.contractor@libertyglobal.com>
#         Damian Wrobel <dwrobel@ertelnet.rybnik.pl>
#

cmake_minimum_required(VERSION 3.16)

project(omi VERSION 1.0.0 LANGUAGES C CXX)

option(RDK_LOGGER_ENABLED "Use RDK loggers for logging" ON)
option(CERTIFICATE_PATH_FORMAT "The kid to certificate path mapping. \
The format accepts a string with a single %s argument which will be substituted by the \
.cryptConfigurations[bundlecrypt-id-arg].\"config.json\".jws.kid \
(see: bundlecrypt configuration JSON schema) where the bundlecrypt-id-arg \
is string passed to the bundlecrypt --id argument" "/your-path-to-the-certificate/%s")

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(THREADS_PREFER_PTHREAD_FLAG ON)

find_package(PkgConfig)
find_package(Threads REQUIRED)
include(GNUInstallDirs)

set (REQUIRES_PUBLIC glib-2.0)
set (REQUIRES_PRIVATE cjose dacjwt devmapper dropprivileges gio-unix-2.0 jansson mntfsimg kwk)
set (REQUIRES ${REQUIRES_PUBLIC} ${REQUIRES_PRIVATE})
pkg_check_modules(PKG_MODULES REQUIRED ${REQUIRES})

if (${RDK_LOGGER_ENABLED})
    set(RDK_LOGGER_LIBRARIES "rdkloggers" CACHE STRING "")
    set(RDK_LOGGER_CFLAGS_OTHER "-DUSE_RDK_LOGGER")
    find_path(RDK_LOGGER_INCLUDE_DIRS "rdk_debug.h" PATH_SUFFIXES "include")
    message(STATUS "Using RDK logger for logging (header: ${RDK_LOGGER_INCLUDE_DIRS})")
    # rdklogger does not have .pc config file
    set(PKGCONF_LIBS_PRIVATE "-l${RDK_LOGGER_LIBRARIES}")
endif()

add_custom_command(
    OUTPUT  omi_dbus_api.c
    DEPENDS dbus/com.lgi.onemw.omi1.xml
    COMMENT "Generating com.lgi.onemw.omi1 interface"
    COMMAND gdbus-codegen --generate-c-code omi_dbus_api --interface-prefix com.lgi.onemw. ${CMAKE_CURRENT_SOURCE_DIR}/dbus/com.lgi.onemw.omi1.xml
)

# omi executable {
set(OMI_EXE "omi")

add_executable(${OMI_EXE}
    src/omi_main.cpp
    src/omi_mount.cpp
    src/omi_parser.cpp
    src/omi_service.cpp
    src/omi_unmount.cpp
    src/omi_utils.cpp
    ${CMAKE_CURRENT_BINARY_DIR}/omi_dbus_api.c
)

target_compile_options(${OMI_EXE} PRIVATE -Wall -Wextra -Werror -Wno-unused-parameter
    ${PKG_MODULES_CFLAGS_OTHER} ${RDK_LOGGER_CFLAGS_OTHER} -DCERTIFICATE_PATH_FORMAT=\"${CERTIFICATE_PATH_FORMAT}\"
)

target_include_directories(${OMI_EXE} PRIVATE
    src ${CMAKE_CURRENT_BINARY_DIR} ${PKG_MODULES_INCLUDE_DIRS} ${RDK_LOGGER_INCLUDE_DIRS}
)

link_directories(${OMI_EXE}
    ${PKG_MODULES_LIBRARY_DIRS} ${RDK_LOGGER_LIBRARY_DIRS}
)

target_link_libraries(${OMI_EXE} PRIVATE
    Threads::Threads ${PKG_MODULES_LIBRARIES} ${RDK_LOGGER_LIBRARIES} ${EXTRA_LD_FLAGS}
)

install(TARGETS ${OMI_EXE} RUNTIME DESTINATION bin)
# } omi executable

# omiclientlib {
set (SONAME "omiclientlib")

add_library(${SONAME} SHARED
    ${CMAKE_CURRENT_BINARY_DIR}/omi_dbus_api.c
    client/omi_proxy.cpp
)

#TODO:dw add directory prefix (e.g. rdk)
set(${SONAME}_PUBLIC_HEADERS
    client/omi_proxy.hpp
    client/i_omi_proxy.hpp
)

set_target_properties(
    ${SONAME}     PROPERTIES
    VERSION       ${PROJECT_VERSION}
    SOVERSION     ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    PUBLIC_HEADER "${${SONAME}_PUBLIC_HEADERS}"
)

target_compile_options(${SONAME} PRIVATE -Wall -Wextra -Werror -Wno-unused-parameter
    ${PKG_MODULES_CFLAGS_OTHER} ${RDK_LOGGER_CFLAGS_OTHER}
)

target_include_directories(${SONAME} PRIVATE
    client ${CMAKE_CURRENT_BINARY_DIR} ${PKG_MODULES_INCLUDE_DIRS} ${RDK_LOGGER_INCLUDE_DIRS}
)

link_directories(${SONAME}
    ${PKG_MODULES_LIBRARY_DIRS} ${RDK_LOGGER_LIBRARY_DIRS}
)

target_link_libraries(${SONAME} PRIVATE
    ${PKG_MODULES_LIBRARIES} ${RDK_LOGGER_LIBRARIES} ${EXTRA_LD_FLAGS}
)

list(JOIN  REQUIRES_PUBLIC " " PKGCONF_REQUIRES_PUBLIC)
list(JOIN  REQUIRES_PRIVATE " " PKGCONF_REQUIRES_PRIVATE)

foreach(LIB ${CMAKE_CXX_IMPLICIT_LINK_LIBRARIES})
    set(PKGCONF_LIBS_PRIVATE "${PKGCONF_LIBS_PRIVATE} -l${LIB}")
endforeach()

set(DBUSDIR ${CMAKE_INSTALL_DATAROOTDIR}/dbus-1/interfaces)

configure_file(${SONAME}.pc.in ${SONAME}.pc @ONLY)

install (
    TARGETS                   ${SONAME}
    LIBRARY       DESTINATION ${CMAKE_INSTALL_LIBDIR}
    PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)

install(
    FILES       ${CMAKE_BINARY_DIR}/${SONAME}.pc
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/pkgconfig
)

install(
    FILES       dbus/com.lgi.onemw.omi1.xml
    DESTINATION ${DBUSDIR}
)
# } omiclientlib

# omi-parser-test {
SET(OMI_TEST_EXE "omi-parser-test")

add_executable(${OMI_TEST_EXE}
    src/omi_parser.cpp
    test/omi_parser_test.cpp
)

target_compile_options(${OMI_TEST_EXE} PRIVATE -Wall -Wextra -Werror -Wno-unused-parameter
    ${PKG_MODULES_CFLAGS_OTHER} ${RDK_LOGGER_CFLAGS_OTHER}
)

target_include_directories(${OMI_TEST_EXE} PRIVATE
    src ${PKG_MODULES_INCLUDE_DIRS} ${RDK_LOGGER_INCLUDE_DIRS}
)

link_directories(${OMI_TEST_EXE}
    ${PKG_MODULES_LIBRARY_DIRS} ${RDK_LOGGER_LIBRARY_DIRS}
)

target_link_libraries(${OMI_TEST_EXE} PRIVATE
    ${PKG_MODULES_LIBRARIES} ${RDK_LOGGER_LIBRARIES} ${EXTRA_LD_FLAGS}
)
install (TARGETS ${OMI_TEST_EXE} RUNTIME DESTINATION bin)
# } omi-parser-test