SUMMARY = "JSON HAL Client and Server library"
LICENSE = "Apache-2.0"
LIC_FILES_CHKSUM = "file://LICENSE;md5=279c0d21cb7bc051383cef7cd415c938"

DEPENDS += " json-c json-schema-validator"

SRC_URI = "${RDKB_COMPONENTS_ROOT_GIT}/generic/json-rpc/generic;protocol=${RDK_GIT_PROTOCOL};branch=${CCSP_GIT_BRANCH};name=json_hal"

PV = "2.0+git${SRCPV}"
SRCREV_json_hal = "${AUTOREV}"

S = "${WORKDIR}/git"

inherit cmake pkgconfig

FILES_${PN} += "${libdir}/* \
                ${bindir}/* "

FILES_SOLIBSDEV = ""
INSANE_SKIP_${PN} += "dev-so"
