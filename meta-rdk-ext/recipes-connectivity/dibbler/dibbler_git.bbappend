FILESEXTRAPATHS_prepend := "${THISDIR}/${BPN}:"

CXXFLAGS_append = " -Os "

SRC_URI_append = "${@bb.utils.contains('DISTRO_FEATURES', 'kirkstone', '', ' \
                   file://DELIA-34037-Dibbler-client-crash-in-delete_radvd_conf.patch \
                   file://RDKB-Fix-BindReuse-Bug.patch \
	           file://0002-port-dibbler-patches-from-1.0.0_RC2-for-dunfell.patch \
                 ', d)}"

SRC_URI_append_kirkstone = " file://DELIA-34037-Dibbler-client-crash-in-delete_radvd_conf_kirkstone.patch \
	                     file://0002-port-dibbler-patches-from-1.0.0_RC2-for-kirkstone.patch \
                           "

SRC_URI_append_hybrid = " file://0004-update_logging_path_hybrid_1_0_1_for_dunfell.patch "
SRC_URI_append_client = " file://0001-RDK-32168-Set-default-log-path-for-dibbler-client.patch "

SRC_URI_append_broadband = "${@bb.utils.contains('DISTRO_FEATURES', 'kirkstone', '', ' \
                              file://dhcpv6c_handle_system_time_change.patch \
			      file://Fix-For-Dibbler-Crash-InNobinding-Rebinding-Solicit-Transition.patch', d)}"

SRC_URI_append_broadband_kirkstone = " file://dhcpv6c_handle_system_time_change_kirkstone.patch \
				       file://Fix-For-Dibbler-Crash-InNobinding-Rebinding-Solicit-Transition_kirkstone.patch \
				       file://rfc3315-fix-unicast-request-and-client-IANA-options.patch"

#SRC_URI_append_broadband = " file://Fix-Dibbler-IPv6-Resolve-Conf-Expiry-Event-Alignment.patch"
SRC_URI_append_kirkstone = " file://0001-TOptIAPrefix-args-in-TClntOptIA_PD-constructor_kirk.patch"
SRC_URI_append_kirkstone = " file://0001-fix-misguided-and-broken-usage-of-clock_gettime-CLOC.patch"
