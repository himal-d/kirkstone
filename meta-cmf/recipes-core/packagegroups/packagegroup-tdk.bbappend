RDEPENDS_packagegroup-tdk_append = "\
  sysstat \
  ${@bb.utils.contains('DISTRO_FEATURES', 'rdk-profiling', ' packagegroup-rdk-profiling', '', d)} \
  "