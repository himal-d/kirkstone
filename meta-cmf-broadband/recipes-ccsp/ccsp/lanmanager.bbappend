SRC_URI_remove = "${RDKB_CCSP_ROOT_GIT}/LanManager/generic;protocol=${RDK_GIT_PROTOCOL};branch=${CCSP_GIT_BRANCH};name=LanManager"
SRC_URI += "${CMF_GIT_ROOT}/rdkb/components/opensource/ccsp/LanManager;protocol=${CMF_GIT_PROTOCOL};branch=${CMF_GIT_BRANCH};name=LanManager"

inherit coverity

