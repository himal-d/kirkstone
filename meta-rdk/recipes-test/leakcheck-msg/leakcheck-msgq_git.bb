SUMMARY = "A simple message queue application"
SECTION = "console/testapp"
LICENSE = "Apache-2.0"

LIC_FILES_CHKSUM = "file://${COREBASE}/../meta-rdk/licenses/Apache-2.0;md5=3b83ef96387f14655fc854ddc3c6bd57"
SRC_URI = "file://utility.c"
SRC_URI += "file://msgq_receive.c"

S = "${WORKDIR}"

DEPENDS += "gcc-sanitizers"
RDEPENDS_${PN} += "${@bb.utils.contains('DISTRO_FEATURES', 'use_lsan', 'liblsan', 'libasan',d)}"
CFLAGS += "${@bb.utils.contains('DISTRO_FEATURES', 'use_lsan','-fsanitize=leak ','-fsanitize=address -fsanitize-recover=address', d)}"
CFLAGS_append_dunfell = "  -I${STAGING_EXECPREFIXDIR}/lib/gcc/${TARGET_SYS}/9.3.0/include"
LDFLAGS += "${@bb.utils.contains('DISTRO_FEATURES', 'use_lsan','-fsanitize=leak -llsan','-fsanitize=address -fsanitize-recover=address -lasan', d)}"
CXXFLAGS += "${@bb.utils.contains('DISTRO_FEATURES', 'use_lsan','-fsanitize=leak ','-fsanitize=address -fsanitize-recover=address', d)}"
CXXFLAGS_append_dunfell = "  -I${STAGING_EXECPREFIXDIR}/lib/gcc/${TARGET_SYS}/9.3.0/include"
TARGET_CC_ARCH += "${LDFLAGS}"


do_compile () {
    ${CC} utility.c -o leakCheck_utility -lpthread -lrt
    ${CC} -fPIC ${CFLAGS} -DMSGQ_CREATE --shared -lrt -lpthread -Wl,-soname,libmsgq.so.0 ${LDFLAGS} -o libmsgq.so.0.0.0 msgq_receive.c
}

do_install () {
    install -d ${D}${bindir}
    install -m 755 ${S}/leakCheck_utility ${D}${bindir}
    install -d ${D}${libdir}
    install -m 755 ${S}/libmsgq.so.0.0.0 ${D}${libdir}/libmsgq.so.0.0.0
    cd ${D}${libdir}
    ln -sf libmsgq.so.0.0.0 libmsgq.so.0
    ln -sf libmsgq.so.0.0.0 libmsgq.so
}

FILES_${PN} += "${bindir}/leakCheck_utility"
