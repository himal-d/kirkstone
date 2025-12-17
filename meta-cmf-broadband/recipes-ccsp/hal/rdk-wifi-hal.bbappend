SRC_URI_remove = "${RDKB_CCSP_ROOT_GIT}/hal/rdk-wifi-hal;protocol=${RDK_GIT_PROTOCOL};branch=${CCSP_GIT_BRANCH};name=rdk-wifi-hal"
SRC_URI += "${CMF_GIT_ROOT}/rdkb/components/opensource/ccsp/hal/rdk-wifi-hal;protocol=${CMF_GIT_PROTOCOL};branch=${CMF_GIT_BRANCH};name=rdk-wifi-hal"

inherit coverity

DEPENDS_remove = "mountutils"
