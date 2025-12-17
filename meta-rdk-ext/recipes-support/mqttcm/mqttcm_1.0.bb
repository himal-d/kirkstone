SUMMARY = "Mqtt Connection Manager"
HOMEPAGE = "https://github.com/xmidt-org/mqttConnManager"
SECTION = "libs"
LICENSE = "Apache-2.0"
LIC_FILES_CHKSUM = "file://LICENSE;md5=86d3f3a95c324c9479bd8986968f4327"

DEPENDS = "mosquitto rbus cpeabs cimplog"

SRCREV = "cabb874685af3dc4053dee3cb5eeda4e823bd154"
SRC_URI = "git://github.com/xmidt-org/mqttConnManager.git;branch=main"

RDEPENDS_${PN} += "util-linux-uuidgen"

PV = "git+${SRCPV}"

S = "${WORKDIR}/git"

ASNEEDED = ""

inherit pkgconfig cmake

EXTRA_OECMAKE = "-DBUILD_TESTING=OFF -DBUILD_YOCTO=true"

LDFLAGS += "-lmosquitto -lrbus -lcpeabs -lcimplog"

CFLAGS_append = " \
        -DBUILD_YOCTO \
        -I${STAGING_INCDIR}/rbus \
        -I${STAGING_INCDIR}/cimplog \
        -I${STAGING_INCDIR}/mosquitto \
        -fPIC \
        "
CFLAGS_append = " -DFEATURE_SUPPORT_MQTTCM"
CFLAGS_append_dunfell = " -Wno-format-truncation -Wno-sizeof-pointer-memaccess"

do_install_append_broadband() {
      install -d ${D}/usr/ccsp/mqttConnManager
}

FILES_SOLIBSDEV = ""
FILES_${PN} += "${exec_prefix}/ccsp/mqttConnManager" 
FILES_${PN} += "${bindir}/*"

ASNEEDED_hybrid = ""
ASNEEDED_client = ""


