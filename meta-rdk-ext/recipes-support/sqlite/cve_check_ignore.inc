#This file will be included for yocto versions dunfell and higher
# -19242 is only an issue in specific development branch commits
CVE_CHECK_IGNORE += "CVE-2019-19242"
# This is believed to be iOS specific (https://groups.google.com/g/sqlite-dev/c/U7OjAbZO6LA)
CVE_CHECK_IGNORE += "CVE-2015-3717"
