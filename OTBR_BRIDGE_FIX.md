# OTBR Bridge Interface Fix

## Issue
`ot-br-posix.service` was failing because:
1. Bridge interface detection was looking for `eth0` which doesn't exist on RDK-B
2. System has `br0` and `brlan0` available but detection logic was wrong
3. Error messages weren't showing the actual otbr-agent failure

## Fix Applied

### 1. Fixed Bridge Interface Detection
**File:** `meta-rdk-matter/recipes-thread/ot-br-posix/files/otbr-agent-wrapper.sh`

**Changes:**
- Updated priority order: `br0 > brlan0 > wlan0 > eth0`
- Fixed detection logic to return first available interface
- Added environment variable support (`BRIDGE_IF`)
- Made bridge interface check fail fast with clear error

### 2. Improved Error Logging
- Better log file handling
- Direct execution attempt to capture immediate errors
- More detailed error messages

## Next Steps

### 1. Rebuild Package
```bash
bitbake -c clean ot-br-posix
bitbake ot-br-posix
```

### 2. Flash and Test

### 3. Verify Bridge Interface Detection
```bash
# Check what interface will be detected
/usr/local/bin/otbr-agent-wrapper.sh
# Should show: "Using bridge interface: br0" (or brlan0)

# Or set manually if needed
export BRIDGE_IF=brlan0
systemctl restart ot-br-posix.service
```

### 4. Check Logs
```bash
# Service logs
journalctl -u ot-br-posix.service -f

# otbr-agent log file
cat /tmp/otbr-agent.log

# Run diagnostic
otbr-diagnose.sh
```

## Expected Behavior

After fix:
1. Script detects `br0` or `brlan0` automatically
2. Shows "Using bridge interface: br0" in logs
3. otbr-agent starts successfully
4. wpan0 interface is created
5. Service stays running

## Manual Override

If you need to use a specific bridge interface:

```bash
# Edit service file
systemctl edit ot-br-posix.service

# Add:
[Service]
Environment=BRIDGE_IF=brlan0

# Or create override file
mkdir -p /etc/systemd/system/ot-br-posix.service.d/
cat > /etc/systemd/system/ot-br-posix.service.d/override.conf << EOF
[Service]
Environment=BRIDGE_IF=brlan0
EOF

systemctl daemon-reload
systemctl restart ot-br-posix.service
```

## Troubleshooting

If still failing after fix:

1. **Check detected interface:**
   ```bash
   # Run wrapper manually
   /usr/local/bin/otbr-agent-wrapper.sh
   ```

2. **Check otbr-agent directly:**
   ```bash
   /usr/sbin/otbr-agent -I wpan0 -B br0 -d 7 spinel+hdlc+uart:///dev/ttyACM0
   ```

3. **Check log file:**
   ```bash
   cat /tmp/otbr-agent.log
   ```

4. **Run diagnostic:**
   ```bash
   otbr-diagnose.sh
   ```

---

**Status:** Bridge interface detection fixed, ready for rebuild and test.

