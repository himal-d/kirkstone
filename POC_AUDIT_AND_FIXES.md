# Matter Protocol POC Audit & Fixes
## Raspberry Pi 4 + Thread + Wi-Fi POC

**Scope:** POC validation only - Production features OUT OF SCOPE

---

## POC Blocking Issues Identified

### 1. ❌ CRITICAL: chip-all-clusters-app Missing Thread Support
**Issue:** `chip-all-clusters-app.bb` doesn't enable Thread (only lighting-app has it)
**Impact:** Cannot commission Thread devices with all-clusters-app
**Location:** `meta-rdk-matter/recipes-matter/chip-all-clusters-app/chip-all-clusters-app.bb`

### 2. ❌ CRITICAL: Hardcoded Thread RCP Device Path
**Issue:** `/dev/ttyACM0` hardcoded in:
- `otbr-agent-wrapper.sh` (line 7)
- `ot-daemon.service` (line 7)
- `wpantund.conf` (line 19)
**Impact:** Will fail if RCP device is on different path
**Fix:** Add device detection or make configurable

### 3. ❌ CRITICAL: Hardcoded Bridge Interface
**Issue:** `brlan0` hardcoded in `otbr-agent-wrapper.sh` (line 9)
**Impact:** Raspberry Pi 4 doesn't use `brlan0` - typically uses `eth0` or `wlan0`
**Fix:** Detect or configure bridge interface

### 4. ⚠️ HIGH: Service Startup Order
**Issue:** Matter apps don't wait for OTBR to be ready
**Impact:** Apps may start before Thread network is available
**Fix:** Add proper systemd dependencies

### 5. ⚠️ HIGH: Hardcoded Pairing Code
**Issue:** `chip-tool.service` has hardcoded pairing code `20202021`
**Impact:** Security risk (but acceptable for POC)
**Fix:** Make configurable via environment variable

### 6. ⚠️ MEDIUM: DEPLOY_TRUSTY Variable
**Issue:** Referenced but never defined (11 recipes)
**Impact:** May cause build warnings/errors
**Fix:** Define default value

### 7. ⚠️ MEDIUM: Thread Interface Configuration
**Issue:** `wpan0` hardcoded - may not exist if OTBR not started
**Impact:** Matter apps may fail if Thread interface not ready
**Fix:** Add interface readiness check

---

## FIXES

### Fix 1: Enable Thread in chip-all-clusters-app

**File:** `meta-rdk-matter/recipes-matter/chip-all-clusters-app/chip-all-clusters-app.bb`

**Change:** Add Thread configuration flags to `target_cflags`:

```bitbake
target_cflags=[
    "-DCHIP_DEVICE_CONFIG_WIFI_STATION_IF_NAME=\"wlan0\"",
    "-DCHIP_DEVICE_CONFIG_LINUX_DHCPC_CMD=\"udhcpc -b -i %s \"",
    "-DCHIP_DEVICE_CONFIG_THREAD_INTERFACE_NAME=\"wpan0\"",
    "-DCHIP_DEVICE_CONFIG_ENABLE_WIFI=1",
    "-DCHIP_DEVICE_CONFIG_ENABLE_THREAD=1",
]
```

### Fix 2: Make Thread RCP Device Configurable

**File:** `meta-rdk-matter/recipes-thread/ot-br-posix/files/otbr-agent-wrapper.sh`

**Change:** Add device detection with fallback:

```bash
#!/bin/bash
set -e

# ==========================
# Configuration
# ==========================
# Try to detect RCP device, fallback to common paths
detect_rcp_device() {
    # Check common paths
    for dev in /dev/ttyACM0 /dev/ttyUSB0 /dev/ttyACM1; do
        if [ -e "$dev" ]; then
            # Verify it's a serial device
            if [ -c "$dev" ]; then
                echo "$dev"
                return 0
            fi
        fi
    done
    # Use environment variable if set
    if [ -n "$RCP_DEVICE" ]; then
        echo "$RCP_DEVICE"
        return 0
    fi
    # Default fallback
    echo "/dev/ttyACM0"
}

RCP_DEVICE=$(detect_rcp_device)
WPAN_IF="wpan0"
# For Raspberry Pi 4, use eth0 as bridge (or wlan0 if WiFi-only)
# Can be overridden via BRIDGE_IF environment variable
BR_IF="${BRIDGE_IF:-eth0}"
OTBR_AGENT_BIN="/usr/sbin/otbr-agent"

# ... rest of script unchanged ...
```

### Fix 3: Fix Bridge Interface for Raspberry Pi 4

**File:** `meta-rdk-matter/recipes-thread/ot-br-posix/files/otbr-agent-wrapper.sh`

**Change:** Update bridge interface detection:

