SUMMARY = "Shared MIME type database and specification"
HOMEPAGE = "http://freedesktop.org/wiki/Software/shared-mime-info"
SECTION = "base"

LICENSE = "GPL-2.0-only"
LIC_FILES_CHKSUM = "file://COPYING;md5=b234ee4d69f5fce4486a80fdaf4a4263"

DEPENDS = "libxml2 intltool-native glib-2.0 shared-mime-info-native"

SRC_URI = "http://freedesktop.org/~hadess/shared-mime-info-${PV}.tar.xz"

inherit autotools pkgconfig gettext mime

EXTRA_OECONF = "--disable-update-mimedb"

FILES:${PN} += "${datadir}/mime"
FILES:${PN}-dev += "${datadir}/pkgconfig/shared-mime-info.pc"

# freedesktop.org.xml is only required when updating the mime database,
# package it separately
PACKAGES =+ "shared-mime-info-data"
FILES:shared-mime-info-data = "${datadir}/mime/packages/freedesktop.org.xml"
RDEPENDS:shared-mime-info-data = "shared-mime-info"

do_install () {
	autotools_do_install

	update-mime-database ${D}${datadir}/mime
}

do_install:class-native () {
	autotools_do_install

	${B}/update-mime-database ${D}${datadir}/mime
}

BBCLASSEXTEND = "native nativesdk"
