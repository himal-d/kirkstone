#
# Yocto recipe to install obuspa open source project
#

SUMMARY = "USP Pa component"
DESCRIPTION = "Agent for USP protocol"
DEPENDS = "openssl sqlite3 curl zlib ccsp-common-library mosquitto libwebsockets"
LICENSE = "BSD-3-Clause"
LIC_FILES_CHKSUM = "file://LICENSE;md5=a3a4606e52c16f583aefb8b47a9db31a"

require recipes-ccsp/ccsp/ccsp_common.inc


# OBUSPA is the reference USP agent codebase
SRC_URI += "git://github.com/BroadbandForum/obuspa;protocol=http;branch=master;rev=8355c200afb6430e3fc55ebabe8a9a709ae5d04f;name=obuspa;destsuffix=obuspa"

# USPPA is the RDK specializations
SRC_URI += "git://github.com/rdkcentral/usp-pa-vendor-rdk;protocol=http;branch=main;rev=c455c7cec7564ea8edb4dce3936cb3d0b94e489a;name=usppa;destsuffix=usp-pa-vendor-rdk"

# Patches for OBUSPA
#SRC_URI += "file://patches/remove_duplicate_min_max_define.patch"

# Configure options for OBUSPA
EXTRA_OECONF += "--disable-websockets --enable-mqtt"
EXTRA_OECONF_append  = " --with-ccsp-platform=bcm --with-ccsp-arch=arm "

# Configuration files for target
SRC_URI += "file://conf/usp_factory_reset.conf"
SRC_URI += "file://conf/usp_dm_comps.conf"
SRC_URI += "file://conf/usp_dm_objs.conf"
SRC_URI += "file://conf/usp_dm_params.conf"
SRC_URI += "file://conf/usp_truststore.pem"
SRC_URI += "file://usp-pa.service"


# Make sure our source directory (for the build) matches the directory structure in the tarball
S = "${WORKDIR}/obuspa"

# Specify the rules to use to build and install this package
inherit autotools pkgconfig systemd


CFLAGS += " \
    -I${STAGING_INCDIR}/dbus-1.0 \
    -I${STAGING_LIBDIR}/dbus-1.0/include \
    -I${STAGING_INCDIR}/ccsp \
"

LDFLAGS += "-ldbus-1 -lccsp_common"

# Specialize the OBUSPA release by copying across the RDK specific source files to the source directory
do_configure_prepend() {
    cp ${WORKDIR}/usp-pa-vendor-rdk/src/vendor/* ${S}/src/vendor
}

# Copy files to staging area
do_install() {
    install -d ${D}${bindir}
    install -d ${D}${sysconfdir}
    install -d ${D}${sysconfdir}/usp-pa
    install -d ${D}${systemd_system_unitdir}
    
    install -m 0777 ${B}/obuspa ${D}${bindir}/UspPa
    install -m 0644 ${WORKDIR}/conf/usp_factory_reset.conf ${D}${sysconfdir}/usp-pa
    install -m 0644 ${WORKDIR}/conf/usp_dm_comps.conf ${D}${sysconfdir}/usp-pa
    install -m 0644 ${WORKDIR}/conf/usp_dm_objs.conf ${D}${sysconfdir}/usp-pa
    install -m 0644 ${WORKDIR}/conf/usp_dm_params.conf ${D}${sysconfdir}/usp-pa
    install -m 0644 ${WORKDIR}/conf/usp_truststore.pem ${D}${sysconfdir}/usp-pa
    install -m 0644 ${WORKDIR}/usp-pa.service ${D}${systemd_system_unitdir}
}

# Files in staging area to copy to system image
FILES_${PN} += "${bindir}/UspPa"
FILES_${PN} += "${systemd_unitdir}/system/usp-pa.service"
FILES_${PN} += "${sysconfdir}/usp-pa/usp_factory_reset.conf"
FILES_${PN} += "${sysconfdir}/usp-pa/usp_dm_comps.conf"
FILES_${PN} += "${sysconfdir}/usp-pa/usp_dm_objs.conf"
FILES_${PN} += "${sysconfdir}/usp-pa/usp_dm_params.conf"
FILES_${PN} += "${sysconfdir}/usp-pa/usp_truststore.pem"

# Signal that a system-d service must be provisioned
SYSTEMD_SERVICE_${PN} = "usp-pa.service"

## Additional steps for DAC Distro Feature
DEPENDS += "${@bb.utils.contains('DISTRO_FEATURES', 'dac', 'rbus', '', d)}"
#add dependencies for the changes into compiler options
LDFLAGS += "${@bb.utils.contains('DISTRO_FEATURES', 'dac', ' -lrbus ', '', d)}"
CFLAGS  += "${@bb.utils.contains('DISTRO_FEATURES', 'dac', ' -isystem${STAGING_INCDIR}/rbus ', '', d)}"
TARGET_CFLAGS  += "${@bb.utils.contains('DISTRO_FEATURES', 'dac', ' -DINCLUDE_LCM_DATAMODEL ', '', d)}"


