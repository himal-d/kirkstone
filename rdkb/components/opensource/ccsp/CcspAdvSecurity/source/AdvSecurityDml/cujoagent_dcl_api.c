#include "cujoagent_dcl_api.h"

/* Gets called internally by webconfig_set() */
static webconfig_error_t
cujoagent_webconfig_apply(__attribute__((unused)) webconfig_subdoc_t *doc,
                          __attribute__((unused)) webconfig_subdoc_data_t *data) {
  return webconfig_error_none;
}

static int cujoagent_consumer_init(cujoagent_wifi_consumer_t *consumer) {
  char *msg = NULL;
  memset(consumer, 0, sizeof(cujoagent_wifi_consumer_t));

  pthread_mutex_init(&consumer->lock, NULL);
  pthread_cond_init(&consumer->cond, NULL);

  consumer->queue = queue_create();
  if (consumer->queue == NULL) {
    msg = "Failed to allocate a consumer queue";
    goto err;
  }
  consumer->queue_wakeup = false;

  consumer->assoc_disassoc_events = queue_create();
  if (consumer->assoc_disassoc_events == NULL) {
    msg = "Failed to allocate a station events queue";
    goto err;
  }

  consumer->webconfig.initializer = webconfig_initializer_dml;
  consumer->webconfig.apply_data = &cujoagent_webconfig_apply;
  if (webconfig_init(&consumer->webconfig) != 0) {
    msg = "Failed to initialize webconfig framework";
    goto err;
  }

  consumer->epfd_m = epoll_create1(EPOLL_CLOEXEC);
  if (consumer->epfd_m == -1) {
    msg = "Failed to create an epoll instance";
    goto err;
  }

  consumer->efd_m = eventfd(0, EFD_CLOEXEC | EFD_NONBLOCK);
  if (consumer->efd_m == -1) {
    msg = "Failed to create eventfd";
    goto err;
  }

  consumer->epfd_c = epoll_create1(EPOLL_CLOEXEC);
  if (consumer->epfd_c == -1) {
    msg = "Failed to create an epoll instance";
    goto err;
  }

  consumer->efd_c = eventfd(0, EFD_CLOEXEC | EFD_NONBLOCK);
  if (consumer->efd_c == -1) {
    msg = "Failed to create eventfd";
    goto err;
  }

  consumer->epfd_s = epoll_create1(EPOLL_CLOEXEC);
  if (consumer->epfd_s == -1) {
    msg = "Failed to create an epoll instance";
    goto err;
  }

  consumer->efd_s = eventfd(0, EFD_CLOEXEC | EFD_NONBLOCK);
  if (consumer->efd_s == -1) {
    msg = "Failed to create eventfd";
    goto err;
  }

  /* CID 339091: Data race condition */
  pthread_mutex_lock(&consumer->lock);
  consumer->comms_ready = false;
  consumer->exit_consumer = false;
  pthread_mutex_unlock(&consumer->lock);
  return 0;

err:
  CcspTraceError(("%s\n", msg));
  return -1;
}

static void cujoagent_consumer_deinit(cujoagent_wifi_consumer_t *consumer) {
  pthread_mutex_destroy(&consumer->lock);
  pthread_cond_destroy(&consumer->cond);

  if (consumer->queue) {
    queue_destroy(consumer->queue);
  }

  if (consumer->assoc_disassoc_events) {
    queue_destroy(consumer->assoc_disassoc_events);
  }

  if (consumer->rbus_handle) {
    rbus_close(consumer->rbus_handle);
  }

  for (int i = 0; i < (int)consumer->subscriptions_count; i++) {
    if (consumer->subscriptions[i].eventName) {
      free((char *)consumer->subscriptions[i].eventName);
    }
  }

  if (consumer->subscriptions) {
    free(consumer->subscriptions);
  }

  if (consumer->epfd_m >= 0) {
    close(consumer->epfd_m);
  }

  if (consumer->efd_m >= 0) {
    close(consumer->efd_m);
  }

  if (consumer->epfd_c >= 0) {
    close(consumer->epfd_c);
  }

  if (consumer->efd_c >= 0) {
    close(consumer->efd_c);
  }

  if (consumer->epfd_s >= 0) {
    close(consumer->epfd_s);
  }

  if (consumer->efd_s >= 0) {
    close(consumer->efd_s);
  }
}

static void cujoagent_update_consumer_wifi_structs(
    cujoagent_wifi_consumer_t *consumer,
    webconfig_subdoc_decoded_data_t *decoded_params) {
  if (!consumer || !decoded_params) {
    CcspTraceError(("Consumer or decoded params invalid\n"));
    return;
  }

  CcspTraceDebug(("Updating consumer config, hal_cap, radio structs\n"));
  consumer->hal_cap.wifi_prop.numRadios = decoded_params->num_radios;
  memcpy(&consumer->config, &decoded_params->config,
         sizeof(wifi_global_config_t));
  memcpy(&consumer->hal_cap, &decoded_params->hal_cap,
         sizeof(wifi_hal_capability_t));
  memcpy(&consumer->radios, &decoded_params->radios,
         decoded_params->num_radios * sizeof(rdk_wifi_radio_t));
}

static void cujoagent_update_decoded_wifi_structs(
    cujoagent_wifi_consumer_t *consumer,
    webconfig_subdoc_decoded_data_t *decoded_params) {
  if (!consumer || !decoded_params) {
    CcspTraceError(("Consumer or decoded params invalid\n"));
    return;
  }

  CcspTraceDebug(("Updating decoded config, hal_cap, radio structs\n"));
  decoded_params->num_radios = consumer->hal_cap.wifi_prop.numRadios;
  memcpy(&decoded_params->config, &consumer->config,
         sizeof(wifi_global_config_t));
  memcpy(&decoded_params->hal_cap, &consumer->hal_cap,
         sizeof(wifi_hal_capability_t));
  memcpy(&decoded_params->radios, &consumer->radios,
         decoded_params->num_radios * sizeof(rdk_wifi_radio_t));
}

static int cujoagent_socket_init(cujoagent_wifi_consumer_t *consumer) {
  char *msg = NULL;
  char *dir = NULL;
  char *dir_name = NULL;
  struct sockaddr_un saddr = {.sun_family = AF_UNIX};
  size_t size = sizeof(saddr.sun_path);
  int count = snprintf(saddr.sun_path, size, "%s", CCSP_CUJOAGENT_SOCK_PATH);;
  int cmd = 0;

  consumer->sock_fd = -1;
  // Allocate memory and check for allocation errors
  dir_name = strdup(CCSP_CUJOAGENT_SOCK_PATH);
  if (dir_name == NULL) {
    msg = "strdup failed";
    return -1;
  }

  dir = dirname(dir_name);

  cmd = v_secure_system("mkdir -p %s", dir);

  if (dir_name != NULL) {
    free(dir_name);
    dir_name = NULL;
  }

  if (cmd != 0) {
    msg = "Failed to create parent directory for the socket path";
    goto err;
  }

  consumer->sock_fd = socket(AF_UNIX, SOCK_DGRAM, 0);
  if (consumer->sock_fd == -1) {
    msg = "Failed to open unix socket";
    goto err;
  }

  if (remove(CCSP_CUJOAGENT_SOCK_PATH) == -1 && errno != ENOENT) {
    msg = "Failed to remove socket filepath";
    goto err;
  }

  if (count < 0 || count >= (int)size) {
    msg = "Socket filepath doesn't fit into buffer";
    goto err;
  }

  if (bind(consumer->sock_fd, (struct sockaddr *)&saddr,
           sizeof(struct sockaddr_un)) == -1) {
    msg = "Failed to bind to the socket";
    goto err;
  }

  return 0;

err:
  CcspTraceError(("%s\n", msg));
  if (consumer->sock_fd >= 0) {
    close(consumer->sock_fd);
    consumer->sock_fd = -1;
  }
  return -1;
}

static int cujoagent_write_event(int eventfd, cujoagent_notify_t notify) {
  size_t su = sizeof(uint64_t);
  uint64_t u = notify;
  if (write(eventfd, &u, su) != (ssize_t)su) {
    CcspTraceError(("Failed to write eventfd value [%" PRIu64 "]\n", u));
    return -1;
  }
  return 0;
}

static int cujoagent_wait_for_event(int epoll_fd, cujoagent_notify_t notify,
                                    int timeout_ms) {
  struct epoll_event events[MAX_EPOLL_EVENTS] = {0};
  int nfds = -1;
  int efd = -1;
  uint32_t event = 0;
  uint64_t u = NOTIFY_NONE;

  nfds = epoll_wait(epoll_fd, events, MAX_EPOLL_EVENTS, timeout_ms);
  for (int i = 0; i < nfds; i++) {
    efd = events[i].data.fd;
    event = events[i].events;

    CcspTraceDebug(("Epoll event: epoll fd [%d], nfds [%d], event fd [%d], "
                    "event [0x%08" PRIx32 "], expect notify [%d]\n",
                    epoll_fd, nfds, efd, event, notify));

    if (!(event & EPOLLIN)) {
      CcspTraceError(("Event [0x%08" PRIx32 "] has bit [0x%08" PRIx32
                      "] not set\n",
                      event, EPOLLIN));
      return -1;
    }

    /* CID 339096: Ignoring number of bytes read */
    int bytes_read = read(efd, &u, sizeof(u));
    if (bytes_read < 0)
    {
      CcspTraceError(("Failed to read eventfd [%d]\n", efd));
      return -1;
    }

    if (u != notify) {
      CcspTraceError(("Eventfd notification mismatch: "
                      "[%" PRIu64 "] != [%d]\n",
                      u, notify));
      return -1;
    }
  }

  return nfds;
}

static int cujoagent_tlv_handshake(cujoagent_wifi_consumer_t *consumer,
                                   struct sockaddr_un *paddr,
                                   socklen_t *addr_len, char *buf) {
  ssize_t mlen = 0;
  struct cujo_fpc_tlv hello_tlv = {0};

  for (;;) {
    CcspTraceInfo(("Waiting for the agent \"hello\"\n"));
    mlen = recvfrom(consumer->sock_fd, buf, MAX_SOCK_RECV_BUFFER, 0,
                    (struct sockaddr *)paddr, addr_len);
    if (mlen == -1) {
      CcspTraceError(("Reading from peer failed\n"));
      return -1;
    }

    memcpy(&hello_tlv, buf, sizeof(hello_tlv));
    if (hello_tlv.tag != CUJO_FPC_HELLO) {
      CcspTraceWarning(("Not a \"hello\" tlv: tag [%u], len [%u], mlen [%zd]\n",
                        hello_tlv.tag, hello_tlv.len, mlen));
      continue;
    }
    CcspTraceInfo(("Received the agent \"hello\"\n"));
    break;
  }

  struct cujo_fpc_proto_version ver = {.major = 1, .minor = 0};
  size_t ver_size = sizeof ver;

  size_t ver_tlv_size = sizeof(struct cujo_fpc_tlv) + ver_size;
  struct cujo_fpc_tlv *ver_tlv = calloc(1, ver_tlv_size);
  if (!ver_tlv) {
    CcspTraceError(("Failed to allocate a \"version\" tlv\n"));
    return -1;
  }

  ver_tlv->tag = CUJO_FPC_PROTOCOL_VERSION;
  ver_tlv->len = ver_size;
  memcpy(ver_tlv->data, &ver, ver_size);

  CcspTraceInfo(("Sending \"version\" tlv: tag [%u], len [%u], size [%zu]\n",
                 ver_tlv->tag, ver_tlv->len, ver_tlv_size));
  mlen = sendto(consumer->sock_fd, ver_tlv, ver_tlv_size, 0,
                (struct sockaddr *)paddr, *addr_len);
  free(ver_tlv);

  if (mlen == -1) {
    CcspTraceError(("Sending \"version\" tlv failed\n"));
    return -1;
  }

  return 0;
}

