DESCRIPTION = "rtRemote"

LICENSE = "Apache-2.0"
LIC_FILES_CHKSUM = "file://LICENSE;md5=cfbe95dd83ee8f2ea75475ecc20723e5"

DEPENDS = " util-linux rt-headers "

PV = "2.x+git${SRCPV}"

S = "${WORKDIR}/git"

SRC_URI = "git://github.com/rdkcentral/rtRemote;branch=release;protocol=https"
SRCREV = "7e29a873d9e1a9b0102a71d812ff40a31bac10e0"

inherit cmake

FILESEXTRAPATHS_prepend := "${THISDIR}/files:"

SRC_URI += "file://rtremote.conf "

ARCHFLAGS_append_arm = "${@bb.utils.contains('TUNE_FEATURES', 'callconvention-hard', '--with-arm-float-abi=hard', '--with-arm-float-abi=softfp', d)}"
ARCHFLAGS_append_mipsel = " --with-mips-arch-variant=r1"
ARCHFLAGS ?= ""
SELECTED_OPTIMIZATION_remove = "-O1"
SELECTED_OPTIMIZATION_remove = "-O2"
SELECTED_OPTIMIZATION_remove = "-Os"
SELECTED_OPTIMIZATION_append = " -O3"
SELECTED_OPTIMIZATION_append = " -Wno-deprecated-declarations -Wno-maybe-uninitialized -Wno-address"

TARGET_CFLAGS += " -fno-delete-null-pointer-checks "
TARGET_CXXFLAGS += " -fno-delete-null-pointer-checks "
TARGET_CXXFLAGS += " -Wl,--warn-unresolved-symbols "

EXTRA_OECMAKE_append_kirkstone = " -DRTREMOTE_GENERATOR_EXPORT=${WORKDIR}/build/rtRemoteConfigGen_export.cmake "
EXTRA_OECMAKE_append_dunfell = " -DRTREMOTE_GENERATOR_EXPORT=${S}/temp/rtRemoteConfigGen_export.cmake "
EXTRA_OECMAKE_append_morty = " -DRTREMOTE_GENERATOR_EXPORT=${S}/temp/rtRemoteConfigGen_export.cmake "
EXTRA_OECMAKE += " -DRT_INCLUDE_DIR=${STAGING_INCDIR}/pxcore "

do_configure_prepend_morty() {
    if [ ! -d ${S}/temp ]; then
        mkdir ${S}/temp
    fi
    cd ${S}/temp

    cmake -DCMAKE_CROSSCOMPILING=OFF -URTREMOTE_GENERATOR_EXPORT -DCMAKE_C_FLAGS=${BUILD_CFLAGS} -DCMAKE_C_COMPILER=${BUILD_CC} -DCMAKE_CXX_COMPILER=${BUILD_CXX} -DCMAKE_CXX_FLAGS=${BUILD_CXX_FLAGS} ..
    cmake --build . --target rtRemoteConfigGen
    rm -rf ${S}/temp/CMakeCache.txt
    rm -rf ${S}/temp/Makefile
    rm -rf ${S}/temp/cmake_install.cmake
    rm -rf ${S}/temp/CMakeFiles 
    cd ..
}

do_configure_prepend_dunfell() {
    if [ ! -d ${S}/temp ]; then
        mkdir ${S}/temp
    fi
    cd ${S}/temp

    cmake -DCMAKE_CROSSCOMPILING=OFF -URTREMOTE_GENERATOR_EXPORT -DCMAKE_C_FLAGS=${BUILD_CFLAGS} -DCMAKE_C_COMPILER=${BUILD_CC} -DCMAKE_CXX_COMPILER=${BUILD_CXX} -DCMAKE_CXX_FLAGS=${BUILD_CXX_FLAGS} ..
    cmake --build . --target rtRemoteConfigGen
    rm -rf ${S}/temp/CMakeCache.txt
    rm -rf ${S}/temp/Makefile
    rm -rf ${S}/temp/cmake_install.cmake
    rm -rf ${S}/temp/CMakeFiles 
    cd ..
}

do_configure_prepend_kirkstone() {

    cd ${WORKDIR}/build
    cmake -DCMAKE_CROSSCOMPILING=OFF -URTREMOTE_GENERATOR_EXPORT -DCMAKE_C_FLAGS="${BUILD_CFLAGS}" -DCMAKE_C_COMPILER="${BUILD_CC}" -DCMAKE_CXX_COMPILER="${BUILD_CXX}" -DCMAKE_CXX_FLAGS="${BUILD_CXX_FLAGS}" -S ${S}  -B ${WORKDIR}/build ..
    cmake --build . --target rtRemoteConfigGen
    rm -rf CMakeCache.txt
    rm -rf Makefile
    rm -rf cmake_install.cmake
    rm -rf CMakeFiles 
}

do_install () {
   install -d ${D}/${libdir}
   cp -a ${S}/librtRemote* ${D}/${libdir}

   mkdir -p ${D}${includedir}/pxcore
   install -m 0644 ${S}/include/rtRemote.h ${D}${includedir}/pxcore/
   install -m 0644 ${S}/include/*.h ${D}${includedir}/

   cp -R ${S}/external/rapidjson/ ${D}${includedir}/pxcore/

   mkdir -p ${D}/etc
   install -m 0644 "${WORKDIR}/rtremote.conf" "${D}/etc/"
}

FILES_${PN} += "${libdir}/*.so"
FILES_SOLIBSDEV = ""
INSANE_SKIP_${PN} += "dev-so staticdev"
INSANE_SKIP_${PN}_append_morty = " ldflags"
DEBIAN_NOAUTONAME_${PN} = "1"

BBCLASSEXTEND = "native"

