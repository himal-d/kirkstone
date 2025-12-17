SRC_URI_remove = "${RDK_GENERIC_ROOT_GIT}/jst/generic;protocol=${RDK_GIT_PROTOCOL};branch=${RDK_GIT_BRANCH}"
SRC_URI += "${CMF_GIT_ROOT}/rdk/components/generic/jst;protocol=${CMF_GIT_PROTOCOL};branch=${CMF_GIT_BRANCH}"

inherit coverity