static void *cujoagent_socket_loop(void *arg) {
  cujoagent_wifi_consumer_t *consumer = arg;
  char *msg = NULL;
  char buf[MAX_SOCK_RECV_BUFFER] = {0};
  struct sockaddr_un paddr = {0};
  socklen_t addr_len = sizeof(struct sockaddr_un);
  struct epoll_event ev;
  struct epoll_event events[MAX_EPOLL_EVENTS] = {0};
  int nfds = 0;
  int efd = 0;
  uint32_t event = 0;
  uint64_t u = NOTIFY_NONE;
  cujoagent_notify_t notify = NOTIFY_NONE;

  if (cujoagent_socket_init(consumer) != 0) {
    msg = "Failed to initialize a socket";
    goto err;
  }

  /* Blocking call, get a hello first and only then proceed further */
  if (cujoagent_tlv_handshake(consumer, &paddr, &addr_len, buf) != 0) {
    msg = "\"hello<->version\" handshake failed";
    goto err;
  }

  ev.events = EPOLLIN;
  ev.data.fd = consumer->sock_fd;
  if (epoll_ctl(consumer->epfd_s, EPOLL_CTL_ADD, consumer->sock_fd, &ev)) {
    msg = "Failed to add a socket fd to epoll interest list";
    goto err;
  }

  /* Socket loop epoll listen for consumer loop eventfd */
  ev.events = EPOLLIN | EPOLLET;
  ev.data.fd = consumer->efd_c;
  if (epoll_ctl(consumer->epfd_s, EPOLL_CTL_ADD, consumer->efd_c, &ev)) {
    msg = "Failed to add the consumer loop evenfd to an epoll interest list";
    goto err;
  }

  /* Consumer loop epoll listen for socket loop evenfd */
  ev.events = EPOLLIN | EPOLLET;
  ev.data.fd = consumer->efd_s;
  if (epoll_ctl(consumer->epfd_c, EPOLL_CTL_ADD, consumer->efd_s, &ev)) {
    msg = "Failed to add the socket loop evenfd to an epoll interest list";
    goto err;
  }

  pthread_mutex_lock(&consumer->lock);
  consumer->comms_ready = true;
  pthread_mutex_unlock(&consumer->lock);

  for (;;) {
    /* Block until event, timeout -1 */
    nfds = epoll_wait(consumer->epfd_s, events, MAX_EPOLL_EVENTS, -1);
    for (int i = 0; i < nfds; i++) {
      efd = events[i].data.fd;
      event = events[i].events;

      CcspTraceDebug(("Epoll event: epoll fd [%d], nfds [%d], event fd [%d], "
                      "event [0x%08" PRIx32 "]\n",
                      consumer->epfd_s, nfds, efd, event));

      if (!(event & EPOLLIN)) {
        continue;
      }

      if (efd == consumer->efd_c) {
        if (read(efd, &u, sizeof(u)) == -1) {
          CcspTraceError(("Failed to read eventfd [%d]\n", efd));
          continue;
        }

        switch (u) {
        case NOTIFY_RADIO_DATA_READY:
          notify = NOTIFY_RADIO_DATA_SENT;
          break;
        case NOTIFY_STATION_DATA_READY:
          notify = NOTIFY_STATION_DATA_SENT;
          break;
        case NOTIFY_BATCH_DATA_READY:
          notify = NOTIFY_BATCH_DATA_SENT;
          break;
        case NOTIFY_SOCKET_THREAD_STOP:
          notify = NOTIFY_SOCKET_THREAD_RETURN;
          break;
        default:
          notify = NOTIFY_NONE;
          break;
        }
        CcspTraceDebug(("Eventfd notification: "
                        "notify received [%" PRIu64
                        "], notify to be sent [%d]\n",
                        u, notify));

        if (notify == NOTIFY_NONE) {
          CcspTraceError(("Unsupported eventfd notification: "
                          "notify received [%" PRIu64
                          "], notify to be sent [%d]\n",
                          u, notify));
          continue;
        }

        if (notify == NOTIFY_SOCKET_THREAD_RETURN) {
          cujoagent_write_event(consumer->efd_s, notify);
          goto out;
        }

        /* It would not be a great idea to access the freed memory, so make
         * sure we see it in the logs if that race is ever going to happen. */
        if (!consumer->tlv_ctx.tlv) {
          CcspTraceWarning(("Invalid wifi tlv: [%p], notify received [%" PRIu64
                            "], notify to be sent [%d]\n",
                            (void *)consumer->tlv_ctx.tlv, u, notify));
          continue;
        }

        /* The agent handles the following types of mishaps just fine, but
         * let's make it clear that it happened at where the data is gathered,
         * rather than blindly sending an invalid tlv and hoping that the agent
         * will take care of it. */
        if (consumer->tlv_ctx.size !=
            (consumer->tlv_ctx.tlv->len + sizeof(struct cujo_fpc_tlv))) {
          CcspTraceError(
              ("Invalid wifi tlv data: tag [%u], len [%u], size "
               "[%zu], notify received [%" PRIu64 "], notify to be sent [%d]\n",
               consumer->tlv_ctx.tlv->tag, consumer->tlv_ctx.tlv->len,
               consumer->tlv_ctx.size, u, notify));
          continue;
        }

        CcspTraceDebug(("Sending wifi tlv: tag [%u], len [%u], size [%zu]\n",
                        consumer->tlv_ctx.tlv->tag, consumer->tlv_ctx.tlv->len,
                        consumer->tlv_ctx.size));
        if (sendto(consumer->sock_fd, consumer->tlv_ctx.tlv,
                   consumer->tlv_ctx.size, 0, (const struct sockaddr *)&paddr,
                   addr_len) == -1) {
          CcspTraceError(("Sending wifi tlv failed. Is the agent running?\n"));
          continue;
        }
        cujoagent_write_event(consumer->efd_s, notify);
      } else if (efd == consumer->sock_fd) {
        addr_len = sizeof(struct sockaddr_un);
        if (cujoagent_tlv_handshake(consumer, &paddr, &addr_len, buf) != 0) {
          CcspTraceError(("\"hello<->version\" handshake failed\n"));
        }

        pthread_mutex_lock(&consumer->lock);
        consumer->comms_ready = true;
        pthread_mutex_unlock(&consumer->lock);
      }
    }
  }

err:
  CcspTraceError(("%s\n", msg));
  if (consumer->sock_fd >= 0) {
    close(consumer->sock_fd);
    consumer->sock_fd = -1;
  }
  if (consumer->efd_s >= 0) {
    close(consumer->efd_s);
    consumer->efd_s = -1;
  }
  if (consumer->epfd_s >= 0) {
    close(consumer->epfd_s);
    consumer->epfd_s = -1;
  }
  if (consumer->efd_c >= 0) {
    close(consumer->efd_c);
    consumer->efd_c = -1;
  }
  if (consumer->epfd_c >= 0) {
    close(consumer->epfd_c);
    consumer->epfd_c = -1;
  }
out:
  CcspTraceDebug(("Returning from socket loop thread routine\n"));
  return NULL;
}

static int cujoagent_spawn_socket_loop(cujoagent_wifi_consumer_t *consumer) {
  pthread_attr_t attr;
  pthread_attr_init(&attr);
  pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);
  pthread_t thr = 0;

  int err = pthread_create(&thr, &attr, &cujoagent_socket_loop, consumer);
  if (err) {
    CcspTraceError(("Failed to start a socket loop thread\n"));
    return err;
  }

  pthread_attr_destroy(&attr);
  return err;
}

static uint64_t cujoagent_timestamp(void) {
  struct timespec ts = {0};
  if (clock_gettime(CLOCK_REALTIME, &ts) != 0) {
    CcspTraceError(("Getting current time failed\n"));
    return -1;
  }

  return (uint64_t)ts.tv_sec * MSECS_PER_SEC +
         (uint64_t)ts.tv_nsec / NANOSECS_PER_MSEC;
}

static size_t cujoagent_copy_to(char *dst, size_t dst_len, char *src) {
  size_t src_len = strlen(src);
  if (src_len >= dst_len) {
    CcspTraceDebug(("Src buffer doesn't fit into dst buffer\n"));
  }

  size_t min_len = (src_len > dst_len - 1) ? dst_len - 1 : src_len;
  memset(dst, 0, dst_len);
  memcpy(dst, src, min_len);
  return min_len;
}

static wifi_interface_name_idex_map_t *
cujoagent_iface_property(wifi_platform_property_t *wifi_prop,
                         unsigned int vap_index) {
  /* We're copying the relevant structs from a (hopefully) successful
   * webconfig_decode(), so we assume that wifi_prop is valid and we don't need
   * to validate the actual values there. Therefore, just a basic check here.*/
  if (!wifi_prop) {
    CcspTraceError(("Wifi property is invalid\n"));
    return NULL;
  }

  wifi_interface_name_idex_map_t *iface_map = NULL;
  for (int i = 0; i < (int)wifi_prop->numRadios * MAX_NUM_VAP_PER_RADIO; i++) {
    if (wifi_prop->interface_map[i].index == vap_index) {
      iface_map = &wifi_prop->interface_map[i];
      break;
    }
  }

  return iface_map;
}

static int
cujoagent_vap_array_index(wifi_platform_property_t *wifi_prop,
                          wifi_interface_name_idex_map_t *iface_map) {
  /* We're copying the relevant structs from a (hopefully) successful
   * webconfig_decode(), so we assume that wifi_prop is valid and we don't need
   * to validate the actual values there. Therefore, just a basic check here.*/
  if (!wifi_prop || !iface_map) {
    CcspTraceError(("Wifi or iface map property is invalid\n"));
    return -1;
  }

  int vap_array_index = -1;
  for (int i = 0; i < (int)wifi_prop->numRadios * MAX_NUM_VAP_PER_RADIO; i++) {
    if (wifi_prop->interface_map[i].rdk_radio_index ==
        iface_map->rdk_radio_index) {
      vap_array_index++;
    }
    if (wifi_prop->interface_map[i].index == iface_map->index) {
      break;
    }
  }

  return vap_array_index;
}

