/*
 * If not stated otherwise in this file or this component's LICENSE file the
 * following copyright and licenses apply:
 *
 * Copyright 2020 Sky
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "ansc_platform.h"
#include "telcovoicemgr_dml_backendmgr.h"
#include "telcovoicemgr_dml_profile_v1.h"
#include "telcovoicemgr_services_apis_v1.h"
#include "telcovoicemgr_dml_hal.h"
#include "telcovoicemgr_dml_json_cfg_init.h"
#include "ccsp_trace.h"
#include "ccsp_syslog.h"

/***********************************************************************/
/***********************************************************************

 APIs for Object:

    Services.VoiceService.{i}.VoiceProfile.{i}
   
    *  VoiceProfile_IsUpdated
    *  VoiceProfile_Synchronize
    *  VoiceProfile_GetParamStringValue
    *  VoiceProfile_SetParamStringValue
    *  VoiceProfile_GetParamUlongValue
    *  VoiceProfile_SetParamUlongValue
    *  VoiceProfile_GetEntryCount
    *  VoiceProfile_GetEntry
    *  VoiceProfile_Validate
    *  VoiceProfile_Commit
    *  VoiceProfile_Rollback

    Services.VoiceService.{i}.VoiceProfile.{i}.SIP.

    *  SIP_IsUpdated
    *  SIP_Synchronize
    *  SIP_GetParamStringValue
    *  SIP_SetParamStringValue
    *  SIP_GetParamUlongValue
    *  SIP_SetParamUlongValue
    *  SIP_GetParamBoolValue
    *  SIP_SetParamBoolValue

***********************************************************************/
/**********************************************************************

    caller:     owner of this object

    prototype:

                ULONG VoiceProfile_IsUpdated(ANSC_HANDLE hInsContext);

    description:

               This function is called to check if VoiceProfile updated .

    argument:   ANSC_HANDLE      hInsContext, 
               The instance handle;

    return:     The status of the operation.

**********************************************************************/
    
BOOL VoiceProfile_IsUpdated(ANSC_HANDLE hInsContext)
{
    BOOL        bIsUpdated = TRUE;
    return bIsUpdated;
}

/**********************************************************************

    caller:     owner of this object

    prototype:

                ULONG VoiceProfile_Synchronize(ANSC_HANDLE hInsContext);

    description:

               This function is called to synchronize VoiceProfile data.

    argument:   ANSC_HANDLE      hInsContext, 
               The instance handle;

    return:     The status of the operation.

**********************************************************************/
ULONG VoiceProfile_Synchronize(ANSC_HANDLE hInsContext)
{
    ANSC_STATUS            returnStatus   = ANSC_STATUS_SUCCESS;
    return returnStatus;
}

/******************************************** **************************

    caller:     owner of this object

    prototype:

        BOOL VoiceProfile_GetParamStringValue(ANSC_HANDLE hInsContext, char* ParamName, char* pValue, ULONG* pUlSize);

    description:

        This function is called to retrieve String parameter value;

    argument:   ANSC_HANDLE                 hInsContext,
                The instance handle;

                char*                       ParamName,
                The parameter name;

                char*                       pValue,
                The buffer of returned ULONG value;

                ULONG*                      pUlSize
                The length of returned buffer value;

    return:     0 if succeeded.
                1 if not enough buffer size
                -1 if not supported

**********************************************************************/
LONG VoiceProfile_GetParamStringValue(ANSC_HANDLE hInsContext, char* ParamName, char* pValue, ULONG* pUlSize)
{

    DML_PROFILE_CTRL_T* pTelcoVoiceMgrCtrl = (DML_PROFILE_CTRL_T*) hInsContext;
    ULONG ret = 1;

    if(pTelcoVoiceMgrCtrl != NULL)
    {
        TELCOVOICEMGR_DML_DATA* pTelcoVoiceMgrDmlData = TelcoVoiceMgrDmlGetDataLocked();
        if(pTelcoVoiceMgrDmlData != NULL)
        {
          TELCOVOICEMGR_DML_VOICEPROFILE* pVoiceProfile = &(pTelcoVoiceMgrCtrl->dml);

          if (pVoiceProfile && pValue && pUlSize)
          {
            if (strcmp(ParamName, "X_RDK-Central_COM_DigitMap") == 0)
            { 
                if(strlen(pVoiceProfile->X_RDK_DigitMap) < *pUlSize)
                {
                  AnscCopyString(pValue, pVoiceProfile->X_RDK_DigitMap);
                  ret = 0;
                }
                else
                {
	           CcspTraceWarning(("%s: Buffer length insufficient, ParamName:%s\n", __FUNCTION__, ParamName));
                   //X_RDK-Central_COM_DigitMap supports maximum 2048 characters
                   // But by default,  the DML library will allocate 1023 buffer size only
                   // If we need more size just put the new size and return 1
                   // If return value is 1 ,the library will allocate required buffer space for us if new size is specified  
                   *pUlSize = MAXLENGTH_DIGITMAP;                
                   ret = 1;
                }
            }
            else if (strcmp(ParamName, "X_RDK-Central_COM_EmergencyDigitMap") == 0)
            {
                if(strlen(pVoiceProfile->EmergencyDigitMap) < *pUlSize)
                {
                  AnscCopyString(pValue, pVoiceProfile->EmergencyDigitMap);
                  ret = 0;
                }
                else
                {
                   CcspTraceWarning(("%s: Buffer length insufficient, ParamName:%s\n", __FUNCTION__, ParamName));
                   //X_RDK-Central_COM_EmergencyDigitMap suppors maximum 2048 characters
                   // But by default, the DML library will allocate 1023 buffer size only
                   // If we need more size just put the new size and return 1
                   // If return value is 1 ,the library will allocate required buffer space for us if new size is specified  
                   *pUlSize = MAXLENGTH_DIGITMAP;                
                   ret = 1;
                }
            }
            else if (strcmp(ParamName, "Alias") == 0)
            {
                AnscCopyString(pValue, pVoiceProfile->Alias);
                ret = 0;
            }
            else if (strcmp(ParamName, "Name") == 0)
            {
                AnscCopyString(pValue, pVoiceProfile->Name);
                ret = 0;
            }
            else if (strcmp(ParamName, "SignalingProtocol") == 0)
            {
                AnscCopyString(pValue, pVoiceProfile->SignalingProtocol);
                ret = 0;
            }
            else if (strcmp(ParamName, "Region") == 0)
            {
                AnscCopyString(pValue, pVoiceProfile->Region);
                ret = 0;
            }
            else if (strcmp(ParamName, "DigitMap") == 0)
            {
                AnscCopyString(pValue, pVoiceProfile->DigitMap);
                ret = 0;
            }
            else if (strcmp(ParamName, "STUNServer") == 0)
            {
                AnscCopyString(pValue, pVoiceProfile->STUNServer);
                ret = 0;
            }
            else
            {
                CcspTraceError(("%s: Invalid ParamName:%s \n", __FUNCTION__, ParamName));
            }
          }
          TelcoVoiceMgrDmlGetDataRelease(pTelcoVoiceMgrDmlData);
        }   
    }

    CcspTraceWarning(("%s: ParamName:%s Value : %s\n", __FUNCTION__, ParamName, pValue));
    return ret;
}

/**********************************************************************

    caller:     owner of this object

    prototype:

        BOOL VoiceProfile_SetParamStringValue(ANSC_HANDLE hInsContext, char* ParamName, char* pString);

    description:

        This function is called to Set String parameter value;

    argument:   ANSC_HANDLE                 hInsContext,
                The instance handle;

                char*                       ParamName,
                The parameter name;

                char*                       pValue,
                The buffer to set value;

    return:     TRUE if succeeded.

**********************************************************************/

BOOL VoiceProfile_SetParamStringValue(ANSC_HANDLE hInsContext, char* ParamName, char* pString)
{
    DML_PROFILE_CTRL_T* pTelcoVoiceMgrCtrl = (DML_PROFILE_CTRL_T*) hInsContext;
    PTELCOVOICEMGR_DML_VOICESERVICE pDmlVoiceService = NULL;
    BOOL ret = FALSE;
    ULONG uVsIndex = 0;
    ULONG uVpIndex = 0;

    if(pTelcoVoiceMgrCtrl != NULL)
    {
        TELCOVOICEMGR_DML_DATA* pTelcoVoiceMgrDmlData = TelcoVoiceMgrDmlGetDataLocked();
        if(pTelcoVoiceMgrDmlData != NULL)
        {
            TELCOVOICEMGR_DML_VOICEPROFILE* pVoiceProfile = &(pTelcoVoiceMgrCtrl->dml);

            if (!pVoiceProfile || !pString)
            {
                CcspTraceError(("%s: NULL Pointer\n", __FUNCTION__));
                TelcoVoiceMgrDmlGetDataRelease(pTelcoVoiceMgrDmlData);
                return FALSE;
            }
            else
            {
                pDmlVoiceService = pVoiceProfile->pParentVoiceService;
                uVsIndex = pDmlVoiceService->InstanceNumber;
                uVpIndex = pVoiceProfile->InstanceNumber;
                TelcoVoiceMgrDmlGetDataRelease(pTelcoVoiceMgrDmlData);
                if (strcmp(ParamName, "X_RDK-Central_COM_DigitMap") == 0)
                {
                    if(TelcoVoiceMgrDmlSetDigitMap(uVsIndex, uVpIndex, pString, "X_RDK-Central_COM_DigitMap") == ANSC_STATUS_SUCCESS)
                    {
                        TELCOVOICEMGR_DML_DATA* pTelcoVoiceMgrDmlData = TelcoVoiceMgrDmlGetDataLocked();
                        if(pTelcoVoiceMgrDmlData != NULL)
                        {
                            snprintf(pVoiceProfile->X_RDK_DigitMap, sizeof(pVoiceProfile->X_RDK_DigitMap),"%s", pString);
                            TelcoVoiceMgrDmlGetDataRelease(pTelcoVoiceMgrDmlData);
                            return TRUE;
                        }
                    }
                }
                else if (strcmp(ParamName, "X_RDK-Central_COM_EmergencyDigitMap") == 0)
                {
                    if(TelcoVoiceMgrDmlSetDigitMap(uVsIndex, uVpIndex, pString, "X_RDK-Central_COM_EmergencyDigitMap") == ANSC_STATUS_SUCCESS)
                    {
                        TELCOVOICEMGR_DML_DATA* pTelcoVoiceMgrDmlData = TelcoVoiceMgrDmlGetDataLocked();
                        if(pTelcoVoiceMgrDmlData != NULL)
                        {
                            snprintf(pVoiceProfile->EmergencyDigitMap, sizeof(pVoiceProfile->EmergencyDigitMap),"%s", pString);
                            TelcoVoiceMgrDmlGetDataRelease(pTelcoVoiceMgrDmlData);
                            return TRUE;
                        }
                    }
                }
                else if (strcmp(ParamName, "DigitMap") == 0)
                {
                    if(TelcoVoiceMgrDmlSetDigitMap(uVsIndex, uVpIndex, pString, "DigitMap") == ANSC_STATUS_SUCCESS)
                    {
                        TELCOVOICEMGR_DML_DATA* pTelcoVoiceMgrDmlData = TelcoVoiceMgrDmlGetDataLocked();
                        if(pTelcoVoiceMgrDmlData != NULL)
                        {
                            AnscCopyString(pVoiceProfile->DigitMap, pString);
                            TelcoVoiceMgrDmlGetDataRelease(pTelcoVoiceMgrDmlData);
                            return TRUE;
                        }
                    }
                }
                else
                {
                    CcspTraceWarning(("%s::Unknown ParamName :%s\n", __FUNCTION__, ParamName));
                }
            }
        }
    }
    else
    {
       CcspTraceWarning(("%s::Invalid Object :%s\n", __FUNCTION__, ParamName));
    }
    return ret;
}

/**********************************************************************

    caller:     owner of this object

    prototype:

        BOOL VoiceProfile_GetParamUlongValue(ANSC_HANDLE hInsContext, char* ParamName, char* pString);

    description:

        This function is called to retrieve Ulong parameter value;

    argument:   ANSC_HANDLE                 hInsContext,
                The instance handle;

                char*                       ParamName,
                The parameter name;

                char*                       puLong,
                The ULong value to return;

    return:     TRUE if succeeded.

**********************************************************************/

BOOL VoiceProfile_GetParamUlongValue(ANSC_HANDLE hInsContext, char*  ParamName, ULONG* puValue)
{

    DML_PROFILE_CTRL_T* pTelcoVoiceMgrCtrl = (DML_PROFILE_CTRL_T*) hInsContext;
    BOOL ret = FALSE;
    if(pTelcoVoiceMgrCtrl != NULL)
    {
        TELCOVOICEMGR_DML_DATA* pTelcoVoiceMgrDmlData = TelcoVoiceMgrDmlGetDataLocked();
        if(pTelcoVoiceMgrDmlData != NULL)
        {
            TELCOVOICEMGR_DML_VOICEPROFILE* pVoiceProfile = &(pTelcoVoiceMgrCtrl->dml);
            if (!pVoiceProfile || !puValue)
            {
                CcspTraceError(("%s: NULL Pointer\n", __FUNCTION__));
                TelcoVoiceMgrDmlGetDataRelease(pTelcoVoiceMgrDmlData);
                return ret;
            }
            if (strcmp(ParamName, "X_RDK-Central_COM_SDigitTimer") == 0)
            {
                * puValue = pVoiceProfile->SDigitTimer;
                ret = TRUE;
            }
            else if (strcmp(ParamName, "X_RDK-Central_COM_ZDigitTimer") == 0)
            {
                * puValue = pVoiceProfile->ZDigitTimer;
                ret = TRUE;
            }
            else if (strcmp(ParamName, "Enable") == 0)
            {
                *puValue = pVoiceProfile->Enable;
                ret = TRUE;
            }
            else if (strcmp(ParamName, "DTMFMethod") == 0)
            {
                *puValue = pVoiceProfile->DTMFMethod;
                ret = 0;
            }
            else if (strcmp(ParamName, "DTMFMethodG711") == 0)
            {
                *puValue = pVoiceProfile->DTMFMethodG711;
                ret = 0;
            }
            else if (strcmp(ParamName, "NumberOfLines") == 0)
            {
                *puValue = pVoiceProfile->NumberOfLines;
                ret = TRUE;
            }
            else if (strcmp(ParamName, "MaxSessions") == 0)
            {
                *puValue = pVoiceProfile->MaxSessions;
                ret = TRUE;
            }
            else if (strcmp(ParamName, "NonVoiceBandwidthReservedUpstream") == 0)
            {
                *puValue = pVoiceProfile->NonVoiceBandwidthReservedUpstream;
                ret = TRUE;
            }
            else if (strcmp(ParamName, "NonVoiceBandwidthReservedDownstream") == 0)
            {
                *puValue = pVoiceProfile->NonVoiceBandwidthReservedDownstream;
                ret = TRUE;
            }
            else if (strcmp(ParamName, "FaxPassThrough") == 0)
            {
                *puValue = pVoiceProfile->FaxPassThrough;
                ret = TRUE;
            }
            else if (strcmp(ParamName, "ModemPassThrough") == 0)
            {
                *puValue = pVoiceProfile->ModemPassThrough;
                ret = TRUE;
            }
            else
            {
                CcspTraceWarning(("%s::Unknown ParamName :%s\n", __FUNCTION__, ParamName));
            }
        }
        TelcoVoiceMgrDmlGetDataRelease(pTelcoVoiceMgrDmlData);
    }

    return ret;
}

/**********************************************************************

    caller:     owner of this object

    prototype:

        BOOL VoiceProfile_SetParamUlongValue(ANSC_HANDLE hInsContext, char* ParamName, ULONG uValue);

    description:

        This function is called to retrieve Ulong parameter value;

    argument:   ANSC_HANDLE                 hInsContext,
                The instance handle;

                char*                       ParamName,
                The parameter name;

                ULONG                       uValue,
                The ULong value to set;

    return:     TRUE if succeeded.

**********************************************************************/
BOOL VoiceProfile_SetParamUlongValue(ANSC_HANDLE hInsContext, char* ParamName, ULONG uValue)
{

    DML_PROFILE_CTRL_T* pTelcoVoiceMgrCtrl = (DML_PROFILE_CTRL_T*) hInsContext;
    PTELCOVOICEMGR_DML_VOICESERVICE pDmlVoiceService = NULL;
    BOOL ret = FALSE;
    ULONG uVsIndex = 0;
    ULONG uVpIndex = 0;

    if(pTelcoVoiceMgrCtrl != NULL)
    {
        TELCOVOICEMGR_DML_DATA* pTelcoVoiceMgrDmlData = TelcoVoiceMgrDmlGetDataLocked();
        if(pTelcoVoiceMgrDmlData != NULL)
        {
            TELCOVOICEMGR_DML_VOICEPROFILE* pVoiceProfile = &(pTelcoVoiceMgrCtrl->dml);

            if (!pVoiceProfile)
            {
                CcspTraceError(("%s: NULL Pointer\n", __FUNCTION__));
                TelcoVoiceMgrDmlGetDataRelease(pTelcoVoiceMgrDmlData);
                return ret;
            }

            pDmlVoiceService = pVoiceProfile->pParentVoiceService;
            if(pDmlVoiceService)
            {
                uVsIndex = pDmlVoiceService->InstanceNumber;
                uVpIndex = pVoiceProfile->InstanceNumber;
                TelcoVoiceMgrDmlGetDataRelease(pTelcoVoiceMgrDmlData);
                if (strcmp(ParamName, "X_RDK-Central_COM_SDigitTimer") == 0)
                {
                    if( TelcoVoiceMgrDmlSetSDigitTimer(uVsIndex, uVpIndex, uValue )== ANSC_STATUS_SUCCESS)
                    {
                        TELCOVOICEMGR_DML_DATA* pTelcoVoiceMgrDmlData = TelcoVoiceMgrDmlGetDataLocked();
                        if(pTelcoVoiceMgrDmlData != NULL)
                        {
                            pVoiceProfile->SDigitTimer  =  uValue ;
                            TelcoVoiceMgrDmlGetDataRelease(pTelcoVoiceMgrDmlData);
                            return TRUE;
                        }
                    }
                }
                else if (strcmp(ParamName, "X_RDK-Central_COM_ZDigitTimer") == 0)
                {
                    if(TelcoVoiceMgrDmlSetZDigitTimer(uVsIndex, uVpIndex, uValue ) == ANSC_STATUS_SUCCESS)
                    {
                        TELCOVOICEMGR_DML_DATA* pTelcoVoiceMgrDmlData = TelcoVoiceMgrDmlGetDataLocked();
                        if(pTelcoVoiceMgrDmlData != NULL)
                        {
                            pVoiceProfile->ZDigitTimer  =  uValue;
                            TelcoVoiceMgrDmlGetDataRelease(pTelcoVoiceMgrDmlData);
                            return TRUE;
                        }
                    }
                }
                else if (strcmp(ParamName, "Enable") == 0)
                {
                    pVoiceProfile->Enable = uValue;
                    ret = TRUE;
                }
            }
            else
            {
                CcspTraceWarning(("%s::Invalid Object pDmlVoiceService\n", __FUNCTION__));
                TelcoVoiceMgrDmlGetDataRelease(pTelcoVoiceMgrDmlData);
            }
        }    
    }

    return ret;
}

/**********************************************************************

    caller:     owner of this object

    prototype:

        ULONG VoiceProfile_GetEntryCount(ANSC_HANDLE hInsContext);

    description:

        This function is called to retrieve the count of the table.

    argument:   ANSC_HANDLE                 hInsContext,
                The instance handle;

    return:     The count of the table

**********************************************************************/
ULONG VoiceProfile_GetEntryCount(ANSC_HANDLE hInsContext)
{
    ULONG count = 0;
    PTELCOVOICEMGR_DML_VOICESERVICE       pDmlVoiceService    = NULL;
    DML_VOICE_SERVICE_CTRL_T* pVoiceService = (DML_VOICE_SERVICE_CTRL_T*) hInsContext;
    if(pVoiceService != NULL)
    {
        TELCOVOICEMGR_DML_DATA* pTelcoVoiceMgrDmlData = TelcoVoiceMgrDmlGetDataLocked();
        if(pTelcoVoiceMgrDmlData != NULL)
        {
            pDmlVoiceService = &(pVoiceService->dml);   
            count =  pDmlVoiceService->VoiceProfileList.ulQuantity;

            TelcoVoiceMgrDmlGetDataRelease(pTelcoVoiceMgrDmlData);
        }
    }
    return count;
}

/**********************************************************************

    caller:     owner of this object
        BOOL VoiceProfile_SetParamBoolValue(ANSC_HANDLE hInsContext, char* ParamName, char* pString);

    description:

        This function is called to set String parameter value;

    argument:   ANSC_HANDLE                 hInsContext,
                The instance handle;

                char*                       ParamName,
                The parameter name;

                char*                       pValue,
                The buffer to set value;

    return:     TRUE if succeeded.

**********************************************************************/
BOOL VoiceProfile_SetParamBoolValue(ANSC_HANDLE hInsContext, char* ParamName, BOOL bValue)
{
    BOOL ret = FALSE;
    if (strcmp(ParamName, "Reset") == 0)
    {
        ret = TRUE;
    }
    else if (strcmp(ParamName, "DigitMapEnable") == 0)
    {
        ret = TRUE;
    }
    else if (strcmp(ParamName, "STUNEnable") == 0)
    {
        ret = TRUE;
    }
    else if (strcmp(ParamName, "PSTNFailOver") == 0)
    {
        ret = TRUE;
    }
    else
    {
         CcspTraceWarning(("%s::Unknown ParamName_Ret_OK:%s\n", __FUNCTION__, ParamName));
        ret = TRUE;
    }
    
    return ret;
}

