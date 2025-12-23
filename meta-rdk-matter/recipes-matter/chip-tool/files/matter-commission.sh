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

