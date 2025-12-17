/*
DM PACK
created with:
python /workspace/home/himal.d/MatterProtocol/build-raspberrypi4-64-rdk-broadband/tmp/work/cortexa72-rdk-linux/rdk-fwupgrade-manager/rdkb-2024q3-kirkstone+git999-r0/recipe-sysroot-native/usr/bin/dm_pack_code_gen.py /workspace/home/himal.d/MatterProtocol/meta-cmf/../rdkb/components/opensource/ccsp/RdkPlatformManager/config/RdkFwUpgradeManager.xml /workspace/home/himal.d/MatterProtocol/meta-cmf/../rdkb/components/opensource/ccsp/RdkPlatformManager/source/FwUpgradeManager/dm_pack_datamodel.c
*/

#include "ansc_platform.h"
#include "ansc_xml_dom_parser_interface.h"
#include "dm_pack_xml_helper.h"
PVOID DMPackCreateDataModelXML(){
 PANSC_XML_DOM_NODE_OBJECT P0,P1,P2,P3,P4,P5,P6,P7;
 P0=DMPackCreatePNode(0,"dataModelInfo");
  P1=DMPackCreateNode(P0,"version","1",1);
  P1=DMPackCreateNode(P0,"moduleName","TR181_RdkFirmwareUpgradeManager",31);
  P1=DMPackCreatePNode(P0,"author");
  P1=DMPackCreatePNode(P0,"description");
  P1=DMPackCreatePNode(P0,"library");
  P1=DMPackCreatePNode(P0,"objects");
   P2=DMPackCreateObject(P1, 0,"DeviceInfo",0);
    DMPackCreateFunctions(P2,"FirmwareUpgrade",6,13,18,10,15,11,16);
    P3=DMPackCreatePNode(P2,"parameters");
     DMPackCreateParam(P3,"X_RDKCENTRAL-COM_FirmwareDownloadStatus",3);
     DMPackCreateW(P3,"X_RDKCENTRAL-COM_FirmwareDownloadProtocol",3,1);
     DMPackCreateW(P3,"X_RDKCENTRAL-COM_FirmwareDownloadURL",3,1);
     DMPackCreateW(P3,"X_RDKCENTRAL-COM_FirmwareToDownload",3,1);
     DMPackCreateW(P3,"X_RDKCENTRAL-COM_FirmwareDownloadNow",0,1);
     DMPackCreateW(P3,"X_RDKCENTRAL-COM_FirmwareDownloadAndFactoryReset",1,1);
    P3=DMPackCreatePNode(P2,"objects");
     P4=DMPackCreateObject(P3, 0,"X_RDKCENTRAL-COM_xOpsDeviceMgmt",0);
      DMPackCreateFunctions(P4,"",0);
      P5=DMPackCreatePNode(P4,"parameters");
      P5=DMPackCreatePNode(P4,"objects");
       P6=DMPackCreateObject(P5, 0,"RPC",0);
        DMPackCreateFunctions(P6,"FirmwareUpgradeRPC",2,12,17);
        P7=DMPackCreatePNode(P6,"parameters");
         DMPackCreateW(P7,"DeferFWDownloadReboot",2,1);
 return P0;
}
