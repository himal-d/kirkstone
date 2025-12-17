DESCRIPTION = "Asterisk is an Open Source PBX and telephony toolkit."
HOMEPAGE = "http://www.asterisk.org/"
LICENSE = "GPLv2"
LIC_FILES_CHKSUM = "file://LICENSE;md5=3aa955c628d43053f8ba9569d173105a"

DEPENDS += "sqlite3 libedit util-linux libxml2 libxml2-native"
RDEPENDS_${PN} += "bash"

SRC_URI = "\
    http://downloads.asterisk.org/pub/telephony/asterisk/releases/asterisk-${PV}.tar.gz \
    file://0001-Use-pkgconfig-to-find-sdl.patch \
    file://0002-Use-pkgconfig-to-find-libxml2.patch \
"

SRC_URI[md5sum] = "cc64dc4aa7d687f06b478051b80ac04d"
SRC_URI[sha256sum] = "6266a2542ae50225fadf0a3eebb1d11e74b1d1d5cd767cd7b4ff4e65568e8f35"

S = "${WORKDIR}/asterisk-${PV}"

inherit autotools-brokensep pkgconfig

EXTRA_OECONF += " \
    --with-libedit=${STAGING_DIR_TARGET}/usr \
    --with-jansson-bundled \
    --with-pjproject-bundled \
    --disable-xmldoc \
    --without-srtp \
    --without-ssl \
    --without-asound \
    --without-execinfo \
    --without-bluetooth \
    --without-gtk2 \
    --without-isdnnet \
    --without-misdn \
    --without-nbs \
    --without-libxslt \
    --without-netsnmp \
    --without-newt \
    --without-osptk \
    --without-lua \
    --without-postgres \
    --without-popt \
    --without-portaudio \
    --without-radius \
    --without-spandsp \
    --without-sdl \
    --without-sqlite \
    --without-suppserv \
    --without-tds \
    --without-unbound \
    --without-vorbis \
    --without-imap \
    --without-uriparser \
    --without-vpb \
    --without-speex \
    --without-speexdsp \
    --without-ogg \
    --without-neon \
    --without-ical \
    --without-neon29 \
    --without-iksemel \
"

EXTRA_OEMAKE += " \
    ASTDATADIR=/usr/share/asterisk \
    ASTETCDIR=/var/asterisk \
"

MENUSELECT_OPTS=" \
    --without-newt \
    --without-curses \
"

MENUSELECT_DISABLED_CATEGORIES="\
    --disable-category MENUSELECT_ADDONS \
    --disable-category MENUSELECT_APPS \
    --disable-category MENUSELECT_BRIDGES \
    --disable-category MENUSELECT_CDR \
    --disable-category MENUSELECT_CEL \
    --disable-category MENUSELECT_CHANNELS \
    --disable-category MENUSELECT_CODECS \
    --disable-category MENUSELECT_FORMATS \
    --disable-category MENUSELECT_FUNCS \
    --disable-category MENUSELECT_PBX \
    --disable-category MENUSELECT_RES \
    --disable-category MENUSELECT_UTILS \
    --disable-category MENUSELECT_AGIS \
"

