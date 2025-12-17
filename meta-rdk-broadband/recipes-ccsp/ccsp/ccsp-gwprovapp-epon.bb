SUMMARY = "CCSP GWProvAPP EPON"
HOMEPAGE = "https://github.com/belvedere-yocto/GwProvApp"

LICENSE = "Apache-2.0"
LIC_FILES_CHKSUM = "file://LICENSE;md5=175792518e4ac015ab6696d16c4f607e"

DEPENDS = "ccsp-common-library hal-cm hal-dhcpv4c hal-ethsw hal-moca hal-mso_mgmt hal-mta hal-platform hal-vlan hal-wifi ruli utopia"
require ccsp_common.inc

SRC_URI = "${CMF_GIT_ROOT}/rdkb/components/opensource/ccsp/GwProvApp-ePON;protocol=${CMF_GIT_PROTOCOL};branch=${CMF_GIT_BRANCH};name=GwProvApp"

SRCREV_GwProvApp = "${AUTOREV}"
SRCREV_FORMAT = "GwProvApp"
PV = "${RDK_RELEASE}+git${SRCPV}"

S = "${WORKDIR}/git"

EXTRA_OECONF_append  = " --with-ccsp-platform=bcm --with-ccsp-arch=arm "

CFLAGS_append = " ${@bb.utils.contains('DISTRO_FEATURES', 'bci', '-DCISCO_CONFIG_TRUE_STATIC_IP -DCISCO_CONFIG_DHCPV6_PREFIX_DELEGATION', '', d)}"

inherit autotools

do_install_append () {
    # Config files and scripts
    install -d ${D}/${STAGING_INCDIR}
    install -d ${D}/usr/ccsp/
    install -m 0755 ${B}/source/gw_prov_epon ${D}/usr/ccsp/gw_prov_epon
    install -d ${D}${systemd_unitdir}/system
    install -m 0644 ${S}/service/gwprovepon.service ${D}${systemd_unitdir}/system
    # install -m 644 ${S}/source/include/Tr69_Tlv.h -t ${D}/${STAGING_INCDIR}
}

SYSTEMD_SERVICE_${PN} = "gwprovepon.service"

FILES_${PN} += " \
    ${STAGING_INCDIR} \
    /usr/ccsp \
    /usr/ccsp/gw_prov_epon \
"

FILES_${PN} += " \
     ${systemd_unitdir}/system/gwprovepon.service \
"

FILES_${PN}-dbg = " \
    ${prefix}/ccsp/.debug \
    ${prefix}/src/debug \
    ${bindir}/.debug \
    ${libdir}/.debug \
"