```bash
# Detect bridge interface for Raspberry Pi 4
detect_bridge_interface() {
    # Check for common bridge interfaces
    for iface in eth0 wlan0 br0; do
        if ip link show "$iface" &>/dev/null 2>&1; then
            # Prefer eth0 (wired) over wlan0
            if [ "$iface" = "eth0" ]; then
                echo "$iface"
                return 0
            fi
        fi
    done
    # Use environment variable if set
    if [ -n "$BRIDGE_IF" ]; then
        echo "$BRIDGE_IF"
        return 0
    fi
    # Default to eth0 for Raspberry Pi 4
    echo "eth0"
}

BR_IF=$(detect_bridge_interface)
```

### Fix 4: Fix Service Dependencies

**File:** `meta-rdk-matter/recipes-matter/chip-lighting-app/files/chip-lighting-app.service`

**Change:** Add OTBR dependency:

```systemd
[Unit]
Description=Chip Lighting App for Matter IoT
After=network-online.target avahi-daemon.service dbus.service ot-br-posix.service
Wants=network-online.target
Requires=avahi-daemon.service

[Service]
Type=simple
ExecStartPre=/bin/sh -c 'while ! ip link show wpan0 >/dev/null 2>&1; do sleep 1; done'
ExecStart=/usr/bin/chip-lighting-app
Restart=on-failure
RestartSec=3
Environment=CHIP_DEVICE_CONFIG_WIFI_STATION_IF_NAME="wlan0"
Environment=CHIP_DEVICE_CONFIG_LINUX_DHCPC_CMD="udhcpc -b -i %s"
Environment=CHIP_DEVICE_CONFIG_THREAD_INTERFACE_NAME="wpan0"
StandardOutput=journal
StandardError=journal
LimitNOFILE=65536

[Install]
WantedBy=multi-user.target
```

**File:** `meta-rdk-matter/recipes-matter/chip-all-clusters-app/files/chip-all-clusters-app.service`

**Change:** Add OTBR dependency and Thread interface wait:

```systemd
[Unit]
Description=Chip All Cluster App for Matter IoT
After=network-online.target avahi-daemon.service dbus.service ot-br-posix.service
Wants=network-online.target
Requires=avahi-daemon.service

[Service]
Type=simple
ExecStartPre=/bin/sh -c 'while ! ip link show wpan0 >/dev/null 2>&1; do sleep 1; done'
ExecStart=/usr/bin/chip-all-clusters-app
Restart=on-failure
RestartSec=3
Environment=CHIP_DEVICE_CONFIG_WIFI_STATION_IF_NAME="wlan0"
Environment=CHIP_DEVICE_CONFIG_LINUX_DHCPC_CMD="udhcpc -b -i %s"
Environment=CHIP_DEVICE_CONFIG_THREAD_INTERFACE_NAME="wpan0"
StandardOutput=journal
StandardError=journal
LimitNOFILE=65536
PIDFile=/var/run/chip-all-clusters-app.pid

[Install]
WantedBy=multi-user.target
```

### Fix 5: Make Pairing Code Configurable

**File:** `meta-rdk-matter/recipes-matter/matter/files/chip-tool.service`

**Change:** Use environment variable:

```systemd
[Unit]
Description=Chip Tool for Matter IoT
After=network-online.target avahi-daemon.service
Wants=network-online.target

[Service]
ExecStart=/usr/bin/chip-tool pairing onnetwork 1 ${MATTER_PAIRING_CODE:-20202021}
Restart=on-failure
RestartSec=5
User=root
Group=root
Environment=CHIP_DEVICE_CONFIG_WIFI_STATION_IF_NAME="wlan0"
Environment=CHIP_DEVICE_CONFIG_LINUX_DHCPC_CMD="udhcpc -b -i %s"
Environment=MATTER_PAIRING_CODE=20202021
StandardOutput=journal
StandardError=journal

[Install]
WantedBy=multi-user.target
```

### Fix 6: Fix DEPLOY_TRUSTY Variable

**File:** `meta-rdk-matter/recipes-matter/matter-common/matter-common.inc`

**Add at top of file:**

```bitbake
# Trusty deployment flag (default: false for POC)
DEPLOY_TRUSTY ??= "false"
```

### Fix 7: Fix ot-daemon.service RCP Path

**File:** `meta-rdk-matter/recipes-thread/ot-daemon/files/ot-daemon.service`

**Note:** This service may not be needed if using otbr-agent. But if used:

```systemd
[Unit]
Description=OpenThread Daemon (ot-daemon) - Thread RCP bridge
After=network.target

[Service]
Type=simple
# Use environment variable or detect device
ExecStartPre=/bin/sh -c 'RCP_DEV=${RCP_DEVICE:-/dev/ttyACM0}; [ -e "$RCP_DEV" ] || exit 1'
ExecStart=/usr/sbin/ot-daemon -v 'spinel+hdlc+uart://${RCP_DEVICE:-/dev/ttyACM0}?baudrate=115200' -I wpan0
Environment=RCP_DEVICE=/dev/ttyACM0

[Install]
WantedBy=multi-user.target
```

---

## POC Commissioning Guide

