require add-non-root-user-group.inc
require lxc-image.inc
require recipes-core/images/rdk-generic.inc

## generate libs json file for BundleGenerator
inherit generate_libs_json

IMAGE_INSTALL += "rdkservices-screencapture"
