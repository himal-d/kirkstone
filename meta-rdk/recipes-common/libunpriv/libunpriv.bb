SUMMARY = "libcap wrapper "
LICENSE = "Apache-2.0"
DEPENDS = "libcap jsoncpp"
S = "${WORKDIR}/git"
SRC_URI = "${CMF_GIT_ROOT}/rdk/components/generic/libunpriv;protocol=${CMF_GIT_PROTOCOL};branch=${CMF_GIT_BRANCH};name=libunpriv \
"
SRCREV_libunpriv = "${AUTOREV}"
SRCREV_FORMAT = "libunpriv"
CXXFLAGS_append = "\
    -I${STAGING_INCDIR} \
    -I${STAGING_INCDIR}/jsoncpp"

LIC_FILES_CHKSUM = "file://LICENSE;md5=175792518e4ac015ab6696d16c4f607e"

inherit autotools pkgconfig

CFLAGS += " -Wall -Werror -Wextra -Wno-unused-parameter "
