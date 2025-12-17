SUMMARY = "CCSP Power Manager"
LICENSE = "Apache-2.0"
LIC_FILES_CHKSUM = "file://LICENSE;md5=175792518e4ac015ab6696d16c4f607e"

DEPENDS = "ccsp-common-library utopia hal-cm hal-dhcpv4c hal-ethsw hal-moca hal-mso_mgmt hal-mta hal-platform hal-vlan hal-wifi dbus rdk-logger breakpad breakpad-wrapper"

require recipes-ccsp/ccsp/ccsp_common.inc

SRC_URI = "${CMF_GIT_ROOT}/rdkb/components/opensource/ccsp/PowerManager;protocol=${CMF_GIT_PROTOCOL};branch=${CMF_GIT_BRANCH};name=powermgr"

SRCREV_powermgr = "${AUTOREV}"
SRCREV_FORMAT = "powermgr"
PV = "${RDK_RELEASE}+git${SRCPV}"

CFLAGS_append = " \
    -I${STAGING_INCDIR}/dbus-1.0 \
    -I${STAGING_LIBDIR}/dbus-1.0/include \
    -I${STAGING_INCDIR}/ccsp \
    "
    
LDFLAGS_append = " \
    -ldbus-1 \
    -lrdkloggers \
"

S = "${WORKDIR}/git"

inherit autotools systemd breakpad-logmapper

# generating minidumps symbols
inherit breakpad-wrapper
BREAKPAD_BIN_append = " rdkbPowerMgr"

CFLAGS += " -Wall -Werror -Wextra -Wno-pointer-sign -Wno-unused-parameter -DINCLUDE_BREAKPAD "
LDFLAGS += "-lbreakpadwrapper -lpthread -lstdc++"

do_install_append () {
    # Config files and scripts
    install -d ${D}/usr/ccsp/pwrMgr
    install -m 755 ${S}/scripts/rdkb_power_manager.sh ${D}/usr/ccsp/pwrMgr/rdkb_power_manager.sh
    ln -sf /usr/bin/rdkbPowerMgr ${D}/usr/ccsp/pwrMgr/rdkbPowerMgr
}

PACKAGES += "${PN}-ccsp"

FILES_${PN}-ccsp = " \
    /fss/gw/usr/ccsp/* \
    ${prefix}/ccsp/pwrMgr/* \
    ${prefix}/ccsp/* \
"

FILES_${PN} = " \
    /usr/bin/rdkbPowerMgr \
    ${prefix}/ccsp/pwrMgr/rdkb_power_manager.sh \
    ${prefix}/ccsp/pwrMgr/rdkbPowerMgr \
"

FILES_${PN}-dbg = " \
    ${prefix}/ccsp/.debug \
    ${prefix}/src/debug \
    ${bindir}/.debug \
    ${libdir}/.debug \
"

# generating minidumps
PACKAGECONFIG_append = " breakpad"

# Breakpad processname and logfile mapping
BREAKPAD_LOGMAPPER_PROCLIST = "rdkbPowerMgr"
BREAKPAD_LOGMAPPER_LOGLIST = "POWERMGRLog.txt.0"
