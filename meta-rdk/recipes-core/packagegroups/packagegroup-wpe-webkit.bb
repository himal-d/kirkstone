DESCRIPTION = "Metrological WPE Packagegroup"
LICENSE = "MIT"

inherit packagegroup

PACKAGES = "\
    packagegroup-wpe-webkit \
"

RDEPENDS_packagegroup-wpe-webkit = "\
    wpe-webkit \
    wpe-backend-rdk-platform-plugin \
    wpe-webkit-web-inspector-plugin \
    ${@bb.utils.contains('DISTRO_FEATURES', 'enable_wpe-webdriver', 'wpe-webdriver', '', d)} \
"

# Additional OSS packages etc, which are only needed for WPE based images.
RDEPENDS_packagegroup-wpe-webkit += "\
    xkeyboard-config \
    shared-mime-info \
"

# Additional thunder packages, which are only needed for WPE based images.
RDEPENDS_packagegroup-wpe-webkit += "\
    wpeframework \
    thunderjs \
"
