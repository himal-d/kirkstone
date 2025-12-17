inherit breakpad-logmapper
DEPENDS += " utopia libunpriv "
CFLAGS_append = " \
    -I${STAGING_INCDIR}/syscfg \
    "
LDFLAGS +=" -lprivilege -lsyscfg"
FILESEXTRAPATHS_prepend := "${THISDIR}/files:"
SRC_URI_append += "file://Webcfg_drop_root.patch"
# Breakpad processname and logfile mapping
BREAKPAD_LOGMAPPER_PROCLIST = "webconfig"
BREAKPAD_LOGMAPPER_LOGLIST = "WEBCONFIGlog.txt.0"
