SUMMARY = "Heap memory profiler for Linux"
DESCRIPTION = "Heaptrack traces all memory allocations and annotates these \
events with stack traces. Dedicated analysis tools then allow you to interpret \
the heap memory profile to find hotspots to reduce memory, leaks, allocation \
hotspots and temporary allocations"
HOMEPAGE = "https://phabricator.kde.org/source/heaptrack/"
#LICENSE = "LGPL-2.1-only"
LIC_FILES_CHKSUM = "file://README.md;md5=450ce5a2a93cedd86cbe334efda9064e"
LICENSE = "LGPLv2.1+ & GPLv2+ & BSD-3-Clause & Apache-2.0 & MIT"

DEPENDS = "zlib boost libunwind elfutils zstd"
RDEPENDS_${PN} += "bash"


SRC_URI = "git://github.com/KDE/heaptrack.git;protocol=https;branch=master \
        "
SRCREV = "c8bbebd325f41dd34af409b68eb3eaa619e326cf"

SRC_URI += "file://remove_zstd_depends.patch \
            file://add_tid_in_heaptrack.patch \
            file://copy_Debugrootfs.sh "

S = "${WORKDIR}/git"

TARGET_CC_ARCH += "${LDFLAGS}"

inherit cmake

EXTRA_OECMAKE += "-DHEAPTRACK_BUILD_PRINT=ON -DHEAPTRACK_BUILD_GUI=ON -DHEAPTRACK_BUILD_BACKTRACE=OFF"

do_install_append() {
install -d ${D}/lib/rdk
install -m 0755 ${WORKDIR}/copy_Debugrootfs.sh ${D}/lib/rdk
}

FILES_${PN} += " /lib/rdk/copy_Debugrootfs.sh"
BBCLASSEXTEND = "native nativesdk"

