SUMMARY = "DPP HAL for RDK CCSP components"
HOMEPAGE = "http://github.com/belvedere-yocto/hal"

LICENSE = "Apache-2.0"
LIC_FILES_CHKSUM = "file://../LICENSE;md5=5c15f0e4e56daf75f2bf1f098e0c77b4"

PROVIDES = "rdk-wifi-util"
RPROVIDES_${PN} = "rdk-wifi-util"

DEPENDS += "openssl halinterface"
SRC_URI = "${RDKB_CCSP_ROOT_GIT}/hal/rdk-wifi-hal;protocol=${RDK_GIT_PROTOCOL};branch=${CCSP_GIT_BRANCH};name=rdk-wifi-util"

SRCREV_rdk-wifi-util = "${AUTOREV}"
SRCREV_FORMAT = "rdk-wifi-util"

PV = "${RDK_RELEASE}+git${SRCPV}"
S = "${WORKDIR}/git/util"

CFLAGS_append = " -I=${includedir}/ccsp "

inherit autotools
