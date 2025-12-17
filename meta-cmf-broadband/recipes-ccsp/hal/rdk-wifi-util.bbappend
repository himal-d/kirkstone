LIC_FILES_CHKSUM = "file://../LICENSE;md5=5d50b1d1fb741ca457897f9e370bc747"

SRC_URI_remove = "${RDKB_CCSP_ROOT_GIT}/hal/rdk-wifi-hal;protocol=${RDK_GIT_PROTOCOL};branch=${CCSP_GIT_BRANCH};name=rdk-wifi-util"
SRC_URI += "${CMF_GIT_ROOT}/rdkb/components/opensource/ccsp/hal/rdk-wifi-hal;protocol=${CMF_GIT_PROTOCOL};branch=${CMF_GIT_BRANCH};name=rdk-wifi-util"

# Add flags to support mesh wifi if the feature is available.
CFLAGS_append = " ${@bb.utils.contains('DISTRO_FEATURES', 'meshwifi', '-DENABLE_FEATURE_MESHWIFI', '', d)}"

inherit coverity
