# Matter POC Demo Guide
## Raspberry Pi 4 Commissioning & Control

**Purpose:** Step-by-step guide for demonstrating Matter device commissioning and control

---

## 📋 Pre-Demo Setup Checklist

| # | Task | Command | Expected Output |
|---|------|---------|----------------|
| 1 | Verify OTBR service | `systemctl status ot-br-posix` | `active (running)` |
| 2 | Verify Thread interface | `ip link show wpan0` | Interface exists with UP state |
| 3 | Start Thread network | `ot-ctl thread start` | `Done` |
| 4 | Check Thread state | `ot-ctl state` | `child`, `router`, or `leader` |
| 5 | Verify Matter apps | `systemctl status chip-lighting-app` | `active (running)` |
| 6 | Verify mDNS | `systemctl status avahi-daemon` | `active (running)` |
| 7 | Test chip-tool | `chip-tool --help` | Help text displayed |
| 8 | Test helper script | `matter-commission.sh` | Usage instructions |

---

## 🔵 Commissioning Aqara Thread Bulb (LB-L03E)

### Step 1: Prepare Bulb for Pairing

**Action:** Put Aqara bulb in pairing mode
- **Method:** Power cycle bulb 5 times quickly (on/off within 2 seconds each)
- **Indicator:** LED should blink or change color pattern
- **Duration:** Bulb stays in pairing mode for ~2 minutes

### Step 2: Get Thread Network Credentials

```bash
# Get operational dataset from OTBR
get-thread-dataset.sh
```

**Expected Output:**
```
Getting OpenThread operational dataset...

Operational Dataset (hex):
0e080000000000010000000300000f35060004001fffe0020811111111222222220708fd1234567890abcdef0510...

Use this for BLE-Thread commissioning:
chip-tool pairing ble-thread <NODE_ID> hex:0e080000... <PIN_CODE> <DISCRIMINATOR>
```