/**********************************************************************

    caller:     owner of this object

    prototype:

    BOOL VoiceProfile_GetParamBoolValue(ANSC_HANDLE hInsContext, char* ParamName, BOOL* pBool);

    description:
        This function is called to retrieve BOOL parameter value;

    argument:   ANSC_HANDLE                 hInsContext,
            The instance handle;

            char*                       ParamName,
            The parameter name;

            BOOL*                      pBool
            The buffer of returned pBool;

    return:     TRUE if succeeded.

**********************************************************************/
BOOL VoiceProfile_GetParamBoolValue(ANSC_HANDLE hInsContext, char* ParamName, BOOL* pBool)
{
    BOOL ret = FALSE;
    DML_PROFILE_CTRL_T* pVoiceProfile = (DML_PROFILE_CTRL_T *) hInsContext;
    if(pVoiceProfile == NULL)
    {
        CcspTraceError(("%s:%d:: Invalid object \n", __FUNCTION__, __LINE__));
        return ret;
    }

    TELCOVOICEMGR_DML_DATA* pTelcoVoiceMgrDmlData = TelcoVoiceMgrDmlGetDataLocked();
    if(pTelcoVoiceMgrDmlData == NULL)
    {
        CcspTraceError(("%s:%d:: TelcoVoiceMgrDmlGetDataLocked: Failed\n", __FUNCTION__, __LINE__));
        return ret;
    }

    PTELCOVOICEMGR_DML_PROFILE pDmlVoiceProfile = &(pVoiceProfile->dml);
    if(pDmlVoiceProfile == NULL )
    {
        TelcoVoiceMgrDmlGetDataRelease(pTelcoVoiceMgrDmlData);
        CcspTraceError(("%s:%d:: pDmlPhyInterface: NULL\n", __FUNCTION__, __LINE__));
        return ret;
    }
    
    if(pDmlVoiceProfile != NULL)
    {
        if (strcmp(ParamName, "Reset") == 0)
        {
            *pBool = pDmlVoiceProfile->Reset;
            ret = TRUE;
        }
        else if (strcmp(ParamName, "DigitMapEnable") == 0)
        {
            *pBool = pDmlVoiceProfile->DigitMapEnable;
            ret = TRUE;
        }
        else if (strcmp(ParamName, "STUNEnable") == 0)
        {
            *pBool = pDmlVoiceProfile->STUNEnable;
            ret = TRUE;
        }
        else if (strcmp(ParamName, "PSTNFailOver") == 0)
        {
            *pBool = pDmlVoiceProfile->PSTNFailOver;
            ret = TRUE;
        }
        else
        {
            CcspTraceWarning(("%s::Unknown ParamName :%s\n", __FUNCTION__, ParamName));
        }
    }
    TelcoVoiceMgrDmlGetDataRelease(pTelcoVoiceMgrDmlData);
    return ret;
}

/**********************************************************************

    caller:     owner of this object

    prototype:

        ANSC_HANDLE VoiceProfile_GetEntry(ANSC_HANDLE hInsContext, ULONG nIndex, ULONG* pInsNumber);

    description:

        This function is called to retrieve the entry specified by the index.

    argument:   ANSC_HANDLE                 hInsContext,
                The instance handle;

                ULONG                       nIndex,
                The index of this entry;

                ULONG*                      pInsNumber
                The output instance number;

    return:     The handle to identify the entry

**********************************************************************/
ANSC_HANDLE VoiceProfile_GetEntry(ANSC_HANDLE hInsContext, ULONG nIndex, ULONG* pInsNumber)
{
    ANSC_HANDLE pDmlEntry = NULL;
    PTELCOVOICEMGR_DML_VOICESERVICE       pDmlVoiceService    = NULL;
    DML_VOICE_SERVICE_CTRL_T* pVoiceService = (DML_VOICE_SERVICE_CTRL_T*) hInsContext;
    if(pVoiceService != NULL)
    {
        TELCOVOICEMGR_DML_DATA* pTelcoVoiceMgrDmlData = TelcoVoiceMgrDmlGetDataLocked();
        if(pTelcoVoiceMgrDmlData != NULL)
        {
            pDmlVoiceService = &(pVoiceService->dml);
            if(nIndex < pDmlVoiceService->VoiceProfileList.ulQuantity)
            {   
                DML_PROFILE_CTRL_T* pDmlVoiceProfile = pDmlVoiceService->VoiceProfileList.pdata[nIndex];
                if(pDmlVoiceProfile != NULL)
                {
                    *pInsNumber = nIndex + 1;
                    pDmlEntry = (ANSC_HANDLE) pDmlVoiceProfile;
                }
            }
            TelcoVoiceMgrDmlGetDataRelease(pTelcoVoiceMgrDmlData);
        }

    }


    return pDmlEntry;  /* return the handle */
}

/**********************************************************************  

    caller:     owner of this object 

    prototype: 

        BOOL VoiceProfile_Validate(ANSC_HANDLE hInsContext);

    description:

        This function is called to validate the update.

    argument:   ANSC_HANDLE                 hInsContext,
                The instance handle;

    return:     0 if there's no issue.

**********************************************************************/
BOOL VoiceProfile_Validate(ANSC_HANDLE hInsContext)
{
    return TRUE;
}

/**********************************************************************  

    caller:     owner of this object 

    prototype: 

        BOOL VoiceProfile_Commit(ANSC_HANDLE hInsContext);

    description:

        This function is called to validate the update.

    argument:   ANSC_HANDLE                 hInsContext,
                The instance handle;

    return:     0 if there's no issue.

**********************************************************************/
ULONG VoiceProfile_Commit(ANSC_HANDLE hInsContext)
{
    return 0;
}

/**********************************************************************  

    caller:     owner of this object 

    prototype: 

        BOOL VoiceProfile_Rollback(ANSC_HANDLE hInsContext);

    description:

        This function is called to validate the update.

    argument:   ANSC_HANDLE                 hInsContext,
                The instance handle;

    return:     0 if there's no issue.

**********************************************************************/
ULONG VoiceProfile_Rollback(ANSC_HANDLE hInsContext)
{
    return 0;
}

/**********************************************************************

    caller:     owner of this object

    prototype:

        BOOL SIP_GetParamStringValue(ANSC_HANDLE hInsContext, char* ParamName, char* pValue, ULONG* pUlSize);

    description:

        This function is called to retrieve String parameter value;

    argument:   ANSC_HANDLE                 hInsContext,
                The instance handle;

                char*                       ParamName,
                The parameter name;

                char*                       pValue,
                The buffer of returned ULONG value;

                ULONG*                      pUlSize
                The length of returned buffer value;

    return:     0  if succeeded.
                1  if short of buufer
                -1 if not supported

**********************************************************************/
LONG SIP_GetParamStringValue(ANSC_HANDLE hInsContext, char* ParamName, char* pValue, ULONG* pUlSize)
{

    DML_PROFILE_CTRL_T* pTelcoVoiceMgrCtrl = (DML_PROFILE_CTRL_T*) hInsContext;
    ULONG ret = 1;

    if(pTelcoVoiceMgrCtrl != NULL)
    {
        TELCOVOICEMGR_DML_DATA* pTelcoVoiceMgrDmlData = TelcoVoiceMgrDmlGetDataLocked();
        if(pTelcoVoiceMgrDmlData != NULL)
        {
          TELCOVOICEMGR_DML_VOICEPROFILE* pVoiceProfile = &(pTelcoVoiceMgrCtrl->dml);

          if (pVoiceProfile != NULL)
          {
            if (strcmp(ParamName, "OutboundProxy") == 0)
            { 
                AnscCopyString(pValue, pVoiceProfile->SIPObj.OutboundProxy);
                ret = 0;
            }
            else if (strcmp(ParamName, "ProxyServer") == 0)
            {
                AnscCopyString(pValue, pVoiceProfile->SIPObj.ProxyServer);
                ret = 0;
            }
            else if (strcmp(ParamName, "RegistrarServer") == 0)
            {
                AnscCopyString(pValue, pVoiceProfile->SIPObj.RegistrarServer);
                ret = 0;
            }
            else if (strcmp(ParamName, "UserAgentDomain") == 0)
            {
                AnscCopyString(pValue, pVoiceProfile->SIPObj.UserAgentDomain);
                ret = 0;
            }
            else if (strcmp(ParamName, "X_RDK-Central_COM_ConferencingURI") == 0)
            {
                AnscCopyString(pValue, pVoiceProfile->SIPObj.ConferencingURI);
                ret = 0;
            }
            else if (strcmp(ParamName, "UserAgentTransport") == 0)
            {
                AnscCopyString(pValue, pVoiceProfile->SIPObj.UserAgentTransport);
                ret = 0;
            }
            else if (strcmp(ParamName, "RegistrarServerTransport") == 0)
            {
                AnscCopyString(pValue, pVoiceProfile->SIPObj.RegistrarServerTransport);
                ret = 0;
            }
            else if (strcmp(ParamName, "Organization") == 0)
            {
                AnscCopyString(pValue, pVoiceProfile->SIPObj.Organization);
                ret = 0;
            }
            else if (strcmp(ParamName, "InboundAuth") == 0)
            {
                if(pVoiceProfile->SIPObj.InboundAuth == SIP_INBOUNDAUTH_NONE)
                {
                    AnscCopyString(pValue, "None");
                }
                else if(pVoiceProfile->SIPObj.InboundAuth == SIP_INBOUNDAUTH_DIGEST)
                {
                    AnscCopyString(pValue, "Digest");
                }
                
                ret = 0;
            }
            else if (strcmp(ParamName, "InboundAuthUsername") == 0)
            {
                AnscCopyString(pValue, pVoiceProfile->SIPObj.InboundAuthUsername);
                ret = 0;
            }
            else if (strcmp(ParamName, "InboundAuthPassword") == 0)
            {
                AnscCopyString(pValue, pVoiceProfile->SIPObj.InboundAuthPassword);
                ret = 0;
            }
            else if (strcmp(ParamName, "RegistrarServerTransport") == 0)
            {
                AnscCopyString(pValue, pVoiceProfile->SIPObj.RegistrarServerTransport);
                ret = 0;
            }
            else if (strcmp(ParamName, "ProxyServerTransport") == 0)
            {
                AnscCopyString(pValue, pVoiceProfile->SIPObj.ProxyServerTransport);
                ret = 0;
            }
            else
            {
                CcspTraceWarning(("%s::Unknown ParamName :%s\n", __FUNCTION__, ParamName));
            }
          }
          TelcoVoiceMgrDmlGetDataRelease(pTelcoVoiceMgrDmlData);
        }   
	
    }

    return ret;
}

/**********************************************************************

    caller:     owner of this object

    prototype:

        BOOL SIP_SetParamStringValue(ANSC_HANDLE hInsContext, char* ParamName, char* pString);

    description:

        This function is called to set String parameter value;

    argument:   ANSC_HANDLE                 hInsContext,
                The instance handle;

                char*                       ParamName,
                The parameter name;

                char*                       pValue,
                The buffer to set value;

    return:     TRUE if succeeded.

**********************************************************************/

BOOL SIP_SetParamStringValue(ANSC_HANDLE hInsContext, char* ParamName, char* pString)
{
    DML_PROFILE_CTRL_T* pTelcoVoiceMgrCtrl = (DML_PROFILE_CTRL_T*) hInsContext;
    PTELCOVOICEMGR_DML_VOICESERVICE pDmlVoiceService = NULL;
    BOOL ret = FALSE;
    ULONG uVsIndex = 0;
    ULONG uVpIndex = 0;

    if(pTelcoVoiceMgrCtrl != NULL)
    {
        TELCOVOICEMGR_DML_DATA* pTelcoVoiceMgrDmlData = TelcoVoiceMgrDmlGetDataLocked();
        if(pTelcoVoiceMgrDmlData != NULL)
        {
            TELCOVOICEMGR_DML_VOICEPROFILE* pVoiceProfile = &(pTelcoVoiceMgrCtrl->dml);

            if (!pVoiceProfile || !pString)
            {
                CcspTraceError(("%s: NULL Pointer\n", __FUNCTION__));
                TelcoVoiceMgrDmlGetDataRelease(pTelcoVoiceMgrDmlData);
                return FALSE;
            }
            else
            {
                pDmlVoiceService = pVoiceProfile->pParentVoiceService;
                uVsIndex = pDmlVoiceService->InstanceNumber;
                uVpIndex = pVoiceProfile->InstanceNumber;
                TelcoVoiceMgrDmlGetDataRelease(pTelcoVoiceMgrDmlData);
                if (strcmp(ParamName, "OutboundProxy") == 0)
                {
                    if(TelcoVoiceMgrDmlSetOutboundProxy(uVsIndex,pVoiceProfile->InstanceNumber, pString) == ANSC_STATUS_SUCCESS)
                    {
                        TELCOVOICEMGR_DML_DATA* pTelcoVoiceMgrDmlData = TelcoVoiceMgrDmlGetDataLocked();
                        if(pTelcoVoiceMgrDmlData != NULL)
                        {
                            AnscCopyString(pVoiceProfile->SIPObj.OutboundProxy, pString);
                            TelcoVoiceMgrDmlGetDataRelease(pTelcoVoiceMgrDmlData);
                            return TRUE;
                        }
                    }
                }
                else if (strcmp(ParamName, "ProxyServer") == 0)
                {
                    if(TelcoVoiceMgrDmlSetProxyServer(uVsIndex,pVoiceProfile->InstanceNumber, pString) == ANSC_STATUS_SUCCESS)
                    {
                        TELCOVOICEMGR_DML_DATA* pTelcoVoiceMgrDmlData = TelcoVoiceMgrDmlGetDataLocked();
                        if(pTelcoVoiceMgrDmlData != NULL)
                        {
                            AnscCopyString(pVoiceProfile->SIPObj.ProxyServer, pString);
                            TelcoVoiceMgrDmlGetDataRelease(pTelcoVoiceMgrDmlData);
                            return TRUE;
                        }
                    }
                }
                else if (strcmp(ParamName, "RegistrarServer") == 0)
                {
                    if(TelcoVoiceMgrDmlSetRegistrarServer(uVsIndex,pVoiceProfile->InstanceNumber, pString) == ANSC_STATUS_SUCCESS)
                    {
                        TELCOVOICEMGR_DML_DATA* pTelcoVoiceMgrDmlData = TelcoVoiceMgrDmlGetDataLocked();
                        if(pTelcoVoiceMgrDmlData != NULL)
                        {
                            AnscCopyString(pVoiceProfile->SIPObj.RegistrarServer, pString);
                            TelcoVoiceMgrDmlGetDataRelease(pTelcoVoiceMgrDmlData);
                            return TRUE;
                        }
                    }
                }
                else if (strcmp(ParamName, "UserAgentDomain") == 0)
                {
                    if(TelcoVoiceMgrDmlSetUserAgentDomain(uVsIndex, uVpIndex, pString) == ANSC_STATUS_SUCCESS)
                    {
                        TELCOVOICEMGR_DML_DATA* pTelcoVoiceMgrDmlData = TelcoVoiceMgrDmlGetDataLocked();
                        if(pTelcoVoiceMgrDmlData != NULL)
                        {
                            AnscCopyString(pVoiceProfile->SIPObj.UserAgentDomain, pString);
                            TelcoVoiceMgrDmlGetDataRelease(pTelcoVoiceMgrDmlData);
                            return TRUE;
                        }
                    }
                }
                else if (strcmp(ParamName, "X_RDK-Central_COM_ConferencingURI") == 0)
                {
                    if(TelcoVoiceMgrDmlSetConferencingURI(uVsIndex, uVpIndex, pString) == ANSC_STATUS_SUCCESS)
                    {
                        TELCOVOICEMGR_DML_DATA* pTelcoVoiceMgrDmlData = TelcoVoiceMgrDmlGetDataLocked();
                        if(pTelcoVoiceMgrDmlData != NULL)
                        {
                            AnscCopyString(pVoiceProfile->SIPObj.ConferencingURI, pString);
                            TelcoVoiceMgrDmlGetDataRelease(pTelcoVoiceMgrDmlData);
                            return TRUE;
                        }
                    }
                }
                else if (strcmp(ParamName, "UserAgentTransport") == 0)
                {
                    ret = 0;
                }
                else if (strcmp(ParamName, "RegistrarServerTransport") == 0)
                {
                    ret = 0;
                }
                else if (strcmp(ParamName, "Organization") == 0)
                {
                    ret = 0;
                }
                else if (strcmp(ParamName, "InboundAuth") == 0)
                {
                    ret = 0;
                }
                else if (strcmp(ParamName, "InboundAuthUsername") == 0)
                {
                    ret = 0;
                }
                else if (strcmp(ParamName, "InboundAuthPassword") == 0)
                {
                    ret = 0;
                }
                else if (strcmp(ParamName, "RegistrarServerTransport") == 0)
                {
                    ret = 0;
                }
                else
                {
                    CcspTraceWarning(("%s::Unknown ParamName :%s\n", __FUNCTION__, ParamName));
                    ret =  0;
                }
            }
        }
        
    }

    return ret;
}

/**********************************************************************

    caller:     owner of this object

    prototype:

        BOOL SIP_GetParamUlongValue(ANSC_HANDLE hInsContext, char* ParamName, ULONG* pValue);

    description:

        This function is called to retrieve Ulong parameter value;

    argument:   ANSC_HANDLE                 hInsContext,
                The instance handle;

                char*                       ParamName,
                The parameter name;

                ULONG*                      pValue
                The value returned

    return:     TRUE if succeeded.

**********************************************************************/
BOOL SIP_GetParamUlongValue(ANSC_HANDLE hInsContext, char* ParamName, ULONG* pValue)
{

    DML_PROFILE_CTRL_T* pTelcoVoiceMgrCtrl = (DML_PROFILE_CTRL_T*) hInsContext;
    BOOL ret = FALSE;

    if(pTelcoVoiceMgrCtrl != NULL)
    {
        TELCOVOICEMGR_DML_DATA* pTelcoVoiceMgrDmlData = TelcoVoiceMgrDmlGetDataLocked();
        if(pTelcoVoiceMgrDmlData != NULL)
        {
            TELCOVOICEMGR_DML_VOICEPROFILE* pVoiceProfile = &(pTelcoVoiceMgrCtrl->dml);

            if (!pVoiceProfile || !pValue)
            {
                CcspTraceError(("%s: NULL Pointer\n", __FUNCTION__));
                TelcoVoiceMgrDmlGetDataRelease(pTelcoVoiceMgrDmlData);
                return ret;
            }

            if (strcmp(ParamName, "OutboundProxyPort") == 0)
            {
                * pValue = pVoiceProfile->SIPObj.OutboundProxyPort;
                ret = TRUE;
            }
            else if (strcmp(ParamName, "ProxyServerPort") == 0)
            {
                * pValue = pVoiceProfile->SIPObj.ProxyServerPort;
                ret = TRUE;
            }
            else if (strcmp(ParamName, "RegistrarServerPort") == 0)
            {
                * pValue = pVoiceProfile->SIPObj.RegistrarServerPort;
                ret = TRUE;
            }
            else if (strcmp(ParamName, "DSCPMark") == 0)
            {
                * pValue = pVoiceProfile->SIPObj.DSCPMark;
                ret = TRUE;
            }
            else if (strcmp(ParamName, "X_RDK_SKBMark") == 0)
            {
                * pValue = pVoiceProfile->SIPObj.X_RDK_SKBMark;
                ret = TRUE;
            }
            else if (strcmp(ParamName, "UserAgentPort") == 0)
            {
                * pValue = pVoiceProfile->SIPObj.UserAgentPort;
                ret = TRUE;
            }
            else if (strcmp(ParamName, "RegistrationPeriod") == 0)
            {
                * pValue = pVoiceProfile->SIPObj.RegistrationPeriod;
                ret = TRUE;
            }
            else if (strcmp(ParamName, "TimerT1") == 0)
            {
                * pValue = pVoiceProfile->SIPObj.TimerT1;
                ret = TRUE;
            }
            else if (strcmp(ParamName, "TimerT2") == 0)
            {
                * pValue = pVoiceProfile->SIPObj.TimerT2;
                ret = TRUE;
            }
            else if (strcmp(ParamName, "TimerT4") == 0)
            {
                * pValue = pVoiceProfile->SIPObj.TimerT4;
                ret = TRUE;
            }
            else if (strcmp(ParamName, "TimerA") == 0)
            {
                * pValue = pVoiceProfile->SIPObj.TimerA;
                ret = TRUE;
            }
            else if (strcmp(ParamName, "TimerB") == 0)
            {
                * pValue = pVoiceProfile->SIPObj.TimerB;
                ret = TRUE;
            }
            else if (strcmp(ParamName, "TimerC") == 0)
            {
                * pValue = pVoiceProfile->SIPObj.TimerC;
                ret = TRUE;
            }
            else if (strcmp(ParamName, "TimerD") == 0)
            {
                * pValue = pVoiceProfile->SIPObj.TimerD;
                ret = TRUE;
            }
            else if (strcmp(ParamName, "TimerE") == 0)
            {
                * pValue = pVoiceProfile->SIPObj.TimerE;
                ret = TRUE;
            }
            else if (strcmp(ParamName, "TimerF") == 0)
            {
                * pValue = pVoiceProfile->SIPObj.TimerF;
                ret = TRUE;
            }
            else if (strcmp(ParamName, "TimerG") == 0)
            {
                * pValue = pVoiceProfile->SIPObj.TimerG;
                ret = TRUE;
            }
            else if (strcmp(ParamName, "TimerH") == 0)
            {
                * pValue = pVoiceProfile->SIPObj.TimerH;
                ret = TRUE;
            }
            else if (strcmp(ParamName, "TimerI") == 0)
            {
                * pValue = pVoiceProfile->SIPObj.TimerI;
                ret = TRUE;
            }
            else if (strcmp(ParamName, "TimerJ") == 0)
            {
                * pValue = pVoiceProfile->SIPObj.TimerJ;
                ret = TRUE;
            }
            else if (strcmp(ParamName, "TimerK") == 0)
            {
                * pValue = pVoiceProfile->SIPObj.TimerK;
                ret = TRUE;
            }
            else if (strcmp(ParamName, "InviteExpires") == 0)
            {
                * pValue = pVoiceProfile->SIPObj.InviteExpires;
                ret = TRUE;
            }
            else if (strcmp(ParamName, "ReInviteExpires") == 0)
            {
                * pValue = pVoiceProfile->SIPObj.ReInviteExpires;
                ret = TRUE;
            }
            else if (strcmp(ParamName, "RegisterExpires") == 0)
            {
                * pValue = pVoiceProfile->SIPObj.RegisterExpires;
                ret = TRUE;
            }
            else if (strcmp(ParamName, "RegistersMinExpires") == 0)
            {
                * pValue = pVoiceProfile->SIPObj.RegistersMinExpires;
                ret = TRUE;
            }
            else if (strcmp(ParamName, "RegisterRetryInterval") == 0)
            {
                * pValue = pVoiceProfile->SIPObj.RegisterRetryInterval;
                ret = TRUE;
            }
            else
            {
                CcspTraceWarning(("%s::Unknown ParamName :%s\n", __FUNCTION__, ParamName));
            }
            TelcoVoiceMgrDmlGetDataRelease(pTelcoVoiceMgrDmlData);
        }    
    }
    return ret;
}

