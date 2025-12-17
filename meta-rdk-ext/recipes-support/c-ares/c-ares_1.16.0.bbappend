FILESEXTRAPATHS_prepend := "${THISDIR}/files:"
SRC_URI_append = " file://CVE-2021-3672.patch \
                   file://CVE-2020-14354_fix.patch \
                   file://CVE-2022-4904_1.16_fix.patch \
                 "
