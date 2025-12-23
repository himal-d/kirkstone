# Matter POC Testing & Validation Guide
## RDK-B Build, Services, Commissioning, and Runtime Checks

---

## 📦 Phase 1: Build Validation

### 1.1 Clean Build (Recommended)

```bash
# Navigate to build directory
cd <your-yocto-build-dir>

# Clean affected packages
bitbake -c clean chip-tool
bitbake -c clean ot-br-posix
bitbake -c clean chip-lighting-app
bitbake -c clean chip-all-clusters-app

# Or clean entire build (if needed)
# bitbake -c cleanall chip-tool ot-br-posix
```

### 1.2 Build Affected Packages

```bash
# Build individual packages
bitbake chip-tool
bitbake ot-br-posix
bitbake chip-lighting-app
bitbake chip-all-clusters-app

# Or build entire image
bitbake <your-image-name>
```

### 1.3 Verify Build Success

**Check build logs for errors:**
```bash
# Check for build errors
grep -i "error\|failed" tmp/work/*/chip-tool/*/temp/log.do_*
grep -i "error\|failed" tmp/work/*/ot-br-posix/*/temp/log.do_*

# Check build output
ls -lh tmp/deploy/images/<machine>/chip-tool*
ls -lh tmp/deploy/images/<machine>/ot-br-posix*
```

**Expected Results:**
- ✅ No build errors
- ✅ Packages built successfully
- ✅ Binaries present in deploy directory

### 1.4 Verify Script Installation

**Check that helper scripts are included:**
```bash
# Check package contents
bitbake -e chip-tool | grep ^FILES=
bitbake -e ot-br-posix | grep ^FILES=

# Verify scripts in package
oe-pkgdata-util list-pkg-files chip-tool | grep matter-commission
oe-pkgdata-util list-pkg-files ot-br-posix | grep get-thread-dataset
```

**Expected Results:**
- ✅ `matter-commission` script in chip-tool package
- ✅ `get-thread-dataset` script in ot-br-posix package

---

## 💾 Phase 2: Image Deployment

### 2.1 Flash Image to Raspberry Pi 4

```bash
# Use your preferred method (dd, balena-etcher, etc.)
# Example with dd:
sudo dd if=tmp/deploy/images/<machine>/<image-name>.wic of=/dev/sdX bs=4M status=progress
sync
```

### 2.2 Boot and Initial Setup

```bash
# SSH into Raspberry Pi 4
ssh root@<pi-ip-address>

# Verify system is running
uname -a
cat /etc/os-release
```

**Expected Results:**
- ✅ System boots successfully
- ✅ Network connectivity works
- ✅ Can SSH into device

---

## 🔧 Phase 3: Service Validation

### 3.1 Check Service Installation

```bash
# Verify services are installed
systemctl list-unit-files | grep -E "chip-tool|ot-br-posix|chip-lighting|avahi"

# Check service files exist
ls -l /lib/systemd/system/chip-tool.service
ls -l /lib/systemd/system/ot-br-posix.service
ls -l /lib/systemd/system/chip-lighting-app.service
```

**Expected Results:**
- ✅ All service files present
- ✅ Services listed in systemd

### 3.2 Verify Helper Scripts Installed

```bash
# Check commissioning helper
which matter-commission
matter-commission.sh

# Check dataset helper
which get-thread-dataset
get-thread-dataset.sh

# Verify chip-tool binary
which chip-tool
chip-tool --help
```

**Expected Results:**
- ✅ `matter-commission` available in PATH
- ✅ `get-thread-dataset` available in PATH
- ✅ `chip-tool` binary available

### 3.3 Check Service Configuration

```bash
# Verify chip-tool.service doesn't auto-pair
cat /lib/systemd/system/chip-tool.service | grep ExecStart
# Should show: ExecStart=/bin/true (NOT pairing command)

# Verify OTBR dependency
cat /lib/systemd/system/chip-tool.service | grep After
# Should include: ot-br-posix.service

# Verify Thread interface env var
cat /lib/systemd/system/chip-tool.service | grep THREAD_INTERFACE
# Should show: CHIP_DEVICE_CONFIG_THREAD_INTERFACE_NAME="wpan0"
```

**Expected Results:**
- ✅ chip-tool.service doesn't auto-run pairing
- ✅ Service has OTBR dependency
- ✅ Thread interface configured

### 3.4 Start and Verify Services

```bash
# Start OTBR service
systemctl start ot-br-posix.service
systemctl status ot-br-posix.service

# Start Matter app
systemctl start chip-lighting-app.service
systemctl status chip-lighting-app.service

# Start Avahi (mDNS)
systemctl start avahi-daemon.service
systemctl status avahi-daemon.service

# Enable services for auto-start (optional)
systemctl enable ot-br-posix.service
systemctl enable chip-lighting-app.service
```