static char *cujoagent_bytes_to_mac_str(mac_address_t mac, mac_addr_str_t key) {
  int count = snprintf(key, MAX_MAC_STR_LEN + 1, MAC_DOT_FMT,
                       mac[0], mac[1], mac[2], mac[3], mac[4], mac[5]);
  if (count < 0 || count >= MAX_MAC_STR_LEN + 1) {
    CcspTraceError(("MAC string doesn't fit into buffer\n"));
    return NULL;
  }
  return (char *)key;
}

static void
cujoagent_new_station_event(struct cujo_fpc_wifi_station_event *event,
                            wifi_station_event_context_t *event_ctx,
                            hash_map_t *assoc_dev_map,
                            wifi_vap_info_t *vap_info) {
  size_t ssid_len = 0;
  unsigned int client_count = 0;
  assoc_dev_data_t *assoc_dev_data = NULL;

  /* It's fine to have a NULL map passed here, we'd want an empty assoc list to
   * be sent for that event then. */
  if (assoc_dev_map) {
    assoc_dev_data = hash_map_get_first(assoc_dev_map);
    for (unsigned int i = 0; assoc_dev_data; i++) {
      /* FIXME: Hard-coding AUTO for now. */
      event->assoc_station_info[i].operating_mode = CUJO_FPC_WIFI_MODE_AUTO;

      memcpy(event->assoc_station_info[i].mac.ether_addr_octet,
             assoc_dev_data->dev_stats.cli_MACAddress, ETH_ALEN);

      assoc_dev_data = hash_map_get_next(assoc_dev_map, assoc_dev_data);
    }

    client_count = hash_map_count(assoc_dev_map);
  }
  event->assoc_station_count = client_count;

  event->event_type = event_ctx->event_type;
  event->timestamp_ms = event_ctx->timestamp_ms;
  event->vap_index = event_ctx->vap_index;

  /* FIXME: Not sure in what form an ESSID is available in RDK WIFI,
   * setting it to SSID for now. */
  ssid_len = cujoagent_copy_to((char *)event->essid, sizeof(event->essid),
                               vap_info->u.sta_info.ssid);
  event->essid_length = ssid_len;
}

static int cujoagent_freq_band(wifi_freq_bands_t oper_band) {
  int band = -1;
  switch (oper_band) {
  case WIFI_FREQUENCY_2_4_BAND:
    band = CUJO_FPC_WIFI_FREQ_2_4;
    break;
  case WIFI_FREQUENCY_5_BAND:
  case WIFI_FREQUENCY_5L_BAND:
  case WIFI_FREQUENCY_5H_BAND:
    band = CUJO_FPC_WIFI_FREQ_5;
    break;
  case WIFI_FREQUENCY_6_BAND:
  case WIFI_FREQUENCY_60_BAND:
    band = CUJO_FPC_WIFI_FREQ_6;
    break;
  default:
    break;
  }
  return band;
}

static void cujoagent_new_radio_event(struct cujo_fpc_radio_event *event,
                                      wifi_station_event_context_t *event_ctx,
                                      wifi_interface_name_idex_map_t *iface_map,
                                      rdk_wifi_radio_t *radio,
                                      wifi_vap_info_t *vap_info) {
  event->event_type = event_ctx->event_type;
  event->timestamp_ms = event_ctx->timestamp_ms;
  cujoagent_copy_to(event->if_name,
                    sizeof(event->if_name),
                    iface_map->interface_name);
  event->vap_index = event_ctx->vap_index;
  event->freq_band = cujoagent_freq_band(radio->oper.band);
  event->channel = radio->oper.channel;

  /* FIXME: Needs proper translation from radio_oper fields and bitmasks. And
   * even then that will be the radio's operating mode, not the station's.
   * Probably not worth the hassle, hard-coding to auto for now. */
  event->operating_mode = CUJO_FPC_WIFI_MODE_AUTO;

  memcpy(event->bssid.ether_addr_octet, vap_info->u.bss_info.bssid, ETH_ALEN);

  /* FIXME: Not sure in what form an ESSID is available in RDK WIFI,
   * setting it to SSID for now. */
  size_t ssid_len = cujoagent_copy_to((char *)event->essid,
                                      sizeof(event->essid),
                                      vap_info->u.sta_info.ssid);
  event->essid_length = ssid_len;

  memcpy(&event->station_mac, &event_ctx->station_mac,
         sizeof(event->station_mac));
}

static void
cujoagent_print_events(struct cujo_fpc_radio_event *radio_event,
                       struct cujo_fpc_wifi_station_event *station_event,
                       struct cujo_fpc_wifi_data_batch_event *batch_event) {
  char da[MAX_MAC_STR_LEN + 1] = {0};
  char sa[MAX_MAC_STR_LEN + 1] = {0};
  char bssid[MAX_MAC_STR_LEN + 1] = {0};

  if (radio_event) {
    CcspTraceDebug(
        ("CUJO_WIFI_RADIO_UPDATE_EVENT: "
         "event_type [%d] timestamp_ms [%" PRIu64 "] "
         "if_name [%s] vap_index [%u] freq_band [%d] channel [%u] "
         "operating_mode [%d] bssid [%s] essid [%s] "
         "essid length [%d] mac [%s] station_update_event_count [%d]\n",
         radio_event->event_type, radio_event->timestamp_ms,
         radio_event->if_name, radio_event->vap_index, radio_event->freq_band,
         radio_event->channel, radio_event->operating_mode,
         ether_ntoa_r(&radio_event->bssid, bssid), radio_event->essid,
         radio_event->essid_length, ether_ntoa_r(&radio_event->station_mac, sa),
         radio_event->station_update_event_count));
  }

  if (station_event) {
    CcspTraceDebug(("CUJO_WIFI_STATION_UPDATE_EVENT: "
                    "event_type [%d] timestamp_ms [%" PRIu64 "] "
                    "vap_index [%u] assoc_station_count [%u]\n",
                    station_event->event_type, station_event->timestamp_ms,
                    station_event->vap_index,
                    station_event->assoc_station_count));

    for (int i = 0; i < (int)station_event->assoc_station_count; i++) {
      CcspTraceDebug(
          ("CUJO_WIFI_STATION_UPDATE_EVENT: "
           "station [%d]: mac [%s] operating_mode [%d]\n",
           i, ether_ntoa_r(&station_event->assoc_station_info[i].mac, sa),
           station_event->assoc_station_info[i].operating_mode));
    }
  }

  if (batch_event) {
    CcspTraceDebug(("CUJO_WIFI_DATA_BATCH_EVENT: "
                    "timestamp_ms [%" PRIu64 "] "
                    "vap_index [%u] mac [%s] wifi_captures_count [%u]\n",
                    batch_event->timestamp_ms, batch_event->vap_index,
                    ether_ntoa_r(&batch_event->mac, sa),
                    batch_event->wifi_captures_count));

    struct cujo_fpc_wifi_pcap *pcap = NULL;
    uint64_t pcap_ts = 0;

    uint8_t version = 0;
    uint16_t hdrlen = 0;
    uint16_t fc = 0, duration = 0;
    uint16_t addr1 = 0, addr2 = 0, addr3 = 0;

    for (unsigned int i = 0, offset = 0; i < batch_event->wifi_captures_count;
         i++) {
      pcap = (struct cujo_fpc_wifi_pcap *)(batch_event->wifi_captures + offset);
      if (pcap->has_radiotap_header){
        version = pcap->data[0];
        hdrlen = le16toh(*(uint16_t *)&pcap->data[2]);
        CcspTraceDebug(("CUJO_WIFI_DATA_BATCH_EVENT: "
                        "radiotap [%u]: version [%" PRIu8 "] len [%" PRIu16
                        "]\n",
                        i, version, hdrlen));
      }

      pcap_ts = (uint64_t)pcap->header.ts.tv_sec * MSECS_PER_SEC +
                (uint64_t)pcap->header.ts.tv_usec / USECS_PER_MSEC;
      CcspTraceDebug(("CUJO_WIFI_DATA_BATCH_EVENT: "
                      "pcap_pkthdr [%u]: timestamp_ms [%" PRIu64
                      "] caplen [%" PRIu32 "] len [%" PRIu32 "]\n",
                      i, pcap_ts, pcap->header.caplen, pcap->header.len));

      fc = le16toh(*(uint16_t *)&pcap->data[hdrlen]);
      duration = le16toh(*(uint16_t *)&pcap->data[hdrlen + sizeof fc]);
      addr1 = hdrlen + sizeof fc + sizeof duration;
      addr2 = addr1 + sizeof(struct ether_addr);
      addr3 = addr2 + sizeof(struct ether_addr);
      CcspTraceDebug(
          ("CUJO_WIFI_DATA_BATCH_EVENT: "
           "ieee frame [%u]: fc [0x%04x] da[%s] sa[%s] bssid[%s]\n",
           i, fc, ether_ntoa_r((struct ether_addr *)&pcap->data[addr1], da),
           ether_ntoa_r((struct ether_addr *)&pcap->data[addr2], sa),
           ether_ntoa_r((struct ether_addr *)&pcap->data[addr3], bssid)));

      offset += sizeof(struct cujo_fpc_wifi_pcap) + pcap->header.caplen;
    }
  }
}

static void cujoagent_free_decoded_macfilter_entries(
    webconfig_subdoc_decoded_data_t *decoded_params) {
  if (!decoded_params) {
    CcspTraceError(("Decoded params invalid\n"));
    return;
  }

  unsigned int i = 0, j = 0;
  hash_map_t *acl_map = NULL;
  acl_entry_t *temp_acl_entry = NULL, *acl_entry = NULL;
  mac_addr_str_t mac_str = {0};

  for (i = 0; i < decoded_params->hal_cap.wifi_prop.numRadios; i++) {
    for (j = 0; j < decoded_params->radios[i].vaps.num_vaps; j++) {
      acl_map = decoded_params->radios[i].vaps.rdk_vap_array[j].acl_map;
      if (acl_map) {
        CcspTraceDebug(("Processing decoded [%p] ACL map\n", (void *)acl_map));
        acl_entry = hash_map_get_first(acl_map);
        while (acl_entry) {
          CcspTraceDebug(
              ("Processing decoded [%p] ACL entry\n", (void *)acl_entry));
          cujoagent_bytes_to_mac_str(acl_entry->mac, mac_str);
          acl_entry = hash_map_get_next(acl_map, acl_entry);
          temp_acl_entry = hash_map_remove(acl_map, mac_str);
          if (temp_acl_entry) {
            CcspTraceDebug(("Freeing [%p] mac [%s] from decoded ACL map [%p]\n",
                            (void *)temp_acl_entry, mac_str, (void *)acl_map));
            free(temp_acl_entry);
          }
        }
        CcspTraceDebug(("Destroying [%p] decoded ACL map\n", (void *)acl_map));
        hash_map_destroy(acl_map);
        decoded_params->radios[i].vaps.rdk_vap_array[j].acl_map = NULL;
      }
    }
  }
}

