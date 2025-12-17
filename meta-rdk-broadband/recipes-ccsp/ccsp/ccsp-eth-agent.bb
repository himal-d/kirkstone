SUMMARY = "This receipe provides test component support."
SECTION = "console/utils"

LICENSE = "Apache-2.0"
LIC_FILES_CHKSUM = "file://LICENSE;md5=175792518e4ac015ab6696d16c4f607e"

DEPENDS = "ccsp-common-library dbus utopia hal-ethsw hal-platform curl ccsp-lm-lite libunpriv"
DEPENDS_append = " ${@bb.utils.contains('DISTRO_FEATURES', 'safec', ' safec', " ", d)}"
DEPENDS_append = " ${@bb.utils.contains('DISTRO_FEATURES', 'WanFailOverSupportEnable', ' rbus ', " ", d)}"

require ccsp_common.inc

SRC_URI = "${CMF_GIT_ROOT}/rdkb/components/opensource/ccsp/CcspEthAgent;protocol=${CMF_GIT_PROTOCOL};branch=${CMF_GIT_BRANCH};name=CcspEthAgent"
CFLAGS += " -Wall -Werror -Wextra -Wno-format-overflow -Wno-format-truncation -Wno-array-bounds"

S = "${WORKDIR}/git"

PV = "${RDK_RELEASE}+git${SRCPV}"
SRCREV = "${AUTOREV}"
SRCREV_FORMAT = "${AUTOREV}"

inherit autotools ${@bb.utils.contains("DISTRO_FEATURES", "kirkstone", "python3native", "pythonnative", d)} breakpad-logmapper

PACKAGECONFIG ?= "dropearly"
PACKAGECONFIG[dropearly] = "--enable-dropearly,--disable-dropearly"
CFLAGS_append = " ${@bb.utils.contains('DISTRO_FEATURES', 'safec',  ' `pkg-config --cflags libsafec`', '-fPIC', d)}"

LDFLAGS_append = " ${@bb.utils.contains('DISTRO_FEATURES', 'safec', ' `pkg-config --libs libsafec`', '', d)}"
LDFLAGS_remove = "${@bb.utils.contains('DISTRO_FEATURES', 'safec', '-lsafec-3.5', '', d)}"
LDFLAGS_append_dunfell = "${@bb.utils.contains('DISTRO_FEATURES', 'safec', ' -lsafec-3.5.1 ', '', d)}"
LDFLAGS_append_kirkstone = " ${@bb.utils.contains('DISTRO_FEATURES', 'safec', ' -lsafec ', '', d)}"
CFLAGS_append = " ${@bb.utils.contains('DISTRO_FEATURES', 'safec', '', ' -DSAFEC_DUMMY_API', d)}"
CFLAGS_append  = " ${@bb.utils.contains('DISTRO_FEATURES', 'rdkb_wan_manager', ' -DFEATURE_RDKB_WAN_MANAGER', '', d)}"
CFLAGS_append = " ${@bb.utils.contains('DISTRO_FEATURES', 'ethstats', '-DETH_STATS_ENABLED', '', d)}"
LDFLAGS_append = " -lrt"
LDFLAGS_remove_morty = " -lrt"

EXTRA_OECONF_append = " ${@bb.utils.contains('DISTRO_FEATURES', 'WanFailOverSupportEnable', ' --enable-wanfailover ', '', d)}"

CFLAGS_append = " \
    -I${STAGING_INCDIR} \
    -I${STAGING_INCDIR}/dbus-1.0 \
    -I${STAGING_LIBDIR}/dbus-1.0/include \
    -I${STAGING_INCDIR}/ccsp \
    -I${STAGING_INCDIR}/utapi \
    -I${STAGING_INCDIR}/utctx \
    -I${STAGING_INCDIR}/ulog \
    -I${STAGING_INCDIR}/syscfg \
    "
CFLAGS_append  = " ${@bb.utils.contains('DISTRO_FEATURES', 'WanFailOverSupportEnable', ' -I=${includedir}/rbus ', '', d)}"
CFLAGS_append  = " ${@bb.utils.contains('DISTRO_FEATURES', 'RbusBuildFlagEnable', ' -I=${includedir}/rbus ', '', d)}"

LDFLAGS_append = " \
    -lccsp_common \
    -ldbus-1 \
    -lutctx \
    -lutapi \
    -lrt \
    -lprivilege \
    "

LDFLAGS_append = " ${@bb.utils.contains('DISTRO_FEATURES', 'RbusBuildFlagEnable', ' -lrbus ', '', d)}"
LDFLAGS_append = " ${@bb.utils.contains('DISTRO_FEATURES', 'WanFailOverSupportEnable', ' -lrbus ', '', d)}"
LDFLAGS_append = " ${@bb.utils.contains('DISTRO_FEATURES', 'WanFailOverSupportEnable', ' -lsysevent ', '', d)}"

do_compile_prepend () {
	if ${@bb.utils.contains('DISTRO_FEATURES', 'rdkb_wan_manager', 'true', 'false', d)}; then
    		sed -i '2i <?define FEATURE_RDKB_WAN_MANAGER=True?>' ${S}/config/TR181-EthAgent.xml
   	fi
        if ${@bb.utils.contains('DISTRO_FEATURES', 'rdkb_wan_upstream', 'true', 'false', d)}; then
                sed -i '2i <?define FEATURE_RDKB_WAN_UPSTREAM=True?>' ${S}/config/TR181-EthAgent.xml
        fi
        if ${@bb.utils.contains('DISTRO_FEATURES', 'rdkb_auto_port_switch', 'true', 'false', d)}; then
                sed -i '2i <?define FEATURE_RDKB_AUTO_PORT_SWITCH=True?>' ${S}/config/TR181-EthAgent.xml
        fi
    (${PYTHON} ${STAGING_BINDIR_NATIVE}/dm_pack_code_gen.py ${S}/config/TR181-EthAgent.xml ${S}/source/EthSsp/dm_pack_datamodel.c)
}

do_install_append () {
    # Config files and scripts
    install -d ${D}${exec_prefix}/ccsp/ethagent
    install -m 644 ${S}/config/TR181-EthAgent.xml ${D}${exec_prefix}/ccsp/ethagent/TR181-EthAgent.xml
}

FILES_${PN} += " ${exec_prefix}/ccsp/ethagent"

# Breakpad processname and logfile mapping
BREAKPAD_LOGMAPPER_PROCLIST = "CcspEthAgent"
BREAKPAD_LOGMAPPER_LOGLIST = "ETHAGENTLog.txt.0"