**Expected Results:**
- ✅ All services start without errors
- ✅ Services show "active (running)"
- ✅ No service failures

### 3.5 Verify Service Logs

```bash
# Check OTBR logs
journalctl -u ot-br-posix.service -n 50 --no-pager

# Check Matter app logs
journalctl -u chip-lighting-app.service -n 50 --no-pager

# Check for errors
journalctl -u ot-br-posix.service --since "5 minutes ago" | grep -i error
journalctl -u chip-lighting-app.service --since "5 minutes ago" | grep -i error
```

**Expected Results:**
- ✅ No critical errors in logs
- ✅ Services initialized successfully
- ✅ Thread interface created (for OTBR)

---

## 🌐 Phase 4: Network & Thread Validation

### 4.1 Verify Thread RCP Device

```bash
# Check RCP device exists
ls -l /dev/ttyACM*

# Check device permissions
ls -l /dev/ttyACM0

# Test device access (optional)
stty -F /dev/ttyACM0 115200
```

**Expected Results:**
- ✅ RCP device present (e.g., `/dev/ttyACM0`)
- ✅ Device has correct permissions

### 4.2 Verify Thread Interface

```bash
# Check wpan0 interface exists
ip link show wpan0

# Check interface state
ip addr show wpan0

# Check interface is UP
ip link show wpan0 | grep -i "state up"
```

**Expected Results:**
- ✅ `wpan0` interface exists
- ✅ Interface is UP
- ✅ Interface has IPv6 address

### 4.3 Start Thread Network

```bash
# Check if ot-ctl is available
which ot-ctl

# Check current Thread state
ot-ctl state

# Start Thread network
ot-ctl thread start

# Wait a few seconds, then check state
sleep 5
ot-ctl state

# Check if network is active
ot-ctl ifconfig up
ot-ctl thread start
```

**Expected Results:**
- ✅ `ot-ctl` command available
- ✅ Thread network starts successfully
- ✅ State shows: `child`, `router`, or `leader`
- ✅ Network is active

### 4.4 Get Thread Operational Dataset

```bash
# Test dataset helper script
get-thread-dataset.sh

# Verify dataset is valid hex
DATASET=$(get-thread-dataset.sh 2>/dev/null | grep -E "^[0-9a-fA-F]+$" | head -1)
echo "Dataset length: ${#DATASET}"
```

**Expected Results:**
- ✅ Script runs without errors
- ✅ Dataset is valid hex string
- ✅ Dataset length > 0

### 4.5 Verify mDNS/Avahi

```bash
# Check Avahi service
systemctl status avahi-daemon.service

# Browse for Matter services
avahi-browse -a | grep -i matter

# Check Avahi logs
journalctl -u avahi-daemon.service -n 20 --no-pager
```

**Expected Results:**
- ✅ Avahi service running
- ✅ Matter services discoverable (after commissioning)

---

## 📱 Phase 5: Commissioning Validation

### 5.1 Pre-Commissioning Checklist

```bash
# Run comprehensive pre-check
echo "=== Pre-Commissioning Checklist ==="
echo "1. OTBR Service:"
systemctl is-active ot-br-posix && echo "  ✓ Active" || echo "  ✗ Failed"

echo "2. Thread Interface:"
ip link show wpan0 >/dev/null 2>&1 && echo "  ✓ Exists" || echo "  ✗ Missing"

echo "3. Thread Network:"
ot-ctl state | grep -qE "child|router|leader" && echo "  ✓ Started" || echo "  ✗ Not started"

echo "4. Matter App:"
systemctl is-active chip-lighting-app && echo "  ✓ Active" || echo "  ✗ Failed"

echo "5. mDNS:"
systemctl is-active avahi-daemon && echo "  ✓ Active" || echo "  ✗ Failed"

echo "6. chip-tool:"
chip-tool --help >/dev/null 2>&1 && echo "  ✓ Available" || echo "  ✗ Missing"

echo "7. Helper Scripts:"
command -v matter-commission >/dev/null && echo "  ✓ matter-commission available" || echo "  ✗ Missing"
command -v get-thread-dataset >/dev/null && echo "  ✓ get-thread-dataset available" || echo "  ✗ Missing"
```

**Expected Results:**
- ✅ All 7 checks pass

### 5.2 Test Helper Scripts

```bash
# Test matter-commission help
matter-commission.sh

# Test get-thread-dataset
get-thread-dataset.sh

# Verify chip-tool works
chip-tool --help
chip-tool pairing list
```

**Expected Results:**
- ✅ Helper scripts show usage/help
- ✅ chip-tool responds to commands
- ✅ No errors

