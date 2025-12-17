/*
DM PACK
created with:
python /workspace/home/himal.d/MatterProtocol/build-raspberrypi4-64-rdk-broadband/tmp/work/cortexa72-rdk-linux/ccsp-hotspot/rdkb-2024q3-kirkstone+git999-r0/recipe-sysroot-native/usr/bin/dm_pack_code_gen.py /workspace/home/himal.d/MatterProtocol/meta-cmf/../rdkb/components/opensource/ccsp/hotspot/source/hotspotfd/config/hotspot.XML /workspace/home/himal.d/MatterProtocol/meta-cmf/../rdkb/components/opensource/ccsp/hotspot/source/hotspotfd/dm_pack_datamodel.c
*/

#include "ansc_platform.h"
#include "ansc_xml_dom_parser_interface.h"
#include "dm_pack_xml_helper.h"
PVOID DMPackCreateDataModelXML(){
 PANSC_XML_DOM_NODE_OBJECT P0,P1,P2,P3,P4,P5;
 P0=DMPackCreatePNode(0,"dataModelInfo");
  P1=DMPackCreateNode(P0,"version","1",1);
  P1=DMPackCreateNode(P0,"moduleName","COSA_TR181_USGv2",16);
  P1=DMPackCreatePNode(P0,"author");
  P1=DMPackCreatePNode(P0,"description");
  P1=DMPackCreatePNode(P0,"library");
  P1=DMPackCreatePNode(P0,"objects");
   P2=DMPackCreateObject(P1, 0,"X_COMCAST-COM_GRE",0);
    P3=DMPackCreatePNode(P2,"objects");
     P4=DMPackCreateObject(P3, 0,"Hotspot",0);
      DMPackCreateFunctions(P4,"HotspotConnectedDevice",2,13,18);
      P5=DMPackCreatePNode(P4,"parameters");
       DMPackCreateW(P5,"ClientChange",3,1);
 return P0;
}
