SUMMARY = "SYSLOG helper library to send data to syslog socket"
DESCRIPTION = "SYSLOG helper library to send data to syslog socket"

LICENSE = "Apache-2.0"
LIC_FILES_CHKSUM = "file://LICENSE;md5=175792518e4ac015ab6696d16c4f607e \
                   "

SRCREV = "${AUTOREV}"
PV = "${RDK_RELEASE}+git${SRCPV}"
SRC_URI = "${CMF_GIT_ROOT}/rdk/components/generic/syslog_helper;protocol=${CMF_GIT_PROTOCOL};branch=${CMF_GIT_BRANCH};name=syslog-helper"

S = "${WORKDIR}/git"
inherit autotools coverity
