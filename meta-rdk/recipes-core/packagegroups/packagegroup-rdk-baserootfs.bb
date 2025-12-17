SUMMARY = "Custom package group for OSS bits used in RDK"

LICENSE = "MIT"
LIC_FILES_CHKSUM = "file://${COMMON_LICENSE_DIR}/MIT;md5=0835ade698e0bcf8506ecda2f7b4f302"

inherit packagegroup

PACKAGES = "\
    packagegroup-rdk-baserootfs \
    "

# Opensource components used in RDK
RDEPENDS_packagegroup-rdk-baserootfs = "\
    bash \
    curl \
    dropbear \
    e2fsprogs \
    e2fsprogs-e2fsck \
    e2fsprogs-mke2fs \
    e2fsprogs-tune2fs \
    fcgi \
    iksemel \
    libgcrypt \
    libgpg-error \
    libpcre \
    libsoup-2.4 \
    lighttpd \
    log4c \
    logrotate \
    mtd-utils-ubifs \
    neon \
    network-hotplug \
    spawn-fcgi \
    yajl \
    xupnp \
    procps \
    "

RDEPENDS_packagegroup-rdk-baserootfs += " ${@bb.utils.contains('DISTRO_FEATURES', 'gstreamer1', 'gstreamer1.0-plugins-base gstreamer1.0-plugins-good', 'gst-plugins-base gst-plugins-good', d)} "

#Adding smartmontools only for Hard Disk enabled devices.
RDEPENDS_packagegroup-rdk-baserootfs += "${@bb.utils.contains('DISTRO_FEATURES', 'storage_hdd','smartmontools', '',d)}"
