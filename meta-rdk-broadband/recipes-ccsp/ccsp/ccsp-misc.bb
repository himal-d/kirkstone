SUMMARY = "CCSP miscellaneous tools."
HOMEPAGE = "http://github.com/belvedere-yocto/CcspMisc"

LICENSE = "Apache-2.0"
LIC_FILES_CHKSUM = "file://LICENSE;md5=175792518e4ac015ab6696d16c4f607e"

DEPENDS = "ccsp-common-library hal-platform utopia libunpriv"
RDEPENDS_${PN} = " trower-base64"
DEPENDS += " trower-base64 "

DEPENDS += "${@bb.utils.contains('DISTRO_FEATURES', 'enable_rdkscheduler',' rdk-scheduler','',d)}"
DEPENDS_append = " ${@bb.utils.contains('DISTRO_FEATURES', 'core-net-lib', ' core-net-lib', " ", d)}"
require ccsp_common.inc
SRC_URI = "${CMF_GIT_ROOT}/rdkb/components/opensource/ccsp/CcspMisc;protocol=${CMF_GIT_PROTOCOL};branch=${CMF_GIT_BRANCH};name=CcspMisc"

SRCREV_CcspMisc = "${AUTOREV}"
SRCREV_FORMAT = "CcspMisc"
PV = "${RDK_RELEASE}+git${SRCPV}"

S = "${WORKDIR}/git"

inherit autotools breakpad-logmapper

DEPENDS_append = " ${@bb.utils.contains('DISTRO_FEATURES', 'safec', ' safec', " ", d)}"

CFLAGS_append = " ${@bb.utils.contains('DISTRO_FEATURES', 'safec',  ' `pkg-config --cflags libsafec`', '-fPIC', d)}"

LDFLAGS_append = " ${@bb.utils.contains('DISTRO_FEATURES', 'safec', ' `pkg-config --libs libsafec`', '', d)}"
LDFLAGS_remove = "${@bb.utils.contains('DISTRO_FEATURES', 'safec', '-lsafec-3.5', '', d)}"
LDFLAGS_append_dunfell = "${@bb.utils.contains('DISTRO_FEATURES', 'safec', ' -lsafec-3.5.1 ', '', d)}"
LDFLAGS_append_kirkstone = " ${@bb.utils.contains('DISTRO_FEATURES', 'safec', ' -lsafec ', '', d)}"
CFLAGS_append = " ${@bb.utils.contains('DISTRO_FEATURES', 'safec', '', ' -DSAFEC_DUMMY_API', d)}"
CFLAGS_append = "${@bb.utils.contains('DISTRO_FEATURES', 'rdkb_wan_manager', ' -DDHCPV4_CLIENT_UDHCPC ', '', d)}"
CFLAGS_append = "${@bb.utils.contains('DISTRO_FEATURES', 'rdkb_wan_manager', ' -DDHCPV6_CLIENT_DIBBLER ', '', d)}"
CFLAGS_append  = " ${@bb.utils.contains('DISTRO_FEATURES', 'core-net-lib', ' -DCORE_NET_LIB', '', d)}"
EXTRA_OECONF_append = " --enable-core_net_lib_feature_support=${@bb.utils.contains('DISTRO_FEATURES', 'core-net-lib', 'yes', 'no', d)} "

CFLAGS += " -Wall -Werror -Wextra -Wno-deprecated-declarations -Wno-array-bounds"

# generating minidumps symbols
inherit breakpad-wrapper
DEPENDS += "breakpad breakpad-wrapper"
BREAKPAD_BIN_append = " psmcli"

LDFLAGS += "-lbreakpadwrapper -lpthread -lstdc++ -lrt"

CFLAGS_append = " \
    -I${STAGING_INCDIR}/dbus-1.0 \
    -I${STAGING_LIBDIR}/dbus-1.0/include \
    -I${STAGING_INCDIR}/ccsp \
    -I${STAGING_INCDIR}/trower-base64 \
    "

CFLAGS_append += "${@bb.utils.contains('DISTRO_FEATURES', 'enable_rdkscheduler',' -I${STAGING_INCDIR}/cimplog','',d)}"

EXTRA_OECONF += "${@bb.utils.contains("DISTRO_FEATURES", "notifylease", " --enable-notifylease ", " ", d)}"
EXTRA_OECONF_append_puma7 += "${@bb.utils.contains("DISTRO_FEATURES", "setLED", " --enable-setLED=yes", " ", d)}"
EXTRA_OECONF_append_bcm3390 += "${@bb.utils.contains("DISTRO_FEATURES", "setLED", " --enable-setLED=yes", " ", d)}"

EXTRA_OECONF += "${@bb.utils.contains("DISTRO_FEATURES", "multipartUtility", " --enable-multipartUtilEnable=yes ", " ", d)}"

EXTRA_OECONF += "${@bb.utils.contains("DISTRO_FEATURES", "wbCfgTestApp", " --enable-wbCfgTestAppEnable ", " ", d)}"

EXTRA_OECONF += "${@bb.utils.contains("DISTRO_FEATURES", "rdkscheduler_testapp", " --enable-rdkSchedulerTestAppEnable ", " ", d)}"

EXTRA_OECONF += "${@bb.utils.contains("DISTRO_FEATURES", "Socket_Example", " --enable-socketExampleEnable ", " ",d)}"

do_install_append () {
    # Config files and scripts
    install -d ${D}/usr/ccsp
    install -d ${D}/etc/
    ln -sf /usr/bin/psmcli ${D}/usr/ccsp/psmcli
    install -d ${D}${includedir}/ccsp
    install -m 644 ${S}/source/TimeConv/time_conversion.h ${D}${includedir}/ccsp
    install -m 644 ${S}/source/dhcp_client_utils/dhcp_client_utils.h ${D}${includedir}/ccsp
    install -m 755 ${S}/source/bridge_utils/scripts/migration_to_psm.sh ${D}/etc/
}

PACKAGES += "${PN}-ccsp"

FILES_${PN}-ccsp = " \
    /usr/ccsp/psmcli \
"

FILES_${PN}-dbg = " \
    ${prefix}/ccsp/.debug \
    ${prefix}/src/debug \
    ${bindir}/.debug \
    ${libdir}/.debug \
"
# generating minidumps
PACKAGECONFIG_append = " breakpad"

# Breakpad processname and logfile mapping
BREAKPAD_LOGMAPPER_PROCLIST = "meshAgent"
BREAKPAD_LOGMAPPER_LOGLIST = "MeshAgentLog.txt.0,MeshServiceLog.txt.0"
