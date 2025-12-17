FILESEXTRAPATHS_prepend := "${THISDIR}/files:"

SRC_URI_remove = "git://github.com/Comcast/trower-base64.git;branch=main"
SRC_URI += "git://github.com/Comcast/trower-base64.git;protocol=https;branch=main"

SRC_URI_append_aarch64 = " file://0001-64-bit-compile-fix.patch "
