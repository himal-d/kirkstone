SRC_URI_remove ="${RDKB_CCSP_ROOT_GIT}/RdkTelcoVoiceManager/generic;protocol=${RDK_GIT_PROTOCOL};branch=${CCSP_GIT_BRANCH};name=TelcoVOICEManager"
SRC_URI += "${CMF_GIT_ROOT}/rdkb/components/opensource/ccsp/RdkTelcoVoiceManager;protocol=${CMF_GIT_PROTOCOL};branch=${CMF_GIT_BRANCH};name=TelcoVOICEManager"
DEPENDS += "breakpad breakpad-wrapper json-hal-lib"

CFLAGS += "-I${STAGING_INCDIR}/breakpad "
CXXFLAGS += "-I${STAGING_INCDIR}/breakpad "

LDFLAGS += "-lbreakpadwrapper  -lpthread -lstdc++"

inherit coverity
