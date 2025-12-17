SUMMARY = "CCSP MoCA component"

LICENSE = "Apache-2.0"
LIC_FILES_CHKSUM = "file://LICENSE;md5=175792518e4ac015ab6696d16c4f607e"

DEPENDS = "ccsp-common-library webconfig-framework utopia hal-moca curl trower-base64 msgpack-c libunpriv"

DEPENDS_append = " ${@bb.utils.contains('DISTRO_FEATURES', 'safec', ' safec', " ", d)}"

require ccsp_common.inc

CFLAGS += " -Wall -Werror -Wextra -Wno-address -Wno-enum-conversion"


SRC_URI = "${CMF_GIT_ROOT}/rdkb/components/opensource/ccsp/CcspMoCA;protocol=${CMF_GIT_PROTOCOL};branch=${CMF_GIT_BRANCH};name=CcspMoCA"

SRCREV_CcspMoCA = "${AUTOREV}"
SRCREV_FORMAT = "CcspMoCA"

PV = "${RDK_RELEASE}+git${SRCPV}"

S = "${WORKDIR}/git"

inherit autotools pkgconfig ${@bb.utils.contains("DISTRO_FEATURES", "kirkstone", "python3native", "pythonnative", d)} breakpad-logmapper

CFLAGS_append = " ${@bb.utils.contains('DISTRO_FEATURES', 'safec',  ' `pkg-config --cflags libsafec`', '-fPIC', d)}"

LDFLAGS_append = " ${@bb.utils.contains('DISTRO_FEATURES', 'safec', ' `pkg-config --libs libsafec`', '', d)}"
LDFLAGS_remove = "${@bb.utils.contains('DISTRO_FEATURES', 'safec', '-lsafec-3.5', '', d)}"
LDFLAGS_append_dunfell = "${@bb.utils.contains('DISTRO_FEATURES', 'safec', ' -lsafec-3.5.1 ', '', d)}"
LDFLAGS_append_kirkstone = " ${@bb.utils.contains('DISTRO_FEATURES', 'safec', ' -lsafec ', '', d)}"
CFLAGS_append = " ${@bb.utils.contains('DISTRO_FEATURES', 'safec', '', ' -DSAFEC_DUMMY_API', d)}"

CFLAGS_append = " \
    -I${STAGING_INCDIR} \
    -I${STAGING_INCDIR}/dbus-1.0 \
    -I${STAGING_LIBDIR}/dbus-1.0/include \
    -I${STAGING_INCDIR}/ccsp \
    -I${STAGING_INCDIR}/utapi \
    -I${STAGING_INCDIR}/utctx \
    -I${STAGING_INCDIR}/ulog \
    -I${STAGING_INCDIR}/syscfg \
    -I${STAGING_INCDIR}/trower-base64 \
    -I${STAGING_INCDIR}/msgpackc \
    "

EXTRA_OECONF_append_mips = " --enable-notify"

CFLAGS_append += "-DCONFIG_VENDOR_CUSTOMER_COMCAST -DCONFIG_CISCO_HOTSPOT"

LDFLAGS_append = " \
    -ldbus-1 \
    -lutctx \
    -lutapi \
    -lmsgpackc \
    -ltrower-base64 \
    -lprivilege \
    "

LDFLAGS_append = " -lsyscfg -lsysevent"
LDFLAGS_remove_morty = " -lsyscfg -lsysevent"

do_compile_prepend () {
	(${PYTHON} ${STAGING_BINDIR_NATIVE}/dm_pack_code_gen.py ${S}/config/TR181-MoCA.XML ${S}/source/MoCASsp/dm_pack_datamodel.c)
}

do_install_append () {
    # Config files and scripts
    install -d ${D}/usr/ccsp/moca
    install -m 644 ${S}/config/CcspMoCA.cfg ${D}/usr/ccsp/moca/CcspMoCA.cfg
    install -m 644 ${S}/config/CcspMoCADM.cfg ${D}/usr/ccsp/moca/CcspMoCADM.cfg
    install -m 0755 ${S}/scripts/MoCA_isolation.sh ${D}/usr/ccsp/moca/MoCA_isolation.sh
    install -m 0755 ${S}/scripts/moca_whitelist_ctl.sh ${D}/usr/ccsp/moca/moca_whitelist_ctl.sh
    install -m 0755 ${S}/scripts/moca_mroute.sh ${D}/usr/ccsp/moca/moca_mroute.sh
    install -m 0755 ${S}/scripts/moca_mroute_ip.sh ${D}/usr/ccsp/moca/moca_mroute_ip.sh
}

PACKAGES += "${PN}-ccsp"

FILES_${PN}-ccsp += " \
    ${prefix}/ccsp/moca/CcspMoCA.cfg  \
    ${prefix}/ccsp/moca/CcspMoCADM.cfg  \
    ${prefix}/ccsp/moca/MoCA_isolation.sh  \
    ${prefix}/ccsp/moca/moca_whitelist_ctl.sh  \
    ${prefix}/ccsp/moca/moca_mroute.sh  \
    ${prefix}/ccsp/moca/moca_mroute_ip.sh  \
"

FILES_${PN}-dbg = " \
    ${prefix}/ccsp/moca/.debug \
    ${prefix}/src/debug \
    ${bindir}/.debug \
    ${libdir}/.debug \
"

# Breakpad processname and logfile mapping
BREAKPAD_LOGMAPPER_PROCLIST = "CcspMoCA"
BREAKPAD_LOGMAPPER_LOGLIST = "MOCAlog.txt.0,moca_telemetry.txt"
