FILESEXTRAPATHS_prepend := "${THISDIR}/${PN}:"

SRC_URI_append_broadband += " file://CVE-2010-0001_fix.patch \
                              file://CVE-2009-2624_fix.patch "
