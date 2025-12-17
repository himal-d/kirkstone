FILESEXTRAPATHS_prepend := "${THISDIR}/lighttpd-1.4.53:"

SRC_URI_append = " file://bind_lighttpd-1.4.53.patch"
SRC_URI_append = " file://lighttpd-md4-compilation-error-fix.patch"
SRC_URI_append = " file://monotonic-time.patch"
SRC_URI_append = " file://CVE-2022-22707_fix.patch"
SRC_URI_append = " file://CVE-2019-11072.patch "

CFLAGS_append_broadband = " -DSO_BINDTODEVICE"

SYSTEMD_SERVICE_${PN}_broadband = ""
INITSCRIPT_NAME_broadband = ""
INITSCRIPT_PARAMS_broadband = ""

FILES_${PN} += "${systemd_unitdir}/system/lighttpd.service"

RDEPENDS_${PN} += " \
    lighttpd-module-auth \
    lighttpd-module-authn-file \
    lighttpd-module-openssl \
"
RDEPENDS_${PN} += "${@bb.utils.contains('DISTRO_FEATURES', 'offline_apps', 'lighttpd-module-alias', '', d)}"
