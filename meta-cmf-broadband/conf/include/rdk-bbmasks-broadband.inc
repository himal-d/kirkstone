BBMASK .= "|meta-rdk-broadband/recipes-extended/hwselftest/"

BBMASK .= "|meta-rdk/recipes-common/nlmonitor/"
BBMASK .= "|meta-rdk/recipes-connectivity/bluetooth/"

# Use the default jansson recipe in meta-openembedded
BBMASK .= "|meta-rdk-ext/recipes-support/jansson/"

BBMASK .= "|meta-cmf-raspberrypi/recipes-extended/wifi-client-hal/"

BBMASK .= "|meta-cmf/recipes-extended/rpcserver/"
