# OTBR Service Fix Summary

## Issue
`ot-br-posix.service` was failing with status code 5 (NOTINSTALLED). The service would start but immediately exit.

## Root Cause
The wrapper script (`otbr-agent-wrapper.sh`) had a logic error:
- Used `exec` which replaced the shell process
- Code after `exec` never executed (waiting for interfaces)
- No error handling or logging of otbr-agent failures

## Fixes Applied

### 1. Fixed Wrapper Script Logic
**File:** `meta-rdk-matter/recipes-thread/ot-br-posix/files/otbr-agent-wrapper.sh`

**Changes:**
- Removed `exec` - now runs otbr-agent in background
- Added proper process management (PID tracking)
- Added error checking and logging
- Added interface verification before declaring success
- Added log file capture (`/tmp/otbr-agent.log`)

### 2. Removed ot-daemon Dependency
**File:** `meta-rdk-matter/recipes-thread/ot-br-posix/files/ot-br-posix.service`

**Change:** Removed `ot-daemon.service` dependency since otbr-agent uses direct RCP mode (`spinel+hdlc+uart://`), not NCP mode through ot-daemon.

### 3. Added Diagnostic Tool
**New File:** `meta-rdk-matter/recipes-thread/ot-br-posix/files/otbr-diagnose.sh`

**Purpose:** Helps diagnose OTBR issues by checking:
- RCP device availability and permissions
- otbr-agent binary and dependencies
- Network interfaces
- Kernel modules
- Service status
- Recent logs

## Next Steps

### 1. Rebuild Package
```bash
bitbake -c clean ot-br-posix
bitbake ot-br-posix
```

### 2. Flash Updated Image

### 3. Test on Device
```bash
# Check service status
systemctl status ot-br-posix.service

# If still failing, run diagnostic
otbr-diagnose.sh

# Check logs
journalctl -u ot-br-posix.service -f
cat /tmp/otbr-agent.log
```

### 4. Manual Test (if needed)
```bash
# Stop service
systemctl stop ot-br-posix.service

# Run wrapper manually to see errors
/usr/local/bin/otbr-agent-wrapper.sh

# Or test otbr-agent directly
/usr/sbin/otbr-agent -I wpan0 -B eth0 -d 7 spinel+hdlc+uart:///dev/ttyACM0
```

## Expected Behavior After Fix

1. Service starts successfully
2. otbr-agent runs in background
3. wpan0 interface is created
4. Service stays running (not restarting)
5. Thread network can be started with `ot-ctl thread start`

## Troubleshooting

If service still fails:

1. **Check RCP device:**
   ```bash
   ls -l /dev/ttyACM0
   # Should be readable/writable by root
   ```

2. **Check otbr-agent binary:**
   ```bash
   /usr/sbin/otbr-agent --help
   # Should show help text
   ```

3. **Check dependencies:**
   ```bash
   ldd /usr/sbin/otbr-agent
   # All libraries should be found
   ```

4. **Check kernel modules:**
   ```bash
   lsmod | grep mac802154
   lsmod | grep ieee802154
   # Should be loaded
   ```

5. **Check log file:**
   ```bash
   cat /tmp/otbr-agent.log
   # Shows actual otbr-agent errors
   ```

6. **Run diagnostic:**
   ```bash
   otbr-diagnose.sh
   # Comprehensive system check
   ```

## Common Issues

| Issue | Solution |
|-------|----------|
| RCP device permission denied | Add user to dialout group or use udev rules |
| otbr-agent missing libraries | Check RDEPENDS in recipe |
| Bridge interface not found | Use `BRIDGE_IF` env var or modify detection |
| Kernel modules not loaded | Add to systemd service ExecStartPre |

---

**Status:** Fixes applied, ready for rebuild and testing.

