FILESEXTRAPATHS_prepend := "${THISDIR}/${PN}:"

SRC_URI_remove = " \
			file://dnsmasq-2.81-XDNS-secondary-XDNS-feature-zombie-fix.patch \
			file://dnsmasq-2.81-XDNS-log-protect-browsing-MultiProfile.patch \
		"

SRC_URI_append = " \
			file://dnsmasq-2.81-Updated-XDNS-secondary-XDNS-feature-zombie-fix.patch \
			file://dnsmasq-2.81-Updated-XDNS-log-protect-browsing-MultiProfile.patch  \
"
