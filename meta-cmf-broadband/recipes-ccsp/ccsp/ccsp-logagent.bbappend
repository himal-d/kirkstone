CFLAGS_append  = " ${@bb.utils.contains('DISTRO_FEATURES', 'rdkb_telcovoice_manager', '-DFEATURE_RDKB_TELCOVOICE_MANAGER', '', d)}"
CFLAGS_append  = " ${@bb.utils.contains('DISTRO_FEATURES', 'rdkb_voice_manager_dmltr104_v2', '-DFEATURE_RDKB_TELCOVOICE_MANAGER', '', d)}"
CFLAGS_append += "${@bb.utils.contains('DISTRO_FEATURES', 'fwupgrade_manager', ' -DFEATURE_RDKB_FWUPGRADE_MANAGER ', '', d)}"
