SUMMARY = "Documentation system for on-line information and printed output"
DESCRIPTION = "Texinfo is a documentation system that can produce both \
online information and printed output from a single source file. The \
GNU Project uses the Texinfo file format for most of its documentation."
HOMEPAGE = "http://www.gnu.org/software/texinfo/"
SECTION = "console/utils"
LICENSE = "GPL-2.0-only"
LIC_FILES_CHKSUM = "file://COPYING;md5=94d55d512a9ba36caa9b7df079bae19f"

PROVIDES:append:class-native = " texinfo-4.8-replacement-native"

DEPENDS = "zlib ncurses texinfo-4.8-replacement-native"
DEPENDS:class-native = "zlib-native ncurses-native"

TARGET_PATCH = "file://use_host_makedoc.patch \
           file://using-native-makeinfo.patch \
"
TARGET_PATCH:class-native = ""

SRC_URI = "${GNU_MIRROR}/texinfo/${BP}.tar.gz \
           file://check-locale-h.patch \
           file://do-compile-native-tools.patch \
           ${TARGET_PATCH} \
          "

SRC_URI[md5sum] = "4e9a1a591ed236003d0d4b008bf07eef"
SRC_URI[sha256sum] = "1f3cdeebe65fdf510f55d765ab1031b54416aa5bc2635b6a54ef9bcb2367c917"

tex_texinfo = "texmf/tex/texinfo"

inherit gettext autotools

do_install:append() {
	mkdir -p ${D}${datadir}/${tex_texinfo}
	install -p -m644 ${S}/doc/texinfo.tex ${S}/doc/txi-??.tex ${D}${datadir}/${tex_texinfo}
}

do_install:append:class-native() {
	install -m 755 info/makedoc ${D}${bindir}
	install -m 755 makeinfo/makeinfo ${D}${bindir}
}

PACKAGES += "info info-doc"

FILES:info = "${bindir}/info ${bindir}/infokey ${bindir}/install-info"
FILES:info-doc = "${infodir}/info.info ${infodir}/dir ${infodir}/info-*.info \
                  ${mandir}/man1/info.1* ${mandir}/man5/info.5* \
                  ${mandir}/man1/infokey.1* ${mandir}/man1/install-info.1*"

FILES:${PN} = "${bindir}/makeinfo ${bindir}/texi* ${bindir}/pdftexi2dvi ${bindir}/pod2texi ${datadir}/texinfo"
FILES:${PN}-doc = "${infodir}/texinfo* \
                   ${datadir}/${tex_texinfo} \
                   ${mandir}/man1 ${mandir}/man5"

BBCLASSEXTEND = "native"
