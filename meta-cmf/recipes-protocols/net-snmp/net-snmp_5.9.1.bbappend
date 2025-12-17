FILESEXTRAPATHS_prepend := "${THISDIR}/files:"
SRC_URI_append_aarch64 = " file://remove_log_error.patch "
SRC_URI_append = " file://0001-libsnmp-Fix-the-build-against-OpenSSL-3.0.patch "
SRC_URI_remove = "file://double_free.patch"
