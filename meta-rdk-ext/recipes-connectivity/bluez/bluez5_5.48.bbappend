FILESEXTRAPATHS_prepend := "${THISDIR}/${PN}_${PV}:"

## Disable Patches
SRC_URI_remove = " \
    file://0001-hciattach-bcm43xx-fix-the-delay-timer-for-firmware-d.patch \
    file://cve-2017-1000250.patch \
    "
## Patches ported by SkyQ
SRC_URI += "file://breakpad.patch \
    file://bluez-5.48-002-disable-unneeded-plugins.patch \
    file://bluez-5.48-003-add-configurable-char-write-value-options.patch \
    file://bluez-5.48-005-enable_auto_connect_on_all_disconnects.patch \
    file://bluez-5.48-006-change_cache_clear_timeout.patch \
    file://bluez-5.48-007-disable_sigpipe_signal.patch \
    file://bluez-5.48-008-make-storage-dir-runtime-configurable.patch \
    file://bluez-5.48-009-fix-gatt-characteristic-crash-on-remove.patch \
    file://bluez-5.48-010-add-configurable-kernel-connection-control.patch \
    file://bluez-5.48-011-add-configurable-secure-connections.patch \
    file://bluez-5.48-012-add-configurable-power-off-on-startup.patch \
    file://bluez-5.48-013-add-configurable-att-le-mtu.patch \
    file://bluez-5.48-014-add-configurable-delayed-gatt-connection.patch \
    file://bluez-5.48-015-delete-autoconnect-on-remove.patch\
    file://bluez-5.48-016-disable-irk-storage-for-sky-devices.patch \
    file://bluez-5.48-017-bluetooth_configuration_hardening.patch \
    file://bluez-5.48-019-improve_firmware_upload_ruwido.patch \
    file://bluez-5.48-020-main_configuration_hardening.patch \
    file://bluez-5.48-021-set-bdaddr-in-phys-uhid.patch \
    file://bluez-5.48-022-enable_bdaddr.patch \
    file://bluez-5.48-023-enable_discovery_filter.patch \
    file://bluez-5.48-024-add-remote-device-name-change-event-handler.patch \
    file://bluez-5.48-025-add-hog-service-for-skyq-rcus.patch \
    file://bluez-5.48-026-disable-bluez-powercyle-respawn.patch \
    file://bluez-5.48-027-free-discovery-reply-on-error.patch \
    file://bluez-5.48-028-crash-in-gatt-client-callback.patch \
    file://bluez-5.48-029-create_storage_directory_before_starting_service.patch \
    file://bluez-5.48-032-restore-file-AMLOGIC-1276.patch \
    file://bluez-5.48-033-enable-debug-logging.patch \
    file://0001-testtools-fix-SIOCGSTAMP-undeclared-error.patch \
    file://0002-libexecdir-location.patch \
    file://bluez-5.48-035-avrcp-transport-volume-change.patch \
    file://bluez-5.48-036-changes_to_fix_crash_during_BT_SIG_tests.patch \
    file://bluez-5.48-037-bluetooth_avdtp_a2dp_abort.patch \
    file://bluez-5.48-038-bluez-stream-free-crash-fix.patch \
    file://bluez-5.48-039-bluetooth_a2dp_ref_negative_abort.patch \
    file://bluez-5.48-040-bluez-btrmgr-crash.patch \
    file://bluez-5.48-041-clear_old_cache_list.patch \
    file://bluez-5.48-043-auto-accept-connection-for_5.10-Kernel.patch \
    file://bluez-5.48-044-add-up-to-date-battery-service.patch \
    file://bluez-5.48-045-ensure-bluez-connects-on-bredr-to-audio-devices.patch \
    file://bluz5_5.48_gatt_db_service_crash.patch \
    file://bluez-5.48-046-prevent-scan-becoming-stuck.patch \
    file://bluez-5.48-047-Gen4-Crash-avoid.patch \
    file://bluez-5.48-048-disable-avc-passthrough-uinput.patch \
    file://bluez-5.48-049-Queue_remove_crash.patch \
    file://bluez-5.48-050-migrate_ble_pairing_data_to_originalPath.patch \
    file://bt_original_path_setup.sh \
    file://bluez-5.48-051-fix-for-incorrect-transaction-label.patch \
    file://bluez-5.48-052-bt_uuid_to_uuid128-crash.patch \
	"
SRC_URI_append_kirkstone = " file://bluez-5.48-kirkstone_compile_errors.patch "

## Disabled SkyQ Patches
#file://bluez-5.48-018-change_storage_dir.patch

#SRC_URI_append_hybrid += " ${@bb.utils.contains('DISTRO_FEATURES', 'enable-rdkv-bt-voice', '', 'file://0001-bluetooth_autoenable_policy_main_conf.patch', d)}"
#SRC_URI_append_client += " ${@bb.utils.contains('DISTRO_FEATURES', 'enable-rdkv-bt-voice', '', 'file://0001-bluetooth_autoenable_policy_main_conf.patch', d)}"


#Patches needed for Flex2 devices
SRC_URI_append = "${@bb.utils.contains('DISTRO_FEATURES', 'flex2_rdk', ' file://bluez-5.48-040-RDKTV-14757-fix-to-retain-connection-after-reboot.patch','',d)}"
SRC_URI_append = "${@bb.utils.contains('DISTRO_FEATURES', 'flex2_rdk', ' file://bluez-5.48-041-rename-bluez-adapter-for-xumo.patch','',d)}"
SRC_URI_append = "${@bb.utils.contains('DISTRO_FEATURES', 'flex2_rdk', ' file://bluez-5.48-042-fix-for-autoenable-policy-main-conf.patch','',d)}"
