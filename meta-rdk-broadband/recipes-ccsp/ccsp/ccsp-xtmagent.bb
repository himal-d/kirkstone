SUMMARY = "CCSP XTM Agent component"

LICENSE = "CLOSED"
#LICENSE = "Apache-2.0"
#LIC_FILES_CHKSUM = "file://LICENSE;md5=175792518e4ac015ab6696d16c4f607e"

DEPENDS = "ccsp-common-library dbus rdk-logger utopia hal-xtm"

require ccsp_common.inc

SRC_URI ="${RDKB_CCSP_ROOT_GIT}/XTMAgent/generic;protocol=${RDK_GIT_PROTOCOL};branch=${CCSP_GIT_BRANCH};name=XTMAgent"
#SRC_URI += "file://xtmagent.tar.gz"

SRCREV_XTMAgent = "${AUTOREV}"
SRCREV_FORMAT = "XTMAgent"

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
    install -d ${D}/usr/ccsp/xtmagent
    install -d ${D}${bindir}
    install -m 755 ${B}/source/XTMAgent/xtmagent ${D}${bindir}
    install -m 644 ${S}/config/XTMAgent.xml ${D}/usr/ccsp/xtmagent/
}

FILES_${PN} = " \
   ${bindir}/xtmagent \
   ${prefix}/ccsp/xtmagent/XTMAgent.xml \
"

FILES_${PN}-dbg = " \
    ${prefix}/ccsp/xtmagent/.debug \
    /usr/src/debug \
    ${bindir}/.debug \
    ${libdir}/.debug \
"
