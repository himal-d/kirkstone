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
            echo "Usage: matter-commission.sh thread-ble <node_id> <pin_code> <discriminator> [--bypass-attestation]"
            echo "Example: matter-commission.sh thread-ble 1 12345678 3840"
            echo "Example: matter-commission.sh thread-ble 1 12345678 3840 --bypass-attestation"
            exit 1
        fi
        
        # Check for bypass flag
        BYPASS_ATTESTATION=""
        if [ "$5" = "--bypass-attestation" ] || [ "$5" = "--bypass" ]; then
            BYPASS_ATTESTATION="--bypass-attestation-verifier true"
            echo "⚠️  WARNING: Attestation verification bypassed (POC only!)"
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
        
        # Verify BlueZ is ready before commissioning
        if command -v verify-ble-ready &> /dev/null; then
            echo "Verifying BlueZ BLE adapter readiness..."
            if ! verify-ble-ready; then
                echo "Error: BlueZ BLE adapter is not ready. Please fix BlueZ issues before commissioning."
                exit 1
            fi
            echo ""
        else
            # Manual verification if script not available
            echo "Checking BlueZ adapter state..."
            if ! systemctl is-active --quiet bluetooth; then
                echo "Warning: BlueZ service not running. Starting..."
                systemctl start bluetooth
                sleep 5
            fi
            if ! hciconfig hci0 &>/dev/null || ! hciconfig hci0 | grep -q "UP"; then
                echo "Warning: BLE adapter not up. Bringing up..."
                hciconfig hci0 up
                hciconfig hci0 piscan
                bluetoothctl power on
                sleep 10
            fi
            echo ""
        fi
        
        echo "Commissioning Thread device (BLE-Thread)..."
        echo "Node ID: $NODE_ID"
        echo "PIN: $PIN_CODE"
        echo "Discriminator: $DISCRIMINATOR"
        echo ""
        
        # Phase 1 Runtime Fix: Enhanced retry logic with BlueZ state reset
        MAX_RETRIES=4
        BASE_DELAY_MS=500
        
        COMMISSION_SUCCESS=false
        
        for attempt in $(seq 1 $MAX_RETRIES); do
            if [ $attempt -gt 1 ]; then
                echo ""
                echo "━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━"
                echo "Retry attempt $attempt of $MAX_RETRIES"
                echo "━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━"
                
                # Reset BlueZ adapter state between retries
                echo "Resetting BlueZ adapter state..."
                hciconfig hci0 down 2>/dev/null || true
                sleep 1
                hciconfig hci0 up 2>/dev/null || true
                sleep 1
                hciconfig hci0 piscan 2>/dev/null || true
                bluetoothctl power on 2>/dev/null || true
                sleep 2
                
                # Exponential backoff: 500ms, 1000ms, 2000ms
                if [ $attempt -gt 2 ]; then
                    backoff_ms=$((BASE_DELAY_MS * (1 << (attempt - 2))))
                    echo "Waiting ${backoff_ms}ms before retry..."
                    sleep $((backoff_ms / 1000))
                else
                    sleep 1
                fi
                
                # Verify adapter is ready before retry
                if command -v verify-ble-ready &> /dev/null; then
                    if ! verify-ble-ready &>/dev/null; then
                        echo "Warning: Adapter not ready, skipping attempt $attempt"
                        continue
                    fi
                else
                    # Manual check
                    if ! hciconfig hci0 | grep -q "UP RUNNING"; then
                        echo "Warning: Adapter not ready, skipping attempt $attempt"
                        continue
                    fi
                fi
            fi
            
            echo ""
            echo "Attempt $attempt: Commissioning..."
            
            # Attempt commissioning
            if chip-tool pairing ble-thread $NODE_ID hex:$DATASET $PIN_CODE $DISCRIMINATOR $BYPASS_ATTESTATION 2>&1; then
                COMMISSION_SUCCESS=true
                echo ""
                echo "✓ Commissioning succeeded on attempt $attempt!"
                break
            else
                COMMISSION_RESULT=$?
                echo ""
                echo "✗ Commissioning attempt $attempt failed (exit code: $COMMISSION_RESULT)"
                
                # Check if error is connection abort (error 36)
                # This is a heuristic - actual error detection would be in SDK
                if [ $attempt -lt $MAX_RETRIES ]; then
                    echo "Will retry with BlueZ state reset..."
                fi
            fi
        done
        
        if [ "$COMMISSION_SUCCESS" = "false" ]; then
            echo ""
            echo "━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━"
            echo "✗ All $MAX_RETRIES commissioning attempts failed"
            echo "━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━"
            echo ""
            echo "Possible causes:"
            echo "  - BlueZ adapter timing issues (may need Phase 2 SDK patches)"
            echo "  - Device not in pairing mode"
            echo "  - Wrong PIN code or discriminator"
            echo "  - Device too far away or interference"
            echo ""
            echo "Next steps:"
            echo "  1. Verify device is in pairing mode (LED blinking)"
            echo "  2. Check BlueZ adapter: hciconfig hci0"
            echo "  3. Try again: matter-commission.sh thread-ble $NODE_ID $PIN_CODE $DISCRIMINATOR"
            echo "  4. If error 36 persists, Phase 2 SDK patches may be needed"
            exit 1
        fi
        ;;
        
    thread-onnetwork)
        if [ -z "$PIN_CODE" ]; then
            echo "Usage: matter-commission.sh thread-onnetwork <node_id> <pin_code>"
            echo "Example: matter-commission.sh thread-onnetwork 1 12345678"
            exit 1
        fi
        
        # Pre-flight checks
        echo "Pre-flight checks for Thread on-network commissioning..."
        
        # Check Thread network
        if ! command -v ot-ctl &> /dev/null; then
            echo "Error: ot-ctl not found"
            exit 1
        fi
        
        THREAD_STATE=$(ot-ctl state 2>/dev/null | grep -v "Done" | head -n 1)
        if [ -z "$THREAD_STATE" ] || [ "$THREAD_STATE" = "disabled" ] || [ "$THREAD_STATE" = "detached" ]; then
            echo "Warning: Thread network not active (state: $THREAD_STATE)"
            echo "Attempting to start Thread network..."
            ot-ctl ifconfig up 2>/dev/null || true
            ot-ctl thread start 2>/dev/null || true
            sleep 3
            THREAD_STATE=$(ot-ctl state 2>/dev/null | grep -v "Done" | head -n 1)
            if [ "$THREAD_STATE" = "disabled" ] || [ "$THREAD_STATE" = "detached" ]; then
                echo "Error: Thread network failed to start. Current state: $THREAD_STATE"
                echo "Please check OTBR service: systemctl status ot-br-posix"
                exit 1
            fi
        fi
        echo "✓ Thread network active (state: $THREAD_STATE)"
        
        # Check Avahi
        if systemctl is-active --quiet avahi-daemon; then
            echo "✓ Avahi daemon running"
        else
            echo "Warning: Avahi daemon not running. Starting..."
            systemctl start avahi-daemon || echo "Error: Failed to start Avahi"
            sleep 2
        fi
        
        echo ""
        echo "Commissioning Thread device (OnNetwork)..."
        echo "Node ID: $NODE_ID"
        echo "PIN: $PIN_CODE"
        echo "Thread State: $THREAD_STATE"
        echo ""
        echo "Note: Ensure device is in pairing mode and on Thread network"
        echo ""
        
        chip-tool pairing onnetwork $NODE_ID $PIN_CODE
        ;;
        
    wifi)
        if [ -z "$PIN_CODE" ]; then
            echo "Usage: matter-commission.sh wifi <node_id> <pin_code>"
            echo "Example: matter-commission.sh wifi 2 12345678"
            exit 1
        fi
        
        # Pre-flight checks
        echo "Pre-flight checks for Wi-Fi commissioning..."
        
        # Check Wi-Fi interface
        if ip link show wlan0 &>/dev/null; then
            WLAN_IP=$(ip addr show wlan0 | grep "inet " | awk '{print $2}' | cut -d/ -f1)
            if [ -n "$WLAN_IP" ]; then
                echo "✓ Wi-Fi interface active (IP: $WLAN_IP)"
            else
                echo "Warning: Wi-Fi interface exists but no IP address assigned"
            fi
        else
            echo "Warning: Wi-Fi interface wlan0 not found"
        fi
        
        # Check Avahi
        if systemctl is-active --quiet avahi-daemon; then
            echo "✓ Avahi daemon running"
        else
            echo "Warning: Avahi daemon not running. Starting..."
            systemctl start avahi-daemon || echo "Error: Failed to start Avahi"
            sleep 2
        fi
        
        echo ""
        echo "Commissioning Wi-Fi device..."
        echo "Node ID: $NODE_ID"
        echo "PIN: $PIN_CODE"
        echo ""
        echo "Note: Ensure device is in pairing mode and on same Wi-Fi network"
        echo ""
        
        chip-tool pairing onnetwork $NODE_ID $PIN_CODE
        ;;
        
    list)
        echo "Listing commissioned devices..."
        echo ""
        chip-tool pairing list
        echo ""
        
        # Also show Thread network devices if available
        if command -v ot-ctl &> /dev/null; then
            THREAD_STATE=$(ot-ctl state 2>/dev/null | grep -v "Done" | head -n 1)
            if [ -n "$THREAD_STATE" ] && [ "$THREAD_STATE" != "disabled" ] && [ "$THREAD_STATE" != "detached" ]; then
                echo "Thread network devices:"
                echo "---"
                ot-ctl router table 2>/dev/null | head -n 10
                ot-ctl child table 2>/dev/null | head -n 10
            fi
        fi
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


