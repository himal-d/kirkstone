mem_stress
==========
This program was developed to test zswap/zram/swap performance. 
It takes a few command line arguments that allows it to be very 
flexible. You can look at one of the test scripts like allocate_keep_busy.sh
for how they are supposed to be used. In case of doubt look at code, it is 
well commented.

src - contains the cpp file.
scripts - contains a scripts to setup swap or zram
test - contains the test scripts and their helper scripts.

Following kernel config parameters are need to enable both zswap and zram
it is always good to build zram as module as module takes device arguments

CONFIG_ZSWAP=y
CONFIG_FRONTSWAP=y
CONFIG_CRYPTO=y
CONFIG_LZO=y
CONFIG_CRYPTO_LZO=y
CONFIG_ZBUD=y
CONFIG_ZRAM=m
CONFIG_ZSMALLOC=y
