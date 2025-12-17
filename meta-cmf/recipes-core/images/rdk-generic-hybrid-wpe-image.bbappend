require add-non-root-user-group.inc
require lxc-image.inc
require recipes-core/images/rdk-generic.inc
ROOTFS_POSTPROCESS_COMMAND += "remove_Failure_case_dsmgr_services; "

IMAGE_INSTALL_append = " ${@bb.utils.contains('DISTRO_FEATURES', 'streamfs', 'streamfs streamfs-fcc', '', d)}"

remove_Failure_case_dsmgr_services () {
                       sed -i '/OnFailure=reboot-notifier@%i.service/ c\#OnFailure=reboot-notifier@%i.service' ${IMAGE_ROOTFS}${systemd_unitdir}/system/dsmgr.service
}
