SRC_URI = "${RDK_COMPONENTS_ROOT_GIT}/rdkssa/generic;protocol=${RDK_GIT_PROTOCOL};branch=${RDK_GIT_BRANCH};name=rdk-oss-ssa"
SRC_URI = "${CMF_GIT_ROOT}/rdk/components/generic/rdkssa;protocol=${CMF_GIT_PROTOCOL};branch=${CMF_GIT_BRANCH};name=rdk-oss-ssa"

inherit coverity
