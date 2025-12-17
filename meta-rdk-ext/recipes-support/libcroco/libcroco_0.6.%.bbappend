FILESEXTRAPATHS_prepend := "${THISDIR}/files:"

SRC_URI_append_video = " file://CVE-2020-12825_fix.patch \
                       "
SRC_URI_remove_kirkstone = "file://CVE-2020-12825_fix.patch \
                           "
