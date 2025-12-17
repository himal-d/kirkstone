SUMMARY = "Minizip"
DEPENDS = ""
LICENSE = "Zlib"

LIC_FILES_CHKSUM = "file://LICENSE;md5=3fb541eb8359212703e21d14eba7ac64"

SRC_URI = "git://github.com/nmoinvaz/minizip.git;branch=1.2;protocol=http"
SRCREV = "71ef99f6a051c11652502cf31cfef292de2e7736"

S = "${WORKDIR}/git"
B = "${WORKDIR}/git"

EXTRA_OECMAKE += "-DUSE_AES=OFF -DBUILD_SHARED_LIBS=ON"
DEPENDS += "zlib"

inherit cmake

unset CMAKE_BUILD_PARALLEL_LEVEL

do_install_append() {
    rm -r ${D}/usr/cmake
}

FILES_${PN} += "${libdir}/*.so"
FILES_SOLIBSDEV = ""
INSANE_SKIP_${PN} += "dev-so"

BBCLASSEXTEND_append += " nativesdk"
