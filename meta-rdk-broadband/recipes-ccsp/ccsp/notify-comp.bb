SUMMARY = "This receipe provides notify-comp support."
SECTION = "console/utils"

LICENSE = "Apache-2.0"
LIC_FILES_CHKSUM = "file://LICENSE;md5=8da35c40378155af4c5404b8f72d1237"

PV = "${RDK_RELEASE}+git${SRCPV}"
DEPENDS = "ccsp-common-library dbus rdk-logger utopia breakpad breakpad-wrapper"
DEPENDS_append = " ${@bb.utils.contains('DISTRO_FEATURES', 'safec', ' safec', " ", d)}"

require recipes-ccsp/ccsp/ccsp_common.inc

SRC_URI = "${CMF_GIT_ROOT}/rdkb/components/generic/notify_comp;protocol=${CMF_GIT_PROTOCOL};branch=${CMF_GIT_BRANCH};name=notify-comp"
SRCREV_notify-comp = "${AUTOREV}"
SRCREV_FORMAT = "notify-comp"

S = "${WORKDIR}/git/notify_comp"
inherit autotools pkgconfig breakpad-wrapper coverity ${@bb.utils.contains("DISTRO_FEATURES", "kirkstone", "python3native", "pythonnative", d)} breakpad-logmapper

CFLAGS_append = " ${@bb.utils.contains('DISTRO_FEATURES', 'safec',  ' `pkg-config --cflags libsafec`', '-fPIC', d)}"

LDFLAGS_append = " ${@bb.utils.contains('DISTRO_FEATURES', 'safec', ' `pkg-config --libs libsafec`', '', d)}"
CFLAGS_append = " ${@bb.utils.contains('DISTRO_FEATURES', 'safec', '', ' -DSAFEC_DUMMY_API', d)}"

CFLAGS += " -Wall -Werror -Wextra -Wno-pointer-sign -Wno-sign-compare -Wno-unused-parameter"

BREAKPAD_BIN_append = " notify_comp"

LDFLAGS += "-lbreakpadwrapper -lpthread -lstdc++"

LDFLAGS_append = " -lrt"
LDFLAGS_remove_morty = " -lrt"

#generating minidumps
PACKAGECONFIG_append = " breakpad"

CFLAGS_append = " \
    -I=${includedir}/ccsp \
    "
do_compile_prepend () {
    (${PYTHON} ${STAGING_BINDIR_NATIVE}/dm_pack_code_gen.py ${S}/scripts/NotifyComponent.xml ${S}/source/NotifyComponent/dm_pack_datamodel.c)
}

do_install_append_armeb () {
    # Config files and scripts
    install -d ${D}${exec_prefix}/ccsp/notify-comp
    install -m 644 ${S}/scripts/msg_daemon.cfg ${D}${exec_prefix}/ccsp/notify-comp/msg_daemon.cfg
}

do_install_append_puma7 () {
    # Config files and scripts
    install -d ${D}${exec_prefix}/ccsp/notify-comp
    install -m 644 ${S}/scripts/msg_daemon.cfg ${D}${exec_prefix}/ccsp/notify-comp/msg_daemon.cfg
}

do_install_append_mips () {
    # Config files and scripts
    install -d ${D}${exec_prefix}/ccsp/notify-comp
    install -m 644 ${S}/scripts/msg_daemon.cfg ${D}${exec_prefix}/ccsp/notify-comp/msg_daemon.cfg
}
do_install_append_bcm3390(){
    # Config files and scripts
    install -d ${D}${exec_prefix}/ccsp/notify-comp
    install -m 644 ${S}/scripts/msg_daemon.cfg ${D}${exec_prefix}/ccsp/notify-comp/msg_daemon.cfg
}

FILES_${PN} += "${exec_prefix}/ccsp/notify-comp"

# Breakpad processname and logfile mapping
BREAKPAD_LOGMAPPER_PROCLIST = "notify_comp"
BREAKPAD_LOGMAPPER_LOGLIST = "NOTIFYLog.txt.0"
