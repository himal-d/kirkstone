
OPTIMIZE_DEFAULT = "-O2"

LAYERDEPENDS_rdk_remove = "multimedia-layer"

#set platform type (broadband, hybrid, or client)
MACHINEOVERRIDES .= ":rdkx:voicecontrol"

PRODUCT_apq8009         :="base"
PRODUCT_SUBTYPE_apq8009 :=""

# Allow missing base recipe files for our bbappends
BB_DANGLINGAPPENDS_WARNONLY ?= "true"

PREFERRED_VERSION_openssl = "1.0.2o"

#Masking CEDM 3.X source recipes
RDKXCPGSRCMASK ?= "|.cpgu-src|.cpgc-src|.cpg-src|.cpg-libs-src"
BBMASK .= "${RDKXCPGSRCMASK}"
