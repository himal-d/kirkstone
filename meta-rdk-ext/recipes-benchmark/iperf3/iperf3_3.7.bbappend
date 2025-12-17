FILESEXTRAPATHS_prepend := "${THISDIR}/${PN}:"

SRC_URI_append = " file://CVE-2023-38403_fix.patch \
                 "
