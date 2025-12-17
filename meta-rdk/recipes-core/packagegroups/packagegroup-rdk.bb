SUMMARY = "Custom package group for RDK bits"

LICENSE = "MIT"
LIC_FILES_CHKSUM = "file://${COMMON_LICENSE_DIR}/MIT;md5=0835ade698e0bcf8506ecda2f7b4f302"

inherit packagegroup

PACKAGES = "\
    packagegroup-rdk-generic \
    "

# Generic RDK components
RDEPENDS_packagegroup-rdk-generic = "\
    devicesettings \
    gst-plugins-rdk \
    iarmbus \
    iarmmgrs \
    "

RDEPENDS_packagegroup-rdk-generic_append_qemuall = " sysint"
RDEPENDS_packagegroup-rdk-media-common_append_qemuall = " sysint-conf"

# since we compile RDK component within qtwebkit (mediaplayersink) it
# is no longer a generic component anymore, and we need to make it
# part of RDK, since it won't compile in stand alone anymore..
RDEPENDS_packagegroup-rdk-generic += "\
    gst-plugins-base \
    gst-plugins-good \
    "
