/*
 * If not stated otherwise in this file or this component's LICENSE file the
 * following copyright and licenses apply:
 *
 * Copyright 2016 RDK Management
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
*/

/**********************************************************************
   Copyright [2014] [Cisco Systems, Inc.]
 
   Licensed under the Apache License, Version 2.0 (the "License");
   you may not use this file except in compliance with the License.
   You may obtain a copy of the License at
 
       http://www.apache.org/licenses/LICENSE-2.0
 
   Unless required by applicable law or agreed to in writing, software
   distributed under the License is distributed on an "AS IS" BASIS,
   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
   See the License for the specific language governing permissions and
   limitations under the License.
**********************************************************************/


/**********************************************************************

    module:	cosa_apis_util.h

        This is base file for all parameters H files.

    ---------------------------------------------------------------

    description:

        This file contains all utility functions for COSA DML API development.

    ---------------------------------------------------------------

    environment:

        COSA independent

    ---------------------------------------------------------------

    author:

        Roger Hu

    ---------------------------------------------------------------

    revision:

        01/30/2011    initial revision.

**********************************************************************/



#include "cosa_apis.h"
#include "plugin_main_apis.h"

#include <stdio.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/ioctl.h>
#include <sys/socket.h>
#include <net/if.h>

#include "ansc_platform.h"
#include "safec_lib_common.h"
#define NUM_INTERFACE_TYPES (sizeof(interface_type_table)/sizeof(interface_type_table[0]))

enum DeviceInterfaceType {
    ETHERNET_INTERFACE,
    IP_INTERFACE,
    USB_INTERFACE,
    HPNA_INTERFACE,
    DSL_INTERFACE,
    WIFI_INTERFACE,
    HOMEPLUG_INTERFACE,
    MOCA_INTERFACE,
    UPA_INTERFACE,
    ATM_LINK_INTERFACE,
    PTM_LINK_INTERFACE,
    ETHERNET_LINK_INTERFACE,
    ETHERNET_VLANT_INTERFACE,
    WIFI_SSID_INTERFACE,
    BRIDGING_INTERFACE,
    PPP_INTERFACE,
    DSL_CHANNEL_INTERFACE
};

typedef struct {
  char     *name;
  enum DeviceInterfaceType      type;
} DEVICE_INTERFACE_PAIR;

DEVICE_INTERFACE_PAIR interface_type_table[] = {
  { "Device.Ethernet.Interface.",  ETHERNET_INTERFACE },
  { "Device.IP.Interface.",   IP_INTERFACE },
  { "Device.USB.Interface.", USB_INTERFACE },
  { "Device.HPNA.Interface.",   HPNA_INTERFACE },
  { "Device.DSL.Interface.",  DSL_INTERFACE },
  { "Device.WiFi.Radio.",  WIFI_INTERFACE },
  { "Device.HomePlug.Interface.",  HOMEPLUG_INTERFACE },
  { "Device.MoCA.Interface.",  MOCA_INTERFACE },
  { "Device.UPA.Interface.",  UPA_INTERFACE },
  { "Device.ATM.Link.",  ATM_LINK_INTERFACE },
  { "Device.PTM.Link.",  PTM_LINK_INTERFACE },
  { "Device.Ethernet.Link.",  ETHERNET_LINK_INTERFACE },
  { "Device.Ethernet.VLANTermination.",  ETHERNET_VLANT_INTERFACE },
  { "Device.WiFi.SSID.",  WIFI_SSID_INTERFACE },
  { "Device.Bridging.Bridge.",  BRIDGING_INTERFACE },
  { "Device.PPP.Interface.",  PPP_INTERFACE },
  { "Device.DSL.Channel.",  DSL_CHANNEL_INTERFACE }};

int interface_type_from_name(char *name, enum DeviceInterfaceType *type_ptr)
{
  int rc = -1;
  int ind = -1;
  unsigned int i = 0;
  if((name == NULL) || (type_ptr == NULL))
     return 0;

  for (i = 0 ; i < NUM_INTERFACE_TYPES ; ++i)
  {
      rc = strcmp_s(name, strlen(name), interface_type_table[i].name, &ind);
      ERR_CHK(rc);
      if( (!ind) && (rc == EOK))
      {
          *type_ptr = interface_type_table[i].type;
          return 1;
      }
  }
  return 0;
}

