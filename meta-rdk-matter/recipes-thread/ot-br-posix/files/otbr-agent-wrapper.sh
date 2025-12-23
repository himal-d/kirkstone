#!/bin/bash
set -e

# ==========================
# Configuration
# ==========================
# Detect RCP device with fallback
detect_rcp_device() {
    # Check common paths
    for dev in /dev/ttyACM0 /dev/ttyUSB0 /dev/ttyACM1; do
        if [ -e "$dev" ]; then
            # Verify it's a character device
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

# Detect bridge interface for Raspberry Pi 4
detect_bridge_interface() {
    # Check for common bridge interfaces (prefer eth0 for Pi 4)
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

RCP_DEVICE=$(detect_rcp_device)
WPAN_IF="wpan0"
BR_IF=$(detect_bridge_interface)
OTBR_AGENT_BIN="/usr/sbin/otbr-agent"

# ==========================
# Helper Functions
# ==========================
log() {
    echo "[otbr-wrapper] $*"
}

wait_for_device() {
    local dev=$1
    local retries=${2:-30}
    for i in $(seq 1 "$retries"); do
        if [ -e "$dev" ]; then
            log "Found device: $dev"
            return 0
        fi
        sleep 1
    done
    log "Error: Device $dev not found after $retries seconds"
    exit 1
}

wait_for_interface() {
    local ifname=$1
    local retries=${2:-30}
    for i in $(seq 1 "$retries"); do
        if ip link show "$ifname" &>/dev/null; then
            log "Interface $ifname is up"
            return 0
        fi
        sleep 1
    done
    log "Error: Interface $ifname not found after $retries seconds"
    exit 1
}

kill_stale_processes() {
    log "Cleaning up stale ot-daemon/otbr-agent..."
    pkill -9 -x ot-daemon || true
    pkill -9 -x otbr-agent || true
}

# ==========================
# Main Script
# ==========================
log "Waiting for RCP at $RCP_DEVICE..."
wait_for_device "$RCP_DEVICE"

kill_stale_processes

log "Starting otbr-agent..."
exec $OTBR_AGENT_BIN -I "$WPAN_IF" -B "$BR_IF" -d 7 spinel+hdlc+uart://"$RCP_DEVICE"
#$OTBR_AGENT_BIN -I "$WPAN_IF" -B "$BR_IF" -d 7 spinel+hdlc+uart://"$RCP_DEVICE" &

# Wait for wpan0 to appear (created by otbr-agent)
log "Waiting for $WPAN_IF interface..."
wait_for_interface "$WPAN_IF"

# Optionally, wait for bridge interface
log "Waiting for $BR_IF interface..."
wait_for_interface "$BR_IF"

log "OpenThread Border Router setup complete."
wait

