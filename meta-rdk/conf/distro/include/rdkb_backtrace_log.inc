# backtrace logging is enabled
# we set this to "y" or "n" and use it as a conditional later

LOG_BACKTRACE = "${@bb.utils.contains('DISTRO_FEATURES', 'logbacktrace', 'y', 'n', d)}"

BACKTRACE_LDFLAGS ?= ""
BACKTRACE_DEPENDS ?= ""


BACKTRACE_DEPENDS_pn-ccsp-gwprovapp = " breakpad-wrapper"
BACKTRACE_DEPENDS_pn-utopia = " breakpad-wrapper"
BACKTRACE_DEPENDS_pn-parodus = " breakpad-wrapper"
BACKTRACE_DEPENDS_pn-mqttcm = " breakpad-wrapper"

BACKTRACE_LDFLAGS_pn-ccsp-gwprovapp = " -lbreakpadwrapper "
BACKTRACE_LDFLAGS_pn-utopia = " -Wl,--no-as-needed -lbreakpadwrapper -Wl,--as-needed "
BACKTRACE_LDFLAGS_pn-parodus = " -Wl,--no-as-needed -lbreakpadwrapper -Wl,--as-needed "
BACKTRACE_LDFLAGS_pn-mqttcm = " -Wl,--no-as-needed -lbreakpadwrapper -Wl,--as-needed "

DEPENDS_append = " ${@LOG_BACKTRACE == "y" and BACKTRACE_DEPENDS or ""}"
LDFLAGS_append = " ${@LOG_BACKTRACE == "y" and BACKTRACE_LDFLAGS or ""}"
