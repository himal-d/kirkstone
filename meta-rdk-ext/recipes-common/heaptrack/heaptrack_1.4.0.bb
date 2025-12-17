SUMMARY = "Heap memory profiler for Linux"
DESCRIPTION = "Heaptrack traces all memory allocations and annotates these \
events with stack traces. Dedicated analysis tools then allow you to interpret \
the heap memory profile to find hotspots to reduce memory, leaks, allocation \
hotspots and temporary allocations"
HOMEPAGE = "https://phabricator.kde.org/source/heaptrack/"
LICENSE = "LGPL-2.1-only"
LIC_FILES_CHKSUM = "file://README.md;md5=4ef5b760f4d060d021f18b2ecd154ee5"

DEPENDS = "zlib boost libunwind elfutils"
RDEPENDS_${PN} += "bash"

SRC_URI = "git://github.com/KDE/heaptrack.git;protocol=https;branch=master \
            "
SRC_URI += "file://copy_Debugrootfs.sh \
            file://add_tid_heaptrack.patch \
            " 
SRCREV = "9e5514ecbbf56c8d5307717e4d1c70cc58dc27fe"

S = "${WORKDIR}/git"

inherit cmake

EXTRA_OECMAKE += "-DHEAPTRACK_BUILD_PRINT=ON -DHEAPTRACK_BUILD_GUI=ON -DHEAPTRACK_BUILD_BACKTRACE=OFF"

do_install_append() {
install -d ${D}/lib/rdk
install -m 0755 ${WORKDIR}/copy_Debugrootfs.sh ${D}/lib/rdk
}

# libunwind is not yet ported to RISCV
COMPATIBLE_HOST_riscv32 = "null"
COMPATIBLE_HOST_riscv64 = "null"

FILES_${PN} += " /lib/rdk/copy_Debugrootfs.sh"
BBCLASSEXTEND = "native nativesdk"