FEATURE_OPTS=" \
    --enable app_dial \
    --enable app_echo \
    --enable app_stack \
    --enable app_playback \
    --enable app_record \
    --enable app_confbridge \
    --enable app_playtones \
    --enable app_read \
    --enable app_system \
    --enable app_transfer \
    --enable app_voicemail \
    --enable app_cdr \
    --enable app_forkcdr \
    --enable func_callerid \
    --enable func_logic \
    --enable func_strings \
    --enable func_timeout \
    --enable func_channel \
    --enable func_db \
    --enable func_shell \
    --enable func_cdr \
    --enable res_timing_timerfd \
    --enable res_rtp_asterisk \
    --enable bridge_builtin_features \
    --enable bridge_simple \
    --enable bridge_softmix \
    --enable cdr_custom \
    --enable cdr_manager \
    --enable cdr_syslog \
    --enable cdr_csv \
    --enable codec_a_mu \
    --enable codec_alaw \
    --enable codec_g722 \
    --enable codec_g726 \
    --enable codec_gsm \
    --enable format_g726 \
    --enable format_gsm \
    --enable format_sln \
    --enable pbx_config \
    --enable pbx_spool \
    --enable chan_pjsip \
    --enable func_pjsip_aor \
    --enable func_pjsip_contact \
    --enable func_pjsip_endpoint \
    --enable res_pjsip \
    --enable res_pjsip_acl \
    --enable res_pjsip_authenticator_digest \
    --enable res_pjsip_caller_id \
    --enable res_pjsip_config_wizard \
    --enable res_pjsip_dialog_info_body_generator \
    --enable res_pjsip_diversion \
    --enable res_pjsip_dlg_options \
    --enable res_pjsip_dtmf_info \
    --enable res_pjsip_empty_info \
    --enable res_pjsip_endpoint_identifier_anonymous \
    --enable res_pjsip_endpoint_identifier_ip \
    --enable res_pjsip_endpoint_identifier_user \
    --enable res_pjsip_exten_state \
    --enable res_pjsip_header_funcs \
    --enable res_pjsip_history \
    --enable res_pjsip_logger \
    --enable res_pjsip_messaging \
    --enable res_pjsip_mwi \
    --enable res_pjsip_mwi_body_generator \
    --enable res_pjsip_nat \
    --enable res_pjsip_notify \
    --enable res_pjsip_one_touch_record_info \
    --enable res_pjsip_outbound_authenticator_digest \
    --enable res_pjsip_outbound_publish \
    --enable res_pjsip_outbound_registration \
    --enable res_pjsip_path \
    --enable res_pjsip_pidf_body_generator \
    --enable res_pjsip_pidf_digium_body_supplement \
    --enable res_pjsip_pidf_eyebeam_body_supplement \
    --enable res_pjsip_publish_asterisk \
    --enable res_pjsip_pubsub \
    --enable res_pjsip_refer \
    --enable res_pjsip_registrar \
    --enable res_pjsip_rfc3326 \
    --enable res_pjsip_sdp_rtp \
    --enable res_pjsip_send_to_voicemail \
    --enable res_pjsip_session \
    --enable res_pjsip_sips_contact \
    --enable res_pjsip_xpidf_body_generator \
    --enable CORE-SOUNDS-EN-GSM \
"

do_configure() {
    # Regenerate configure script after patch
    ./bootstrap.sh

    oe_runconf

    # configure menuselect
    cd ${B}/menuselect
    CC="${BUILD_CC}" \
    CFLAGS="${BUILD_CFLAGS}" \
    LD="${BUILD_LD}" \
    LDFLAGS="${BUILD_LDFLAGS}" \
    CONFIG_SITE= \
    ./configure ${MENUSELECT_OPTS} \
    --build=${BUILD_SYS} \
    --host=${BUILD_SYS} \
    --target=${BUILD_SYS} \
    --with-libtool-sysroot=${STAGING_DIR_HOST}

    # Fix path to libxml2
    ln -s ${STAGING_INCDIR_NATIVE}/libxml2/libxml ${STAGING_INCDIR_NATIVE}/libxml
}

do_compile_prepend() {
    oe_runmake \
        CC="${BUILD_CC}" \
        CFLAGS="${BUILD_CFLAGS}" \
        LD=${BUILD_LD} \
        LDFLAGS="${BUILD_LDFLAGS}" \
        -C "${B}/menuselect"

    oe_runmake \
        CC="${BUILD_CC}" \
        CFLAGS="${BUILD_CFLAGS}" \
        LD=${BUILD_LD} \
        LDFLAGS="${BUILD_LDFLAGS}" \
       menuselect-tree

    ./menuselect/menuselect \
        ${MENUSELECT_DISABLED_CATEGORIES} \
        --disable BUILD_NATIVE \
        menuselect.makeopts

    ./menuselect/menuselect ${FEATURE_OPTS} menuselect.makeopts
}

do_install_append() {
    # /run provided by base-files
    rm -rf ${D}${localstatedir}/run

    # remove /tmp to avoid not shipped directory warning
    rm -rf ${D}/tmp
}

FILES_${PN} += " \
    ${bindir} \
    ${libdir} \
    ${localstatedir} \
    ${sysconfdir} \
    ${sysconfdir}/asterisk \
    ${datadir}/asterisk/sounds \
"

