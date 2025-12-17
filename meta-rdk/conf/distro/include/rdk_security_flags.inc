# ASLR enabled
# we set this to "y" or "n" and use it as a conditional later

ASLR = "${@bb.utils.contains('DISTRO_FEATURES', 'aslr', 'y', 'n', d)}"

# toggle aslr off for specific packages
ASLR_pn-ccsp-wifi-agent = "n"
ASLR_pn-docsis = "n"
# ASLR_pn-hal-wifi = "n"
ASLR_pn-hal-wifi-xb3 = "n"
ASLR_pn-mesh-agent = "n"
ASLR_pn-tr69hostif = "n"
ASLR_pn-xre-receiver-default = "n"
ASLR_pn-pxcore-libnode = "n"
ASLR_pn-qtbase = "n"
ASLR_pn-ccsp-xconf = "n"
ASLR_pn-qtn-csmd-logic = "n"
ASLR_pn-plumewifi = "n"
ASLR_pn-hal-mta-broadcom = "n"
ASLR_pn-hal-wifi-ciscoxb3 = "n"
ASLR_pn-broadcom-refsw = "n"
ASLR_pn-broadcom-ursr = "n"
ASLR_pn-ccsp-xdns = "n"

# Warn on use of format strings that represent possible security problems
SECURITY_STRINGFORMAT ?= "-Wformat -Wformat-security -Wno-error=format-security"

# packages which explicitly set a "-Wno-format" preventing the -Wformat-security checks
# (we remove -Wformat-security or the compiler crashes on the conflict with -Wno-format)

SECURITY_STRINGFORMAT_pn-audiohal = ""
SECURITY_STRINGFORMAT_pn-gptimer = ""
SECURITY_STRINGFORMAT_pn-halsnmp = ""
SECURITY_STRINGFORMAT_pn-pcd = ""
SECURITY_STRINGFORMAT_pn-qtn-qwcfg = ""
SECURITY_STRINGFORMAT_pn-rmfgeneric = ""
SECURITY_STRINGFORMAT_pn-rmfpodmgr = ""
SECURITY_STRINGFORMAT_pn-rmfpodserver = ""
SECURITY_STRINGFORMAT_pn-runsnmp = ""
SECURITY_STRINGFORMAT_pn-snmpmanager-priv = ""

# ASLR support
# --enable-default-pie   compile as position independent executable (gcc-6.x)
# -no-pie                cancel the effects of --enable-default-pie (gcc-6.x)
#
# Additional compile flags
# _FORTIFY_SOURCE        perform additional compile time checks
# -fstack-protector      protect stack against buffer overruns
# -Wl,-z,relro,-z,now    prevent changes to relocation entries

SECURITY_NOPIE ?= "${@ASLR == "y" and GCCVERSION > "6.0" and "-no-pie -fno-PIE" or ""}"
SECURITY_FORTIFY ?= "-D_FORTIFY_SOURCE=2 -Wno-error=unused-result"
SECURITY_CFLAGS ?= "-fstack-protector ${SECURITY_FORTIFY} ${SECURITY_STRINGFORMAT}"
SECURITY_NO_PIE_CFLAGS ?= "-fstack-protector ${SECURITY_FORTIFY} ${SECURITY_STRINGFORMAT} ${SECURITY_NOPIE}"
SECURITY_LDFLAGS ?= "-fstack-protector -Wl,-z,relro"
# removed this from SECURITY_LDFLAGS ",-z,now"

# packages which break due to the extra compiler checks enabled by _FORTIFY
# most of these are caused by calls to open() with O_CREAT that are mising file permissions
# (TODO: patch compile issues and remove these lines)

