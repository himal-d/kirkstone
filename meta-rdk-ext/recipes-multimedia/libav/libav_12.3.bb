require libav_12.3.inc

LICENSE = "LGPLv2.1"
LIC_FILES_CHKSUM = "file://COPYING.LGPLv2.1;md5=bd7a443320af8c812e4c18d1b79df004"

SRC_URI = "https://github.com/libav/libav/archive/refs/tags/v12.3.tar.gz"

SRC_URI[md5sum] = "78f791a4f595a67abd3a7d0c976524c5"
SRC_URI[sha256sum] = "68c9e91be8456d1a7cec3af497312b4ffb1a68352849c2f68a0ad596b7409089"

inherit autotools pkgconfig

do_rm_work() {
}

