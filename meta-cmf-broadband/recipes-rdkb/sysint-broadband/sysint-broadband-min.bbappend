
SRC_URI_remove = "${RDKB_COMPONENTS_ROOT_GIT}/generic/sysint/generic;protocol=${RDK_GIT_PROTOCOL};branch=${RDK_GIT_BRANCH};name=sysintbroadband"
SRC_URI_remove = "${RDKB_COMPONENTS_ROOT_GIT}/generic/sysint/devices/${SYSINTB_DEVICE};module=.;protocol=${RDK_GIT_PROTOCOL};branch=${RDK_GIT_BRANCH};destsuffix=git/device;name=sysintdevice"

SRC_URI += "${CMF_GIT_ROOT}/rdkb/components/opensource/ccsp/sysint;protocol=${CMF_GIT_PROTOCOL};branch=${CMF_GIT_BRANCH};name=sysintbroadband"
SRC_URI += "${CMF_GIT_ROOT}/rdkb/devices/intel-x86-pc/emulator/sysint;module=.;protocol=${CMF_GIT_PROTOCOL};branch=${CMF_GIT_BRANCH};destsuffix=git/device;name=sysintdevice"
