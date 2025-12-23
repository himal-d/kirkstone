# Matter POC Quick Test Reference
## Fast Validation Commands

---

## 🚀 Quick Start (5 Minutes)

```bash
# 1. Check services
systemctl status ot-br-posix chip-lighting-app avahi-daemon

# 2. Start Thread network
ot-ctl thread start
ot-ctl state

# 3. Test helpers
matter-commission.sh
get-thread-dataset.sh

# 4. Commission device (replace PIN/DISC)
matter-commission.sh thread-ble 1 12345678 3840

# 5. Verify and control
matter-commission.sh list
matter-commission.sh control-on 1 1
```

---

## ✅ One-Line Validation

```bash
# Full validation
systemctl is-active ot-br-posix chip-lighting-app avahi-daemon && \
ip link show wpan0 >/dev/null && \
ot-ctl state | grep -qE "child|router|leader" && \
chip-tool --help >/dev/null && \
command -v matter-commission >/dev/null && \
echo "✅ All checks passed" || echo "❌ Some checks failed"
```

---

## 🔍 Quick Diagnostics

```bash
# Service status
systemctl status ot-br-posix chip-lighting-app

# Thread network
ot-ctl state
ip link show wpan0

# Commissioned devices
chip-tool pairing list

# Recent errors
journalctl -p err -n 20
```

---

## 📝 Test Checklist

- [ ] Services running: `systemctl status ot-br-posix chip-lighting-app`
- [ ] Thread network: `ot-ctl state` shows active
- [ ] Helpers work: `matter-commission.sh` shows help
- [ ] Device commissioned: `chip-tool pairing list` shows device
- [ ] Control works: `matter-commission.sh control-on 1 1` succeeds

---

**For detailed testing, see POC_TESTING_VALIDATION.md**

