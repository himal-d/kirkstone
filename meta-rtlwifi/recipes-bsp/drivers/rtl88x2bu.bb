SUMMARY = "RTL88X2BU kernel driver (wifi)"
DESCRIPTION = "RTL88X2BU kernel driver"
LICENSE = "GPLv2"
LIC_FILES_CHKSUM = "file://Kconfig;md5=e71d544fd90fb1393f4f62c4faea6384"

SRC_URI = "git://github.com/EntropicEffect/rtl8822bu.git;protocol=https"
SRCREV = "5cb6d6ecc539de2420ab38436cdaa686aab9cad7"

S = "${WORKDIR}/git"

PV = "1.0-git"

DEPENDS = "virtual/kernel"

inherit module

EXTRA_OEMAKE  = "ARCH=${ARCH}"
EXTRA_OEMAKE += "KSRC=${STAGING_KERNEL_BUILDDIR}"

do_compile () {
    unset LDFLAGS
    oe_runmake
}

do_install () {
    install -d ${D}/lib/modules/${KERNEL_VERSION}
    install -m 0755 ${B}/88x2bu.ko ${D}/lib/modules/${KERNEL_VERSION}/88x2bu.ko
}

