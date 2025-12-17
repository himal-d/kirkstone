/*
DM PACK
created with:
python /workspace/home/himal.d/MatterProtocol/build-raspberrypi4-64-rdk-broadband/tmp/work/cortexa72-rdk-linux/ccsp-eth-agent/rdkb-2024q3-kirkstone+git999-r0/recipe-sysroot-native/usr/bin/dm_pack_code_gen.py /workspace/home/himal.d/MatterProtocol/meta-cmf/../rdkb/components/opensource/ccsp/CcspEthAgent/config/TR181-EthAgent.xml /workspace/home/himal.d/MatterProtocol/meta-cmf/../rdkb/components/opensource/ccsp/CcspEthAgent/source/EthSsp/dm_pack_datamodel.c
*/

#include "ansc_platform.h"
#include "ansc_xml_dom_parser_interface.h"
#include "dm_pack_xml_helper.h"
PVOID DMPackCreateDataModelXML(){
 PANSC_XML_DOM_NODE_OBJECT P0,P1,P2,P3,P4,P5,P6,P7;
 P0=DMPackCreatePNode(0,"dataModelInfo");
  P1=DMPackCreateNode(P0,"version","1",1);
  P1=DMPackCreateNode(P0,"moduleName","CcspEthAgent",12);
  P1=DMPackCreatePNode(P0,"author");
  P1=DMPackCreatePNode(P0,"description");
  P1=DMPackCreatePNode(P0,"library");
  P1=DMPackCreatePNode(P0,"objects");
   P2=DMPackCreateObject(P1, 0,"DeviceInfo",0);
    DMPackCreateFunctions(P2,"AutowanFeatureSupport",1,10);
    P3=DMPackCreatePNode(P2,"parameters");
     DMPackCreateW(P3,"X_RDKCENTRAL-COM_AutowanFeatureSupport",0,0);
    P3=DMPackCreatePNode(P2,"objects");
     P4=DMPackCreateObject(P3, 0,"X_RDKCENTRAL-COM_xOpsDeviceMgmt",0);
      P5=DMPackCreatePNode(P4,"objects");
       P6=DMPackCreateObject(P5, 0,"Logging",0);
        DMPackCreateFunctions(P6,"EthLogging",7,10,12,15,17,20,21,22);
        P7=DMPackCreatePNode(P6,"parameters");
         DMPackCreateW(P7,"xOpsDMEthLogEnabled",0,1);
         DMPackCreateW(P7,"xOpsDMEthLogPeriod",2,1);
   P2=DMPackCreateObject(P1, 0,"Ethernet",0);
    DMPackCreateFunctions(P2,"Ethernet",2,10,15);
    P3=DMPackCreatePNode(P2,"parameters");
     DMPackCreateW(P3,"X_RDKCENTRAL-COM_EthHost_Sync",0,1);
    P3=DMPackCreatePNode(P2,"objects");
     P4=DMPackCreateObject(P3, 0,"X_RDKCENTRAL-COM_WAN",0);
      DMPackCreateFunctions(P4,"EthWan",3,10,12,15);
      P5=DMPackCreatePNode(P4,"parameters");
       DMPackCreateW(P5,"Enabled",0,1);
       DMPackCreateW(P5,"Port",2,0);
     P4=DMPackCreateObject(P3, 1,"Interface","128");
      DMPackCreateFunctions(P4,"Interface",13,0,2,10,11,12,13,15,16,17,18,20,21,22);
      P5=DMPackCreatePNode(P4,"parameters");
       DMPackCreateW(P5,"Enable",0,1);
       DMPackCreateParamTS(P5,"Status","string: Up(1),Down(2),Unknown(3),Dormant(4),NotPresent(5),LowerLayerDown(6),Error(7)","uint32/mapped");
       DMPackCreateParamTSW(P5,"Alias","string(64)","string",1);
       DMPackCreateParamTS(P5,"Name","string(64)","string");
       DMPackCreateN(P5,"LastChange",2,0);
       DMPackCreateParamTSW(P5,"LowerLayers","string(1024)","string",1);
       DMPackCreateParam(P5,"Upstream",0);
       DMPackCreateParam(P5,"MACAddress",3);
       DMPackCreateParamTSW(P5,"MaxBitRate","int[-1:]","int",0);
       DMPackCreateW(P5,"CurrentBitRate",2,0);
       DMPackCreateParamTSW(P5,"DuplexMode","string: Half(1),Full(2),Auto(3)","uint32/mapped",1);
       DMPackCreateParam(P5,"X_CISCO_COM_AssociatedDevice",3);
      P5=DMPackCreatePNode(P4,"objects");
       P6=DMPackCreateObject(P5, 2,"X_RDKCENTRAL-COM_AssociatedDevice","256");
        DMPackCreateFunctions(P6,"AssociatedDevice1",5,0,2,5,6,13);
        P7=DMPackCreatePNode(P6,"parameters");
         DMPackCreateParamTSW(P7,"MACAddress","string(1024)","string",1);
       P6=DMPackCreateObject(P5, 0,"Stats",0);
        DMPackCreateFunctions(P6,"Stats",4,10,11,12,13);
        P7=DMPackCreatePNode(P6,"parameters");
         DMPackCreateN(P7,"BytesSent",3,0);
         DMPackCreateN(P7,"BytesReceived",3,0);
         DMPackCreateN(P7,"PacketsSent",2,0);
         DMPackCreateN(P7,"PacketsReceived",2,0);
         DMPackCreateN(P7,"ErrorsSent",2,0);
         DMPackCreateN(P7,"ErrorsReceived",2,0);
         DMPackCreateN(P7,"UnicastPacketsSent",2,0);
         DMPackCreateN(P7,"UnicastPacketsReceived",2,0);
         DMPackCreateN(P7,"DiscardPacketsSent",2,0);
         DMPackCreateN(P7,"DiscardPacketsReceived",2,0);
         DMPackCreateN(P7,"MulticastPacketsSent",2,0);
         DMPackCreateN(P7,"MulticastPacketsReceived",2,0);
         DMPackCreateN(P7,"BroadcastPacketsSent",2,0);
         DMPackCreateN(P7,"BroadcastPacketsReceived",2,0);
         DMPackCreateN(P7,"UnknownProtoPacketsReceived",2,0);
     P4=DMPackCreateObject(P3, 3,"X_RDK_Interface","128");
      DMPackCreateFunctions(P4,"EthRdkInterface",13,0,2,3,4,10,13,18,17,12,15,20,21,22);
      P5=DMPackCreatePNode(P4,"parameters");
       DMPackCreateW(P5,"Upstream",0,1);
       DMPackCreateW(P5,"WanValidated",0,1);
       DMPackCreateParamTSW(P5,"Name","string(64)","string",1);
       DMPackCreateParamTS(P5,"Status","string: Up(1), Down(2)","uint32/mapped");
       DMPackCreateParamTSW(P5,"WanStatus","string: Up(1),Down(2)","uint32/mapped",1);
       DMPackCreateW(P5,"Enable",0,1);
       DMPackCreateParamTSW(P5,"LowerLayers","string(128)","string",1);
       DMPackCreateParam(P5,"WanConfigPort",0);
       DMPackCreateW(P5,"AddToLanBridge",0,1);
 return P0;
}
