# POC Commissioning Audit & Fixes
## Raspberry Pi 4 Matter Commissioning Issues

---

## 🔴 CRITICAL ISSUES BLOCKING COMMISSIONING

### Issue 1: chip-tool.service Auto-Runs Pairing Command
**Location:** `meta-rdk-matter/recipes-matter/chip-tool/files/chip-tool.service`
**Problem:** Service automatically runs `pairing onnetwork 1 20202021` on startup
**Impact:** ❌ Prevents manual commissioning, conflicts with device commissioning
**Fix:** Remove auto-pairing, make service manual/interactive

### Issue 2: chip-tool Missing Thread Support
**Location:** `meta-rdk-matter/recipes-matter/chip-tool/chip-tool.bb`
**Problem:** Thread configuration flags not enabled in build
**Impact:** ❌ Cannot commission Thread devices
**Fix:** Add Thread enable flags to chip-tool build

### Issue 3: Missing Thread Operational Dataset Helper
**Problem:** No script to extract OTBR operational dataset for Thread commissioning
**Impact:** ❌ Cannot get Thread network credentials for BLE-Thread commissioning
**Fix:** Create helper script to extract operational dataset

### Issue 4: chip-tool Service Missing OTBR Dependency
**Location:** `meta-rdk-matter/recipes-matter/chip-tool/files/chip-tool.service`
**Problem:** Service doesn't wait for OTBR/Thread network
**Impact:** ⚠️ May fail if Thread network not ready
**Fix:** Add OTBR dependency

### Issue 5: Missing Commissioning Helper Script
**Problem:** No convenient script for commissioning Thread/Wi-Fi devices
**Impact:** ⚠️ Manual commissioning is error-prone
**Fix:** Create commissioning helper script

---

## ✅ FIXES TO APPLY

### Fix 1: Remove Auto-Pairing from chip-tool.service

**File:** `meta-rdk-matter/recipes-matter/chip-tool/files/chip-tool.service`

**Change:** Remove ExecStart pairing command, make it a simple service that doesn't auto-run

```systemd
[Unit]
Description=Chip Tool for Matter IoT (Manual Commissioning Tool)
After=network-online.target avahi-daemon.service ot-br-posix.service
Wants=network-online.target

[Service]
Type=oneshot
RemainAfterExit=yes
# Don't auto-run pairing - user must run manually
ExecStart=/bin/true
Environment=CHIP_DEVICE_CONFIG_WIFI_STATION_IF_NAME="wlan0"
Environment=CHIP_DEVICE_CONFIG_LINUX_DHCPC_CMD="udhcpc -b -i %s"
Environment=CHIP_DEVICE_CONFIG_THREAD_INTERFACE_NAME="wpan0"
StandardOutput=journal
StandardError=journal

[Install]
WantedBy=multi-user.target
```

**Justification:** chip-tool should be available but not auto-commission. User runs commands manually.

---

### Fix 2: Enable Thread Support in chip-tool Build

**File:** `meta-rdk-matter/recipes-matter/chip-tool/chip-tool.bb`

**Change:** Add Thread configuration to `target_cflags`:

```bitbake
target_cflags=[
    "-DCHIP_DEVICE_CONFIG_WIFI_STATION_IF_NAME=\"wlan0\"",
    "-DCHIP_DEVICE_CONFIG_LINUX_DHCPC_CMD=\"udhcpc -b -i %s \"",
    "-DCHIP_DEVICE_CONFIG_THREAD_INTERFACE_NAME=\"wpan0\"",
    "-DCHIP_DEVICE_CONFIG_ENABLE_WIFI=1",
    "-DCHIP_DEVICE_CONFIG_ENABLE_THREAD=1",
]
```

**Justification:** Required for Thread device commissioning in POC.

---

### Fix 3: Create Thread Operational Dataset Helper Script

**New File:** `meta-rdk-matter/recipes-thread/ot-br-posix/files/get-thread-dataset.sh`

**Content:**
```bash
#!/bin/bash
# Get OpenThread operational dataset for Matter Thread commissioning
# Usage: get-thread-dataset.sh

set -e

echo "Getting OpenThread operational dataset..."
echo ""

# Check if ot-ctl is available
if ! command -v ot-ctl &> /dev/null; then
    echo "Error: ot-ctl not found. Is ot-daemon running?"
    exit 1
fi

# Get active operational dataset
DATASET=$(ot-ctl dataset active -x 2>/dev/null | grep -v "Done" | tr -d '\n' | tr -d ' ')

if [ -z "$DATASET" ]; then
    echo "Error: Could not get operational dataset. Is Thread network started?"
    echo "Try: ot-ctl thread start"
    exit 1
fi

echo "Operational Dataset (hex):"
echo "$DATASET"
echo ""
echo "Use this for BLE-Thread commissioning:"
echo "chip-tool pairing ble-thread <NODE_ID> hex:$DATASET <PIN_CODE> <DISCRIMINATOR>"
echo ""
echo "Or for onnetwork Thread commissioning (if device supports it):"
echo "chip-tool pairing onnetwork <NODE_ID> <PIN_CODE>"
```

