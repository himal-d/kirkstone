FILESEXTRAPATHS_prepend := "${THISDIR}/files:"

SRC_URI_remove = "git://github.com/Comcast/nopoll.git;branch=nopoll_yocto"
SRC_URI += "git://github.com/Comcast/nopoll.git;protocol=https;branch=nopoll_yocto"

SRC_URI += "file://0001_nopoll_conn_new6_opts.patch"
SRC_URI += "file://0002_nopoll_conn_new_common_logs.patch"
SRC_URI += "file://0003_nopoll_transport_auto.patch"
SRC_URI += "file://0004_memory-leak-fix.patch"
