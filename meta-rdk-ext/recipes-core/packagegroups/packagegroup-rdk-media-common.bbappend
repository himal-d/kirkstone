RDEPENDS_packagegroup-rdk-media-common += "\
    ${@bb.utils.contains('DISTRO_FEATURES', 'syslog-ng', 'syslog-ng', '', d)} \
    "
