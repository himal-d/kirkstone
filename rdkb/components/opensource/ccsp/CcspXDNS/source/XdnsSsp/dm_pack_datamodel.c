/*
DM PACK
created with:
python /workspace/home/himal.d/MatterProtocol/build-raspberrypi4-64-rdk-broadband/tmp/work/cortexa72-rdk-linux/ccsp-xdns/rdkb-2024q3-kirkstone+git999-r0/recipe-sysroot-native/usr/bin/dm_pack_code_gen.py /workspace/home/himal.d/MatterProtocol/meta-cmf/../rdkb/components/opensource/ccsp/CcspXDNS/config/CcspXdns_dm.xml /workspace/home/himal.d/MatterProtocol/meta-cmf/../rdkb/components/opensource/ccsp/CcspXDNS/source/XdnsSsp/dm_pack_datamodel.c
*/

#include "ansc_platform.h"
#include "ansc_xml_dom_parser_interface.h"
#include "dm_pack_xml_helper.h"
PVOID DMPackCreateDataModelXML(){
 PANSC_XML_DOM_NODE_OBJECT P0,P1,P2,P3,P4,P5,P6,P7,P8,P9;
 P0=DMPackCreatePNode(0,"dataModelInfo");
  P1=DMPackCreateNode(P0,"version","1",1);
  P1=DMPackCreateNode(P0,"moduleName","CcspXdnsSsp",11);
  P1=DMPackCreatePNode(P0,"author");
  P1=DMPackCreatePNode(P0,"description");
  P1=DMPackCreatePNode(P0,"library");
   P2=DMPackCreateNode(P1,"path","libdmlxdns",10);
   P2=DMPackCreateNode(P1,"func_Init","COSA_Init",9);
   P2=DMPackCreateNode(P1,"func_Unload","COSA_Unload",11);
   P2=DMPackCreateNode(P1,"func_MemoryCheck","COSA_MemoryCheck",16);
   P2=DMPackCreateNode(P1,"func_MemoryUsage","COSA_MemoryUsage",16);
   P2=DMPackCreateNode(P1,"func_MemoryTable","COSA_MemoryTable",16);
  P1=DMPackCreatePNode(P0,"objects");
   P2=DMPackCreateObject(P1, 0,"DeviceInfo",0);
    DMPackCreateFunctions(P2,"XDNSDeviceInfo",2,10,15);
    P3=DMPackCreatePNode(P2,"parameters");
     DMPackCreateW(P3,"X_RDKCENTRAL-COM_EnableXDNS",0,1);
    P3=DMPackCreatePNode(P2,"objects");
     P4=DMPackCreateObject(P3, 0,"X_RDKCENTRAL-COM_RFC",0);
      DMPackCreateFunctions(P4,"",0);
      P5=DMPackCreatePNode(P4,"parameters");
      P5=DMPackCreatePNode(P4,"objects");
       P6=DMPackCreateObject(P5, 0,"Feature",0);
        P7=DMPackCreatePNode(P6,"objects");
         P8=DMPackCreateObject(P7, 0,"AvoidUnNecesaryXDNSretries",0);
          DMPackCreateFunctions(P8,"XDNSRefac",2,10,15);
          P9=DMPackCreatePNode(P8,"parameters");
           DMPackCreateW(P9,"Enable",0,1);
   P2=DMPackCreateObject(P1, 0,"X_RDKCENTRAL-COM_XDNS",0);
    DMPackCreateFunctions(P2,"XDNS",7,13,18,10,15,20,21,22);
    P3=DMPackCreatePNode(P2,"parameters");
     DMPackCreateParamTSW(P3,"DefaultDeviceDnsIPv4","string(256)","string",1);
     DMPackCreateParamTSW(P3,"DefaultDeviceDnsIPv6","string(256)","string",1);
     DMPackCreateParamTSW(P3,"DefaultSecondaryDeviceDnsIPv4","string(256)","string",1);
     DMPackCreateParamTSW(P3,"DefaultSecondaryDeviceDnsIPv6","string(256)","string",1);
     DMPackCreateParamTSW(P3,"DefaultDeviceTag","string(256)","string",1);
     DMPackCreateW(P3,"DNSSecEnable",0,1);
     DMPackCreateW(P3,"Data",3,1);
    P3=DMPackCreatePNode(P2,"objects");
     P4=DMPackCreateObject(P3, 4,"DNSMappingTable","128");
      DMPackCreateFunctions(P4,"DNSMappingTable",11,0,2,5,6,3,4,13,18,20,21,22);
      P5=DMPackCreatePNode(P4,"parameters");
       DMPackCreateParamTSW(P5,"MacAddress","string(256)","string",1);
       DMPackCreateParamTSW(P5,"DnsIPv4","string(256)","string",1);
       DMPackCreateParamTSW(P5,"DnsIPv6","string(256)","string",1);
       DMPackCreateParamTSW(P5,"Tag","string(256)","string",1);
 return P0;
}
