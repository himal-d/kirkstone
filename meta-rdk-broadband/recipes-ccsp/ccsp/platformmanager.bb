SUMMARY = "This receipe provides platform manager support."
SECTION = "console/utils"
LICENSE = "Apache-2.0"
LIC_FILES_CHKSUM = "file://LICENSE;md5=a216a5e80a6d5a6b13b08f42cf4e479f"

DEPENDS = "ccsp-common-library dbus rdk-logger hal-platform util-linux ruli utopia "
DEPENDS_append = " ${@bb.utils.contains('DISTRO_FEATURES', 'safec', ' safec', " ", d)}"

require recipes-ccsp/ccsp/ccsp_common.inc

SRC_URI ="${RDKB_CCSP_ROOT_GIT}/PlatformManager/generic;protocol=${RDK_GIT_PROTOCOL};branch=${CCSP_GIT_BRANCH};name=PlatformManager"

SRCREV_PlatformManager = "${AUTOREV}"
SRCREV_FORMAT = "PlatformManager"
PV = "${RDK_RELEASE}+git${SRCPV}"
S = "${WORKDIR}/git"

inherit autotools systemd

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

EXTRA_OECONF_append = " ${@bb.utils.contains('DISTRO_FEATURES', 'rdkb_wan_manager', '--enable-wanmgr', '', d)}"
LDFLAGS += "-pthread -ltelemetry_msgsender"
LDFLAGS += "-lhal_platform"

do_install_append () {
    # Config files and scripts
    install -d ${D}${exec_prefix}/ccsp/platformmanager
    install -d ${D}${systemd_unitdir}/system
    install -D -m 0644 ${S}/config/PlatformManager.service ${D}${systemd_unitdir}/system/PlatformManager.service
}
SYSTEMD_SERVICE_${PN} = "PlatformManager.service"
FILES_${PN} += " \
    ${exec_prefix}/ccsp/platformmanager \
    /usr/bin/* \
        ${systemd_unitdir}/system/PlatformManager.service \
"
