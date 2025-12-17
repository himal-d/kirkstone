SUMMARY = "CCSP DSL Agent component"

LICENSE = "CLOSED"
#LICENSE = "Apache-2.0"
#LIC_FILES_CHKSUM = "file://LICENSE;md5=175792518e4ac015ab6696d16c4f607e"

DEPENDS = "ccsp-common-library dbus rdk-logger utopia hal-dsl avro-c"

require ccsp_common.inc

SRC_URI ="${RDKB_CCSP_ROOT_GIT}/DSLAgent/generic;protocol=${RDK_GIT_PROTOCOL};branch=${CCSP_GIT_BRANCH};name=DSLAgent"

SRCREV_DSLAgent = "${AUTOREV}"
SRCREV_FORMAT = "DSLAgent"

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
    -I${STAGING_INCDIR}/libparodus \
    "


DEPENDS_append = "${@bb.utils.contains("DISTRO_FEATURES", "seshat", " libseshat ", " ", d)}"
CFLAGS_append = "${@bb.utils.contains("DISTRO_FEATURES", "seshat", " -DENABLE_SESHAT ", " ", d)}"
LDFLAGS_append = "${@bb.utils.contains("DISTRO_FEATURES", "seshat", " -llibseshat ", " ", d)}"
CFLAGS_append = "\
    ${@bb.utils.contains("DISTRO_FEATURES", "seshat", "-I${STAGING_INCDIR}/libseshat ", " ", d)} \
"


do_install () {
    # Config files and scripts
    install -d ${D}/usr/ccsp/dslagent
    install -d ${D}${bindir}
    install -d ${D}${exec_prefix}/ccsp/harvester/
    install -m 755 ${B}/source/DSLAgent/dslagent ${D}${bindir}
    install -m 644 ${S}/config/DSLAgent.xml ${D}/usr/ccsp/dslagent
    install -m 644 ${S}/source/TR-181/integration_src.shared/XdslReport.avsc ${D}/usr/ccsp/harvester/
}


FILES_${PN} = " \
   ${bindir}/dslagent \
   ${prefix}/ccsp/dslagent/DSLAgent.xml \
   ${exec_prefix}/ccsp/harvester/XdslReport.avsc \
"

FILES_${PN}-dbg = " \
    ${prefix}/ccsp/dslagent/.debug \
    /usr/src/debug \
    ${bindir}/.debug \
    ${libdir}/.debug \
"
