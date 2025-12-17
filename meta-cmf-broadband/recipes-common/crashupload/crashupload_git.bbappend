FILESEXTRAPATHS_prepend := "${THISDIR}/files:"
SRC_URI += "file://crash_upload.patch;apply=no"

do_crashupload_patches () {
    cd ${S}
    if [ ! -e patch_applied ]; then
       patch -p1 < ${WORKDIR}/crash_upload.patch
       touch patch_applied
    fi
}
addtask crashupload_patches after do_unpack before do_configure

do_install_append () {
        install -d ${D}${base_libdir}/rdk
        install -m 0755 ${S}/uploadDumpsUtilsBroadband.sh ${D}${base_libdir}/rdk/uploadDumpsUtils.sh

        sed -i -e "\$aType=oneshot\n\n[Install]\nWantedBy=multi-user.target\n" ${D}${systemd_unitdir}/system/coredump-upload.service
        sed -i -e '/Path Exists.*/aAfter=network-online.target\nRequires=network-online.target' ${D}${systemd_unitdir}/system/coredump-upload.path
        sed -i -e '/PathChanged=.*/aUnit=coredump-upload.service'  ${D}${systemd_unitdir}/system/coredump-upload.path
}


FILES_${PN} += " \
                ${base_libdir}/rdk/* \
               "
