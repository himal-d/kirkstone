SUMMARY = "Custom package group for RDK bits"

LICENSE = "MIT"
LIC_FILES_CHKSUM = "file://${COMMON_LICENSE_DIR}/MIT;md5=0835ade698e0bcf8506ecda2f7b4f302"

inherit packagegroup

PACKAGES = "\
    packagegroup-rdk-openmax \
    "

# Opensource components used in RDK
RDEPENDS_packagegroup-rdk-openmax = "\
    curl \
    dropbear \
    e2fsprogs \
    e2fsprogs-e2fsck \
    e2fsprogs-mke2fs \
    e2fsprogs-tune2fs \
    fcgi \
    glib-2.0 \
    gnutls \
    gssdp \
    gst-fluendo-mpegdemux \
    gst-meta-audio \
    gst-meta-base \
    gst-meta-video \
    gupnp \
    iksemel \
    jansson \
    libgcrypt \
    libgpg-error \
    libpcre \
    libsoup-2.4 \
    libxml2 \
    lighttpd \
    log4c \
    logrotate \
    mtd-utils-ubifs \
    network-hotplug \
    neon \
    popt \
    smartmontools \
    spawn-fcgi \
    yajl \
    gupnp-av \
    gst-plugins-base \
    gst-plugins-good \
    gst-plugins-bad \
    gdb \
    strace \
    tcf-agent \
    alsa-utils-amixer \
    alsa-utils-aplay \
    ldd \
    gst-meta-audio \
    gst-meta-base \
    gst-meta-video \
    gst-meta-debug \
    libomxil \
    libomxffmpegdist \     
    gst-omx \
    mongoose \
    libtinyxml \
    gst-plugins-bad-bz2 \
    gst-plugins-bad-audiovisualizers \
    gst-plugins-bad-camerabin2 \
    gst-plugins-bad-coloreffects \
    gst-plugins-bad-colorspace \
    gst-plugins-bad-curl \
    gst-plugins-bad-fbdevsink \
    gst-plugins-bad-gaudieffects \
    gst-plugins-bad-mpegdemux \
    gst-plugins-bad-mpegtsdemux \
    gst-plugins-bad-linsys \
    gst-plugins-bad-mpegvideoparse \
    gst-plugins-bad-rtpvp8 \
    gst-plugins-bad-sdi \
    gst-plugins-bad-shm \
    gst-plugins-bad-smooth \
    gst-plugins-bad-videofiltersbad \
    gst-plugins-bad-videomaxrate \
    gst-plugins-bad-y4mdec \
    gstreamer1.0 \
    gstreamer1.0-plugins-base \ 
    gstreamer1.0-plugins-good \
    gstreamer1.0-plugins-bad \
    gstreamer1.0-libav \
    gstreamer1.0-plugins-bad-fbdevsink  \
    gstreamer1.0-plugins-base-videoconvert  \
    gstreamer1.0-plugins-base-videotestsrc   \
    gstreamer1.0-plugins-base-playback   \
    gstreamer1.0-plugins-base-alsa   \
    gstreamer1.0-plugins-base-videoscale   \
    gstreamer1.0-plugins-good-isomp4  \
    gstreamer1.0-plugins-good-autodetect  \
    "

RDEPENDS_packagegroup-rdk-openmax_append_qemuall = " alsa-conf "
