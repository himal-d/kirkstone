SUMMARY = "HAL for RDK CCSP components"
HOMEPAGE = "http://github.com/belvedere-yocto/hal"

LICENSE = "Apache-2.0"
LIC_FILES_CHKSUM = "file://../../LICENSE;md5=175792518e4ac015ab6696d16c4f607e"

PROVIDES = "hal-bridgeutil"
RPROVIDES_${PN} = "hal-bridgeutil"

DEPENDS += "rdkb-halif-bridge-util"
SRC_URI = "${CMF_GIT_ROOT}/rdkb/components/opensource/ccsp/hal;protocol=${CMF_GIT_PROTOCOL};branch=${CMF_GIT_BRANCH};name=bridgeutil"

SRCREV_bridgeutil = "${AUTOREV}"
SRCREV_FORMAT = "bridgeutil"

PV = "${RDK_RELEASE}+git${SRCPV}"

S = "${WORKDIR}/git/source/bridgeutil"

CFLAGS_append = " -I=${includedir}/ccsp "

CFLAGS_append += " ${@bb.utils.contains('DISTRO_FEATURES', 'rdkb_extender', '-DRDKB_EXTENDER_ENABLED', '', d)}"
DEPENDS_append = " ${@bb.utils.contains('DISTRO_FEATURES', 'core-net-lib', ' core-net-lib', " ", d)}"
CFLAGS_append  = " ${@bb.utils.contains('DISTRO_FEATURES', 'core-net-lib', ' -DCORE_NET_LIB', '', d)}"
EXTRA_OECONF_append = " --enable-core_net_lib_feature_support=${@bb.utils.contains('DISTRO_FEATURES', 'core-net-lib', 'yes', 'no', d)} "

inherit autotools coverity