**Installation:** Add to `ot-br-posix.bb` do_install

**Justification:** Required for Thread device commissioning - need operational dataset.

---

### Fix 4: Create Commissioning Helper Script

**New File:** `meta-rdk-matter/recipes-matter/chip-tool/files/matter-commission.sh`

**Content:**
```bash
#!/bin/bash
# Matter Device Commissioning Helper Script
# Usage: matter-commission.sh <type> <node_id> [pin_code] [discriminator]

set -e

TYPE=${1:-help}
NODE_ID=${2:-1}
PIN_CODE=${3:-}
DISCRIMINATOR=${4:-}

case "$TYPE" in
    thread-ble)
        if [ -z "$PIN_CODE" ] || [ -z "$DISCRIMINATOR" ]; then
            echo "Usage: matter-commission.sh thread-ble <node_id> <pin_code> <discriminator>"
            echo "Example: matter-commission.sh thread-ble 1 12345678 3840"
            exit 1
        fi
        
        # Get operational dataset
        if ! command -v ot-ctl &> /dev/null; then
            echo "Error: ot-ctl not found"
            exit 1
        fi
        
        DATASET=$(ot-ctl dataset active -x 2>/dev/null | grep -v "Done" | tr -d '\n' | tr -d ' ')
        
        if [ -z "$DATASET" ]; then
            echo "Error: Thread network not started. Run: ot-ctl thread start"
            exit 1
        fi
        
        echo "Commissioning Thread device (BLE-Thread)..."
        echo "Node ID: $NODE_ID"
        echo "PIN: $PIN_CODE"
        echo "Discriminator: $DISCRIMINATOR"
        echo ""
        
        chip-tool pairing ble-thread $NODE_ID hex:$DATASET $PIN_CODE $DISCRIMINATOR
        ;;
        
    thread-onnetwork)
        if [ -z "$PIN_CODE" ]; then
            echo "Usage: matter-commission.sh thread-onnetwork <node_id> <pin_code>"
            echo "Example: matter-commission.sh thread-onnetwork 1 12345678"
            exit 1
        fi
        
        echo "Commissioning Thread device (OnNetwork)..."
        echo "Node ID: $NODE_ID"
        echo "PIN: $PIN_CODE"
        echo ""
        
        chip-tool pairing onnetwork $NODE_ID $PIN_CODE
        ;;
        
    wifi)
        if [ -z "$PIN_CODE" ]; then
            echo "Usage: matter-commission.sh wifi <node_id> <pin_code>"
            echo "Example: matter-commission.sh wifi 2 12345678"
            exit 1
        fi
        
        echo "Commissioning Wi-Fi device..."
        echo "Node ID: $NODE_ID"
        echo "PIN: $PIN_CODE"
        echo ""
        
        chip-tool pairing onnetwork $NODE_ID $PIN_CODE
        ;;
        
    list)
        echo "Listing commissioned devices..."
        chip-tool pairing list
        ;;
        
    control-on)
        if [ -z "$NODE_ID" ] || [ "$NODE_ID" = "1" ]; then
            echo "Usage: matter-commission.sh control-on <node_id> <endpoint>"
            echo "Example: matter-commission.sh control-on 1 1"
            exit 1
        fi
        ENDPOINT=${3:-1}
        echo "Turning on device $NODE_ID endpoint $ENDPOINT..."
        chip-tool onoff on $NODE_ID $ENDPOINT
        ;;
        
    control-off)
        if [ -z "$NODE_ID" ] || [ "$NODE_ID" = "1" ]; then
            echo "Usage: matter-commission.sh control-off <node_id> <endpoint>"
            echo "Example: matter-commission.sh control-off 1 1"
            exit 1
        fi
        ENDPOINT=${3:-1}
        echo "Turning off device $NODE_ID endpoint $ENDPOINT..."
        chip-tool onoff off $NODE_ID $ENDPOINT
        ;;
        
    *)
        echo "Matter Commissioning Helper"
        echo ""
        echo "Usage: matter-commission.sh <command> [args...]"
        echo ""
        echo "Commands:"
        echo "  thread-ble <node_id> <pin> <discriminator>  - Commission Thread device via BLE"
        echo "  thread-onnetwork <node_id> <pin>            - Commission Thread device on-network"
        echo "  wifi <node_id> <pin>                         - Commission Wi-Fi device"
        echo "  list                                         - List commissioned devices"
        echo "  control-on <node_id> [endpoint]              - Turn device on"
        echo "  control-off <node_id> [endpoint]             - Turn device off"
        echo ""
        echo "Examples:"
        echo "  matter-commission.sh thread-ble 1 12345678 3840"
        echo "  matter-commission.sh wifi 2 87654321"
        echo "  matter-commission.sh list"
        echo "  matter-commission.sh control-on 1 1"
        ;;
esac
```

