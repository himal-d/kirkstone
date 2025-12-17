PV_kirkstone = "${RDK_RELEASE}+git${SRCPV}"

inherit coverity

DEPENDS_append = " breakpad breakpad-wrapper "
DEPENDS_append = " ${@bb.utils.contains('DISTRO_FEATURES', 'safec', ' safec', '', d)}"

CFLAGS += "-I${STAGING_INCDIR}/breakpad "
CXXFLAGS += "-I${STAGING_INCDIR}/breakpad "

LDFLAGS += "-lbreakpadwrapper -lpthread"
