#!/bin/bash
# Configure BLE Adapter Connection Parameters for Matter Commissioning
# This script sets more lenient connection parameters optimized for UART-based BLE
# (e.g., Raspberry Pi onboard BCM BLE) to reduce connection abort errors

set -e

ADAPTER=${1:-hci0}
MAX_WAIT=30  # Maximum seconds to wait for adapter

echo "Configuring BLE adapter $ADAPTER for Matter commissioning..."

# Wait for adapter to be available
WAIT_COUNT=0
while ! hciconfig $ADAPTER &>/dev/null 2>&1; do
    if [ $WAIT_COUNT -ge $MAX_WAIT ]; then
        echo "Error: Adapter $ADAPTER not found after ${MAX_WAIT} seconds"
        exit 1
    fi
    echo "Waiting for adapter $ADAPTER... ($WAIT_COUNT/$MAX_WAIT)"
    sleep 1
    WAIT_COUNT=$((WAIT_COUNT + 1))
done

# Bring adapter up if down
if ! hciconfig $ADAPTER | grep -q "UP"; then
    echo "Bringing adapter $ADAPTER up..."
    hciconfig $ADAPTER up
    sleep 1
fi

# Set connection parameters (more lenient for UART BLE)
# Connection interval: 30ms (default: 15ms) - gives more time for UART communication
# Connection latency: 2 (default: 0) - allows some missed intervals
# Supervision timeout: 10000ms (default: 5000ms) - longer timeout for Matter commissioning
echo "Setting connection parameters..."
hciconfig $ADAPTER connmin 30 connmax 30 2>/dev/null || echo "Warning: Failed to set connection interval"
hciconfig $ADAPTER connlat 2 2>/dev/null || echo "Warning: Failed to set connection latency"
hciconfig $ADAPTER connto 10000 2>/dev/null || echo "Warning: Failed to set supervision timeout"

# Enable page/inquiry scan (required for connections)
echo "Enabling page/inquiry scan..."
hciconfig $ADAPTER piscan 2>/dev/null || echo "Warning: Failed to enable page scan"

# Power on via bluetoothctl (more reliable than hciconfig)
echo "Powering on adapter..."
bluetoothctl power on 2>/dev/null || echo "Warning: Failed to power on via bluetoothctl"
sleep 2

# Verify configuration
echo ""
echo "Verifying configuration..."
if hciconfig $ADAPTER | grep -q "UP RUNNING"; then
    echo "✓ Adapter $ADAPTER is UP and RUNNING"
else
    echo "✗ Adapter $ADAPTER is not in expected state"
    hciconfig $ADAPTER
    exit 1
fi

if bluetoothctl show 2>/dev/null | grep -q "Powered: yes"; then
    echo "✓ Adapter is powered on"
else
    echo "✗ Adapter is not powered on"
    exit 1
fi

echo ""
echo "BLE adapter $ADAPTER configured successfully for Matter commissioning"
echo "Connection parameters: interval=30ms, latency=2, timeout=10000ms"

