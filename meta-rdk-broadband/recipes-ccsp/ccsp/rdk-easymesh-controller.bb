# Component can be added to build with: DISTRO_FEATURES = " easymesh-controller"

SUMMARY = "RDK EasyMesh Controller component"

LICENSE = "BSD-2-Clause-Patent & Apache-2.0"
LIC_FILES_CHKSUM = " \
    file://LICENSE;md5=ad1d394d8d45e5585e02e2bc6eb139e4 \
    file://ssp/LICENSE;md5=3b83ef96387f14655fc854ddc3c6bd57 \
"

DEPENDS = "ccsp-common-library dbus rdk-logger json-c libubox openssl zlib"

require recipes-ccsp/ccsp/ccsp_common.inc

SRC_URI =  "${CMF_GITHUB_ROOT}/RdkEasyMeshController;protocol=${CMF_GIT_PROTOCOL};branch=${CMF_GITHUB_MAIN_BRANCH};name=RdkEasyMeshController"
SRC_URI += "${CMF_GITHUB_ROOT}/RdkEasyMeshControllerSSP;protocol=${CMF_GIT_PROTOCOL};branch=${CMF_GITHUB_MAIN_BRANCH};destsuffix=git/ssp;name=ssp"

SRCREV_RdkEasyMeshController = "${AUTOREV}"
SRCREV_ssp = "${AUTOREV}"
SRCREV_FORMAT = "RdkEasyMeshController"

PV = "${RDK_RELEASE}+git${SRCPV}"

S = "${WORKDIR}/git"

# inherit cmake pkgconfig
inherit autotools pkgconfig systemd

EXTRA_OECONF_append  = " --with-ccsp-platform=bcm --with-ccsp-arch=arm "

CFLAGS_append = " \
    -I${STAGING_INCDIR} \
    -I${STAGING_INCDIR}/dbus-1.0 \
    -I${STAGING_LIBDIR}/dbus-1.0/include \
    -I${STAGING_INCDIR}/ccsp \
    -I${STAGING_INCDIR}/libubox \
"

LDFLAGS_append = " \
    -ldbus-1 \
    -lrdkloggers \
    -ljson-c \
    -lz \
    -lcrypto \
    -lpthread \
    -L${STAGING_LIBDIR} -lubox \
"
ISSYSTEMD = "${@bb.utils.contains('DISTRO_FEATURES', 'systemd', 'true', 'false', d)}"

do_install_append () {
    # Config files and scripts
    install -d ${D}${exec_prefix}/ccsp/easymesh
    ln -sf ${bindir}/em-ctl ${D}${exec_prefix}/ccsp/easymesh/em-ctl
    install -m 644 ${S}/ssp/scripts/RdkEasyMeshController.xml ${D}${exec_prefix}/ccsp/easymesh/RdkEasyMeshController.xml
    if [ ${ISSYSTEMD} = "true" ]; then
        install -d ${D}${systemd_unitdir}/system
        install -D -m 0644 ${S}/scripts/RdkEasyMeshController.service ${D}${systemd_unitdir}/system/RdkEasyMeshController.service
        install -D -m 0644 ${S}/scripts/RdkEasyMeshController.path ${D}${systemd_unitdir}/system/RdkEasyMeshController.path
    fi
}

# This will automatically start the service on boot up on platforms that use systemd init system.
# The .service systemd unit shouldn't start automatically upon bootup, but rather wait for
# CcspWiFiAgent to finish initializing. It will be started by the .path unit.
#SYSTEMD_SERVICE_${PN} += " ${@bb.utils.contains('DISTRO_FEATURES', 'systemd', 'RdkEasyMeshController.service', '', d)}"
SYSTEMD_SERVICE_${PN} += " ${@bb.utils.contains('DISTRO_FEATURES', 'systemd', 'RdkEasyMeshController.path', '', d)}"

FILES_${PN} += " \
    ${exec_prefix}/ccsp/easymesh/em-ctl \
    ${exec_prefix}/ccsp/easymesh/RdkEasyMeshController.xml \
    ${bindir}/* \
"

FILES_${PN}_append = " ${@bb.utils.contains('DISTRO_FEATURES', 'systemd', '${systemd_unitdir}/system/RdkEasyMeshController.service', '', d)}"
FILES_${PN}_append = " ${@bb.utils.contains('DISTRO_FEATURES', 'systemd', '${systemd_unitdir}/system/RdkEasyMeshController.path', '', d)}"
