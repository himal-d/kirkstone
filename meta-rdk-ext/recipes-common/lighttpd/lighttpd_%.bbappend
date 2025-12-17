FILESEXTRAPATHS_prepend := "${THISDIR}/${PN}:"

inherit logrotate

LOGROTATE_NAME    = "lighttpd"
LOGROTATE_LOGNAME_lighttpd = "lighttpd*.log"
#HDD_ENABLE
LOGROTATE_SIZE_lighttpd    = "1048576"
LOGROTATE_ROTATION_lighttpd  = "1"
#HDD_DISABLE
LOGROTATE_SIZE_MEM_lighttpd    = "204800"
LOGROTATE_ROTATION_MEM_lighttpd  = "1"

RDEPENDS_${PN} += " \
    libpcreposix \
    pcregrep \
    lighttpd-module-cgi \
    lighttpd-module-redirect \
    lighttpd-module-setenv \
    lighttpd-module-ssi \
    lighttpd-module-access \
    lighttpd-module-accesslog \
    lighttpd-module-rewrite \
    lighttpd-module-secdownload \
	"
