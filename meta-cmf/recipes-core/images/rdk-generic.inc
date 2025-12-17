require recipes-core/images/syslog-ng-config.inc

# Remove QT5 dependencies
IMAGE_INSTALL_remove = "packagegroup-rdk-qt5"

# liberation-fonts has included to have font files
IMAGE_INSTALL_append = " liberation-fonts"

ROOTFS_POSTPROCESS_COMMAND += "${@bb.utils.contains('DISTRO_FEATURES','syslog-ng',' patch_syslog_ng_config; ',' ',d)}"

python patch_syslog_ng_config() {
  bb.build.exec_func('patch_ssl_log',d)
}
patch_ssl_log() {
  syslog_ng_conf="${IMAGE_ROOTFS}/${sysconfdir}/syslog-ng/syslog-ng.conf"
  sed -i '/f_sslendpoint/d' ${syslog_ng_conf}
}

