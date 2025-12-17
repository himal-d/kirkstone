#ifndef CUJOAGENT_DCL_API_H
#define CUJOAGENT_DCL_API_H

#include <endian.h>
#include <inttypes.h>
#include <libgen.h>
#include <limits.h>

#include <netinet/ether.h>
#include <sys/epoll.h>
#include <sys/eventfd.h>
#include <sys/socket.h>
#include <sys/uio.h>
#include <sys/un.h>

#include "ccsp_trace.h"
#include "secure_wrapper.h"
#include "user_base.h"

#include "wifi_webconfig.h"

#include "fingerprint-connection-proto.h"

#define RBUS_CONSUMER_NAME              "wifi-data-collection-consumer"

#ifdef NON_PRIVILEGED
#define CCSP_CUJOAGENT_SOCK_PATH        "/tmp/wifi.sock"
#else
#define CCSP_CUJOAGENT_SOCK_PATH        "/var/run/cujo/wifi.sock"
#endif

#define PRIVATE_BRIDGE                  "brlan0"
#ifdef INTEL_PUMA7
#define WIFI_WEBCONFIG_INIT_DATA_NAMESPACE WIFI_WEBCONFIG_INIT_DML_DATA
#else
#define WIFI_WEBCONFIG_INIT_DATA_NAMESPACE WIFI_WEBCONFIG_INIT_DATA
#endif

#define DEV_WIFI_EVENTS_VAP_FRAMES_MGMT                                        \
  "Device.WiFi.Events.VAP.%d.Frames.Mgmt"
#define WIFI_ACCESSPOINT_DEVICE_CONNECTED                                      \
  "Device.WiFi.AccessPoint.%d.X_RDK_deviceConnected"
#define WIFI_ACCESSPOINT_DEVICE_DISCONNECTED                                   \
  "Device.WiFi.AccessPoint.%d.X_RDK_deviceDisconnected"

#define MSECS_PER_SEC           1000
#define USECS_PER_MSEC          1000
#define NANOSECS_PER_MSEC       1000000

#define EPOLL_TIMEOUT_MS        1000
#define MAX_EPOLL_EVENTS        2
#define MAX_SOCK_RECV_BUFFER    1024

#define MAC_DOT_FMT             "%02hhx:%02hhx:%02hhx:%02hhx:%02hhx:%02hhx"
#define MAX_MAC_STR_LEN         17

#define FCTL_FTYPE              0x000c
#define FCTL_STYPE              0x00f0

#define STYPE_ASSOC_REQ         0x0000
#define STYPE_ASSOC_RESP        0x0010
#define STYPE_REASSOC_REQ       0x0020
#define STYPE_REASSOC_RESP      0x0030
#define STYPE_PROBE_REQ         0x0040
#define STYPE_PROBE_RESP        0x0050
#define STYPE_BEACON            0x0080
#define STYPE_ATIM              0x0090
#define STYPE_DISASSOC          0x00A0
#define STYPE_AUTH              0x00B0
#define STYPE_DEAUTH            0x00C0
#define STYPE_ACTION            0x00D0

#define FC_GET_TYPE(fc)         (((fc) & (FCTL_FTYPE)) >> 2)
#define FC_GET_STYPE(fc)        (((fc) & (FCTL_STYPE)) >> 4)

#define EMPTY_RT_LEN            0x08

typedef enum {
  NOTIFY_NONE,
  NOTIFY_WEBCONFIG_INIT_READY,
  NOTIFY_RADIO_DATA_READY,
  NOTIFY_RADIO_DATA_SENT,
  NOTIFY_STATION_DATA_READY,
  NOTIFY_STATION_DATA_SENT,
  NOTIFY_BATCH_DATA_READY,
  NOTIFY_BATCH_DATA_SENT,
  NOTIFY_SOCKET_THREAD_STOP,
  NOTIFY_SOCKET_THREAD_RETURN,
} cujoagent_notify_t;

typedef enum {
  consumer_event_type_webconfig,
  consumer_event_type_station_update,
  consumer_event_type_mgmt_frame,
} cujoagent_consumer_event_type_t;

typedef enum {
  consumer_event_webconfig_init,
  consumer_event_webconfig_set_data,
  consumer_event_webconfig_get_data,
  consumer_event_sta_connect,
  consumer_event_sta_disconnect,
  consumer_event_probe_req,
  consumer_event_auth,
  consumer_event_assoc_req,
  consumer_event_reassoc_req,
} cujoagent_consumer_event_subtype_t;

typedef struct {
  cujoagent_consumer_event_type_t event_type;
  cujoagent_consumer_event_subtype_t event_subtype;
  void *msg;
  size_t mlen;
} __attribute__((__packed__)) cujoagent_wifi_consumer_event_t;

typedef struct {
  enum cujo_fpc_event_type event_type;
  uint64_t timestamp_ms;
  unsigned int vap_index;
  struct ether_addr station_mac;
} __attribute__((__packed__)) wifi_station_event_context_t;

typedef struct {
  struct cujo_fpc_tlv *tlv;
  size_t size;
} __attribute__((__packed__)) cujoagent_tlv_context_t;

typedef struct {
  pthread_mutex_t lock;
  pthread_cond_t cond;

  queue_t *queue;
  bool queue_wakeup;
  queue_t *assoc_disassoc_events;

  wifi_global_config_t config;
  wifi_hal_capability_t hal_cap;
  rdk_wifi_radio_t radios[MAX_NUM_RADIOS];

  webconfig_t webconfig;
  rbusHandle_t rbus_handle;
  rbusEventSubscription_t *subscriptions;
  unsigned int subscriptions_count;

  int sock_fd;

  /* Epoll and event fd's for the consumer queue to notify the main thread
   * that the initial webconfig processing is done */
  int epfd_m;
  int efd_m;

  /* Epoll and event fd's for: 1) the main consumer queue notifying the comms
   * socket loop that the tlv data is ready 2) waiting for the notification from
   * the comms socket loop that the sending of tlv has finished. */
  int epfd_c;
  int efd_c;

  /* Epoll and event fd's for: 1) the comms socket loop to wait for the tlv data
   * ready 2) notifying the main consumer queue that tlv finished sending.*/
  int epfd_s;
  int efd_s;

  bool comms_ready;
  cujoagent_tlv_context_t tlv_ctx;

  bool exit_consumer;
} cujoagent_wifi_consumer_t;

extern cujoagent_wifi_consumer_t *g_cujoagent_dcl;

int cujoagent_consumer_initialize(cujoagent_wifi_consumer_t *consumer);
int cujoagent_rbus_initialize(cujoagent_wifi_consumer_t *consumer);

int cujoagent_wifidatacollection_init(cujoagent_wifi_consumer_t *consumer);
int cujoagent_wifidatacollection_deinit(cujoagent_wifi_consumer_t *consumer, bool do_rbus_event_unsubscribe);
#endif
