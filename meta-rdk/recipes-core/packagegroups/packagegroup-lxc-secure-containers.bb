SUMMARY = "Custom package group for containers"
LICENSE = "Apache-2.0"
LIC_FILES_CHKSUM = "file://${COREBASE}/../meta-rdk/licenses/Apache-2.0;md5=3b83ef96387f14655fc854ddc3c6bd57"

inherit packagegroup

PACKAGES = "\
    packagegroup-lxc-secure-containers \
    "

RDEPENDS_packagegroup-lxc-secure-containers = "\
    libcap \
    lxc \
    lxccpid \
    "
