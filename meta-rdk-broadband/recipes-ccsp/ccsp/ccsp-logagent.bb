SUMMARY = "This receipe provides log agent support."
SECTION = "console/utils"

LICENSE = "Apache-2.0"
LIC_FILES_CHKSUM = "file://LICENSE;md5=175792518e4ac015ab6696d16c4f607e"

PV = "${RDK_RELEASE}+git${SRCPV}"

DEPENDS = "ccsp-common-library dbus rdk-logger utopia"
DEPENDS_append = " ${@bb.utils.contains('DISTRO_FEATURES', 'systemd', 'systemd', '', d)}"
DEPENDS_append = " ${@bb.utils.contains('DISTRO_FEATURES', 'safec', ' safec', " ", d)}"

require recipes-ccsp/ccsp/ccsp_common.inc

SRC_URI = "${CMF_GIT_ROOT}/rdkb/components/generic/CcspLogAgent;protocol=${CMF_GIT_PROTOCOL};branch=${CMF_GIT_BRANCH};name=LogAgent"
SRCREV_LogAgent = "${AUTOREV}"
SRCREV_FORMAT = "LogAgent"

S = "${WORKDIR}/git"

inherit autotools pkgconfig coverity ${@bb.utils.contains("DISTRO_FEATURES", "kirkstone", "python3native", "pythonnative", d)}

CFLAGS_append = " ${@bb.utils.contains('DISTRO_FEATURES', 'safec',  ' `pkg-config --cflags libsafec`', '-fPIC', d)}"

LDFLAGS_append = " ${@bb.utils.contains('DISTRO_FEATURES', 'safec', ' `pkg-config --libs libsafec`', '', d)}"
LDFLAGS_remove = " ${@bb.utils.contains('DISTRO_FEATURES', 'safec', '-lsafec-3.5', '', d)}"
LDFLAGS_append_dunfell = " ${@bb.utils.contains('DISTRO_FEATURES', 'safec', '-lsafec-3.5.1', '', d)}"
LDFLAGS_append_kirkstone = " ${@bb.utils.contains('DISTRO_FEATURES', 'safec', ' -lsafec ', '', d)}"
CFLAGS_append = " ${@bb.utils.contains('DISTRO_FEATURES', 'safec', '', ' -DSAFEC_DUMMY_API', d)}"

EXTRA_OECONF_append = " ${@bb.utils.contains('DISTRO_FEATURES', 'systemd', '--enable-notify', '', d)}"
EXTRA_OECONF_append  = " --with-ccsp-platform=bcm --with-ccsp-arch=arm "

CFLAGS += " -Wall -Werror -Wextra "

CFLAGS_append = " \
    -I=${includedir}/dbus-1.0 \
    -I=${libdir}/dbus-1.0/include \
    -I=${includedir}/ccsp \
    "

LDFLAGS_append = " \
    -ldbus-1 \
    "

do_compile_prepend () {
	(${PYTHON} ${STAGING_BINDIR_NATIVE}/dm_pack_code_gen.py ${S}/scripts/LogAgent.xml ${S}/source/LogComponent/dm_pack_datamodel.c)
}

LDFLAGS_append = " -lpthread"
LDFLAGS_remove_morty = " -lpthread"

do_install_append () {
    # Config files and scripts
    install -d ${D}${prefix}/ccsp/logagent
    install -m 644 ${S}/scripts/msg_daemon.cfg ${D}${prefix}/ccsp/logagent/msg_daemon.cfg
}

FILES_${PN} += "${prefix}/ccsp/logagent"
