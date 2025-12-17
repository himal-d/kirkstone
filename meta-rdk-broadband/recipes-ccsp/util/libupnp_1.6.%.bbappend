
DESCRIPTION = "The portable SDK for UPnP* Devices (libupnp) provides developers with an API and open source code for building control points, devices, and bridges that are compliant with Version 1.0 of the Universal Plug and Play Device Architecture Specification."

HOMEPAGE = "http://pupnp.sourceforge.net/"

FILESEXTRAPATHS_prepend := "${THISDIR}/${PN}:" 

SRC_URI += "\
    file://01-ltmain.sh_${PV}.patch \
    file://02-wecb_${PV}.patch \
    file://ixml_header01.patch \
    "