SECURITY_FORTIFY_pn-alljoyn = ""
SECURITY_FORTIFY_pn-audiohal = ""
SECURITY_FORTIFY_pn-avcap-samples = ""
SECURITY_FORTIFY_pn-bluetooth-core = ""
SECURITY_FORTIFY_pn-ccsp-tr069-pa = ""
SECURITY_FORTIFY_pn-ccsp-p-and-m = ""
SECURITY_FORTIFY_pn-ccsp-snmp-pa = ""
SECURITY_FORTIFY_pn-comcast-firmwaretool = ""
SECURITY_FORTIFY_pn-ctrlm-testapp = ""
SECURITY_FORTIFY_pn-dial = ""
SECURITY_FORTIFY_pn-docsis = ""
SECURITY_FORTIFY_pn-ebtables = ""
SECURITY_FORTIFY_pn-ecfs-search = ""
SECURITY_FORTIFY_pn-extswitch = ""
SECURITY_FORTIFY_pn-factory-nvram = ""
SECURITY_FORTIFY_pn-gdb = ""
SECURITY_FORTIFY_pn-hal-cm-xb6 = ""
SECURITY_FORTIFY_pn-keyutils = ""
SECURITY_FORTIFY_pn-libarris-nvm = ""
SECURITY_FORTIFY_pn-liblan-service = ""
SECURITY_FORTIFY_pn-libpcd = ""
SECURITY_FORTIFY_pn-libunwind = ""
SECURITY_FORTIFY_pn-logger = ""
SECURITY_FORTIFY_pn-mini-cli = ""
SECURITY_FORTIFY_pn-mfrlib-samsung = ""
SECURITY_FORTIFY_pn-ncurses = ""
SECURITY_FORTIFY_pn-otamgr = ""
SECURITY_FORTIFY_pn-pcd = ""
SECURITY_FORTIFY_pn-production-data = ""
SECURITY_FORTIFY_pn-qca = ""
SECURITY_FORTIFY_pn-qtn-qwcfg = ""
SECURITY_FORTIFY_pn-qtn-qevent = ""
SECURITY_FORTIFY_pn-rdkbrowser2 = ""
SECURITY_FORTIFY_pn-ucresolv = ""
SECURITY_FORTIFY_pn-upgradebox = ""
SECURITY_FORTIFY_pn-utopia = ""
SECURITY_FORTIFY_pn-xrtestapp = ""
SECURITY_FORTIFY_pn-broadcom-mocadriver = ""


# workarounds for various packages
SECURITY_CFLAGS_append_pn-broadcom-refsw = " ${SECURITY_NOPIE} ${SECURITY_LDFLAGS}"
SECURITY_CFLAGS_append_pn-broadcom-ursr = " ${SECURITY_NOPIE} ${SECURITY_LDFLAGS}"
SECURITY_CFLAGS_append_pn-ctrlm-main = " ${SECURITY_NOPIE} ${SECURITY_LDFLAGS}"

# don't set eglibc compile flags
SECURITY_CFLAGS_pn-eglibc = ""
SECURITY_CFLAGS_pn-eglibc-initial = ""
SECURITY_LDFLAGS_remove_pn-eglibc = "-fstack-protector"
SECURITY_LDFLAGS_remove_pn-eglibc-initial = "-fstack-protector"

# don't set glibc compile flags
SECURITY_CFLAGS_pn-glibc = ""
SECURITY_CFLAGS_pn-glibc-initial = ""
SECURITY_LDFLAGS_remove_pn-glibc = "-fstack-protector"
SECURITY_LDFLAGS_remove_pn-glibc-initial = "-fstack-protector"

SECURITY_CFLAGS_pn-gcc-runtime = ""
SECURITY_LDFLAGS_remove_pn-gcc-runtime = "-fstack-protector"

# kernel modules can't be -pie
TARGET_CC_KERNEL_ARCH_append = " ${SECURITY_NOPIE}"
MAKE_append_pn-broadcom-refsw = " KCFLAGS=-fno-PIE"
MAKE_append_pn-broadcom-ursr = " KCFLAGS=-fno-PIE"
MOD_OPTS_append_pn-broadcom-rgdriver = " KCFLAGS=-fno-PIE"

TARGET_CC_ARCH_append_class-target = " ${@ASLR == "y" and SECURITY_CFLAGS or ""}"
TARGET_LDFLAGS_append_class-target = " ${@ASLR == "y" and SECURITY_LDFLAGS or ""}"
