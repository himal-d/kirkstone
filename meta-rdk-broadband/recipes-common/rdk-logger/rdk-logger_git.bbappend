CFLAGS_append += " ${@bb.utils.contains('DISTRO_FEATURES', 'bci', '', '-DFEATURE_SUPPORT_ONBOARD_LOGGING',d)}"
EXTRA_OECONF  += " ${@bb.utils.contains('DISTRO_FEATURES', 'bci', '', ' --enable-onboardlog',d)}"

HASBCI = "${@bb.utils.contains('DISTRO_FEATURES', 'bci', 'true', 'false',d)}"
do_install_append() {
   if [ ${HASBCI} = "false" ]; then
    install -d ${D}/etc
       touch ${D}/etc/ONBOARD_LOGGING_ENABLE
   fi
}

FILES_${PN} += " \
       ${@bb.utils.contains("DISTRO_FEATURES", "bci", " ", "/etc/* ", d)} \
"
