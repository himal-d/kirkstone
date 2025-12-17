require add-non-root-user-group.inc
require lxc-image.inc
require recipes-core/images/rdk-generic.inc

IMAGE_INSTALL_append = " ${@bb.utils.contains('DISTRO_FEATURES', 'streamfs', 'streamfs streamfs-fcc', '', d)}"

## generate libs json file for BundleGenerator
inherit generate_libs_json
