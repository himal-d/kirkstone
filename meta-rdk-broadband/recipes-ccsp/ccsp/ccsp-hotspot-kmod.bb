SUMMARY = "CCSP Hotspot Kernel Module"
HOMEPAGE = "https://github.com/belvedere-yocto/hotspot"

LICENSE = "GPLv2"
LIC_FILES_CHKSUM = "file://COPYING;md5=90a09ab320e2368b0ee7213fd5be2d5c"

SRC_URI = "${CMF_GIT_ROOT}/rdkb/components/cpc/mtu_modifier;protocol=${CMF_GIT_PROTOCOL};branch=${CMF_GIT_BRANCH};name=hotspot-kmod"
CFLAGS += " -Wall -Werror -Wextra -Wno-pointer-sign -Wno-sign-compare "

SRCREV_hotspot-kmod = "${AUTOREV}"
SRCREV_FORMAT = "hotspot-kmod"
PV = "${RDK_RELEASE}+git${SRCPV}"
do_compile[lockfiles] = "${TMPDIR}/kernel-scripts.lock"

S = "${WORKDIR}/git"

inherit module

PACKAGES += "kernel-module-${PN}"