/**********************************************************************

    caller:     owner of this object

    prototype:

        BOOL SIP_SetParamUlongValue(ANSC_HANDLE hInsContext, char* ParamName, ULONG uValue);

    description:

        This function is called to set Ulong parameter value;

    argument:   ANSC_HANDLE                 hInsContext,
                The instance handle;

                char*                       ParamName,
                The parameter name;

                ULONG                       uValue
                The value need to set

    return:     TRUE if succeeded.

**********************************************************************/
BOOL SIP_SetParamUlongValue(ANSC_HANDLE hInsContext, char* ParamName, ULONG uValue)
{
    DML_PROFILE_CTRL_T* pTelcoVoiceMgrCtrl = (DML_PROFILE_CTRL_T*) hInsContext;
    PTELCOVOICEMGR_DML_VOICESERVICE pDmlVoiceService = NULL;
    BOOL ret = FALSE;
    ULONG uVsIndex = 0;
    ULONG uVpIndex = 0;

    if(pTelcoVoiceMgrCtrl != NULL)
    {
        TELCOVOICEMGR_DML_DATA* pTelcoVoiceMgrDmlData = TelcoVoiceMgrDmlGetDataLocked();
        if(pTelcoVoiceMgrDmlData != NULL)
        {
            TELCOVOICEMGR_DML_VOICEPROFILE* pVoiceProfile = &(pTelcoVoiceMgrCtrl->dml);

            if (!pVoiceProfile)
            {
                CcspTraceError(("%s: NULL Pointer\n", __FUNCTION__));
                TelcoVoiceMgrDmlGetDataRelease(pTelcoVoiceMgrDmlData);
                return ret;
            }
            pDmlVoiceService = pVoiceProfile->pParentVoiceService;
            if(pDmlVoiceService)
            {
                uVsIndex = pDmlVoiceService->InstanceNumber;
                uVpIndex = pVoiceProfile->InstanceNumber;
                TelcoVoiceMgrDmlGetDataRelease(pTelcoVoiceMgrDmlData);
                if (strcmp(ParamName, "OutboundProxyPort") == 0)
                {
                    if(TelcoVoiceMgrDmlSetOutboundProxyPort(uVsIndex,uVpIndex, uValue) == ANSC_STATUS_SUCCESS)
                    {
                        TELCOVOICEMGR_DML_DATA* pTelcoVoiceMgrDmlData = TelcoVoiceMgrDmlGetDataLocked();
                        if(pTelcoVoiceMgrDmlData != NULL)
                        {
                            pVoiceProfile->SIPObj.OutboundProxyPort  =  uValue;
                            TelcoVoiceMgrDmlGetDataRelease(pTelcoVoiceMgrDmlData);
                            return TRUE;
                        }
                    }
                }
                else if (strcmp(ParamName, "ProxyServerPort") == 0)
                {
                    if(TelcoVoiceMgrDmlSetProxyServerPort(uVsIndex,uVpIndex, uValue) == ANSC_STATUS_SUCCESS)
                    {
                        TELCOVOICEMGR_DML_DATA* pTelcoVoiceMgrDmlData = TelcoVoiceMgrDmlGetDataLocked();
                        if(pTelcoVoiceMgrDmlData != NULL)
                        {
                            pVoiceProfile->SIPObj.ProxyServerPort  =  uValue;
                            TelcoVoiceMgrDmlGetDataRelease(pTelcoVoiceMgrDmlData);
                            return TRUE;
                        }
                    }
                }
                else if (strcmp(ParamName, "RegistrarServerPort") == 0)
                {
                    if(TelcoVoiceMgrDmlSetRegistrarServerPort(uVsIndex,uVpIndex, uValue) == ANSC_STATUS_SUCCESS)
                    {
                        TELCOVOICEMGR_DML_DATA* pTelcoVoiceMgrDmlData = TelcoVoiceMgrDmlGetDataLocked();
                        if(pTelcoVoiceMgrDmlData != NULL)
                        {
                            pVoiceProfile->SIPObj.RegistrarServerPort  =  uValue;
                            TelcoVoiceMgrDmlGetDataRelease(pTelcoVoiceMgrDmlData);
                            return TRUE;
                        }
                    }
                }
                else if (strcmp(ParamName, "DSCPMark") == 0)
                {
                    if(TelcoVoiceMgrDmlSetSipDscpMark(uVsIndex, uVpIndex, uValue) == ANSC_STATUS_SUCCESS)
                    {
                        TELCOVOICEMGR_DML_DATA* pTelcoVoiceMgrDmlData = TelcoVoiceMgrDmlGetDataLocked();
                        if(pTelcoVoiceMgrDmlData != NULL)
                        {
                            pVoiceProfile->SIPObj.DSCPMark  =  uValue;
                            TelcoVoiceMgrDmlGetDataRelease(pTelcoVoiceMgrDmlData);
                            ret = TRUE;
                        }
                    }
                }
                else if (strcmp(ParamName, "UserAgentPort") == 0)
                {
                        pVoiceProfile->SIPObj.UserAgentPort  =  uValue;
                        ret = TRUE;
                }
                else
                {
                    CcspTraceWarning(("%s::Unknown ParamName :%s\n", __FUNCTION__, ParamName));
                    ret =  FALSE;
                }
            }
            else
            {
                TelcoVoiceMgrDmlGetDataRelease(pTelcoVoiceMgrDmlData);
            }
        }
        
    }

    return ret;
}

/**********************************************************************

    caller:     owner of this object

    prototype:

        BOOL SIP_GetParamIntValue(ANSC_HANDLE hInsContext, char* ParamName, int* pInt);

    description:

        This function is called to retrieve int parameter value;

    argument:   ANSC_HANDLE                 hInsContext,
                The instance handle;

                char*                       ParamName,
                The parameter name;

                int*                        pInt
                The value returned

    return:     TRUE if succeeded.

**********************************************************************/
BOOL SIP_GetParamIntValue(ANSC_HANDLE hInsContext, char* ParamName, int* pInt)
{
    DML_PROFILE_CTRL_T* pTelcoVoiceMgrCtrl = (DML_PROFILE_CTRL_T*) hInsContext;
    BOOL ret = FALSE;

    if(pTelcoVoiceMgrCtrl != NULL)
    {
        TELCOVOICEMGR_DML_DATA* pTelcoVoiceMgrDmlData = TelcoVoiceMgrDmlGetDataLocked();
        if(pTelcoVoiceMgrDmlData != NULL)
        {
            TELCOVOICEMGR_DML_VOICEPROFILE* pVoiceProfile = &(pTelcoVoiceMgrCtrl->dml);

            if (!pVoiceProfile || !pInt)
            {
                CcspTraceError(("%s: NULL Pointer\n", __FUNCTION__));
                TelcoVoiceMgrDmlGetDataRelease(pTelcoVoiceMgrDmlData);
                return ret;
            }

            if (strcmp(ParamName, "EthernetPriorityMark") == 0)
            {
               * pInt = pVoiceProfile->SIPObj.EthernetPriorityMark;
               ret = TRUE;
            }
            else if (strcmp(ParamName, "VLANIDMark") == 0)
            {
               * pInt = pVoiceProfile->SIPObj.VLANIDMark;
               ret = TRUE;
            }
            else
            {
                CcspTraceWarning(("%s::Unknown ParamName :%s\n", __FUNCTION__, ParamName));
                ret =  FALSE;
            }
            TelcoVoiceMgrDmlGetDataRelease(pTelcoVoiceMgrDmlData);
        }
        
    }

    return ret;
}

/**********************************************************************

    caller:     owner of this object

    prototype:

        BOOL SIP_SetParamIntValue(ANSC_HANDLE hInsContext, char* ParamName, int iValue);

    description:

        This function is called to set Ulong parameter value;

    argument:   ANSC_HANDLE                 hInsContext,
                The instance handle;

                char*                       ParamName,
                The parameter name;

                int                         iValue
                The value need to set

    return:     TRUE if succeeded.

**********************************************************************/
BOOL SIP_SetParamIntValue(ANSC_HANDLE hInsContext, char* ParamName, int iValue)
{
    DML_PROFILE_CTRL_T* pTelcoVoiceMgrCtrl = (DML_PROFILE_CTRL_T*) hInsContext;
    PTELCOVOICEMGR_DML_VOICESERVICE pDmlVoiceService = NULL;
    BOOL ret = FALSE;
    ULONG uVsIndex = 0;
    ULONG uVpIndex = 0;

    if(pTelcoVoiceMgrCtrl != NULL)
    {
        TELCOVOICEMGR_DML_DATA* pTelcoVoiceMgrDmlData = TelcoVoiceMgrDmlGetDataLocked();
        if(pTelcoVoiceMgrDmlData != NULL)
        {
            TELCOVOICEMGR_DML_VOICEPROFILE* pVoiceProfile = &(pTelcoVoiceMgrCtrl->dml);

            if (!pVoiceProfile)
            {
                CcspTraceError(("%s: NULL Pointer\n", __FUNCTION__));
                TelcoVoiceMgrDmlGetDataRelease(pTelcoVoiceMgrDmlData);
                return ret;
            }

            pDmlVoiceService = pVoiceProfile->pParentVoiceService;
            if(pDmlVoiceService)
            {
                uVsIndex = pDmlVoiceService->InstanceNumber;
                uVpIndex = pVoiceProfile->InstanceNumber;
                TelcoVoiceMgrDmlGetDataRelease(pTelcoVoiceMgrDmlData);

                if (strcmp(ParamName, "EthernetPriorityMark") == 0)
                {
                    if(TelcoVoiceMgrDmlSetSipEthernetPriorityMark(uVsIndex,uVpIndex,iValue) == ANSC_STATUS_SUCCESS)
                    {
                       TELCOVOICEMGR_DML_DATA* pTelcoVoiceMgrDmlData = TelcoVoiceMgrDmlGetDataLocked();
                       if(pTelcoVoiceMgrDmlData != NULL)
                       {
                            pVoiceProfile->SIPObj.EthernetPriorityMark  =  iValue;
                            TelcoVoiceMgrDmlGetDataRelease(pTelcoVoiceMgrDmlData);
                            ret =  TRUE;
                       }
                    }
                }
                else if (strcmp(ParamName, "VLANIDMark") == 0)
                {
                    ret = TRUE;
                }
                else
                {
                    CcspTraceWarning(("%s::Unknown ParamName :%s\n", __FUNCTION__, ParamName));
                    ret =  FALSE;
                }
            }
            else
            {
                CcspTraceWarning(("%s::Invalid Object pDmlVoiceService\n", __FUNCTION__));
                TelcoVoiceMgrDmlGetDataRelease(pTelcoVoiceMgrDmlData);
            }
        }
    }

    return ret;
}

/**********************************************************************

    caller:     owner of this object

    prototype:

        BOOL SIP_GetParamBoolValue(ANSC_HANDLE hInsContext, char* ParamName, char* pValue, ULONG* pUlSize);

    description:

        This function is called to retrieve String parameter value;

    argument:   ANSC_HANDLE                 hInsContext,
                The instance handle;

                char*                       ParamName,
                The parameter name;

                char*                       pValue,
                The buffer of returned ULONG value;

                ULONG*                      pUlSize
                The length of returned buffer value;

    return:     TRUE if succeeded.

**********************************************************************/
BOOL SIP_GetParamBoolValue(ANSC_HANDLE hInsContext, char* ParamName, BOOL* pBool)
{
    DML_PROFILE_CTRL_T* pTelcoVoiceMgrCtrl = (DML_PROFILE_CTRL_T*) hInsContext;
    BOOL ret = FALSE;

    if(pTelcoVoiceMgrCtrl != NULL)
    {
        TELCOVOICEMGR_DML_DATA* pTelcoVoiceMgrDmlData = TelcoVoiceMgrDmlGetDataLocked();
        if(pTelcoVoiceMgrDmlData != NULL)
        {
            TELCOVOICEMGR_DML_VOICEPROFILE* pVoiceProfile = &(pTelcoVoiceMgrCtrl->dml);

            if (!pVoiceProfile || !pBool)
            {
                CcspTraceError(("%s: NULL Pointer\n", __FUNCTION__));
                TelcoVoiceMgrDmlGetDataRelease(pTelcoVoiceMgrDmlData);
                return ret;
            }

            if (strcmp(ParamName, "X_RDK-Central_COM_NetworkDisconnect") == 0)
            {
               * pBool = pVoiceProfile->SIPObj.NetworkDisconnect;
               ret = TRUE;
            }
            else if (strcmp(ParamName, "X_RDK_PRACKRequired") == 0)
            {
               * pBool = pVoiceProfile->SIPObj.X_RDK_PRACKRequired;
               ret = TRUE;
            }
            else if (strcmp(ParamName, "UseCodecPriorityInSDPResponse") == 0)
            {
               * pBool = pVoiceProfile->SIPObj.UseCodecPriorityInSDPResponse;
               ret = TRUE;
            }
            else
            {
                CcspTraceWarning(("%s::Unknown ParamName :%s\n", __FUNCTION__, ParamName));
            }
            TelcoVoiceMgrDmlGetDataRelease(pTelcoVoiceMgrDmlData);
        }   
    }

    return ret;
}

/**********************************************************************

    caller:     owner of this object

    prototype:

        BOOL SIP_SetParamStringValue(ANSC_HANDLE hInsContext, char* ParamName, char* pString);

    description:

        This function is called to set String parameter value;

    argument:   ANSC_HANDLE                 hInsContext,
                The instance handle;

                char*                       ParamName,
                The parameter name;

                char*                       pValue,
                The buffer to set value;

    return:     TRUE if succeeded.

**********************************************************************/
BOOL SIP_SetParamBoolValue(ANSC_HANDLE hInsContext, char* ParamName, BOOL bValue)
{
    DML_PROFILE_CTRL_T* pTelcoVoiceMgrCtrl = (DML_PROFILE_CTRL_T*) hInsContext;
    PTELCOVOICEMGR_DML_VOICESERVICE pDmlVoiceService = NULL;
    BOOL ret = FALSE;
    ULONG uVsIndex = 0;
    ULONG uVpIndex = 0;

    if(pTelcoVoiceMgrCtrl != NULL)
    {
        TELCOVOICEMGR_DML_DATA* pTelcoVoiceMgrDmlData = TelcoVoiceMgrDmlGetDataLocked();
        if(pTelcoVoiceMgrDmlData != NULL)
        {
            TELCOVOICEMGR_DML_VOICEPROFILE* pVoiceProfile = &(pTelcoVoiceMgrCtrl->dml);

            if (!pVoiceProfile)
            {
                CcspTraceError(("%s: NULL Pointer\n", __FUNCTION__));
                TelcoVoiceMgrDmlGetDataRelease(pTelcoVoiceMgrDmlData);
                return ret;
            }
            pDmlVoiceService = pVoiceProfile->pParentVoiceService;
            if(pDmlVoiceService)
            {
                uVsIndex = pDmlVoiceService->InstanceNumber;
                uVpIndex = pVoiceProfile->InstanceNumber;
                TelcoVoiceMgrDmlGetDataRelease(pTelcoVoiceMgrDmlData);
                if (strcmp(ParamName, "X_RDK-Central_COM_NetworkDisconnect") == 0)
                {
                    if(TelcoVoiceMgrDmlSetNetworkDisconnect(uVsIndex,uVpIndex, bValue) == ANSC_STATUS_SUCCESS)
                    {
                        TELCOVOICEMGR_DML_DATA* pTelcoVoiceMgrDmlData = TelcoVoiceMgrDmlGetDataLocked();
                        if(pTelcoVoiceMgrDmlData != NULL)
                        {
                            pVoiceProfile->SIPObj.NetworkDisconnect  =  bValue;
                            TelcoVoiceMgrDmlGetDataRelease(pTelcoVoiceMgrDmlData);
                            return TRUE;
                        }
                    }
                }
                else if (strcmp(ParamName, "X_RDK_PRACKRequired") == 0)
                {
                    if(TelcoVoiceMgrDmlSetPrackRequired(uVsIndex,uVpIndex, bValue) == ANSC_STATUS_SUCCESS)
                    {
                        TELCOVOICEMGR_DML_DATA* pTelcoVoiceMgrDmlData = TelcoVoiceMgrDmlGetDataLocked();
                        if(pTelcoVoiceMgrDmlData != NULL)
                        {
                            pVoiceProfile->SIPObj.X_RDK_PRACKRequired  =  bValue;
                            TelcoVoiceMgrDmlGetDataRelease(pTelcoVoiceMgrDmlData);
                            return TRUE;
                        }
                    }
                }
                else
                {
                    CcspTraceWarning(("%s::Unknown ParamName :%s\n", __FUNCTION__, ParamName));
                }
            }
            else
            {
                TelcoVoiceMgrDmlGetDataRelease(pTelcoVoiceMgrDmlData);
            }
        }
    }

    return ret;
}

/**********************************************************************

    caller:     owner of this object

    prototype:

        BOOL RTP_GetParamUlongValue(ANSC_HANDLE hInsContext, char* ParamName, ULONG* pValue);

    description:

        This function is called to retrieve Ulong parameter value;

    argument:   ANSC_HANDLE                 hInsContext,
                The instance handle;

                char*                       ParamName,
                The parameter name;

                ULONG*                      pValue
                The value returned

    return:     TRUE if succeeded.

**********************************************************************/
BOOL RTP_GetParamUlongValue(ANSC_HANDLE hInsContext, char* ParamName, ULONG* pValue)
{
    DML_PROFILE_CTRL_T* pTelcoVoiceMgrCtrl = (DML_PROFILE_CTRL_T*) hInsContext;
    BOOL ret = FALSE;

    if(pTelcoVoiceMgrCtrl != NULL)
    {
        TELCOVOICEMGR_DML_DATA* pTelcoVoiceMgrDmlData = TelcoVoiceMgrDmlGetDataLocked();
        if(pTelcoVoiceMgrDmlData != NULL)
        {
            TELCOVOICEMGR_DML_VOICEPROFILE* pVoiceProfile = &(pTelcoVoiceMgrCtrl->dml);

            if (!pVoiceProfile || !pValue)
            {
                CcspTraceError(("%s: NULL Pointer\n", __FUNCTION__));
                TelcoVoiceMgrDmlGetDataRelease(pTelcoVoiceMgrDmlData);
                return ret;
            }

            if (strcmp(ParamName, "DSCPMark") == 0)
            {
               *pValue = pVoiceProfile->RTPObj.DSCPMark;
               ret = TRUE;
            }
            else if (strcmp(ParamName, "X_RDK_SKBMark") == 0)
            {
               *pValue = pVoiceProfile->RTPObj.X_RDK_SKBMark;
               ret = TRUE;
            }
            else if (strcmp(ParamName, "LocalPortMin") == 0)
            {
               *pValue = pVoiceProfile->RTPObj.LocalPortMin;
               ret = TRUE;
            }
            else if (strcmp(ParamName, "LocalPortMax") == 0)
            {
               *pValue = pVoiceProfile->RTPObj.LocalPortMax;
               ret = TRUE;
            }
            else if (strcmp(ParamName, "TelephoneEventPayloadType") == 0)
            {
               *pValue = pVoiceProfile->RTPObj.TelephoneEventPayloadType;
               ret = TRUE;
            }
            else
            {
                CcspTraceWarning(("%s::Unknown ParamName :%s\n", __FUNCTION__, ParamName));
            }
            TelcoVoiceMgrDmlGetDataRelease(pTelcoVoiceMgrDmlData);
        }
    }

    return ret;
}

/**********************************************************************

    caller:     owner of this object

    prototype:

        BOOL RTP_SetParamUlongValue(ANSC_HANDLE hInsContext, char* ParamName, ULONG uValue);

    description:

        This function is called to set Ulong parameter value;

    argument:   ANSC_HANDLE                 hInsContext,
                The instance handle;

                char*                       ParamName,
                The parameter name;

                ULONG                       uValue
                The value need to set

    return:     TRUE if succeeded.

**********************************************************************/
BOOL RTP_SetParamUlongValue(ANSC_HANDLE hInsContext, char* ParamName, ULONG uValue)
{
    DML_PROFILE_CTRL_T* pTelcoVoiceMgrCtrl = (DML_PROFILE_CTRL_T*) hInsContext;
    PTELCOVOICEMGR_DML_VOICESERVICE pDmlVoiceService = NULL;
    BOOL ret = FALSE;
    ULONG uVsIndex = 0;
    ULONG uVpIndex = 0;

    if(pTelcoVoiceMgrCtrl != NULL)
    {
        TELCOVOICEMGR_DML_DATA* pTelcoVoiceMgrDmlData = TelcoVoiceMgrDmlGetDataLocked();
        if(pTelcoVoiceMgrDmlData != NULL)
        {
            TELCOVOICEMGR_DML_VOICEPROFILE* pVoiceProfile = &(pTelcoVoiceMgrCtrl->dml);

            if (!pVoiceProfile)
            {
                CcspTraceError(("%s: NULL Pointer\n", __FUNCTION__));
                TelcoVoiceMgrDmlGetDataRelease(pTelcoVoiceMgrDmlData);
                ret = FALSE;
            }
            else
            {
                pDmlVoiceService = pVoiceProfile->pParentVoiceService;
                TelcoVoiceMgrDmlGetDataRelease(pTelcoVoiceMgrDmlData);
                if (strcmp(ParamName, "DSCPMark") == 0)
                {
                    if(TelcoVoiceMgrDmlSetRtpDscpMark(uVsIndex, uVpIndex, uValue) == ANSC_STATUS_SUCCESS)
                    {
                        TELCOVOICEMGR_DML_DATA* pTelcoVoiceMgrDmlData = TelcoVoiceMgrDmlGetDataLocked();
                        if(pTelcoVoiceMgrDmlData != NULL)
                        {
                            pVoiceProfile->RTPObj.DSCPMark  =  uValue;
                            TelcoVoiceMgrDmlGetDataRelease(pTelcoVoiceMgrDmlData);
                            ret = TRUE;
                        }
                    }
                }
                else
                {
                    CcspTraceWarning(("%s::Unknown ParamName :%s\n", __FUNCTION__, ParamName));
                }
            }
        }
    }

    return ret;
}

