RDEPENDS_packagegroup-rdk-media-common_remove = "virtual/ea-games-provider"

RDEPENDS_packagegroup-rdk-media-common_append = " rfc"
RDEPENDS_packagegroup-rdk-media-common_append = " rdm"
RDEPENDS_packagegroup-rdk-media-common_append = " memstress"
RDEPENDS_packagegroup-rdk-media-common_append = " rdkat"
RDEPENDS_packagegroup-rdk-media-common_append = " cpuprocanalyzer"
RDEPENDS_packagegroup-rdk-media-common_append = " libunpriv"
RDEPENDS_packagegroup-rdk-media-common_append = " ctrlm-main"
RDEPENDS_packagegroup-rdk-media-common_append = " xdialserver"
RDEPENDS_packagegroup-rdk-media-common_append = " dibbler-client"
RDEPENDS_packagegroup-rdk-media-common_append = " gst-external-plugin"
RDEPENDS_packagegroup-rdk-media-common_append = "\
   ${@bb.utils.contains("DISTRO_FEATURES", "tinyrdk", " smartmon","",d)}\
   "

RDEPENDS_packagegroup-rdk-media-common_append = "\
   ${@bb.utils.contains("DISTRO_FEATURES", "rialto_servermanager_sim", "\
   rialto-servermanager-sim \
   ","",d)} \
"

RDEPENDS_packagegroup-rdk-media-common_append = "\
   ${@bb.utils.contains("DISTRO_FEATURES", "blercudaemon", "asbluetoothrcu","",d)} \
   ${@bb.utils.contains("DISTRO_FEATURES", "rdkbrowser2", "rdkbrowser2","",d)} \
   "

RDEPENDS_packagegroup-rdk-media-common_remove_ipclient = "virtual/media-utils"

# smartmon does not build in voice build due to boost issues.
RDEPENDS_packagegroup-rdk-media-common_remove_voice = " smartmon"
