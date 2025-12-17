SUMMARY = "This receipe provides xconf service support."
SECTION = "console/utils"

LICENSE = "Apache-2.0" 
LIC_FILES_CHKSUM = "file://LICENSE;md5=175792518e4ac015ab6696d16c4f607e"

PV = "${RDK_RELEASE}+git${SRCPV}"

DEPENDS = "ccsp-common-library hal-cm hal-dhcpv4c hal-ethsw hal-moca hal-mso_mgmt hal-mta hal-platform hal-vlan hal-wifi telemetry"
DEPENDS_append = " ${@bb.utils.contains('DISTRO_FEATURES', 'fwupgrade_manager', ' hal-fwupgrade', '',d)}"
DEPENDS_append = " ${@bb.utils.contains('DISTRO_FEATURES', 'safec', ' safec', " ", d)}"

RDEPENDS_${PN}_append = " bash"
RDEPENDS_${PN}_remove_morty = "bash"

require recipes-ccsp/ccsp/ccsp_common.inc

SRC_URI = "${CMF_GIT_ROOT}/rdkb/components/opensource/ccsp/Xconf;protocol=${CMF_GIT_PROTOCOL};branch=${CMF_GIT_BRANCH};name=Xconf"

SRCREV_Xconf = "${AUTOREV}"
SRCREV_FORMAT = "Xconf"

S = "${WORKDIR}/git"

inherit autotools

CFLAGS_append = " \
    -I=${includedir}/ccsp \
    -I=${includedir}/dbus-1.0 \
    -I=${includedir}/../lib/dbus-1.0/include \
    "
CFLAGS_append = " ${@bb.utils.contains('DISTRO_FEATURES', 'safec',  ' `pkg-config --cflags libsafec`', '-fPIC', d)}"
CFLAGS_append = " ${@bb.utils.contains('DISTRO_FEATURES', 'safec', '', ' -DSAFEC_DUMMY_API', d)}"

LDFLAGS_append = " -ltelemetry_msgsender -lsecure_wrapper"
LDFLAGS_append = " ${@bb.utils.contains('DISTRO_FEATURES', 'fwupgrade_manager', ' -lfw_upgrade', '', d)}"
LDFLAGS_remove = " ${@bb.utils.contains('DISTRO_FEATURES', 'fwupgrade_manager', ' -lcm_mgnt', '', d)}"
LDFLAGS_append = " ${@bb.utils.contains('DISTRO_FEATURES', 'safec', ' `pkg-config --libs libsafec`', '', d)}"

do_install_append () {
    install -d ${D}${sysconfdir}
    install -m 755 ${S}/scripts/bundleUtils.sh ${D}${sysconfdir}
    install -m 755 ${S}/scripts/firmwareSched.sh ${D}${sysconfdir}
    install -m 755 ${S}/scripts/rdkfwupgrader_message.sh ${D}${sysconfdir}
}

FILES_${PN} += "${sysconfdir}"
