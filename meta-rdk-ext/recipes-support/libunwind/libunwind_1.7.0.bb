FILESEXTRAPATHS_prepend := "${THISDIR}/libunwind:"
require libunwind_1.7.0.inc

SRC_URI = "git://github.com/libunwind/libunwind.git;protocol=https;branch=master \
          "
SRCREV = "26b0cfc407f2bf89f8a3a9770bd1d73ad2cc3306"


SRC_URI += "${@bb.utils.contains('DISTRO_FEATURES', 'enable_heaptrack','file://core.patch','',d)}"
S = "${WORKDIR}/git"

#SRC_URI[sha256sum] = "4a6aec666991fb45d0889c44aede8ad6eb108071c3554fcdff671f9c94794976"
PROVIDES = "${MLPREFIX}${PN}"

#inherit cmake
#EXTRA_OECONF:append:libc-musl = " --disable-documentation --disable-tests --enable-static"
EXTRA_OECONF += "--enable-debug"
# http://errors.yoctoproject.org/Errors/Details/20487/
ARM_INSTRUCTION_SET_armv4 = "arm"
ARM_INSTRUCTION_SET_armv5 = "arm"

COMPATIBLE_HOST_riscv32 = "null"
LDFLAGS += "-Wl,-z,relro,-z,now ${@bb.utils.contains('DISTRO_FEATURES', 'ld-is-gold', ' -fuse-ld=bfd ', '', d)}"

SECURITY_LDFLAGS_append_libc-musl = " -lssp_nonshared"
CACHED_CONFIGUREVARS_append_libc-musl = " LDFLAGS='${LDFLAGS} -lucontext'"
