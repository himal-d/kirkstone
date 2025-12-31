# Matter SDK Common Patches
# This file contains SDK-level patches that apply to all Matter applications
# (chip-tool, lighting-app, etc.) since they share the same connectedhomeip SDK source
#
# To use: Add "require matter-common-sdk-patches.inc" to your Matter recipe
# OR inherit matter-app-base.bbclass

# Phase 2 SDK patches for BLE error 36 fix (le-connection-abort-by-local)
# These patches modify src/platform/Linux/bluez/BluezEndpoint.cpp to:
# 1. Add delayed connect after device discovery (200ms delay)
# 2. Enhanced retry logic with BlueZ device state reset
# 3. Adapter readiness verification before ConnectDevice
#
# These are SDK-level changes that affect all Matter apps using BLE commissioning
# Target file: src/platform/Linux/bluez/BluezEndpoint.cpp

FILESEXTRAPATHS:prepend := "${THISDIR}/files:"

SRC_URI += "file://0002-BLE-Add-delayed-connect-after-scan.patch"
SRC_URI += "file://0003-BLE-Enhanced-retry-logic-with-state-reset.patch"
SRC_URI += "file://0004-BLE-Adapter-readiness-verification.patch"

