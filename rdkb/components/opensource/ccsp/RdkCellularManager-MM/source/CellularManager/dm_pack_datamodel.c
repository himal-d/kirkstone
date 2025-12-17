/*
DM PACK
created with:
python /workspace/home/himal.d/MatterProtocol/build-raspberrypi4-64-rdk-broadband/tmp/work/cortexa72-rdk-linux/rdk-cellularmanager-mm/rdkb-2024q3-kirkstone+git999-r0/recipe-sysroot-native/usr/bin/dm_pack_code_gen.py /workspace/home/himal.d/MatterProtocol/meta-cmf/../rdkb/components/opensource/ccsp/RdkCellularManager-MM/config/RdkCellularManager.xml /workspace/home/himal.d/MatterProtocol/meta-cmf/../rdkb/components/opensource/ccsp/RdkCellularManager-MM/source/CellularManager/dm_pack_datamodel.c
*/

#include "ansc_platform.h"
#include "ansc_xml_dom_parser_interface.h"
#include "dm_pack_xml_helper.h"
PVOID DMPackCreateDataModelXML(){
 PANSC_XML_DOM_NODE_OBJECT P0,P1,P2,P3;
 P0=DMPackCreatePNode(0,"dataModelInfo");
  P1=DMPackCreateNode(P0,"version","1",1);
  P1=DMPackCreateNode(P0,"moduleName","TR181_RdkCellularManager",24);
  P1=DMPackCreatePNode(P0,"author");
  P1=DMPackCreatePNode(P0,"description");
  P1=DMPackCreatePNode(P0,"library");
  P1=DMPackCreatePNode(P0,"objects");
   P2=DMPackCreateObject(P1, 0,"Cellular",0);
    DMPackCreateFunctions(P2,"Cellular",9,10,15,12,17,13,18,20,21,22);
 return P0;
}
