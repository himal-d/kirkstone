SRC_URI_remove = "${RDKB_CCSP_ROOT_GIT}/RdkPlatformManager/generic;protocol=${RDK_GIT_PROTOCOL};branch=${CCSP_GIT_BRANCH};name=FwUpgradeManager"
SRC_URI += "${CMF_GIT_ROOT}/rdkb/components/opensource/ccsp/RdkPlatformManager;protocol=${CMF_GIT_PROTOCOL};branch=${CMF_GIT_BRANCH};name=FwUpgradeManager"

inherit coverity

DEPENDS += "breakpad breakpad-wrapper"

CFLAGS += "-I${STAGING_INCDIR}/breakpad "
CXXFLAGS += "-I${STAGING_INCDIR}/breakpad "

LDFLAGS += "-lbreakpadwrapper -lpthread"
