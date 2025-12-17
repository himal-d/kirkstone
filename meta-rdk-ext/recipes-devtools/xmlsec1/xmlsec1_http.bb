SUMMARY = "XMLSec Library"
LICENSE = "MIT"

LIC_FILES_CHKSUM = "file://COPYING;md5=352791d62092ea8104f085042de7f4d0"

#SRC_URI = "git://github.com/lsh123/xmlsec.git"
SRC_URI ="\
  https://www.aleksey.com/xmlsec/download/older-releases/xmlsec1-1.2.27.tar.gz \
  file://xmlsec1-remove-pkgconfig-install-files.patch \
"
SRC_URI[md5sum] = "508bee7e4f1b99f2d50aaa7d38ede56e"

S = "${WORKDIR}/xmlsec1-1.2.27"

inherit autotools pkgconfig

PARALLEL_MAKE = ""

FILES_${PN} += "${libdir}/xmlsec1Conf.sh"

DEPENDS = "libtool libxml2 openssl zlib libgpg-error"

EXTRA_OECONF_append = " \ 
  --enable-pkgconfig=no \
  --disable-dependency-tracking \
  --disable-manpages-build \
  --disable-docs-build \
  --enable-apps=no \
  --enable-docs=no \
  --enable-md5=no \
  --enable-ripemd160=no \
  --enable-crypto-dl=no \
  --enable-apps-crypto-dl=no \
  --without-libxslt \
  --without-gcrypt \
  --without-gnutls \
  --without-nss \
  --without-nspr \
  --with-default-crypto=openssl \
  --with-libxml=${STAGING_EXECPREFIXDIR} \
  --with-openssl=${STAGING_EXECPREFIXDIR} \
"

FILES_${PN} += "${libdir}/*.so"

BBCLASSEXTEND_append += " nativesdk"
