SRC_URI_remove = "${RDKB_CCSP_ROOT_GIT}/RdkInterDeviceManager/generic;protocol=${RDK_GIT_PROTOCOL};branch=${CCSP_GIT_BRANCH};name=InterDeviceManager"
SRC_URI += "${CMF_GIT_ROOT}/rdkb/components/opensource/ccsp/RdkInterDeviceManager;protocol=${CMF_GIT_PROTOCOL};branch=${CMF_GIT_BRANCH};name=InterDeviceManager"

inherit coverity

DEPENDS += "breakpad breakpad-wrapper xupnp"

CFLAGS += "-I${STAGING_INCDIR}/breakpad "
CXXFLAGS += "-I${STAGING_INCDIR}/breakpad "

LDFLAGS += "-lbreakpadwrapper -lpthread  -lstdc++ -lupnpidm"
