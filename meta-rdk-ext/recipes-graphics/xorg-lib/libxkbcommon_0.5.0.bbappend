FILESEXTRAPATHS_prepend := "${THISDIR}/${PN}:"
SRC_URI_append_kirkstone = " file://Define_macros_before_use_Kirkstone.patch"
SRC_URI_append = " file://CVE-2018-15853_fix.patch \
                   file://CVE-2018-15857_fix.patch \
                   file://CVE-2018-15858_fix.patch \
                   file://CVE-2018-15859_fix.patch \
                   file://CVE-2018-15861_fix.patch \
                   file://CVE-2018-15862_fix.patch \
                   file://CVE-2018-15863_fix.patch \
                   file://CVE-2018-15864_fix.patch \
                 "

