SUMMARY = "External RBUS test tool"
PN = "rbustools"

inherit pkgconfig autotools 

FILESEXTRAPATHS_prepend := "${THISDIR}/files:"
DEPENDS += " rbus "

LICENSE = "Apache-2.0"
LICENSE_LOCATION ?= "LICENSE"
LIC_FILES_CHKSUM = "file://${LICENSE_LOCATION};md5=ed63516ecab9f06e324238dd2b259549"

LDFLAGS_append += "-L${PKG_CONFIG_SYSROOT_DIR}/${libdir} -lrbus "
#CXXFLAGS_append += " -I${includedir}/rbus "

LD_LIBRARY_PATH="${PKG_CONFIG_SYSROOT_DIR}/usr/${libdir}"

INCLUDE_DIRS += "\
	-I${PKG_CONFIG_SYSROOT_DIR}/usr/include/rdk/ds \
	-I${PKG_CONFIG_SYSROOT_DIR}/usr/include/rdk/ds-hal \
	-I${PKG_CONFIG_SYSROOT_DIR}/usr/include/rdk/ds-rpc \
	-I${PKG_CONFIG_SYSROOT_DIR}/usr/include/rdk/iarmbus \
	-I${PKG_CONFIG_SYSROOT_DIR}/usr/include/rdk/iarmmgrs/tr69Bus \
	-I${PKG_CONFIG_SYSROOT_DIR}/usr/include/rdk/iarmmgrs/mfr \
	-I${PKG_CONFIG_SYSROOT_DIR}/usr/include/rdk/iarmmgrs/power \
	-I${PKG_CONFIG_SYSROOT_DIR}/usr/include/rdk/iarmmgrs-hal \
	-I${PKG_CONFIG_SYSROOT_DIR}/usr/include \
	"

CPPFLAGS += "${INCLUDE_DIRS}"
# C++11 is required
CXXFLAGS += " -std=c++11 -fPIC -D_REENTRANT -rdynamic -Wall -Werror ${INCLUDE_DIRS}"
CFLAGS += " -std=c99 -Wall -Werror ${INCLUDE_DIRS}"

SRC_URI = "${RDK_GENERIC_ROOT_GIT}/rbustools/generic;protocol=${RDK_GIT_PROTOCOL};branch=${RDK_GIT_BRANCH}"
#SRCREV ?= "${AUTOREV}"

S = "${WORKDIR}/git"
