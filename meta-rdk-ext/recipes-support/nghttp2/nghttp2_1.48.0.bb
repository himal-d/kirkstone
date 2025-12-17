SUMMARY = "HTTP/2 C Library and tools"
HOMEPAGE = "https://nghttp2.org/"
SECTION = "libs"
LICENSE = "MIT"
LIC_FILES_CHKSUM = "file://COPYING;md5=764abdf30b2eadd37ce47dcbce0ea1ec"

UPSTREAM_CHECK_URI = "https://github.com/nghttp2/nghttp2/releases"

SRC_URI = "\
    https://github.com/nghttp2/nghttp2/releases/download/v${PV}/nghttp2-${PV}.tar.xz \
    file://0001-fetch-ocsp-response-use-python3.patch \
    file://CVE-2023-35945_1.48_fix.patch \
          "
SRC_URI[sha256sum] = "47d8f30ee4f1bc621566d10362ca1b3ac83a335c63da7144947c806772d016e4"

inherit cmake manpages python3native
PACKAGECONFIG[manpages] = ""

# examples are never installed, and don't need to be built in the
# first place
EXTRA_OECMAKE = "-DENABLE_EXAMPLES=OFF -DENABLE_APP=OFF -DENABLE_HPACK_TOOLS=OFF"

PACKAGES =+ "lib${BPN} ${PN}-client ${PN}-proxy ${PN}-server"

RDEPENDS_${PN} = "${PN}-client (>= ${PV}) ${PN}-proxy (>= ${PV}) ${PN}-server (>= ${PV})"
RDEPENDS_${PN}_class-native = ""
RDEPENDS_${PN}-proxy = "openssl python3-core python3-io python3-shell"

ALLOW_EMPTY_${PN} = "1"
ALLOW_EMPTY_${PN}-client = "1"
ALLOW_EMPTY_${PN}-server = "1"
FILES_${PN} = ""
FILES_lib${BPN} = "${libdir}/*${SOLIBS}"
FILES_${PN}-client = "${bindir}/h2load ${bindir}/nghttp"
FILES_${PN}-proxy = "${bindir}/nghttpx ${datadir}/${BPN}/fetch-ocsp-response"
FILES_${PN}-server = "${bindir}/nghttpd"

BBCLASSEXTEND = "native nativesdk"