ANSC_STATUS
CosaUtilStringToHex
    (
        char          *str,
        unsigned char *hex_str
    )
{   
    /* Coverity Issue Fix - CID:58220,59700  : UnInitialised Variable*/
    INT   i = 0, index = 0,val = 0;
    CHAR  byte[3]       = {'\0'};

    while(str[i] != '\0')
    {
        byte[0] = str[i];
        byte[1] = str[i+1];
        byte[2] = '\0';
        if(_ansc_sscanf(byte, "%x", &val) != 1)
            break;
	hex_str[index] = val;

        i += 2;
        index++;
    }
    if(index != 8)
        return ANSC_STATUS_FAILURE;

    return ANSC_STATUS_SUCCESS;
}

ULONG
CosaUtilGetIfAddr
    (
        char*       netdev
    )
{
    ANSC_IPV4_ADDRESS       ip4_addr = {};


    struct ifreq            ifr;
    int                     fd = 0;
    errno_t                 rc = -1;
    rc = strcpy_s(ifr.ifr_name,sizeof(ifr.ifr_name),netdev);
    if(rc != EOK)
    {
        ERR_CHK(rc);
        return 0;
    }
    if ((fd = socket(AF_INET, SOCK_DGRAM, 0)) >= 0)
    {
        if (!ioctl(fd, SIOCGIFADDR, &ifr))
        {
           rc = memcpy_s(&ip4_addr.Value, sizeof(ip4_addr.Value), ifr.ifr_ifru.ifru_addr.sa_data + 2,4);
           if(rc != EOK)
           {
              ERR_CHK(rc);
              close(fd);
              return 0;
           }
        }
        else
           perror("CosaUtilGetIfAddr IOCTL failure.");

        close(fd);
    }
    else
        perror("CosaUtilGetIfAddr failed to open socket.");


    return ip4_addr.Value;

}

ANSC_STATUS
CosaSListPushEntryByInsNum
    (
        PSLIST_HEADER               pListHead,
        PCOSA_CONTEXT_LINK_OBJECT   pCosaContext
    )
{
    PCOSA_CONTEXT_LINK_OBJECT       pCosaContextEntry = (PCOSA_CONTEXT_LINK_OBJECT)NULL;
    PSINGLE_LINK_ENTRY              pSLinkEntry       = (PSINGLE_LINK_ENTRY       )NULL;
    ULONG                           ulIndex           = 0;

    //CcspXdnsConsoleTrace(("RDK_LOG_DEBUG, Xdns %s : pListHead->Depth %d ENTER \n", __FUNCTION__ , pListHead->Depth));

    if ( pListHead->Depth == 0 )
    {
        AnscSListPushEntryAtBack(pListHead, &pCosaContext->Linkage);
    }
    else
    {
        pSLinkEntry = AnscSListGetFirstEntry(pListHead);

        for ( ulIndex = 0; ulIndex < pListHead->Depth; ulIndex++ )
        {
            pCosaContextEntry = ACCESS_COSA_CONTEXT_LINK_OBJECT(pSLinkEntry);
            pSLinkEntry       = AnscSListGetNextEntry(pSLinkEntry);

            if ( pCosaContext->InstanceNumber < pCosaContextEntry->InstanceNumber )
            {
                AnscSListPushEntryByIndex(pListHead, &pCosaContext->Linkage, ulIndex);
                return ANSC_STATUS_SUCCESS;
            }
        }

        AnscSListPushEntryAtBack(pListHead, &pCosaContext->Linkage);
    }

    return ANSC_STATUS_SUCCESS;
}

PCOSA_CONTEXT_LINK_OBJECT
CosaSListGetEntryByInsNum
    (
        PSLIST_HEADER               pListHead,
        ULONG                       InstanceNumber
    )
{
    PCOSA_CONTEXT_LINK_OBJECT       pCosaContextEntry = (PCOSA_CONTEXT_LINK_OBJECT)NULL;
    PSINGLE_LINK_ENTRY              pSLinkEntry       = (PSINGLE_LINK_ENTRY       )NULL;
    ULONG                           ulIndex           = 0;

    if ( pListHead->Depth == 0 )
    {
        return NULL;
    }
    else
    {
        pSLinkEntry = AnscSListGetFirstEntry(pListHead);

        for ( ulIndex = 0; ulIndex < pListHead->Depth; ulIndex++ )
        {
            pCosaContextEntry = ACCESS_COSA_CONTEXT_LINK_OBJECT(pSLinkEntry);
            pSLinkEntry       = AnscSListGetNextEntry(pSLinkEntry);

            if ( pCosaContextEntry->InstanceNumber == InstanceNumber )
            {
                return pCosaContextEntry;
            }
        }
    }

    return NULL;
}