**Note:** Copy the hex dataset string (you'll need it)

### Step 3: Commission Bulb

**Option A: Using Helper Script (Recommended)**

```bash
# Replace PIN_CODE and DISCRIMINATOR with bulb's actual values
# Typical Aqara values: PIN=12345678, Discriminator=3840
matter-commission.sh thread-ble 1 12345678 3840
```

**Option B: Manual Command**

```bash
# Use dataset from Step 2
chip-tool pairing ble-thread 1 hex:<DATASET> 12345678 3840
```

**Expected Output:**
```
Commissioning Thread device (BLE-Thread)...
Node ID: 1
PIN: 12345678
Discriminator: 3840

[Device commissioning process logs...]
Device commissioned successfully
```

### Step 4: Verify Commissioning

```bash
# List all commissioned devices
matter-commission.sh list
```

**Expected Output:**
```
Listing commissioned devices...
Node ID: 1
  Fabric ID: 1
  Endpoint: 1
  Device Type: On/Off Light
```

### Step 5: Control Bulb

```bash
# Turn bulb ON
matter-commission.sh control-on 1 1
# Or: chip-tool onoff on 1 1

# Turn bulb OFF
matter-commission.sh control-off 1 1
# Or: chip-tool onoff off 1 1

# Read current state
chip-tool onoff read on-off 1 1
```

**Expected Output (ON):**
```
[Control command sent...]
OnOff: 1 (ON)
```

**Expected Output (OFF):**
```
[Control command sent...]
OnOff: 0 (OFF)
```

---

## 📶 Commissioning Wi-Fi Matter Device

### Step 1: Prepare Device for Pairing

**Action:** Put Wi-Fi device in pairing mode
- **Method:** Follow device-specific instructions (usually button press or app)
- **Indicator:** Device LED or status indicator shows pairing mode

### Step 2: Commission Device

```bash
# Commission Wi-Fi device (use node ID 2 or next available)
matter-commission.sh wifi 2 <PIN_CODE>

# Or manually:
chip-tool pairing onnetwork 2 <PIN_CODE>
```

**Expected Output:**
```
Commissioning Wi-Fi device...
Node ID: 2
PIN: 87654321

[Device commissioning process logs...]
Device commissioned successfully
```

### Step 3: Verify and Control

```bash
# List devices
matter-commission.sh list

# Control device
matter-commission.sh control-on 2 1
matter-commission.sh control-off 2 1
```

---

## 📊 Demo Flow Table

| Step | Action | Command | Expected Result |
|------|--------|---------|----------------|
| **Setup** |
| 1 | Check services | `systemctl status ot-br-posix chip-lighting-app` | Both active |
| 2 | Start Thread | `ot-ctl thread start` | Network started |
| 3 | Verify Thread | `ot-ctl state` | Shows network state |
| **Thread Bulb** |
| 4 | Get dataset | `get-thread-dataset.sh` | Hex dataset displayed |
| 5 | Put bulb in pairing | Manual (power cycle) | LED blinks |
| 6 | Commission | `matter-commission.sh thread-ble 1 <PIN> <DISC>` | Success message |
| 7 | Verify | `matter-commission.sh list` | Device listed |
| 8 | Control ON | `matter-commission.sh control-on 1 1` | Bulb turns on |
| 9 | Control OFF | `matter-commission.sh control-off 1 1` | Bulb turns off |
| **Wi-Fi Device** |
| 10 | Put device in pairing | Manual (device-specific) | Device ready |
| 11 | Commission | `matter-commission.sh wifi 2 <PIN>` | Success message |
| 12 | Verify | `matter-commission.sh list` | Both devices listed |
| 13 | Control | `matter-commission.sh control-on 2 1` | Device responds |
| **Persistence** |
| 14 | Reboot | `reboot` | System restarts |
| 15 | Verify after reboot | `matter-commission.sh list` | Devices still listed |
| 16 | Control after reboot | `matter-commission.sh control-on 1 1` | Still works |

---

## 🔍 Verification Logs

### Successful Commissioning Log

```bash
# Watch commissioning in real-time
journalctl -u chip-lighting-app -f
```

**Expected Log Pattern:**
```
[timestamp] CHIP:DL: Device is pairing...
[timestamp] CHIP:DL: BLE connection established
[timestamp] CHIP:DL: Operational credentials received
[timestamp] CHIP:DL: Device commissioned successfully
[timestamp] CHIP:DL: Device node ID: 1
```

### Successful Control Log

```bash
# Watch control commands
journalctl -u chip-lighting-app -f | grep -i onoff
```

**Expected Log Pattern:**
```
[timestamp] CHIP:CTL: Received on/off command
[timestamp] CHIP:CTL: Command executed successfully
[timestamp] CHIP:CTL: Device state: ON
```

---

## 🛠️ Troubleshooting Quick Reference

| Issue | Symptom | Solution |
|-------|---------|----------|
| Thread network not started | `ot-ctl state` shows "detached" | `ot-ctl thread start` |
| Device not discovered | Commissioning fails | Check mDNS: `avahi-browse -a` |
| Wrong PIN code | Commissioning fails | Verify PIN from device manual |
| Thread interface missing | `ip link show wpan0` fails | Restart OTBR: `systemctl restart ot-br-posix` |
| Device not responding | Control commands fail | Check device is powered and in range |
| Services not starting | `systemctl status` shows failed | Check logs: `journalctl -u <service>` |

---

## 📝 Post-Reboot Verification

### Automated Verification Script

```bash
#!/bin/bash
# Post-reboot verification

echo "=== Post-Reboot Verification ==="
echo ""

echo "1. Checking services..."
systemctl is-active ot-br-posix && echo "  ✓ OTBR active" || echo "  ✗ OTBR failed"
systemctl is-active chip-lighting-app && echo "  ✓ Matter app active" || echo "  ✗ Matter app failed"
systemctl is-active avahi-daemon && echo "  ✓ mDNS active" || echo "  ✗ mDNS failed"

echo ""
echo "2. Checking Thread network..."
ot-ctl state | grep -q "child\|router\|leader" && echo "  ✓ Thread network active" || echo "  ✗ Thread network not started"

echo ""
echo "3. Checking commissioned devices..."
DEVICES=$(chip-tool pairing list 2>/dev/null | grep -c "Node ID" || echo "0")
echo "  Found $DEVICES commissioned device(s)"

echo ""
echo "4. Testing device control..."
chip-tool onoff on 1 1 2>&1 | grep -q "success\|Success" && echo "  ✓ Device control works" || echo "  ✗ Device control failed"

echo ""
echo "=== Verification Complete ==="
```

**Save as:** `/usr/local/bin/verify-matter-poc.sh`
**Make executable:** `chmod +x /usr/local/bin/verify-matter-poc.sh`
**Run:** `verify-matter-poc.sh`

---

## 🎯 Demo Success Criteria

✅ **All criteria must pass for successful POC:**

- [ ] Thread Border Router running and Thread network started
- [ ] Aqara Thread bulb successfully commissioned (appears in pairing list)
- [ ] Bulb responds to ON/OFF commands
- [ ] Wi-Fi Matter device successfully commissioned (if available)
- [ ] Wi-Fi device responds to control commands
- [ ] All devices persist after reboot
- [ ] All devices still controllable after reboot

---

## 📋 Quick Command Reference

```bash
# Thread Network
ot-ctl thread start              # Start Thread network
ot-ctl state                     # Check Thread state
ot-ctl dataset active -x        # Get operational dataset

# Commissioning
get-thread-dataset.sh            # Get Thread dataset (helper)
matter-commission.sh thread-ble 1 <PIN> <DISC>  # Commission Thread device
matter-commission.sh wifi 2 <PIN>               # Commission Wi-Fi device
matter-commission.sh list                        # List devices

# Control
matter-commission.sh control-on 1 1   # Turn device ON
matter-commission.sh control-off 1 1  # Turn device OFF
chip-tool onoff on 1 1                 # Direct control
chip-tool onoff off 1 1                # Direct control

# Verification
systemctl status ot-br-posix          # Check OTBR
systemctl status chip-lighting-app    # Check Matter app
chip-tool pairing list                # List devices
journalctl -u chip-lighting-app -f   # Watch logs
```

---

**Ready for POC demonstration!**


