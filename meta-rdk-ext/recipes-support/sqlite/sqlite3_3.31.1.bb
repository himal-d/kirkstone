require sqlite3_3.31.1.inc

LICENSE = "PD"
LIC_FILES_CHKSUM = "file://sqlite3.h;endline=11;md5=786d3dc581eff03f4fd9e4a77ed00c66"

SRC_URI = "http://www.sqlite.org/2020/sqlite-autoconf-${SQLITE_PV}.tar.gz \
           file://CVE-2020-9327.patch \
           file://CVE-2020-11656.patch \
           file://CVE-2020-11655.patch \
           file://CVE-2020-15358.patch \
           file://CVE-2020-13434.patch \
           file://CVE-2020-13435.patch \
           file://CVE-2020-13630.patch \
           file://CVE-2020-13631.patch \
           file://CVE-2020-13632.patch \
           "
SRC_URI[md5sum] = "2d0a553534c521504e3ac3ad3b90f125"
SRC_URI[sha256sum] = "62284efebc05a76f909c580ffa5c008a7d22a1287285d68b7825a2b6b51949ae"


require ${@bb.utils.contains_any('DISTRO_FEATURES','morty daisy','cve_check_whitelist.inc','cve_check_ignore.inc',d)}
