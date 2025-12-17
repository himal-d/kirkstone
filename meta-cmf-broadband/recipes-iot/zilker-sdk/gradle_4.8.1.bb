SUMMARY = "Gradle is a build automation tool for multi-language software development"
HOMEPAGE = "https://services.gradle.org/distributions/"

LICENSE = "Apache-2.0"
LIC_FILES_CHKSUM = "file://LICENSE;md5=2dc9d26236dd5d32f892d3e36cc4a554"

SRC_URI += "https://services.gradle.org/distributions/gradle-4.8.1-bin.zip;name=gradle"
SRC_URI[gradle.md5sum] = "90db63b9cd864a6e6bc8d0c5e72ca5a2"
SRC_URI[gradle.sha256sum] = "af334d994b5e69e439ab55b5d2b7d086da5ea6763d78054f49f147b06370ed71" 


S = "${WORKDIR}/gradle-${PV}"

do_install() {
      install -m 0755 -d  ${D}${bindir}
      install -m 0755 -d  ${D}${libdir}
      cp ${S}/bin/* ${D}${bindir}	
      cp -r  ${S}/lib/* ${D}${libdir}	
}

BBCLASSEXTEND = "native nativesdk"
