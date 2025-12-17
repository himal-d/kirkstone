inherit breakpad-logmapper
DEPENDS += " utopia "
CFLAGS_append = " \
    -I${STAGING_INCDIR}/syscfg \
    "
LDFLAGS +=" -lsyscfg"
# Breakpad processname and logfile mapping
BREAKPAD_LOGMAPPER_PROCLIST = "parodus"
BREAKPAD_LOGMAPPER_LOGLIST = "PARODUSlog.txt.0"
