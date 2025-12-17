/*
DM PACK
created with:
python /workspace/home/himal.d/MatterProtocol/build-raspberrypi4-64-rdk-broadband/tmp/work/cortexa72-rdk-linux/mesh-agent/rdkb-2024q3-kirkstone+git999-r0/recipe-sysroot-native/usr/bin/dm_pack_code_gen.py /workspace/home/himal.d/MatterProtocol/meta-cmf/../rdkb/components/opensource/ccsp/MeshAgent/config/TR181-MeshAgent.xml /workspace/home/himal.d/MatterProtocol/meta-cmf/../rdkb/components/opensource/ccsp/MeshAgent/source/MeshAgentSsp/dm_pack_datamodel.c
*/

#include "ansc_platform.h"
#include "ansc_xml_dom_parser_interface.h"
#include "dm_pack_xml_helper.h"
PVOID DMPackCreateDataModelXML(){
 PANSC_XML_DOM_NODE_OBJECT P0,P1,P2,P3,P4,P5,P6,P7,P8,P9;
 P0=DMPackCreatePNode(0,"dataModelInfo");
  P1=DMPackCreateNode(P0,"version","2",1);
  P1=DMPackCreateNode(P0,"moduleName","RDKCENTRAL_MeshAgent",20);
  P1=DMPackCreatePNode(P0,"author");
  P1=DMPackCreateNode(P0,"description","MeshAgent component",19);
  P1=DMPackCreatePNode(P0,"library");
   P2=DMPackCreateNode(P1,"path","libMeshAgentSsp",15);
   P2=DMPackCreateNode(P1,"func_Init","COSA_Init",9);
  P1=DMPackCreatePNode(P0,"objects");
   P2=DMPackCreateObject(P1, 0,"DeviceInfo",0);
    P3=DMPackCreatePNode(P2,"objects");
     P4=DMPackCreateObject(P3, 0,"X_RDKCENTRAL-COM_RFC",0);
      DMPackCreateFunctions(P4,"",0);
      P5=DMPackCreatePNode(P4,"parameters");
      P5=DMPackCreatePNode(P4,"objects");
       P6=DMPackCreateObject(P5, 0,"Feature",0);
        P7=DMPackCreatePNode(P6,"objects");
         P8=DMPackCreateObject(P7, 0,"OVS",0);
          DMPackCreateFunctions(P8,"OVS",2,10,15);
          P9=DMPackCreatePNode(P8,"parameters");
           DMPackCreateW(P9,"Enable",0,1);
         P8=DMPackCreateObject(P7, 0,"SM_APP",0);
          DMPackCreateFunctions(P8,"MeshAgent",2,10,15);
          P9=DMPackCreatePNode(P8,"parameters");
           DMPackCreateW(P9,"Disable",0,1);
         P8=DMPackCreateObject(P7, 0,"XleAdaptiveFh",0);
          DMPackCreateFunctions(P8,"XleAdaptiveFh",2,10,15);
          P9=DMPackCreatePNode(P8,"parameters");
           DMPackCreateW(P9,"Enable",0,1);
         P8=DMPackCreateObject(P7, 0,"MeshRetryReduction",0);
          DMPackCreateFunctions(P8,"MeshRetryReduction",2,10,15);
          P9=DMPackCreatePNode(P8,"parameters");
           DMPackCreateW(P9,"Enable",0,1);
         P8=DMPackCreateObject(P7, 0,"MeshWifiOptimization",0);
          DMPackCreateFunctions(P8,"MeshAgent",4,13,12,18,17);
          P9=DMPackCreatePNode(P8,"parameters");
           DMPackCreateParamTSW(P9,"Mode","string: Disable(0),Monitor(1),Enable(2)","uint32/mapped",1);
           DMPackCreateParamTSW(P9,"MwoBroker","string(128)","string",1);
           DMPackCreateW(P9,"ReinitPeriod",2,1);
         P8=DMPackCreateObject(P7, 0,"GRE_ACC",0);
          DMPackCreateFunctions(P8,"GreAcc",2,10,15);
          P9=DMPackCreatePNode(P8,"parameters");
           DMPackCreateW(P9,"Enable",0,1);
         P8=DMPackCreateObject(P7, 0,"MeshGREBackhaulCache",0);
          DMPackCreateFunctions(P8,"MeshGREBackhaulCache",2,10,15);
          P9=DMPackCreatePNode(P8,"parameters");
           DMPackCreateW(P9,"Enable",0,1);
         P8=DMPackCreateObject(P7, 0,"MeshSecuritySchemaLegacy",0);
          DMPackCreateFunctions(P8,"MeshSecuritySchemaLegacy",2,10,15);
          P9=DMPackCreatePNode(P8,"parameters");
           DMPackCreateW(P9,"Enable",0,1);
     P4=DMPackCreateObject(P3, 0,"X_RDKCENTRAL-COM_xOpsDeviceMgmt",0);
      P5=DMPackCreatePNode(P4,"objects");
       P6=DMPackCreateObject(P5, 0,"Mesh",0);
        DMPackCreateFunctions(P6,"MeshAgent",9,13,10,12,18,15,17,20,21,22);
        P7=DMPackCreatePNode(P6,"parameters");
         DMPackCreateW(P7,"Enable",0,1);
         DMPackCreateW(P7,"Data",3,1);
         DMPackCreateParamTSW(P7,"URL","string(128)","string",1);
         DMPackCreateParamTSW(P7,"State","string: Full(0),Monitor(1)","uint32/mapped",1);
         DMPackCreateParamTSW(P7,"Status","string: Off(0),Init(1),Monitor(2),Full(3)","uint32/mapped",0);
         DMPackCreateW(P7,"X_RDKCENTRAL-COM_Connected-Client",3,1);
         DMPackCreateW(P7,"PodEthernetBackhaulEnable",0,1);
         DMPackCreateW(P7,"XleModeCloudCtrlEnable",0,1);
         DMPackCreateW(P7,"Opensync",0,1);
       P6=DMPackCreateObject(P5, 0,"MWO",0);
        DMPackCreateFunctions(P6,"MWO",2,13,18);
        P7=DMPackCreatePNode(P6,"parameters");
         DMPackCreateW(P7,"AugmentedInterference",3,1);
         DMPackCreateW(P7,"Configs",3,1);
         DMPackCreateW(P7,"SteeringProfileData",3,1);
         DMPackCreateW(P7,"ClientProfileData",3,1);
         DMPackCreateW(P7,"WifiMotionSettings",3,1);
 return P0;
}
