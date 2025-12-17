FILESEXTRAPATHS_prepend := "${THISDIR}/${BPN}:"

SRC_URI_append = " file://logrotate_daemon_3_21_0.patch \
                   file://logrotate-update-service-files.patch \
                 "
