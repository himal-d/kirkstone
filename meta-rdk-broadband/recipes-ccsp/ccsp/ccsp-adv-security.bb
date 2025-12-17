SUMMARY = "Advanced Security Agent"
LICENSE = "Apache-2.0"
LIC_FILES_CHKSUM = "file://LICENSE;md5=3b83ef96387f14655fc854ddc3c6bd57"
DEPENDS = "ccsp-common-library webconfig-framework utopia dbus rdk-logger hal-platform hal-cm trower-base64 msgpack-c"
DEPENDS_append = " ${@bb.utils.contains('DISTRO_FEATURES', 'safec', ' safec', " ", d)}"
require recipes-ccsp/ccsp/ccsp_common.inc
SRC_URI = "${RDKB_CCSP_ROOT_GIT}/CcspAdvSecurity/generic;protocol=${RDK_GIT_PROTOCOL};branch=${CCSP_GIT_BRANCH};name=ccsp-adv-security"
SRCREV_ccsp-adv-security = "${AUTOREV}"
PV = "${RDK_RELEASE}+git${SRCPV}"
CFLAGS_append = " ${@bb.utils.contains('DISTRO_FEATURES', 'safec',  ' `pkg-config --cflags libsafec`', '-fPIC', d)}"
LDFLAGS_append = " ${@bb.utils.contains('DISTRO_FEATURES', 'safec', ' `pkg-config --libs libsafec`', '', d)}"
CFLAGS_append = " ${@bb.utils.contains('DISTRO_FEATURES', 'safec', '', ' -DSAFEC_DUMMY_API', d)}"
CFLAGS_append = " \
    -I${STAGING_INCDIR}/libevent \
    -I${STAGING_INCDIR}/dbus-1.0 \
    -I${STAGING_LIBDIR}/dbus-1.0/include \
    -I${STAGING_INCDIR}/ccsp \
    -I${STAGING_INCDIR}/openssl/include \
    -I${STAGING_INCDIR}/trower-base64 \
    "
LDFLAGS_append = " \
    -ldbus-1 \
    -lrdkloggers \
    -lcjson \
    -lbreakpadwrapper \
"
RDEPENDS_${PN}_append = " bash"
RDEPENDS_${PN}_remove_morty = "bash"

S = "${WORKDIR}/git"

CFLAGS += " -Wall -Werror -Wextra "

do_compile_prepend () {
       (${PYTHON} ${STAGING_BINDIR_NATIVE}/dm_pack_code_gen.py ${S}/config/TR181-AdvSecurity.xml ${S}/source/AdvSecuritySsp/dm_pack_datamodel.c)
}

inherit autotools coverity ${@bb.utils.contains("DISTRO_FEATURES", "kirkstone", "python3native", "pythonnative", d)} breakpad-logmapper

do_install_append () {
    # Config files and scripts
    install -d ${D}/usr/ccsp/advsec
    install -d ${D}/usr/include/advsec
    install -d ${D}/var/empty
    # Binaries, Libraries, Include, Start_script
    install -m 0755 ${S}/scripts/start_adv_security.sh -t ${D}/usr/ccsp/advsec
    install -m 0755 ${S}/scripts/advsec_log_fp_status.sh -t ${D}/usr/ccsp/advsec
    install -m 0755 ${S}/scripts/advsec_cpu_mem_recovery.sh -t ${D}/usr/ccsp/advsec
    ln -sf ../../../usr/bin/CcspAdvSecuritySsp ${D}/usr/ccsp/advsec/CcspAdvSecuritySsp
    install -m 755 ${S}/scripts/advsec.sh -t ${D}/usr/ccsp/advsec
}

PACKAGES += "${PN}-ccsp"
INSANE_SKIP_${PN} += "ldflags libdir"

FILES_${PN} += " \
    ${bindir}/CcspAdvSecuritySsp \
    ${prefix}/ccsp/* \
    ${prefix}/ccsp/advsec/CcspAdvSecuritySsp \
    ${prefix}/ccsp/advsec/start_adv_security.sh \
    ${prefix}/ccsp/advsec/advsec_log_fp_status.sh \
    ${prefix}/ccsp/advsec/advsec_cpu_mem_recovery.sh \
    ${prefix}/ccsp/advsec/advsec.sh \
"

FILES_${PN}-dbg += " \
    ${prefix}/ccsp/advsec/.debug \
    ${prefix}/src/debug \
    ${bindir}/.debug \
    ${libdir}/.debug \
"

# Breakpad processname and logfile mapping
BREAKPAD_LOGMAPPER_PROCLIST = "CcspAdvSecurity"
BREAKPAD_LOGMAPPER_LOGLIST = "ADVSEClog.txt.0,agent.txt"

EXTRA_OECONF_append  = " --with-ccsp-arch=arm "
