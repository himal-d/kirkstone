inherit coverity

DEPENDS += " breakpad breakpad-wrapper utopia"

CFLAGS_append = " \
    -I${S}/source/GponManager \
    -I${S}/source/TR-181/middle_layer_src \
    -I${S}/source/TR-181/include \
    -I${STAGING_INCDIR}/breakpad \
    "

CXXFLAGS += "-I${STAGING_INCDIR}/breakpad "

LDFLAGS += "-lbreakpadwrapper -lpthread"
