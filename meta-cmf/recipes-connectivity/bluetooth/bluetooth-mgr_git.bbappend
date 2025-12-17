DEPENDS_remove_ipclient = "virtual/media-utils"
DEPENDS_remove_ipclient = "audiocapturemgr"

RDEPENDS_${PN}_remove_ipclient = "virtual/media-utils"
RDEPENDS_${PN}_remove_ipclient = "audiocapturemgr"

EXTRA_OECONF_remove_ipclient = "${ENABLE_ACM}"
EXTRA_OECONF_remove_ipclient = "${ENABLE_AC_RMF}"

CFLAGS_remove_ipclient = " ${@bb.utils.contains('RDEPENDS_${PN}', 'virtual/media-utils', ' -I${STAGING_INCDIR}/media-utils/audioCapture', ' ', d)}"

ENABLE_SAFEC = "--enable-safec=${@bb.utils.contains('DISTRO_FEATURES', 'safec','yes', 'no', d)}"
EXTRA_OECONF += " ${ENABLE_SAFEC}"

do_install_append_ipclient() {
    #remove audiocapturemgr service entry for ipclient from btmgr.service
    bbnote "Modifying btmgr.service"
    sed -i 's/audiocapturemgr.service/ /g' ${D}${systemd_system_unitdir}/btmgr.service
}
