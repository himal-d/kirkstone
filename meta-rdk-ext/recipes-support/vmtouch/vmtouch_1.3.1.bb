SUMMARY = "the Virtual Memory Toucher"
DESCRIPTION = "Portable file system cache diagnostics and control"
HOMEPAGE = "https://hoytech.com/vmtouch/"
LICENSE = "BSD"

LIC_FILES_CHKSUM = "file://LICENSE;md5=ea4594d5258fd05f3b214aa3cea63837"

SRCREV = "b8b30e81d51544d6b8f428552f10d5b398a77fcb"
SRC_URI = "git://github.com/hoytech/vmtouch.git;branch=master;protocol=git"

S = "${WORKDIR}/git"

DEPENDS_append = " perl-native"

do_install() {
    install -d ${D}${bindir}

    install -m 0555 \
        ${S}/vmtouch \
        ${D}${bindir}
}
