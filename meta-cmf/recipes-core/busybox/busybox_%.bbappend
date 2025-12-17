FILESEXTRAPATHS_prepend := "${THISDIR}/busybox:"

SRC_URI_append_client = " \
   file://nc.cfg \
   "

SRC_URI_remove_broadband = "file://nc.cfg"
SRC_URI_append_broadband = " \
   file://nc-n.cfg \
   "
