FILESEXTRAPATHS_prepend := "${THISDIR}/files:"

SRC_URI_append = " file://CVE-2022-32221_7.79.1_fix.patch \
                   file://CVE-2022-35252_7.79.1_fix.patch \
                   file://CVE-2022-43552_7.79.1_fix.patch \
                 "
