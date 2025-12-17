 - By default OMI functionality (in RDK) is controlled
   by DAC-sec distro feature see: rdkservices_git.bb
   for more details.

 - omi.service requires extra configuration to be enabled
   in the linux kernel. There is one place which aims to
   provide this configuration for your kernel
   see: dac-sec.inc for more details.