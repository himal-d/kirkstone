SUMMARY = "Scripts for rdkb devices."
SECTION = "console/utils"

LICENSE = "Apache-2.0"
LIC_FILES_CHKSUM = "file://LICENSE;md5=175792518e4ac015ab6696d16c4f607e"

FILESEXTRAPATHS_prepend := "${THISDIR}/files:"
PV = "${RDK_RELEASE}"
 
SYSINTB_DEVICE ??= "intel-x86-pc/rdk-broadband"

 
SRC_URI = "${RDKB_COMPONENTS_ROOT_GIT}/generic/sysint/generic;protocol=${RDK_GIT_PROTOCOL};branch=${RDK_GIT_BRANCH};name=sysintbroadband"
SRC_URI += "${RDKB_COMPONENTS_ROOT_GIT}/generic/sysint/devices/${SYSINTB_DEVICE};module=.;protocol=${RDK_GIT_PROTOCOL};branch=${RDK_GIT_BRANCH};destsuffix=git/device;name=sysintdevice"
SRC_URI += "${@bb.utils.contains('DISTRO_FEATURES','benchmark_enable','file://deviceinfo.sh ','',d)}"

SRCREV = "${AUTOREV}"
SRCREV_sysintbroadband = "${AUTOREV}"
SRCREV_sysintdevice = "${AUTOREV}"
SRCREV_FORMAT = "sysintbroadband_sysintdevice"

S = "${WORKDIR}/git"

inherit systemd 

do_install() {
	install -d ${D}${sysconfdir}
        install -d ${D}/rdklogger
        install -d ${D}${systemd_unitdir}/system
        # Creating generic location for sysint utils
        install -d ${D}${base_libdir}/rdk
        if [ -f ${S}/device/imagelist ]; then
	    install -m 0644 ${S}/device/imagelist ${D}${sysconfdir}
        fi
	install -m 0755 ${S}/*.sh ${D}/rdklogger/
	#do we need all the scripts - review later?

	if [ -f ${S}/device/etc/device.properties ]; then
            install -m 0644 ${S}/device/etc/device.properties ${D}${sysconfdir}
        else
            install -m 0644 ${S}/etc/device.properties ${D}${sysconfdir}
        fi

	if [ -f ${S}/device/etc/include.properties ]; then
	    install -m 0644 ${S}/device/etc/include.properties ${D}${sysconfdir}
	fi

	install -m 755 ${S}/log_timestamp.sh ${D}${sysconfdir}
        rm -f ${D}/rdklogger/log_timestamp.sh
        echo "IMAGE_TYPE=OSS" >> ${D}${sysconfdir}/device.properties
        
        if ${@bb.utils.contains('DISTRO_FEATURES', 'benchmark_enable', 'true', 'false', d)}; then
            install -d ${D}${sbindir}
            install -d ${D}${base_libdir}/rdk
            install -m 0755 ${S}/../deviceinfo.sh ${D}${sbindir}/deviceinfo.sh
        fi

}

do_install_append_qemux86broadband() {
	install -d ${D}${systemd_unitdir}/system
        install -m 0755 ${S}/device/lib/rdk/* ${D}${base_libdir}/rdk
	install -m 0755 ${S}/device/systemd_units/* ${D}${systemd_unitdir}/system/
}
 
 
FILES_${PN} += "${sysconfdir}/*"
FILES_${PN} += "rdklogger/*"
FILES_${PN} += "${base_libdir}/rdk/*"
FILES_${PN} += "${sbindir}/deviceinfo.sh"
FILES_${PN}_append_qemux86broadband += "${systemd_unitdir}/system/*"
