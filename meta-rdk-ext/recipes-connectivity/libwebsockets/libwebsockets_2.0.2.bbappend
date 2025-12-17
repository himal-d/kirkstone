FILESEXTRAPATHS_prepend := "${THISDIR}/${PN}:"
SRC_URI_append_kirkstone = " file://libwebsockets-kirkstone-fix.patch"
