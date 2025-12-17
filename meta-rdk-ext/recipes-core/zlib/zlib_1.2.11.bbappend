FILESEXTRAPATHS_prepend:="${THISDIR}/${PN}:"

SRC_URI += " file://CVE-2022-37434_fix.patch \
             file://CVE-2023-45853_fix.patch \
	     file://CVE-2018-25032_fix.patch \
           "

