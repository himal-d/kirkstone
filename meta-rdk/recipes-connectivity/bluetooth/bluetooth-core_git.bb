SUMMARY = "bluetooth-core"

LICENSE = "Apache-2.0"
LIC_FILES_CHKSUM = "file://LICENSE;md5=175792518e4ac015ab6696d16c4f607e"

BLUEZ ?= "${@bb.utils.contains('DISTRO_FEATURES', 'bluetooth', bb.utils.contains('DISTRO_FEATURES', 'bluez5', 'bluez5', 'bluez4', d), '', d)}"

DEPENDS = "dbus ${BLUEZ} rdk-logger"
DEPENDS_append = "${@bb.utils.contains('DISTRO_FEATURES', 'gdbus_bluez5', 'glib-2.0-native', '', d)}"

RDEPENDS_${PN} = "dbus ${BLUEZ} rdk-logger"
PV = "${RDK_RELEASE}+git${SRCPV}"

SRCREV = "${AUTOREV}"
SRCREV_FORMAT = "bluetooth-core"

SRC_URI = "${CMF_GIT_ROOT}/rdk/components/generic/bluetooth;protocol=${CMF_GIT_PROTOCOL};branch=${CMF_GIT_BRANCH}"
S = "${WORKDIR}/git"

CFLAGS_append_morty = " -DMORTY_BUILD"
CFLAGS_append_daisy = " -DMORTY_BUILD"

ENABLE_BTR_IFCE = "--enable-btr-ifce=${@bb.utils.contains('DISTRO_FEATURES', 'bluetooth', \
                                            bb.utils.contains('DISTRO_FEATURES', 'gdbus_bluez5', 'gdbus_bluez5', \
                                                bb.utils.contains('DISTRO_FEATURES', 'bluez5', 'bluez5', 'bluez4', d), d), 'none', d)}"
EXTRA_OECONF += "${ENABLE_BTR_IFCE}"

ENABLE_STREAMING_IN = "--enable-streaming-in=${@bb.utils.contains('DISTRO_FEATURES', 'btr_disable_streaming_in','no','yes',d)}"
EXTRA_OECONF += " ${ENABLE_STREAMING_IN} "

ENABLE_RDK_LOGGER = "--enable-rdk-logger=${@bb.utils.contains('RDEPENDS_${PN}', '${MLPREFIX}rdk-logger', 'yes', 'no', d)}"
EXTRA_OECONF += " ${ENABLE_RDK_LOGGER}"

inherit autotools pkgconfig coverity
