SUMMARY = "RDK IP based mediaclient (STB) Image"

REQUIRED_DISTRO_FEATURES = "ipclient rdkshell"

IMAGE_FEATURES += "splash mediaclient"

inherit rdk-image-sdk

require ${RDKROOT}/meta-rdk/recipes-core/images/sdk-common.inc
require ${RDKROOT}/meta-rdk/recipes-core/images/rdk-generic-media-common.inc

IMAGE_INSTALL += "packagegroup-rdk-oss-ipstb"
#Add a uuid generator for generating random receiver id
IMAGE_INSTALL += "util-linux-uuidgen"
IMAGE_INSTALL += "rdkservices-screencapture"

python __anonymous () {
    if "client" not in d.getVar('MACHINEOVERRIDES', True):
        raise bb.parse.SkipPackage("Image is meant for video client class of devices")
}

#REFPLTV-976 removing the Control Manager service, as feature not fully functional.
require ${RDKROOT}/meta-cmf/recipes-core/images/add-non-root-user-group.inc
require ${RDKROOT}/meta-cmf/recipes-core/images/lxc-image.inc
require ${RDKROOT}/meta-cmf/recipes-core/images/rdk-generic.inc

#Add the final common image which will be created as symbolic link
IMAGE_LINK_NAME = "${IMAGE_BASENAME}"

IMAGE_INSTALL_append = " ${@bb.utils.contains('DISTRO_FEATURES', 'streamfs', 'streamfs streamfs-fcc', '', d)}"
