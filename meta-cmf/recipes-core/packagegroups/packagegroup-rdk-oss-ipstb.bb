SUMMARY = "Custom package group for OSS bits used in RDK"

LICENSE = "MIT"
LIC_FILES_CHKSUM = "file://${COMMON_LICENSE_DIR}/MIT;md5=0835ade698e0bcf8506ecda2f7b4f302"

inherit packagegroup

PACKAGES = "\
    packagegroup-rdk-oss-ipstb \
    "

# Opensource components used in RDK
RDEPENDS_packagegroup-rdk-oss-ipstb = "\
    util-linux-sfdisk \
    "
RDEPENDS_packagegroup-rdk-oss-ipstb_rpi += "\
    sysint \
    sysint-conf \
    "
