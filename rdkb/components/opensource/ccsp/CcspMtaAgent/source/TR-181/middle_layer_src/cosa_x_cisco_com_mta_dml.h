/*
 * If not stated otherwise in this file or this component's LICENSE file the
 * following copyright and licenses apply:
 *
 * Copyright 2015 RDK Management
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

// #ifdef CONFIG_TI_PACM
/**************************************************************************

    module: cosa_X_CISCO_COM_mta_dml.h

        For COSA Data Model Library Development

    -------------------------------------------------------------------

    description:

        This file defines the apis for objects to support Data Model Library.

    -------------------------------------------------------------------


    author:

        COSA XML TOOL CODE GENERATOR 1.0

    -------------------------------------------------------------------

    revision:

        01/05/2012    initial revision.

**************************************************************************/


#ifndef  _COSA_MTA_DML_H
#define  _COSA_MTA_DML_H

/***********************************************************************

 APIs for Object:

    X_CISCO_COM_MTA.

    *  X_CISCO_COM_MTA_GetParamBoolValue
    *  X_CISCO_COM_MTA_GetParamIntValue
    *  X_CISCO_COM_MTA_GetParamUlongValue
    *  X_CISCO_COM_MTA_GetParamStringValue
    *  X_CISCO_COM_MTA_SetParamBoolValue
    *  X_CISCO_COM_MTA_SetParamIntValue
    *  X_CISCO_COM_MTA_SetParamUlongValue
    *  X_CISCO_COM_MTA_SetParamStringValue
    *  X_CISCO_COM_MTA_Validate
    *  X_CISCO_COM_MTA_Commit
    *  X_CISCO_COM_MTA_Rollback

***********************************************************************/
BOOL
X_CISCO_COM_MTA_GetParamBoolValue
    (
        ANSC_HANDLE                 hInsContext,
        char*                       ParamName,
        BOOL*                       pBool
    );

BOOL
X_CISCO_COM_MTA_GetParamIntValue
    (
        ANSC_HANDLE                 hInsContext,
        char*                       ParamName,
        int*                        pInt
    );

BOOL
X_CISCO_COM_MTA_GetParamUlongValue
    (
        ANSC_HANDLE                 hInsContext,
        char*                       ParamName,
        ULONG*                      pUlong
    );

ULONG
X_CISCO_COM_MTA_GetParamStringValue
    (
        ANSC_HANDLE                 hInsContext,
        char*                       ParamName,
        char*                       pValue,
        ULONG*                      pUlSize
    );

BOOL
X_CISCO_COM_MTA_SetParamBoolValue
    (
        ANSC_HANDLE                 hInsContext,
        char*                       ParamName,
        BOOL                        bValue
    );

BOOL
X_CISCO_COM_MTA_SetParamIntValue
    (
        ANSC_HANDLE                 hInsContext,
        char*                       ParamName,
        int                         value
    );

BOOL
X_CISCO_COM_MTA_SetParamUlongValue
    (
        ANSC_HANDLE                 hInsContext,
        char*                       ParamName,
        ULONG                       uValuepUlong
    );

BOOL
X_CISCO_COM_MTA_SetParamStringValue
    (
        ANSC_HANDLE                 hInsContext,
        char*                       ParamName,
        char*                       strValue
    );

BOOL
X_CISCO_COM_MTA_Validate
    (
        ANSC_HANDLE                 hInsContext,
        char*                       pReturnParamName,
        ULONG*                      puLength
    );

ULONG
X_CISCO_COM_MTA_Commit
    (
        ANSC_HANDLE                 hInsContext
    );

ULONG
X_CISCO_COM_MTA_Rollback
    (
        ANSC_HANDLE                 hInsContext
    );

/***********************************************************************

 APIs for Object:

    X_CISCO_COM_MTA_V6.

    *  X_CISCO_COM_MTA_V6_GetParamUlongValue
    *  X_CISCO_COM_MTA_V6_GetParamStringValue
    *  X_CISCO_COM_MTA_V6_Validate
    *  X_CISCO_COM_MTA_V6_Commit
    *  X_CISCO_COM_MTA_V6_Rollback

***********************************************************************/

BOOL
X_CISCO_COM_MTA_V6_GetParamUlongValue
    (
        ANSC_HANDLE                 hInsContext,
        char*                       ParamName,
        ULONG*                      pUlong
    );

ULONG
X_CISCO_COM_MTA_V6_GetParamStringValue
    (
        ANSC_HANDLE                 hInsContext,
        char*                       ParamName,
        char*                       pValue,
        ULONG*                      pUlSize
    );

BOOL
X_CISCO_COM_MTA_V6_Validate
    (
        ANSC_HANDLE                 hInsContext,
        char*                       pReturnParamName,
        ULONG*                      puLength
    );

