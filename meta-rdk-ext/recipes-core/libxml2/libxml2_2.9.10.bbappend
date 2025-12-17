FILESEXTRAPATHS_prepend:="${THISDIR}/${PN}:"

SRC_URI_append_broadband = " file://CVE-2022-40304_fix.patch \
                             file://CVE-2023-28484_fix.patch \
                             file://CVE-2023-29469_fix.patch "
