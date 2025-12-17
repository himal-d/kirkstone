DEPENDS += "breakpad breakpad-wrapper nanomsg"

CFLAGS += "-I${STAGING_INCDIR}/breakpad "
CXXFLAGS += "-I${STAGING_INCDIR}/breakpad "

LDFLAGS += "-lbreakpadwrapper -lpthread"

CFLAGS_append = " -DFEATURE_802_1P_COS_MARKING "
inherit coverity
