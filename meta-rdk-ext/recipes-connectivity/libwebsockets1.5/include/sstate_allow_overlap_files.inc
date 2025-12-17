#This file will be included for yocto versions dunfell and higher
SSTATE_ALLOW_OVERLAP_FILES += "${STAGING_DIR}/${MACHINE}/pkgdata/runtime-reverse/libwebsockets-dev ${STAGING_DIR}/${MACHINE}/pkgdata/runtime-reverse/libwebsockets-dbg ${STAGING_LIBDIR}/libwebsockets.so ${STAGING_LIBDIR}/pkgconfig/libwebsockets.pc"
