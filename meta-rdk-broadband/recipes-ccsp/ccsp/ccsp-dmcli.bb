SUMMARY = "CCSP Command Line Interface."
HOMEPAGE = "http://github.com/belvedere-yocto/CcspDmCli"

LICENSE = "Apache-2.0"
LIC_FILES_CHKSUM = "file://LICENSE;md5=175792518e4ac015ab6696d16c4f607e"

DEPENDS = "ccsp-common-library dbus telemetry"
DEPENDS_append = " ${@bb.utils.contains('DISTRO_FEATURES', 'safec', ' safec', " ", d)}"

require ccsp_common.inc
SRC_URI = "${CMF_GIT_ROOT}/rdkb/components/opensource/ccsp/CcspDmCli;protocol=${CMF_GIT_PROTOCOL};branch=${CMF_GIT_BRANCH};name=CcspDmCli"

SRCREV_CcspDmCli = "${AUTOREV}"
SRCREV_FORMAT = "CcspDmCli"
PV = "${RDK_RELEASE}+git${SRCPV}"

S = "${WORKDIR}/git"

inherit autotools ${@bb.utils.contains("DISTRO_FEATURES", "kirkstone", "python3native", "pythonnative", d)}

CFLAGS_append = " ${@bb.utils.contains('DISTRO_FEATURES', 'safec',  ' `pkg-config --cflags libsafec`', '-fPIC', d)}"

LDFLAGS_append = " ${@bb.utils.contains('DISTRO_FEATURES', 'safec', ' `pkg-config --libs libsafec`', '', d)}"
LDFLAGS_remove = "${@bb.utils.contains('DISTRO_FEATURES', 'safec', '-lsafec-3.5', '', d)}"
LDFLAGS_append_dunfell = "${@bb.utils.contains('DISTRO_FEATURES', 'safec', ' -lsafec-3.5.1 ', '', d)}"
LDFLAGS_append_kirkstone = " ${@bb.utils.contains('DISTRO_FEATURES', 'safec', ' -lsafec ', '', d)}"
CFLAGS_append = " ${@bb.utils.contains('DISTRO_FEATURES', 'safec', '', ' -DSAFEC_DUMMY_API', d)}"

CFLAGS_append = " \
    -I${STAGING_INCDIR}/dbus-1.0 \
    -I${STAGING_LIBDIR}/dbus-1.0/include \
    -I${STAGING_INCDIR}/ccsp \
"

LDFLAGS += "-ldbus-1 -ltelemetry_msgsender"

CFLAGS += " -Wall -Werror -Wextra "
CPPLAGS += " -Wall -Werror -Wextra "

# generating minidumps symbols
inherit breakpad-wrapper
DEPENDS += "breakpad breakpad-wrapper"
BREAKPAD_BIN_append = " dmcli"

LDFLAGS += "-lbreakpadwrapper -lpthread -lstdc++"
CFLAGS += " -DINCLUDE_BREAKPAD"

do_compile_prepend () {
    (${PYTHON} ${STAGING_BINDIR_NATIVE}/dm_pack_code_gen.py ${S}/source/MsgBusTestServer/config/MsgBusTest.XML ${S}/source/MsgBusTestServer/dm_pack_datamodel.c)
}
do_install_append () {
    # Config files and scripts
    install -d ${D}/fss/gw/usr/ccsp
    install -d ${D}/usr/ccsp/MsgBusTestServer
    ln -sf ${bindir}/dmcli ${D}/fss/gw/usr/ccsp/ccsp_bus_client_tool
    
}

do_install_append_mips () {
    # Config files and scripts
    install -d ${D}/usr/ccsp
    install -d ${D}/usr/ccsp/MsgBusTestServer
    ln -sf ${bindir}/dmcli ${D}/usr/ccsp/ccsp_bus_client_tool
   
}

do_install_append_puma7 () {
    # Config files and scripts
    ln -sf ${bindir}/dmcli ${D}${bindir}/ccsp_bus_client_tool
    install -d ${D}/usr/ccsp
    ln -sf ${bindir}/dmcli ${D}/usr/ccsp/ccsp_bus_client_tool
}

do_install_append_arrisxb3atom () {
    install -d ${D}/usr/ccsp
    install -d ${D}/usr/ccsp/MsgBusTestServer
    ln -sf ${bindir}/dmcli ${D}/usr/ccsp/ccsp_bus_client_tool
   
}

do_install_append_bcm3390 () {
    # Config files and scripts
    ln -sf ${bindir}/dmcli ${D}${bindir}/ccsp_bus_client_tool
    install -d ${D}/usr/ccsp
    install -d ${D}/usr/ccsp/MsgBusTestServer
    ln -sf ${bindir}/dmcli ${D}/usr/ccsp/ccsp_bus_client_tool
  
}

do_install_append_ciscoxb3atom () {
    # Config files and scripts
    install -d ${D}/usr/ccsp
    install -d ${D}/usr/ccsp/MsgBusTestServer
   
}

PACKAGES += "${PN}-ccsp"

FILES_${PN}-ccsp = " \
    /fss/gw/usr/ccsp/* \
    ${prefix}/ccsp/* \
"

FILES_${PN}_append_arrisxb3atom = " \
    /usr/ccsp/* \
    ${prefix}/ccsp/* \
"

FILES_${PN}_append_ciscoxb3atom = " \
    /usr/ccsp/* \
    ${prefix}/ccsp/* \
"

FILES_${PN}-dbg = " \
    ${prefix}/ccsp/.debug \
    ${prefix}/src/debug \
    ${bindir}/.debug \
    ${libdir}/.debug \
"

# generating minidumps
PACKAGECONFIG_append = " breakpad"