PUCHAR
CosaUtilGetLowerLayers
    (
        PUCHAR                      pTableName,
        PUCHAR                      pKeyword
    )
{

    ULONG                           ulNumOfEntries              = 0;
    ULONG                           i                           = 0;
    ULONG                           j                           = 0;
    ULONG                           ulEntryNameLen              = 256;
    CHAR                            ucEntryParamName[256]       = {0};
    CHAR                            ucEntryNameValue[256]       = {0};
    CHAR                            ucEntryFullPath[256]        = {0};
    CHAR                            ucLowerEntryPath[256]       = {0};
    CHAR                            ucLowerEntryName[256]       = {0};
    ULONG                           ulEntryInstanceNum          = 0;
    ULONG                           ulEntryPortNum              = 0;
    char*                           pMatchedLowerLayer          = NULL;
    PANSC_TOKEN_CHAIN               pTableListTokenChain        = (PANSC_TOKEN_CHAIN)NULL;
    PANSC_STRING_TOKEN              pTableStringToken           = (PANSC_STRING_TOKEN)NULL;
    errno_t                         rc                          = -1;
    int                             ind                         = -1;
    enum DeviceInterfaceType        type;

    if ( !pTableName || AnscSizeOfString((char*)pTableName) == 0 ||
         !pKeyword   || AnscSizeOfString((char*)pKeyword) == 0
       )
    {
        return NULL;
    }

    pTableListTokenChain = AnscTcAllocate((char*)pTableName, ",");

    if ( !pTableListTokenChain )
    {
        return NULL;
    }

    while ((pTableStringToken = AnscTcUnlinkToken(pTableListTokenChain)))
    {
        if ( pTableStringToken->Name )
        {
            if(!interface_type_from_name(pTableStringToken->Name, &type))
            {
                   AnscTraceWarning(("\nUnrecognized match\n")); 
            }
            else
            {
                  if (type == ETHERNET_INTERFACE)
                  {
                       ulNumOfEntries =       CosaGetParamValueUlong("Device.Ethernet.InterfaceNumberOfEntries");

                       for ( i = 0 ; i < ulNumOfEntries; i++ )
                       {
                           ulEntryInstanceNum = CosaGetInstanceNumberByIndex("Device.Ethernet.Interface.", i);

                           if ( ulEntryInstanceNum )
                           {
                               _ansc_sprintf(ucEntryFullPath, "%s%lu", "Device.Ethernet.Interface.", ulEntryInstanceNum);

                               rc = sprintf_s(ucEntryParamName, sizeof(ucEntryParamName),"%s%s", ucEntryFullPath, ".Name");
			       if(rc < EOK) {
				    ERR_CHK(rc);
				}

                              if ( 0 == CosaGetParamValueString(ucEntryParamName, ucEntryNameValue, &ulEntryNameLen))
                              {
                                  rc = strcmp_s( ucEntryNameValue ,sizeof(ucEntryNameValue), (char*)pKeyword, &ind);
                                  ERR_CHK(rc);
                                  if((!ind) && (rc == EOK))
                                  {
                                      pMatchedLowerLayer =  AnscCloneString(ucEntryFullPath);

                                      break;
                                  }
                              }
                           }
                       }
                  }
                  else if(type == IP_INTERFACE)
                  {
                     ulNumOfEntries =       CosaGetParamValueUlong("Device.IP.InterfaceNumberOfEntries");
                     for ( i = 0 ; i < ulNumOfEntries; i++ )
                     {
                         ulEntryInstanceNum = CosaGetInstanceNumberByIndex("Device.IP.Interface.", i);

                     if ( ulEntryInstanceNum )
                     {
                        _ansc_sprintf(ucEntryFullPath, "%s%lu", "Device.IP.Interface.", ulEntryInstanceNum);

                        rc = sprintf_s(ucEntryParamName, sizeof(ucEntryParamName),"%s%s", ucEntryFullPath, ".Name");
			if(rc < EOK) {
			    ERR_CHK(rc);
			}


			if  ( 0 == CosaGetParamValueString(ucEntryParamName, ucEntryNameValue, &ulEntryNameLen)) 
		        {
                            rc = strcmp_s( ucEntryNameValue ,sizeof(ucEntryNameValue), (char*)pKeyword, &ind);
                            ERR_CHK(rc);
                            if((!ind) && (rc == EOK))
                            {

			    	pMatchedLowerLayer =  AnscCloneString(ucEntryFullPath);

                                break;
                            }
                        }
                    }
                }
            }
            else if ( type == USB_INTERFACE )
            {
            }
            else if ( type == HPNA_INTERFACE )
            {
            }
            else if ( type == DSL_INTERFACE )
            {
            }
            else if ( type == WIFI_INTERFACE )
            {
                ulNumOfEntries =       CosaGetParamValueUlong("Device.WiFi.RadioNumberOfEntries");

                for (i = 0; i < ulNumOfEntries; i++)
                {
                    ulEntryInstanceNum = CosaGetInstanceNumberByIndex("Device.WiFi.Radio.", i);
 
                    if (ulEntryInstanceNum)
                    {
                        _ansc_sprintf(ucEntryFullPath, "%s%lu", "Device.WiFi.Radio.", ulEntryInstanceNum);
 
                        rc = sprintf_s(ucEntryParamName, sizeof(ucEntryParamName),"%s%s", ucEntryFullPath, ".Name");
			if(rc < EOK) {
			    ERR_CHK(rc);
			}
 
			if ( 0 == CosaGetParamValueString(ucEntryParamName, ucEntryNameValue, &ulEntryNameLen) )
                        {
		            rc = strcmp_s( ucEntryNameValue ,sizeof(ucEntryNameValue), (char*)pKeyword, &ind);
                            ERR_CHK(rc);
                            if((!ind) && (rc == EOK))
                            {
                                pMatchedLowerLayer = AnscCloneString(ucEntryFullPath);

                                break;
                            }
			}
                    }
                }
            }
            else if ( type == HOMEPLUG_INTERFACE )
            {
            }
            else if ( type == MOCA_INTERFACE )
            {
            }
            else if (type == UPA_INTERFACE )
            {
            }
            else if ( type == ATM_LINK_INTERFACE )
            {
            }
            else if ( type == PTM_LINK_INTERFACE )
            {
            }
            else if ( type == ETHERNET_LINK_INTERFACE )
            {
                ulNumOfEntries =       CosaGetParamValueUlong("Device.Ethernet.LinkNumberOfEntries");

                for ( i = 0 ; i < ulNumOfEntries; i++ )
                {
                    ulEntryInstanceNum = CosaGetInstanceNumberByIndex("Device.Ethernet.Link.", i);

                    if ( ulEntryInstanceNum )
                    {
                        _ansc_sprintf(ucEntryFullPath, "%s%lu", "Device.Ethernet.Link.", ulEntryInstanceNum);

                        rc = sprintf_s(ucEntryParamName, sizeof(ucEntryParamName),"%s%s", ucEntryFullPath, ".Name");
			if(rc < EOK) {
			    ERR_CHK(rc);
			}
 
			if ( 0 == CosaGetParamValueString(ucEntryParamName, ucEntryNameValue, &ulEntryNameLen) )
                        {
		            rc = strcmp_s( ucEntryNameValue ,sizeof(ucEntryNameValue), (char*)pKeyword, &ind);
                            ERR_CHK(rc);
                            if((!ind) && (rc == EOK))
                            {
                            pMatchedLowerLayer =  AnscCloneString(ucEntryFullPath);

                            break;
                            }
			}
                    }
                }
            }
            else if ( type == ETHERNET_VLANT_INTERFACE )
            {
            }
            else if ( type == WIFI_SSID_INTERFACE )
            {
            }
            else if ( type == BRIDGING_INTERFACE )
            {
                ulNumOfEntries =  CosaGetParamValueUlong("Device.Bridging.BridgeNumberOfEntries");
                AnscTraceFlow(("----------CosaUtilGetLowerLayers, bridgenum:%lu\n", ulNumOfEntries));
                for ( i = 0 ; i < ulNumOfEntries; i++ )
                {
                    ulEntryInstanceNum = CosaGetInstanceNumberByIndex("Device.Bridging.Bridge.", i);
                    AnscTraceFlow(("----------CosaUtilGetLowerLayers, instance num:%lu\n", ulEntryInstanceNum));

                    if ( ulEntryInstanceNum )
                    {
                        snprintf(ucEntryFullPath,sizeof(ucEntryFullPath), "%s%lu", "Device.Bridging.Bridge.", ulEntryInstanceNum);
                        rc = sprintf_s(ucLowerEntryPath, sizeof(ucLowerEntryPath),"%s%s", ucEntryFullPath, ".PortNumberOfEntries");
			if(rc < EOK) {
			     ERR_CHK(rc);
			}
 
                        ulEntryPortNum = CosaGetParamValueUlong(ucLowerEntryPath);
                        AnscTraceFlow(("----------CosaUtilGetLowerLayers, Param:%s,port num:%lu\n",ucLowerEntryPath, ulEntryPortNum));

                        for ( j = 1; j<= ulEntryPortNum; j++) {
                            rc = sprintf_s(ucLowerEntryName, sizeof(ucEntryFullPath),"%s%s%lu", ucEntryFullPath, ".Port.", j);
			    if(rc < EOK) {
				ERR_CHK(rc);
			    }
                            rc = sprintf_s(ucEntryParamName, sizeof(ucEntryFullPath),"%s%s%lu%s", ucEntryFullPath, ".Port.", j, ".Name");
			    if(rc < EOK)
			    {
				ERR_CHK(rc);
			    }
                            AnscTraceFlow(("----------CosaUtilGetLowerLayers, Param:%s,Param2:%s\n", ucLowerEntryName, ucEntryParamName));
 
			    if ( 0 == CosaGetParamValueString(ucEntryParamName, ucEntryNameValue, &ulEntryNameLen) )
                            {
				rc = strcmp_s( ucEntryNameValue ,sizeof(ucEntryNameValue), (char*)pKeyword, &ind);
                                ERR_CHK(rc);
                                if((!ind) && (rc == EOK))
                                {
                                    pMatchedLowerLayer =  AnscCloneString(ucLowerEntryName);
                                    AnscTraceFlow(("----------CosaUtilGetLowerLayers, J:%lu, LowerLayer:%s\n", j, pMatchedLowerLayer));
                                    break;
				}
                            }
                        }
                    }
                }
            }
            else if ( type == PPP_INTERFACE )
            {
            }
            else if (  type == DSL_CHANNEL_INTERFACE)
            {
            }
         } 
            if ( pMatchedLowerLayer )
            {
                AnscFreeMemory(pTableStringToken);
                break;
            }
        }

        AnscFreeMemory(pTableStringToken);
   } 
    if ( pTableListTokenChain )
    {
        AnscTcFree((ANSC_HANDLE)pTableListTokenChain);
    }

    AnscTraceWarning
        ((
            "CosaUtilGetLowerLayers: %s matched LowerLayer(%s) with keyword %s in the table %s\n",
            pMatchedLowerLayer ? "Found a":"Not find any",
            pMatchedLowerLayer ? pMatchedLowerLayer : "",
            pKeyword,
            pTableName
        ));

    return (PUCHAR)pMatchedLowerLayer;
}

