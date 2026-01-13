# Matter SDK Patch Propagation - Implementation Example

## Quick Answer

**Your QR code BLE patch in `matter-common-sdk-patches.inc` is NOT automatically applied.**

You must add **one line** to each Matter recipe to propagate patches.

---

## Required Change Per Recipe

### Before (Current State)

```bitbake
# chip-tool.bb
inherit systemd
# ❌ Missing patch propagation
```

### After (Fixed)

```bitbake
# chip-tool.bb
inherit systemd
inherit matter-app-base  # ← ADD THIS LINE
```

---

## Complete Recipe Update Examples

### Example 1: chip-tool.bb

```bitbake
PN = "chip-tool"
SUMMARY = "Chip Tools CLI"
LICENSE = "Apache-2.0"
LIC_FILES_CHKSUM = "file://${COMMON_LICENSE_DIR}/Apache-2.0;md5=89aea4e17d99a7cacdbeed46a0096b10"

SRCBRANCH = "v1.4-branch-nxp_imx_2025_q1"
IMX_MATTER_SRC ?= "gitsm://github.com/NXP/matter.git;protocol=https"
SRC_URI = "${IMX_MATTER_SRC};branch=${SRCBRANCH}"
SRC_URI += "file://chip-tool.service"
SRC_URI += "file://matter-commission.sh"
SRC_URI += "file://verify-ble-ready.sh"
SRC_URI += "file://wifi-ble-coexistence.sh"
MATTER_PY_PATH ?= "${STAGING_BINDIR_NATIVE}/python3-native/python3"

inherit systemd
inherit matter-app-base  # ← ADD THIS LINE

SYSTEMD_SERVICE:${PN} = "chip-tool.service"
SYSTEMD_AUTO_ENABLE:${PN} = "disable"

# ... rest of recipe unchanged
```

### Example 2: chip-all-clusters-app.bb

```bitbake
PN = "chip-all-clusters-app"
SUMMARY = "Matter Chip All Clusters App CLI"
LICENSE = "Apache-2.0"
LIC_FILES_CHKSUM = "file://${COMMON_LICENSE_DIR}/Apache-2.0;md5=89aea4e17d99a7cacdbeed46a0096b10"

SRCBRANCH = "v1.4-branch-nxp_imx_2025_q1"
IMX_MATTER_SRC ?= "gitsm://github.com/NXP/matter.git;protocol=https"
SRC_URI = "${IMX_MATTER_SRC};branch=${SRCBRANCH}"
SRC_URI += "file://chip-all-clusters-app.service"
# ... other files
MATTER_PY_PATH ?= "${STAGING_BINDIR_NATIVE}/python3-native/python3"

inherit systemd
inherit matter-app-base  # ← ADD THIS LINE

# ... rest of recipe unchanged
```

---

## All Recipes That Need This Change

Add `inherit matter-app-base` to:

1. ✅ `chip-tool/chip-tool.bb`
2. ✅ `chip-all-clusters-app/chip-all-clusters-app.bb`
3. ✅ `chip-lighting-app/chip-lighting-app.bb`
4. ✅ `chip-bridge-app/chip-bridge-app.bb`
5. ✅ `chip-ota-provider-app/chip-ota-provider-app.bb`
6. ✅ `chip-ota-requestor-app/chip-ota-requestor-app.bb`
7. ✅ `chip-energy-management-app/chip-energy-management-app.bb`
8. ✅ Any other Matter app recipes

---

## Verification Commands

After making changes, verify patches are applied:

```bash
# 1. Check recipes inherit matter-app-base
grep -r "inherit matter-app-base" meta-rdk-matter/recipes-matter/*/*.bb

# 2. Build and check patch application
bitbake chip-tool -c patch

# 3. Verify SRC_URI includes patches
bitbake -e chip-tool | grep "SRC_URI.*\.patch"

# 4. Check patch was applied to source
find tmp/work -path "*/chip-tool/*/git/src/platform/Linux/bluez/BluezEndpoint.cpp" \
    -exec grep -l "your-patch-content" {} \;
```

---

## Why This Works

```
matter-common-sdk-patches.inc
    ↓ (defines SRC_URI += "file://your-patch.patch")
    ↓
matter-app-base.bbclass
    ↓ (require matter-common-sdk-patches.inc)
    ↓
Your Recipe (inherit matter-app-base)
    ↓ (inherits SRC_URI from bbclass)
    ↓
Patches Applied ✅
```

Without `inherit matter-app-base`, the recipe's `SRC_URI` never includes the patches.

