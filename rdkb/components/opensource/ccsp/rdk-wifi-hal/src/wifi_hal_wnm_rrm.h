/*
 * IEEE 802.11v WNM related functions and structures
 * hostapd / Radio Measurement (RRM)
 * Copyright (c) 2011-2014, Qualcomm Atheros, Inc.
 * Copyright(c) 2013 - 2016 Intel Mobile Communications GmbH.
 * Copyright(c) 2011 - 2016 Intel Corporation. All rights reserved.
 *
 * This software may be distributed under the terms of the BSD license.
 * See README_hostapd for more details.
 */


#ifndef WIFI_HAL_WNM_RRM_H
#define WIFI_HAL_WNM_RRM_H

#ifdef __cplusplus
extern "C" {
#endif

/* Try to detect hostap BTM patch */
#if defined(MBO_IE_HEADER)
#define CONFIG_USE_HOSTAP_BTM_PATCH
#endif

struct sta_info;
struct wifi_interface_info_t;

/* WNM action handler */
int handle_wnm_action_frame(struct wifi_interface_info_t *interface,
    const mac_address_t sta, struct ieee80211_mgmt *mgmt, size_t len);

int handle_rrm_action_frame(struct wifi_interface_info_t *interface,
    const mac_address_t sta, const struct ieee80211_mgmt *mgmt, size_t len, int ssi_signal);

int wifi_rrm_send_beacon_req(struct wifi_interface_info_t *interface, const u8 *addr,
    u16 num_of_repetitions, u8 measurement_request_mode,
    u8 oper_class, u8 channel, u16 random_interval,
    u16 measurement_duration, u8 mode, const u8* bssid,
    struct wpa_ssid_value* ssid, u8* rep_cond, u8* rep_cond_threshold,
    u8* rep_detail, const u8* ap_ch_rep, unsigned int ap_ch_rep_len,
    const u8* req_elem, unsigned int req_elem_len, u8 *ch_width,
    u8 *ch_center_freq0, u8 *ch_center_freq1, u8 last_indication);

/* called by BTM API */
int wifi_wnm_send_bss_tm_req(struct wifi_interface_info_t *interface, struct sta_info *sta,
    u8 dialog_token, u8 req_mode, int disassoc_timer, u8 valid_int,
    const u8 *bss_term_dur, const char *url,
    const u8 *nei_rep, size_t nei_rep_len,
    const u8 *mbo_attrs, size_t mbo_len);

#ifdef __cplusplus
}
#endif

#endif /* WIFI_HAL_WNM_RRM_H */
