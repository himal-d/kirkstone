FILESEXTRAPATHS_prepend := "${THISDIR}/files:"

SRC_URI_append = " \
           file://0001-Fix-passing-NULL-to-g_task_get_cancellable.patch \
           file://CVE-2023-32665_2.72.3_fix.patch \
           "