static void
cujoagent_remove_device_from_associated_devices_map(mac_address_t mac,
                                                    hash_map_t *assoc_dev_map) {
  if (!assoc_dev_map) {
    CcspTraceError(("Associated device map invalid\n"));
    return;
  }

  mac_addr_str_t mac_str = {0};
  cujoagent_bytes_to_mac_str(mac, mac_str);

  assoc_dev_data_t *assoc_dev_data = hash_map_remove(assoc_dev_map, mac_str);
  if (assoc_dev_data) {
    CcspTraceDebug(("Freeing [%p] mac [%s] from assoc device map [%p]\n",
                    (void *)assoc_dev_data, mac_str, (void *)assoc_dev_map));
    free(assoc_dev_data);
  }
}

static void
cujoagent_free_all_associated_devices_maps(rdk_wifi_radio_t *radios,
                                           unsigned int num_radios) {
  if (!radios) {
    CcspTraceError(("Radios invalid\n"));
    return;
  }

  hash_map_t *assoc_dev_map = NULL;
  assoc_dev_data_t *assoc_dev_data = NULL;
  assoc_dev_data_t *temp_assoc_dev_data = NULL;
  mac_addr_str_t mac_str = {0};

  for (unsigned int i = 0; i < num_radios; i++) {
    for (unsigned int j = 0; j < radios[i].vaps.num_vaps; j++) {
      /* Full associated device map */
      assoc_dev_map = radios[i].vaps.rdk_vap_array[j].associated_devices_map;
      if (assoc_dev_map) {
        CcspTraceDebug(("Processing [%p] full associated device map\n",
                        (void *)assoc_dev_map));
        assoc_dev_data = hash_map_get_first(assoc_dev_map);
        while (assoc_dev_data) {
          CcspTraceDebug(("Processing [%p] full associated device data\n",
                          (void *)assoc_dev_data));
          cujoagent_bytes_to_mac_str(assoc_dev_data->dev_stats.cli_MACAddress,
                                     mac_str);
          assoc_dev_data = hash_map_get_next(assoc_dev_map, assoc_dev_data);
          temp_assoc_dev_data = hash_map_remove(assoc_dev_map, mac_str);
          if (temp_assoc_dev_data) {
            CcspTraceDebug(
                ("Freeing [%p] mac [%s] from full associated device map [%p]\n",
                 (void *)temp_assoc_dev_data, mac_str, (void *)assoc_dev_map));
            free(temp_assoc_dev_data);
          }
        }
        CcspTraceDebug(("Destroying [%p] full associated device map\n",
                        (void *)assoc_dev_map));
        hash_map_destroy(assoc_dev_map);
        radios[i].vaps.rdk_vap_array[j].associated_devices_map = NULL;
      }

      /* Diff associated device map */
      assoc_dev_map =
          radios[i].vaps.rdk_vap_array[j].associated_devices_diff_map;
      if (assoc_dev_map) {
        CcspTraceDebug(("Processing [%p] diff associated device map\n",
                        (void *)assoc_dev_map));
        assoc_dev_data = hash_map_get_first(assoc_dev_map);
        while (assoc_dev_data) {
          CcspTraceDebug(("Processing [%p] diff associated device data\n",
                          (void *)assoc_dev_data));
          cujoagent_bytes_to_mac_str(assoc_dev_data->dev_stats.cli_MACAddress,
                                     mac_str);
          assoc_dev_data = hash_map_get_next(assoc_dev_map, assoc_dev_data);
          temp_assoc_dev_data = hash_map_remove(assoc_dev_map, mac_str);
          if (temp_assoc_dev_data) {
            CcspTraceDebug(
                ("Freeing [%p] mac [%s] from diff associated device map [%p]\n",
                 (void *)temp_assoc_dev_data, mac_str, (void *)assoc_dev_map));
            free(temp_assoc_dev_data);
          }
        }
        CcspTraceDebug(("Destroying [%p] diff associated device map\n",
                        (void *)assoc_dev_map));
        hash_map_destroy(assoc_dev_map);
        radios[i].vaps.rdk_vap_array[j].associated_devices_diff_map = NULL;
      }
    }
  }
}

static void cujoagent_update_associated_devices_map(mac_address_t event_mac,
                                                    hash_map_t *full,
                                                    hash_map_t *diff) {
  if (!full || !diff) {
    CcspTraceError(("Associated device map(s) invalid: full [%p] diff [%p]\n",
                    (void *)full, (void *)diff));
    return;
  }

  assoc_dev_data_t *diff_assoc_dev_data = NULL;
  assoc_dev_data_t *temp_assoc_dev_data = NULL;
  mac_addr_str_t mac_str = {0};

  CcspTraceDebug(("Updating associated_devices_map [%p] from "
                  "associated_devices_diff_map [%p]\n",
                  (void *)full, (void *)diff));

  cujoagent_bytes_to_mac_str(event_mac, mac_str);
  diff_assoc_dev_data = hash_map_get(diff, mac_str);
  if (!diff_assoc_dev_data) {
    CcspTraceError(("Failed to update associated_devices_map [%p], event mac "
                    "[%s] not found in associated_devices_diff_map [%p]\n",
                    (void *)full, mac_str, (void *)diff));
    return;
  }

  CcspTraceDebug(("Processing [%p] diff associated device data\n",
                  (void *)diff_assoc_dev_data));

  if (diff_assoc_dev_data->client_state == client_state_disconnected) {
    temp_assoc_dev_data = hash_map_remove(full, mac_str);
    if (temp_assoc_dev_data) {
      CcspTraceDebug(("Freeing [%p] diff mac [%s] from full assoc map [%p]\n",
                      (void *)temp_assoc_dev_data, mac_str, (void *)full));
      free(temp_assoc_dev_data);
    } else {
      CcspTraceDebug(("Diff mac [%s] is not in full assoc map [%p]\n", mac_str,
                      (void *)full));
    }
  } else if (diff_assoc_dev_data->client_state == client_state_connected) {
    temp_assoc_dev_data = hash_map_get(full, mac_str);
    if (!temp_assoc_dev_data) {
      temp_assoc_dev_data = malloc(sizeof(assoc_dev_data_t));
      if (temp_assoc_dev_data == NULL) {
        CcspTraceError(("Failed to allocate a diff mac [%s]\n", mac_str));
        return;
      }
      *temp_assoc_dev_data = *diff_assoc_dev_data;
      CcspTraceDebug(("Adding [%p] diff mac [%s] to full assoc map [%p]\n",
                      (void *)temp_assoc_dev_data, mac_str, (void *)full));
      hash_map_put(full, strdup(mac_str), temp_assoc_dev_data);
    } else {
      CcspTraceDebug(
          ("The diff mac [%s] is already present [%p] in full assoc map "
           "[%p], updating it\n",
           mac_str, (void *)temp_assoc_dev_data, (void *)full));
      *temp_assoc_dev_data = *diff_assoc_dev_data;
    }
  }
}

