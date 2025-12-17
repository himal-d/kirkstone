inherit coverity

DEPENDS += "json-c"

LDFLAGS += "-lbreakpadwrapper -lpthread"
