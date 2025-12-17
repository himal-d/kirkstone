SUMMARY = "CCSP MTA Agent"
HOMEPAGE = "http://github.com/belvedere-yocto/CcspMtaAgent"

LICENSE = "Apache-2.0"
LIC_FILES_CHKSUM = "file://LICENSE;md5=175792518e4ac015ab6696d16c4f607e"

DEPENDS = "utopia ccsp-common-library dbus hal-cm hal-dhcpv4c hal-ethsw hal-moca hal-mso_mgmt hal-mta hal-platform hal-vlan hal-wifi"
DEPENDS_append = " ${@bb.utils.contains('DISTRO_FEATURES', 'safec', ' safec', " ", d)}"

require ccsp_common.inc

CFLAGS += " -Wall -Werror -Wextra -Wno-free-nonheap-object -Wno-array-bounds -Wno-stringop-overread"

SRC_URI = "${CMF_GIT_ROOT}/rdkb/components/opensource/ccsp/CcspMtaAgent;protocol=${CMF_GIT_PROTOCOL};branch=${CMF_GIT_BRANCH};name=CcspMtaAgent"

SRCREV_CcspMtaAgent = "${AUTOREV}"
SRCREV_FORMAT = "CcspMtaAgent"
PV = "${RDK_RELEASE}+git${SRCPV}"

S = "${WORKDIR}/git"

inherit autotools ${@bb.utils.contains("DISTRO_FEATURES", "kirkstone", "python3native", "pythonnative", d)} breakpad-logmapper

CFLAGS_append = " ${@bb.utils.contains('DISTRO_FEATURES', 'safec',  ' `pkg-config --cflags libsafec`', '-fPIC', d)}"

LDFLAGS_append = " ${@bb.utils.contains('DISTRO_FEATURES', 'safec', ' `pkg-config --libs libsafec`', '', d)}"
LDFLAGS_remove = "${@bb.utils.contains('DISTRO_FEATURES', 'safec', '-lsafec-3.5', '', d)}"
LDFLAGS_append_dunfell = "${@bb.utils.contains('DISTRO_FEATURES', 'safec', ' -lsafec-3.5.1 ', '', d)}"
LDFLAGS_append_kirkstone = " ${@bb.utils.contains('DISTRO_FEATURES', 'safec', ' -lsafec ', '', d)}"
CFLAGS_append = " ${@bb.utils.contains('DISTRO_FEATURES', 'safec', '', ' -DSAFEC_DUMMY_API', d)}"

CFLAGS_append = " \
    -I=${includedir}/dbus-1.0 \
    -I=${libdir}/dbus-1.0/include \
    -I=${includedir}/ccsp \
    "

LDFLAGS += "-ldbus-1"

do_compile_prepend () {
    (${PYTHON} ${STAGING_BINDIR_NATIVE}/dm_pack_code_gen.py ${S}/config/CcspMtaAgent.xml ${S}/source/MtaAgentSsp/dm_pack_datamodel.c)
}

do_install_append () {
    # Config files and scripts
    install -d ${D}/usr/ccsp/mta
    install -d ${D}/usr/include/middle_layer_src
    install -d ${D}/usr/include/middle_layer_src/mta
    install -m 644 ${S}/source/TR-181/middle_layer_src/*.h ${D}/usr/include/middle_layer_src/mta
    install -d ${D}/usr/include/ccsp
    install -m 644 ${S}/source/TR-181/include/*.h ${D}/usr/include/ccsp

    # Config files and scripts
    install -m 644 ${S}/config/CcspMta.cfg ${D}/usr/ccsp/mta/CcspMta.cfg
    install -m 644 ${S}/config/CcspMtaLib.cfg ${D}/usr/ccsp/mta/CcspMtaLib.cfg
}


PACKAGES += "${PN}-ccsp"

FILES_${PN}-ccsp = " \
    ${prefix}/ccsp/mta/CcspMta.cfg \
    ${prefix}/ccsp/mta/CcspMtaLib.cfg \
"

FILES_${PN}-dbg = " \
    ${prefix}/ccsp/mta/.debug \
    ${prefix}/src/debug \
    ${bindir}/.debug \
    ${libdir}/.debug \
"

# Breakpad processname and logfile mapping
BREAKPAD_LOGMAPPER_PROCLIST = "CcspMtaAgentSsp"
BREAKPAD_LOGMAPPER_LOGLIST = "MTAlog.txt.0"
