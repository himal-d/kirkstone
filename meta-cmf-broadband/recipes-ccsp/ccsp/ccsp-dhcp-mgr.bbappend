SRC_URI_remove = "${RDKB_CCSP_ROOT_GIT}/DhcpManager/generic;protocol=${RDK_GIT_PROTOCOL};branch=${CCSP_GIT_BRANCH};name=DhcpManager"
SRC_URI += "${CMF_GIT_ROOT}/rdkb/components/opensource/ccsp/DhcpManager;protocol=${CMF_GIT_PROTOCOL};branch=${CMF_GIT_BRANCH};name=DhcpManager"

inherit coverity

DEPENDS += " nanomsg"

CFLAGS_remove = " -DFEATURE_RDKB_WAN_MANAGER"