/**********************************************************************

    caller:     owner of this object

    prototype:

        BOOL RTP_GetParamIntValue(ANSC_HANDLE hInsContext, char* ParamName, int* pInt);

    description:

        This function is called to retrieve int parameter value;

    argument:   ANSC_HANDLE                 hInsContext,
                The instance handle;

                char*                       ParamName,
                The parameter name;

                int*                        pInt
                The value returned

    return:     TRUE if succeeded.

**********************************************************************/
BOOL RTP_GetParamIntValue(ANSC_HANDLE hInsContext, char* ParamName, int* pInt)
{
    BOOL ret = FALSE;
    DML_PROFILE_CTRL_T* pTelcoVoiceMgrCtrl = (DML_PROFILE_CTRL_T*) hInsContext;
    if(pTelcoVoiceMgrCtrl != NULL)
    {
        TELCOVOICEMGR_DML_DATA* pTelcoVoiceMgrDmlData = TelcoVoiceMgrDmlGetDataLocked();
        if(pTelcoVoiceMgrDmlData != NULL)
        {
            TELCOVOICEMGR_DML_VOICEPROFILE* pVoiceProfile = &(pTelcoVoiceMgrCtrl->dml);

            if (!pVoiceProfile || !pInt)
            {
                CcspTraceError(("%s: NULL Pointer\n", __FUNCTION__));
                TelcoVoiceMgrDmlGetDataRelease(pTelcoVoiceMgrDmlData);
                return ret;
            }

            if (strcmp(ParamName, "EthernetPriorityMark") == 0)
            {
               * pInt = pVoiceProfile->RTPObj.EthernetPriorityMark;
               ret = TRUE;
            }
            else if (strcmp(ParamName, "VLANIDMark") == 0)
            {
               * pInt = pVoiceProfile->RTPObj.VLANIDMark;
               ret = TRUE;
            }
            else
            {
                CcspTraceWarning(("%s::Unknown ParamName :%s\n", __FUNCTION__, ParamName));
            }
            TelcoVoiceMgrDmlGetDataRelease(pTelcoVoiceMgrDmlData);
        }
    }

    return ret;
}

/**********************************************************************

    caller:     owner of this object

    prototype:

        BOOL RTP_SetParamIntValue(ANSC_HANDLE hInsContext, char* ParamName, int iValue);

    description:

        This function is called to set Ulong parameter value;

    argument:   ANSC_HANDLE                 hInsContext,
                The instance handle;

                char*                       ParamName,
                The parameter name;

                int                         iValue
                The value need to set

    return:     TRUE if succeeded.

**********************************************************************/
BOOL RTP_SetParamIntValue(ANSC_HANDLE hInsContext, char* ParamName, int iValue)
{

    DML_PROFILE_CTRL_T* pTelcoVoiceMgrCtrl = (DML_PROFILE_CTRL_T*) hInsContext;
    PTELCOVOICEMGR_DML_VOICESERVICE pDmlVoiceService = NULL;
    BOOL ret = FALSE;
    ULONG uVsIndex = 0;
    ULONG uVpIndex = 0;

    if(pTelcoVoiceMgrCtrl != NULL)
    {
        TELCOVOICEMGR_DML_DATA* pTelcoVoiceMgrDmlData = TelcoVoiceMgrDmlGetDataLocked();
        if(pTelcoVoiceMgrDmlData != NULL)
        {
            TELCOVOICEMGR_DML_VOICEPROFILE* pVoiceProfile = &(pTelcoVoiceMgrCtrl->dml);

            if (!pVoiceProfile)
            {
                CcspTraceError(("%s: NULL Pointer\n", __FUNCTION__));
                TelcoVoiceMgrDmlGetDataRelease(pTelcoVoiceMgrDmlData);
            }
            else
            {
                pDmlVoiceService = pVoiceProfile->pParentVoiceService;
                uVsIndex = pDmlVoiceService->InstanceNumber;
                uVpIndex = pVoiceProfile->InstanceNumber;
                TelcoVoiceMgrDmlGetDataRelease(pTelcoVoiceMgrDmlData);
                if (strcmp(ParamName, "EthernetPriorityMark") == 0)
                {
                    if(TelcoVoiceMgrDmlSetRtpEthernetPriorityMark(uVsIndex,uVpIndex, iValue) == ANSC_STATUS_SUCCESS)
                    {
                        TELCOVOICEMGR_DML_DATA* pTelcoVoiceMgrDmlData = TelcoVoiceMgrDmlGetDataLocked();
                        if(pTelcoVoiceMgrDmlData != NULL)
                        {
                            pVoiceProfile->RTPObj.EthernetPriorityMark  =  iValue;
                            TelcoVoiceMgrDmlGetDataRelease(pTelcoVoiceMgrDmlData);
                            ret = TRUE;
                        }
                    }
                }
            }
        }
    }

    return ret;
}

/**********************************************************************

    caller:     owner of this object

    prototype:
        BOOL Redundancy_GetParamUlongValue (ANSC_HANDLE hInsContext, char* ParamName, ULONG* pValue);

    description:

        This function is called to retrieve Ulong parameter value;

    argument:   ANSC_HANDLE                 hInsContext,

                    The instance handle;

                    char*                       ParamName,
                    The parameter name;

                    ULONG*                      pValue
                    The value returned

        return:     TRUE if succeeded.

**********************************************************************/

BOOL Redundancy_GetParamUlongValue(ANSC_HANDLE hInsContext, char* ParamName, ULONG* pValue)
{
    BOOL ret = FALSE;
    DML_PROFILE_CTRL_T* pTelcoVoiceMgrCtrl = (DML_PROFILE_CTRL_T*) hInsContext;
    if(pTelcoVoiceMgrCtrl != NULL)
    {
        TELCOVOICEMGR_DML_DATA* pTelcoVoiceMgrDmlData = TelcoVoiceMgrDmlGetDataLocked();
        if(pTelcoVoiceMgrDmlData != NULL)
        {
            TELCOVOICEMGR_DML_VOICEPROFILE* pVoiceProfile = &(pTelcoVoiceMgrCtrl->dml);

            if (!pVoiceProfile || !pValue)
            {
                CcspTraceError(("%s: NULL Pointer\n", __FUNCTION__));
                TelcoVoiceMgrDmlGetDataRelease(pTelcoVoiceMgrDmlData);
                return ret;
            }

            if (strcmp(ParamName, "BlockPayloadType") == 0)
            {
                *pValue = pVoiceProfile->RTPObj.RedundancyObj.BlockPayloadType;
                ret = TRUE;
            }
            else if (strcmp(ParamName, "PayloadType") == 0)
            {
                *pValue = pVoiceProfile->RTPObj.RedundancyObj.PayloadType;
                ret = TRUE;
            }
            else if (strcmp(ParamName, "MaxSessionsUsingRedundancy") == 0)
            {
                *pValue = pVoiceProfile->RTPObj.RedundancyObj.MaxSessionsUsingRedundancy;
                ret = TRUE;
            }
            else
            {
                CcspTraceWarning(("%s::Unknown ParamName :%s\n", __FUNCTION__, ParamName));
            }
        }
        TelcoVoiceMgrDmlGetDataRelease(pTelcoVoiceMgrDmlData);
    }
    return ret;
}

/**********************************************************************

    caller:     owner of this object

    prototype:

        BOOL Redundancy_SetParamUlongValue(ANSC_HANDLE hInsContext, char* ParamName, ULONG uValue);

    description:

        This function is called to set Ulong parameter value;

    argument:   ANSC_HANDLE                 hInsContext,
                The instance handle;

                char*                       ParamName,
                The parameter name;

                ULONG                       uValue
                The value need to set

    return:     TRUE if succeeded.

**********************************************************************/
BOOL Redundancy_SetParamUlongValue(ANSC_HANDLE hInsContext, char* ParamName, ULONG uValue)
{
    BOOL ret = FALSE;

    if (strcmp(ParamName, "PayloadType") == 0)
    {
        ret = TRUE;
    }
    else if (strcmp(ParamName, "MaxSessionsUsingRedundancy") == 0)
    {
        ret = TRUE;
    }
    return ret;
}



/**********************************************************************

    caller:     owner of this object

    prototype:

        BOOL Redundancy_SetParamIntValue(ANSC_HANDLE hInsContext, char* ParamName, int iValue);

    description:

        This function is called to set Ulong parameter value;

    argument:   ANSC_HANDLE                 hInsContext,
                The instance handle;

                char*                       ParamName,
                The parameter name;

                int                         iValue
                The value need to set

    return:     TRUE if succeeded.

**********************************************************************/
BOOL Redundancy_SetParamIntValue(ANSC_HANDLE hInsContext, char* ParamName, int iValue)
{
    BOOL ret = FALSE;
    if (strcmp(ParamName, "FaxAndModemRedundancy") == 0)
    {
        ret = FALSE;
    }
    else if (strcmp(ParamName, "ModemRedundancy") == 0)
    {
        ret = FALSE;
    }
    else if (strcmp(ParamName, "DTMFRedundancy") == 0)
    {
        ret = FALSE;
    }
    else if (strcmp(ParamName, "VoiceRedundancy") == 0)
    {
        ret = FALSE;
    }
    return ret;
}


/**********************************************************************

    caller:     owner of this object

    prototype:

        BOOL Redundancy_SetParamBoolValue(ANSC_HANDLE hInsContext, char* ParamName, char* pString);

    description:

        This function is called to set String parameter value;

    argument:   ANSC_HANDLE                 hInsContext,
                The instance handle;

                char*                       ParamName,
                The parameter name;

                char*                       pValue,
                The buffer to set value;

    return:     TRUE if succeeded.

**********************************************************************/
BOOL Redundancy_SetParamBoolValue(ANSC_HANDLE hInsContext, char* ParamName, BOOL bValue)
{
    BOOL ret = FALSE;
    if (strcmp(ParamName, "X_RDK-Central_COM_NetworkDisconnect") == 0)
    {
        ret = FALSE;
    }
    else if (strcmp(ParamName, "X_RDK-Central_COM_NetworkDisconnect") == 0)
    {
            ret = FALSE;
    }
    return ret;
}

/**********************************************************************

    caller:     owner of this object

    prototype:

        BOOL  Redundancy_GetParamIntValue(ANSC_HANDLE hInsContext, char* ParamName, int* pInt)

    description:

        This function is called to retrieve int parameter value;

    argument:   ANSC_HANDLE                 hInsContext,
                The instance handle;

                char*                       ParamName,
                The parameter name;

                int*                        pInt
                The value returned

    return:     TRUE if succeeded.

**********************************************************************/
BOOL Redundancy_GetParamIntValue(ANSC_HANDLE hInsContext, char* ParamName, int* pInt)
{
    BOOL ret = FALSE;
    DML_PROFILE_CTRL_T* pTelcoVoiceMgrCtrl = (DML_PROFILE_CTRL_T*) hInsContext;
    if(pTelcoVoiceMgrCtrl != NULL)
    {
        TELCOVOICEMGR_DML_DATA* pTelcoVoiceMgrDmlData = TelcoVoiceMgrDmlGetDataLocked();
        if(pTelcoVoiceMgrDmlData != NULL)
        {
            TELCOVOICEMGR_DML_VOICEPROFILE* pVoiceProfile = &(pTelcoVoiceMgrCtrl->dml);

            if (!pVoiceProfile || !pInt)
            {
                CcspTraceError(("%s: NULL Pointer\n", __FUNCTION__));
                TelcoVoiceMgrDmlGetDataRelease(pTelcoVoiceMgrDmlData);
                return ret;
            }
            if (strcmp(ParamName, "ModemRedundancy") == 0)
            {
                *pInt = pVoiceProfile->RTPObj.RedundancyObj.ModemRedundancy;
                ret = TRUE;
            }
            else if (strcmp(ParamName, "FaxAndModemRedundancy") == 0)
            {
                *pInt = pVoiceProfile->RTPObj.RedundancyObj.FaxAndModemRedundancy;
                ret = TRUE;
            }
            else if (strcmp(ParamName, "DTMFRedundancy") == 0)
            {
                *pInt = pVoiceProfile->RTPObj.RedundancyObj.DTMFRedundancy;
                ret = TRUE;
            }
            else if (strcmp(ParamName, "VoiceRedundancy") == 0)
            {
                *pInt = pVoiceProfile->RTPObj.RedundancyObj.VoiceRedundancy;
                ret = TRUE;
            }
            else
            {
                CcspTraceWarning(("%s::Unknown ParamName :%s\n", __FUNCTION__, ParamName));
            }
            TelcoVoiceMgrDmlGetDataRelease(pTelcoVoiceMgrDmlData);
        }
    }
    return ret;
}

/**********************************************************************

    caller:     owner of this object

    prototype:

    BOOL Redundancy_GetParamBoolValue(ANSC_HANDLE hInsContext, char* ParamName, BOOL* pBool);

    description:
        This function is called to retrieve BOOL parameter value;

    argument:   ANSC_HANDLE                 hInsContext,
            The instance handle;

            char*                       ParamName,
            The parameter name;

            BOOL*                      pBool
            The buffer of returned pBool;

    return:     TRUE if succeeded.

**********************************************************************/
BOOL Redundancy_GetParamBoolValue(ANSC_HANDLE hInsContext, char* ParamName, BOOL* pBool)
{
    BOOL ret = FALSE;
    DML_PROFILE_CTRL_T* pTelcoVoiceMgrCtrl = (DML_PROFILE_CTRL_T*) hInsContext;
    if(pTelcoVoiceMgrCtrl != NULL)
    {
        TELCOVOICEMGR_DML_DATA* pTelcoVoiceMgrDmlData = TelcoVoiceMgrDmlGetDataLocked();
        if(pTelcoVoiceMgrDmlData != NULL)
        {
            TELCOVOICEMGR_DML_VOICEPROFILE* pVoiceProfile = &(pTelcoVoiceMgrCtrl->dml);

            if (!pVoiceProfile || !pBool)
            {
                CcspTraceError(("%s: NULL Pointer\n", __FUNCTION__));
                TelcoVoiceMgrDmlGetDataRelease(pTelcoVoiceMgrDmlData);
                return ret;
            }
            if (strcmp(ParamName, "Enable") == 0)
            {
                *pBool = pVoiceProfile->RTPObj.RedundancyObj.Enable;
                ret = TRUE;
            }
            else
            {
                CcspTraceWarning(("%s::Unknown ParamName :%s\n", __FUNCTION__, ParamName));
            }
            TelcoVoiceMgrDmlGetDataRelease(pTelcoVoiceMgrDmlData);
        }
    }
    return ret;
}


/**********************************************************************

    caller:     owner of this object

    prototype:
        BOOL RTCP_GetParamUlongValue(ANSC_HANDLE hInsContext, char* ParamName, ULONG* pValue);

    description:

        This function is called to retrieve Ulong parameter value;

    argument:   ANSC_HANDLE                 hInsContext,
                The instance handle;

                char*                       ParamName,
                The parameter name;

                ULONG*                      pValue
                The value returned

    return:     TRUE if succeeded.

**********************************************************************/
BOOL RTCP_GetParamUlongValue(ANSC_HANDLE hInsContext, char* ParamName, ULONG* pValue)
{
    BOOL ret = FALSE;
    DML_PROFILE_CTRL_T* pTelcoVoiceMgrCtrl = (DML_PROFILE_CTRL_T*) hInsContext;
    if(pTelcoVoiceMgrCtrl != NULL)
    {
        TELCOVOICEMGR_DML_DATA* pTelcoVoiceMgrDmlData = TelcoVoiceMgrDmlGetDataLocked();
        if(pTelcoVoiceMgrDmlData != NULL)
        {
            TELCOVOICEMGR_DML_VOICEPROFILE* pVoiceProfile = &(pTelcoVoiceMgrCtrl->dml);

            if (!pVoiceProfile || !pValue)
            {
                CcspTraceError(("%s: NULL Pointer\n", __FUNCTION__));
                TelcoVoiceMgrDmlGetDataRelease(pTelcoVoiceMgrDmlData);
                return ret;
            }
            if (strcmp(ParamName, "TxRepeatInterval") == 0)
            {
                *pValue =  pVoiceProfile->RTPObj.RTCPObj.TxRepeatInterval;
                ret = TRUE;
            }
            else
            {
                CcspTraceWarning(("%s::Unknown ParamName :%s\n", __FUNCTION__, ParamName));
            }
            TelcoVoiceMgrDmlGetDataRelease(pTelcoVoiceMgrDmlData);
        }
    }
    return ret;
}


/**********************************************************************

    caller:     owner of this object

    prototype:

        LONG RTCP_GetParamStringValue(ANSC_HANDLE hInsContext, char* ParamName, char* pValue, ULONG* pUlSize);

    description:

        This function is called to retrieve String parameter value;

    argument:   ANSC_HANDLE                 hInsContext,
                The instance handle;

                char*                       ParamName
                The parameter name;

                char*                       pValue,
                The buffer of returned ULONG value;

                ULONG*                      pUlSize
                The length of returned buffer value;

    return:     0 if succeeded.
                1 if not enough buffer size
                -1 if not supported

**********************************************************************/

LONG RTCP_GetParamStringValue(ANSC_HANDLE hInsContext, char* ParamName, char* pValue, ULONG* pUlSize)
{
    ULONG ret = 1;
    DML_PROFILE_CTRL_T* pTelcoVoiceMgrCtrl = (DML_PROFILE_CTRL_T*) hInsContext;
    if(pTelcoVoiceMgrCtrl != NULL)
    {
        TELCOVOICEMGR_DML_DATA* pTelcoVoiceMgrDmlData = TelcoVoiceMgrDmlGetDataLocked();
        if(pTelcoVoiceMgrDmlData != NULL)
        {
            TELCOVOICEMGR_DML_VOICEPROFILE* pVoiceProfile = &(pTelcoVoiceMgrCtrl->dml);

            if (!pVoiceProfile || !pValue)
            {
                CcspTraceError(("%s: NULL Pointer\n", __FUNCTION__));
                return 1;
            }

            if (strcmp(ParamName, "LocalCName") == 0)
            {
                AnscCopyString(pValue,pVoiceProfile->RTPObj.RTCPObj.LocalCName);
                ret = 0;
            }
            else
            {
                CcspTraceWarning(("%s::Unknown ParamName :%s\n", __FUNCTION__, ParamName));
            }
            TelcoVoiceMgrDmlGetDataRelease(pTelcoVoiceMgrDmlData);
        }
    }
    return ret;
}

/**********************************************************************

    caller:     owner of this object

    prototype:

        BOOL RTCP_SetParamUlongValue(ANSC_HANDLE hInsContext, char* ParamName, ULONG uValue);

    description:

        This function is called to set Ulong parameter value;

    argument:   ANSC_HANDLE                 hInsContext,
                The instance handle;

                char*                       ParamName,
                The parameter name;

                ULONG                       uValue
                The value need to set

    return:     TRUE if succeeded.

**********************************************************************/
BOOL RTCP_SetParamUlongValue(ANSC_HANDLE hInsContext, char* ParamName, ULONG uValue)
{
    BOOL ret = FALSE;
    if (strcmp(ParamName, "TxRepeatInterval") == 0)
    {
        ret = TRUE;
    }
    return ret;
}

/**********************************************************************

        caller:     owner of this object

        prototype:

    BOOL RTCP_GetParamBoolValue(ANSC_HANDLE hInsContext, char* ParamName, BOOL* pBool);

description:
    This function is called to retrieve ULONG parameter value;

argument:   ANSC_HANDLE                 hInsContext,
            The instance handle;

            char*                       ParamName,
            The parameter name;

            BOOL*                      pBool
            The buffer of returned pBool;

return:     TRUE if succeeded.

**********************************************************************/
BOOL RTCP_GetParamBoolValue(ANSC_HANDLE hInsContext, char* ParamName, BOOL* pBool)
{
    BOOL ret = FALSE;
    DML_PROFILE_CTRL_T* pTelcoVoiceMgrCtrl = (DML_PROFILE_CTRL_T*) hInsContext;
    if(pTelcoVoiceMgrCtrl != NULL)
    {
        TELCOVOICEMGR_DML_DATA* pTelcoVoiceMgrDmlData = TelcoVoiceMgrDmlGetDataLocked();
        if(pTelcoVoiceMgrDmlData != NULL)
        {
            TELCOVOICEMGR_DML_VOICEPROFILE* pVoiceProfile = &(pTelcoVoiceMgrCtrl->dml);

            if (!pVoiceProfile || !pBool)
            {
                CcspTraceError(("%s: NULL Pointer\n", __FUNCTION__));
                TelcoVoiceMgrDmlGetDataRelease(pTelcoVoiceMgrDmlData);
                return ret;
            }
            if (strcmp(ParamName, "Enable") == 0)
            {
                *pBool = pVoiceProfile->RTPObj.RTCPObj.Enable;
                ret = TRUE;
            }
            else
            {
                CcspTraceWarning(("%s::Unknown ParamName :%s\n", __FUNCTION__, ParamName));
            }
            TelcoVoiceMgrDmlGetDataRelease(pTelcoVoiceMgrDmlData);
        }
    }
    return ret;
}

/**********************************************************************

    caller:     owner of this object

    prototype:

        BOOL RTCP_SetParamStringValue(ANSC_HANDLE hInsContext, char* ParamName, char* pString);

    description:

        This function is called to set String parameter value;

    argument:   ANSC_HANDLE                 hInsContext,
                The instance handle;

                char*                       ParamName,
                The parameter name;

                char*                       pValue,
                The buffer to set value;

    return:     TRUE if succeeded.

**********************************************************************/
BOOL RTCP_SetParamStringValue(ANSC_HANDLE hInsContext, char* ParamName, char* pString)
{
    BOOL ret = FALSE;
    if (strcmp(ParamName, "LocalCName") == 0)
    {
        ret = TRUE;
    }
    return ret;
}

/**********************************************************************

    caller:     owner of this object

    prototype:

        BOOL RTCP_SetParamBoolValue(ANSC_HANDLE hInsContext, char* ParamName, char* pString);

    description:

        This function is called to set String parameter value;

    argument:   ANSC_HANDLE                 hInsContext,
                The instance handle;

                char*                       ParamName,
                The parameter name;

                char*                       pValue,
                The buffer to set value;

    return:     TRUE if succeeded.

**********************************************************************/
BOOL RTCP_SetParamBoolValue(ANSC_HANDLE hInsContext, char* ParamName, BOOL bValue)
{
    BOOL ret = FALSE;
    if (strcmp(ParamName, "Enable") == 0)
    {
        ret = TRUE;
    }
    return ret;
}

/**********************************************************************

    caller:     owner of this object

    prototype:

        LONG RTP_GetParamStringValue(ANSC_HANDLE hInsContext, char* ParamName, char* pValue, ULONG* pUlSize);

    description:

        This function is called to retrieve String parameter value;

    argument:   ANSC_HANDLE                 hInsContext,
                The instance handle;

                char*                       ParamName,
                The parameter name;

                char*                       pValue,
                The buffer of returned ULONG value;

                ULONG*                      pUlSize
                The length of returned buffer value;

    return:     0  if succeeded.
                1  if short of buufer
                -1 if not supported

**********************************************************************/

LONG RTP_GetParamStringValue(ANSC_HANDLE hInsContext, char* ParamName, char* pValue, ULONG* pUlSize)
{
    return TRUE;
}