/*
    CosaUtilGetFullPathNameByKeyword

   Description:
        This funcation serves for searching other pathname  except lowerlayer.

    PUCHAR                      pTableName
        This is the Table names divided by ",". For example
        "Device.Ethernet.Interface., Device.Dhcpv4." 
        
    PUCHAR                      pParameterName
        This is the parameter name which hold the keyword. eg: "name"
        
    PUCHAR                      pKeyword
        This is keyword. eg: "wan0".

    return value
        return result string which need be free by the caller.
*/
PUCHAR
CosaUtilGetFullPathNameByKeyword
    (
        PUCHAR                      pTableName,
        PUCHAR                      pParameterName,
        PUCHAR                      pKeyword
    )
{

    ULONG                           ulNumOfEntries              = 0;
    ULONG                           i                           = 0;
    ULONG                           ulEntryNameLen              = 256;
    CHAR                            ucEntryParamName[256]       = {0};
    CHAR                            ucEntryNameValue[256]       = {0};
    CHAR                            ucTmp[128]                  = {0};
    CHAR                            ucTmp2[128]                 = {0};
    CHAR                            ucEntryFullPath[256]        = {0};
    char*                           pMatchedLowerLayer          = NULL;
    ULONG                           ulEntryInstanceNum          = 0;
    PANSC_TOKEN_CHAIN               pTableListTokenChain        = (PANSC_TOKEN_CHAIN)NULL;
    PANSC_STRING_TOKEN              pTableStringToken           = (PANSC_STRING_TOKEN)NULL;
    char*                           pString                     = NULL;
    char*                           pString2                    = NULL;
    errno_t                         rc                          = -1;
    int                             ind                         =  -1;

    if ( !pTableName || AnscSizeOfString((char*)pTableName) == 0 ||
         !pKeyword   || AnscSizeOfString((char*)pKeyword) == 0   ||
         !pParameterName   || AnscSizeOfString((char*)pParameterName) == 0
       )
    {
        return NULL;
    }

    pTableListTokenChain = AnscTcAllocate((char*)pTableName, ",");

    if ( !pTableListTokenChain )
    {
        return NULL;
    }

    while ((pTableStringToken = AnscTcUnlinkToken(pTableListTokenChain)))
    {
        if ( pTableStringToken->Name )
        {
            /* Get the string XXXNumberOfEntries */
            pString2 = &pTableStringToken->Name[0];
            pString  = pString2;
            for (i = 0;pTableStringToken->Name[i]; i++)
            {
                if ( pTableStringToken->Name[i] == '.' )
                {
                    pString2 = pString;
                    pString  = &pTableStringToken->Name[i+1];
                }
            }

            pString--;
            pString[0] = '\0';
            rc = sprintf_s(ucTmp2, sizeof(ucTmp2),"%s%s", pString2, "NumberOfEntries");
	    if(rc < EOK) {
		ERR_CHK(rc);
	    }
            pString[0] = '.';

            /* Enumerate the entry in this table */
            if ( TRUE )
            {
                pString2--;
                pString2[0]='\0';
                rc = sprintf_s(ucTmp, sizeof(ucTmp),"%s.%s", pTableStringToken->Name, ucTmp2);
		if(rc < EOK) {
		    ERR_CHK(rc);
		}
                pString2[0]='.';
                ulNumOfEntries =       CosaGetParamValueUlong(ucTmp);

                for ( i = 0 ; i < ulNumOfEntries; i++ )
                {
                    ulEntryInstanceNum = CosaGetInstanceNumberByIndex(pTableStringToken->Name, i);

                    if ( ulEntryInstanceNum )
                    {
                        rc = sprintf_s(ucEntryFullPath, sizeof(ucEntryFullPath),"%s%lu%s", pTableStringToken->Name, ulEntryInstanceNum, ".");
			if(rc < EOK) {
			    ERR_CHK(rc);
			}

                        snprintf(ucEntryParamName,sizeof(ucEntryParamName), "%s%s", ucEntryFullPath, pParameterName);

			if ( 0 == CosaGetParamValueString(ucEntryParamName, ucEntryNameValue, &ulEntryNameLen))
                        {
                        rc = strcmp_s( ucEntryNameValue ,sizeof(ucEntryNameValue), (char*)pKeyword, &ind);
                        ERR_CHK(rc);
                        if((!ind) && (rc == EOK))
                        {
                            pMatchedLowerLayer =  AnscCloneString(ucEntryFullPath);

                            break;
                        }
                        }
                    }
                }
             }

            if ( pMatchedLowerLayer )
            {
                AnscFreeMemory(pTableStringToken);
                break;
            }
        }

        AnscFreeMemory(pTableStringToken);
    }

    if ( pTableListTokenChain )
    {
        AnscTcFree((ANSC_HANDLE)pTableListTokenChain);
    }

    AnscTraceWarning
        ((
            "CosaUtilGetFullPathNameByKeyword: %s matched parameters(%s) with keyword %s in the table %s(%s)\n",
            pMatchedLowerLayer ? "Found a":"Not find any",
            pMatchedLowerLayer ? pMatchedLowerLayer : "",
            pKeyword,
            pTableName,
            pParameterName
        ));

    return (PUCHAR)pMatchedLowerLayer;
}

ANSC_STATUS
CosaUtilGetStaticRouteTable
    (
        UINT                        *count,
        StaticRoute                 **out_sroute
    )
{
	return CosaUtilGetStaticRouteTablePriv(count, out_sroute);
}

