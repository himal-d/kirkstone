/*
DM PACK
created with:
python /workspace/home/himal.d/MatterProtocol/build-raspberrypi4-64-rdk-broadband/tmp/work/cortexa72-rdk-linux/telemetry/rdkb-2024q3-kirkstone+git999-r0/recipe-sysroot-native/usr/bin/dm_pack_code_gen.py /workspace/home/himal.d/MatterProtocol/meta-cmf/../rdk/components/generic/telemetry/config/TR181-T2-USGv2.XML /workspace/home/himal.d/MatterProtocol/meta-cmf/../rdk/components/generic/telemetry/source/t2ssp/dm_pack_datamodel.c
*/

#include "ansc_platform.h"
#include "ansc_xml_dom_parser_interface.h"
#include "dm_pack_xml_helper.h"
PVOID DMPackCreateDataModelXML(){
 PANSC_XML_DOM_NODE_OBJECT P0,P1,P2,P3;
 P0=DMPackCreatePNode(0,"dataModelInfo");
  P1=DMPackCreateNode(P0,"version","1",1);
  P1=DMPackCreateNode(P0,"moduleName","COSA_TR181_T2_USGv2",19);
  P1=DMPackCreatePNode(P0,"author");
  P1=DMPackCreateNode(P0,"description","COSA TR181 Telemetry for USGv2",30);
  P1=DMPackCreatePNode(P0,"library");
   P2=DMPackCreateNode(P1,"path","libT2_tr181",11);
   P2=DMPackCreateNode(P1,"func_Init","COSA_Init",9);
   P2=DMPackCreateNode(P1,"func_Unload","COSA_Unload",11);
  P1=DMPackCreatePNode(P0,"objects");
   P2=DMPackCreateObject(P1, 0,"X_RDKCENTRAL-COM_T2",0);
    DMPackCreateFunctions(P2,"Telemetry",2,13,18);
    P3=DMPackCreatePNode(P2,"parameters");
     DMPackCreateW(P3,"ReportProfiles",3,1);
     DMPackCreateW(P3,"ReportProfilesMsgPack",3,1);
     DMPackCreateW(P3,"Temp_ReportProfiles",3,1);
   P2=DMPackCreateObject(P1, 0,"X_RDK_T2",0);
    DMPackCreateFunctions(P2,"Telemetry",1,12);
    P3=DMPackCreatePNode(P2,"parameters");
     DMPackCreateW(P3,"TotalUsedMem",2,0);
 return P0;
}
