FILESEXTRAPATHS_prepend:="${THISDIR}/${PN}:"

SRC_URI_append = " file://CVE-2022-40303_fix.patch \
                   file://CVE-2022-40304_fix.patch \
                   file://CVE-2023-28484_fix.patch \
                   file://CVE-2023-29469_2.9.14_fix.patch \
                   file://CVE-2023-45322-1_fix.patch \
                   file://CVE-2023-45322-2_fix.patch \
                   file://CVE-2024-25062_fix.patch \
                   "
