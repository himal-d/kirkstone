# Overview

In RDKV, previously a bash script "logRotateDaemon.sh" was executed to have a log rotation for the log files present in /opt/logs path by the provided Rotation count and Size from the "logRotate.properties" file. The logRotateDaemon.sh script was managed by systemd service "logrotate.service". RDKV has a systemd timer unit "logrotate.timer" which is configured to start "logrotate.service" for every 1 minute  to trigger "logRotateDaemon.sh". For every 1 minute, the execution of "logRotateDaemon.sh" consumes more CPU time comparing to the opensource logrotate binary.

To check the CPU time, the time comparison between the "logRotateDaemon.sh" bash script and the "open source log rotate binary" were tried as part of "RDK-41209 [PoC] Replace the RDK log rotate with open source log rotate module" ticket and it is concluded that open source logrotate module consumes less CPU time.

# Implementation details:
 1. Instead of logRotateDaemon.sh bash script, Open source logrotate binary will rotate the logs.
 2. Open source logrotate binary will now run as a separate Daemon. The Daemon will wake up every 1 minute. Systemd timer unit "logrotate.timer" configured to call the logrotate.service once on bootup after 2 mins wait time.
 3. Logrotate will execute by parsing the configuration file, where the configuration file has the log path, log filename, log size, and rotation count.
	<logpath/logfilename>{
	size <size>
        rotate <rotate count>
	}         
 4. The log files apart from the logrotate configuration file will be handled in a separate script and get rotate based on the constant size. It will be get called from the Daemon.
 5. Also, Daemon will be calling the existing handling of sending SIGHUP after rotating log files to close the fd of the log file.
 6. The creation of the logrotate configuration file is based on the newly designed framework which has been designed like syslog-ng configuration.  

# Framework
A new framework is developed to generate the logrotate configuration while building the image. The framework collect the following information from the recipe files.

 -Logrotate module name  
 -Logrotate log file name 
 -Logrotate size when harddisk is enabled 
 -Logrotate rotation count when harddisk is enabled 
 -Logrotate size when harddisk is disabled
 -Logrotate rotation count when harddisk is disabled

# logrotate.bbclass
A bbclass "logrotate" is developed to generate metadata files based on hdd enable and hdd disable cases by collecting data from recipes which inherited from the bbclass.

- A directory logrotate will be created - '${D}${sysconfdir}/logrotate/'
- All the values of logrotate will be collected from the recipes ( inherited the bbclass ) and placed at '${D}${sysconfdir}/logrotate/<PN><logname>_orig.metadata' and '${D}${sysconfdir}/logrotate/<PN><logname>_mem.metadata'
	Ex:sysintmessages_orig.metadata, sysintmessages_mem.metadata

# logrotate.inc
Post rootfs, the framework generates the logrotate configuration file "logrotatedata.conf" from the metadata files based on the Hard disk enable flag "HDD_ENABLED" from the device.properties.

- If the Hard disk is enabled, *_orig.metadata files are copied to the logrotate configuration file.
- If the Hard disk is disabed, *_mem.metadata files are copied to the logrotate configuraton file.
- After the creation of the logrotate configuration file, all the metadata files will be removed during the build time.
- The created logrotate configuration file will be present in /etc/logrotatedata.conf.

# Developer guide for introducing new log file
It is very simple to add a new log file for log rotation in RDKV via logrotate. 

Following are the steps to add the new logrotate facility in RDKV.

1. Figure out the Yocto recipe from where the systemd service is installed. The details must be updated in the respective recipe.
2. Inherit the bbclass "logrotate" in the recipe.
   - inherit logrotate
3. Add the logrotate name in the recipe. The LOGROTATE_NAME is the name which must be used for the further configurations. For easy understanding, keep the service name as LOGROTATE_NAME.
   - LOGROTATE_NAME = "<service_name>"
4. In the recipe, add the log file name.
   - LOGROTATE_LOGNAME_<servicename> = "<logfilename>"	
5. Add the size of the logrotate in the recipe when hard disk is enabled
   - LOGROTATE_SIZE_<servicename> = "<size>"
6. Add the rotate count of the logrotate in the recipe when hard disk is enabled
   - LOGROTATE_ROTATION_<servicename> = "<rotate count>"
7. Add the size of the logrotate in the recipe when hard disk is disabled 
   - LOGROTATE_SIZE_MEM_<servicename> = "<size>"
8. Add the rotate count of the logrotate in the recipe when the hard disk disabled
   - LOGROTATE_ROTATION_MEM_<servicename> = "<rotate count>"

## Example configurations:

1. meta-rdk-ext/recipes-common/lighttpd/lighttpd_1.4.53.bb

- inherit logrotate
- LOGROTATE_NAME="lighttpd"
- LOGROTATE_LOGNAME_lighttpd = "lighttpd*.log"
- #HDD_ENABLE
- LOGROTATE_SIZE_lighttpd    = "1048576"
- LOGROTATE_ROTATION_lighttpd  = "1"
- #HDD_DISABLE
- LOGROTATE_SIZE_MEM_lighttpd    = "204800"
- LOGROTATE_ROTATION_MEM_lighttpd  = "1"

2. meta-rdk-ext/recipes-connectivity/bluez/bluez5_5.%.bbappend  

- inherit logrotate
- LOGROTATE_NAME="bluez"
- LOGROTATE_LOGNAME_bluez="bluez.log"
- #HDD_DISABLE
- LOGROTATE_SIZE_MEM_bluez="250000"
- LOGROTATE_ROTATION_MEM_bluez="2"
- #HDD_ENABLE
- LOGROTATE_SIZE_bluez="512000"
- LOGROTATE_ROTATION_bluez="5"

# Confluence page
For more details, please refer https://etwiki.sys.comcast.net/display/CPE/RDK+Open+source+Logrotate+Daemon+Implementation
