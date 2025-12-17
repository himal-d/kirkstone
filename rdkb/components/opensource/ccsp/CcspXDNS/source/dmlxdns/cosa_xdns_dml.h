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

#ifndef  _COSA_XDNS_DML_H
#define  _COSA_XDNS_DML_H
#define MAX_XDNS_SERV 2

/***********************************************************************

 APIs for Object:

    SelfHeal.


***********************************************************************/
/***********************************************************************

 APIs for Object:

    SelfHeal.XDNS.

    *  XDNS_GetParamStringValue
    *  XDNS_SetParamStringValue
    *  XDNS_GetParamBoolValue
    *  XDNS_SetParamBoolValue
    *  XDNS_Validate
    *  XDNS_Commit
    *  XDNS_Rollback

***********************************************************************/

ULONG
XDNS_GetParamStringValue
    (
        ANSC_HANDLE                 hInsContext,
        char*                       ParamName,
        char*                       pValue,
        ULONG*                      pUlSize
    );

BOOL
XDNS_SetParamStringValue
    (
        ANSC_HANDLE                 hInsContext,
        char*                       ParamName,
        char*                       strValue
    );

BOOL
XDNS_GetParamBoolValue
    (
        ANSC_HANDLE                 hInsContext,
        char*                       ParamName,
        BOOL*                       pBool
    );

BOOL
XDNS_SetParamBoolValue
    (
        ANSC_HANDLE                 hInsContext,
        char*                       ParamName,
        BOOL                        bValue
    );


BOOL
XDNS_Validate
    (
        ANSC_HANDLE                 hInsContext,
        char*                       pReturnParamName,
        ULONG*                      puLength
    );

ULONG
XDNS_Commit
    (
        ANSC_HANDLE                 hInsContext
    );

ULONG
XDNS_Rollback
    (
        ANSC_HANDLE                 hInsContext
    );

/***********************************************************************

 APIs for Object:

    Device.DeviceInfo.

    *  XDNSDeviceInfo_GetParamBoolValue
    *  XDNSDeviceInfo_SetParamBoolValue

***********************************************************************/

BOOL
XDNSDeviceInfo_GetParamBoolValue
    (
        ANSC_HANDLE                 hInsContext,
        char*                       ParamName,
        BOOL*                       pBool
    );
BOOL
XDNSDeviceInfo_SetParamBoolValue
    (
        ANSC_HANDLE                 hInsContext,
        char*                       ParamName,
        BOOL                        bValue
    );

/***********************************************************************

 APIs for Object:

    DeviceInfo.X_RDKCENTRAL-COM_RFC.Feature.AvoidUnNecesaryXDNSretries.

    *  XDNSRefac_GetParamBoolValue
    *  XDNSRefac_SetParamBoolValue

***********************************************************************/

BOOL
XDNSRefac_GetParamBoolValue
    (
        ANSC_HANDLE                 hInsContext,
        char*                       ParamName,
        BOOL*                       pBool
    );
BOOL
XDNSRefac_SetParamBoolValue
    (
        ANSC_HANDLE                 hInsContext,
        char*                       ParamName,
        BOOL                        bValue
    );


/***********************************************************************

 APIs for Object:

    X_RDKCENTRAL-COM_XDNS.DNSMappingTable.{i}.

    *  DNSMappingTable_GetEntryCount
    *  DNSMappingTable_GetEntry
    *  DNSMappingTable_IsUpdated
    *  DNSMappingTable_Synchronize
    *  DNSMappingTable_AddEntry
    *  DNSMappingTable_DelEntry
    *  DNSMappingTable_GetParamStringValue
    *  DNSMappingTable_SetParamStringValue
    *  DNSMappingTable_Validate
    *  DNSMappingTable_Commit
    *  DNSMappingTable_Rollback

***********************************************************************/

ULONG
DNSMappingTable_GetEntryCount
    (
        ANSC_HANDLE
    );

ANSC_HANDLE
DNSMappingTable_GetEntry
    (
        ANSC_HANDLE                 hInsContext,
        ULONG                       nIndex,
        ULONG*                      pInsNumber
    );

BOOL
DNSMappingTable_IsUpdated
    (
        ANSC_HANDLE                 hInsContext
    );

ULONG
DNSMappingTable_Synchronize
    (
        ANSC_HANDLE                 hInsContext
    );

ANSC_HANDLE
DNSMappingTable_AddEntry
    (
        ANSC_HANDLE                 hInsContext,
        ULONG*                      pInsNumber
    );

ULONG
DNSMappingTable_DelEntry
    (
        ANSC_HANDLE                 hInsContext,
        ANSC_HANDLE                 hInstance
    );

ULONG
DNSMappingTable_GetParamStringValue
    (
        ANSC_HANDLE                 hInsContext,
        char*                       ParamName,
        char*                       pValue,
        ULONG*                      pUlSize
    );

BOOL
DNSMappingTable_SetParamStringValue
    (
        ANSC_HANDLE                 hInsContext,
        char*                       ParamName,
        char*                       strValue
    );

BOOL
DNSMappingTable_Validate
    (
        ANSC_HANDLE                 hInsContext,
        char*                       pReturnParamName,
        ULONG*                      puLength
    );

ULONG
DNSMappingTable_Commit
    (
        ANSC_HANDLE                 hInsContext
    );

ULONG
DNSMappingTable_Rollback
    (
        ANSC_HANDLE                 hInsContext
    );




#endif
