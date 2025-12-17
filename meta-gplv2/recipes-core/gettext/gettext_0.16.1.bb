SUMMARY = "Utilities and libraries for producing multi-lingual messages"
DESCRIPTION = "GNU gettext is a set of tools that provides a framework to help other programs produce multi-lingual messages. These tools include a set of conventions about how programs should be written to support message catalogs, a directory and file naming organization for the message catalogs themselves, a runtime library supporting the retrieval of translated messages, and a few stand-alone programs to massage in various ways the sets of translatable and already translated strings."
HOMEPAGE = "http://www.gnu.org/software/gettext/gettext.html"
SECTION = "libs"
LICENSE = "GPL-2.0-only"
LIC_FILES_CHKSUM = "file://COPYING;md5=9ea3144f04c41cd2eada5d3f472e6ea5"

PR = "r6"
DEPENDS = "virtual/libiconv"
DEPENDS:class-native = ""
PROVIDES = "virtual/libintl virtual/gettext"
PROVIDES:class-native = "virtual/gettext-native"

SRC_URI = "${GNU_MIRROR}/gettext/gettext-${PV}.tar.gz \
           file://gettext-vpath.patch \
           file://linklib_from_0.17.patch \
	   file://gettext-autoconf-lib-link-no-L.patch \
           file://disable_java.patch \
           file://fix_aclocal_version.patch \
           file://fix_gnu_source_circular.patch \
           file://hardcode_macro_version.patch \
           file://0001-gettext-libgrep-fix-compile-error-Werror-format-secu.patch \
          "

SRC_URI[md5sum] = "3d9ad24301c6d6b17ec30704a13fe127"
SRC_URI[sha256sum] = "0bf850d1a079fb5a61f0a47b1a9efd35eb44032255375e1cedb0253bc27b376d"

PARALLEL_MAKE = ""

inherit autotools texinfo

EXTRA_OECONF += "--without-lispdir \
                 --disable-csharp \
                 --disable-libasprintf \
                 --disable-java \
                 --disable-native-java \
                 --disable-openmp \
                 --without-emacs \
                "
EXTRA_OECONF:append:libc-musl = "\
                                 gt_cv_func_gnugettext1_libc=yes \
                                 gt_cv_func_gnugettext2_libc=yes \
                                "

acpaths = '-I ${S}/autoconf-lib-link/m4/ \
           -I ${S}/gettext-runtime/m4 \
           -I ${S}/gettext-tools/m4'

do_configure:prepend() {
	rm -f ${S}/config/m4/libtool.m4
}

do_install:append:libc-musl () {
	rm -f ${D}${libdir}/charset.alias
}

# these lack the .x behind the .so, but shouldn't be in the -dev package
# Otherwise you get the following results:
# 7.4M    glibc/images/ep93xx/Angstrom-console-image-glibc-ipk-2008.1-test-20080104-ep93xx.rootfs.tar.gz
# 25M     uclibc/images/ep93xx/Angstrom-console-image-uclibc-ipk-2008.1-test-20080104-ep93xx.rootfs.tar.gz
# because gettext depends on gettext-dev, which pulls in more -dev packages:
# 15228   KiB /ep93xx/libstdc++-dev_4.2.2-r2_ep93xx.ipk
# 1300    KiB /ep93xx/uclibc-dev_0.9.29-r8_ep93xx.ipk
# 140     KiB /armv4t/gettext-dev_0.14.1-r6_armv4t.ipk
# 4       KiB /ep93xx/libgcc-s-dev_4.2.2-r2_ep93xx.ipk

PACKAGES =+ "libgettextlib libgettextsrc"
FILES:libgettextlib = "${libdir}/libgettextlib-*.so*"
FILES:libgettextsrc = "${libdir}/libgettextsrc-*.so*"

PACKAGES =+ "gettext-runtime gettext-runtime-dev gettext-runtime-staticdev gettext-runtime-doc"

FILES:${PN} += "${libdir}/${BPN}/*"

FILES:gettext-runtime = "${bindir}/gettext \
                         ${bindir}/ngettext \
                         ${bindir}/envsubst \
                         ${bindir}/gettext.sh \
                         ${libdir}/libasprintf${SODEV} \
                         ${libdir}/GNU.Gettext.dll \
                        "
FILES:gettext-runtime-staticdev += "${libdir}/libasprintf.a"
FILES:gettext-runtime-dev += "${includedir}/autosprintf.h \
                              ${libdir}/libasprintf${SOLIBDEV}"
FILES:gettext-runtime-doc = "${mandir}/man1/gettext.* \
                             ${mandir}/man1/ngettext.* \
                             ${mandir}/man1/envsubst.* \
                             ${mandir}/man1/.* \
                             ${mandir}/man3/* \
                             ${docdir}/gettext/gettext.* \
                             ${docdir}/gettext/ngettext.* \
                             ${docdir}/gettext/envsubst.* \
                             ${docdir}/gettext/*.3.html \
                             ${datadir}/gettext/ABOUT-NLS \
                             ${docdir}/gettext/csharpdoc/* \
                             ${docdir}/libasprintf/autosprintf.html \
                             ${infodir}/autosprintf.info \
                            "

do_install:append() {
    rm -f ${D}${libdir}/preloadable_libintl.so
}

do_install:append:class-native () {
	rm ${D}${datadir}/aclocal/*
	rm ${D}${datadir}/gettext/config.rpath
	rm ${D}${datadir}/gettext/po/Makefile.in.in
	rm ${D}${datadir}/gettext/po/remove-potcdate.sin
}

# Anyone inheriting gettext will have both gettext-native and gettext
# available, and we don't want to use older macros from the target gettext in
# a non-gplv3 build, so kill them and let dependent recipes rely on
# gettext-native.
SYSROOT_DIRS_IGNORE += "${datadir}/aclocal"

BBCLASSEXTEND = "native nativesdk"
