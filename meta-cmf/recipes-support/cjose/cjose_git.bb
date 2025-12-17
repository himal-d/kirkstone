SUMMARY = "JOSE Library"
DESCRIPTION = "C library implementation of Javascript Object Signing and Encryption (JOSE)."

LICENSE = "MIT"
LIC_FILES_CHKSUM = "file://LICENSE;md5=7249e2f9437adfb8c88d870438042f0e"

DEPENDS = "jansson openssl"

inherit autotools pkgconfig

# Latest revision (May 11, 2019)
SRCREV = "9261231f08d2a3cbcf5d73c5f9e754a2f1c379ac"
SRC_URI = "git://git@github.com/cisco/cjose.git;branch=master;protocol=https"

S = "${WORKDIR}/git"

CFLAGS += "-I ${S}/include "
