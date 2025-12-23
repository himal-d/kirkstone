# Matter POC Commissioning Guide
## Raspberry Pi 4 + Aqara Thread Bulb + Wi-Fi Device

---

## Quick Start Checklist

### Pre-Flight Checks
```bash
# 1. Verify Thread RCP device
ls -l /dev/ttyACM*

# 2. Check OTBR service
systemctl status ot-br-posix.service

# 3. Verify Thread interface
ip link show wpan0

# 4. Check Matter app
systemctl status chip-lighting-app.service

# 5. Verify mDNS
systemctl status avahi-daemon.service
```

---

## Commissioning Aqara Thread Bulb (LB-L03E)

### Step 1: Put Bulb in Pairing Mode
- Follow Aqara instructions (typically: power cycle 5 times, or use Aqara app)

### Step 2: Verify Thread Network
```bash
# Check OTBR is running
systemctl status ot-br-posix.service

# Check Thread state
ot-ctl state
# Should show: detached, child, router, or leader

# Start Thread network if not started
ot-ctl thread start
ot-ctl ifconfig up
```

### Step 3: Commission Bulb
```bash
# Option A: OnNetwork commissioning (if bulb supports it)
chip-tool pairing onnetwork 1 <PIN_CODE>

# Option B: BLE-Thread commissioning (if bulb supports BLE)
# First get operational dataset from OTBR
OTBR_DATASET=$(ot-ctl dataset active -x)
chip-tool pairing ble-thread 1 hex:$OTBR_DATASET <PIN_CODE> <DISCRIMINATOR>

# Option C: Manual operational dataset
chip-tool pairing ble-thread 1 hex:<OPERATIONAL_DATASET> <PIN_CODE> <DISCRIMINATOR>
```

### Step 4: Verify Commissioning
```bash
# List commissioned devices
chip-tool pairing list

# Should show device with node ID 1
```

### Step 5: Control Bulb
```bash
# Turn on
chip-tool onoff on 1 1

# Turn off
chip-tool onoff off 1 1

# Read on/off state
chip-tool onoff read on-off 1 1

# Set brightness (if supported)
chip-tool levelcontrol move-to-level 128 0 0 0 1 1

# Set color temperature (CCT)
chip-tool colorcontrol movetocolortemperature 370 0 0 0 1 1
```

---

## Commissioning Wi-Fi Matter Device

### Step 1: Put Device in Pairing Mode
- Follow device-specific instructions

### Step 2: Commission Device
```bash
# Commission with node ID 2 (or next available)
chip-tool pairing onnetwork 2 <PIN_CODE>

# Verify
chip-tool pairing list
```

### Step 3: Control Device
```bash
# Example: On/Off control
chip-tool onoff on 2 1
chip-tool onoff off 2 1
```

---

## Verification After Reboot

```bash
# 1. Check all services started
systemctl status ot-br-posix.service
systemctl status chip-lighting-app.service
systemctl status avahi-daemon.service

# 2. Verify Thread network restored
ot-ctl state
ip link show wpan0

# 3. Verify devices still commissioned
chip-tool pairing list

# 4. Test control
chip-tool onoff on 1 1
```

---

## Troubleshooting Commands

### Thread Network Issues
```bash
# Check OTBR logs
journalctl -u ot-br-posix.service -f

# Check Thread interface
ip addr show wpan0

# Reset Thread network (if needed)
ot-ctl factoryreset
ot-ctl thread start
```

### Matter App Issues
```bash
# Check app logs
journalctl -u chip-lighting-app.service -f

# Verify Thread is enabled
strings /usr/bin/chip-lighting-app | grep -i thread

# Check mDNS discovery
avahi-browse -a
```

### Commissioning Issues
```bash
# Check pairing list
chip-tool pairing list

# Remove failed pairing (if needed)
chip-tool pairing unpair <NODE_ID>

# Check device logs
journalctl -u chip-lighting-app.service | grep -i pairing
```

### RCP Device Issues
```bash
# Check device exists
ls -l /dev/ttyACM*

# Check permissions
ls -l /dev/ttyACM0

# Test device access
stty -F /dev/ttyACM0 115200

# Check OTBR wrapper logs
journalctl -u ot-br-posix.service | grep -i rcp
```

---

## Environment Variables

You can override defaults using environment variables:

```bash
# RCP device path
export RCP_DEVICE=/dev/ttyUSB0

# Bridge interface
export BRIDGE_IF=wlan0

# Matter pairing code
export MATTER_PAIRING_CODE=12345678
```

---

## Common Issues & Solutions

### Issue: "wpan0 interface not found"
**Solution:**
```bash
# Check OTBR service
systemctl restart ot-br-posix.service
# Wait 10 seconds
ip link show wpan0
```

### Issue: "Cannot commission device"
**Solution:**
```bash
# Verify Thread network is started
ot-ctl thread start

# Check mDNS
avahi-browse -a | grep -i matter

# Verify Matter app is running
systemctl status chip-lighting-app.service
```

### Issue: "Device disappears after reboot"
**Solution:**
```bash
# Check Matter app persistence directory
ls -la /tmp/chip_*

# Verify services start in correct order
systemctl list-dependencies chip-lighting-app.service
```

### Issue: "RCP device not found"
**Solution:**
```bash
# Check USB device
lsusb | grep -i nrf

# Check device path
ls -l /dev/ttyACM*

# Set custom path
export RCP_DEVICE=/dev/ttyUSB0
systemctl restart ot-br-posix.service
```

---

## Expected Outputs

### Successful OTBR Start
```
[otbr-wrapper] Waiting for RCP at /dev/ttyACM0...
[otbr-wrapper] Found device: /dev/ttyACM0
[otbr-wrapper] Starting otbr-agent...
[otbr-wrapper] Waiting for wpan0 interface...
[otbr-wrapper] Interface wpan0 is up
[otbr-wrapper] OpenThread Border Router setup complete.
```

### Successful Commissioning
```
[1640995200.123456][12345:12345] CHIP:DL: Device is paired
[1640995200.123456][12345:12345] CHIP:DL: Device commissioned successfully
```

### Successful Control
```
[1640995200.123456][12345:12345] CHIP:CTL: Sending on/off command
[1640995200.123456][12345:12345] CHIP:CTL: Command sent successfully
```

---

## Next Steps After POC Validation

Once POC goals are achieved:
1. Document any platform-specific issues
2. Note any Thread/Wi-Fi coexistence issues
3. Record commissioning times and reliability
4. Document any device-specific quirks

---

**For detailed troubleshooting, see `POC_AUDIT_AND_FIXES.md`**


