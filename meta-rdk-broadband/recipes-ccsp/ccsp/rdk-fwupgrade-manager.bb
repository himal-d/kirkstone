SUMMARY = "RDK Firmware Upgrade Manager component"

LICENSE = "Apache-2.0"
LIC_FILES_CHKSUM = "file://LICENSE;md5=175792518e4ac015ab6696d16c4f607e"

DEPENDS = "ccsp-common-library hal-cm dbus rdk-logger utopia halinterface hal-fwupgrade libunpriv"
require ccsp_common.inc

SRC_URI ="${RDKB_CCSP_ROOT_GIT}/RdkPlatformManager/generic;protocol=${RDK_GIT_PROTOCOL};branch=${CCSP_GIT_BRANCH};name=FwUpgradeManager"

SRCREV_FwUpgradeManager = "${AUTOREV}"
SRCREV_FORMAT = "FwUpgradeManager"

PV = "${RDK_RELEASE}+git${SRCPV}"

S = "${WORKDIR}/git"

EXTRA_OECONF_append  = " ${@bb.utils.contains('DISTRO_FEATURES','kirkstone','','--with-ccsp-platform=bcm --with-ccsp-arch=arm',d)} "

inherit autotools pkgconfig

do_compile_prepend () {
    (${PYTHON} ${STAGING_BINDIR_NATIVE}/dm_pack_code_gen.py ${S}/config/RdkFwUpgradeManager.xml ${S}/source/FwUpgradeManager/dm_pack_datamodel.c)
}

CFLAGS_append = " \
    -I${STAGING_INCDIR} \
    -I${STAGING_INCDIR}/dbus-1.0 \
    -I${STAGING_LIBDIR}/dbus-1.0/include \
    -I${STAGING_INCDIR}/ccsp \
    -I ${STAGING_INCDIR}/syscfg \
    -I ${STAGING_INCDIR}/sysevent \
    "

LDFLAGS += " -lprivilege"

CFLAGS_append = " ${@bb.utils.contains('DISTRO_FEATURES', 'safec', ' -fPIC -I${STAGING_INCDIR}/libsafec', '-fPIC', d)}"
CFLAGS_append  = " ${@bb.utils.contains('DISTRO_FEATURES', 'rdkb_wan_manager', '-DFEATURE_RDKB_WAN_MANAGER', '', d)}"

LDFLAGS_append = " -ldbus-1"
LDFLAGS_remove_morty = " -ldbus-1"

do_configure[depends] += "ccsp-common-library:do_install"

do_install_append () {
    # Config files and scripts
    install -d ${D}${exec_prefix}/rdk/fwupgrademanager
    ln -sf ${bindir}/fwupgrademanager ${D}${exec_prefix}/rdk/fwupgrademanager/fwupgrademanager
    install -m 644 ${S}/config/RdkFwUpgradeManager.xml ${D}/usr/rdk/fwupgrademanager/
}


FILES_${PN} = " \
   ${exec_prefix}/rdk/fwupgrademanager/fwupgrademanager \
   ${exec_prefix}/rdk/fwupgrademanager/RdkFwUpgradeManager.xml \
   ${bindir}/* \
"

FILES_${PN}-dbg = " \
    ${exec_prefix}/ccsp/fwupgrademanager/.debug \
    /usr/src/debug \
    ${bindir}/.debug \
    ${libdir}/.debug \
"
