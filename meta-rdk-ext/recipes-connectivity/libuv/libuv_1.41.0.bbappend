FILESEXTRAPATHS_prepend := "${THISDIR}/${PN}:"

SRC_URI_append = "file://CVE-2024-24806_1.41_fix.patch"