static void
cujoagent_process_webconfig_event(cujoagent_wifi_consumer_t *consumer,
                                  char const *s,
                                  __attribute__((unused)) size_t slen,
                                  cujoagent_consumer_event_subtype_t subtype) {
  webconfig_subdoc_data_t *data = NULL;
  data = (webconfig_subdoc_data_t *) malloc(sizeof(webconfig_subdoc_data_t));
  if (data == NULL)
  {
    CcspTraceError(("%s:%d Failed to allocate memory for webconfig subdoc data",
                    __FUNCTION__, __LINE__));
    return;
  }
  memset(data, 0, sizeof(webconfig_subdoc_data_t));

  webconfig_subdoc_decoded_data_t *decoded_params = &data->u.decoded;
  wifi_hal_capability_t *hal_cap = &decoded_params->hal_cap;
  wifi_platform_property_t *wifi_prop = &hal_cap->wifi_prop;

  /* Depending on the subdoc type the relevant structures have to be populated
   * for a successful webconfig_decode(). */
  cujoagent_update_decoded_wifi_structs(consumer, decoded_params);

  webconfig_error_t err = webconfig_decode(&consumer->webconfig, data, s);
  if (err) {
    CcspTraceError(("Webconfig decode failed with [%d]\n", err));
    if (data != NULL) {
      free(data);
      data = NULL;
    }
    return;
  }

  wifi_station_event_context_t *queue_data = NULL;
  wifi_interface_name_idex_map_t *iface_map = NULL;
  rdk_wifi_radio_t *radio = NULL;
  int vap_array_index = 0;
  wifi_vap_info_t *vap_info = NULL;
  hash_map_t *assoc_dev_map = NULL;
  hash_map_t *assoc_dev_diff_map = NULL;
  assoc_dev_data_t *diff_assoc_dev_data = NULL;
  unsigned int assoc_dev_count = 0;

  struct cujo_fpc_wifi_station_event *station_update_event = NULL;
  size_t station_update_event_size = 0;
  struct cujo_fpc_radio_event radio_update_event = {0};
  size_t radio_update_event_size = sizeof radio_update_event;
  mac_addr_str_t mac_in_queue = {0};

  webconfig_subdoc_type_t subdoc_type = data->type;
  CcspTraceDebug(("Processing webconfig subdoc type [%d]\n", subdoc_type));
  switch (subtype) {
  case consumer_event_webconfig_init:
    /* A special case where we need to notify the main thread that decoding
     * initial webconfig data is finished and consumer structures are updated,
     * so the subscription to the RBUS can continue. */

    /* De-allocate ACL maps, we do not consume ACL data in any way. */
    cujoagent_free_decoded_macfilter_entries(decoded_params);

    /* Update the consumer, so that the relevant data is updated for the
     * next callbacks. */
    cujoagent_update_consumer_wifi_structs(consumer, decoded_params);
    cujoagent_write_event(consumer->efd_m, NOTIFY_WEBCONFIG_INIT_READY);
    break; // consumer_event_webconfig_init
  case consumer_event_webconfig_set_data:
    switch (subdoc_type) {
    case webconfig_subdoc_type_associated_clients:
      if (decoded_params->assoclist_notifier_type == assoclist_notifier_full) {
        cujoagent_free_all_associated_devices_maps(
            consumer->radios, consumer->hal_cap.wifi_prop.numRadios);
      }
      break; // webconfig_subdoc_type_associated_clients
    default:
      break;
    }

    /* De-allocate ACL maps, we do not consume ACL data in any way. */
    cujoagent_free_decoded_macfilter_entries(decoded_params);

    /* Update the consumer, so that the relevant data is updated for the
     * next callbacks. */
    cujoagent_update_consumer_wifi_structs(consumer, decoded_params);

    break; // consumer_event_webconfig_set_data
  case consumer_event_webconfig_get_data:
    switch (subdoc_type) {
    case webconfig_subdoc_type_associated_clients:
      if (decoded_params->assoclist_notifier_type == assoclist_notifier_full) {
        cujoagent_free_all_associated_devices_maps(
            consumer->radios, consumer->hal_cap.wifi_prop.numRadios);
        cujoagent_update_consumer_wifi_structs(consumer, decoded_params);
      }

      while (queue_count(consumer->assoc_disassoc_events)) {
        queue_data = queue_pop(consumer->assoc_disassoc_events);
        if (queue_data == NULL) {
          continue;
        }

        cujoagent_bytes_to_mac_str(queue_data->station_mac.ether_addr_octet,
                                   mac_in_queue);
        CcspTraceDebug(("Processing event [%d] for mac [%s]\n",
                        queue_data->event_type, mac_in_queue));

        iface_map = cujoagent_iface_property(wifi_prop, queue_data->vap_index);
        if (!iface_map) {
          CcspTraceError(("Couldn't find interface map for vap index [%u]\n",
                          queue_data->vap_index));
          free(queue_data);
          continue;
        }
        radio = &decoded_params->radios[iface_map->rdk_radio_index];

        vap_array_index = cujoagent_vap_array_index(wifi_prop, iface_map);
        if (vap_array_index == -1) {
          CcspTraceError(
              ("Couldn't find vap array index for iface map index [%u]\n",
               iface_map->index));
          free(queue_data);
          continue;
        }
        vap_info = &radio->vaps.vap_map.vap_array[vap_array_index];

        /* It might be the very first connect to the vap,
         * create consumer's full map for those cases. */
        if (decoded_params->assoclist_notifier_type ==
            assoclist_notifier_diff) {
          if (consumer->radios[iface_map->rdk_radio_index]
                  .vaps.rdk_vap_array[vap_array_index]
                  .associated_devices_map == NULL) {
            consumer->radios[iface_map->rdk_radio_index]
                .vaps.rdk_vap_array[vap_array_index]
                .associated_devices_map = hash_map_create();
            CcspTraceDebug(("New associated_devices_map created [%p]\n",
                            (void *)consumer->radios[iface_map->rdk_radio_index]
                                .vaps.rdk_vap_array[vap_array_index]
                                .associated_devices_map));
          }
        }

        assoc_dev_map = consumer->radios[iface_map->rdk_radio_index]
                            .vaps.rdk_vap_array[vap_array_index]
                            .associated_devices_map;

        if (decoded_params->assoclist_notifier_type ==
            assoclist_notifier_diff) {
          assoc_dev_diff_map = radio->vaps.rdk_vap_array[vap_array_index]
                                   .associated_devices_diff_map;

          /* The connect/disconnect event mac not matching with anything
           * present in the diff assoc list is a red flag. It makes no sense to
           * try updating the full assoc map we maintain in consumer or send a
           * TLV with potentially wrong data in that case either. */
          diff_assoc_dev_data = hash_map_get(assoc_dev_diff_map, mac_in_queue);
          if (!diff_assoc_dev_data) {
            CcspTraceError(("Event [%d] mac [%s] not found in "
                            "associated_devices_diff_map [%p]\n",
                            queue_data->event_type, mac_in_queue,
                            (void *)assoc_dev_diff_map));
            free(queue_data);
            continue;
          }

          /* The data for station events is gathered per connected/disconnected
           * MAC, but we are sending the list of _all_ currently associated
           * devices with it as well. Therefore, we need to update the full
           * associated devices map first (in order to gather the correct
           * associated devices list for the current station update event) and
           * only then de-allocate the particular client (not the entire map).
           * When we're done with processing the connect/disconnect queue we
           * can finally nuke the map. */
          cujoagent_update_associated_devices_map(
              queue_data->station_mac.ether_addr_octet, assoc_dev_map,
              assoc_dev_diff_map);

          /* The following might happen if multiple (rapid) consecutive
           * connect/disconnect events for a particular station were pushed to
           * the assoc_disassoc_events queue and then the diff assoclist event
           * we are processing here reflects only the "cumulative" state of
           * those multiple connections/disconnections. In that case it makes
           * no sense to send a TLV with potentially wrong data for the
           * station. Also, we should skip removing the device from the diff
           * map, so that we have it intact for the next event in the queue
           * (i.e. consider the assoc list as the source of truth). */
          if (((diff_assoc_dev_data->client_state ==
                client_state_disconnected) &&
               (queue_data->event_type == CUJO_FPC_CONNECT)) ||
              ((diff_assoc_dev_data->client_state == client_state_connected) &&
               (queue_data->event_type == CUJO_FPC_DISCONNECT))) {
            CcspTraceWarning(("Event [%d] for mac [%s] mismatch with the diff "
                              "assoc list [%p] device client state [%d]\n",
                              queue_data->event_type, mac_in_queue,
                              (void *)assoc_dev_diff_map,
                              diff_assoc_dev_data->client_state));
            free(queue_data);
            continue;
          }

          cujoagent_remove_device_from_associated_devices_map(
              queue_data->station_mac.ether_addr_octet, assoc_dev_diff_map);
        }

        /* We can skip to processing the next connect/disconnect event only
         * after we had updated the consumer maintained assoc list above. */
        if (!consumer->comms_ready) {
          CcspTraceWarning(
              ("Not yet ready to send tlv data for mac [%s] event [%d]\n",
               mac_in_queue, queue_data->event_type));
          free(queue_data);
          continue;
        }

        /* ================================ */
        /* CUJO_FPC_WIFI_RADIO_UPDATE_EVENT */
        /* ================================ */
        cujoagent_new_radio_event(&radio_update_event, queue_data, iface_map,
                                  radio, vap_info);

        /* We're sending radio update event for every station update event */
        radio_update_event.station_update_event_count = 1;

        consumer->tlv_ctx.size =
            sizeof(struct cujo_fpc_tlv) + radio_update_event_size;
        consumer->tlv_ctx.tlv = calloc(1, consumer->tlv_ctx.size);
        if (!consumer->tlv_ctx.tlv) {
          CcspTraceError(
              ("Failed to allocate radio event tlv for mac [%s] event [%d]\n",
               mac_in_queue, queue_data->event_type));
          free(queue_data);
          break;
        }
        consumer->tlv_ctx.tlv->tag = CUJO_FPC_WIFI_RADIO_UPDATE_EVENT;
        consumer->tlv_ctx.tlv->len = radio_update_event_size;
        memcpy(consumer->tlv_ctx.tlv->data, &radio_update_event,
               radio_update_event_size);

        if ((cujoagent_write_event(consumer->efd_c, NOTIFY_RADIO_DATA_READY) == -1) ||
            (cujoagent_wait_for_event(consumer->epfd_c,
                                      NOTIFY_RADIO_DATA_SENT,
                                      EPOLL_TIMEOUT_MS) <= 0)) {
          CcspTraceError(("Sending radio event tlv for mac [%s] event [%d] "
                          "failed or timed out\n",
                          mac_in_queue, queue_data->event_type));
          free(consumer->tlv_ctx.tlv);
          consumer->tlv_ctx.tlv = NULL;
          free(queue_data);

          /* Assume that we either can't reliably notify the comms loop or the
           * comms loops failed to send the data. We are in the consumer queue
           * here, hence, already under the lock and it is expected to be safe
           * to set the comms_ready here. */
          consumer->comms_ready = false;
          continue;
        }
        free(consumer->tlv_ctx.tlv);
        consumer->tlv_ctx.tlv = NULL;

        /* ================================== */
        /* CUJO_FPC_WIFI_STATION_UPDATE_EVENT */
        /* ================================== */
        assoc_dev_count = 0;
        if (assoc_dev_map) {
          assoc_dev_count = hash_map_count(assoc_dev_map);
        }
        station_update_event_size =
            sizeof(struct cujo_fpc_wifi_station_event) +
            assoc_dev_count * sizeof(struct cujo_fpc_assoc_station_info);
        station_update_event = malloc(station_update_event_size);
        if (station_update_event == NULL) {
          CcspTraceError(("Failed to allocate station update event for mac "
                          "[%s] event [%d]\n",
                          mac_in_queue, queue_data->event_type));
          free(queue_data);
          break;
        }

        cujoagent_new_station_event(station_update_event, queue_data,
                                    assoc_dev_map, vap_info);

        consumer->tlv_ctx.size =
            sizeof(struct cujo_fpc_tlv) + station_update_event_size;
        consumer->tlv_ctx.tlv = calloc(1, consumer->tlv_ctx.size);
        if (!consumer->tlv_ctx.tlv) {
          CcspTraceError(
              ("Failed to allocate station event tlv for mac [%s] event [%d]\n",
               mac_in_queue, queue_data->event_type));
          free(station_update_event);
          station_update_event = NULL;
          free(queue_data);
          break;
        }
        consumer->tlv_ctx.tlv->tag = CUJO_FPC_WIFI_STATION_UPDATE_EVENT;
        consumer->tlv_ctx.tlv->len = station_update_event_size;
        memcpy(consumer->tlv_ctx.tlv->data, station_update_event,
               station_update_event_size);

        if ((cujoagent_write_event(consumer->efd_c, NOTIFY_STATION_DATA_READY) == -1) ||
            (cujoagent_wait_for_event(consumer->epfd_c,
                                      NOTIFY_STATION_DATA_SENT,
                                      EPOLL_TIMEOUT_MS) <= 0)) {
          CcspTraceError(("Sending station event tlv for mac [%s] event [%d] "
                          "failed or timed out\n",
                          mac_in_queue, queue_data->event_type));
          free(station_update_event);
          /* CID 340314: Unused value */
          free(consumer->tlv_ctx.tlv);
          consumer->tlv_ctx.tlv = NULL;
          free(queue_data);

          /* Assume that we either can't reliably notify the comms loop or the
           * comms loops failed to send the data. We are in the consumer queue
           * here, hence, already under the lock and it is expected to be safe
           * to set the comms_ready here. */
          consumer->comms_ready = false;
          continue;
        }
        free(consumer->tlv_ctx.tlv);
        consumer->tlv_ctx.tlv = NULL;

        cujoagent_print_events(&radio_update_event, station_update_event, NULL);

        /* Allocated before calling the cujoagent_new_station_event() */
        free(station_update_event);
        station_update_event = NULL;

        /* Allocated in cujoagent_process_station_update_event() */
        free(queue_data);
      }

      if (decoded_params->assoclist_notifier_type == assoclist_notifier_diff) {
        cujoagent_free_all_associated_devices_maps(decoded_params->radios,
                                                   decoded_params->num_radios);
      }

      break; // webconfig_subdoc_type_associated_clients
    default:
      break;
    }
    break; // consumer_event_webconfig_get_data
  default:
    break; // default
  }
  webconfig_data_free(data);
  if (data != NULL) {
    free(data);
    data = NULL;
  }
}

