SUMMARY = "HAL for RDK CCSP components"
HOMEPAGE = "http://github.com/belvedere-yocto/hal"

LICENSE = "Apache-2.0"
LIC_FILES_CHKSUM = "file://LICENSE;md5=175792518e4ac015ab6696d16c4f607e"


SRC_URI = "${CMF_GIT_ROOT}/rdkb/components/opensource/ccsp/halinterface;protocol=${CMF_GIT_PROTOCOL};branch=${CMF_GIT_BRANCH};name=halinterface"

SRCREV_halinterface = "${AUTOREV}"
SRCREV_FORMAT = "halinterface"

PV = "${RDK_RELEASE}"

S = "${WORKDIR}/git"

inherit autotools coverity
