FILESEXTRAPATHS_prepend := "${THISDIR}/files:"

SRC_URI_append = " file://CVE-2020-35525_fix.patch \
                   file://CVE-2020-35527_fix.patch \
		   file://CVE-2022-35737_fix.patch \
                 "

