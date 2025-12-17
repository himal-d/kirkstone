SUMMARY = "Container generator tool"
DESCRIPTION = "The container generator and other components are used to post process root file system and create environment for containers"
LICENSE = "Apache-2.0"
LIC_FILES_CHKSUM = "file://LICENSE;md5=175792518e4ac015ab6696d16c4f607e"

PV = "${RDK_RELEASE}+git${SRCPV}"
PR="0"

SRC_URI = "${CMF_GIT_ROOT}/rdk/components/generic/lxc-container-generator;protocol=${CMF_GIT_PROTOCOL};branch=${CMF_GIT_MASTER_BRANCH};name=lxc-container-generator"
SRCREV ?= "${AUTOREV}"
S = "${WORKDIR}/git"

inherit native

install_lxc_config() {
	if [ "$#" -eq 2 ]; then
		if [ -f ${WORKDIR}/xml/$2 ]; then
			if [ -d ${D}${datadir}/${BPN}/$1 ]; then
				install -m 644 ${WORKDIR}/xml/$2 ${D}${datadir}/${BPN}/$1/
			else
				echo "install_lxc_config: Directory ${D}${datadir}/${BPN}/$1/ does not exists!"
				exit 1
			fi
		fi
	else
		echo "install_lxc_config: Wrong number of parameters!"
		exit 1
	fi
}

PREFERRED_VERSION_lxc ?= "2.0.6"
YOCTO_VERSION_MAJOR_dunfell = "3"
YOCTO_VERSION_MAJOR ?= "2"

do_install() {
	install -d ${D}${datadir}/${BPN}
	install -d ${D}${datadir}/${BPN}/secure
	install -d ${D}${datadir}/${BPN}/non_secure

	install -d ${D}${datadir}/${BPN}/src/lib/dobby
	install -m 755 ${S}/src/*.py ${D}${datadir}/${BPN}/src/
	install -m 755 ${S}/src/lib/*.py ${D}${datadir}/${BPN}/src/lib/
	install -m 755 ${S}/src/lib/dobby/*.py ${D}${datadir}/${BPN}/src/lib/dobby/
	install -d ${D}${datadir}/${BPN}/src/conf
	install -m 755 ${S}/src/conf/config.ini ${D}${datadir}/${BPN}/src/conf/config.ini
        install -d ${D}${datadir}/${BPN}/include
        install -m 644 ${S}/include/*.xml ${D}${datadir}/${BPN}/include/

        # Install yocto version-specific autoinstalled libs config files
        install -m 755 ${S}/src/conf/config-yocto-${YOCTO_VERSION_MAJOR}.x/* ${D}${datadir}/${BPN}/src/conf/
        install -m 755 ${S}/src/conf/config-lxc-${PREFERRED_VERSION_lxc}/* ${D}${datadir}/${BPN}/src/conf/

	#install_lxc_config non_secure lxc_conf_EXAMPLE.xml
	#install_lxc_config non_secure lxc_conf_EXAMPLE_appendsample.xml
}

FILESEXTRAPATHS_prepend := "${THISDIR}/files:"
SRC_URI += "${@bb.utils.contains('DISTRO_FEATURES', 'disable-lxcgen-warnings','file://0001-convert-error-to-warning.patch;apply=no','',d)} \
            ${@bb.utils.contains('DISTRO_FEATURES', 'disable-lxcgen-warnings','file://0001-switch-exceptions-to-warnings.diff;apply=no','',d)} \
            ${@bb.utils.contains('DISTRO_FEATURES', 'disable-lxcgen-warnings','file://0001-capkeep-support.diff;apply=no','',d)} \
"

addtask do_apply_patch after do_unpack before do_configure

do_apply_patch() {
    cd ${S}
    if [ ! -e patch_applied ]; then
        if [ "${@bb.utils.contains('DISTRO_FEATURES', 'disable-lxcgen-warnings', 'true', 'false', d)}" = "true" ]; then
                patch -p1 < ${WORKDIR}/0001-convert-error-to-warning.patch
                patch -p1 < ${WORKDIR}/0001-switch-exceptions-to-warnings.diff
                patch -p1 < ${WORKDIR}/0001-capkeep-support.diff
        fi
        touch patch_applied
    fi
}
