FILESEXTRAPATHS_prepend := "${THISDIR}/files:"

SRC_URI_remove = "git://github.com/google/protobuf.git;branch=3.11.x"
SRC_URI += "git://github.com/protocolbuffers/protobuf.git;protocol=https;branch=main"

SRC_URI += "file://0002-fix-missing-symbols.patch"
