SRC_URI_remove = "git://github.com/rdkcentral/rtRemote;branch=release;protocol=https"
SRC_URI += "${CMF_GITHUB_ROOT}/rtRemote;protocol=${CMF_GIT_PROTOCOL};branch=${CMF_GITHUB_RELEASE_BRANCH}"

SRCREV = "${AUTOREV}"

inherit coverity

CFLAGS_raspberrypi4-64 += " -fpermissive "
CXXFLAGS_raspberrypi4-64 += " -fpermissive "