### 5.3 Commission Thread Device (Aqara Bulb)

```bash
# Step 1: Put bulb in pairing mode
# (Manual: Power cycle 5 times quickly)

# Step 2: Get Thread dataset
DATASET=$(get-thread-dataset.sh 2>/dev/null | grep -E "^[0-9a-fA-F]+$" | head -1)
echo "Dataset: $DATASET"

# Step 3: Commission (replace PIN and discriminator)
# Typical Aqara values: PIN=12345678, Discriminator=3840
matter-commission.sh thread-ble 1 12345678 3840

# Or try on-network method
matter-commission.sh thread-onnetwork 1 12345678
```

**Expected Results:**
- ✅ Commissioning command executes
- ✅ Device connects to Thread network
- ✅ Commissioning completes successfully
- ✅ No timeout or connection errors

### 5.4 Verify Thread Device Commissioning

```bash
# List commissioned devices
matter-commission.sh list
# Or: chip-tool pairing list

# Check device details
chip-tool pairing list | grep -A 5 "Node ID: 1"
```

**Expected Results:**
- ✅ Device appears in pairing list
- ✅ Node ID: 1 assigned
- ✅ Device type shown correctly

### 5.5 Test Thread Device Control

```bash
# Turn device ON
matter-commission.sh control-on 1 1
# Or: chip-tool onoff on 1 1

# Wait and verify
sleep 2

# Read state
chip-tool onoff read on-off 1 1

# Turn device OFF
matter-commission.sh control-off 1 1
# Or: chip-tool onoff off 1 1

# Wait and verify
sleep 2
chip-tool onoff read on-off 1 1
```

**Expected Results:**
- ✅ ON command succeeds
- ✅ Device state shows ON (1)
- ✅ OFF command succeeds
- ✅ Device state shows OFF (0)
- ✅ Physical device responds (bulb turns on/off)

### 5.6 Commission Wi-Fi Device (If Available)

```bash
# Put device in pairing mode (device-specific)

# Commission Wi-Fi device
matter-commission.sh wifi 2 <PIN_CODE>

# Verify
matter-commission.sh list

# Test control
matter-commission.sh control-on 2 1
matter-commission.sh control-off 2 1
```

**Expected Results:**
- ✅ Wi-Fi device commissions successfully
- ✅ Device appears in pairing list
- ✅ Control commands work

---

## 🔄 Phase 6: Runtime & Persistence Validation

### 6.1 Verify Services Auto-Start

```bash
# Reboot system
reboot

# Wait for system to come back up (2-3 minutes)
# Then SSH back in and check services

# Check services started automatically
systemctl status ot-br-posix.service
systemctl status chip-lighting-app.service
systemctl status avahi-daemon.service
```

**Expected Results:**
- ✅ All services auto-start after reboot
- ✅ Services are active (running)
- ✅ No service failures

### 6.2 Verify Thread Network Restores

```bash
# After reboot, check Thread network
ot-ctl state

# If not started, start it
ot-ctl thread start
sleep 5
ot-ctl state

# Check interface
ip link show wpan0
```

**Expected Results:**
- ✅ Thread network can be started after reboot
- ✅ Network state becomes active
- ✅ wpan0 interface exists

### 6.3 Verify Devices Persist

```bash
# List devices after reboot
matter-commission.sh list
# Or: chip-tool pairing list

# Verify previously commissioned devices still listed
chip-tool pairing list | grep "Node ID: 1"
```

**Expected Results:**
- ✅ Previously commissioned devices still in list
- ✅ Node IDs preserved
- ✅ No need to re-commission

### 6.4 Test Control After Reboot

```bash
# Test device control after reboot
matter-commission.sh control-on 1 1
sleep 2
chip-tool onoff read on-off 1 1

matter-commission.sh control-off 1 1
sleep 2
chip-tool onoff read on-off 1 1
```

**Expected Results:**
- ✅ Control commands work after reboot
- ✅ Device responds correctly
- ✅ State changes persist

---

## 📊 Phase 7: Comprehensive Validation Script

### 7.1 Create Validation Script

