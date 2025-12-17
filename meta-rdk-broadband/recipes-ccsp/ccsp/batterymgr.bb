SUMMARY = "Battery Manager"
LICENSE = "Apache-2.0"
LIC_FILES_CHKSUM = "file://LICENSE;md5=175792518e4ac015ab6696d16c4f607e"

require recipes-ccsp/ccsp/ccsp_common.inc
DEPENDS = "ccsp-common-library rbus rdk-logger breakpad breakpad-wrapper telemetry utopia"

SRC_URI = "${CMF_GIT_ROOT}/rdkb/components/opensource/ccsp/BatteryManager;protocol=${CMF_GIT_PROTOCOL};branch=${CMF_GIT_BRANCH};name=batterymgr"

SRCREV = "${AUTOREV}"
PV = "${RDK_RELEASE}+git${SRCPV}"

S = "${WORKDIR}/git"

DEPENDS += "glib-2.0"

CFLAGS_append = " \
      -I${STAGING_INCDIR} \
      -I${STAGING_INCDIR}/ccsp \
      -I${STAGING_INCDIR}/rbus \
      -I${STAGING_INCDIR}/breakpad \
      -I ${STAGING_INCDIR}/syscfg \
      "

LDFLAGS_append = " \
    -ldbus-1 \
    -lrdkloggers \
    -lrbus \
"

# generating minidumps symbols
inherit breakpad-wrapper
BREAKPAD_BIN_append = " batterymgr"

LDFLAGS += "-lbreakpadwrapper -lpthread"


inherit cmake

do_install () {
    install -d ${D}${bindir}
    install -d ${D}${libdir}

    install -m 0755 ${B}/source/batterymgr ${D}${bindir}/batterymgr
    install -m 0755 ${B}/hal/ble/battery_hal_test ${D}${bindir}/battery_hal_test

    install -m 0755 ${B}/hal/ble/libbattery_hal_bluetooth.so.1 ${D}${libdir}/
    ln -s libbattery_hal_bluetooth.so.1 ${D}${libdir}/libbattery_hal_bluetooth.so
}

FILES_${PN} = " \
   ${bindir}/* \
   ${libdir}/* \
"
