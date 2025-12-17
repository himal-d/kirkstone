SRC_URI_remove = "${RDKB_COMPONENTS_ROOT_GIT}/generic/json-rpc/generic;protocol=${RDK_GIT_PROTOCOL};branch=${CCSP_GIT_BRANCH};name=json_hal"
SRC_URI += "${CMF_GIT_ROOT}/rdkb/components/generic/json-rpc;protocol=${CMF_GIT_PROTOCOL};branch=${CMF_GIT_BRANCH};name=json_hal"

inherit coverity
