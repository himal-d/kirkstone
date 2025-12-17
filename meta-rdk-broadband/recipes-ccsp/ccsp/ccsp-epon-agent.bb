SUMMARY = "CCSP CcspEPONAgent component"
HOMEPAGE = "http://github.com/belvedere-yocto/CcspEPONAgent"

LICENSE = "Apache-2.0"
LIC_FILES_CHKSUM = "file://LICENSE;md5=175792518e4ac015ab6696d16c4f607e"

DEPENDS = "ccsp-common-library hal-cm hal-dhcpv4c hal-ethsw hal-moca hal-mso_mgmt hal-mta hal-platform hal-vlan hal-wifi utopia"

require ccsp_common.inc

SRC_URI = "${CMF_GIT_ROOT}/rdkb/components/opensource/ccsp/CcspEPONAgent;protocol=${CMF_GIT_PROTOCOL};branch=${CMF_GIT_BRANCH};name=CcspEPONAgent"

SRCREV_CcspEPONAgent = "${AUTOREV}"
SRCREV_FORMAT = "CcspEPONAgent"
PV = "${RDK_RELEASE}+git${SRCPV}"

S = "${WORKDIR}/git"

inherit autotools pkgconfig ${@bb.utils.contains("DISTRO_FEATURES", "kirkstone", "python3native", "pythonnative", d)}

CFLAGS_append = " \
    -I${STAGING_INCDIR}/dbus-1.0 \
    -I${STAGING_LIBDIR}/dbus-1.0/include \
    -I${STAGING_INCDIR}/ccsp \
    "

LDFLAGS_append = " \
    -ldbus-1 \
    -lsyscfg \
    "
CFLAGS += " -Wall -Werror -Wextra "

do_compile_prepend () {
    (${PYTHON} ${STAGING_BINDIR_NATIVE}/dm_pack_code_gen.py ${S}/config/TR181-EPON.XML ${S}/source/EPONAgentSsp/dm_pack_datamodel.c)
}

do_install_append () {
    # Config files and scripts
    install -d ${D}/usr/ccsp/epon
    ln -sf /usr/bin/CcspEPONAgentSsp ${D}/usr/ccsp/epon/CcspEPONAgentSsp
    install -m 644 ${S}/config/CcspEPONDM.cfg ${D}/usr/ccsp/epon/CcspEPONDM.cfg
    install -m 644 ${S}/config/CcspEPON.cfg ${D}/usr/ccsp/epon/CcspEPON.cfg
}

FILES_${PN} += " \
    /usr/ccsp/epon/ \
    /usr/ccsp/epon/CcspEPONAgentSsp \
    /usr/ccsp/epon/CcspEPONDM.cfg \
    /usr/ccsp/epon/CcspEPON.cfg \
"

FILES_${PN}-dbg = " \
    ${prefix}/ccsp/epon/.debug \
    ${prefix}/src/debug \
    ${bindir}/.debug \
    ${libdir}/.debug \
"
