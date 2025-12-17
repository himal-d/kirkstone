SRC_URI_remove = "${RDKB_CCSP_CPC_ROOT_GIT}/CoreNetLib/generic;protocol=${RDK_GIT_PROTOCOL};branch=${CCSP_GIT_BRANCH};name=CoreNetLib"
SRC_URI += "${CMF_GIT_ROOT}/rdkb/components/opensource/ccsp/CoreNetLib;protocol=${CMF_GIT_PROTOCOL};branch=${CMF_GIT_BRANCH};name=CoreNetLib"

PV_kirkstone = "${RDK_RELEASE}+git${SRCPV}"
inherit coverity
