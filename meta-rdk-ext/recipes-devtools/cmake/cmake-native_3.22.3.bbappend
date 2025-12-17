CMAKE_EXTRACONF_append = "${@bb.utils.contains('DISTRO_FEATURES', 'nrdp_5.3', ' -DBUILD_TESTING=OFF ', '', d)}"