static void cujoagent_process_station_update_event(
    cujoagent_wifi_consumer_t *consumer, wifi_station_event_context_t *ctx,
    size_t ctx_size, cujoagent_consumer_event_subtype_t subtype) {

  wifi_station_event_context_t *data = NULL;
  switch (subtype) {
  case consumer_event_sta_connect:
  case consumer_event_sta_disconnect:
    /* The consumer queue_data->msg will be free'ed on return from the
     * current function, therefore, we can't just queue_push() to yet another
     * queue for storing the assoc list data to be digested by the handler
     * later. So, malloc() and memcpy() again. */
    data = malloc(sizeof *data);
    if (data == NULL) {
      CcspTraceError(("Failed to allocate the station event context\n"));
      return;
    }
    memcpy(data, ctx, ctx_size);
    queue_push(consumer->assoc_disassoc_events, data);
    break;
  default:
    break;
  }

  return;
}

static int cujoagent_new_data_batch_event(
    struct cujo_fpc_wifi_data_batch_event **event, size_t *event_size,
    struct cujo_fpc_wifi_pcap *pcap, size_t pcap_size,
    cujoagent_wifi_consumer_t *consumer, frame_data_t *rdk_mgmt) {
  size_t size = sizeof(struct cujo_fpc_wifi_data_batch_event) + pcap_size;
  *event = malloc(size);
  if (*event == NULL) {
    CcspTraceError(("Failed to allocate data batch event\n"));
    return -1;
  }
  *event_size = size;

  /* XXX: An event for each received frame. */
  (*event)->wifi_captures_count = 1;

  (*event)->timestamp_ms = cujoagent_timestamp();
  (*event)->vap_index = rdk_mgmt->frame.ap_index;

  wifi_hal_capability_t *hal_cap = &consumer->hal_cap;
  wifi_platform_property_t *wifi_prop = &hal_cap->wifi_prop;

  wifi_interface_name_idex_map_t *iface_map =
      cujoagent_iface_property(wifi_prop, rdk_mgmt->frame.ap_index);
  if (!iface_map) {
    CcspTraceError(("Couldn't find interface map for vap index [%d]\n",
                    rdk_mgmt->frame.ap_index));
    return -1;
  }
  rdk_wifi_radio_t *radio = &consumer->radios[iface_map->rdk_radio_index];

  int vap_array_index = cujoagent_vap_array_index(wifi_prop, iface_map);
  if (vap_array_index == -1) {
    CcspTraceError(("Couldn't find vap array index for iface map index [%u]\n",
                    iface_map->index));
    return -1;
  }
  wifi_vap_info_t *vap_info = &radio->vaps.vap_map.vap_array[vap_array_index];

  memcpy((*event)->mac.ether_addr_octet, vap_info->u.bss_info.bssid, ETH_ALEN);
  memcpy((*event)->wifi_captures, pcap, pcap_size);

  return 0;
}

static void
cujoagent_process_mgmt_frame_event(cujoagent_wifi_consumer_t *consumer,
                                   frame_data_t *rdk_mgmt,
                                   __attribute__((unused)) size_t rdk_mgmt_len,
                                   cujoagent_consumer_event_subtype_t subtype) {
  mac_addr_str_t sta_mac = {0};
  cujoagent_bytes_to_mac_str(rdk_mgmt->frame.sta_mac, sta_mac);

  /* We don't need to update any data maintained in the consumer from the frame
   * event payload, therefore it's fine to bail out here. Arguably, we could do
   * that as early as at the RBUS notification callback, but we are already
   * under a mutex lock here and that should help to avoid any potential races
   * in contrast of acquiring the lock at RBUS notification callback while
   * something else is being processed in the queue. */
  if (!consumer->comms_ready) {
    CcspTraceWarning((
        "Not yet ready to send tlv data for rdk frame type [%d] sta_mac [%s]\n",
        rdk_mgmt->frame.type, sta_mac));
    return;
  }

  /* FIXME: Fake empty radiotap header */
  uint8_t rt[EMPTY_RT_LEN] = {0x00, 0x00, EMPTY_RT_LEN, 0x00, 0x00, 0x00, 0x00, 0x00};
  size_t data_size = rdk_mgmt->frame.len + EMPTY_RT_LEN;

  size_t pcap_size = sizeof(struct cujo_fpc_wifi_pcap) + data_size;
  struct cujo_fpc_wifi_pcap *pcap = malloc(pcap_size);
  if (pcap == NULL) {
    CcspTraceError(
        ("Failed to allocate wifi pcap for frame type [%d] sta_mac [%s]\n",
         rdk_mgmt->frame.type, sta_mac));
    return;
  }

  /* FIXME: timestamp is not yet available in the RBUS payload */
  struct timeval tv = {0};
  gettimeofday(&tv, NULL);
  memcpy(&pcap->header.ts, &tv, sizeof(pcap->header.ts));

  /* Assuming no partial packet captures */
  pcap->header.caplen = data_size;
  pcap->header.len = data_size;

  pcap->has_radiotap_header = true;

  memcpy(pcap->data, &rt, EMPTY_RT_LEN);
  memcpy(pcap->data + EMPTY_RT_LEN, rdk_mgmt->data, rdk_mgmt->frame.len);

  struct cujo_fpc_wifi_data_batch_event *data_batch_event = NULL;
  size_t data_batch_event_size = 0;

  switch (subtype) {
  case consumer_event_probe_req:
  case consumer_event_auth:
  case consumer_event_assoc_req:
  case consumer_event_reassoc_req:
    cujoagent_new_data_batch_event(&data_batch_event,
                                   &data_batch_event_size,
                                   pcap, pcap_size,
                                   consumer, rdk_mgmt);
    break;
  default:
    break;
  }

  if (data_batch_event == NULL) {
    CcspTraceError(("Gathering data for wifi data batch event frame type [%d] "
                    "sta_mac [%s] failed\n",
                    rdk_mgmt->frame.type, sta_mac));
    free(pcap);
    return;
  }

  /* ========================== */
  /* CUJO_WIFI_DATA_BATCH_EVENT */
  /* ========================== */
  consumer->tlv_ctx.size = sizeof(struct cujo_fpc_tlv) + data_batch_event_size;
  consumer->tlv_ctx.tlv = calloc(1, consumer->tlv_ctx.size);
  if (!consumer->tlv_ctx.tlv) {
    CcspTraceError(("Failed to allocate wifi data batch event tlv for rdk "
                    "frame type [%d] sta_mac [%s]\n",
                    rdk_mgmt->frame.type, sta_mac));
    free(pcap);
    free(data_batch_event);
    return;
  }

  consumer->tlv_ctx.tlv->tag = CUJO_FPC_WIFI_DATA_BATCH_EVENT;
  consumer->tlv_ctx.tlv->len = data_batch_event_size;
  memcpy(consumer->tlv_ctx.tlv->data, data_batch_event, data_batch_event_size);

  if ((cujoagent_write_event(consumer->efd_c, NOTIFY_BATCH_DATA_READY) == -1) ||
      (cujoagent_wait_for_event(consumer->epfd_c,
                                NOTIFY_BATCH_DATA_SENT,
                                EPOLL_TIMEOUT_MS) <= 0)) {
    CcspTraceError(("Sending data batch tlv for rdk frame type [%d] sta_mac "
                    "[%s] failed or timed out\n",
                    rdk_mgmt->frame.type, sta_mac));
    free(pcap);
    free(data_batch_event);
    free(consumer->tlv_ctx.tlv);
    consumer->tlv_ctx.tlv = NULL;

    /* Assume that we either can't reliably notify the comms loop or the comms
     * loops failed to send the data. We are in the consumer queue here, hence,
     * already under the lock and it is expected to be safe to set the
     * comms_ready here. */
    consumer->comms_ready = false;
    return;
  }

  cujoagent_print_events(NULL, NULL, data_batch_event);

  free(pcap);
  free(data_batch_event);
  free(consumer->tlv_ctx.tlv);
  consumer->tlv_ctx.tlv = NULL;

  return;
}

static void *cujoagent_consumer_queue_loop(void *arg) {
  cujoagent_wifi_consumer_event_t *queue_data = NULL;
  cujoagent_wifi_consumer_t *consumer = arg;

  pthread_mutex_lock(&consumer->lock);
  for (;;) {
    while (!consumer->queue_wakeup) {
      pthread_cond_wait(&consumer->cond, &consumer->lock);
    }

    if (consumer->exit_consumer) {
      break;
    }

    while (queue_count(consumer->queue)) {
      queue_data = queue_pop(consumer->queue);
      if (queue_data == NULL) {
        continue;
      }

      switch (queue_data->event_type) {
      case consumer_event_type_webconfig:
        cujoagent_process_webconfig_event(consumer, queue_data->msg,
                                          queue_data->mlen,
                                          queue_data->event_subtype);
        break;
      case consumer_event_type_station_update:
        cujoagent_process_station_update_event(consumer, queue_data->msg,
                                               queue_data->mlen,
                                               queue_data->event_subtype);
        break;
      case consumer_event_type_mgmt_frame:
        cujoagent_process_mgmt_frame_event(consumer, queue_data->msg,
                                           queue_data->mlen,
                                           queue_data->event_subtype);
        break;
      default:
        break;
      }

      /* Free data allocated at every push to queue */
      if (queue_data->msg) {
        free(queue_data->msg);
      }
      free(queue_data);
    }

    consumer->queue_wakeup = false;
  }
  pthread_mutex_unlock(&consumer->lock);

  CcspTraceDebug(("Returning from consumer thread routine\n"));
  return NULL;
}

static int cujoagent_spawn_consumer_loop(cujoagent_wifi_consumer_t *consumer) {
  pthread_attr_t attr;
  pthread_attr_init(&attr);
  pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);
  pthread_t thr = 0;

  int err =
      pthread_create(&thr, &attr, &cujoagent_consumer_queue_loop, consumer);
  if (err) {
    CcspTraceError(("Failed to start a consumer queue loop thread\n"));
    return err;
  }

  pthread_attr_destroy(&attr);
  return err;
}

static int
cujoagent_push_to_consumer_queue(cujoagent_wifi_consumer_t *consumer,
                                 void const *msg, size_t mlen,
                                 cujoagent_consumer_event_type_t type,
                                 cujoagent_consumer_event_subtype_t subtype) {
  cujoagent_wifi_consumer_event_t *data = NULL;

  data = (cujoagent_wifi_consumer_event_t *)malloc(sizeof(cujoagent_wifi_consumer_event_t));
  if (data == NULL) {
    CcspTraceError(("Failed to allocate consumer queue data\n"));
    return -1;
  }
  memset(data, 0, sizeof(cujoagent_wifi_consumer_event_t));

  data->event_type = type;
  data->event_subtype = subtype;

  data->msg = malloc(mlen + 1);
  if (data->msg == NULL) {
    CcspTraceError(("Failed to allocate consumer queue data message\n"));
    if (data != NULL) {
      free(data);
      data = NULL;
    }
    return -1;
  }
  memset(data->msg, 0, mlen + 1);

  memcpy(data->msg, msg, mlen);
  data->mlen = mlen;

  pthread_mutex_lock(&consumer->lock);
  queue_push(consumer->queue, data);
  consumer->queue_wakeup = true;
  pthread_mutex_unlock(&consumer->lock);
  pthread_cond_signal(&consumer->cond);

  return 0;
}

