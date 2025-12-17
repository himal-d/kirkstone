FILESEXTRAPATHS_prepend := "${THISDIR}/${PN}:"
SRC_URI += " \
            file://0001-libexecdir-location.patch \
            file://0002-bluez-5.6xx-bluetooth_autoenable_policy_main_conf.patch \
            file://0007-add-configurable-secure-connections_5_66.patch \
            file://0005-clear_old_cache_list.patch \
            file://0008-enabling_network_security_5_66.patch \
            file://CVE-2023-45866-5.66.patch \
           "