### Prerequisites
1. Raspberry Pi 4 with Thread RCP (e.g., nRF52840 dongle) connected
2. Thread RCP device at `/dev/ttyACM0` (or set `RCP_DEVICE` env var)
3. Wi-Fi connected on `wlan0` (or configure interface name)
4. All services enabled and running

### Step 1: Verify Thread Border Router

```bash
# Check OTBR service status
systemctl status ot-br-posix.service

# Check Thread interface
ip link show wpan0

# Check OTBR agent
ot-ctl state
ot-ctl thread start
ot-ctl ifconfig up
ot-ctl thread start
```

### Step 2: Verify Matter Apps

```bash
# Check lighting-app
systemctl status chip-lighting-app.service

# Check all-clusters-app
systemctl status chip-all-clusters-app.service

# Verify apps can see Thread network
journalctl -u chip-lighting-app -f
```

### Step 3: Commission Aqara Thread Bulb

```bash
# Put bulb in pairing mode (follow Aqara instructions)

# Commission using chip-tool
chip-tool pairing ble-thread 1 hex:<OPERATIONAL_DATASET> <PIN_CODE> <DISCRIMINATOR>

# Or if using onnetwork commissioning:
chip-tool pairing onnetwork 1 <PIN_CODE>

# Verify device is commissioned
chip-tool pairing list

# Control the bulb
chip-tool onoff on 1 1
chip-tool onoff off 1 1
```

### Step 4: Commission Wi-Fi Matter Device

```bash
# Commission Wi-Fi device
chip-tool pairing onnetwork <NODE_ID> <PIN_CODE>

# Verify
chip-tool pairing list

# Control device
chip-tool onoff on <NODE_ID> 1
```

### Step 5: Verify Persistence After Reboot

```bash
# Reboot device
reboot

# After reboot, verify services start
systemctl status ot-br-posix.service
systemctl status chip-lighting-app.service

# Verify devices still commissioned
chip-tool pairing list

# Test control
chip-tool onoff on 1 1
```

---

## Runtime Verification Checklist

### Pre-Commissioning
- [ ] OTBR service running: `systemctl status ot-br-posix`
- [ ] Thread interface exists: `ip link show wpan0`
- [ ] Thread network started: `ot-ctl state` shows "detached" or "child"
- [ ] Avahi/mDNS running: `systemctl status avahi-daemon`
- [ ] Matter app running: `systemctl status chip-lighting-app`
- [ ] Matter app logs show Thread enabled: `journalctl -u chip-lighting-app | grep -i thread`

### Thread Commissioning
- [ ] Aqara bulb in pairing mode
- [ ] Commission command succeeds
- [ ] Device appears in pairing list: `chip-tool pairing list`
- [ ] Can control device: `chip-tool onoff on 1 1`

### Wi-Fi Commissioning
- [ ] Wi-Fi device in pairing mode
- [ ] Commission command succeeds
- [ ] Device appears in pairing list
- [ ] Can control device

### Post-Reboot
- [ ] All services auto-start
- [ ] Thread network restores
- [ ] Commissioned devices still in list
- [ ] Can control devices after reboot

---

## Troubleshooting

### Thread Interface Not Found
```bash
# Check RCP device
ls -l /dev/ttyACM*

# Check OTBR logs
journalctl -u ot-br-posix -f

# Manually start OTBR
/usr/local/bin/otbr-agent-wrapper.sh
```

### Matter App Can't See Thread
```bash
# Verify Thread interface is up
ip link show wpan0

# Check Matter app logs
journalctl -u chip-lighting-app -f | grep -i thread

# Verify Thread is enabled in build
strings /usr/bin/chip-lighting-app | grep -i thread
```

### Commissioning Fails
```bash
# Check mDNS
avahi-browse -a

# Check Matter app logs
journalctl -u chip-lighting-app -f

# Verify pairing code
echo $MATTER_PAIRING_CODE
```

### Services Don't Start After Reboot
```bash
# Check service dependencies
systemctl list-dependencies chip-lighting-app.service

# Check service logs
journalctl -u chip-lighting-app -b

# Verify OTBR started first
systemctl status ot-br-posix.service
```

---

## File Changes Summary

1. ✅ `chip-all-clusters-app.bb` - Add Thread support
2. ✅ `otbr-agent-wrapper.sh` - Device detection, bridge interface detection
3. ✅ `chip-lighting-app.service` - Add OTBR dependency, Thread interface wait
4. ✅ `chip-all-clusters-app.service` - Add OTBR dependency, Thread interface wait
5. ✅ `chip-tool.service` - Configurable pairing code
6. ✅ `matter-common.inc` - Define DEPLOY_TRUSTY
7. ✅ `ot-daemon.service` - Configurable RCP device (if used)

---

**Next Steps:**
1. Apply code fixes
2. Rebuild Yocto image
3. Flash to Raspberry Pi 4
4. Follow commissioning guide
5. Verify checklist items