static rbusError_t
cujoagent_webconfig_init_get(cujoagent_wifi_consumer_t *consumer) {
  struct epoll_event ev = {.events = EPOLLIN | EPOLLET,
                           .data.fd = consumer->efd_m};
  if (epoll_ctl(consumer->epfd_m, EPOLL_CTL_ADD, consumer->efd_m, &ev)) {
    CcspTraceError(("Failed to add a webconfig init event fd to epoll "
                    "interest list\n"));
    return RBUS_ERROR_BUS_ERROR;
  }

  char *s = NULL;
  char const *name = WIFI_WEBCONFIG_INIT_DATA_NAMESPACE;

  rbusError_t err = rbus_getStr(consumer->rbus_handle, name, &s);
  if (err) {
    CcspTraceError(("Failed to get [%s] over RBUS: [%d]\n", name, err));
    return err;
  }

  cujoagent_push_to_consumer_queue(consumer, s, strlen(s),
                                   consumer_event_type_webconfig,
                                   consumer_event_webconfig_init);

  /* rbus_getStr() return is strdup()'ed, free it */
  free(s);

  /* Wait until the WIFI_WEBCONFIG_INIT_DATA_NAMESPACE is processed in the
   * consumer queue thread (or time out). Otherwise, the subscribing code won't
   * get any vap indexes for subscription to the appropriate connect/disconnect
   * events only. */
  if (cujoagent_wait_for_event(consumer->epfd_m, NOTIFY_WEBCONFIG_INIT_READY,
                               EPOLL_TIMEOUT_MS) <= 0) {
    CcspTraceError(("Processing webconfig init failed or timed out\n"));
    return RBUS_ERROR_BUS_ERROR;
  }

  if (epoll_ctl(consumer->epfd_m, EPOLL_CTL_DEL, consumer->efd_m, NULL)) {
    CcspTraceError(("Failed to remove a webconfig init event fd from epoll "
                    "interest list\n"));
    return RBUS_ERROR_BUS_ERROR;
  }

  close(consumer->efd_m);
  consumer->efd_m = -1;

  close(consumer->epfd_m);
  consumer->epfd_m = -1;

  return RBUS_ERROR_SUCCESS;
}

static rbusError_t
cujoagent_assoc_list_init_get(cujoagent_wifi_consumer_t *consumer) {
  char *s = NULL;
  char const *name = WIFI_WEBCONFIG_GET_ASSOC;

  rbusError_t err = rbus_getStr(consumer->rbus_handle, name, &s);
  if (err) {
    CcspTraceError(("Failed to get [%s] over RBUS: [%d]\n", name, err));
    return err;
  }

  cujoagent_push_to_consumer_queue(consumer, s, strlen(s),
                                   consumer_event_type_webconfig,
                                   consumer_event_webconfig_set_data);

  /* rbus_getStr() return is strdup()'ed, free it */
  free(s);
  return RBUS_ERROR_SUCCESS;
}

static void cujoagent_webconfig_handler(__attribute__((unused))
                                        rbusHandle_t handle,
                                        rbusEvent_t const *event,
                                        rbusEventSubscription_t *subscription) {
  cujoagent_wifi_consumer_t *consumer = subscription->userData;

  rbusValue_t value = rbusObject_GetValue(event->data, subscription->eventName);
  if (!value) {
    CcspTraceError(("Failed to get [%s] value\n", subscription->eventName));
    return;
  }

  int slen = 0;
  char const *s = rbusValue_GetString(value, &slen);
  if (s == NULL) {
    CcspTraceError(
        ("Failed to get string for [%s]\n", subscription->eventName));
    return;
  }

  /* The WIFI_WEBCONFIG_GET_ASSOC case. Practically should happen way more
   * often than any wifi config changes. Pushing to the "get" case of the queue,
   * because event based notification payload is a partial _diff_ type of the
   * assoclist. */
  cujoagent_consumer_event_subtype_t subtype = consumer_event_webconfig_get_data;

  if (strcmp(subscription->eventName, WIFI_WEBCONFIG_DOC_DATA_NORTH) == 0) {
    subtype = consumer_event_webconfig_set_data;
  }

  cujoagent_push_to_consumer_queue(consumer, s, slen,
                                   consumer_event_type_webconfig,
                                   subtype);
}

static void
cujoagent_frame_events_handler(__attribute__((unused)) rbusHandle_t handle,
                               rbusEvent_t const *event,
                               rbusEventSubscription_t *subscription) {
  cujoagent_wifi_consumer_t *consumer = subscription->userData;

  rbusValue_t value = rbusObject_GetValue(event->data, subscription->eventName);
  if (!value) {
    CcspTraceError(("Failed to get [%s] value\n", subscription->eventName));
    return;
  }

  int len = 0;
  uint8_t const *data = rbusValue_GetBytes(value, &len);
  if (!data || (len > (int)sizeof(frame_data_t))) {
    CcspTraceError(("Invalid event [%s] data\n", subscription->eventName));
    return;
  }

  frame_data_t *rdk_mgmt = (frame_data_t *)data;
  uint16_t fc = le16toh(*(uint16_t*)&rdk_mgmt->data[0]);
  uint16_t subtype = fc & FCTL_STYPE;

  CcspTraceDebug(("Subscription [%s] rbus payload: rdk frame type [%d], "
                  "ieee80211 frame fc [0x%04x] "
                  "type [%" PRIu16 "] subtype [%" PRIu16 "]\n",
                  subscription->eventName, rdk_mgmt->frame.type, fc,
                  FC_GET_TYPE(fc), FC_GET_STYPE(fc)));

  /* TODO: Action No Ack frames, i.e. frame control B7..B4 == 1110 */
  int event_subtype = WIFI_MGMT_FRAME_TYPE_INVALID;
  switch (rdk_mgmt->frame.type) {
  case WIFI_MGMT_FRAME_TYPE_PROBE_REQ:
    if (subtype == STYPE_PROBE_REQ) {
      event_subtype = consumer_event_probe_req;
    }
    break;
  case WIFI_MGMT_FRAME_TYPE_AUTH:
    if (subtype == STYPE_AUTH) {
      event_subtype = consumer_event_auth;
    }
    break;
  case WIFI_MGMT_FRAME_TYPE_ASSOC_REQ:
    if (subtype == STYPE_ASSOC_REQ) {
      event_subtype = consumer_event_assoc_req;
    }
    break;
  case WIFI_MGMT_FRAME_TYPE_REASSOC_REQ:
    if (subtype == STYPE_REASSOC_REQ) {
      event_subtype = consumer_event_reassoc_req;
    }
    break;
  default:
    break;
  }

  if (event_subtype == WIFI_MGMT_FRAME_TYPE_INVALID) {
    CcspTraceError(("Unsupported or invalid mgmt frame: rdk frame type [%d], "
                    "ieee80211 subtype [%" PRIu16 "]\n",
                    rdk_mgmt->frame.type, FC_GET_STYPE(fc)));
    return;
  }

  cujoagent_push_to_consumer_queue(consumer, data, len,
                                   consumer_event_type_mgmt_frame,
                                   event_subtype);
}

static rbusError_t
cujoagent_station_event_mac(rbusEvent_t const *event,
                        rbusEventSubscription_t *subscription,
                        struct ether_addr *station_mac) {
  if (!event || !subscription || !station_mac) {
    return RBUS_ERROR_BUS_ERROR;
  }

  rbusValue_t value = rbusObject_GetValue(event->data, subscription->eventName);
  if (!value) {
    CcspTraceError(("Failed to get [%s] value\n", subscription->eventName));
    return RBUS_ERROR_BUS_ERROR;
  }

  int len = 0;
  uint8_t const *data = rbusValue_GetBytes(value, &len);
  if (!data || (len != ETH_ALEN)) {
    CcspTraceError(("Invalid event [%s] data\n", subscription->eventName));
    return RBUS_ERROR_BUS_ERROR;
  }

  memcpy(station_mac->ether_addr_octet, data, len);
  return RBUS_ERROR_SUCCESS;
}

static void cujoagent_new_station_event_context(
    wifi_station_event_context_t *ctx, enum cujo_fpc_event_type event_type,
    rbusEvent_t const *event, rbusEventSubscription_t *subscription) {

  ctx->event_type = event_type;
  ctx->timestamp_ms = cujoagent_timestamp();

  const char *fmt = NULL;
  switch (event_type) {
  case CUJO_FPC_CONNECT:
    fmt = WIFI_ACCESSPOINT_DEVICE_CONNECTED;
    break;
  case CUJO_FPC_DISCONNECT:
    fmt = WIFI_ACCESSPOINT_DEVICE_DISCONNECTED;
    break;
  default:
    break;
  }

  if (fmt == NULL) {
    return;
  }

  unsigned int event_vap_idx;
  if (sscanf(subscription->eventName, fmt, &event_vap_idx) != 1) {
    return;
  }

  /* The above is the vap number as it is in an event name used for
   * subscription. The actual vap index matching with the interface
   * and vap maps is: event_vap_idx - 1 */
  ctx->vap_index = event_vap_idx - 1;

  if (cujoagent_station_event_mac(event, subscription, &ctx->station_mac) !=
      RBUS_ERROR_SUCCESS) {
    return;
  }
}

static void
cujoagent_device_connected_handler(__attribute__((unused)) rbusHandle_t handle,
                                   rbusEvent_t const *event,
                                   rbusEventSubscription_t *subscription) {
  cujoagent_wifi_consumer_t *consumer = subscription->userData;

  wifi_station_event_context_t ctx = {0};
  cujoagent_new_station_event_context(&ctx, CUJO_FPC_CONNECT, event,
                                      subscription);

  cujoagent_push_to_consumer_queue(consumer, &ctx, sizeof(ctx),
                                   consumer_event_type_station_update,
                                   consumer_event_sta_connect);
}

static void cujoagent_device_disconnected_handler(
    __attribute__((unused)) rbusHandle_t handle, rbusEvent_t const *event,
    rbusEventSubscription_t *subscription) {
  cujoagent_wifi_consumer_t *consumer = subscription->userData;

  wifi_station_event_context_t ctx = {0};
  cujoagent_new_station_event_context(&ctx, CUJO_FPC_DISCONNECT, event,
                                      subscription);

  cujoagent_push_to_consumer_queue(consumer, &ctx, sizeof(ctx),
                                   consumer_event_type_station_update,
                                   consumer_event_sta_disconnect);
}