/**********************************************************************

    caller:     owner of this object

    prototype:

        BOOL SIPEventSubscribe_SetParamStringValue(ANSC_HANDLE hInsContext, char* ParamName, char* pString);

    description:

        This function is called to set String parameter value;

    argument:   ANSC_HANDLE                 hInsContext,
                The instance handle;

                char*                       ParamName,
                The parameter name;

                char*                       pValue,
                The buffer to set value;

    return:     TRUE if succeeded.

**********************************************************************/
BOOL SIPEventSubscribe_SetParamStringValue(ANSC_HANDLE hInsContext, char* ParamName, char* pString)
{
    BOOL ret = FALSE;
    DML_SIP_EVENTSUBSCRIBE_CTRL_T* pSIPEvtSubscribe = (DML_SIP_EVENTSUBSCRIBE_CTRL_T *) hInsContext;
    if(pSIPEvtSubscribe == NULL)
    {
        CcspTraceError(("%s:%d:: Invalid object \n", __FUNCTION__, __LINE__));
        return ret;
    }

    TELCOVOICEMGR_DML_DATA* pTelcoVoiceMgrDmlData = TelcoVoiceMgrDmlGetDataLocked();
    if(pTelcoVoiceMgrDmlData == NULL)
    {
        CcspTraceError(("%s:%d:: TelcoVoiceMgrDmlGetDataLocked: Failed\n", __FUNCTION__, __LINE__));
        return ret;
    }

    PTELCOVOICEMGR_DML_SIP_EVENTSUBSCRIBE pDmlSIPEvtSubscribe = &(pSIPEvtSubscribe->dml);
    if(pDmlSIPEvtSubscribe == NULL )
    {
        TelcoVoiceMgrDmlGetDataRelease(pTelcoVoiceMgrDmlData);
        CcspTraceError(("%s:%d:: pDmlSIPEvtSubscribe: NULL\n", __FUNCTION__, __LINE__));
        return ret;
    }

    if (strcmp(ParamName, "Alias") == 0)
    {
        ret = TRUE;
    }
    else if (strcmp(ParamName, "Event") == 0)
    {
        ret = TRUE;
    }
    else if (strcmp(ParamName, "Notifier") == 0)
    {
        ret = TRUE;
    }
    else if (strcmp(ParamName, "NotifierTransport") == 0)
    {
        ret = TRUE;
    }
    else
    {
        CcspTraceWarning(("%s::Unknown ParamName :%s\n", __FUNCTION__, ParamName));
    }
    
    TelcoVoiceMgrDmlGetDataRelease(pTelcoVoiceMgrDmlData);
    return ret;
}

/**********************************************************************

        caller:     owner of this object

        prototype:

    BOOL SRTP_GetParamBoolValue(ANSC_HANDLE hInsContext, char* ParamName, BOOL* pBool);

description:
    This function is called to retrieve ULONG parameter value;

argument:   ANSC_HANDLE                 hInsContext,
            The instance handle;

            char*                       ParamName,
            The parameter name;

            BOOL*                      pBool
            The buffer of returned pBool;

return:     TRUE if succeeded.

**********************************************************************/
BOOL SRTP_GetParamBoolValue(ANSC_HANDLE hInsContext, char* ParamName, BOOL* pBool)
{
    BOOL ret = FALSE;
    DML_PROFILE_CTRL_T* pTelcoVoiceMgrCtrl = (DML_PROFILE_CTRL_T*) hInsContext;
    if(pTelcoVoiceMgrCtrl != NULL)
    {
        TELCOVOICEMGR_DML_DATA* pTelcoVoiceMgrDmlData = TelcoVoiceMgrDmlGetDataLocked();
        if(pTelcoVoiceMgrDmlData != NULL)
        {
            TELCOVOICEMGR_DML_VOICEPROFILE* pDmlVoiceProfile = &(pTelcoVoiceMgrCtrl->dml);

            if (!pDmlVoiceProfile || !pBool)
            {
                CcspTraceError(("%s: NULL Pointer\n", __FUNCTION__));
                TelcoVoiceMgrDmlGetDataRelease(pTelcoVoiceMgrDmlData);
                return FALSE;
            }

            PTELCOVOICEMGR_DML_RTP_SRTP pDmlRtpSRTP = &(pDmlVoiceProfile->RTPObj.SRTPObj);

            if (strcmp(ParamName, "Enable") == 0)
            {
                *pBool = pDmlRtpSRTP->Enable;
                ret = TRUE;
            }
            else
            {
                CcspTraceWarning(("%s::Unknown ParamName :%s\n", __FUNCTION__, ParamName));
            }
            TelcoVoiceMgrDmlGetDataRelease(pTelcoVoiceMgrDmlData);
        }
    }
    return ret;
}


/**********************************************************************

    caller:     owner of this object

    prototype:

        BOOL SRTP_SetParamBoolValue(ANSC_HANDLE hInsContext, char* ParamName, char* pString);

    description:

        This function is called to set String parameter value;

    argument:   ANSC_HANDLE                 hInsContext,
                The instance handle;

                char*                       ParamName,
                The parameter name;

                char*                       pValue,
                The buffer to set value;

    return:     TRUE if succeeded.

**********************************************************************/
BOOL SRTP_SetParamBoolValue(ANSC_HANDLE hInsContext, char* ParamName, BOOL bValue)
{
    BOOL ret = FALSE;
    DML_PROFILE_CTRL_T* pVoiceProfile = (DML_PROFILE_CTRL_T *) hInsContext;
    if(pVoiceProfile == NULL)
    {
        CcspTraceError(("%s:%d:: Invalid object \n", __FUNCTION__, __LINE__));
        return ret;
    }

    TELCOVOICEMGR_DML_DATA* pTelcoVoiceMgrDmlData = TelcoVoiceMgrDmlGetDataLocked();
    if(pTelcoVoiceMgrDmlData == NULL)
    {
        CcspTraceError(("%s:%d:: TelcoVoiceMgrDmlGetDataLocked: Failed\n", __FUNCTION__, __LINE__));
        return ret;
    }

    PTELCOVOICEMGR_DML_PROFILE pDmlVoiceProfile = &(pVoiceProfile->dml);
    if(pDmlVoiceProfile == NULL )
    {
        TelcoVoiceMgrDmlGetDataRelease(pTelcoVoiceMgrDmlData);
        CcspTraceError(("%s:%d:: pDmlVoiceProfile: NULL\n", __FUNCTION__, __LINE__));
        return ret;
    }
    
    PTELCOVOICEMGR_DML_RTP_SRTP pDml_RTP_SRTP = &(pDmlVoiceProfile->RTPObj.SRTPObj);
    if(pDml_RTP_SRTP != NULL)
    {

        if (strcmp(ParamName, "Enable") == 0)
        {
            ret = TRUE;
        }
        else
        {
            CcspTraceWarning(("%s::Unknown ParamName :%s\n", __FUNCTION__, ParamName));
        }
        
    }
    TelcoVoiceMgrDmlGetDataRelease(pTelcoVoiceMgrDmlData);
    return ret;
}

/**********************************************************************

    caller:     owner of this object

    prototype:

        BOOL SRTP_SetParamStringValue(ANSC_HANDLE hInsContext, char* ParamName, char* pString);

    description:

        This function is called to set String parameter value;

    argument:   ANSC_HANDLE                 hInsContext,
                The instance handle;

                char*                       ParamName,
                The parameter name;

                char*                       pValue,
                The buffer to set value;

    return:     TRUE if succeeded.

**********************************************************************/
BOOL SRTP_SetParamStringValue(ANSC_HANDLE hInsContext, char* ParamName, char* pString)
{
    BOOL ret = FALSE;
    DML_PROFILE_CTRL_T* pVoiceProfile = (DML_PROFILE_CTRL_T *) hInsContext;
    if(pVoiceProfile == NULL)
    {
        CcspTraceError(("%s:%d:: Invalid object \n", __FUNCTION__, __LINE__));
        return ret;
    }

    TELCOVOICEMGR_DML_DATA* pTelcoVoiceMgrDmlData = TelcoVoiceMgrDmlGetDataLocked();
    if(pTelcoVoiceMgrDmlData == NULL)
    {
        CcspTraceError(("%s:%d:: TelcoVoiceMgrDmlGetDataLocked: Failed\n", __FUNCTION__, __LINE__));
        return ret;
    }

    PTELCOVOICEMGR_DML_PROFILE pDmlVoiceProfile = &(pVoiceProfile->dml);
    if(pDmlVoiceProfile == NULL )
    {
        TelcoVoiceMgrDmlGetDataRelease(pTelcoVoiceMgrDmlData);
        CcspTraceError(("%s:%d:: pDmlVoiceProfile: NULL\n", __FUNCTION__, __LINE__));
        return ret;
    }
    
    PTELCOVOICEMGR_DML_RTP_SRTP pDml_RTP_SRTP = &(pDmlVoiceProfile->RTPObj.SRTPObj);
    if(pDml_RTP_SRTP != NULL)
    {
        if (strcmp(ParamName, "KeyingMethods") == 0)
        {
            ret = TRUE;
        }
        else if (strcmp(ParamName, "EncryptionKeySizes") == 0)
        {
            ret = TRUE;
        }
        else
        {
           CcspTraceWarning(("%s::Unknown ParamName :%s\n", __FUNCTION__, ParamName)); 
        }
    }
    TelcoVoiceMgrDmlGetDataRelease(pTelcoVoiceMgrDmlData);
    return ret;
}

/**********************************************************************

    caller:     owner of this object

    prototype:

        LONG SRTP_GetParamStringValue(ANSC_HANDLE hInsContext, char* ParamName, char* pValue, ULONG* pUlSize);

    description:

        This function is called to retrieve String parameter value;

    argument:   ANSC_HANDLE                 hInsContext,
                The instance handle;

                char*                       ParamName
                The parameter name;

                char*                       pValue,
                The buffer of returned ULONG value;

                ULONG*                      pUlSize
                The length of returned buffer value;

    return:     0 if succeeded.
                1 if not enough buffer size
                -1 if not supported

**********************************************************************/

LONG SRTP_GetParamStringValue(ANSC_HANDLE hInsContext, char* ParamName, char* pValue, ULONG* pUlSize)
{
    LONG ret = -1;
    DML_PROFILE_CTRL_T* pVoiceProfile = (DML_PROFILE_CTRL_T *) hInsContext;
    if(pVoiceProfile == NULL)
    {
        CcspTraceError(("%s:%d:: Invalid object \n", __FUNCTION__, __LINE__));
        return ret;
    }

    TELCOVOICEMGR_DML_DATA* pTelcoVoiceMgrDmlData = TelcoVoiceMgrDmlGetDataLocked();
    if(pTelcoVoiceMgrDmlData == NULL)
    {
        CcspTraceError(("%s:%d:: TelcoVoiceMgrDmlGetDataLocked: Failed\n", __FUNCTION__, __LINE__));
        return ret;
    }

    PTELCOVOICEMGR_DML_PROFILE pDmlVoiceProfile = &(pVoiceProfile->dml);
    if(pDmlVoiceProfile == NULL )
    {
        TelcoVoiceMgrDmlGetDataRelease(pTelcoVoiceMgrDmlData);
        CcspTraceError(("%s:%d:: pDmlVoiceProfile: NULL\n", __FUNCTION__, __LINE__));
        return ret;
    }
    
    PTELCOVOICEMGR_DML_RTP_SRTP pDml_RTP_SRTP = &(pDmlVoiceProfile->RTPObj.SRTPObj);
    if(pDml_RTP_SRTP != NULL)
    {
        if (strcmp(ParamName, "KeyingMethods") == 0)
        {
            AnscCopyString(pValue,pDml_RTP_SRTP->KeyingMethods);
            ret = 0;
        }
        else if (strcmp(ParamName, "EncryptionKeySizes") == 0)
        {
            AnscCopyString(pValue,pDml_RTP_SRTP->EncryptionKeySizes);
            ret = 0;
        }
        else
        {
            CcspTraceWarning(("%s::Unknown ParamName :%s\n", __FUNCTION__, ParamName));
            ret = -1;
        }
    }
    TelcoVoiceMgrDmlGetDataRelease(pTelcoVoiceMgrDmlData);
    return ret;
}


/**********************************************************************

    caller:     owner of this object

    prototype:
        BOOL H323_GetParamUlongValue(ANSC_HANDLE hInsContext, char* ParamName, ULONG* pValue);

    description:

        This function is called to retrieve Ulong parameter value;

    argument:   ANSC_HANDLE                 hInsContext,
                The instance handle;

                char*                       ParamName,
                The parameter name;

                ULONG*                      pValue
                The value returned

    return:     TRUE if succeeded.

**********************************************************************/
BOOL H323_GetParamUlongValue(ANSC_HANDLE hInsContext, char* ParamName, ULONG* pValue)
{
    BOOL ret = FALSE;
    DML_PROFILE_CTRL_T* pVoiceProfile = (DML_PROFILE_CTRL_T *) hInsContext;
    if(pVoiceProfile == NULL)
    {
        CcspTraceError(("%s:%d:: Invalid object \n", __FUNCTION__, __LINE__));
        return ret;
    }

    TELCOVOICEMGR_DML_DATA* pTelcoVoiceMgrDmlData = TelcoVoiceMgrDmlGetDataLocked();
    if(pTelcoVoiceMgrDmlData == NULL)
    {
        CcspTraceError(("%s:%d:: TelcoVoiceMgrDmlGetDataLocked: Failed\n", __FUNCTION__, __LINE__));
        return ret;
    }

    PTELCOVOICEMGR_DML_PROFILE pDmlVoiceProfile = &(pVoiceProfile->dml);
    if(pDmlVoiceProfile == NULL )
    {
        TelcoVoiceMgrDmlGetDataRelease(pTelcoVoiceMgrDmlData);
        CcspTraceError(("%s:%d:: pDmlVoiceProfile: NULL\n", __FUNCTION__, __LINE__));
        return ret;
    }
    
    PTELCOVOICEMGR_DML_H323 pDmlH323 = &(pDmlVoiceProfile->H323Obj);
    if(pDmlH323 != NULL)
    {
        if (strcmp(ParamName, "GatekeeperPort") == 0)
        {
            *pValue = pDmlH323->GatekeeperPort;
            ret = TRUE;
        }
        else if (strcmp(ParamName, "TimeToLive") == 0)
        {
            *pValue = pDmlH323->TimeToLive;
            ret = TRUE;
        }
        else if (strcmp(ParamName, "DSCPMark") == 0)
        {
            *pValue = pDmlH323->DSCPMark;
            ret = TRUE;
        }
        else
        {
            CcspTraceWarning(("%s::Unknown ParamName :%s\n", __FUNCTION__, ParamName));
        }
    }
    TelcoVoiceMgrDmlGetDataRelease(pTelcoVoiceMgrDmlData);
    return ret;
}

/**********************************************************************

        caller:     owner of this object

        prototype:

    BOOL H323_GetParamBoolValue(ANSC_HANDLE hInsContext, char* ParamName, BOOL* pBool);

description:
    This function is called to retrieve ULONG parameter value;

argument:   ANSC_HANDLE                 hInsContext,
            The instance handle;

            char*                       ParamName,
            The parameter name;

            BOOL*                      pBool
            The buffer of returned pBool;

return:     TRUE if succeeded.

**********************************************************************/
BOOL H323_GetParamBoolValue(ANSC_HANDLE hInsContext, char* ParamName, BOOL* pBool)
{
    BOOL ret = FALSE;
    DML_PROFILE_CTRL_T* pVoiceProfile = (DML_PROFILE_CTRL_T *) hInsContext;
    if(pVoiceProfile == NULL)
    {
        CcspTraceError(("%s:%d:: Invalid object \n", __FUNCTION__, __LINE__));
        return ret;
    }

    TELCOVOICEMGR_DML_DATA* pTelcoVoiceMgrDmlData = TelcoVoiceMgrDmlGetDataLocked();
    if(pTelcoVoiceMgrDmlData == NULL)
    {
        CcspTraceError(("%s:%d:: TelcoVoiceMgrDmlGetDataLocked: Failed\n", __FUNCTION__, __LINE__));
        return ret;
    }

    PTELCOVOICEMGR_DML_PROFILE pDmlVoiceProfile = &(pVoiceProfile->dml);
    if(pDmlVoiceProfile == NULL )
    {
        TelcoVoiceMgrDmlGetDataRelease(pTelcoVoiceMgrDmlData);
        CcspTraceError(("%s:%d:: pDmlVoiceProfile: NULL\n", __FUNCTION__, __LINE__));
        return ret;
    }
    
    PTELCOVOICEMGR_DML_H323 pDmlH323 = &(pDmlVoiceProfile->H323Obj);
    if(pDmlH323 != NULL)
    {
        if (strcmp(ParamName, "H235Authentication") == 0)
        {
            *pBool = pDmlH323->H235Authentication;
            ret = TRUE;
        }
        else
        {
            CcspTraceWarning(("%s::Unknown ParamName :%s\n", __FUNCTION__, ParamName));
        }
    }
    TelcoVoiceMgrDmlGetDataRelease(pTelcoVoiceMgrDmlData);
    return ret;
}

/**********************************************************************

    caller:     owner of this object

    prototype:

        LONG H323_GetParamStringValue(ANSC_HANDLE hInsContext, char* ParamName, char* pValue, ULONG* pUlSize);

    description:

        This function is called to retrieve String parameter value;

    argument:   ANSC_HANDLE                 hInsContext,
                The instance handle;

                char*                       ParamName
                The parameter name;

                char*                       pValue,
                The buffer of returned ULONG value;

                ULONG*                      pUlSize
                The length of returned buffer value;

    return:     0 if succeeded.
                1 if not enough buffer size
                -1 if not supported

**********************************************************************/

LONG H323_GetParamStringValue(ANSC_HANDLE hInsContext, char* ParamName, char* pValue, ULONG* pUlSize)
{
    ULONG ret = 1;
    DML_PROFILE_CTRL_T* pVoiceProfile = (DML_PROFILE_CTRL_T *) hInsContext;
    if(pVoiceProfile == NULL)
    {
        CcspTraceError(("%s:%d:: Invalid object \n", __FUNCTION__, __LINE__));
        return ret;
    }

    TELCOVOICEMGR_DML_DATA* pTelcoVoiceMgrDmlData = TelcoVoiceMgrDmlGetDataLocked();
    if(pTelcoVoiceMgrDmlData == NULL)
    {
        CcspTraceError(("%s:%d:: TelcoVoiceMgrDmlGetDataLocked: Failed\n", __FUNCTION__, __LINE__));
        return ret;
    }

    PTELCOVOICEMGR_DML_PROFILE pDmlVoiceProfile = &(pVoiceProfile->dml);
    if(pDmlVoiceProfile == NULL )
    {
        TelcoVoiceMgrDmlGetDataRelease(pTelcoVoiceMgrDmlData);
        CcspTraceError(("%s:%d:: pDmlVoiceProfile: NULL\n", __FUNCTION__, __LINE__));
        return ret;
    }
    
    PTELCOVOICEMGR_DML_H323 pDmlH323 = &(pDmlVoiceProfile->H323Obj);
    if(pDmlH323 != NULL)
    {
        if (strcmp(ParamName, "GatekeeperID") == 0)
        {
            AnscCopyString(pValue,pDmlH323->GatekeeperID);
            ret = 0;
        }
        else if (strcmp(ParamName, "Gatekeeper") == 0)
        {
            AnscCopyString(pValue,pDmlH323->Gatekeeper);
            ret = 0;
        }
        else if (strcmp(ParamName, "AuthPassword") == 0)
        {
            AnscCopyString(pValue,pDmlH323->AuthPassword);
            ret = 0;
        }
        else if (strcmp(ParamName, "SendersID") == 0)
        {
            AnscCopyString(pValue,pDmlH323->SendersID);
            ret = 0;
        }
        else
        {
            CcspTraceWarning(("%s::Unknown ParamName :%s\n", __FUNCTION__, ParamName));
        }
    }
    TelcoVoiceMgrDmlGetDataRelease(pTelcoVoiceMgrDmlData);
    return ret;
}

/**********************************************************************

    caller:     owner of this object

    prototype:

        BOOL H323_SetParamBoolValue(ANSC_HANDLE hInsContext, char* ParamName, char* pString);

    description:

        This function is called to set String parameter value;

    argument:   ANSC_HANDLE                 hInsContext,
                The instance handle;

                char*                       ParamName,
                The parameter name;

                char*                       pValue,
                The buffer to set value;

    return:     TRUE if succeeded.

**********************************************************************/
BOOL H323_SetParamBoolValue(ANSC_HANDLE hInsContext, char* ParamName, BOOL bValue)
{
    BOOL ret = FALSE;
    DML_PROFILE_CTRL_T* pVoiceProfile = (DML_PROFILE_CTRL_T *) hInsContext;
    if(pVoiceProfile == NULL)
    {
        CcspTraceError(("%s:%d:: Invalid object \n", __FUNCTION__, __LINE__));
        return ret;
    }

    TELCOVOICEMGR_DML_DATA* pTelcoVoiceMgrDmlData = TelcoVoiceMgrDmlGetDataLocked();
    if(pTelcoVoiceMgrDmlData == NULL)
    {
        CcspTraceError(("%s:%d:: TelcoVoiceMgrDmlGetDataLocked: Failed\n", __FUNCTION__, __LINE__));
        return ret;
    }

    PTELCOVOICEMGR_DML_PROFILE pDmlVoiceProfile = &(pVoiceProfile->dml);
    if(pDmlVoiceProfile == NULL )
    {
        TelcoVoiceMgrDmlGetDataRelease(pTelcoVoiceMgrDmlData);
        CcspTraceError(("%s:%d:: pDmlVoiceProfile: NULL\n", __FUNCTION__, __LINE__));
        return ret;
    }
    
    PTELCOVOICEMGR_DML_H323 pDmlH323 = &(pDmlVoiceProfile->H323Obj);
    if(pDmlH323 != NULL)
    {
        if (strcmp(ParamName, "H235Authentication") == 0)
        {
            ret = TRUE;
        }
        else
        {
            CcspTraceWarning(("%s::Unknown ParamName :%s\n", __FUNCTION__, ParamName));
        }
    }
    TelcoVoiceMgrDmlGetDataRelease(pTelcoVoiceMgrDmlData);
    return ret;
}