```bash
# Create comprehensive validation script
cat > /usr/local/bin/validate-matter-poc.sh << 'EOF'
#!/bin/bash
# Matter POC Comprehensive Validation Script

PASS=0
FAIL=0

check() {
    if [ $? -eq 0 ]; then
        echo "  ✓ $1"
        ((PASS++))
        return 0
    else
        echo "  ✗ $1"
        ((FAIL++))
        return 1
    fi
}

echo "=== Matter POC Validation ==="
echo ""

echo "1. Service Status:"
systemctl is-active ot-br-posix >/dev/null 2>&1
check "OTBR service active"

systemctl is-active chip-lighting-app >/dev/null 2>&1
check "Matter app service active"

systemctl is-active avahi-daemon >/dev/null 2>&1
check "mDNS service active"

echo ""
echo "2. Thread Network:"
ip link show wpan0 >/dev/null 2>&1
check "Thread interface (wpan0) exists"

ot-ctl state 2>/dev/null | grep -qE "child|router|leader"
check "Thread network started"

echo ""
echo "3. Tools & Scripts:"
command -v chip-tool >/dev/null 2>&1
check "chip-tool available"

command -v matter-commission >/dev/null 2>&1
check "matter-commission script available"

command -v get-thread-dataset >/dev/null 2>&1
check "get-thread-dataset script available"

echo ""
echo "4. Commissioning:"
chip-tool pairing list 2>/dev/null | grep -q "Node ID"
check "At least one device commissioned"

echo ""
echo "5. Device Control:"
chip-tool onoff on 1 1 >/dev/null 2>&1
sleep 1
chip-tool onoff read on-off 1 1 2>/dev/null | grep -q "1"
check "Device control (ON) works"

chip-tool onoff off 1 1 >/dev/null 2>&1
sleep 1
chip-tool onoff read on-off 1 1 2>/dev/null | grep -q "0"
check "Device control (OFF) works"

echo ""
echo "=== Validation Summary ==="
echo "Passed: $PASS"
echo "Failed: $FAIL"
echo "Total:  $((PASS + FAIL))"

if [ $FAIL -eq 0 ]; then
    echo ""
    echo "✅ All checks passed!"
    exit 0
else
    echo ""
    echo "❌ Some checks failed"
    exit 1
fi
EOF

chmod +x /usr/local/bin/validate-matter-poc.sh
```

### 7.2 Run Validation Script

```bash
# Run validation
validate-matter-poc.sh
```

**Expected Results:**
- ✅ All checks pass
- ✅ Script exits with code 0

---

## 🐛 Phase 8: Troubleshooting

### 8.1 Common Issues & Solutions

| Issue | Symptom | Solution |
|-------|---------|----------|
| **Build fails** | Error in bitbake log | Check dependencies, clean and rebuild |
| **Service won't start** | `systemctl status` shows failed | Check logs: `journalctl -u <service>` |
| **Thread interface missing** | `ip link show wpan0` fails | Restart OTBR: `systemctl restart ot-br-posix` |
| **Thread network not starting** | `ot-ctl state` shows detached | Check RCP device: `ls -l /dev/ttyACM*` |
| **Commissioning fails** | Timeout or connection error | Verify device in pairing mode, check PIN |
| **Device not responding** | Control commands fail | Check device powered, verify commissioning |
| **Devices lost after reboot** | `pairing list` empty | Check Matter app persistence directory |

### 8.2 Diagnostic Commands

```bash
# Check all service statuses
systemctl status ot-br-posix chip-lighting-app avahi-daemon

# Check recent errors
journalctl -p err -n 50

# Check Thread network details
ot-ctl state
ot-ctl dataset active -x
ot-ctl ifconfig

# Check network interfaces
ip addr show
ip link show

# Check mDNS discovery
avahi-browse -a

# Check Matter app logs
journalctl -u chip-lighting-app -f
```

---

## ✅ Success Criteria

### Build Validation
- [x] All packages build without errors
- [x] Helper scripts included in packages
- [x] Image builds successfully

### Service Validation
- [x] All services install correctly
- [x] Services start without errors
- [x] Services auto-start after reboot

### Network Validation
- [x] Thread RCP device detected
- [x] Thread interface (wpan0) created
- [x] Thread network starts successfully
- [x] Operational dataset accessible

### Commissioning Validation
- [x] Thread device commissions successfully
- [x] Wi-Fi device commissions successfully (if available)
- [x] Devices appear in pairing list
- [x] Control commands work

### Persistence Validation
- [x] Services auto-start after reboot
- [x] Thread network restores after reboot
- [x] Commissioned devices persist after reboot
- [x] Device control works after reboot

---

## 📋 Quick Reference

### Essential Commands
```bash
# Service management
systemctl status ot-br-posix chip-lighting-app
systemctl restart ot-br-posix

# Thread network
ot-ctl thread start
ot-ctl state
get-thread-dataset.sh

# Commissioning
matter-commission.sh thread-ble 1 <PIN> <DISC>
matter-commission.sh wifi 2 <PIN>
matter-commission.sh list

# Control
matter-commission.sh control-on 1 1
matter-commission.sh control-off 1 1

# Validation
validate-matter-poc.sh
```

---

**Follow this guide step-by-step to validate your Matter POC implementation!**

