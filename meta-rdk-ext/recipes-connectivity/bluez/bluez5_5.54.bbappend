
FILESEXTRAPATHS_prepend := "${THISDIR}/${PN}:"
SRC_URI += " \
            file://0001-libexecdir-location.patch \
            file://0004-bluetooth_avdtp_a2dp_abort.patch \
            file://0005-clear_old_cache_list.patch \
            file://0007-bluez-stream-free-crash-fix.patch \
            file://0009-unpairing_issue_on_disconnection.patch \
            file://0010-bluez-btrmgr-crash.patch \
            file://0011-bluez-5.54-add-up-to-date-battery-service.patch \
            file://0012-bluez-5.54-ensure-bluez-connects-on-bredr-to-audio-devices.patch \
            file://bt_original_path_setup.sh \
           "
SRC_URI_append_hybrid += "file://0002-bluetooth_autoenable_policy_main_conf.patch"
SRC_URI_append_client += "file://0002-bluetooth_autoenable_policy_main_conf.patch"
