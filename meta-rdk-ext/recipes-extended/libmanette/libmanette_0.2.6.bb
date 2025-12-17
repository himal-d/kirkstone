SUMMARY = "The simple GObject game controller library"
HOMEPAGE = "https://gnome.pages.gitlab.gnome.org/libmanette/"
LICENSE = "LGPLv2.1 & Zlib"
LIC_FILES_CHKSUM = "file://COPYING;md5=4fbd65380cdd255951079008b364516c"
DEPENDS = "libevdev libgudev"
SRC_URI = "https://download.gnome.org/sources/libmanette/0.2/libmanette-${PV}.tar.xz \
           file://0001-old-kernel-and-64-bit-kernel-build-error-fix.patch \
           file://0001-send-event-in-thread-context.patch \
           file://0001-default-gamepad-db-dir-usr-share.patch \
           file://gamecontrollerdb \
           file://0001-new-SDL-gamedb.patch \
           file://0002-add-wayland-inputfd-support.patch \
           file://0001-map-key-menu-back-as-btn.patch \
           "

SRC_URI[sha256sum] = "63653259a821ec7d90d681e52e757e2219d462828c9d74b056a5f53267636bac"

inherit ${@bb.utils.contains_any('DISTRO_FEATURES', 'dunfell kirkstone', 'meson', ' ', d)} pkgconfig gobject-introspection ptest vala

PACKAGECONFIG[wayland-inputfd] = "-Dwayland-inputfd=true,-Dwayland-inputfd=false,wayland wayland-native"

do_install_append() {
    install -d ${D}${datadir}/libmanette/
    cp -f ${WORKDIR}/gamecontrollerdb ${D}${datadir}/libmanette/
    chmod 0644 ${D}${datadir}/libmanette/gamecontrollerdb
    rm ${D}/usr/bin/manette-test
    rmdir --ignore-fail-on-non-empty ${D}/usr/bin/
}

FILES_${PN} += "${datadir}/libmanette/"
#FILES_${PN}-ptest =+ "${bindir}/manette-test"
#FILES_${PN}-ptest =+ "${bindir}/ManetteEventMapping"
#FILES_${PN}-ptest =+ "${bindir}/ManetteMapping"
#FILES_${PN}-ptest =+ "${bindir}/ManetteMappingManager"
#FILES_${PN}-dev =+ "${libdir}/girepository-1.0"