/**********************************************************************

    caller:     owner of this object

    prototype:

        BOOL H323_SetParamIntValue(ANSC_HANDLE hInsContext, char* ParamName, int iValue);

    description:

        This function is called to set Ulong parameter value;

    argument:   ANSC_HANDLE                 hInsContext,
                The instance handle;

                char*                       ParamName,
                The parameter name;

                int                         iValue
                The value need to set

    return:     TRUE if succeeded.

**********************************************************************/
BOOL H323_SetParamIntValue(ANSC_HANDLE hInsContext, char* ParamName, int iValue)
{
    BOOL ret = FALSE;
    DML_PROFILE_CTRL_T* pVoiceProfile = (DML_PROFILE_CTRL_T *) hInsContext;
    if(pVoiceProfile == NULL)
    {
        CcspTraceError(("%s:%d:: Invalid object \n", __FUNCTION__, __LINE__));
        return ret;
    }

    TELCOVOICEMGR_DML_DATA* pTelcoVoiceMgrDmlData = TelcoVoiceMgrDmlGetDataLocked();
    if(pTelcoVoiceMgrDmlData == NULL)
    {
        CcspTraceError(("%s:%d:: TelcoVoiceMgrDmlGetDataLocked: Failed\n", __FUNCTION__, __LINE__));
        return ret;
    }

    PTELCOVOICEMGR_DML_PROFILE pDmlVoiceProfile = &(pVoiceProfile->dml);
    if(pDmlVoiceProfile == NULL )
    {
        TelcoVoiceMgrDmlGetDataRelease(pTelcoVoiceMgrDmlData);
        CcspTraceError(("%s:%d:: pDmlVoiceProfile: NULL\n", __FUNCTION__, __LINE__));
        return ret;
    }
    
    PTELCOVOICEMGR_DML_H323 pDmlH323 = &(pDmlVoiceProfile->H323Obj);
    if(pDmlH323 != NULL)
    {
        if (strcmp(ParamName, "VLANIDMark") == 0)
        {
            ret = FALSE;
        }
        else if (strcmp(ParamName, "EthernetPriorityMark") == 0)
        {
            ret = FALSE;
        }
        else
        {
            CcspTraceWarning(("%s::Unknown ParamName :%s\n", __FUNCTION__, ParamName));
        }
    }
    TelcoVoiceMgrDmlGetDataRelease(pTelcoVoiceMgrDmlData);
    return ret;
}   

/**********************************************************************

    caller:     owner of this object

    prototype:

        BOOL H323_SetParamUlongValue(ANSC_HANDLE hInsContext, char* ParamName, ULONG uValue);

    description:

        This function is called to set Ulong parameter value;

    argument:   ANSC_HANDLE                 hInsContext,
                The instance handle;

                char*                       ParamName,
                The parameter name;

                ULONG                       uValue
                The value need to set

    return:     TRUE if succeeded.

**********************************************************************/
BOOL H323_SetParamUlongValue(ANSC_HANDLE hInsContext, char* ParamName, ULONG uValue)
{
    BOOL ret = FALSE;
    DML_PROFILE_CTRL_T* pVoiceProfile = (DML_PROFILE_CTRL_T *) hInsContext;
    if(pVoiceProfile == NULL)
    {
        CcspTraceError(("%s:%d:: Invalid object \n", __FUNCTION__, __LINE__));
        return ret;
    }

    TELCOVOICEMGR_DML_DATA* pTelcoVoiceMgrDmlData = TelcoVoiceMgrDmlGetDataLocked();
    if(pTelcoVoiceMgrDmlData == NULL)
    {
        CcspTraceError(("%s:%d:: TelcoVoiceMgrDmlGetDataLocked: Failed\n", __FUNCTION__, __LINE__));
        return ret;
    }

    PTELCOVOICEMGR_DML_PROFILE pDmlVoiceProfile = &(pVoiceProfile->dml);
    if(pDmlVoiceProfile == NULL )
    {
        TelcoVoiceMgrDmlGetDataRelease(pTelcoVoiceMgrDmlData);
        CcspTraceError(("%s:%d:: pDmlVoiceProfile: NULL\n", __FUNCTION__, __LINE__));
        return ret;
    }
    
    PTELCOVOICEMGR_DML_H323 pDmlH323 = &(pDmlVoiceProfile->H323Obj);
    if(pDmlH323 != NULL)
    {
        if (strcmp(ParamName, "GatekeeperPort") == 0)
        {
            ret = TRUE;
        }
        else if (strcmp(ParamName, "TimeToLive") == 0)
        {
            ret = TRUE;
        }
        else if (strcmp(ParamName, "DSCPMark") == 0)
        {
            ret = TRUE;
        }
        else
        {
            CcspTraceWarning(("%s::Unknown ParamName :%s\n", __FUNCTION__, ParamName));
        }
    }
    TelcoVoiceMgrDmlGetDataRelease(pTelcoVoiceMgrDmlData);
    return ret;
}

/**********************************************************************

    caller:     owner of this object

    prototype:

        BOOL H323_SetParamStringValue(ANSC_HANDLE hInsContext, char* ParamName, char* pString);

    description:

        This function is called to set String parameter value;

    argument:   ANSC_HANDLE                 hInsContext,
                The instance handle;

                char*                       ParamName,
                The parameter name;

                char*                       pValue,
                The buffer to set value;

    return:     TRUE if succeeded.

**********************************************************************/
BOOL H323_SetParamStringValue(ANSC_HANDLE hInsContext, char* ParamName, char* pString)
{
    BOOL ret = FALSE;
    DML_PROFILE_CTRL_T* pVoiceProfile = (DML_PROFILE_CTRL_T *) hInsContext;
    if(pVoiceProfile == NULL)
    {
        CcspTraceError(("%s:%d:: Invalid object \n", __FUNCTION__, __LINE__));
        return ret;
    }

    TELCOVOICEMGR_DML_DATA* pTelcoVoiceMgrDmlData = TelcoVoiceMgrDmlGetDataLocked();
    if(pTelcoVoiceMgrDmlData == NULL)
    {
        CcspTraceError(("%s:%d:: TelcoVoiceMgrDmlGetDataLocked: Failed\n", __FUNCTION__, __LINE__));
        return ret;
    }

    PTELCOVOICEMGR_DML_PROFILE pDmlVoiceProfile = &(pVoiceProfile->dml);
    if(pDmlVoiceProfile == NULL )
    {
        TelcoVoiceMgrDmlGetDataRelease(pTelcoVoiceMgrDmlData);
        CcspTraceError(("%s:%d:: pDmlVoiceProfile: NULL\n", __FUNCTION__, __LINE__));
        return ret;
    }
    
    PTELCOVOICEMGR_DML_H323 pDmlH323 = &(pDmlVoiceProfile->H323Obj);
    if(pDmlH323 != NULL)
    {
        if (strcmp(ParamName, "Gatekeeper") == 0)
        {
            ret = TRUE;
        }
        else if (strcmp(ParamName, "GatekeeperID") == 0)
        {
            ret = TRUE;
        }
        else if (strcmp(ParamName, "AuthPassword") == 0)
        {
            ret = TRUE;
        }
        else if (strcmp(ParamName, "SendersID") == 0)
        {
            ret = TRUE;
        }
        else
        {
            CcspTraceWarning(("%s::Unknown ParamName :%s\n", __FUNCTION__, ParamName));
        }
    }
    TelcoVoiceMgrDmlGetDataRelease(pTelcoVoiceMgrDmlData);
    return ret;
}

/**********************************************************************

    caller:     owner of this object

    prototype:

        BOOL  H323_GetParamIntValue(ANSC_HANDLE hInsContext, char* ParamName, int* pInt)

    description:

        This function is called to retrieve int parameter value;

    argument:   ANSC_HANDLE                 hInsContext,
                The instance handle;

                char*                       ParamName,
                The parameter name;

                int*                        pInt
                The value returned

    return:     TRUE if succeeded.

**********************************************************************/
BOOL H323_GetParamIntValue(ANSC_HANDLE hInsContext, char* ParamName, int* pInt)
{
    BOOL ret = FALSE;
    DML_PROFILE_CTRL_T* pVoiceProfile = (DML_PROFILE_CTRL_T *) hInsContext;
    if(pVoiceProfile == NULL)
    {
        CcspTraceError(("%s:%d:: Invalid object \n", __FUNCTION__, __LINE__));
        return ret;
    }

    TELCOVOICEMGR_DML_DATA* pTelcoVoiceMgrDmlData = TelcoVoiceMgrDmlGetDataLocked();
    if(pTelcoVoiceMgrDmlData == NULL)
    {
        CcspTraceError(("%s:%d:: TelcoVoiceMgrDmlGetDataLocked: Failed\n", __FUNCTION__, __LINE__));
        return ret;
    }

    PTELCOVOICEMGR_DML_PROFILE pDmlVoiceProfile = &(pVoiceProfile->dml);
    if(pDmlVoiceProfile == NULL )
    {
        TelcoVoiceMgrDmlGetDataRelease(pTelcoVoiceMgrDmlData);
        CcspTraceError(("%s:%d:: pDmlVoiceProfile: NULL\n", __FUNCTION__, __LINE__));
        return ret;
    }
    
    PTELCOVOICEMGR_DML_H323 pDmlH323 = &(pDmlVoiceProfile->H323Obj);
    if(pDmlH323 != NULL)
    {
        if (strcmp(ParamName, "VLANIDMark") == 0)
        {
            *pInt = pDmlH323->VLANIDMark;
            ret = TRUE;
        }
        else if (strcmp(ParamName, "EthernetPriorityMark") == 0)
        {
            *pInt = pDmlH323->EthernetPriorityMark;
            ret = TRUE;
        }
        else if (strcmp(ParamName, "GatekeeperPort") == 0)
        {
            *pInt = pDmlH323->GatekeeperPort;
            ret = TRUE;
        }
        else if (strcmp(ParamName, "TimeToLive") == 0)
        {
            *pInt = pDmlH323->TimeToLive;
            ret = TRUE;
        }
        else if (strcmp(ParamName, "DSCPMark") == 0)
        {
            *pInt = pDmlH323->DSCPMark;
            ret = TRUE;
        }
        else
        {
            CcspTraceWarning(("%s::Unknown ParamName :%s\n", __FUNCTION__, ParamName));
        }
    }
    TelcoVoiceMgrDmlGetDataRelease(pTelcoVoiceMgrDmlData);
    return ret;
}

/**********************************************************************

    caller:     owner of this object

    prototype:                                                                                                                                                                                               
        BOOL MGCP_GetParamUlongValue(ANSC_HANDLE hInsContext, char* ParamName, ULONG* pValue);

    description:

        This function is called to retrieve Ulong parameter value;

    argument:   ANSC_HANDLE                 hInsContext,
                The instance handle;

                char*                       ParamName,
                The parameter name;

                ULONG*                      pValue
                The value returned

    return:     TRUE if succeeded.

**********************************************************************/
BOOL MGCP_GetParamUlongValue(ANSC_HANDLE hInsContext, char* ParamName, ULONG* pValue)
{
    BOOL ret = FALSE;
    DML_PROFILE_CTRL_T* pVoiceProfile = (DML_PROFILE_CTRL_T *) hInsContext;
    if(pVoiceProfile == NULL)
    {
        CcspTraceError(("%s:%d:: Invalid object \n", __FUNCTION__, __LINE__));
        return ret;
    }

    TELCOVOICEMGR_DML_DATA* pTelcoVoiceMgrDmlData = TelcoVoiceMgrDmlGetDataLocked();
    if(pTelcoVoiceMgrDmlData == NULL)
    {
        CcspTraceError(("%s:%d:: TelcoVoiceMgrDmlGetDataLocked: Failed\n", __FUNCTION__, __LINE__));
        return ret;
    }

    PTELCOVOICEMGR_DML_PROFILE pDmlVoiceProfile = &(pVoiceProfile->dml);
    if(pDmlVoiceProfile == NULL )
    {
        TelcoVoiceMgrDmlGetDataRelease(pTelcoVoiceMgrDmlData);
        CcspTraceError(("%s:%d:: pDmlVoiceProfile: NULL\n", __FUNCTION__, __LINE__));
        return ret;
    }
    
    PTELCOVOICEMGR_DML_MGCP pDmlMGCP = &(pDmlVoiceProfile->MGCPObj);
    if(pDmlMGCP != NULL)
    {
        if (strcmp(ParamName, "CallAgentPort1") == 0)
        {
            *pValue = pDmlMGCP->CallAgentPort1;
            ret = TRUE;
        }
        else if (strcmp(ParamName, "CallAgentPort2") == 0)
        {
            *pValue = pDmlMGCP->CallAgentPort2;
            ret = TRUE;
        }
        else if (strcmp(ParamName, "RetranIntervalTimer") == 0)
        {
            *pValue = pDmlMGCP->RetranIntervalTimer;
            ret = TRUE;
        }
        else if (strcmp(ParamName, "MaxRetranCount") == 0)
        {
            *pValue = pDmlMGCP->MaxRetranCount;
            ret = TRUE;
        }
        else if (strcmp(ParamName, "LocalPort") == 0)
        {
            *pValue = pDmlMGCP->LocalPort;
            ret = TRUE;
        }
        else if (strcmp(ParamName, "DSCPMark") == 0)
        {
            *pValue = pDmlMGCP->DSCPMark;
            ret = TRUE;
        }
        else
        {
            CcspTraceWarning(("%s::Unknown ParamName :%s\n", __FUNCTION__, ParamName));
        }
    }
    TelcoVoiceMgrDmlGetDataRelease(pTelcoVoiceMgrDmlData);
    return ret;
}

/**********************************************************************

    caller:     owner of this object

    prototype:

        BOOL MGCP_SetParamUlongValue(ANSC_HANDLE hInsContext, char* ParamName, ULONG uValue);

    description:

        This function is called to set Ulong parameter value;

    argument:   ANSC_HANDLE                 hInsContext,
                The instance handle;

                char*                       ParamName,
                The parameter name;

                ULONG                       uValue
                The value need to set

    return:     TRUE if succeeded.

**********************************************************************/
BOOL MGCP_SetParamUlongValue(ANSC_HANDLE hInsContext, char* ParamName, ULONG uValue)
{

    BOOL ret = FALSE;
    DML_PROFILE_CTRL_T* pVoiceProfile = (DML_PROFILE_CTRL_T *) hInsContext;
    if(pVoiceProfile == NULL)
    {
        CcspTraceError(("%s:%d:: Invalid object \n", __FUNCTION__, __LINE__));
        return ret;
    }

    TELCOVOICEMGR_DML_DATA* pTelcoVoiceMgrDmlData = TelcoVoiceMgrDmlGetDataLocked();
    if(pTelcoVoiceMgrDmlData == NULL)
    {
        CcspTraceError(("%s:%d:: TelcoVoiceMgrDmlGetDataLocked: Failed\n", __FUNCTION__, __LINE__));
        return ret;
    }

    PTELCOVOICEMGR_DML_PROFILE pDmlVoiceProfile = &(pVoiceProfile->dml);
    if(pDmlVoiceProfile == NULL )
    {
        TelcoVoiceMgrDmlGetDataRelease(pTelcoVoiceMgrDmlData);
        CcspTraceError(("%s:%d:: pDmlVoiceProfile: NULL\n", __FUNCTION__, __LINE__));
        return ret;
    }
    
    PTELCOVOICEMGR_DML_MGCP pDmlMGCP = &(pDmlVoiceProfile->MGCPObj);
    if(pDmlMGCP != NULL)
    {

        if (strcmp(ParamName, "CallAgentPort1") == 0)
        {
            ret = TRUE;
        }
        else if (strcmp(ParamName, "CallAgentPort2") == 0)
        {
            ret = TRUE;
        }
        else if (strcmp(ParamName, "RetranIntervalTimer") == 0)
        {
            ret = TRUE;
        }
        else if (strcmp(ParamName, "MaxRetranCount") == 0)
        {
            ret = TRUE;
        }
        else if (strcmp(ParamName, "LocalPort") == 0)
        {
            ret = TRUE;
        }
        else if (strcmp(ParamName, "DSCPMark") == 0)
        {
            ret = TRUE;
        }
        else
        {
            CcspTraceWarning(("%s::Unknown ParamName :%s\n", __FUNCTION__, ParamName));
        }

    }
    TelcoVoiceMgrDmlGetDataRelease(pTelcoVoiceMgrDmlData);
    return ret;
}


/**********************************************************************

    caller:     owner of this object

    prototype:

        BOOL MGCP_SetParamBoolValue(ANSC_HANDLE hInsContext, char* ParamName, char* pString);

    description:

        This function is called to set String parameter value;

    argument:   ANSC_HANDLE                 hInsContext,
                The instance handle;

                char*                       ParamName,
                The parameter name;

                char*                       pValue,
                The buffer to set value;

    return:     TRUE if succeeded.

**********************************************************************/
BOOL MGCP_SetParamBoolValue(ANSC_HANDLE hInsContext, char* ParamName, BOOL bValue)
{
    BOOL ret = FALSE;
        DML_PROFILE_CTRL_T* pVoiceProfile = (DML_PROFILE_CTRL_T *) hInsContext;
    if(pVoiceProfile == NULL)
    {
        CcspTraceError(("%s:%d:: Invalid object \n", __FUNCTION__, __LINE__));
        return ret;
    }

    TELCOVOICEMGR_DML_DATA* pTelcoVoiceMgrDmlData = TelcoVoiceMgrDmlGetDataLocked();
    if(pTelcoVoiceMgrDmlData == NULL)
    {
        CcspTraceError(("%s:%d:: TelcoVoiceMgrDmlGetDataLocked: Failed\n", __FUNCTION__, __LINE__));
        return ret;
    }

    PTELCOVOICEMGR_DML_PROFILE pDmlVoiceProfile = &(pVoiceProfile->dml);
    if(pDmlVoiceProfile == NULL )
    {
        TelcoVoiceMgrDmlGetDataRelease(pTelcoVoiceMgrDmlData);
        CcspTraceError(("%s:%d:: pDmlVoiceProfile: NULL\n", __FUNCTION__, __LINE__));
        return ret;
    }
    
    PTELCOVOICEMGR_DML_MGCP pDmlMGCP = &(pDmlVoiceProfile->MGCPObj);
    if(pDmlMGCP != NULL)
    {

        if (strcmp(ParamName, "AllowPiggybackEvents") == 0)
        {
            ret = TRUE;
        }
        else if (strcmp(ParamName, "SendRSIPImmediately") == 0)
        {
            ret = TRUE;
        }
        else
        {
            CcspTraceWarning(("%s::Unknown ParamName :%s\n", __FUNCTION__, ParamName));
        }
    }
    TelcoVoiceMgrDmlGetDataRelease(pTelcoVoiceMgrDmlData);
    return ret;
}


/**********************************************************************

        caller:     owner of this object

        prototype:

    BOOL MGCP_GetParamBoolValue(ANSC_HANDLE hInsContext, char* ParamName, BOOL* pBool);

description:
    This function is called to retrieve ULONG parameter value;

argument:   ANSC_HANDLE                 hInsContext,
            The instance handle;

            char*                       ParamName,
            The parameter name;

            BOOL*                      pBool
            The buffer of returned pBool;

return:     TRUE if succeeded.

**********************************************************************/
BOOL MGCP_GetParamBoolValue(ANSC_HANDLE hInsContext, char* ParamName, BOOL* pBool)
{
    BOOL ret = FALSE;
    DML_PROFILE_CTRL_T* pVoiceProfile = (DML_PROFILE_CTRL_T *) hInsContext;
    if(pVoiceProfile == NULL)
    {
        CcspTraceError(("%s:%d:: Invalid object \n", __FUNCTION__, __LINE__));
        return ret;
    }

    TELCOVOICEMGR_DML_DATA* pTelcoVoiceMgrDmlData = TelcoVoiceMgrDmlGetDataLocked();
    if(pTelcoVoiceMgrDmlData == NULL)
    {
        CcspTraceError(("%s:%d:: TelcoVoiceMgrDmlGetDataLocked: Failed\n", __FUNCTION__, __LINE__));
        return ret;
    }

    PTELCOVOICEMGR_DML_PROFILE pDmlVoiceProfile = &(pVoiceProfile->dml);
    if(pDmlVoiceProfile == NULL )
    {
        TelcoVoiceMgrDmlGetDataRelease(pTelcoVoiceMgrDmlData);
        CcspTraceError(("%s:%d:: pDmlVoiceProfile: NULL\n", __FUNCTION__, __LINE__));
        return ret;
    }
    
    PTELCOVOICEMGR_DML_MGCP pDmlMGCP = &(pDmlVoiceProfile->MGCPObj);
    if(pDmlMGCP != NULL)
    {

        if (strcmp(ParamName, "AllowPiggybackEvents") == 0)
        {
            *pBool = pDmlMGCP->AllowPiggybackEvents; 
            ret = TRUE;
        }
        else if (strcmp(ParamName, "SendRSIPImmediately") == 0)
        {
            *pBool = pDmlMGCP->SendRSIPImmediately;
            ret = TRUE;
        }
        else
        {
            CcspTraceWarning(("%s::Unknown ParamName :%s\n", __FUNCTION__, ParamName));
        }
    }
    TelcoVoiceMgrDmlGetDataRelease(pTelcoVoiceMgrDmlData);
    return ret;
}

/**********************************************************************

    caller:     owner of this object

    prototype:

        BOOL MGCP_SetParamIntValue(ANSC_HANDLE hInsContext, char* ParamName, int iValue);

    description:

        This function is called to set Ulong parameter value;

    argument:   ANSC_HANDLE                 hInsContext,
                The instance handle;

                char*                       ParamName,
                The parameter name;

                int                         iValue
                The value need to set

    return:     TRUE if succeeded.

**********************************************************************/
BOOL MGCP_SetParamIntValue(ANSC_HANDLE hInsContext, char* ParamName, int iValue)
{
    BOOL ret = FALSE;
    DML_PROFILE_CTRL_T* pVoiceProfile = (DML_PROFILE_CTRL_T *) hInsContext;
    if(pVoiceProfile == NULL)
    {
        CcspTraceError(("%s:%d:: Invalid object \n", __FUNCTION__, __LINE__));
        return ret;
    }

    TELCOVOICEMGR_DML_DATA* pTelcoVoiceMgrDmlData = TelcoVoiceMgrDmlGetDataLocked();
    if(pTelcoVoiceMgrDmlData == NULL)
    {
        CcspTraceError(("%s:%d:: TelcoVoiceMgrDmlGetDataLocked: Failed\n", __FUNCTION__, __LINE__));
        return ret;
    }

    PTELCOVOICEMGR_DML_PROFILE pDmlVoiceProfile = &(pVoiceProfile->dml);
    if(pDmlVoiceProfile == NULL )
    {
        TelcoVoiceMgrDmlGetDataRelease(pTelcoVoiceMgrDmlData);
        CcspTraceError(("%s:%d:: pDmlVoiceProfile: NULL\n", __FUNCTION__, __LINE__));
        return ret;
    }
    
    PTELCOVOICEMGR_DML_MGCP pDmlMGCP = &(pDmlVoiceProfile->MGCPObj);
    if(pDmlMGCP != NULL)
    {
        if (strcmp(ParamName, "VLANIDMark") == 0)
        {
            ret = FALSE;
        }
        else if (strcmp(ParamName, "EthernetPriorityMark") == 0)
        {
            ret = FALSE;
        }
        else
        {
            CcspTraceWarning(("%s::Unknown ParamName :%s\n", __FUNCTION__, ParamName));
        }
    }
    TelcoVoiceMgrDmlGetDataRelease(pTelcoVoiceMgrDmlData);
    return ret;
}   

