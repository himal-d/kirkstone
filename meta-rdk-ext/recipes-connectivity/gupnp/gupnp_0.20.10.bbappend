FILESEXTRAPATHS_prepend := "${THISDIR}/${PN}:"
## The below patch is required to use gssdp-1.2 with gupnp-1.0
SRC_URI_append = " file://0001-Use-gssdp-1.2.patch"
SRC_URI_remove_morty = " file://0001-Use-gssdp-1.2.patch"

SRC_URI_append = " file://CVE-2021-33516_fix.patch "