static int cujoagent_fill_subscription(rbusEventSubscription_t *consumer_subs,
                                       unsigned int idx,
                                       char const *filler_name,
                                       rbusEventSubscription_t *filler_sub) {
  rbusEventSubscription_t *sub = &consumer_subs[idx];
  *sub = *filler_sub;
  sub->eventName = strdup(filler_name);
  if (sub->eventName == NULL) {
    CcspTraceError(("Failed to allocate the consumer subscription name\n"));
    return -1;
  }

  return 0;
}

static rbusError_t
cujoagent_rbus_subscribe(cujoagent_wifi_consumer_t *consumer) {
  /* WIFI_WEBCONFIG_DOC_DATA_SOUTH:
   *    _to_ OneWifi. Mentioned for the reference. Changes to subdocs coming
   *    from e.g. ovsdb or e.g. dml.
   *
   * WIFI_WEBCONFIG_DOC_DATA_NORTH:
   *    _from_ OneWifi. Basically any of the webconfig_subdoc_type_t subdocs.
   *
   * WIFI_WEBCONFIG_GET_ASSOC:
   *    "AddAssociatedClients" for connected clients.
   *    "RemoveWiFiAssociatedClients" for disconnected clients.
   *
   * DEV_WIFI_EVENTS_VAP_FRAMES_MGMT:
   *    RDK metadata + IEEE802 mgmt frame.
   *
   * WIFI_ACCESSPOINT_DEVICE_CONNECTED:
   *    Raw binary connected client MAC address.
   *
   * WIFI_ACCESSPOINT_DEVICE_DISCONNECTED:
   *    Raw binary disconnected client MAC address. */
  rbusEventSubscription_t filler_subs[] = {
      /* event name, filter, interval, duration, handler, user data, handle, async handler, publish on subscribe */
      {WIFI_WEBCONFIG_DOC_DATA_NORTH, NULL, 0, 0, cujoagent_webconfig_handler, consumer, NULL, NULL, false},
      {WIFI_WEBCONFIG_GET_ASSOC, NULL, 0, 0, cujoagent_webconfig_handler, consumer, NULL, NULL, false},
      {DEV_WIFI_EVENTS_VAP_FRAMES_MGMT, NULL, 0, 0, cujoagent_frame_events_handler, consumer, NULL, NULL, false},
      {WIFI_ACCESSPOINT_DEVICE_CONNECTED, NULL, 0, 0, cujoagent_device_connected_handler, consumer, NULL, NULL, false},
      {WIFI_ACCESSPOINT_DEVICE_DISCONNECTED, NULL, 0, 0, cujoagent_device_disconnected_handler, consumer, NULL, NULL, false},
  };
  size_t filler_subs_count = sizeof(filler_subs) / sizeof(*filler_subs);

  wifi_platform_property_t *wifi_prop = &consumer->hal_cap.wifi_prop;
  if (!wifi_prop) {
    CcspTraceError(("Wifi property is invalid\n"));
    return RBUS_ERROR_BUS_ERROR;
  }

  unsigned int vap_subs_count = 0;
  unsigned int *vap_subs_indexes = NULL;
  for (unsigned int i = 0; i < wifi_prop->numRadios * MAX_NUM_VAP_PER_RADIO; i++) {
    if (strcmp(wifi_prop->interface_map[i].bridge_name, PRIVATE_BRIDGE) == 0) {
      vap_subs_count++;
      unsigned int *tmp = reallocarray(vap_subs_indexes, vap_subs_count,
                                       sizeof *vap_subs_indexes);
      if (tmp == NULL) {
        CcspTraceError(("Failed to reallocate vaps indexes\n"));
        free(vap_subs_indexes);
        return RBUS_ERROR_BUS_ERROR;
      }
      vap_subs_indexes = tmp;
      vap_subs_indexes[vap_subs_count - 1] = wifi_prop->interface_map[i].index;
    }
  }

  consumer->subscriptions_count = 0;
  for (int i = 0; i < (int)filler_subs_count; i++) {
    switch (i) {
    case 0: // WIFI_WEBCONFIG_DOC_DATA_NORTH
    case 1: // WIFI_WEBCONFIG_GET_ASSOC
      consumer->subscriptions_count++;
      break;
    case 2: // DEV_WIFI_EVENTS_VAP_FRAMES_MGMT
    case 3: // WIFI_ACCESSPOINT_DEVICE_CONNECTED
    case 4: // WIFI_ACCESSPOINT_DEVICE_DISCONNECTED
      consumer->subscriptions_count += vap_subs_count;
      break;
    default:
      break;
    }
  }

  consumer->subscriptions = calloc(1, sizeof(rbusEventSubscription_t) *
                                          consumer->subscriptions_count);
  if (consumer->subscriptions == NULL) {
    CcspTraceError(("Failed to allocate the subscriptions\n"));
    /* CID 339680 Resource leak  */
    free(vap_subs_indexes);
    return RBUS_ERROR_BUS_ERROR;
  }

  int count = 0;
  unsigned int subs_idx = 0;
  char buf[RBUS_MAX_NAME_LENGTH] = {0};
  char const *filler_name = NULL;
  for (int i = 0; i < (int)filler_subs_count; i++) {
    if (subs_idx >= consumer->subscriptions_count) {
      CcspTraceError(
          ("Subscription index [%u] is greater than subscriptions count [%u]\n",
           subs_idx, consumer->subscriptions_count));
      break;
    }

    filler_name = filler_subs[i].eventName;
    switch (i) {
    case 0: // WIFI_WEBCONFIG_DOC_DATA_NORTH
    case 1: // WIFI_WEBCONFIG_GET_ASSOC
      cujoagent_fill_subscription(consumer->subscriptions, subs_idx,
                                  filler_name, &filler_subs[i]);
      subs_idx++;
      break;
    case 2: // DEV_WIFI_EVENTS_VAP_FRAMES_MGMT
    case 3: // WIFI_ACCESSPOINT_DEVICE_CONNECTED
    case 4: // WIFI_ACCESSPOINT_DEVICE_DISCONNECTED
      for (unsigned int j = 0; j < vap_subs_count; j++) {
        count = snprintf(buf, RBUS_MAX_NAME_LENGTH, filler_name,
                         vap_subs_indexes[j] + 1);
        if (count < 0 || count >= RBUS_MAX_NAME_LENGTH) {
          CcspTraceError(("Name [%s] doesn't fit into buffer\n", filler_name));
          return RBUS_ERROR_BUS_ERROR;
        }
        cujoagent_fill_subscription(consumer->subscriptions, subs_idx,
                                    buf, &filler_subs[i]);
        subs_idx++;
      }
      break;
    default:
      break;
    }
  }

  free(vap_subs_indexes);

  rbusError_t err = rbusEvent_SubscribeEx(consumer->rbus_handle,
                                          consumer->subscriptions,
                                          consumer->subscriptions_count, 0);
  if (err) {
    CcspTraceError(("Unable to subscribe to event(s): [%d]\n", err));
  }

  return err;
}

int cujoagent_consumer_initialize(cujoagent_wifi_consumer_t *consumer) {
  if (!consumer) {
    return -1;
  }

  if (!(!cujoagent_consumer_init(consumer) &&
        !cujoagent_spawn_consumer_loop(consumer) &&
        !cujoagent_spawn_socket_loop(consumer))) {
    cujoagent_wifidatacollection_deinit(consumer, FALSE);
    return -1;
  }

  return 0;
}

int cujoagent_rbus_initialize(cujoagent_wifi_consumer_t *consumer) {
  if (!consumer) {
    return -1;
  }

  if (rbus_open(&consumer->rbus_handle, RBUS_CONSUMER_NAME) !=
      RBUS_ERROR_SUCCESS) {
    return -1;
  }

  /* Order matters here:
   *  Get the WIFI_WEBCONFIG_INIT_DATA_NAMESPACE first, so that the appropriate
   *  wifi data is present in the consumer before any subscriptions happen.
   *
   *  Query full assoc list after subscribing to WIFI_WEBCONFIG_GET_ASSOC.
   *  This ensures no stations are missed in the assoc list maintained in the
   *  consumer. Of course, at the small price of potentially missing some
   *  connects/disconnects happening right after subscribing, but before we
   *  sync the full assoc list. */
  if (!(!cujoagent_webconfig_init_get(consumer) &&
        !cujoagent_rbus_subscribe(consumer) &&
        !cujoagent_assoc_list_init_get(consumer))) {
    cujoagent_wifidatacollection_deinit(consumer, FALSE);
    return -1;
  }

  return 0;
}

int cujoagent_wifidatacollection_init(cujoagent_wifi_consumer_t *consumer) {
  if (!consumer) {
    return -1;
  }

  CcspTraceInfo(("Initializing wifi data collection consumer\n"));
  if (cujoagent_consumer_initialize(g_cujoagent_dcl) != 0) {
    CcspTraceError(("Failed to initialize wifi data collection consumer!\n"));
    return -1;
  }

  CcspTraceInfo(("Initializing wifi data collection rbus\n"));
  if (cujoagent_rbus_initialize(g_cujoagent_dcl) != 0) {
    CcspTraceError(("Failed to initialize wifi data collection rbus!\n"));
    return -1;
  }

  return 0;
}

int cujoagent_wifidatacollection_deinit(cujoagent_wifi_consumer_t *consumer, bool do_rbus_event_unsubscribe) {
  if (!consumer) {
    return -1;
  }

  if (do_rbus_event_unsubscribe) {
    rbusEvent_UnsubscribeEx(consumer->rbus_handle,
                            consumer->subscriptions,
                            consumer->subscriptions_count);
  }

  /* We _definitely_ would like to _avoid_ canceling or exiting the thread and
   * then dealing with clean-ups. Therefore, set the relevant predicate(s) and
   * signal the condition to allow the thread start function to return. */
  pthread_mutex_lock(&consumer->lock);
  consumer->exit_consumer = true;
  consumer->queue_wakeup = true;
  pthread_mutex_unlock(&consumer->lock);
  pthread_cond_signal(&consumer->cond);

  /* To avoid thread canceling simply break the epoll_wait() loop to return the
   * thread start function. For the cases when the agent hello-version is in
   * progress, the thread will error out on a closed socket and proceed to the
   * return anyway. */
  cujoagent_write_event(consumer->efd_c, NOTIFY_SOCKET_THREAD_STOP);
  cujoagent_wait_for_event(consumer->epfd_c, NOTIFY_SOCKET_THREAD_RETURN, EPOLL_TIMEOUT_MS);
  if (consumer->sock_fd >= 0) {
    close(consumer->sock_fd);
    consumer->sock_fd = -1;
  }

  cujoagent_free_all_associated_devices_maps(
      consumer->radios, consumer->hal_cap.wifi_prop.numRadios);
  cujoagent_consumer_deinit(consumer);
  return 0;
}