/**********************************************************************

    caller:     owner of this object

    prototype:
        BOOL ButtonMap_GetParamUlongValue(ANSC_HANDLE hInsContext, char* ParamName, ULONG* pValue);

    description:

        This function is called to retrieve Ulong parameter value;

    argument:   ANSC_HANDLE                 hInsContext,

                    The instance handle;

                    char*                       ParamName,
                    The parameter name;

                    ULONG*                      pValue
                    The value returned

        return:     TRUE if succeeded.

**********************************************************************/

BOOL ButtonMap_GetParamUlongValue(ANSC_HANDLE hInsContext, char* ParamName, ULONG* pValue)
{
    BOOL ret = FALSE;
    DML_PROFILE_CTRL_T* pVoiceProfile = (DML_PROFILE_CTRL_T *) hInsContext;
    if(pVoiceProfile == NULL)
    {
        CcspTraceError(("%s:%d:: Invalid object \n", __FUNCTION__, __LINE__));
        return ret;
    }

    TELCOVOICEMGR_DML_DATA* pTelcoVoiceMgrDmlData = TelcoVoiceMgrDmlGetDataLocked();
    if(pTelcoVoiceMgrDmlData == NULL)
    {
        CcspTraceError(("%s:%d:: TelcoVoiceMgrDmlGetDataLocked: Failed\n", __FUNCTION__, __LINE__));
        return ret;
    }

    PTELCOVOICEMGR_DML_PROFILE pDmlVoiceProfile = &(pVoiceProfile->dml);
    if(pDmlVoiceProfile == NULL )
    {
        TelcoVoiceMgrDmlGetDataRelease(pTelcoVoiceMgrDmlData);
        CcspTraceError(("%s:%d:: pDmlVoiceProfile: NULL\n", __FUNCTION__, __LINE__));
        return ret;
    }
    
    PTELCOVOICEMGR_DML_BUTTONMAP pDmlButtonMap = &(pDmlVoiceProfile->ButtonMapObj);
    if(pDmlButtonMap != NULL)
    {
        if (strcmp(ParamName, "NumberOfButtons") == 0)
        {
            *pValue = pDmlButtonMap->NumberOfButtons;
            ret = TRUE;
        }
        else
        {
            CcspTraceWarning(("%s::Unknown ParamName :%s\n", __FUNCTION__, ParamName));
        }
    }
    TelcoVoiceMgrDmlGetDataRelease(pTelcoVoiceMgrDmlData);
    return ret;
}


/**********************************************************************

    caller:     owner of this object

    prototype:

        ULONG Button_GetEntryCount(ANSC_HANDLE hInsContext);

    description:

        This function is called to retrieve the count of the table.

    argument:   ANSC_HANDLE                 hInsContext,
                The instance handle;

    return:     The count of the table

**********************************************************************/
ULONG Button_GetEntryCount(ANSC_HANDLE hInsContext)
{
    ULONG count = 0;
    PTELCOVOICEMGR_DML_PROFILE    pDmlVoiceProfile    = NULL;
    DML_PROFILE_CTRL_T* pVoiceProfile = (DML_PROFILE_CTRL_T*) hInsContext;
    if(pVoiceProfile != NULL)
    {
        TELCOVOICEMGR_DML_DATA* pTelcoVoiceMgrDmlData = TelcoVoiceMgrDmlGetDataLocked();
        if(pTelcoVoiceMgrDmlData != NULL)
        {
            pDmlVoiceProfile = &(pVoiceProfile->dml);   
            count =  pDmlVoiceProfile->ButtonMapObj.ButtonList.ulQuantity;
            TelcoVoiceMgrDmlGetDataRelease(pTelcoVoiceMgrDmlData);
        }
    }
    return count;
}
/**********************************************************************
    caller:     owner of this object

    prototype:

        ANSC_HANDLE Button_GetEntry(ANSC_HANDLE hInsContext, ULONG nIndex, ULONG* pInsNumber);

    description:

        This function is called to retrieve the entry specified by the index.

    argument:   ANSC_HANDLE                 hInsContext,
                The instance handle;

                ULONG                       nIndex,
                The index of this entry;

                ULONG*                      pInsNumber
                The output instance number;

    return:     The handle to identify the entry

**********************************************************************/
ANSC_HANDLE Button_GetEntry(ANSC_HANDLE hInsContext, ULONG nIndex, ULONG* pInsNumber)
{
    ANSC_HANDLE pDmlEntry = NULL;
    PTELCOVOICEMGR_DML_PROFILE    pDmlVoiceProfile    = NULL;
    DML_PROFILE_CTRL_T* pVoiceProfile = (DML_PROFILE_CTRL_T*) hInsContext;
    if(pVoiceProfile != NULL)
    {
        TELCOVOICEMGR_DML_DATA* pTelcoVoiceMgrDmlData = TelcoVoiceMgrDmlGetDataLocked();
        if(pTelcoVoiceMgrDmlData != NULL)
        {
            pDmlVoiceProfile = &(pVoiceProfile->dml);
            if(nIndex < pDmlVoiceProfile->ButtonMapObj.ButtonList.ulQuantity)
            {   
                DML_BUTTON_CTRL_T* pButton = pDmlVoiceProfile->ButtonMapObj.ButtonList.pdata[nIndex];
                if(pButton != NULL)
                {
                    *pInsNumber = nIndex + 1;
                    pDmlEntry = (ANSC_HANDLE) pButton;
                }
            }
            TelcoVoiceMgrDmlGetDataRelease(pTelcoVoiceMgrDmlData);
        }

    }
    return pDmlEntry;  /* return the handle */
}

/**********************************************************************

    caller:     owner of this object

    prototype:

        BOOL Button_SetParamBoolValue(ANSC_HANDLE hInsContext, char* ParamName, char* pString);

    description:

        This function is called to set String parameter value;

    argument:   ANSC_HANDLE                 hInsContext,
                The instance handle;

                char*                       ParamName,
                The parameter name;

                char*                       pValue,
                The buffer to set value;

    return:     TRUE if succeeded.

**********************************************************************/
BOOL Button_SetParamBoolValue(ANSC_HANDLE hInsContext, char* ParamName, BOOL bValue)
{
    BOOL ret = FALSE;
    if (strcmp(ParamName, "UserAccess") == 0)
    {
        ret = FALSE;
    }
    return ret;
}

/**********************************************************************

        caller:     owner of this object

        prototype:

    BOOL Button_GetParamBoolValue(ANSC_HANDLE hInsContext, char* ParamName, BOOL* pBool);

description:
    This function is called to retrieve ULONG parameter value;

argument:   ANSC_HANDLE                 hInsContext,
            The instance handle;

            char*                       ParamName,
            The parameter name;

            BOOL*                      pBool
            The buffer of returned pBool;

return:     TRUE if succeeded.

**********************************************************************/
BOOL Button_GetParamBoolValue(ANSC_HANDLE hInsContext, char* ParamName, BOOL* pBool)
{
        BOOL ret = FALSE;
        if (strcmp(ParamName, "UserAccess") == 0)
        {
            ret = TRUE;
        }
        else
        {
            CcspTraceWarning(("%s::Unknown ParamName :%s\n", __FUNCTION__, ParamName));
            ret =  TRUE;
        }
        return ret;
}

/**********************************************************************

    caller:     owner of this object

    prototype:

        LONG Button_GetParamStringValue(ANSC_HANDLE hInsContext, char* ParamName, char* pValue, ULONG* pUlSize);

    description:

        This function is called to retrieve String parameter value;

    argument:   ANSC_HANDLE                 hInsContext,
                The instance handle;

                char*                       ParamName
                The parameter name;

                char*                       pValue,
                The buffer of returned ULONG value;

                ULONG*                      pUlSize
                The length of returned buffer value;

    return:     0 if succeeded.
                1 if not enough buffer size
                -1 if not supported

**********************************************************************/

LONG Button_GetParamStringValue(ANSC_HANDLE hInsContext, char* ParamName, char* pValue, ULONG* pUlSize)
{
    ULONG ret = 1;
    if (strcmp(ParamName, "Alias") == 0)
    {
        ret = 0;
    }
    else if (strcmp(ParamName, "ButtonName") == 0)
    {
        ret = 0;
    }
    else if (strcmp(ParamName, "FacilityAction") == 0)
    {
        ret = 0;
    }
    else if (strcmp(ParamName, "FacilityActionArgument") == 0)
    {
        ret = 0;
    }
    else if (strcmp(ParamName, "QuickDialNumber") == 0)
    {
        ret = 0;
    }
    else if (strcmp(ParamName, "ButtonMessage") == 0)
    {
        ret = 0;
    }
    else
    {
        CcspTraceWarning(("%s::Unknown ParamName :%s\n", __FUNCTION__, ParamName));
    }
    return ret;
}


/**********************************************************************

    caller:     owner of this object

    prototype:
        BOOL FaxT38_GetParamUlongValue(ANSC_HANDLE hInsContext, char* ParamName, ULONG* pValue);

    description:

        This function is called to retrieve Ulong parameter value;

    argument:   ANSC_HANDLE                 hInsContext,

                    The instance handle;

                    char*                       ParamName,
                    The parameter name;

                    ULONG*                      pValue
                    The value returned

        return:     TRUE if succeeded.

**********************************************************************/

BOOL FaxT38_GetParamUlongValue(ANSC_HANDLE hInsContext, char* ParamName, ULONG* pValue)
{
    BOOL ret = FALSE;

    if (strcmp(ParamName, "BitRate") == 0)
    {
        ret = TRUE;
    }
    else if (strcmp(ParamName, "HighSpeedPacketRate") == 0)
    {
        ret = TRUE;
    }
    else if (strcmp(ParamName, "HighSpeedRedundancy") == 0)
    {
        ret = TRUE;
    }
    else if (strcmp(ParamName, "LowSpeedRedundancy") == 0)
    {
        ret = TRUE;
    }
    else
    {
        CcspTraceWarning(("%s::Unknown ParamName :%s\n", __FUNCTION__, ParamName));
        ret =  TRUE;
    }
    return ret;
}

/**********************************************************************

    caller:     owner of this object

    prototype:

        BOOL FaxT38_SetParamUlongValue(ANSC_HANDLE hInsContext, char* ParamName, ULONG uValue);

    description:

        This function is called to set Ulong parameter value;

    argument:   ANSC_HANDLE                 hInsContext,
                The instance handle;

                char*                       ParamName,
                The parameter name;

                ULONG                       uValue
                The value need to set

    return:     TRUE if succeeded.

**********************************************************************/
BOOL FaxT38_SetParamUlongValue(ANSC_HANDLE hInsContext, char* ParamName, ULONG uValue)
{
    BOOL ret = FALSE;

    if (strcmp(ParamName, "BitRate") == 0)
    {
        ret = TRUE;
    }
    else if (strcmp(ParamName, "HighSpeedPacketRate") == 0)
    {
        ret = TRUE;
    }
    else if (strcmp(ParamName, "HighSpeedRedundancy") == 0)
    {
        ret = TRUE;
    }
    else if (strcmp(ParamName, "LowSpeedRedundancy") == 0)
    {
        ret = TRUE;
    }
    return ret;
}

/**********************************************************************

        caller:     owner of this object

        prototype:

    BOOL FaxT38_GetParamBoolValue(ANSC_HANDLE hInsContext, char* ParamName, BOOL* pBool);

description:
    This function is called to retrieve ULONG parameter value;

argument:   ANSC_HANDLE                 hInsContext,
            The instance handle;

            char*                       ParamName,
            The parameter name;

            BOOL*                      pBool
            The buffer of returned pBool;

return:     TRUE if succeeded.

**********************************************************************/
BOOL FaxT38_GetParamBoolValue(ANSC_HANDLE hInsContext, char* ParamName, BOOL* pBool)
{
    BOOL ret = FALSE;
    if (strcmp(ParamName, "Enable") == 0)
    {
        ret = TRUE;
    }
    else
    {
        CcspTraceWarning(("%s::Unknown ParamName :%s\n", __FUNCTION__, ParamName));
        ret =  TRUE;
    }
    return ret;
}

/**********************************************************************

    caller:     owner of this object

    prototype:

        BOOL FaxT38_SetParamBoolValue(ANSC_HANDLE hInsContext, char* ParamName, char* pString);

    description:

        This function is called to set String parameter value;

    argument:   ANSC_HANDLE                 hInsContext,
                The instance handle;

                char*                       ParamName,
                The parameter name;

                char*                       pValue,
                The buffer to set value;

    return:     TRUE if succeeded.

**********************************************************************/
BOOL FaxT38_SetParamBoolValue(ANSC_HANDLE hInsContext, char* ParamName, BOOL bValue)
{
    BOOL ret = FALSE;
    if (strcmp(ParamName, "Enable") == 0)
    {
        ret = FALSE;
    }
    return ret;
}

/**********************************************************************

    caller:     owner of this object

    prototype:

        BOOL FaxT38_SetParamStringValue(ANSC_HANDLE hInsContext, char* ParamName, char* pString);

    description:

        This function is called to set String parameter value;

    argument:   ANSC_HANDLE                 hInsContext,
                The instance handle;

                char*                       ParamName,
                The parameter name;

                char*                       pValue,
                The buffer to set value;

    return:     TRUE if succeeded.

**********************************************************************/
BOOL FaxT38_SetParamStringValue(ANSC_HANDLE hInsContext, char* ParamName, char* pString)
{
    BOOL ret = FALSE;
    if (strcmp(ParamName, "TCFMethod") == 0)
    {
        ret = TRUE;
    }
    return ret;
}

/**********************************************************************

    caller:     owner of this object

    prototype:

        LONG FaxT38_GetParamStringValue(ANSC_HANDLE hInsContext, char* ParamName, char* pValue, ULONG* pUlSize);

    description:

        This function is called to retrieve String parameter value;

    argument:   ANSC_HANDLE                 hInsContext,
                The instance handle;

                char*                       ParamName
                The parameter name;

                char*                       pValue,
                The buffer of returned ULONG value;

                ULONG*                      pUlSize
                The length of returned buffer value;

    return:     0 if succeeded.
                1 if not enough buffer size
                -1 if not supported

**********************************************************************/

LONG FaxT38_GetParamStringValue(ANSC_HANDLE hInsContext, char* ParamName, char* pValue, ULONG* pUlSize)
{
    ULONG ret = 1;
    if (strcmp(ParamName, "TCFMethod") == 0)
    {
        ret = 0;
    }
    else
    {
        CcspTraceWarning(("%s::Unknown ParamName :%s\n", __FUNCTION__, ParamName));
        ret =  0;
    }
    return ret;
}

/**********************************************************************

    caller:     owner of this object

    prototype:

        ULONG SIPResponseMap_GetEntryCount(ANSC_HANDLE hInsContext);

    description:

        This function is called to retrieve the count of the table.

    argument:   ANSC_HANDLE                 hInsContext,
                The instance handle;

    return:     The count of the table

**********************************************************************/
ULONG SIPResponseMap_GetEntryCount(ANSC_HANDLE hInsContext)
{
    ULONG count = 0;
    PTELCOVOICEMGR_DML_PROFILE    pDmlVoiceProfile    = NULL;
    DML_PROFILE_CTRL_T* pVoiceProfile = (DML_PROFILE_CTRL_T*) hInsContext;
    if(pVoiceProfile != NULL)
    {
        TELCOVOICEMGR_DML_DATA* pTelcoVoiceMgrDmlData = TelcoVoiceMgrDmlGetDataLocked();
        if(pTelcoVoiceMgrDmlData != NULL)
        {
            pDmlVoiceProfile = &(pVoiceProfile->dml);   
            count =  pDmlVoiceProfile->SIPObj.SipResponseMapList.ulQuantity;
            TelcoVoiceMgrDmlGetDataRelease(pTelcoVoiceMgrDmlData);
        }
    }
    return count;
}
/**********************************************************************
    caller:     owner of this object

    prototype:

        ANSC_HANDLE SIPResponseMap_GetEntry(ANSC_HANDLE hInsContext, ULONG nIndex, ULONG* pInsNumber);

    description:

        This function is called to retrieve the entry specified by the index.

    argument:   ANSC_HANDLE                 hInsContext,
                The instance handle;

                ULONG                       nIndex,
                The index of this entry;

                ULONG*                      pInsNumber
                The output instance number;

    return:     The handle to identify the entry

**********************************************************************/
ANSC_HANDLE SIPResponseMap_GetEntry(ANSC_HANDLE hInsContext, ULONG nIndex, ULONG* pInsNumber)
{
    ANSC_HANDLE pDmlEntry = NULL;
    PTELCOVOICEMGR_DML_PROFILE    pDmlVoiceProfile    = NULL;
    DML_PROFILE_CTRL_T* pVoiceProfile = (DML_PROFILE_CTRL_T*) hInsContext;
    if(pVoiceProfile != NULL)
    {
        TELCOVOICEMGR_DML_DATA* pTelcoVoiceMgrDmlData = TelcoVoiceMgrDmlGetDataLocked();
        if(pTelcoVoiceMgrDmlData != NULL)
        {
            pDmlVoiceProfile = &(pVoiceProfile->dml);
            if(nIndex < pDmlVoiceProfile->SIPObj.SipResponseMapList.ulQuantity)
            {   
                DML_SIP_RESPONSEMAP_CTRL_T* pSIPRespMap = pDmlVoiceProfile->SIPObj.SipResponseMapList.pdata[nIndex];
                if(pSIPRespMap != NULL)
                {
                    *pInsNumber = nIndex + 1;
                    pDmlEntry = (ANSC_HANDLE) pSIPRespMap;
                }
            }
            TelcoVoiceMgrDmlGetDataRelease(pTelcoVoiceMgrDmlData);
        }

    }
    return pDmlEntry;  /* return the handle */
}

/**********************************************************************

    caller:     owner of this object

    prototype:

        BOOL SIPResponseMap_GetParamUlongValue(ANSC_HANDLE hInsContext, char* ParamName, ULONG uValue);

    description:

        This function is called to set Ulong parameter value;

    argument:   ANSC_HANDLE                 hInsContext,
                The instance handle;

                char*                       ParamName,
                The parameter name;

                ULONG                       uValue
                The value need to set

    return:     TRUE if succeeded.

**********************************************************************/
BOOL SIPResponseMap_GetParamUlongValue(ANSC_HANDLE hInsContext, char* ParamName, ULONG uValue)
{
    BOOL ret = FALSE;
    if (strcmp(ParamName, "SIPResponseNumber") == 0)
    {
        ret = TRUE;
    }
    else if (strcmp(ParamName, "Tone") == 0)
    {
        ret = TRUE;
    }
    else
    {
        CcspTraceWarning(("%s::Unknown ParamName :%s\n", __FUNCTION__, ParamName));
        ret =  TRUE;
    }
    return ret;
}


/**********************************************************************

    caller:     owner of this object

    prototype:

        LONG SIPResponseMap_GetParamStringValue(ANSC_HANDLE hInsContext, char* ParamName, char* pValue, ULONG* pUlSize);

    description:
        This function is called to retrieve String parameter value;

    argument:   ANSC_HANDLE                 hInsContext,
                The instance handle;

                char*                       ParamName
                The parameter name;

                char*                       pValue,
                The buffer of returned ULONG value;

                ULONG*                      pUlSize
                The length of returned buffer value;

    return:     0 if succeeded.
                1 if not enough buffer size
                -1 if not supported

**********************************************************************/

LONG SIPResponseMap_GetParamStringValue(ANSC_HANDLE hInsContext, char* ParamName, char* pValue, ULONG* pUlSize)
{
    ULONG ret = 1;
    if (strcmp(ParamName, "Alias") == 0)
    {
        ret = 0;
    }
    else if (strcmp(ParamName, "TextMessage") == 0)
    {
        ret = 0;
    }
    else
    {
        CcspTraceWarning(("%s::Unknown ParamName :%s\n", __FUNCTION__, ParamName));
        ret =  0;
    }
    return ret;
}

/**********************************************************************

    caller:     owner of this object

    prototype:
        BOOL SIPResponseMap_SetParamUlongValue(ANSC_HANDLE hInsContext, char* ParamName, ULONG pValue);

    description:

        This function is called to set Ulong parameter value;

    argument:   ANSC_HANDLE                 hInsContext,
                The instance handle;

                char*                       ParamName,
                The parameter name;

                ULONG                       uValue
                The value need to set

    return:     TRUE if succeeded.

**********************************************************************/
BOOL SIPResponseMap_SetParamUlongValue(ANSC_HANDLE hInsContext, char* ParamName, ULONG pValue)
{
    BOOL ret = FALSE;

    if (strcmp(ParamName, "SIPResponseNumber") == 0)
    {
        ret = TRUE;
    }
    else if (strcmp(ParamName, "Tone") == 0)
    {
        ret = TRUE;
    }

    return ret;
}

/**********************************************************************

    caller:     owner of this object

    prototype:

        BOOL SIPResponseMap_SetParamStringValue(ANSC_HANDLE hInsContext, char* ParamName, char* pString);

    description:

        This function is called to set String parameter value;

    argument:   ANSC_HANDLE                 hInsContext,
                The instance handle;

                char*                       ParamName,
                The parameter name;

                char*                       pValue,
                The buffer to set value;

    return:     TRUE if succeeded.

**********************************************************************/
BOOL SIPResponseMap_SetParamStringValue(ANSC_HANDLE hInsContext, char* ParamName, char* pString)
{
    BOOL ret = FALSE;
    if (strcmp(ParamName, "Alias") == 0)
    {
        ret = TRUE;
    }
    else if (strcmp(ParamName, "TextMessage") == 0)
    {
        ret = TRUE;
    }
    return ret;
}

