SUMMARY = "This receipe provides utility to start parodus."
SECTION = "console/utils"

LICENSE = "Apache-2.0"
LIC_FILES_CHKSUM = "file://LICENSE;md5=3b83ef96387f14655fc854ddc3c6bd57"
DEPENDS = "cjson utopia breakpad breakpad-wrapper"
DEPENDS_append = " ${@bb.utils.contains('DISTRO_FEATURES', 'safec', ' safec', " ", d)}"
require recipes-ccsp/ccsp/ccsp_common.inc

# generating minidumps symbols
inherit breakpad-wrapper
BREAKPAD_BIN_append = " parodusStart"

CFLAGS += " -Wall -Werror -Wextra "

SRC_URI = "${CMF_GIT_ROOT}/rdkb/components/generic/startParodus;protocol=${CMF_GIT_PROTOCOL};branch=${CMF_GIT_BRANCH};name=startParodus"
SRCREV = "${AUTOREV}"
PV = "${RDK_RELEASE}+git${SRCPV}"

S = "${WORKDIR}/git"

EXTRA_OECONF_append  = " --with-ccsp-arch=arm "

inherit autotools pkgconfig
DEPENDS_append = " hal-platform hal-cm openssl cpgc lxy "
RDEPENDS_${PN} += " cjson hal-platform hal-cm utopia "

LDFLAGS_append = " -lbreakpadwrapper -lhal_platform -lcm_mgnt -lsyscfg -lcjson -lsysevent -lutapi -lutctx "

CFLAGS_append = " ${@bb.utils.contains('DISTRO_FEATURES', 'safec',  ' `pkg-config --cflags libsafec`', '-fPIC', d)}"

LDFLAGS_append = " ${@bb.utils.contains('DISTRO_FEATURES', 'safec', ' `pkg-config --libs libsafec`', '', d)}"
CFLAGS_append = " ${@bb.utils.contains('DISTRO_FEATURES', 'safec', '', ' -DSAFEC_DUMMY_API', d)}"

CFLAGS_append = " -I${STAGING_INCDIR} -I${STAGING_INCDIR}/ccsp -I${STAGING_INCDIR}/syscfg -I${STAGING_INCDIR}/cjson -DFEATURE_DNS_QUERY -DXPKI_CERT_SUPPORT"
CFLAGS_append = " ${@bb.utils.contains("DISTRO_FEATURES", "seshat", " -DENABLE_SESHAT ", " ", d)} "
CFLAGS_append = " ${@bb.utils.contains("DISTRO_FEATURES", "WanFailOverSupportEnable", " -DWAN_FAILOVER_SUPPORTED ", " ", d)} "
CFLAGS_append = "${@bb.utils.contains("DISTRO_FEATURES", "webconfig_bin", "-DENABLE_WEBCFGBIN ", " ", d)}"

# generating minidumps
PACKAGECONFIG_append = " breakpad"

FILES_${PN} += "/usr/bin/* "
