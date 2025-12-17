SRC_URI_remove = "${RDK_GENERIC_ROOT_GIT}/bluetooth_leAppMgr/generic;protocol=${RDK_GIT_PROTOCOL};branch=${RDK_GIT_BRANCH}"
SRC_URI += "${CMF_GIT_ROOT}/rdk/components/generic/bluetooth_leAppMgr;protocol=${CMF_GIT_PROTOCOL};branch=${CMF_GIT_BRANCH}"

ENABLE_SAFEC = "--enable-safec=${@bb.utils.contains('DISTRO_FEATURES', 'safec', 'yes', 'no', d)}"
EXTRA_OECONF += " ${ENABLE_SAFEC}"
