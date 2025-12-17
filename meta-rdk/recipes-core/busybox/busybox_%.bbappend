FILESEXTRAPATHS_prepend := "${THISDIR}/busybox:"

SRC_URI_append = "${@bb.utils.contains('DISTRO_FEATURES', 'nls_support',' file://busybox-support-chinese-display.patch',' ',d)}"
