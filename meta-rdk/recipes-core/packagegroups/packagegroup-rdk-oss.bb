SUMMARY = "Custom package group for OSS bits used in RDK"

LICENSE = "MIT"

inherit packagegroup

PACKAGES = "\
    packagegroup-rdk-oss \
    "

# Opensource components used in RDK
RDEPENDS_packagegroup-rdk-oss = "\
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
    gupnp \
    gupnp-av \
    iksemel \
    jansson \
    libgcrypt \
    libgpg-error \
    libpcre \
    libsoup-2.4 \
    libtinyxml \
    libxml2 \
    lighttpd \
    log4c \
    logrotate \
    mtd-utils-ubifs \
    mongoose \
    neon \
    perl \
    popt \
    smartmontools \
    spawn-fcgi \
    yajl \
    rbustools  \
    rbusmirrors \
    "
GST_ALSA = "${@bb.utils.contains('COMBINED_FEATURES', 'alsa', 'gstreamer1.0-plugins-base-alsa', '',d)}"

RDEPENDS_packagegroup-rdk-oss += "${@bb.utils.contains('DISTRO_FEATURES', 'benchmark_enable', ' \
    gstreamer1.0 \
    gstreamer1.0-plugins-base \ 
    gstreamer1.0-plugins-good \
    gstreamer1.0-plugins-bad \
    gstreamer1.0-plugins-bad-debugutilsbad  \
    gstreamer1.0-plugins-bad-fbdevsink  \
    gstreamer1.0-plugins-bad-mpegtsdemux  \
    gstreamer1.0-plugins-bad-videoparsersbad \
    gstreamer1.0-plugins-base-videoconvert  \
    gstreamer1.0-plugins-base-videotestsrc   \
    gstreamer1.0-plugins-base-playback   \
    ${GST_ALSA} \
    gstreamer1.0-plugins-base-videoscale   \
    gstreamer1.0-plugins-good-isomp4  \
    gstreamer1.0-plugins-good-autodetect  \
    gstreamer1.0-plugins-good-audioparsers \
    westeros \
    westeros-sink \
', '', d)}"
