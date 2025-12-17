FILESEXTRAPATHS_prepend := "${THISDIR}/${PN}:"
SRC_URI_append  = " file://dropbear_2017-ssh_log.patch"
SRC_URI_append  = " file://ssh_telemetry_2017_uninit_init_add.patch"

SRC_URI_append = " file://verbose.patch"
SRC_URI_append = " file://revsshipv6.patch"
SRC_URI_append = " file://0001-Fixed-Race-Conditions-Observed-when-using-port-forwa.patch"

CFLAGS_append_broadband = " -DRDK_BROADBAND"
