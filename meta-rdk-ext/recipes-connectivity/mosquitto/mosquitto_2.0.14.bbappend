FILESEXTRAPATHS_prepend := "${THISDIR}/files:"

SRC_URI_append = " file://CVE-2023-3592_2.0.14_fix.patch \
                   file://CVE-2023-0809_2.0.14_fix.patch \
                   file://CVE-2023-28366_2.0.14_fix.patch \
                 "

