SUMMARY = "CCSP VLAN Agent component"

LICENSE = "CLOSED"
#LICENSE = "Apache-2.0"
#LIC_FILES_CHKSUM = "file://LICENSE;md5=175792518e4ac015ab6696d16c4f607e"

DEPENDS = "ccsp-common-library dbus rdk-logger utopia hal-vlan-eth hal-platform"

require ccsp_common.inc

SRC_URI ="${RDKB_CCSP_ROOT_GIT}/VLANAgent/generic;protocol=${RDK_GIT_PROTOCOL};branch=${CCSP_GIT_BRANCH};name=VLANAgent"
#SRC_URI += "file://vlanagent.tar.gz"

SRCREV_VLANAgent = "${AUTOREV}"
SRCREV_FORMAT = "VLANAgent"

#PV = "${RDK_RELEASE}"
PV = "${RDK_RELEASE}+git${SRCPV}"

S = "${WORKDIR}/git"
B = "${WORKDIR}/build"

EXTRA_OECONF_append  = " --with-ccsp-platform=bcm --with-ccsp-arch=arm "

inherit autotools pkgconfig

CFLAGS_append = " \
    -I${STAGING_INCDIR} \
    -I${STAGING_INCDIR}/dbus-1.0 \
    -I${STAGING_LIBDIR}/dbus-1.0/include \
    -I${STAGING_INCDIR}/ccsp \
    -I ${STAGING_INCDIR}/syscfg \
    -I ${STAGING_INCDIR}/sysevent \
    "

do_install () {
    # Config files and scripts
    install -d ${D}/usr/ccsp/vlanagent
    install -d ${D}${bindir}
    install -m 755 ${B}/source/VLANAgent/vlanagent ${D}${bindir}
    install -m 644 ${S}/config/VLANAgent.xml ${D}/usr/ccsp/vlanagent/
}

FILES_${PN} = " \
   ${bindir}/vlanagent \
   ${prefix}/ccsp/vlanagent/VLANAgent.xml \
"

FILES_${PN}-dbg = " \
    ${prefix}/ccsp/vlanagent/.debug \
    /usr/src/debug \
    ${bindir}/.debug \
    ${libdir}/.debug \
"
