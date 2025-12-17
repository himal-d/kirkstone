SUMMARY = "C wrapper for breakpad"

LICENSE = "Apache-2.0"
LIC_FILES_CHKSUM = "file://LICENSE;md5=175792518e4ac015ab6696d16c4f607e"

SRC_URI = "${CMF_GIT_ROOT}/rdk/components/generic/breakpad_wrapper;protocol=${CMF_GIT_PROTOCOL};branch=${CMF_GIT_BRANCH};name=breakpad_wrapper"

DEPENDS_broadband += "breakpad"
DEPENDS_client += "breakpad"
DEPENDS_hybrid += "breakpad"

SRCREV_breakpad_wrapper = "${AUTOREV}"
PV = "${RDK_RELEASE}+git${SRCPV}"

S = "${WORKDIR}/git"

inherit autotools coverity

CPPFLAGS_append = " \
    -I${STAGING_INCDIR}/breakpad/ \
    "

LDFLAGS_broadband += "-lbreakpad_client -lpthread"
LDFLAGS_client += "-lbreakpad_client -lpthread"
LDFLAGS_hybrid += "-lbreakpad_client -lpthread"

do_install_append () {
    # Config files and scripts
    install -d ${D}${includedir}/
    install -D -m 0644 ${S}/*.h ${D}${includedir}/
}


FILES_${PN} += "${libdir}/*.so"
