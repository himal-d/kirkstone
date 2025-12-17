EXTRA_OECONF_append = " --enable-ccsp-common"
EXTRA_OECONF_append = " --enable-dml"
EXTRA_OECONF_append = " --enable-journalctl"

EXTRA_OECONF_append = "${@bb.utils.contains('DISTRO_FEATURES', 'sm_app', ' --enable-sm-app', '', d)}"
