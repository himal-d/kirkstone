DEPENDS += "cjson"
DEPENDS_remove = "mountutils"

LDFLAGS += "-lcjson"

PV_kirkstone = "${RDK_RELEASE}+git${SRCPV}"