/**********************************************************************

    caller:     owner of this object

    prototype:

        ULONG SIPEventSubscribe_GetEntryCount(ANSC_HANDLE hInsContext);

    description:

        This function is called to retrieve the count of the table.

    argument:   ANSC_HANDLE                 hInsContext,
                The instance handle;

    return:     The count of the table

**********************************************************************/
ULONG SIPEventSubscribe_GetEntryCount(ANSC_HANDLE hInsContext)
{
    ULONG count = 0;
    PTELCOVOICEMGR_DML_PROFILE    pDmlVoiceProfile    = NULL;
    DML_PROFILE_CTRL_T* pVoiceProfile = (DML_PROFILE_CTRL_T*) hInsContext;
    if(pVoiceProfile != NULL)
    {
        TELCOVOICEMGR_DML_DATA* pTelcoVoiceMgrDmlData = TelcoVoiceMgrDmlGetDataLocked();
        if(pTelcoVoiceMgrDmlData != NULL)
        {
            pDmlVoiceProfile = &(pVoiceProfile->dml);   
            count =  pDmlVoiceProfile->SIPObj.SipEventSubscribeList.ulQuantity;
            TelcoVoiceMgrDmlGetDataRelease(pTelcoVoiceMgrDmlData);
        }
    }
    return count;
}
/**********************************************************************
    caller:     owner of this object

    prototype:

        ANSC_HANDLE SIPEventSubscribe_GetEntry(ANSC_HANDLE hInsContext, ULONG nIndex, ULONG* pInsNumber);

    description:

        This function is called to retrieve the entry specified by the index.

    argument:   ANSC_HANDLE                 hInsContext,
                The instance handle;

                ULONG                       nIndex,
                The index of this entry;

                ULONG*                      pInsNumber
                The output instance number;

    return:     The handle to identify the entry

**********************************************************************/
ANSC_HANDLE SIPEventSubscribe_GetEntry(ANSC_HANDLE hInsContext, ULONG nIndex, ULONG* pInsNumber)
{
    ANSC_HANDLE pDmlEntry = NULL;
    PTELCOVOICEMGR_DML_PROFILE    pDmlVoiceProfile    = NULL;
    DML_PROFILE_CTRL_T* pVoiceProfile = (DML_PROFILE_CTRL_T*) hInsContext;
    if(pVoiceProfile != NULL)
    {
        TELCOVOICEMGR_DML_DATA* pTelcoVoiceMgrDmlData = TelcoVoiceMgrDmlGetDataLocked();
        if(pTelcoVoiceMgrDmlData != NULL)
        {
            pDmlVoiceProfile = &(pVoiceProfile->dml);
            if(nIndex < pDmlVoiceProfile->SIPObj.SipEventSubscribeList.ulQuantity)
            {   
                DML_SIP_EVENTSUBSCRIBE_CTRL_T* pSIPEvtSubscribe = pDmlVoiceProfile->SIPObj.SipEventSubscribeList.pdata[nIndex];
                if(pSIPEvtSubscribe != NULL)
                {
                    *pInsNumber = nIndex + 1;
                    pDmlEntry = (ANSC_HANDLE) pSIPEvtSubscribe;
                }
            }
            TelcoVoiceMgrDmlGetDataRelease(pTelcoVoiceMgrDmlData);
        }

    }
    return pDmlEntry;  /* return the handle */
}

/**********************************************************************

    caller:     owner of this object

    prototype:

        LONG SIPEventSubscribe_GetParamStringValue(ANSC_HANDLE hInsContext, char* ParamName, char* pValue, ULONG* pUlSize);

    description:
        This function is called to retrieve String parameter value;

    argument:   ANSC_HANDLE                 hInsContext,
                The instance handle;

                char*                       ParamName
                The parameter name;

                char*                       pValue,
                The buffer of returned ULONG value;

                ULONG*                      pUlSize
                The length of returned buffer value;

    return:     0 if succeeded.
                1 if not enough buffer size
                -1 if not supported

**********************************************************************/

LONG SIPEventSubscribe_GetParamStringValue(ANSC_HANDLE hInsContext, char* ParamName, char* pValue, ULONG* pUlSize)
{
    ULONG ret = 1;
    DML_SIP_EVENTSUBSCRIBE_CTRL_T* pSIPEvtSubscribe = (DML_SIP_EVENTSUBSCRIBE_CTRL_T *) hInsContext;
    if(pSIPEvtSubscribe == NULL)
    {
        CcspTraceError(("%s:%d:: Invalid object \n", __FUNCTION__, __LINE__));
        return ret;
    }

    TELCOVOICEMGR_DML_DATA* pTelcoVoiceMgrDmlData = TelcoVoiceMgrDmlGetDataLocked();
    if(pTelcoVoiceMgrDmlData == NULL)
    {
        CcspTraceError(("%s:%d:: TelcoVoiceMgrDmlGetDataLocked: Failed\n", __FUNCTION__, __LINE__));
        return ret;
    }

    PTELCOVOICEMGR_DML_SIP_EVENTSUBSCRIBE pDmlSIPEvtSubscribe = &(pSIPEvtSubscribe->dml);
    if(pDmlSIPEvtSubscribe == NULL )
    {
        TelcoVoiceMgrDmlGetDataRelease(pTelcoVoiceMgrDmlData);
        CcspTraceError(("%s:%d:: pDmlSIPEvtSubscribe: NULL\n", __FUNCTION__, __LINE__));
        return ret;
    }
    
    if (strcmp(ParamName, "Alias") == 0)
    {
        AnscCopyString(pValue,pDmlSIPEvtSubscribe->Alias);
        ret = 0;
    }
    else if (strcmp(ParamName, "Event") == 0)
    {
        AnscCopyString(pValue,pDmlSIPEvtSubscribe->Event);
        ret = 0;
    }
    else if (strcmp(ParamName, "NotifierTransport") == 0)
    {
        AnscCopyString(pValue,pDmlSIPEvtSubscribe->NotifierTransport);
        ret = 0;
    }
    else if (strcmp(ParamName, "Notifier") == 0)
    {
        AnscCopyString(pValue,pDmlSIPEvtSubscribe->Notifier);
        ret = 0;
    }
    else
    {
        CcspTraceWarning(("%s::Unknown ParamName :%s\n", __FUNCTION__, ParamName));
    }
    TelcoVoiceMgrDmlGetDataRelease(pTelcoVoiceMgrDmlData);
    return ret;
}


/**********************************************************************

    caller:     owner of this object

    prototype:
        BOOL SIPEventSubscribe_GetParamUlongValue(ANSC_HANDLE hInsContext, char* ParamName, ULONG* pValue);

    description:

        This function is called to retrieve Ulong parameter value;

    argument:   ANSC_HANDLE                 hInsContext,
                The instance handle;

                char*                       ParamName,
                The parameter name;

                ULONG*                      pValue
                The value returned

    return:     TRUE if succeeded.

**********************************************************************/
BOOL SIPEventSubscribe_GetParamUlongValue(ANSC_HANDLE hInsContext, char* ParamName, ULONG* pValue)
{
    BOOL ret = FALSE;
    DML_SIP_EVENTSUBSCRIBE_CTRL_T* pSIPEvtSubscribe = (DML_SIP_EVENTSUBSCRIBE_CTRL_T *) hInsContext;
    if(pSIPEvtSubscribe == NULL)
    {
        CcspTraceError(("%s:%d:: Invalid object \n", __FUNCTION__, __LINE__));
        return ret;
    }

    TELCOVOICEMGR_DML_DATA* pTelcoVoiceMgrDmlData = TelcoVoiceMgrDmlGetDataLocked();
    if(pTelcoVoiceMgrDmlData == NULL)
    {
        CcspTraceError(("%s:%d:: TelcoVoiceMgrDmlGetDataLocked: Failed\n", __FUNCTION__, __LINE__));
        return ret;
    }

    PTELCOVOICEMGR_DML_SIP_EVENTSUBSCRIBE pDmlSIPEvtSubscribe = &(pSIPEvtSubscribe->dml);
    if(pDmlSIPEvtSubscribe == NULL )
    {
        TelcoVoiceMgrDmlGetDataRelease(pTelcoVoiceMgrDmlData);
        CcspTraceError(("%s:%d:: pDmlSIPEvtSubscribe: NULL\n", __FUNCTION__, __LINE__));
        return ret;
    }
    

    if (strcmp(ParamName, "NotifierPort") == 0)
    {
        *pValue = pDmlSIPEvtSubscribe->NotifierPort;
        ret = TRUE;
    }
    else if (strcmp(ParamName, "ExpireTime") == 0)
    {
        *pValue = pDmlSIPEvtSubscribe->ExpireTime;
        ret = TRUE;
    }
    else
    {
        CcspTraceWarning(("%s::Unknown ParamName :%s\n", __FUNCTION__, ParamName));
    }
    TelcoVoiceMgrDmlGetDataRelease(pTelcoVoiceMgrDmlData);
    return ret;
}


/**********************************************************************

    caller:     owner of this object

    prototype:

        BOOL SIPEventSubscribe_SetParamUlongValue(ANSC_HANDLE hInsContext, char* ParamName, int iValue);

    description:

        This function is called to set Ulong parameter value;

    argument:   ANSC_HANDLE                 hInsContext,
                The instance handle;

                char*                       ParamName,
                The parameter name;

                int                         iValue
                The value need to set

    return:     TRUE if succeeded.

**********************************************************************/
BOOL SIPEventSubscribe_SetParamUlongValue(ANSC_HANDLE hInsContext, char* ParamName, int iValue)
{
    BOOL ret = FALSE;
    DML_SIP_EVENTSUBSCRIBE_CTRL_T* pSIPEvtSubscribe = (DML_SIP_EVENTSUBSCRIBE_CTRL_T *) hInsContext;
    if(pSIPEvtSubscribe == NULL)
    {
        CcspTraceError(("%s:%d:: Invalid object \n", __FUNCTION__, __LINE__));
        return ret;
    }

    TELCOVOICEMGR_DML_DATA* pTelcoVoiceMgrDmlData = TelcoVoiceMgrDmlGetDataLocked();
    if(pTelcoVoiceMgrDmlData == NULL)
    {
        CcspTraceError(("%s:%d:: TelcoVoiceMgrDmlGetDataLocked: Failed\n", __FUNCTION__, __LINE__));
        return ret;
    }

    PTELCOVOICEMGR_DML_SIP_EVENTSUBSCRIBE pDmlSIPEvtSubscribe = &(pSIPEvtSubscribe->dml);
    if(pDmlSIPEvtSubscribe == NULL )
    {
        TelcoVoiceMgrDmlGetDataRelease(pTelcoVoiceMgrDmlData);
        CcspTraceError(("%s:%d:: pDmlSIPEvtSubscribe: NULL\n", __FUNCTION__, __LINE__));
        return ret;
    }

    if (strcmp(ParamName, "NotifierPort") == 0)
    {
        ret = TRUE;
    }
    else if (strcmp(ParamName, "ExpireTime") == 0)
    {
        ret = TRUE;
    }
    else
    {
        CcspTraceWarning(("%s::Unknown ParamName :%s\n", __FUNCTION__, ParamName));
    }
    TelcoVoiceMgrDmlGetDataRelease(pTelcoVoiceMgrDmlData);
    return ret;
}


/**********************************************************************

    caller:     owner of this object

    prototype:

        LONG ServiceProviderInfo_GetParamStringValue(ANSC_HANDLE hInsContext, char* ParamName, char* pValue, ULONG* pUlSize);

    description:

        This function is called to retrieve String parameter value;

    argument:   ANSC_HANDLE                 hInsContext,
                The instance handle;

                char*                       ParamName
                The parameter name;

                char*                       pValue,
                The buffer of returned ULONG value;

                ULONG*                      pUlSize
                The length of returned buffer value;

    return:     0 if succeeded.
                1 if not enough buffer size
                -1 if not supported

**********************************************************************/
LONG ServiceProviderInfo_GetParamStringValue(ANSC_HANDLE hInsContext, char* ParamName, char* pValue, ULONG* pUlSize)
{
    ULONG ret = 1;
    if (strcmp(ParamName, "Name") == 0)
    {
        ret = 0;
    }
    else if (strcmp(ParamName, "ContactPhoneNumber") == 0)
    {
        ret = 0;
    }
    else if (strcmp(ParamName, "URL") == 0)
    {
        ret = 0;
    }
    else if (strcmp(ParamName, "EmailAddress") == 0)
    {
        ret = 0;
    }
    else
    {
        CcspTraceWarning(("%s::Unknown ParamName :%s\n", __FUNCTION__, ParamName));
        ret =  0;
    }
    return ret;
}

/**********************************************************************

    caller:     owner of this object

    prototype:

        BOOL ServiceProviderInfo_SetParamStringValue(ANSC_HANDLE hInsContext, char* ParamName, char* pString);

    description:

        This function is called to set String parameter value;

    argument:   ANSC_HANDLE                 hInsContext,
                The instance handle;

                char*                       ParamName,
                The parameter name;

                char*                       pValue,
                The buffer to set value;

    return:     TRUE if succeeded.

**********************************************************************/
BOOL ServiceProviderInfo_SetParamStringValue(ANSC_HANDLE hInsContext, char* ParamName, char* pString)
{
    BOOL ret = FALSE;
    if (strcmp(ParamName, "Name") == 0)
    {
        ret = TRUE;
    }
    else if (strcmp(ParamName, "ContactPhoneNumber") == 0)
    {
        ret = TRUE;
    }
    else if (strcmp(ParamName, "URL") == 0)
    {
        ret = TRUE;
    }
    else if (strcmp(ParamName, "EmailAddress") == 0)
    {
        ret = TRUE;
    }
    return ret;
}

/**********************************************************************

    caller:     owner of this object

    prototype:

        LONG MGCP_GetParamStringValue(ANSC_HANDLE hInsContext, char* ParamName, char* pValue, ULONG* pUlSize);

    description:

        This function is called to retrieve String parameter value;

    argument:   ANSC_HANDLE                 hInsContext,
                The instance handle;

                char*                       ParamName
                The parameter name;

                char*                       pValue,
                The buffer of returned ULONG value;

                ULONG*                      pUlSize
                The length of returned buffer value;

    return:     0 if succeeded.
                1 if not enough buffer size
                -1 if not supported

**********************************************************************/

LONG MGCP_GetParamStringValue(ANSC_HANDLE hInsContext, char* ParamName, char* pValue, ULONG* pUlSize)
{
    ULONG ret = 1;
    DML_PROFILE_CTRL_T* pVoiceProfile = (DML_PROFILE_CTRL_T *) hInsContext;
    if(pVoiceProfile == NULL)
    {
        CcspTraceError(("%s:%d:: Invalid object \n", __FUNCTION__, __LINE__));
        return ret;
    }

    TELCOVOICEMGR_DML_DATA* pTelcoVoiceMgrDmlData = TelcoVoiceMgrDmlGetDataLocked();
    if(pTelcoVoiceMgrDmlData == NULL)
    {
        CcspTraceError(("%s:%d:: TelcoVoiceMgrDmlGetDataLocked: Failed\n", __FUNCTION__, __LINE__));
        return ret;
    }

    PTELCOVOICEMGR_DML_PROFILE pDmlVoiceProfile = &(pVoiceProfile->dml);
    if(pDmlVoiceProfile == NULL )
    {
        TelcoVoiceMgrDmlGetDataRelease(pTelcoVoiceMgrDmlData);
        CcspTraceError(("%s:%d:: pDmlVoiceProfile: NULL\n", __FUNCTION__, __LINE__));
        return ret;
    }
    
    PTELCOVOICEMGR_DML_MGCP pDmlMGCP = &(pDmlVoiceProfile->MGCPObj);
    if(pDmlMGCP != NULL)
    {
        if (strcmp(ParamName, "CallAgent1") == 0)
        {
            AnscCopyString(pValue, pDmlMGCP->CallAgent1);
            ret = 0;
        }
        else if (strcmp(ParamName, "CallAgent2") == 0)
        {
            AnscCopyString(pValue, pDmlMGCP->CallAgent1);
            ret = 0;
        }
        else if (strcmp(ParamName, "RegisterMode") == 0)
        {
            if (MGCP_REGISTERMODE_WILDCARD == pDmlMGCP->RegisterMode)
            {
                AnscCopyString(pValue, "Wildcard");
                ret = 0;
            }
            else if (MGCP_REGISTERMODE_INDIVIDUAL == pDmlMGCP->RegisterMode)
            {
                AnscCopyString(pValue, "Individual");
                ret = 0;
            }
        }
        else if (strcmp(ParamName, "Domain") == 0)
        {
            AnscCopyString(pValue, pDmlMGCP->Domain);
            ret = 0;
        }
        else if (strcmp(ParamName, "User") == 0)
        {
            AnscCopyString(pValue, pDmlMGCP->User);
            ret = 0;
        }
        else
        {
            CcspTraceWarning(("%s::Unknown ParamName :%s\n", __FUNCTION__, ParamName));
        }
    }
    TelcoVoiceMgrDmlGetDataRelease(pTelcoVoiceMgrDmlData);
    return ret;
}


/**********************************************************************

    caller:     owner of this object

    prototype:

        BOOL  MGCP_GetParamIntValue(ANSC_HANDLE hInsContext, char* ParamName, int* pInt)

    description:

        This function is called to retrieve int parameter value;

    argument:   ANSC_HANDLE                 hInsContext,
                The instance handle;

                char*                       ParamName,
                The parameter name;

                int*                        pInt
                The value returned

    return:     TRUE if succeeded.

**********************************************************************/
BOOL MGCP_GetParamIntValue(ANSC_HANDLE hInsContext, char* ParamName, int* pInt)
{
    BOOL ret = FALSE;
    DML_PROFILE_CTRL_T* pVoiceProfile = (DML_PROFILE_CTRL_T *) hInsContext;
    if(pVoiceProfile == NULL)
    {
        CcspTraceError(("%s:%d:: Invalid object \n", __FUNCTION__, __LINE__));
        return ret;
    }

    TELCOVOICEMGR_DML_DATA* pTelcoVoiceMgrDmlData = TelcoVoiceMgrDmlGetDataLocked();
    if(pTelcoVoiceMgrDmlData == NULL)
    {
        CcspTraceError(("%s:%d:: TelcoVoiceMgrDmlGetDataLocked: Failed\n", __FUNCTION__, __LINE__));
        return ret;
    }

    PTELCOVOICEMGR_DML_PROFILE pDmlVoiceProfile = &(pVoiceProfile->dml);
    if(pDmlVoiceProfile == NULL )
    {
        TelcoVoiceMgrDmlGetDataRelease(pTelcoVoiceMgrDmlData);
        CcspTraceError(("%s:%d:: pDmlVoiceProfile: NULL\n", __FUNCTION__, __LINE__));
        return ret;
    }
    
    PTELCOVOICEMGR_DML_MGCP pDmlMGCP = &(pDmlVoiceProfile->MGCPObj);
    if(pDmlMGCP != NULL)
    {

        if (strcmp(ParamName, "VLANIDMark") == 0)
        {
            *pInt = pDmlMGCP->VLANIDMark;
            ret = TRUE;
        }
        else if (strcmp(ParamName, "EthernetPriorityMark") == 0)
        {
            *pInt = pDmlMGCP->EthernetPriorityMark;
            ret = TRUE;
        }
        else if (strcmp(ParamName, "CallAgentPort1") == 0)
        {
            *pInt = pDmlMGCP->CallAgentPort1;
            ret = TRUE;
        }
        else if (strcmp(ParamName, "CallAgentPort2") == 0)
        {
            *pInt = pDmlMGCP->CallAgentPort2;
            ret = TRUE;
        }
        else if (strcmp(ParamName, "RetranIntervalTimer") == 0)
        {
            *pInt = pDmlMGCP->RetranIntervalTimer;
            ret = TRUE;
        }
        else if (strcmp(ParamName, "MaxRetranCount") == 0)
        {
            *pInt = pDmlMGCP->MaxRetranCount;
            ret = TRUE;
        }
        else if (strcmp(ParamName, "LocalPort") == 0)
        {
            *pInt = pDmlMGCP->LocalPort;
            ret = TRUE;
        }
        else if (strcmp(ParamName, "DSCPMark") == 0)
        {
            *pInt = pDmlMGCP->DSCPMark;
            ret = TRUE;
        }
        else
        {
            CcspTraceWarning(("%s::Unknown ParamName :%s\n", __FUNCTION__, ParamName));
        }
    }
    TelcoVoiceMgrDmlGetDataRelease(pTelcoVoiceMgrDmlData);
    return ret;
}

/**********************************************************************

    caller:     owner of this object

    prototype:

        BOOL MGCP_SetParamStringValue(ANSC_HANDLE hInsContext, char* ParamName, char* pString);

    description:

        This function is called to set String parameter value;

    argument:   ANSC_HANDLE                 hInsContext,
                The instance handle;

                char*                       ParamName,
                The parameter name;

                char*                       pValue,
                The buffer to set value;

    return:     TRUE if succeeded.

**********************************************************************/
BOOL MGCP_SetParamStringValue(ANSC_HANDLE hInsContext, char* ParamName, char* pString)
{
    BOOL ret = FALSE;
    DML_PROFILE_CTRL_T* pVoiceProfile = (DML_PROFILE_CTRL_T *) hInsContext;
    if(pVoiceProfile == NULL)
    {
        CcspTraceError(("%s:%d:: Invalid object \n", __FUNCTION__, __LINE__));
        return ret;
    }

    TELCOVOICEMGR_DML_DATA* pTelcoVoiceMgrDmlData = TelcoVoiceMgrDmlGetDataLocked();
    if(pTelcoVoiceMgrDmlData == NULL)
    {
        CcspTraceError(("%s:%d:: TelcoVoiceMgrDmlGetDataLocked: Failed\n", __FUNCTION__, __LINE__));
        return ret;
    }

    PTELCOVOICEMGR_DML_PROFILE pDmlVoiceProfile = &(pVoiceProfile->dml);
    if(pDmlVoiceProfile == NULL )
    {
        TelcoVoiceMgrDmlGetDataRelease(pTelcoVoiceMgrDmlData);
        CcspTraceError(("%s:%d:: pDmlVoiceProfile: NULL\n", __FUNCTION__, __LINE__));
        return ret;
    }
    
    PTELCOVOICEMGR_DML_MGCP pDmlMGCP = &(pDmlVoiceProfile->MGCPObj);
    if(pDmlMGCP != NULL)
    {
        if (strcmp(ParamName, "CallAgent1") == 0)
        {
            ret = TRUE;
        }
        else if (strcmp(ParamName, "CallAgent2") == 0)
        {
            ret = TRUE;
        }
        else if (strcmp(ParamName, "RegisterMode") == 0)
        {
            ret = TRUE;
        }
        else if (strcmp(ParamName, "Domain") == 0)
        {
            ret = TRUE;
        }
        else if (strcmp(ParamName, "User") == 0)
        {
            ret = TRUE;
        }
        else
        {
            CcspTraceWarning(("%s::Unknown ParamName :%s\n", __FUNCTION__, ParamName));
        } 
    }
    TelcoVoiceMgrDmlGetDataRelease(pTelcoVoiceMgrDmlData);
    return ret;
}

