FILESEXTRAPATHS_prepend := "${THISDIR}/files:"

SRC_URI_append_broadband = " file://CVE-2023-26257_fix.patch \
                             file://CVE-2023-36321_2.18_fix.patch \
                           "
