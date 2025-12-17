SRC_URI_remove = "git://github.com/xmidt-org/parodus.git"
SRC_URI += "git://github.com/xmidt-org/parodus.git;protocol=https;branch=master"

DEPENDS += "breakpad breakpad-wrapper"

CFLAGS += "-I${STAGING_INCDIR}/breakpad "
CXXFLAGS += "-I${STAGING_INCDIR}/breakpad "

LDFLAGS += "-lbreakpadwrapper"
