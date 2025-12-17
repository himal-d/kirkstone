SRC_URI_remove = "${RDK_GENERIC_ROOT_GIT}/OvsAgent/generic;protocol=${RDK_GIT_PROTOCOL};branch=${RDK_GIT_BRANCH};name=ovs-agent"
SRC_URI += "${CMF_GIT_ROOT}/rdk/components/generic/OvsAgent;protocol=${CMF_GIT_PROTOCOL};branch=${CMF_GIT_BRANCH};name=ovs-agent"

inherit coverity
