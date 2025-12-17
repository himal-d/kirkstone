SUMMARY = "Ovs Agent"

LICENSE = "Apache-2.0"
LIC_FILES_CHKSUM = "file://LICENSE;md5=c69ddb4023dccc5f90337c20fd9408f2"

DEPENDS = "ccsp-common-library utopia rdk-logger telemetry jansson libsyswrapper"
DEPENDS_append = " ${@bb.utils.contains('DISTRO_FEATURES', 'safec', ' safec', " ", d)}"
require recipes-ccsp/ccsp/ccsp_common.inc

SRC_URI = "${RDK_GENERIC_ROOT_GIT}/OvsAgent/generic;protocol=${RDK_GIT_PROTOCOL};branch=${RDK_GIT_BRANCH};name=ovs-agent"

SRCREV_ovs-agent = "${AUTOREV}"
SRCREV_FORMAT = "ovs-agent"
PV = "${RDK_RELEASE}+git${SRCPV}"

CFLAGS_append = " ${@bb.utils.contains('DISTRO_FEATURES', 'safec',  ' `pkg-config --cflags libsafec`', '-fPIC', d)}"

LDFLAGS_append = " ${@bb.utils.contains('DISTRO_FEATURES', 'safec', ' `pkg-config --libs libsafec`', '', d)}"
CFLAGS_append = " ${@bb.utils.contains('DISTRO_FEATURES', 'safec', '', ' -DSAFEC_DUMMY_API', d)}"

CFLAGS_append = " \
    -I${STAGING_INCDIR}/dbus-1.0 \
    -I${STAGING_LIBDIR}/dbus-1.0/include \
    -I${STAGING_INCDIR}/ccsp \
    -DENABLE_MESH_SOCKETS \
    "

LDFLAGS_append = " \
    -lrdkloggers \
"
LDFLAGS_append = " -ltelemetry_msgsender -lsecure_wrapper"
S = "${WORKDIR}/git"

inherit pkgconfig autotools systemd

do_install_append () {
    # Config files and scripts
    install -d ${D}/usr/ccsp/ovsagent
    install -d ${D}/usr/include/ovsagent
    install -m 644 ${S}/source/include/*.h ${D}/usr/include/ovsagent
    ln -sf ${bindir}/OvsAgent ${D}/usr/ccsp/ovsagent/OvsAgent
    install -m 755 ${S}/scripts/syscfg_check.sh -t ${D}/usr/ccsp/ovsagent
    install -m 755 ${S}/scripts/OvsAgent_ovsdb-server_check.sh -t ${D}/usr/ccsp/ovsagent

    # systemd scripts
    install -d ${D}${systemd_unitdir}/system
    install -D -m 0644 ${S}/systemd_units/OvsAgent_ovsdb-server.service ${D}${systemd_unitdir}/system/OvsAgent_ovsdb-server.service
    install -D -m 0644 ${S}/systemd_units/OvsAgent.service ${D}${systemd_unitdir}/system/OvsAgent.service
    install -D -m 0644 ${S}/systemd_units/OvsAgent.path ${D}${systemd_unitdir}/system/OvsAgent.path
}

SYSTEMD_SERVICE_${PN} = "OvsAgent.path"

FILES_${PN} += " \
    ${bindir}/OvsAgent \
    ${prefix}/ccsp/ovsagent/OvsAgent \
    ${prefix}/ccsp/ovsagent/syscfg_check.sh \
    ${prefix}/ccsp/ovsagent/OvsAgent_ovsdb-server_check.sh \
    ${systemd_unitdir}/system/OvsAgent_ovsdb-server.service \
    ${systemd_unitdir}/system/OvsAgent.service \
    ${systemd_unitdir}/system/OvsAgent.path \
    ${libdir}/libOvsAgentSsp.so* \
    ${libdir}/libOvsAgentApi.so* \
    ${libdir}/libOvsAction.so* \
    ${libdir}/libOvsDbApi.so* \
    ${libdir}/systemd \
"

FILES_${PN}-dbg = " \
    ${prefix}/ccsp/ovsagent/.debug \
    ${prefix}/src/debug \
    ${bindir}/.debug \
    ${libdir}/.debug \
"