**Installation:** Add to `chip-tool.bb` do_install

**Justification:** Simplifies commissioning for POC demo - single script for all operations.

---

## 📋 COMMISSIONING PROCEDURE

### Pre-Commissioning Checklist

| Step | Command | Expected Result |
|------|---------|----------------|
| 1. Check OTBR | `systemctl status ot-br-posix` | Service active |
| 2. Check Thread interface | `ip link show wpan0` | Interface exists |
| 3. Start Thread network | `ot-ctl thread start` | Network started |
| 4. Check Thread state | `ot-ctl state` | Shows "child", "router", or "leader" |
| 5. Check Matter apps | `systemctl status chip-lighting-app` | Service active |
| 6. Check mDNS | `systemctl status avahi-daemon` | Service active |
| 7. Verify chip-tool | `chip-tool --help` | Tool available |

---

### Commissioning Aqara Thread Bulb (LB-L03E)

#### Method 1: BLE-Thread Commissioning (Recommended)

```bash
# Step 1: Put bulb in pairing mode (follow Aqara instructions)
# Typically: Power cycle 5 times quickly

# Step 2: Get Thread operational dataset
get-thread-dataset.sh
# Copy the hex dataset string

# Step 3: Commission via BLE-Thread
# Replace PIN_CODE and DISCRIMINATOR with bulb's values
matter-commission.sh thread-ble 1 <PIN_CODE> <DISCRIMINATOR>

# Or manually:
chip-tool pairing ble-thread 1 hex:<DATASET> <PIN_CODE> <DISCRIMINATOR>
```

#### Method 2: OnNetwork Commissioning (If Supported)

```bash
# Step 1: Put bulb in pairing mode

# Step 2: Commission on-network
matter-commission.sh thread-onnetwork 1 <PIN_CODE>

# Or manually:
chip-tool pairing onnetwork 1 <PIN_CODE>
```

#### Verification

```bash
# List commissioned devices
matter-commission.sh list
# Or: chip-tool pairing list

# Control bulb
matter-commission.sh control-on 1 1
matter-commission.sh control-off 1 1

# Or manually:
chip-tool onoff on 1 1
chip-tool onoff off 1 1
```

---

### Commissioning Wi-Fi Matter Device

```bash
# Step 1: Put device in pairing mode

# Step 2: Commission
matter-commission.sh wifi 2 <PIN_CODE>

# Or manually:
chip-tool pairing onnetwork 2 <PIN_CODE>

# Step 3: Verify
matter-commission.sh list

# Step 4: Control
matter-commission.sh control-on 2 1
```

---

## 🔍 TROUBLESHOOTING

### Commissioning Fails

**Check Thread Network:**
```bash
# Verify Thread network is running
ot-ctl state
# Should show: child, router, or leader

# If not, start it:
ot-ctl thread start
ot-ctl ifconfig up
```

**Check mDNS:**
```bash
# Check Avahi is running
systemctl status avahi-daemon

# Check Matter services discovered
avahi-browse -a | grep -i matter
```

**Check Device in Pairing Mode:**
- Aqara bulb: LED should blink or change color
- Verify PIN code and discriminator are correct

**Check Logs:**
```bash
# Matter app logs
journalctl -u chip-lighting-app -f

# chip-tool output
# Run commissioning with verbose output
chip-tool pairing onnetwork 1 <PIN> --verbose
```

### Thread Network Not Starting

```bash
# Check RCP device
ls -l /dev/ttyACM*

# Check OTBR service
systemctl status ot-br-posix
journalctl -u ot-br-posix -f

# Restart OTBR
systemctl restart ot-br-posix

# Check Thread interface
ip link show wpan0
```

### Device Not Discoverable

```bash
# Check mDNS
avahi-browse -a

# Check Matter app is advertising
journalctl -u chip-lighting-app | grep -i advertise

# Verify network connectivity
ping -c 3 <device_ip>
```

---

## 📊 VERIFICATION CHECKLIST

After commissioning, verify:

- [ ] Device appears in pairing list: `chip-tool pairing list`
- [ ] Device responds to control commands
- [ ] Thread device can be controlled: `chip-tool onoff on 1 1`
- [ ] Wi-Fi device can be controlled: `chip-tool onoff on 2 1`
- [ ] Devices persist after reboot: `reboot` then `chip-tool pairing list`

---

## 🔄 POST-REBOOT VERIFICATION

```bash
# After reboot, verify:

# 1. Services started
systemctl status ot-br-posix
systemctl status chip-lighting-app

# 2. Thread network restored
ot-ctl state
ip link show wpan0

# 3. Devices still commissioned
chip-tool pairing list

# 4. Devices still controllable
chip-tool onoff on 1 1
```

---

**Next:** Apply fixes and test commissioning procedure.

