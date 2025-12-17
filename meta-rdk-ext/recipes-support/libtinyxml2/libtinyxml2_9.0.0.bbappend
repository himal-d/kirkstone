FILESEXTRAPATHS_prepend := "${THISDIR}/${PN}:"
SRC_URI_append += " file://libtinyxml2_9_change.patch"