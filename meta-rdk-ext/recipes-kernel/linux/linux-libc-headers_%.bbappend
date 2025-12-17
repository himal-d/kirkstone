FILESEXTRAPATHS_prepend_broadband := "${THISDIR}/files:"

SRC_URI_append_broadband = "\
                  file://0001-add-support-for-http-host-headers-cookie-url-netfilt.patch \
                  file://http_netfilter.cfg \
                 "

SRC_URI_remove_broadband = "${@bb.utils.contains_any('DISTRO_FEATURES', 'dunfell kirkstone', ' file://0001-add-support-for-http-host-headers-cookie-url-netfilt.patch', '', d)}"

SRC_URI_append_broadband = "${@bb.utils.contains_any('DISTRO_FEATURES', 'dunfell kirkstone', ' file://0001-http-headers-netfliter-dunfell.patch', '', d)}"
