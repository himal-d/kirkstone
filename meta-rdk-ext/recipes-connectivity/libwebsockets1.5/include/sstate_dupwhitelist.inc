#This file will be included for yocto versions morty and daisy
SSTATE_DUPWHITELIST += "${STAGING_DIR}/${MACHINE}/pkgdata/runtime-reverse/libwebsockets-dev ${STAGING_DIR}/${MACHINE}/pkgdata/runtime-reverse/libwebsockets-dbg ${STAGING_LIBDIR}/libwebsockets.so ${STAGING_LIBDIR}/pkgconfig/libwebsockets.pc"