ULONG
X_CISCO_COM_MTA_V6_Commit
    (
        ANSC_HANDLE                 hInsContext
    );

ULONG
X_CISCO_COM_MTA_V6_Rollback
    (
        ANSC_HANDLE                 hInsContext
    );

/***********************************************************************

 APIs for Object:

    X_CISCO_COM_MLD.Group.{i}.

    *  MTALog_GetEntryCount
    *  MTALog_GetEntry
    *  MTALog_IsUpdated
    *  MTALog_Synchronize
    *  MTALog_GetParamUlongValue
    *  MTALog_GetParamStringValue

***********************************************************************/
ULONG
MTALog_GetEntryCount
    (
        ANSC_HANDLE                 hInsContext
    );

ANSC_HANDLE
MTALog_GetEntry
    (
        ANSC_HANDLE                 hInsContext,
        ULONG                       nIndex,
        ULONG*                      pInsNumber
    );

BOOL
MTALog_IsUpdated
    (
        ANSC_HANDLE                 hInsContext
    );

ULONG
MTALog_Synchronize
    (
        ANSC_HANDLE                 hInsContext
    );

BOOL
MTALog_GetParamUlongValue
    (
        ANSC_HANDLE                 hInsContext,
        char*                       ParamName,
        ULONG*                      puLong
    );

ULONG
MTALog_GetParamStringValue
    (
        ANSC_HANDLE                 hInsContext,
        char*                       ParamName,
        char*                       pValue,
        ULONG*                      pUlSize
    );

/***********************************************************************

 APIs for Object:

    X_CISCO_COM_MLD.Group.{i}.

    *  DECTLog_GetEntryCount
    *  DECTLog_GetEntry
    *  DECTLog_IsUpdated
    *  DECTLog_Synchronize
    *  DECTLog_GetParamUlongValue
    *  DECTLog_GetParamStringValue

***********************************************************************/
ULONG
DECTLog_GetEntryCount
    (
        ANSC_HANDLE                 hInsContext
    );

ANSC_HANDLE
DECTLog_GetEntry
    (
        ANSC_HANDLE                 hInsContext,
        ULONG                       nIndex,
        ULONG*                      pInsNumber
    );

BOOL
DECTLog_IsUpdated
    (
        ANSC_HANDLE                 hInsContext
    );

ULONG
DECTLog_Synchronize
    (
        ANSC_HANDLE                 hInsContext
    );

BOOL
DECTLog_GetParamUlongValue
    (
        ANSC_HANDLE                 hInsContext,
        char*                       ParamName,
        ULONG*                      puLong
    );

ULONG
DECTLog_GetParamStringValue
    (
        ANSC_HANDLE                 hInsContext,
        char*                       ParamName,
        char*                       pValue,
        ULONG*                      pUlSize
    );

#ifdef CONFIG_TI_BBU

/***********************************************************************

 APIs for Object:

    Battery.

    *  Battery_GetParamBoolValue
    *  Battery_GetParamIntValue
    *  Battery_GetParamUlongValue
    *  Battery_GetParamStringValue

***********************************************************************/
BOOL
Battery_GetParamBoolValue
    (
        ANSC_HANDLE                 hInsContext,
        char*                       ParamName,
        BOOL*                       pBool
    );

BOOL
Battery_GetParamIntValue
    (
        ANSC_HANDLE                 hInsContext,
        char*                       ParamName,
        int*                        pInt
    );

BOOL
Battery_GetParamUlongValue
    (
        ANSC_HANDLE                 hInsContext,
        char*                       ParamName,
        ULONG*                      puLong
    );

ULONG
Battery_GetParamStringValue
    (
        ANSC_HANDLE                 hInsContext,
        char*                       ParamName,
        char*                       pValue,
        ULONG*                      pUlSize
    );
#endif /* CONFIG_TI_BBU */

BOOL
X_RDKCENTRAL_COM_MTA_GetParamUlongValue
    (
        ANSC_HANDLE                 hInsContext,
        char*                       ParamName,
        ULONG*                      puLong
    );

ULONG
X_RDKCENTRAL_COM_MTA_GetParamStringValue
    (
        ANSC_HANDLE                 hInsContext,
        char*                       ParamName,
        char*                       pValue,
        ULONG*                      pUlSize
    );

BOOL
X_RDKCENTRAL_COM_MTA_GetParamBoolValue

    (
        ANSC_HANDLE                 hInsContext,
        char*                       ParamName,
        BOOL*                       pBool
    );

BOOL
X_RDKCENTRAL_COM_MTA_SetParamBoolValue

    (
        ANSC_HANDLE                 hInsContext,
        char*                       ParamName,
        BOOL                       bValue
    );
int CosaDmlTR104DataSet(char* pString,int bootup);
#endif /* _COSA_MTA_DML_H */

// #endif /* CONFIG_TI_PACM */
