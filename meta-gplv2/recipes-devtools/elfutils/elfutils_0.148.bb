SUMMARY = "Utilities and libraries for handling compiled object files"
HOMEPAGE = "https://fedorahosted.org/elfutils"
SECTION = "base"
LICENSE = "(GPL-2.0-or-later & Elfutils-Exception)"
LIC_FILES_CHKSUM = "file://COPYING;md5=0636e73ff0215e8d672dc4c32c317bb3\
                    file://EXCEPTION;md5=570adcb0c1218ab57f2249c67d0ce417"
DEPENDS = "libtool bzip2 zlib virtual/libintl"

PR = "r11"

SRC_URI = "https://fedorahosted.org/releases/e/l/${BPN}/${BP}.tar.bz2"

SRC_URI[md5sum] = "a0bed1130135f17ad27533b0034dba8d"
SRC_URI[sha256sum] = "8aebfa4a745db21cf5429c9541fe482729b62efc7e53e9110151b4169fe887da"

# pick the patch from debian
# http://ftp.de.debian.org/debian/pool/main/e/elfutils/elfutils_0.148-1.debian.tar.gz

SRC_URI += "\
        file://redhat-portability.diff \
        file://redhat-robustify.diff \
        file://hppa_backend.diff \
        file://arm_backend.diff \
        file://mips_backend.diff \
        file://m68k_backend.diff \
        file://testsuite-ignore-elflint.diff \
        file://elf_additions.diff \
        file://elfutils-fsize.patch \
        file://remove-unused.patch \
        file://fix_for_gcc-4.7.patch \
        file://dso-link-change.patch \
        file://nm-Fix-size-passed-to-snprintf-for-invalid-sh_name-case.patch \
        file://elfutils-ar-c-fix-num-passed-to-memset.patch \
        file://Fix_elf_cvt_gunhash.patch \
        file://elf_begin.c-CVE-2014-9447-fix.patch \
        file://fix-build-gcc-4.8.patch \
        file://gcc6.patch \
        file://0001-Fix-fallthrough-warnings.patch \
        file://0002-Fix-printf-overflow-warnings.patch \
        file://0001-Make-it-compile-with-GCC-7.patch \
        file://0002-Make-it-build-with-GCC-7-and-compile-time-hardening-.patch \
"

# Only apply when building musl based target recipe
SRC_URI:append:libc-musl = " file://musl-support-for-elfutils-0.148.patch"

# The buildsystem wants to generate 2 .h files from source using a binary it just built,
# which can not pass the cross compiling, so let's work around it by adding 2 .h files
# along with the do_configure:prepend()

SRC_URI += "\
        file://i386_dis.h \
        file://x86_64_dis.h \
"
inherit autotools gettext

# There is a fix in 0.175 version (https://sourceware.org/bugzilla/show_bug.cgi?id=23884)
# but 0.175 has different license, so to be safe don't backport the fix, just ignore the issue
CFLAGS += "-Wno-error=missing-attributes"

# There is a fix in 0.171 version (commit b10d7eb74064c5906f031cd17c0f82041c6a4ca1)
# but 0.171 has different license, so to be safe don't backport the fix, just ignore the issue
CFLAGS += "-Wno-error=format-truncation="

# There is a fix in 0.182 version (commit 5621fe5443da23112170235dd5cac161e5c75e65)
# but 0.182 has different license, so to be safe don't backport the fix, just ignore the issue
CFLAGS += "-Wno-error=stringop-overflow="

# There are fixes in later versions for this but the old version won't be reproducible
TARGET_CC_ARCH:remove:class-target = " -Wdate-time"

EXTRA_OECONF = "--program-prefix=eu- --without-lzma"
EXTRA_OECONF:append:class-native = " --without-bzlib"

do_configure:prepend() {
    sed -i '/^i386_dis.h:/,+4 {/.*/d}' ${S}/libcpu/Makefile.am

    cp ${WORKDIR}/*dis.h ${S}/libcpu
}

# we can not build complete elfutils when using musl
# but some recipes e.g. gcc 4.5 depends on libelf so we
# build only libelf for musl cases

EXTRA_OEMAKE:libc-musl = "-C libelf"
EXTRA_OEMAKE:class-native = ""
EXTRA_OEMAKE:class-nativesdk = ""

BBCLASSEXTEND = "native nativesdk"

# Package utilities separately
PACKAGES =+ "${PN}-binutils libelf libasm libdw"
FILES:${PN}-binutils = "\
    ${bindir}/eu-addr2line \
    ${bindir}/eu-ld \
    ${bindir}/eu-nm \
    ${bindir}/eu-readelf \
    ${bindir}/eu-size \
    ${bindir}/eu-strip"

FILES:libelf = "${libdir}/libelf-${PV}.so ${libdir}/libelf.so.*"
FILES:libasm = "${libdir}/libasm-${PV}.so ${libdir}/libasm.so.*"
FILES:libdw  = "${libdir}/libdw-${PV}.so ${libdir}/libdw.so.* ${libdir}/elfutils/lib*"
# Some packages have the version preceeding the .so instead properly
# versioned .so.<version>, so we need to reorder and repackage.
#FILES_${PN} += "${libdir}/*-${PV}.so ${base_libdir}/*-${PV}.so"
#FILES_SOLIBSDEV = "${libdir}/libasm.so ${libdir}/libdw.so ${libdir}/libelf.so"

# The package contains symlinks that trip up insane
INSANE_SKIP:${MLPREFIX}libdw = "dev-so"
