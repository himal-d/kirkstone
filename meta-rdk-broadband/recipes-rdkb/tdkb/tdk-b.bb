SUMMARY = "Test Development Kit for RDKB stack"
SECTION = "console/utils"

LICENSE = "Apache-2.0"
LIC_FILES_CHKSUM = "file://LICENSE;md5=175792518e4ac015ab6696d16c4f607e"

PV = "${RDK_RELEASE}+git${SRCPV}"

SRC_URI = "${CMF_GIT_ROOT}/rdkb/tools/tdkb;protocol=${CMF_GIT_PROTOCOL};branch=${CMF_GIT_BRANCH};destsuffix=git;name=tdkb"
SRCREV_tdkb = "${AUTOREV}"
SRCREV_FORMAT = "tdkb"

S = "${WORKDIR}/git"

DEPENDS += "jsoncpp jsonrpc ccsp-common-library ccsp-lm-lite hal-cm hal-dhcpv4c hal-ethsw hal-moca hal-mso_mgmt hal-mta hal-platform hal-vlan hal-wifi ccsp-cm-agent ccsp-mta-agent ccsp-p-and-m test-and-diagnostic trower-base64 rbus"

DEPENDS_append = " ${@bb.utils.contains('DISTRO_FEATURES', 'safec', ' safec', " ", d)}"

DEPENDS_append = " ${@bb.utils.contains("DISTRO_FEATURES", 'OneWifi', ' ccsp-one-wifi', ' ccsp-wifi-agent', d)}"

RDEPENDS_${PN} = "jsoncpp jsonrpc ccsp-cm-agent bash trower-base64"

require recipes-ccsp/ccsp/ccsp_common.inc

tdkdir = "/usr/ccsp/tdk/"

inherit autotools systemd coverity

CFLAGS += " -Wall -Werror -Wextra -Wno-unused-parameter -Wno-unused-but-set-parameter -Wno-pointer-sign -Wno-sign-compare -Wno-implicit-function-declaration "

CFLAGS_append = " \
    -I=${includedir}/dbus-1.0 \
    -I=${libdir}/dbus-1.0/include \
    -I=${includedir}/ccsp \
    -I=${includedir}/middle_layer_src/pam \
    -I=${includedir}/middle_layer_src/mta \
    -I=${includedir}/middle_layer_src/cm \
    -I=${includedir}/middle_layer_src/wifi \
    -I=${includedir}/cimplog \
    -I${STAGING_DIR_TARGET}${includedir}/trower-base64 \
    "

CFLAGS_append = " ${@bb.utils.contains('DISTRO_FEATURES', 'safec',  ' `pkg-config --cflags libsafec`', '-fPIC', d)}"

CFLAGS_append = " ${@bb.utils.contains('DISTRO_FEATURES', 'safec', '', ' -DSAFEC_DUMMY_API', d)}"

CFLAGS_append  = " ${@bb.utils.contains('DISTRO_FEATURES', 'rdkb_wan_manager', '-DFEATURE_RDKB_WAN_MANAGER', '', d)}"

CPPFLAGS_append = " ${@bb.utils.contains('DISTRO_FEATURES', 'OneWifi', '-DRDK_ONEWIFI', '', d)}"

LDFLAGS_append = " \
    -ldbus-1 \
    -ltrower-base64 \
    "
LDFLAGS_append = " ${@bb.utils.contains('DISTRO_FEATURES', 'safec', ' `pkg-config --libs libsafec`', '', d)}"
LDFLAGS_remove = "${@bb.utils.contains('DISTRO_FEATURES', 'safec', '-lsafec-3.5', '', d)}"
LDFLAGS_append_dunfell = "${@bb.utils.contains('DISTRO_FEATURES', 'safec', ' -lsafec-3.5.1 ', '', d)}"
LDFLAGS_append_kirkstone = " ${@bb.utils.contains('DISTRO_FEATURES', 'safec', ' -lsafec ', '', d)}"

#Adding new package "tdk-b-dl" which will be downloaded package only of tdk_rdm distro feature is enabled
TDKB_DL_PACK:= "${@bb.utils.contains('DISTRO_FEATURES', 'tdk_rdm', '${PN}-dl', '', d)}"
PACKAGE_BEFORE_PN += "${TDKB_DL_PACK}"

#ENABLE_WAN_MANAGER = "${@bb.utils.contains('DISTRO_FEATURES', 'rdkb_wan_manager', '--enable-rdkb_wan_manager', '--disable-rdkb_wan_manager', d)}"
#EXTRA_OECONF_append = "${ENABLE_WAN_MANAGER}"
#EXTRA_OECONF_append  = " --with-ccsp-platform=bcm --with-ccsp-arch=arm "


# Install all TDK scripts
do_install_append () {
    install -d ${D}/${tdkdir}
    install -d ${D}/${sbindir}
    install -d ${D}/${systemd_unitdir}/system
    install -D -p -m 755 ${S}/agent/scripts/TDK_version.txt ${D}/
    install -D -p -m 755 ${S}/agent/scripts/*.sh ${D}/${tdkdir}
    install -D -p -m 755 ${S}/agent/scripts/tdk_cmd_utility.config ${D}/${tdkdir}
    install -D -p -m 755 ${S}/agent/scripts/tdkb_launcher.sh ${D}/${sbindir}

    install -m 0644 ${S}/tdk.service ${D}/${systemd_unitdir}/system/tdk.service

    install -D -p -m 755 ${S}/tdkb_lib/cfg/TDKB.cfg ${D}/${tdkdir}
    install -D -p -m 755 ${S}/tdkb_lib/cfg/TDKBDM.cfg ${D}/${tdkdir}
    install -D -p -m 755 ${S}/tdkb_lib/cfg/TR181-TDKB.XML ${D}/${tdkdir}

    rm ${D}${bindir}/runSysStat.sh
    rm ${D}${bindir}/RemoveLogs.sh
    rm ${D}${bindir}/file_copy.sh
    rm ${D}${bindir}/TDK_version.txt
    rm ${D}/${tdkdir}/tdkb_launcher.sh
}

#In both RDM and non RDM scenarios, below startup script and service files will be part of tdk package only
SYSTEMD_SERVICE_${PN} = "tdk.service"

#In both RDM and non RDM scenarios, below files will be part of tdk package only
FILES_${PN} = " \
    /TDK_version.txt \
    /etc/tdk_platform.properties \
    ${sbindir}/tdkb_launcher.sh \
"

#All artifacts will be part of tdk-b package when tdk_rdm distro is not present (in non rdm tdk-b builds)
FILES_${PN} += "${@bb.utils.contains('DISTRO_FEATURES', 'tdk_rdm', ' ', ' ${bindir}/rdk_tdk_agent_process ${bindir}/tdk_cmd_utility ${libdir}/*.so* ${tdkdir}/* /etc/*', d)"

#All artifacts will be packed in tdk-b-dl package when tdk_rdm distro is enabled
FILES_${PN}-dl = "${@bb.utils.contains('DISTRO_FEATURES', 'tdk_rdm', ' ${bindir}/rdk_tdk_agent_process ${bindir}/tdk_cmd_utility ${libdir}/*.so* ${tdkdir}/* /etc/* ', '', d)"

FILES_${PN}-dbg = " \
    ${prefix}/src/debug \
    ${bindir}/.debug \
    ${libdir}/.debug \
    ${tdkdir}/.debug \
"

