FILESEXTRAPATHS_prepend := "${THISDIR}/${PN}:"

SRC_URI_remove = "${RDKB_CCSP_ROOT_GIT}/RdkLedManager/generic;protocol=${RDK_GIT_PROTOCOL};branch=${CCSP_GIT_BRANCH};name=LedManager"
SRC_URI += "${CMF_GIT_ROOT}/rdkb/components/opensource/ccsp/RdkLedManager;protocol=${CMF_GIT_PROTOCOL};branch=${CMF_GIT_BRANCH};name=LedManager"

inherit coverity

DEPENDS += "json-c breakpad breakpad-wrapper"
DEPENDS_remove = "hal-ledmanager"

CFLAGS += " -Wno-implicit-function-declaration -DFEATURE_RDKB_LED_MANAGER"
CFLAGS += "-I${STAGING_INCDIR}/breakpad "
CXXFLAGS += "-I${STAGING_INCDIR}/breakpad "

LDFLAGS += "-lbreakpadwrapper -lpthread -lstdc++"

SRC_URI += "file://0001-Remove-hal-dependencies.patch;apply=no"

do_ledmanager_patches() {
    cd ${S}
    if [ ! -e patch_applied ]; then
        bbnote "Patching 0001-Remove-hal-dependencies.patch"
        patch -p1 < ${WORKDIR}/0001-Remove-hal-dependencies.patch
        touch patch_applied
    fi
}

addtask ledmanager_patches after do_unpack do_patch before do_configure
