SUMMARY = "CCSP GWProvAPP"
HOMEPAGE = "https://github.com/belvedere-yocto/GwProvApp"

LICENSE = "Apache-2.0"
LIC_FILES_CHKSUM = "file://LICENSE;md5=175792518e4ac015ab6696d16c4f607e"

DEPENDS = "ccsp-common-library hal-cm hal-dhcpv4c hal-ethsw hal-moca hal-mso_mgmt hal-mta hal-platform hal-vlan hal-wifi ruli utopia "
DEPENDS_append = " telemetry "
DEPENDS_append = " ${@bb.utils.contains('DISTRO_FEATURES', 'safec', ' safec', " ", d)}"

require ccsp_common.inc

SRC_URI = "${CMF_GIT_ROOT}/rdkb/components/opensource/ccsp/GwProvApp;protocol=${CMF_GIT_PROTOCOL};branch=${CMF_GIT_BRANCH};name=GwProvApp"

SRCREV_GwProvApp = "${AUTOREV}"
SRCREV_FORMAT = "GwProvApp"
PV = "${RDK_RELEASE}+git${SRCPV}"

S = "${WORKDIR}/git"

CFLAGS += " -Wall -Werror -Wextra -Wno-pointer-sign -Wno-sign-compare -Wno-deprecated-declarations -Wno-address -Wno-type-limits -Wno-unused-parameter "


CFLAGS_append = " ${@bb.utils.contains('DISTRO_FEATURES', 'bci', '-DCISCO_CONFIG_TRUE_STATIC_IP -DCISCO_CONFIG_DHCPV6_PREFIX_DELEGATION', '', d)}"
CFLAGS_append += " ${@bb.utils.contains('DISTRO_FEATURES', 'bci', '', '-DFEATURE_SUPPORT_ONBOARD_LOGGING',d)}"
CFLAGS_append = " ${@bb.utils.contains('DISTRO_FEATURES', 'dslite', '-DDSLITE_FEATURE_SUPPORT', '', d)}"

inherit autotools breakpad-logmapper
CFLAGS_append = " ${@bb.utils.contains('DISTRO_FEATURES', 'safec',  ' `pkg-config --cflags libsafec`', '-fPIC', d)}"

LDFLAGS_append = " ${@bb.utils.contains('DISTRO_FEATURES', 'safec', ' `pkg-config --libs libsafec`', '', d)}"
LDFLAGS_remove = "${@bb.utils.contains('DISTRO_FEATURES', 'safec', '-lsafec-3.5', '', d)}"
LDFLAGS_append_dunfell = "${@bb.utils.contains('DISTRO_FEATURES', 'safec', ' -lsafec-3.5.1 ', '', d)}"
LDFLAGS_append_kirkstone = " ${@bb.utils.contains('DISTRO_FEATURES', 'safec', ' -lsafec ', '', d)}"
CFLAGS_append = " ${@bb.utils.contains('DISTRO_FEATURES', 'safec', '', ' -DSAFEC_DUMMY_API', d)}"

CFLAGS_append =  "${@bb.utils.contains('DISTRO_FEATURES', 'lld_support', ' -DENABLE_LLD_SUPPORT ', '', d)}"

EXTRA_OECONF_append = " ${@bb.utils.contains('DISTRO_FEATURES', 'rdkb_wan_manager', '--enable-wanmgr', '', d)}"
LDFLAGS += "-pthread -ltelemetry_msgsender"

do_install_append () {
    # Config files and scripts
    install -d ${D}/${includedir}
}


PACKAGES += "${PN}-ccsp"

FILES_${PN}-ccsp = " /usr/ccsp/"

#Breakpad processname and logfile mapping
BREAKPAD_LOGMAPPER_PROCLIST = "gw_prov_utopia"
BREAKPAD_LOGMAPPER_LOGLIST = "GWPROVLog.txt.0"
