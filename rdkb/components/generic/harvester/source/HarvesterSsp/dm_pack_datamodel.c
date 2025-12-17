/*
DM PACK
created with:
python /workspace/home/himal.d/MatterProtocol/build-raspberrypi4-64-rdk-broadband/tmp/work/cortexa72-rdk-linux/harvester/rdkb-2024q3-kirkstone+git999-r0/recipe-sysroot-native/usr/bin/dm_pack_code_gen.py /workspace/home/himal.d/MatterProtocol/meta-cmf/../rdkb/components/generic/harvester/config-atom/Harvester.XML /workspace/home/himal.d/MatterProtocol/meta-cmf/../rdkb/components/generic/harvester/source/HarvesterSsp/dm_pack_datamodel.c
*/

#include "ansc_platform.h"
#include "ansc_xml_dom_parser_interface.h"
#include "dm_pack_xml_helper.h"
PVOID DMPackCreateDataModelXML(){
 PANSC_XML_DOM_NODE_OBJECT P0,P1,P2,P3,P4,P5,P6,P7;
 P0=DMPackCreatePNode(0,"dataModelInfo");
  P1=DMPackCreateNode(P0,"version","1",1);
  P1=DMPackCreateNode(P0,"moduleName","COSA_TR181_Harvester",20);
  P1=DMPackCreatePNode(P0,"author");
  P1=DMPackCreatePNode(P0,"description");
  P1=DMPackCreatePNode(P0,"library");
   P2=DMPackCreateNode(P1,"path","libHarvesterSsp",15);
   P2=DMPackCreateNode(P1,"func_Init","COSA_Init",9);
  P1=DMPackCreatePNode(P0,"objects");
   P2=DMPackCreateObject(P1, 0,"X_RDKCENTRAL-COM_Report",0);
    P3=DMPackCreatePNode(P2,"objects");
     P4=DMPackCreateObject(P3, 0,"InterfaceDevicesWifi",0);
      DMPackCreateFunctions(P4,"InterfaceDevicesWifi",8,10,12,15,17,13,20,21,22);
      P5=DMPackCreatePNode(P4,"parameters");
       DMPackCreateW(P5,"Enabled",0,1);
       DMPackCreateW(P5,"ReportingPeriod",2,1);
       DMPackCreateW(P5,"PollingPeriod",2,1);
       DMPackCreateW(P5,"Schema",3,0);
       DMPackCreateW(P5,"SchemaID",3,0);
      P5=DMPackCreatePNode(P4,"objects");
       P6=DMPackCreateObject(P5, 0,"Default",0);
        DMPackCreateFunctions(P6,"InterfaceDevicesWifi_Default",2,12,17);
        DMPackCreateFunctions(P6,"InterfaceDevicesWifi",3,20,21,22);
        P7=DMPackCreatePNode(P6,"parameters");
         DMPackCreateW(P7,"ReportingPeriod",2,1);
         DMPackCreateW(P7,"PollingPeriod",2,1);
         DMPackCreateW(P7,"OverrideTTL",2,0);
     P4=DMPackCreateObject(P3, 0,"RadioInterfaceStatistics",0);
      DMPackCreateFunctions(P4,"RadioInterfaceStatistics",8,10,12,15,17,13,20,21,22);
      P5=DMPackCreatePNode(P4,"parameters");
       DMPackCreateW(P5,"Enabled",0,1);
       DMPackCreateW(P5,"ReportingPeriod",2,1);
       DMPackCreateW(P5,"PollingPeriod",2,1);
       DMPackCreateW(P5,"Schema",3,0);
       DMPackCreateW(P5,"SchemaID",3,0);
      P5=DMPackCreatePNode(P4,"objects");
       P6=DMPackCreateObject(P5, 0,"Default",0);
        DMPackCreateFunctions(P6,"RadioInterfaceStatistics_Default",2,12,17);
        DMPackCreateFunctions(P6,"RadioInterfaceStatistics",3,20,21,22);
        P7=DMPackCreatePNode(P6,"parameters");
         DMPackCreateW(P7,"ReportingPeriod",2,1);
         DMPackCreateW(P7,"PollingPeriod",2,1);
         DMPackCreateW(P7,"OverrideTTL",2,0);
     P4=DMPackCreateObject(P3, 0,"NeighboringAP",0);
      DMPackCreateFunctions(P4,"NeighboringAP",8,10,12,15,17,13,20,21,22);
      P5=DMPackCreatePNode(P4,"parameters");
       DMPackCreateW(P5,"Enabled",0,1);
       DMPackCreateW(P5,"ReportingPeriod",2,1);
       DMPackCreateW(P5,"PollingPeriod",2,1);
       DMPackCreateW(P5,"Schema",3,0);
       DMPackCreateW(P5,"SchemaID",3,0);
       DMPackCreateW(P5,"OnDemandScan",0,1);
       DMPackCreateW(P5,"LastScanData",3,0);
      P5=DMPackCreatePNode(P4,"objects");
       P6=DMPackCreateObject(P5, 0,"Default",0);
        DMPackCreateFunctions(P6,"NeighboringAP_Default",2,12,17);
        DMPackCreateFunctions(P6,"NeighboringAP",3,20,21,22);
        P7=DMPackCreatePNode(P6,"parameters");
         DMPackCreateW(P7,"ReportingPeriod",2,1);
         DMPackCreateW(P7,"PollingPeriod",2,1);
         DMPackCreateW(P7,"OverrideTTL",2,0);
 return P0;
}
