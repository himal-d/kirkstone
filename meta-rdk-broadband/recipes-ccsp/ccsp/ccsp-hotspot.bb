SUMMARY = "CCSP Hotspot"
HOMEPAGE = "https://github.com/belvedere-yocto/hotspot"

LICENSE = "Apache-2.0 & ISC"
LIC_FILES_CHKSUM = "file://LICENSE;md5=7fd38647ff87fdac48b3fb87e20c1b07"

DEPENDS = "dbus libnetfilter-queue utopia ccsp-lm-lite telemetry libunpriv"
DEPENDS_append = " ${@bb.utils.contains('DISTRO_FEATURES', 'safec', ' safec', " ", d)}"

require ccsp_common.inc
CFLAGS += " -Wall -Werror -Wextra -Wno-pointer-sign -Wno-sign-compare "
CFLAGS_append_kirkstone = " -Wno-array-bounds -Wno-stringop-overflow "
SRC_URI = "${CMF_GIT_ROOT}/rdkb/components/opensource/ccsp/hotspot;protocol=${CMF_GIT_PROTOCOL};branch=${CMF_GIT_BRANCH};name=hotspot"

SRCREV_hotspot = "${AUTOREV}"
SRCREV_FORMAT = "hotspot"
PV = "${RDK_RELEASE}+git${SRCPV}"

S = "${WORKDIR}/git"

inherit autotools pkgconfig ${@bb.utils.contains("DISTRO_FEATURES", "kirkstone", "python3native", "pythonnative", d)}

CFLAGS_append = " ${@bb.utils.contains('DISTRO_FEATURES', 'safec',  ' `pkg-config --cflags libsafec`', '-fPIC', d)}"

LDFLAGS_append = " ${@bb.utils.contains('DISTRO_FEATURES', 'safec', ' `pkg-config --libs libsafec`', '', d)}"
LDFLAGS_remove = "${@bb.utils.contains('DISTRO_FEATURES', 'safec', '-lsafec-3.5', '', d)}"
LDFLAGS_append_dunfell = "${@bb.utils.contains('DISTRO_FEATURES', 'safec', ' -lsafec-3.5.1 ', '', d)}"
LDFLAGS_append_kirkstone = " ${@bb.utils.contains('DISTRO_FEATURES', 'safec', ' -lsafec ', '', d)}"
CFLAGS_append = " ${@bb.utils.contains('DISTRO_FEATURES', 'safec', '', ' -DSAFEC_DUMMY_API', d)}"
CFLAGS_append = " ${@bb.utils.contains('DISTRO_FEATURES', 'OneWifi', '-DRDK_ONEWIFI', '', d)}"

EXTRA_OECONF_append = " ${@bb.utils.contains('DISTRO_FEATURES', 'WanFailOverSupportEnable', ' --enable-wanfailover ', '', d)}"

CFLAGS_append = " \
   -I${STAGING_INCDIR}/dbus-1.0 \
   -I${STAGING_LIBDIR}/dbus-1.0/include \
   -I${STAGING_INCDIR}/ccsp \
   "

LDFLAGS += "-ldbus-1 -lbreakpadwrapper"

do_compile_prepend(){
    (${PYTHON} ${STAGING_BINDIR_NATIVE}/dm_pack_code_gen.py ${S}/source/hotspotfd/config/hotspot.XML ${S}/source/hotspotfd/dm_pack_datamodel.c)
}

do_install_append () {
    # Config files and scripts
	install -d ${D}/usr/ccsp
	install -d ${D}/usr/ccsp/hotspot
	install -d ${D}/usr/include/ccsp

	install -m 777 ${D}/usr/bin/hotspot_arpd -t ${D}/usr/ccsp
	install -m 644 ${S}/source/hotspotfd/include/dhcpsnooper.h ${D}/usr/include/ccsp
	install -m 644 ${S}/source/hotspotfd/include/hotspotfd.h ${D}/usr/include/ccsp
    	install -m 777 ${S}/source/HotspotApi/libHotspotApi.h ${D}/usr/include/ccsp
    	ln -sf /usr/bin/CcspHotspot ${D}${prefix}/ccsp/hotspot/CcspHotspot
}

PACKAGES += "${PN}-ccsp"

FILES_${PN}-ccsp = " \
    /usr/ccsp/hotspot_arpd \
    /usr/ccsp/* \
    "
FILES_${PN} += " \
    ${prefix}/ccsp/hotspot/CcspHotspot \
    ${prefix}/ccsp/hotspot/hotspot.XML  \
    ${libdir}/libHotspotApi.so* \
	"

FILES_${PN}-dbg = " \
   ${prefix}/ccsp/.debug \
   ${prefix}/ccsp/hotspot/.debug \
   ${prefix}/src/debug \
   ${bindir}/.debug \
   ${libdir}/.debug \
   "
