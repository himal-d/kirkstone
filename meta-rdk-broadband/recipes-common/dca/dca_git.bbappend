DEPENDS += " ccsp-common-library"
require recipes-ccsp/ccsp/ccsp_common.inc
LDFLAGS += " -lccsp_common"
CFLAGS += " -DENABLE_RDKB_SUPPORT \
            -I${STAGING_INCDIR}/ccsp \
            -I${STAGING_INCDIR}/dbus-1.0 \
            -I${STAGING_LIBDIR}/dbus-1.0/include \
          "
#Enable ccsp message bus to get tr181 paramter as a new source to telemetry
EXTRA_OECONF += " --enable-tr181messagebus"
