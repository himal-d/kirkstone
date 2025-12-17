FILESEXTRAPATHS_prepend:="${THISDIR}/${PN}:"

SRC_URI_append = " file://CVE-2020-25219_fix.patch \
                   file://CVE-2020-26154_fix.patch  "
