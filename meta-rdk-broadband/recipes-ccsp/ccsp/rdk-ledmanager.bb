SUMMARY = "RDK LED Manager component"

LICENSE = "Apache-2.0"
LIC_FILES_CHKSUM = "file://LICENSE;md5=e32b0a505c9a82d64d7970df0a5c1ece"

DEPENDS = "ccsp-common-library rdk-logger utopia hal-platform hal-ledmanager libunpriv"

require ccsp_common.inc

SRC_URI ="${RDKB_CCSP_ROOT_GIT}/RdkLedManager/generic;protocol=${RDK_GIT_PROTOCOL};branch=${CCSP_GIT_BRANCH};name=LedManager"

SRCREV_LedManager = "${AUTOREV}"
SRCREV_FORMAT = "LedManager"

PV = "${RDK_RELEASE}+git${SRCPV}"

S = "${WORKDIR}/git"

inherit autotools pkgconfig

CFLAGS_append = " \
    -I${STAGING_INCDIR} \
    -I${STAGING_INCDIR}/dbus-1.0 \
    -I${STAGING_LIBDIR}/dbus-1.0/include \
    -I${STAGING_INCDIR}/ccsp \
    -I ${STAGING_INCDIR}/syscfg \
    -I ${STAGING_INCDIR}/sysevent \
    "
EXTRA_OECONF_append = " ${@bb.utils.contains('DISTRO_FEATURES', 'webconfigled', ' --enable-webconfigled ', '', d)}"
CFLAGS_append += " ${@bb.utils.contains('DISTRO_FEATURES', 'webconfigled', '-DLEDMGR_WEBCONFIG', '', d)} "

LDFLAGS += " -lprivilege"

LDFLAGS_append = " -ldbus-1"
LDFLAGS_remove_morty = " -ldbus-1"

do_install_append () {
    # Config files and scripts
    install -d ${D}${exec_prefix}/rdk/rdkledmanager
    ln -sf ${bindir}/rdkledmanager ${D}${exec_prefix}/rdk/rdkledmanager/rdkledmanager 
}


FILES_${PN} = " \
   ${exec_prefix}/rdk/rdkledmanager/rdkledmanager \
   ${bindir}/* \
"

FILES_${PN}-dbg = " \
    ${exec_prefix}/rdk/rdkledmanager/.debug \
    /usr/src/debug \
    ${bindir}/.debug \
    ${libdir}/.debug \
"
