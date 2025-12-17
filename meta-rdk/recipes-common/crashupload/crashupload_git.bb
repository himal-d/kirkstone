SUMMARY = "Crashupload application"
SECTION = "console/utils"

LICENSE = "Apache-2.0"
LIC_FILES_CHKSUM = "file://LICENSE;md5=175792518e4ac015ab6696d16c4f607e"

PV = "${RDK_RELEASE}+git${SRCPV}"
SRCREV = "${AUTOREV}"

SRC_URI = "${CMF_GIT_ROOT}/rdk/components/generic/crashupload;module=.;protocol=${CMF_GIT_PROTOCOL};branch=${CMF_GIT_BRANCH}"

PV = "${RDK_RELEASE}+git${SRCPV}"
SRCREV = "${AUTOREV}"
S = "${WORKDIR}/git"

DEPENDS = "glib-2.0 libsyswrapper"

export LINK = "${LD}"

CFLAGS += " \
        -I=${libdir}/glib-2.0/include \
        -I=${includedir}/glib-2.0 \
        -DYOCTO_BUILD "

export GLIBS = "-lglib-2.0 -lz"
export USE_DBUS = "y"

LDFLAGS += "-Wl,-O1 -lsecure_wrapper"

inherit coverity
inherit systemd

do_compile() {
        oe_runmake -B -C ${S}/src
}

do_install() {
        install -d ${D}${base_libdir}/rdk
        install -d ${D}${bindir}
        install -d ${D}${sysconfdir} ${D}${sysconfdir}/rfcdefaults
        install -m 0755 ${S}/uploadDumps.sh ${D}${base_libdir}/rdk
        install -m 0755 ${S}/src/inotify-minidump-watcher ${D}${bindir}
        install -m 0755 ${S}/rfcdefaults/crashupload.ini ${D}${sysconfdir}/rfcdefaults
        ln -sf ${bindir}/inotify-minidump-watcher ${D}${bindir}/waitForFlag
}

do_install_append_broadband() {
        use_sysv="${@bb.utils.contains('DISTRO_FEATURES', 'systemd', 'false', 'true', d)}"
        $use_sysv || install -d ${D}${systemd_unitdir}/system
        $use_sysv || install -m 0644 ${S}/coredump-upload.service ${D}${systemd_unitdir}/system/
        $use_sysv || install -m 0644 ${S}/coredump-upload.path ${D}${systemd_unitdir}/system/
        $use_sysv || install -m 0644 ${S}/minidump-on-bootup-upload.service ${D}${systemd_unitdir}/system/
        $use_sysv || install -m 0644 ${S}/minidump-on-bootup-upload.timer ${D}${systemd_unitdir}/system/
        install -d ${D}${sysconfdir}
        #install -m 0755 ${S}/uploadDumpsUtils.sh ${D}${base_libdir}/rdk
}

SYSTEMD_SERVICE_${PN}_append_broadband = " coredump-upload.service \
                                           coredump-upload.path \
                                           minidump-on-bootup-upload.service \
                                           minidump-on-bootup-upload.timer \
"
RDEPENDS_${PN} += "busybox"

PACKAGE_BEFORE_PN += "${PN}-conf"

FILES_${PN} += "${base_libdir}/rdk/uploadDumps.sh"
#FILES_${PN}_append_broadband = " ${base_libdir}/rdk/uploadDumpsUtils.sh"
FILES_${PN} += " ${bindir}/inotify-minidump-watcher"
FILES_${PN} += "${bindir}/waitForFlag"
FILES_${PN}-conf = "${sysconfdir}/rfcdefaults/crashupload.ini"
