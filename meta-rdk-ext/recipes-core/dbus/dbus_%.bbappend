FILESEXTRAPATHS_prepend := "${THISDIR}/dbus:"

SRC_URI_append = " \
    file://dbus_rdk_system_configuration.patch \
    file://sky-add-option-to-disable-uid-in-auth.patch \
"

SRC_URI_append_broadband = " \
    file://01-dbus-ccsp-apis-${PV}.patch \
"

# Prevent a circular dependency between systemd and dbus when combining dbus
# 1.10.6 (ie the version of dbus in OE 2.1) with systemd 216 (ie the meta-rdk
# version of systemd, used by the RDK for both OE 1.6 and OE 2.1).
PACKAGECONFIG_remove_krogoth = "systemd"

#Removed --with-xml expact as the configuration is not supported in 1.14. It was not supported in dunfell version 1.12.16 as well.
EXTRA_OECONF_broadband = "--disable-tests \
                          --disable-xml-docs \
                          --disable-doxygen-docs \
                          --disable-libaudit \
                          --disable-checks \
                          --disable-systemd"

do_install_append() {
         # Remove <includedir>system.d</includedir> from system.conf since it consumes much CPU cycles for dbus-daemon
         sed -i '/system.d/d' ${D}${sysconfdir}/dbus-1/system.conf
}

SRC_URI_append = "file://CVE-2022-42010_fix.patch \
                  file://CVE-2022-42012_fix.patch \
                  file://CVE-2022-42011_fix.patch \
                  file://CVE-2023-34969_fix.patch \
                 "
