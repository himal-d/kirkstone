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
#include "telcovoicemgr_dml_line_v1.h"
#include "telcovoicemgr_services_apis_v1.h"
#include "telcovoicemgr_dml_hal.h"
#include "ccsp_trace.h"
#include "ccsp_syslog.h"

/***********************************************************************

 APIs for Object:

    Services.VoiceService.{i}.VoiceProfile.{i}.Line.{i}.

    *  Line_IsUpdated
    *  Line_Synchronize
    *  Line_GetParamStringValue
    *  Line_SetParamStringValue
    *  Line_GetParamUlongValue
    *  Line_GetEntryCount
    *  Line_GetEntry
    *  Line_Validate
    *  Line_Commit
    *  Line_Rollback


***********************************************************************/
/**********************************************************************

    caller:     owner of this object

    prototype:

                ULONG Line_IsUpdated(ANSC_HANDLE hInsContext);

    description:

               This function is called to check if Line updated .

    argument:   ANSC_HANDLE      hInsContext, 
               The instance handle;

    return:     The status of the operation.

**********************************************************************/
    

BOOL Line_IsUpdated(ANSC_HANDLE hInsContext)
{
    BOOL        bIsUpdated = TRUE;

    return bIsUpdated;
}

/**********************************************************************

    caller:     owner of this object

    prototype:

                ULONG EventSubscribe_IsUpdated(ANSC_HANDLE hInsContext);

    description:

               This function is called to check if EventSubscribe updated .

    argument:   ANSC_HANDLE      hInsContext, 
               The instance handle;

    return:     The status of the operation.

**********************************************************************/
    

BOOL EventSubscribe_IsUpdated(ANSC_HANDLE hInsContext)
{
    BOOL        bIsUpdated = TRUE;

    return bIsUpdated;
}
/**********************************************************************

    caller:     owner of this object

    prototype:

                ULONG Event_IsUpdated(ANSC_HANDLE hInsContext);

    description:

               This function is called to check if Event updated .

    argument:   ANSC_HANDLE      hInsContext, 
               The instance handle;

    return:     The status of the operation.

**********************************************************************/
    

BOOL Event_IsUpdated(ANSC_HANDLE hInsContext)
{
    BOOL        bIsUpdated = TRUE;

    return bIsUpdated;
}

/**********************************************************************

    caller:     owner of this object

    prototype:

                ULONG Description_IsUpdated(ANSC_HANDLE hInsContext);

    description:

               This function is called to check if Description updated .

    argument:   ANSC_HANDLE      hInsContext, 
               The instance handle;

    return:     The status of the operation.

**********************************************************************/
    

BOOL Description_IsUpdated(ANSC_HANDLE hInsContext)
{
    BOOL        bIsUpdated = TRUE;

    return bIsUpdated;
}

/**********************************************************************

    caller:     owner of this object

    prototype:

                ULONG Pattern_IsUpdated(ANSC_HANDLE hInsContext);

    description:

               This function is called to check if Pattern updated .

    argument:   ANSC_HANDLE      hInsContext, 
               The instance handle;

    return:     The status of the operation.

**********************************************************************/
    

BOOL Pattern_IsUpdated(ANSC_HANDLE hInsContext)
{
    BOOL        bIsUpdated = TRUE;

    return bIsUpdated;
}

/**********************************************************************

    caller:     owner of this object

    prototype:

                ULONG List_IsUpdated(ANSC_HANDLE hInsContext);

    description:

               This function is called to check if List updated .

    argument:   ANSC_HANDLE      hInsContext, 
               The instance handle;

    return:     The status of the operation.

**********************************************************************/
    

BOOL List_IsUpdated(ANSC_HANDLE hInsContext)
{
    BOOL        bIsUpdated = TRUE;

    return bIsUpdated;
}

/**********************************************************************

    caller:     owner of this object

    prototype:

                ULONG Session_IsUpdated(ANSC_HANDLE hInsContext);

    description:

               This function is called to check if Session updated .

    argument:   ANSC_HANDLE      hInsContext, 
               The instance handle;

    return:     The status of the operation.

**********************************************************************/
    

BOOL Session_IsUpdated(ANSC_HANDLE hInsContext)
{
    BOOL        bIsUpdated = TRUE;

    return bIsUpdated;
}


/**********************************************************************

    caller:     owner of this object

    prototype:

                ULONG Line_Synchronize(ANSC_HANDLE hInsContext);

    description:

               This function is called to synchronize Line data.

    argument:   ANSC_HANDLE      hInsContext, 
               The instance handle;

    return:     The status of the operation.

**********************************************************************/
ULONG Line_Synchronize(ANSC_HANDLE hInsContext)
{
    ANSC_STATUS            returnStatus   = ANSC_STATUS_SUCCESS;
    return returnStatus;
}


/**********************************************************************

    caller:     owner of this object

    prototype:

                ULONG EventSubscribe_Synchronize(ANSC_HANDLE hInsContext);

    description:

               This function is called to synchronize EventSubscribe data.

    argument:   ANSC_HANDLE      hInsContext, 
               The instance handle;

    return:     The status of the operation.

**********************************************************************/
ULONG EventSubscribe_Synchronize(ANSC_HANDLE hInsContext)
{
    ANSC_STATUS            returnStatus   = ANSC_STATUS_SUCCESS;
    return returnStatus;
}
/**********************************************************************

    caller:     owner of this object

    prototype:

                ULONG Description_Synchronize(ANSC_HANDLE hInsContext);

    description:

               This function is called to synchronize Description data.

    argument:   ANSC_HANDLE      hInsContext, 
               The instance handle;

    return:     The status of the operation.

**********************************************************************/
ULONG Description_Synchronize(ANSC_HANDLE hInsContext)
{
    ANSC_STATUS            returnStatus   = ANSC_STATUS_SUCCESS;
    return returnStatus;
}
/**********************************************************************

    caller:     owner of this object

    prototype:

                ULONG Event_Synchronize(ANSC_HANDLE hInsContext);

    description:

               This function is called to synchronize Event data.

    argument:   ANSC_HANDLE      hInsContext, 
               The instance handle;

    return:     The status of the operation.

**********************************************************************/
ULONG Event_Synchronize(ANSC_HANDLE hInsContext)
{
    ANSC_STATUS            returnStatus   = ANSC_STATUS_SUCCESS;
    return returnStatus;
}
/**********************************************************************

    caller:     owner of this object

    prototype:

                ULONG Pattern_Synchronize(ANSC_HANDLE hInsContext);

    description:

               This function is called to synchronize Pattern data.

    argument:   ANSC_HANDLE      hInsContext, 
               The instance handle;

    return:     The status of the operation.

**********************************************************************/
ULONG Pattern_Synchronize(ANSC_HANDLE hInsContext)
{
    ANSC_STATUS            returnStatus   = ANSC_STATUS_SUCCESS;
    return returnStatus;
}

/**********************************************************************

    caller:     owner of this object

    prototype:

                ULONG List_Synchronize(ANSC_HANDLE hInsContext);

    description:

               This function is called to synchronize List data.

    argument:   ANSC_HANDLE      hInsContext, 
               The instance handle;

    return:     The status of the operation.

**********************************************************************/
ULONG List_Synchronize(ANSC_HANDLE hInsContext)
{
    ANSC_STATUS            returnStatus   = ANSC_STATUS_SUCCESS;
    return returnStatus;
}

/**********************************************************************

    caller:     owner of this object

    prototype:

                ULONG Session_Synchronize(ANSC_HANDLE hInsContext);

    description:

               This function is called to synchronize Session data.

    argument:   ANSC_HANDLE      hInsContext, 
               The instance handle;

    return:     The status of the operation.

**********************************************************************/
ULONG Session_Synchronize(ANSC_HANDLE hInsContext)
{
    ANSC_STATUS            returnStatus   = ANSC_STATUS_SUCCESS;
    return returnStatus;
}

/**********************************************************************

    caller:     owner of this object

    prototype:

        BOOL Line_GetParamStringValue(ANSC_HANDLE hInsContext, char* ParamName, char* pValue, ULONG* pUlSize);

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

   return:     0 if succeeded;
                1 if short of buffer size; (*pUlSize = required size)
                -1 if not supported.

**********************************************************************/
LONG Line_GetParamStringValue(ANSC_HANDLE hInsContext, char* ParamName, char* pValue, ULONG* pUlSize)
{
    DML_LINE_CTRL_T* pTelcoVoiceMgrCtrl = (DML_LINE_CTRL_T*) hInsContext;
    PTELCOVOICEMGR_DML_PROFILE pVoiceProfile = NULL;
    PTELCOVOICEMGR_DML_VOICESERVICE pVoiceService = NULL;
    char    buf[1024] = {0};
    LONG ret = -1;

    CcspTraceWarning(("%s::ParamName:%s\n", __FUNCTION__, ParamName));

    if(pTelcoVoiceMgrCtrl != NULL)
    {
        TELCOVOICEMGR_DML_DATA* pTelcoVoiceMgrDmlData = TelcoVoiceMgrDmlGetDataLocked();
        if(pTelcoVoiceMgrDmlData != NULL)
        {
            TELCOVOICEMGR_DML_LINE* pLine = &(pTelcoVoiceMgrCtrl->dml);
            if (pLine && pValue && pUlSize)
            {
                pVoiceProfile = (PTELCOVOICEMGR_DML_PROFILE) pLine->pParentVoiceProfile;
                if (pVoiceProfile)
                {
                    pVoiceService = pVoiceProfile->pParentVoiceService;
                }
            }

            if (pVoiceService && pVoiceProfile && pLine)
            {
                if (strcmp(ParamName, "DirectoryNumber") == 0)
                {
                    snprintf(buf, sizeof(buf), "%s", pLine->DirectoryNumber);
                    if ( AnscSizeOfString(buf) < *pUlSize)
                    {
                        AnscCopyString(pValue, buf);
                        ret = 0;
                    }
                    else
                    {
                        *pUlSize = AnscSizeOfString(pValue);
                        ret = 1;
                    }
                }
                else if (strcmp(ParamName, "X_RDK_OutboundProxyAddresses") == 0)
                {
                    //Fetch status from voice stack
                    hal_param_t req_param;
                    memset(&req_param, 0, sizeof(req_param));
                    snprintf(req_param.name, sizeof(req_param.name), TELCOVOICE_QUERY_VOICEPROFILE_LINE"%s",
                              pVoiceService->InstanceNumber, pVoiceProfile->InstanceNumber, pLine->InstanceNumber,"X_RDK_OutboundProxyAddresses");
                    if (ANSC_STATUS_SUCCESS == TelcoVoiceHal_GetSingleParameter(&req_param))
                    {
                        snprintf(buf, sizeof(buf), "%s",  req_param.value);
                        if ( AnscSizeOfString(buf) < *pUlSize)
                        {
                            AnscCopyString(pValue, buf);
                            ret = 0;
                        }
                        else
                        {
                            *pUlSize = AnscSizeOfString(pValue);
                            ret = 1;
                        }
                    }
                    else
                    {
                        CcspTraceError(("%s:%d:: X_RDK_OutbandProxyAddresses:get failed \n", __FUNCTION__, __LINE__));
                        *pUlSize = AnscSizeOfString(pValue);
                        ret = 1;
                    }
                }
                else if (strcmp(ParamName, "Alias") == 0)
                {
                    snprintf(buf, sizeof(buf), "%s", pLine->Alias);
                    if ( AnscSizeOfString(buf) < *pUlSize)
                    {
                        AnscCopyString(pValue, buf);
                        ret = 0;
                    }
                    else
                    {
                        *pUlSize = AnscSizeOfString(pValue);
                        ret = 1;
                    }
                }
                else if (strcmp(ParamName, "PhyReferenceList") == 0)
                {
                    snprintf(buf, sizeof(buf), "%s", pLine->PhyReferenceList);
                    if ( AnscSizeOfString(buf) < *pUlSize)
                    {
                        AnscCopyString(pValue, buf);
                        ret = 0;
                    }
                    else
                    {
                        *pUlSize = AnscSizeOfString(pValue);
                        ret = 1;
                    }
                }
                else
                {
                    CcspTraceWarning(("%s::Unknown ParamName:%s\n", __FUNCTION__, ParamName));
                    ret = 1;
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

        BOOL Line_SetParamStringValue(ANSC_HANDLE hInsContext, char* ParamName, char* pString);

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

BOOL Line_SetParamStringValue(ANSC_HANDLE hInsContext, char* ParamName, char* pString)
{
    DML_LINE_CTRL_T* pTelcoVoiceMgrCtrl = (DML_LINE_CTRL_T*) hInsContext;
    PTELCOVOICEMGR_DML_PROFILE pVoiceProfile = NULL;
    PTELCOVOICEMGR_DML_VOICESERVICE pVoiceService = NULL;
    BOOL bStatus = TRUE;
    ULONG uVsIndex = 0;
    ULONG uVpIndex = 0;
    ULONG uLineIndex = 0;

    CcspTraceWarning(("%s::ParamName:%s\n", __FUNCTION__, ParamName));
    if(pTelcoVoiceMgrCtrl != NULL)
    {
        TELCOVOICEMGR_DML_DATA* pTelcoVoiceMgrDmlData = TelcoVoiceMgrDmlGetDataLocked();
        if(pTelcoVoiceMgrDmlData != NULL)
        {
            TELCOVOICEMGR_DML_LINE* pLine = &(pTelcoVoiceMgrCtrl->dml);
            if (pLine && pString)
            {
                pVoiceProfile = (PTELCOVOICEMGR_DML_PROFILE) pLine->pParentVoiceProfile;
                if (pVoiceProfile)
                {
                    pVoiceService = pVoiceProfile->pParentVoiceService;
                }
            }

            if (pVoiceService && pVoiceProfile && pLine)
            {
                uVsIndex = pVoiceService->InstanceNumber;
                uVpIndex = pVoiceProfile->InstanceNumber;
                uLineIndex = pLine->InstanceNumber;
                TelcoVoiceMgrDmlGetDataRelease(pTelcoVoiceMgrDmlData);
                if (strcmp(ParamName, "DirectoryNumber") == 0)
                {
                    if(TelcoVoiceMgrDmlSetDirectoryNumber(uVsIndex, uVpIndex, uLineIndex, pString) == ANSC_STATUS_SUCCESS)
                    {
                        TELCOVOICEMGR_DML_DATA* pTelcoVoiceMgrDmlData = TelcoVoiceMgrDmlGetDataLocked();
                        if(pTelcoVoiceMgrDmlData != NULL)
                        {
                            AnscCopyString(pLine->DirectoryNumber, pString);
                            TelcoVoiceMgrDmlGetDataRelease(pTelcoVoiceMgrDmlData);
                            return TRUE;
                        }
                    }
                    else
                    {
                        bStatus =  FALSE;
                    }
                }
                else
                {
                    CcspTraceWarning(("%s::Unknown ParamName:%s\n", __FUNCTION__, ParamName));
                    bStatus =  FALSE;
                }
            }
            else
            {
                TelcoVoiceMgrDmlGetDataRelease(pTelcoVoiceMgrDmlData);
            }
        }
    }

    return bStatus;
}

/**********************************************************************

    caller:     owner of this object

    prototype:

        BOOL Line_GetParamUlongValue(ANSC_HANDLE hInsContext, char* ParamName, ULONG* pValue);

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
BOOL Line_GetParamUlongValue(ANSC_HANDLE hInsContext, char* ParamName, ULONG* pValue)
{
    DML_LINE_CTRL_T* pTelcoVoiceMgrCtrl = (DML_LINE_CTRL_T*) hInsContext;
    PTELCOVOICEMGR_DML_PROFILE pVoiceProfile = NULL;
    PTELCOVOICEMGR_DML_VOICESERVICE pVoiceService = NULL;
    ULONG ret = 1;
    ULONG uVsIndex = 0;
    ULONG uVpIndex = 0;
    ULONG uVlIndex = 0;
    TELCOVOICEMGR_CALL_STATE_ENUM  callState = VOICE_CALL_STATE_IDLE;
    TELCOVOICEMGR_LINE_STATUS_ENUM lineStatus = VOICE_LINE_STATE_DISABLED;

    CcspTraceWarning(("%s::ParamName:%s\n", __FUNCTION__, ParamName));

    if(pTelcoVoiceMgrCtrl != NULL)
    {
        TELCOVOICEMGR_DML_DATA* pTelcoVoiceMgrDmlData = TelcoVoiceMgrDmlGetDataLocked();
        if(pTelcoVoiceMgrDmlData != NULL)
        {
            TELCOVOICEMGR_DML_LINE* pLine = &(pTelcoVoiceMgrCtrl->dml);
            if (pLine && pValue)
            {
                pVoiceProfile = (PTELCOVOICEMGR_DML_PROFILE) pLine->pParentVoiceProfile;
                if (pVoiceProfile)
                {
                    pVoiceService = pVoiceProfile->pParentVoiceService;
                }
            }

            if (pVoiceService && pVoiceProfile && pLine)
            {
                uVsIndex = pVoiceService->InstanceNumber;
                uVpIndex = pVoiceProfile->InstanceNumber;
                uVlIndex = pLine->InstanceNumber;
                TelcoVoiceMgrDmlGetDataRelease(pTelcoVoiceMgrDmlData);

                if (strcmp(ParamName, "CallState") == 0)
                {
                    if(ANSC_STATUS_SUCCESS == TelcoVoiceMgrDmlGetLineCallState(uVsIndex, uVpIndex, uVlIndex, &callState))
                    {
                        TELCOVOICEMGR_DML_DATA* pTelcoVoiceMgrDmlData = TelcoVoiceMgrDmlGetDataLocked();
                        if(pTelcoVoiceMgrDmlData != NULL)
                        {
                            pLine->CallState = callState;
                            *pValue = pLine->CallState;
                            TelcoVoiceMgrDmlGetDataRelease(pTelcoVoiceMgrDmlData);
                            ret = TRUE;
                        }
                    }
                }
                else if (strcmp(ParamName, "Enable") == 0)
                {
                    *pValue = pLine->Enable;
                    ret =TRUE;
                }
                else if (strcmp(ParamName, "Status") == 0)
                {
                    if(ANSC_STATUS_SUCCESS == TelcoVoiceMgrDmlGetLineStatus(uVsIndex, uVpIndex, uVlIndex, &lineStatus))
                    {
                        TELCOVOICEMGR_DML_DATA* pTelcoVoiceMgrDmlData = TelcoVoiceMgrDmlGetDataLocked();
                        if(pTelcoVoiceMgrDmlData != NULL)
                        {
                            pLine->Status = lineStatus;
                            *pValue = pLine->Status;
                            TelcoVoiceMgrDmlGetDataRelease(pTelcoVoiceMgrDmlData);
                            ret = TRUE;
                        }
                    }
                }
                else if (strcmp(ParamName, "RingVolumeStatus") == 0)
                {
                    *pValue = pLine->RingVolumeStatus;
                    ret = TRUE;
                }
                else
                {
                    CcspTraceWarning(("%s::Unknown ParamName:%s\n", __FUNCTION__, ParamName));
                    ret = FALSE;
                }
            }
            else
            {
                CcspTraceWarning(("%s::Invalid Object\n", __FUNCTION__));
                TelcoVoiceMgrDmlGetDataRelease(pTelcoVoiceMgrDmlData);
            }
        }
    }

    return ret;
}

/**********************************************************************

    caller:     owner of this object

    prototype:

        BOOL Line_SetParamUlongValue(ANSC_HANDLE hInsContext, char* ParamName, ULONG uValue);

    description:

        This function is called to retrieve Ulong parameter value;

    argument:   ANSC_HANDLE                 hInsContext,
                The instance handle;

                char*                       ParamName,
                The parameter name;

                ULONG                       uValue
                The value returned

    return:     TRUE if succeeded.

**********************************************************************/
BOOL Line_SetParamUlongValue(ANSC_HANDLE hInsContext, char* ParamName, ULONG uValue)
{
    DML_LINE_CTRL_T* pTelcoVoiceMgrCtrl = (DML_LINE_CTRL_T*) hInsContext;
    PTELCOVOICEMGR_DML_PROFILE pVoiceProfile = NULL;
    PTELCOVOICEMGR_DML_VOICESERVICE pVoiceService = NULL;
    BOOL bStatus = TRUE;
    ULONG uVsIndex = 0;
    ULONG uVpIndex = 0;
    ULONG uLineIndex = 0;

    if(pTelcoVoiceMgrCtrl != NULL)
    {
        TELCOVOICEMGR_DML_DATA* pTelcoVoiceMgrDmlData = TelcoVoiceMgrDmlGetDataLocked();
        if(pTelcoVoiceMgrDmlData != NULL)
        {
            TELCOVOICEMGR_DML_LINE* pLine = &(pTelcoVoiceMgrCtrl->dml);
            if (pLine)
            {
                pVoiceProfile = (PTELCOVOICEMGR_DML_PROFILE) pLine->pParentVoiceProfile;
                if (pVoiceProfile)
                {
                    pVoiceService = pVoiceProfile->pParentVoiceService;
                }
            }
            if (pVoiceService && pVoiceProfile && pLine)
            {
                uVsIndex = pVoiceService->InstanceNumber;
                uVpIndex = pVoiceProfile->InstanceNumber;
                uLineIndex = pLine->InstanceNumber;
                TelcoVoiceMgrDmlGetDataRelease(pTelcoVoiceMgrDmlData);
                if (strcmp(ParamName, "Enable") == 0)
                {
                    if(ANSC_STATUS_SUCCESS == TelcoVoiceMgrDmlSetLineEnable(uVsIndex, uVpIndex, uLineIndex, uValue))
                    {
                        CcspTraceWarning(("%s::ParamName:%s Val : %d set succeeded (%d, %d, %d)\n", __FUNCTION__, ParamName, uValue, uVsIndex, uVpIndex, uLineIndex));
                        TELCOVOICEMGR_DML_DATA* pTelcoVoiceMgrDmlData = TelcoVoiceMgrDmlGetDataLocked();
                        if(pTelcoVoiceMgrDmlData != NULL)
                        {
                            pLine->Enable = uValue;
                            TelcoVoiceMgrDmlGetDataRelease(pTelcoVoiceMgrDmlData);
                            return TRUE;
                        }
                    }
                }
                else
                {
                    CcspTraceWarning(("%s::Unknown ParamName:%s\n", __FUNCTION__, ParamName));
                    bStatus =  FALSE;
                }
            }
            else
            {
                TelcoVoiceMgrDmlGetDataRelease(pTelcoVoiceMgrDmlData);
            }
        }
    }

    return bStatus;
}

/**********************************************************************

    caller:     owner of this object

    prototype:

    BOOL Line_GetParamBoolValue(ANSC_HANDLE hInsContext, char* ParamName, BOOL* pBool);

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
BOOL Line_GetParamBoolValue(ANSC_HANDLE hInsContext, char* ParamName, BOOL* pBool)
{
    DML_LINE_CTRL_T* pTelcoVoiceMgrCtrl = (DML_LINE_CTRL_T*) hInsContext;
    BOOL ret = FALSE;

    if(pTelcoVoiceMgrCtrl == NULL)
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

    TELCOVOICEMGR_DML_LINE* pLine = &(pTelcoVoiceMgrCtrl->dml);
    if(pLine == NULL )
    {
        TelcoVoiceMgrDmlGetDataRelease(pTelcoVoiceMgrDmlData);
        CcspTraceError(("%s:%d:: pLine: NULL\n", __FUNCTION__, __LINE__));
        return ret;
    }
    else
    {
        if (strcmp(ParamName, "RingMuteStatus") == 0)
        {
            *pBool = pLine->RingMuteStatus;
            ret = TRUE;
        }
        else
        {
            CcspTraceWarning(("%s::Unknown ParamName:%s\n", __FUNCTION__, ParamName));
            ret = FALSE;
        }
        TelcoVoiceMgrDmlGetDataRelease(pTelcoVoiceMgrDmlData);
    }
    

    return ret;
}

/**********************************************************************

    caller:     owner of this object

    prototype:

        ULONG Line_GetEntryCount(ANSC_HANDLE hInsContext);

    description:

        This function is called to retrieve the count of the table.

    argument:   ANSC_HANDLE                 hInsContext,
                The instance handle;

    return:     The count of the table

**********************************************************************/
ULONG Line_GetEntryCount(ANSC_HANDLE hInsContext)
{
    ULONG count = 0;
    PTELCOVOICEMGR_DML_PROFILE       pDmlVoiceProfile    = NULL;
    DML_PROFILE_CTRL_T* pVoiceProfile = (DML_PROFILE_CTRL_T*) hInsContext;

    if(pVoiceProfile != NULL)
    {
        TELCOVOICEMGR_DML_DATA* pTelcoVoiceMgrDmlData = TelcoVoiceMgrDmlGetDataLocked();
        if(pTelcoVoiceMgrDmlData != NULL)
        {
            pDmlVoiceProfile = &(pVoiceProfile->dml);   
            count = pDmlVoiceProfile->LineList.ulQuantity;
            TelcoVoiceMgrDmlGetDataRelease(pTelcoVoiceMgrDmlData);
        }
    }

    return count;
}
/**********************************************************************
    VoiceService.{i}.VoiceProfile.{i}.Line.{i}.Codec.List.{i}.
    caller:     owner of this object

    prototype:

        ULONG List_GetEntryCount(ANSC_HANDLE hInsContext);

    description:

        This function is called to retrieve the count of the table.

    argument:   ANSC_HANDLE                 hInsContext,
                The instance handle;

    return:     The count of the table

**********************************************************************/
ULONG List_GetEntryCount(ANSC_HANDLE hInsContext)
{
    ULONG count = 0;
    PTELCOVOICEMGR_DML_LINE          pDmlLine    = NULL;
    DML_LINE_CTRL_T* pTelcoVoiceMgrCtrl = (DML_LINE_CTRL_T*) hInsContext;

    if(pTelcoVoiceMgrCtrl != NULL)
    {
        TELCOVOICEMGR_DML_DATA* pTelcoVoiceMgrDmlData = TelcoVoiceMgrDmlGetDataLocked();
        if(pTelcoVoiceMgrDmlData != NULL)
        {
            pDmlLine = &(pTelcoVoiceMgrCtrl->dml);
            count = pDmlLine->LineCodecObj.LineCodecList.ulQuantity;
            TelcoVoiceMgrDmlGetDataRelease(pTelcoVoiceMgrDmlData);
        }
    }

    return count;
}

/**********************************************************************
    VoiceService.{i}.VoiceProfile.{i}.Line.{i}.Session.{i}.
    caller:     owner of this object

    prototype:

        ULONG Session_GetEntryCount(ANSC_HANDLE hInsContext);

    description:

        This function is called to retrieve the count of the table.

    argument:   ANSC_HANDLE                 hInsContext,
                The instance handle;

    return:     The count of the table

**********************************************************************/
ULONG Session_GetEntryCount(ANSC_HANDLE hInsContext)
{
    ULONG count = 0;
    PTELCOVOICEMGR_DML_LINE          pDmlLine    = NULL;
    DML_LINE_CTRL_T* pTelcoVoiceMgrCtrl = (DML_LINE_CTRL_T*) hInsContext;

    if(pTelcoVoiceMgrCtrl != NULL)
    {
        TELCOVOICEMGR_DML_DATA* pTelcoVoiceMgrDmlData = TelcoVoiceMgrDmlGetDataLocked();
        if(pTelcoVoiceMgrDmlData != NULL)
        {
            pDmlLine = &(pTelcoVoiceMgrCtrl->dml);
            count = pDmlLine->LineSessionList.ulQuantity;
            TelcoVoiceMgrDmlGetDataRelease(pTelcoVoiceMgrDmlData);
        }
    }

    return count;
}
/**********************************************************************
    VoiceService.{i}.VoiceProfile.{i}.Line.{i}.SIP.EventSubscribe.{i}.
    caller:     owner of this object

    prototype:

        ULONG EventSubscribe_GetEntryCount(ANSC_HANDLE hInsContext);

    description:

        This function is called to retrieve the count of the table.

    argument:   ANSC_HANDLE                 hInsContext,
                The instance handle;

    return:     The count of the table

**********************************************************************/
ULONG EventSubscribe_GetEntryCount(ANSC_HANDLE hInsContext)
{
    ULONG count = 0;
    PTELCOVOICEMGR_DML_LINE          pDmlLine    = NULL;
    DML_LINE_CTRL_T* pTelcoVoiceMgrCtrl = (DML_LINE_CTRL_T*) hInsContext;

    if(pTelcoVoiceMgrCtrl != NULL)
    {
        TELCOVOICEMGR_DML_DATA* pTelcoVoiceMgrDmlData = TelcoVoiceMgrDmlGetDataLocked();
        if(pTelcoVoiceMgrDmlData != NULL)
        {
            pDmlLine = &(pTelcoVoiceMgrCtrl->dml);
            count = pDmlLine->LineSipObj.LineSipEventSubscribeList.ulQuantity;
            TelcoVoiceMgrDmlGetDataRelease(pTelcoVoiceMgrDmlData);
        }
    }
    return count;
}
/**********************************************************************
    VoiceService.{i}.VoiceProfile.{i}.Line.{i}.Ringer.Event.{i}.
    caller:     owner of this object

    prototype:

        ULONG Event_GetEntryCount(ANSC_HANDLE hInsContext);

    description:

        This function is called to retrieve the count of the table.

    argument:   ANSC_HANDLE                 hInsContext,
                The instance handle;

    return:     The count of the table

**********************************************************************/
ULONG Event_GetEntryCount(ANSC_HANDLE hInsContext)
{

    ULONG count = 0;
    PTELCOVOICEMGR_DML_LINE          pDmlLine    = NULL;
    DML_LINE_CTRL_T* pTelcoVoiceMgrCtrl = (DML_LINE_CTRL_T*) hInsContext;

    if(pTelcoVoiceMgrCtrl != NULL)
    {
        TELCOVOICEMGR_DML_DATA* pTelcoVoiceMgrDmlData = TelcoVoiceMgrDmlGetDataLocked();
        if(pTelcoVoiceMgrDmlData != NULL)
        {
            pDmlLine = &(pTelcoVoiceMgrCtrl->dml);
            count = pDmlLine->LineRingerObj.LineRingerEventList.ulQuantity;
            TelcoVoiceMgrDmlGetDataRelease(pTelcoVoiceMgrDmlData);
        }
    }
    return count;
}
/**********************************************************************
    VoiceService.{i}.VoiceProfile.{i}.Line.{i}.Ringer.Description.{i}.
    caller:     owner of this object

    prototype:

        ULONG Description_GetEntryCount(ANSC_HANDLE hInsContext);

    description:

        This function is called to retrieve the count of the table.

    argument:   ANSC_HANDLE                 hInsContext,
                The instance handle;

    return:     The count of the table

**********************************************************************/
ULONG Description_GetEntryCount(ANSC_HANDLE hInsContext)
{
    ULONG count = 0;
    PTELCOVOICEMGR_DML_LINE          pDmlLine    = NULL;
    DML_LINE_CTRL_T* pTelcoVoiceMgrCtrl = (DML_LINE_CTRL_T*) hInsContext;

    if(pTelcoVoiceMgrCtrl != NULL)
    {
        TELCOVOICEMGR_DML_DATA* pTelcoVoiceMgrDmlData = TelcoVoiceMgrDmlGetDataLocked();
        if(pTelcoVoiceMgrDmlData != NULL)
        {
            pDmlLine = &(pTelcoVoiceMgrCtrl->dml);
            count = pDmlLine->LineRingerObj.LineRingerDescriptionList.ulQuantity;
            TelcoVoiceMgrDmlGetDataRelease(pTelcoVoiceMgrDmlData);
        }
    }
    return count;
}
/**********************************************************************
    VoiceService.{i}.VoiceProfile.{i}.Line.{i}.Ringer.Pattern.{i}.
    caller:     owner of this object

    prototype:

        ULONG Pattern_GetEntryCount(ANSC_HANDLE hInsContext);

    description:

        This function is called to retrieve the count of the table.

    argument:   ANSC_HANDLE                 hInsContext,
                The instance handle;

    return:     The count of the table

**********************************************************************/
ULONG Pattern_GetEntryCount(ANSC_HANDLE hInsContext)
{
    ULONG count = 0;
    PTELCOVOICEMGR_DML_LINE          pDmlLine    = NULL;
    DML_LINE_CTRL_T* pTelcoVoiceMgrCtrl = (DML_LINE_CTRL_T*) hInsContext;

    if(pTelcoVoiceMgrCtrl != NULL)
    {
        TELCOVOICEMGR_DML_DATA* pTelcoVoiceMgrDmlData = TelcoVoiceMgrDmlGetDataLocked();
        if(pTelcoVoiceMgrDmlData != NULL)
        {
            pDmlLine = &(pTelcoVoiceMgrCtrl->dml);
            count = pDmlLine->LineRingerObj.LineRingerPatternList.ulQuantity;
            TelcoVoiceMgrDmlGetDataRelease(pTelcoVoiceMgrDmlData);
        }
    }
    return count;
}
/**********************************************************************

    caller:     owner of this object

    prototype:

        ANSC_HANDLE Line_GetEntry(ANSC_HANDLE hInsContext, ULONG nIndex, ULONG* pInsNumber);

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
ANSC_HANDLE Line_GetEntry(ANSC_HANDLE hInsContext, ULONG  nIndex, ULONG* pInsNumber)
{
    ANSC_HANDLE pDmlEntry = NULL;
    PTELCOVOICEMGR_DML_PROFILE          pDmlVoiceProfile    = NULL;
    DML_PROFILE_CTRL_T* pVoiceProfile = (DML_PROFILE_CTRL_T*) hInsContext;

    if(pVoiceProfile != NULL)
    {
        TELCOVOICEMGR_DML_DATA* pTelcoVoiceMgrDmlData = TelcoVoiceMgrDmlGetDataLocked();
        if(pTelcoVoiceMgrDmlData != NULL)
        {
            pDmlVoiceProfile = &(pVoiceProfile->dml);  
            if(nIndex < pDmlVoiceProfile->LineList.ulQuantity)
            {
                DML_LINE_CTRL_T* pDmlLine = pDmlVoiceProfile->LineList.pdata[nIndex];
                if ( pDmlLine != NULL )
                {
                    *pInsNumber = nIndex + 1;
                    pDmlEntry = (ANSC_HANDLE) pDmlLine;
                }
            }
                TelcoVoiceMgrDmlGetDataRelease(pTelcoVoiceMgrDmlData);
        }
    }

    return pDmlEntry;  /* return the handle */
}
/**********************************************************************
    VoiceService.{i}.VoiceProfile.{i}.Line.{i}.Codec.List.{i}.
    caller:     owner of this object

    prototype:

        ANSC_HANDLE List_GetEntry(ANSC_HANDLE hInsContext, ULONG nIndex, ULONG* pInsNumber);

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
ANSC_HANDLE List_GetEntry(ANSC_HANDLE hInsContext, ULONG  nIndex, ULONG* pInsNumber)
{
    ANSC_HANDLE pDmlEntry = NULL;
    PTELCOVOICEMGR_DML_LINE          pDmlLine    = NULL;
    DML_LINE_CTRL_T* pLine = (DML_PROFILE_CTRL_T*) hInsContext;

    if(pLine != NULL)
    {
        TELCOVOICEMGR_DML_DATA* pTelcoVoiceMgrDmlData = TelcoVoiceMgrDmlGetDataLocked();
        if(pTelcoVoiceMgrDmlData != NULL)
        {
            pDmlLine = &(pLine->dml);
            if(nIndex < pDmlLine->LineCodecObj.LineCodecList.ulQuantity)
            {
                DML_LINE_CODECLIST_CTRL_T* pDmlCodecList = pDmlLine->LineCodecObj.LineCodecList.pdata[nIndex];
                if ( pDmlCodecList != NULL )
                {
                    *pInsNumber = nIndex + 1;
                    pDmlEntry = (ANSC_HANDLE) pDmlCodecList;
                }
            }
            TelcoVoiceMgrDmlGetDataRelease(pTelcoVoiceMgrDmlData);
        }
    }

    return pDmlEntry;  /* return the handle */
}
/**********************************************************************
    VoiceService.{i}.VoiceProfile.{i}.Line.{i}.Session.{i}.
    caller:     owner of this object

    prototype:

        ANSC_HANDLE Session_GetEntry(ANSC_HANDLE hInsContext, ULONG nIndex, ULONG* pInsNumber);

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
ANSC_HANDLE Session_GetEntry(ANSC_HANDLE hInsContext, ULONG  nIndex, ULONG* pInsNumber)
{
    ANSC_HANDLE pDmlEntry = NULL;
    PTELCOVOICEMGR_DML_LINE          pDmlLine    = NULL;
    DML_LINE_CTRL_T* pLine = (DML_PROFILE_CTRL_T*) hInsContext;

    if(pLine != NULL)
    {
        TELCOVOICEMGR_DML_DATA* pTelcoVoiceMgrDmlData = TelcoVoiceMgrDmlGetDataLocked();
        if(pTelcoVoiceMgrDmlData != NULL)
        {
            pDmlLine = &(pLine->dml);
            if(nIndex < pDmlLine->LineSessionList.ulQuantity)
            {
                DML_LINE_SESSION_CTRL_T* pDmlLineSession = pDmlLine->LineSessionList.pdata[nIndex];
                if ( pDmlLineSession != NULL )
                {
                    *pInsNumber = nIndex + 1;
                    pDmlEntry = (ANSC_HANDLE) pDmlLineSession;
                }
            }
            TelcoVoiceMgrDmlGetDataRelease(pTelcoVoiceMgrDmlData);
        }
    }

    return pDmlEntry;  /* return the handle */
}

/**********************************************************************
    VoiceService.{i}.VoiceProfile.{i}.Line.{i}.SIP.EventSubscribe.{i}.
    caller:     owner of this object

    prototype:

        ANSC_HANDLE EventSubscribe_GetEntry(ANSC_HANDLE hInsContext, ULONG nIndex, ULONG* pInsNumber);

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
ANSC_HANDLE EventSubscribe_GetEntry(ANSC_HANDLE hInsContext, ULONG  nIndex, ULONG* pInsNumber)
{
    ANSC_HANDLE pDmlEntry = NULL;
    PTELCOVOICEMGR_DML_LINE          pDmlLine    = NULL;
    DML_LINE_CTRL_T* pLine = (DML_PROFILE_CTRL_T*) hInsContext;

    if(pLine != NULL)
    {
        TELCOVOICEMGR_DML_DATA* pTelcoVoiceMgrDmlData = TelcoVoiceMgrDmlGetDataLocked();
        if(pTelcoVoiceMgrDmlData != NULL)
        {
            pDmlLine = &(pLine->dml);
            if(nIndex < pDmlLine->LineSipObj.LineSipEventSubscribeList.ulQuantity)
            {
                DML_LINE_SESSION_CTRL_T* pDmlLineEventSubscribe = pDmlLine->LineSipObj.LineSipEventSubscribeList.pdata[nIndex];
                if ( pDmlLineEventSubscribe != NULL )
                {
                    *pInsNumber = nIndex + 1;
                    pDmlEntry = (ANSC_HANDLE) pDmlLineEventSubscribe;
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

        ANSC_HANDLE Event_GetEntry(ANSC_HANDLE hInsContext, ULONG nIndex, ULONG* pInsNumber);

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
ANSC_HANDLE Event_GetEntry(ANSC_HANDLE hInsContext, ULONG  nIndex, ULONG* pInsNumber)
{
    ANSC_HANDLE pDmlEntry = NULL;
    PTELCOVOICEMGR_DML_LINE          pDmlLine    = NULL;
    DML_LINE_CTRL_T* pLine = (DML_PROFILE_CTRL_T*) hInsContext;

    if(pLine != NULL)
    {
        TELCOVOICEMGR_DML_DATA* pTelcoVoiceMgrDmlData = TelcoVoiceMgrDmlGetDataLocked();
        if(pTelcoVoiceMgrDmlData != NULL)
        {
            pDmlLine = &(pLine->dml);
            if(nIndex < pDmlLine->LineRingerObj.LineRingerEventList.ulQuantity)
            {
                DML_LINE_SESSION_CTRL_T* pDmlLineRingerEvent = pDmlLine->LineRingerObj.LineRingerEventList.pdata[nIndex];
                if ( pDmlLineRingerEvent != NULL )
                {
                    *pInsNumber = nIndex + 1;
                    pDmlEntry = (ANSC_HANDLE) pDmlLineRingerEvent;
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

        ANSC_HANDLE Description_GetEntry(ANSC_HANDLE hInsContext, ULONG nIndex, ULONG* pInsNumber);

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
ANSC_HANDLE Description_GetEntry(ANSC_HANDLE hInsContext, ULONG  nIndex, ULONG* pInsNumber)
{
    ANSC_HANDLE pDmlEntry = NULL;
    PTELCOVOICEMGR_DML_LINE          pDmlLine    = NULL;
    DML_LINE_CTRL_T* pLine = (DML_PROFILE_CTRL_T*) hInsContext;

    if(pLine != NULL)
    {
        TELCOVOICEMGR_DML_DATA* pTelcoVoiceMgrDmlData = TelcoVoiceMgrDmlGetDataLocked();
        if(pTelcoVoiceMgrDmlData != NULL)
        {
            pDmlLine = &(pLine->dml);
            if(nIndex < pDmlLine->LineRingerObj.LineRingerDescriptionList.ulQuantity)
            {
                DML_LINE_SESSION_CTRL_T* pDmlLineRingerDescription = pDmlLine->LineRingerObj.LineRingerDescriptionList.pdata[nIndex];
                if ( pDmlLineRingerDescription != NULL )
                {
                    *pInsNumber = nIndex + 1;
                    pDmlEntry = (ANSC_HANDLE) pDmlLineRingerDescription;
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

        ANSC_HANDLE Pattern_GetEntry(ANSC_HANDLE hInsContext, ULONG nIndex, ULONG* pInsNumber);

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
ANSC_HANDLE Pattern_GetEntry(ANSC_HANDLE hInsContext, ULONG  nIndex, ULONG* pInsNumber)
{
    ANSC_HANDLE pDmlEntry = NULL;
    PTELCOVOICEMGR_DML_LINE          pDmlLine    = NULL;
    DML_LINE_CTRL_T* pLine = (DML_PROFILE_CTRL_T*) hInsContext;

    if(pLine != NULL)
    {
        TELCOVOICEMGR_DML_DATA* pTelcoVoiceMgrDmlData = TelcoVoiceMgrDmlGetDataLocked();
        if(pTelcoVoiceMgrDmlData != NULL)
        {
            pDmlLine = &(pLine->dml);
            if(nIndex < pDmlLine->LineRingerObj.LineRingerPatternList.ulQuantity)
            {
                DML_LINE_SESSION_CTRL_T* pDmlLineRingerPattern = pDmlLine->LineRingerObj.LineRingerPatternList.pdata[nIndex];
                if ( pDmlLineRingerPattern != NULL )
                {
                    *pInsNumber = nIndex + 1;
                    pDmlEntry = (ANSC_HANDLE) pDmlLineRingerPattern;
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

        BOOL Line_Validate(ANSC_HANDLE hInsContext);

    description:

        This function is called to validate the update.

    argument:   ANSC_HANDLE                 hInsContext,
                The instance handle;

    return:     TRUE if there's no issue.

**********************************************************************/
BOOL Line_Validate(ANSC_HANDLE hInsContext)
{
    return TRUE;
}

/**********************************************************************

    caller:     owner of this object

    prototype:

        BOOL Line_Commit(ANSC_HANDLE hInsContext);

    description:

        This function is called to validate the update.

    argument:   ANSC_HANDLE                 hInsContext,
                The instance handle;

    return:     0 if there's no issue.

**********************************************************************/

ULONG Line_Commit(ANSC_HANDLE hInsContext)
{
    return 0;
}

/**********************************************************************

    caller:     owner of this object

    prototype:

        BOOL Line_Rollback(ANSC_HANDLE hInsContext);

    description:

        This function is called to validate the update.

    argument:   ANSC_HANDLE                 hInsContext,
                The instance handle;

    return:     0 if there's no issue.

**********************************************************************/
ULONG Line_Rollback(ANSC_HANDLE hInsContext)
{
    return 0;
}

/***********************************************************************

 APIs for Object:

    Services.VoiceService.{i}.VoiceProfile.{i}.Line.{i}.VoiceProcessing

    *  VoiceProcessing_GetParamIntValue
    *  VoiceProcessing_SetParamIntValue
    *  VoiceProcessing_Validate
    *  VoiceProcessing_Commit
    *  VoiceProcessing_Rollback

***********************************************************************/
/**********************************************************************

    caller:     owner of this object

    prototype:

        BOOL VoiceProcessing_SetParamUlongValue(ANSC_HANDLE hInsContext, char* ParamName, ULONG uValue);

    description:

        This function is called to retrieve Ulong parameter value;

    argument:   ANSC_HANDLE                 hInsContext,
                The instance handle;

                char*                       ParamName,
                The parameter name;

                ULONG                       uValue
                The value returned

    return:     TRUE if succeeded.

**********************************************************************/
BOOL VoiceProcessing_SetParamUlongValue(ANSC_HANDLE hInsContext, char* ParamName, ULONG uValue)
{
    CcspTraceWarning(("%s::Unknown ParamName:%s\n", __FUNCTION__, ParamName));
    return FALSE;
}

/**********************************************************************

    caller:     owner of this object

    prototype:

        BOOL VoiceProcessing_GetParamUlongValue(ANSC_HANDLE hInsContext, char* ParamName, ULONG* pValue);

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
BOOL VoiceProcessing_GetParamUlongValue(ANSC_HANDLE hInsContext, char* ParamName, ULONG* pValue)
{
    BOOL    bStatus = FALSE;
    DML_LINE_CTRL_T* pTelcoVoiceMgrCtrl = (DML_LINE_CTRL_T*) hInsContext;
    PTELCOVOICEMGR_DML_PROFILE pVoiceProfile = NULL;
    PTELCOVOICEMGR_DML_VOICESERVICE pVoiceService = NULL;

    CcspTraceWarning(("%s::ParamName:%s\n", __FUNCTION__, ParamName));
    if(pTelcoVoiceMgrCtrl != NULL)
    {
        TELCOVOICEMGR_DML_DATA* pTelcoVoiceMgrDmlData = TelcoVoiceMgrDmlGetDataLocked();
        if(pTelcoVoiceMgrDmlData != NULL)
        {
            TELCOVOICEMGR_DML_LINE* pLine = &(pTelcoVoiceMgrCtrl->dml);
            if (pLine && pValue)
            {
                pVoiceProfile = (PTELCOVOICEMGR_DML_PROFILE) pLine->pParentVoiceProfile;
                if (pVoiceProfile)
                {
                    pVoiceService = pVoiceProfile->pParentVoiceService;
                }
            }

            if (pVoiceService && pVoiceProfile && pLine)
            {
                if (strcmp(ParamName, "EchoCancellationTail") == 0)
                {
                    *pValue = pLine->LineVoiceProcessingObj.EchoCancellationTail;
                    bStatus = TRUE;
                }
                else
                {
                    CcspTraceWarning(("%s::Unknown ParamName:%s\n", __FUNCTION__, ParamName));
                    bStatus = FALSE;
                }
            }

            TelcoVoiceMgrDmlGetDataRelease(pTelcoVoiceMgrDmlData);
        }
    }

    CcspTraceWarning(("%s::Exit, bStatus:%d\n", __FUNCTION__, bStatus));
    return bStatus;
}

/**********************************************************************

    caller:     owner of this object

    prototype:

        BOOL VoiceProcessing_GetParamIntValue(ANSC_HANDLE hInsContext, char* ParamName, int* pInt);

    description:

        This function is called to retrieve integer parameter value;

    argument:   ANSC_HANDLE                 hInsContext,
                The instance handle;

                char*                       ParamName,
                The parameter name;

                int*                        pInt
                The buffer of returned integer value;

    return:     TRUE if succeeded.

**********************************************************************/
BOOL VoiceProcessing_GetParamIntValue(ANSC_HANDLE hInsContext, char* ParamName, int* pInt)
{
    BOOL    bStatus = FALSE;

    DML_LINE_CTRL_T* pTelcoVoiceMgrCtrl = (DML_LINE_CTRL_T*) hInsContext;
    PTELCOVOICEMGR_DML_PROFILE pVoiceProfile = NULL;
    PTELCOVOICEMGR_DML_VOICESERVICE pVoiceService = NULL;

    CcspTraceWarning(("%s::ParamName:%s\n", __FUNCTION__, ParamName));
    if(pTelcoVoiceMgrCtrl != NULL)
    {
        TELCOVOICEMGR_DML_DATA* pTelcoVoiceMgrDmlData = TelcoVoiceMgrDmlGetDataLocked();
        if(pTelcoVoiceMgrDmlData != NULL)
        {
            TELCOVOICEMGR_DML_LINE* pLine = &(pTelcoVoiceMgrCtrl->dml);
            if (pLine && pInt)
            {
                pVoiceProfile = (PTELCOVOICEMGR_DML_PROFILE) pLine->pParentVoiceProfile;
                if (pVoiceProfile)
                {
                    pVoiceService = pVoiceProfile->pParentVoiceService;
                }
            }

            if (pVoiceService && pVoiceProfile && pLine)
            {
                if (strcmp(ParamName, "ReceiveGain") == 0)
                {
                    * pInt = pLine->LineVoiceProcessingObj.ReceiveGain;
                    bStatus = TRUE;
                }
                else if (strcmp(ParamName, "TransmitGain") == 0)
                {
                    * pInt = pLine->LineVoiceProcessingObj.TransmitGain;
                    bStatus = TRUE;
                }
                else
                {
                    CcspTraceWarning(("%s::Unknown ParamName:%s\n", __FUNCTION__, ParamName));
                    bStatus =  FALSE;
                }
            }

            TelcoVoiceMgrDmlGetDataRelease(pTelcoVoiceMgrDmlData);
        }
    }

    CcspTraceWarning(("%s::Exit, bStatus:%d\n", __FUNCTION__, bStatus));
    return bStatus;
}


/**********************************************************************

    caller:     owner of this object

    prototype:

        BOOL VoiceProcessing_SetParamIntValue(ANSC_HANDLE hInsContext, char* ParamName, int iValue);

    description:

        This function is called to set integer parameter value;

    argument:   ANSC_HANDLE                 hInsContext,
                The instance handle;

                char*                       ParamName,
                The parameter name;

                int                         iValue
                The updated integer value;

    return:     TRUE if succeeded.

**********************************************************************/
BOOL VoiceProcessing_SetParamIntValue(ANSC_HANDLE hInsContext, char* ParamName, int iValue)
{
    BOOL    bStatus = FALSE;
    ULONG uVsIndex = 0;
    ULONG uVpIndex = 0;
    ULONG uLineIndex = 0;
    DML_LINE_CTRL_T* pTelcoVoiceMgrCtrl = (DML_LINE_CTRL_T*) hInsContext;
    PTELCOVOICEMGR_DML_LINE pLine = NULL;
    PTELCOVOICEMGR_DML_PROFILE pVoiceProfile = NULL;
    PTELCOVOICEMGR_DML_VOICESERVICE pVoiceService = NULL;

    CcspTraceWarning(("%s::ParamName:%s\n", __FUNCTION__, ParamName));
    if(pTelcoVoiceMgrCtrl != NULL)
    {
        TELCOVOICEMGR_DML_DATA* pTelcoVoiceMgrDmlData = TelcoVoiceMgrDmlGetDataLocked();
        if(pTelcoVoiceMgrDmlData != NULL)
        {
            TELCOVOICEMGR_DML_LINE* pLine = &(pTelcoVoiceMgrCtrl->dml);
            if (pLine)
            {
                pVoiceProfile = (PTELCOVOICEMGR_DML_PROFILE) pLine->pParentVoiceProfile;
                if (pVoiceProfile)
                {
                    pVoiceService = pVoiceProfile->pParentVoiceService;
                }
            }

            if (pVoiceService && pVoiceProfile && pLine)
            {
                uVsIndex = pVoiceService->InstanceNumber;
                uVpIndex = pVoiceProfile->InstanceNumber;
                uLineIndex = pLine->InstanceNumber;
                TelcoVoiceMgrDmlGetDataRelease(pTelcoVoiceMgrDmlData);
                if (strcmp(ParamName, "ReceiveGain") == 0)
                {
                    if(ANSC_STATUS_SUCCESS == TelcoVoiceMgrDmlSetReceiveGain(uVsIndex,
                                                                    uVpIndex,
                                                                    uLineIndex,
                                                                    iValue))
                    {
                        TELCOVOICEMGR_DML_DATA* pTelcoVoiceMgrDmlData = TelcoVoiceMgrDmlGetDataLocked();
                        if(pTelcoVoiceMgrDmlData != NULL)
                        {
                            pLine->LineVoiceProcessingObj.ReceiveGain = iValue;
                            TelcoVoiceMgrDmlGetDataRelease(pTelcoVoiceMgrDmlData);
                            return TRUE;
                        }
                    }
                }
                else if (strcmp(ParamName, "TransmitGain") == 0)
                {
                    if(ANSC_STATUS_SUCCESS == TelcoVoiceMgrDmlSetTransmitGain(uVsIndex,
                                                                    uVpIndex,
                                                                    uLineIndex,
                                                                    iValue))
                    {
                        TELCOVOICEMGR_DML_DATA* pTelcoVoiceMgrDmlData = TelcoVoiceMgrDmlGetDataLocked();
                        if(pTelcoVoiceMgrDmlData != NULL)
                        {
                            pLine->LineVoiceProcessingObj.TransmitGain = iValue;
                            TelcoVoiceMgrDmlGetDataRelease(pTelcoVoiceMgrDmlData);
                            return TRUE;
                        }
                    }
                }
                else
                {
                    CcspTraceWarning(("%s::Unknown ParamName:%s\n", __FUNCTION__, ParamName));
                    bStatus =  FALSE;
                }

            }
            else
            {
                TelcoVoiceMgrDmlGetDataRelease(pTelcoVoiceMgrDmlData);
            }
        }
    }
    CcspTraceWarning(("%s::Exit, bStatus:%d\n", __FUNCTION__, bStatus));
    return bStatus;
}

/**********************************************************************

        caller:     owner of this object

        prototype:

    BOOL VoiceProcessing_GetParamBoolValue(ANSC_HANDLE hInsContext, char* ParamName, BOOL* pBool);

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
BOOL VoiceProcessing_GetParamBoolValue(ANSC_HANDLE hInsContext, char* ParamName, BOOL* pBool)
{
    BOOL    bStatus = FALSE;
    DML_LINE_CTRL_T* pTelcoVoiceMgrCtrl = (DML_LINE_CTRL_T*) hInsContext;
    PTELCOVOICEMGR_DML_PROFILE pVoiceProfile = NULL;
    PTELCOVOICEMGR_DML_VOICESERVICE pVoiceService = NULL;

    CcspTraceWarning(("%s::ParamName:%s\n", __FUNCTION__, ParamName));
    if(pTelcoVoiceMgrCtrl != NULL)
    {
        TELCOVOICEMGR_DML_DATA* pTelcoVoiceMgrDmlData = TelcoVoiceMgrDmlGetDataLocked();
        if(pTelcoVoiceMgrDmlData != NULL)
        {
            TELCOVOICEMGR_DML_LINE* pLine = &(pTelcoVoiceMgrCtrl->dml);
            if (pLine && pBool)
            {
                pVoiceProfile = (PTELCOVOICEMGR_DML_PROFILE) pLine->pParentVoiceProfile;
                if (pVoiceProfile)
                {
                    pVoiceService = pVoiceProfile->pParentVoiceService;
                }
            }

            if (pVoiceService && pVoiceProfile && pLine)
            {
                if (strcmp(ParamName, "EchoCancellationEnable") == 0)
                {
                    *pBool = pLine->LineVoiceProcessingObj.EchoCancellationEnable;
                    bStatus = TRUE;
                }
                else if (strcmp(ParamName, "EchoCancellationInUse") == 0)
                {
                    *pBool = pLine->LineVoiceProcessingObj.EchoCancellationInUse;
                    bStatus = TRUE;
                }
                else
                {
                    CcspTraceWarning(("%s::Unknown ParamName:%s\n", __FUNCTION__, ParamName));
                    bStatus =  FALSE;
                }
            }

            TelcoVoiceMgrDmlGetDataRelease(pTelcoVoiceMgrDmlData);
        }
    }

    CcspTraceWarning(("%s::Exit, bStatus:%d\n", __FUNCTION__, bStatus));
    return bStatus;
}

BOOL VoiceProcessing_SetParamBoolValue(ANSC_HANDLE hInsContext, char* ParamName, BOOL bValue)
{
    BOOL    bStatus = FALSE;

    CcspTraceWarning(("%s::Exit\n", __FUNCTION__));
    return TRUE;
}

/**********************************************************************

    caller:     owner of this object

    prototype:

        BOOL VoiceProcessing_Validate(ANSC_HANDLE hInsContext);

    description:

        This function is called to validate the update.

    argument:   ANSC_HANDLE                 hInsContext,
                The instance handle;

    return:     0 if there's no issue.

**********************************************************************/
BOOL VoiceProcessing_Validate(ANSC_HANDLE hInsContext)
{
    CcspTraceWarning(("%s::Enter\n", __FUNCTION__));
    return TRUE;
}

/**********************************************************************

    caller:     owner of this object

    prototype:

        ULONG VoiceProcessing_Commit(ANSC_HANDLE hInsContext);

    description:

        This function is called to validate the update.

    argument:   ANSC_HANDLE                 hInsContext,
                The instance handle;

    return:     0 if there's no issue.

**********************************************************************/

ULONG VoiceProcessing_Commit(ANSC_HANDLE hInsContext)
{
    CcspTraceWarning(("%s::Enter\n", __FUNCTION__));
    return 0;
}

/**********************************************************************

    caller:     owner of this object

    prototype:

        ULONG VoiceProcessing_Rollback(ANSC_HANDLE hInsContext);

    description:

        This function is called to validate the update.

    argument:   ANSC_HANDLE                 hInsContext,
                The instance handle;

    return:     0 if there's no issue.

**********************************************************************/
ULONG VoiceProcessing_Rollback(ANSC_HANDLE hInsContext)
{
    CcspTraceWarning(("%s::Enter\n", __FUNCTION__));
    return 0;
}

/**********************************************************************

    caller:     owner of this object

    prototype:

        BOOL EventSubscribe_Validate(ANSC_HANDLE hInsContext);

    description:

        This function is called to validate the update.

    argument:   ANSC_HANDLE                 hInsContext,
                The instance handle;

    return:     0 if there's no issue.

**********************************************************************/
BOOL EventSubscribe_Validate(ANSC_HANDLE hInsContext)
{
    CcspTraceWarning(("%s::Enter\n", __FUNCTION__));
    return TRUE;
}

/**********************************************************************

    caller:     owner of this object

    prototype:

        ULONG EventSubscribe_Commit(ANSC_HANDLE hInsContext);

    description:

        This function is called to validate the update.

    argument:   ANSC_HANDLE                 hInsContext,
                The instance handle;

    return:     0 if there's no issue.

**********************************************************************/

ULONG EventSubscribe_Commit(ANSC_HANDLE hInsContext)
{
    CcspTraceWarning(("%s::Enter\n", __FUNCTION__));
    return 0;
}

/**********************************************************************

    caller:     owner of this object

    prototype:

        ULONG EventSubscribe_Rollback(ANSC_HANDLE hInsContext);

    description:

        This function is called to validate the update.

    argument:   ANSC_HANDLE                 hInsContext,
                The instance handle;

    return:     0 if there's no issue.

**********************************************************************/
ULONG EventSubscribe_Rollback(ANSC_HANDLE hInsContext)
{
    CcspTraceWarning(("%s::Enter\n", __FUNCTION__));
    return 0;
}

/**********************************************************************

    caller:     owner of this object

    prototype:

        BOOL Event_Validate(ANSC_HANDLE hInsContext);

    description:

        This function is called to validate the update.

    argument:   ANSC_HANDLE                 hInsContext,
                The instance handle;

    return:     0 if there's no issue.

**********************************************************************/
BOOL Event_Validate(ANSC_HANDLE hInsContext)
{
    CcspTraceWarning(("%s::Enter\n", __FUNCTION__));
    return TRUE;
}

/**********************************************************************

    caller:     owner of this object

    prototype:

        ULONG Event_Commit(ANSC_HANDLE hInsContext);

    description:

        This function is called to validate the update.

    argument:   ANSC_HANDLE                 hInsContext,
                The instance handle;

    return:     0 if there's no issue.

**********************************************************************/

ULONG Event_Commit(ANSC_HANDLE hInsContext)
{
    CcspTraceWarning(("%s::Enter\n", __FUNCTION__));
    return 0;
}

/**********************************************************************

    caller:     owner of this object

    prototype:

        ULONG Event_Rollback(ANSC_HANDLE hInsContext);

    description:

        This function is called to validate the update.

    argument:   ANSC_HANDLE                 hInsContext,
                The instance handle;

    return:     0 if there's no issue.

**********************************************************************/
ULONG Event_Rollback(ANSC_HANDLE hInsContext)
{
    CcspTraceWarning(("%s::Enter\n", __FUNCTION__));
    return 0;
}

/**********************************************************************

    caller:     owner of this object

    prototype:

        BOOL Description_Validate(ANSC_HANDLE hInsContext);

    description:

        This function is called to validate the update.

    argument:   ANSC_HANDLE                 hInsContext,
                The instance handle;

    return:     0 if there's no issue.

**********************************************************************/
BOOL Description_Validate(ANSC_HANDLE hInsContext)
{
    CcspTraceWarning(("%s::Enter\n", __FUNCTION__));
    return TRUE;
}

/**********************************************************************

    caller:     owner of this object

    prototype:

        ULONG Description_Commit(ANSC_HANDLE hInsContext);

    description:

        This function is called to validate the update.

    argument:   ANSC_HANDLE                 hInsContext,
                The instance handle;

    return:     0 if there's no issue.

**********************************************************************/

ULONG Description_Commit(ANSC_HANDLE hInsContext)
{
    CcspTraceWarning(("%s::Enter\n", __FUNCTION__));
    return 0;
}

/**********************************************************************

    caller:     owner of this object

    prototype:

        ULONG Description_Rollback(ANSC_HANDLE hInsContext);

    description:

        This function is called to validate the update.

    argument:   ANSC_HANDLE                 hInsContext,
                The instance handle;

    return:     0 if there's no issue.

**********************************************************************/
ULONG Description_Rollback(ANSC_HANDLE hInsContext)
{
    CcspTraceWarning(("%s::Enter\n", __FUNCTION__));
    return 0;
}

/**********************************************************************

    caller:     owner of this object

    prototype:

        BOOL Pattern_Validate(ANSC_HANDLE hInsContext);

    description:

        This function is called to validate the update.

    argument:   ANSC_HANDLE                 hInsContext,
                The instance handle;

    return:     0 if there's no issue.

**********************************************************************/
BOOL Pattern_Validate(ANSC_HANDLE hInsContext)
{
    CcspTraceWarning(("%s::Enter\n", __FUNCTION__));
    return TRUE;
}

/**********************************************************************

    caller:     owner of this object

    prototype:

        ULONG Pattern_Commit(ANSC_HANDLE hInsContext);

    description:

        This function is called to validate the update.

    argument:   ANSC_HANDLE                 hInsContext,
                The instance handle;

    return:     0 if there's no issue.

**********************************************************************/

ULONG Pattern_Commit(ANSC_HANDLE hInsContext)
{
    CcspTraceWarning(("%s::Enter\n", __FUNCTION__));
    return 0;
}

/**********************************************************************

    caller:     owner of this object

    prototype:

        ULONG Pattern_Rollback(ANSC_HANDLE hInsContext);

    description:

        This function is called to validate the update.

    argument:   ANSC_HANDLE                 hInsContext,
                The instance handle;

    return:     0 if there's no issue.

**********************************************************************/
ULONG Pattern_Rollback(ANSC_HANDLE hInsContext)
{
    CcspTraceWarning(("%s::Enter\n", __FUNCTION__));
    return 0;
}


/***********************************************************************

 APIs for Object:

    Services.VoiceService.{i}.VoiceProfile.{i}.Line.{i}.Stats

    *  Stats_GetParamBoolValue
    *  Stats_GetParamUlongValue
    *  Stats_SetParamBoolValue

***********************************************************************/

/**********************************************************************

    caller:     owner of this object

    prototype:

        BOOL        Stats_GetParamBoolValue(ANSC_HANDLE hInsContext, char* ParamName, BOOL* pBool);

    description:

        This function is called to retrieve String parameter value;

    argument:   ANSC_HANDLE                 hInsContext,
                The instance handle;

                char*                       ParamName,
                The parameter name;

                BOOL*                      pBool
                The buffer of returned pBool;

    return:     TRUE if succeeded.

**********************************************************************/

BOOL Stats_GetParamBoolValue(ANSC_HANDLE hInsContext, char* ParamName, BOOL* pBool)
{
    PTELCOVOICEMGR_DML_LINE pLine = (PTELCOVOICEMGR_DML_LINE) hInsContext;

    CcspTraceWarning(("%s::ParamName:%s\n", __FUNCTION__, ParamName));

    if (pLine && pBool)
    {
        if (strcmp(ParamName, "ResetStatistics") == 0)
        {
            /*Always return FALSE when read the ResetStatistics param*/
            *pBool = FALSE;
            return TRUE;
        }
        else
        {
            CcspTraceWarning(("%s::Unknown ParamName:%s\n", __FUNCTION__, ParamName));
            return FALSE;
        }
    }
    return FALSE;
}

/**********************************************************************

    caller:     owner of this object

    prototype:

        BOOL Stats_SetParamBoolValue(ANSC_HANDLE hInsContext, char* ParamName, BOOL bvalue);

    description:

        This function is called to retrieve ULONG parameter value;

    argument:   ANSC_HANDLE                 hInsContext,
                The instance handle;

                char*                       ParamName,
                The parameter name;

                BOOL                      bvalue
                The buffer of returned pBool;

    return:     TRUE if succeeded.

**********************************************************************/


BOOL Stats_SetParamBoolValue(ANSC_HANDLE hInsContext, char* ParamName, BOOL bValue)
{
    BOOL    bStatus = FALSE;
    DML_LINE_CTRL_T* pTelcoVoiceMgrCtrl = (DML_LINE_CTRL_T*) hInsContext;
    PTELCOVOICEMGR_DML_LINE pLine = NULL;
    PTELCOVOICEMGR_DML_PROFILE pVoiceProfile = NULL;
    PTELCOVOICEMGR_DML_VOICESERVICE pVoiceService = NULL;
    ULONG uVsIndex = 0;
    ULONG uVpIndex = 0;
    ULONG uLineIndex = 0;

    CcspTraceWarning(("%s::ParamName:%s\n", __FUNCTION__, ParamName));
    if(pTelcoVoiceMgrCtrl != NULL)
    {
        TELCOVOICEMGR_DML_DATA* pTelcoVoiceMgrDmlData = TelcoVoiceMgrDmlGetDataLocked();
        if(pTelcoVoiceMgrDmlData != NULL)
        {
            TELCOVOICEMGR_DML_LINE* pLine = &(pTelcoVoiceMgrCtrl->dml);
            if (pLine)
            {
                pVoiceProfile = (PTELCOVOICEMGR_DML_PROFILE) pLine->pParentVoiceProfile;
                if (pVoiceProfile)
                {
                    pVoiceService = pVoiceProfile->pParentVoiceService;
                }
            }

            if (pVoiceService && pVoiceProfile && pLine)
            {
                uVsIndex = pVoiceProfile->InstanceNumber;
                uVpIndex = pVoiceProfile->InstanceNumber;
                uLineIndex = pLine->InstanceNumber;
                TelcoVoiceMgrDmlGetDataRelease(pTelcoVoiceMgrDmlData);
                if (strcmp(ParamName, "ResetStatistics") == 0)
                {
                    if(TRUE == bValue)
                    {
                        if(ANSC_STATUS_SUCCESS == TelcoVoiceMgrDmlResetLineStats(uVsIndex,
                                                                        uVpIndex,
                                                                        uLineIndex))
                        {
                            return TRUE;
                        }
                    }
                }
                else
                {
                    CcspTraceWarning(("%s::Unknown ParamName:%s\n", __FUNCTION__, ParamName));
                }
            }
            else
            {
                TelcoVoiceMgrDmlGetDataRelease(pTelcoVoiceMgrDmlData);
            }
        }
    }
    return bStatus;
}


/**********************************************************************

    caller:     owner of this object

    prototype:

        BOOL Stats_GetParamBoolValue(ANSC_HANDLE hInsContext, char* ParamName, ULONG* puLong);

    description:

        This function is called to retrieve String parameter value;

    argument:   ANSC_HANDLE                 hInsContext,
                The instance handle;

                char*                       ParamName,
                The parameter name;

                ULONG*                      puLong
                The buffer of returned puLong;

    return:     TRUE if succeeded.

**********************************************************************/

BOOL Stats_GetParamUlongValue(ANSC_HANDLE hInsContext, char* ParamName, ULONG* puLong)
{
    BOOL  bStatus = FALSE;
    ULONG uVsIndex = 0;
    ULONG uVpIndex = 0;
    ULONG uLineIndex = 0;
    DML_LINE_CTRL_T* pTelcoVoiceMgrCtrl = (DML_LINE_CTRL_T*) hInsContext;
    PTELCOVOICEMGR_DML_PROFILE            pVoiceProfile = NULL;
    PTELCOVOICEMGR_DML_VOICESERVICE       pVoiceService = NULL;
    TELCOVOICEMGR_DML_VOICESERVICE_STATS  stVoiceStats;
    memset(&stVoiceStats, 0, sizeof(stVoiceStats));
    CcspTraceWarning(("%s::ParamName:%s\n", __FUNCTION__, ParamName));
    if(pTelcoVoiceMgrCtrl != NULL)
    {
        TELCOVOICEMGR_DML_DATA* pTelcoVoiceMgrDmlData = TelcoVoiceMgrDmlGetDataLocked();
        if(pTelcoVoiceMgrDmlData != NULL)
        {
            TELCOVOICEMGR_DML_LINE* pLine = &(pTelcoVoiceMgrCtrl->dml);
            if (pLine && puLong)
            {
                pVoiceProfile = (PTELCOVOICEMGR_DML_PROFILE) pLine->pParentVoiceProfile;
                if (pVoiceProfile)
                {
                    pVoiceService = pVoiceProfile->pParentVoiceService;
                }
            }

            if (pVoiceService && pVoiceProfile && pLine)
            {
                uVsIndex = pVoiceProfile->InstanceNumber;
                uVpIndex = pVoiceProfile->InstanceNumber;
                uLineIndex = pLine->InstanceNumber;
                TelcoVoiceMgrDmlGetDataRelease(pTelcoVoiceMgrDmlData);
                if(ANSC_STATUS_SUCCESS == TelcoVoiceMgrDmlGetLineStats(uVsIndex,
                                                                uVpIndex,
                                                                uLineIndex,
                                                                &stVoiceStats))
                {
                    bStatus = TRUE;

                    if (strcmp(ParamName, "AverageFarEndInterarrivalJitter") == 0)
                    {
                        *puLong = stVoiceStats.AverageFarEndInterarrivalJitter;
                    }
                    else if (strcmp(ParamName, "AverageReceiveInterarrivalJitter") == 0)
                    {
                        *puLong = stVoiceStats.AverageReceiveInterarrivalJitter;
                    }
                    else if (strcmp(ParamName, "AverageRoundTripDelay") == 0)
                    {
                        *puLong = stVoiceStats.AverageRoundTripDelay;
                    }
                    else if (strcmp(ParamName, "BytesReceived") == 0)
                    {
                        *puLong = stVoiceStats.BytesReceived;
                    }
                    else if (strcmp(ParamName, "BytesSent") == 0)
                    {
                        *puLong = stVoiceStats.BytesSent;
                    }
                    else if (strcmp(ParamName, "FarEndInterarrivalJitter") == 0)
                    {
                        *puLong = stVoiceStats.FarEndInterarrivalJitter;
                    }
                    else if (strcmp(ParamName, "FarEndPacketLossRate") == 0)
                    {
                        *puLong = stVoiceStats.FarEndPacketLossRate;
                    }
                    else if (strcmp(ParamName, "IncomingCallsAnswered") == 0)
                    {
                        *puLong = stVoiceStats.IncomingCallsAnswered;
                    }
                    else if (strcmp(ParamName, "IncomingCallsConnected") == 0)
                    {
                        *puLong = stVoiceStats.IncomingCallsConnected;
                    }
                    else if (strcmp(ParamName, "IncomingCallsFailed") == 0)
                    {
                        *puLong = stVoiceStats.IncomingCallsFailed;
                    }
                    else if (strcmp(ParamName, "IncomingCallsReceived") == 0)
                    {
                        *puLong = stVoiceStats.IncomingCallsReceived;
                    }
                    else if (strcmp(ParamName, "OutgoingCallsAnswered") == 0)
                    {
                        *puLong = stVoiceStats.OutgoingCallsAnswered;
                    }
                    else if (strcmp(ParamName, "OutgoingCallsAttempted") == 0)
                    {
                        *puLong = stVoiceStats.OutgoingCallsAttempted;
                    }
                    else if (strcmp(ParamName, "OutgoingCallsConnected") == 0)
                    {
                        *puLong = stVoiceStats.OutgoingCallsConnected;
                    }
                    else if (strcmp(ParamName, "OutgoingCallsFailed") == 0)
                    {
                        *puLong = stVoiceStats.OutgoingCallsFailed;
                    }
                    else if (strcmp(ParamName, "PacketsLost") == 0)
                    {
                        *puLong = stVoiceStats.PacketsLost;
                    }
                    else if (strcmp(ParamName, "PacketsReceived") == 0)
                    {
                        *puLong = stVoiceStats.PacketsReceived;
                    }
                    else if (strcmp(ParamName, "PacketsSent") == 0)
                    {
                        *puLong = stVoiceStats.PacketsSent;
                    }
                    else if (strcmp(ParamName, "ReceiveInterarrivalJitter") == 0)
                    {
                        *puLong = stVoiceStats.ReceiveInterarrivalJitter;
                    }
                    else if (strcmp(ParamName, "ReceivePacketLossRate") == 0)
                    {
                        *puLong = stVoiceStats.ReceivePacketLossRate;
                    }
                    else if (strcmp(ParamName, "RoundTripDelay") == 0)
                    {
                        *puLong = stVoiceStats.RoundTripDelay;
                    }
                    else if (strcmp(ParamName, "Overruns") == 0)
                    {
                        *puLong = stVoiceStats.Overruns;
                    }
                    else if (strcmp(ParamName, "Underruns") == 0)
                    {
                        *puLong = stVoiceStats.Underruns;
                    }
                    else if (strcmp(ParamName, "CallsDropped") == 0)
                    {
                        *puLong = stVoiceStats.CallsDropped;
                    }
                    else if (strcmp(ParamName, "TotalCallTime") == 0)
                    {
                        *puLong = stVoiceStats.TotalCallTime;
                    }
                    else if (strcmp(ParamName, "ServerDownTime") == 0)
                    {
                        *puLong = stVoiceStats.ServerDownTime;
                    }
                    else
                    {
                        CcspTraceWarning(("%s::Unknown ParamName:%s\n", __FUNCTION__, ParamName));
                        bStatus = FALSE;
                    }
                }
            }
            else
            {
                TelcoVoiceMgrDmlGetDataRelease(pTelcoVoiceMgrDmlData);
            }
        }
    }

    CcspTraceWarning(("%s::Exit, bStatus:%d\n", __FUNCTION__, bStatus));
    return bStatus;
}

/***********************************************************************

 APIs for Object:

    Services.VoiceService.{i}.VoiceProfile.{i}.Line.{i}.CallingFeatures

    *  CallingFeatures_GetParamBoolValue
    *  CallingFeatures_GetParamUlongValue
    *  CallingFeatures_Validate
    *  CallingFeatures_Commit
    *  CallingFeatures_Rollback

***********************************************************************/
/**********************************************************************

    caller:     owner of this object

    prototype:

        BOOL CallingFeatures_SetParamUlongValue(ANSC_HANDLE hInsContext, char* ParamName, ULONG uValue);

    description:

        This function is called to retrieve Ulong parameter value;

    argument:   ANSC_HANDLE                 hInsContext,
                The instance handle;

                char*                       ParamName,
                The parameter name;

                ULONG                       uValue
                The value returned

    return:     TRUE if succeeded.

**********************************************************************/
BOOL CallingFeatures_SetParamUlongValue(ANSC_HANDLE hInsContext, char* ParamName, ULONG uValue)
{
    CcspTraceWarning(("%s::Unknown ParamName:%s\n", __FUNCTION__, ParamName));
    return FALSE;
}

/**********************************************************************

    caller:     owner of this object

    prototype:

        BOOL CallingFeatures_GetParamUlongValue(ANSC_HANDLE hInsContext, char* ParamName, ULONG* pValue);

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
BOOL CallingFeatures_GetParamUlongValue(ANSC_HANDLE hInsContext, char* ParamName, ULONG* pValue)
{

    DML_LINE_CTRL_T* pTelcoVoiceMgrCtrl = (DML_LINE_CTRL_T*) hInsContext;

    TELCOVOICEMGR_DML_LINE* pLine = &(pTelcoVoiceMgrCtrl->dml);

    if( !pLine || !pValue || !ParamName )
    {
        return FALSE;
    }

    if (strcmp(ParamName, "MaxSessions") == 0)
    {
        *pValue = pLine->LineCallingFeaturesObj.MaxSessions;
    }
    else if (strcmp(ParamName, "ConferenceCallingSessionCount") == 0)
    {
        *pValue = pLine->LineCallingFeaturesObj.ConferenceCallingSessionCount;
    }
    else if (strcmp(ParamName, "CallForwardOnNoAnswerRingCount") == 0)
    {
        *pValue = pLine->LineCallingFeaturesObj.CallForwardOnNoAnswerRingCount;
    }
    else
    {
        CcspTraceWarning(("%s::Unknown ParamName:%s\n", __FUNCTION__, ParamName));
        return FALSE;
    }
    return TRUE;
}

LONG CallingFeatures_GetParamStringValue(ANSC_HANDLE hInsContext, char* ParamName, char* pValue, ULONG* pUlSize)
{
    DML_LINE_CTRL_T* pTelcoVoiceMgrCtrl = (DML_LINE_CTRL_T*) hInsContext;

    TELCOVOICEMGR_DML_LINE* pLine = &(pTelcoVoiceMgrCtrl->dml);

    if( !pLine || !pValue || !ParamName )
    {
        return -1;
    }

    if (strcmp(ParamName, "CallerIDName") == 0)
    {
        AnscCopyString(pValue, pLine->LineCallingFeaturesObj.CallerIDName);
    }
    else if (strcmp(ParamName, "CallWaitingStatus") == 0)
    {
        switch( pLine->LineCallingFeaturesObj.CallWaitingStatus )
        {
            case VOICE_CW_STATE_DISABLED:
                AnscCopyString(pValue, "Disabled");
                break;

            case VOICE_CW_STATE_IDLE:
                AnscCopyString(pValue, "Idle");
                break;

            case VOICE_CW_STATE_SECONDARY_RINGING:
                AnscCopyString(pValue, "Ringing");
                break;

            case VOICE_CW_STATE_SECONDARY_CONNECTING:
                AnscCopyString(pValue, "Connecting");
                break;

            case VOICE_CW_STATE_SECONDARY_CONNECTED:
                AnscCopyString(pValue, "Connected");
                break;

            default:
                AnscCopyString(pValue, "");
                break;
        }
    }
    else if (strcmp(ParamName, "ConferenceCallingStatus") == 0)
    {
        switch( pLine->LineCallingFeaturesObj.ConferenceCallingStatus )
        {
            case VOICE_CONFERENCE_CALLING_STATE_DISABLED:
                AnscCopyString(pValue, "Disabled");
                break;

            case VOICE_CONFERENCE_CALLING_STATE_IDLE:
                AnscCopyString(pValue, "Idle");
                break;

            case VOICE_CONFERENCE_CALLING_STATE_SECONDARY_RINGING:
                AnscCopyString(pValue, "Ringing");
                break;

            case VOICE_CONFERENCE_CALLING_STATE_SECONDARY_CONNECTING:
                AnscCopyString(pValue, "Connecting");
                break;

            case VOICE_CONFERENCE_CALLING_STATE_SECONDARY_CONNECTED:
                AnscCopyString(pValue, "Connected");
                break;

            case VOICE_CONFERENCE_CALLING_STATE_IN_CONFERENCE_CALL:
                AnscCopyString(pValue, "In Call");
                break;

            default:
                AnscCopyString(pValue, "");
                break;
        }
    }
    else if (strcmp(ParamName, "CallForwardOnBusyNumber") == 0)
    {
        AnscCopyString(pValue, pLine->LineCallingFeaturesObj.CallForwardOnBusyNumber);
    }
    else if (strcmp(ParamName, "CallForwardUnconditionalNumber") == 0)
    {
        AnscCopyString(pValue, pLine->LineCallingFeaturesObj.CallForwardUnconditionalNumber);
    }
    else if (strcmp(ParamName, "CallForwardOnNoAnswerNumber") == 0)
    {
        AnscCopyString(pValue, pLine->LineCallingFeaturesObj.CallForwardOnNoAnswerNumber);
    }
    else
    {
        CcspTraceWarning(("%s::Unknown ParamName:%s\n", __FUNCTION__, ParamName));
        return -1;
    }
    return 0;
}
BOOL CallingFeatures_SetParamStringValue(ANSC_HANDLE hInsContext, char* ParamName, char* pString)
{
    CcspTraceWarning(("%s::Unknown ParamName:%s\n", __FUNCTION__, ParamName));
    return FALSE;
}
/**********************************************************************

    caller:     owner of this object

    prototype:

        BOOL CallingFeatures_GetParamBoolValue(ANSC_HANDLE hInsContext, char* ParamName, BOOL* pBool);

    description:

        This function is called to retrieve String parameter value;

    argument:   ANSC_HANDLE                 hInsContext,
                The instance handle;

                char*                       ParamName,
                The parameter name;

                BOOL*                      pBool
                The buffer of returned pBool;

    return:     TRUE if succeeded.

**********************************************************************/

BOOL CallingFeatures_GetParamBoolValue(ANSC_HANDLE hInsContext, char* ParamName, BOOL* pBool)
{

    DML_LINE_CTRL_T* pTelcoVoiceMgrCtrl = (DML_LINE_CTRL_T*) hInsContext;

    TELCOVOICEMGR_DML_LINE* pLine = &(pTelcoVoiceMgrCtrl->dml);

    BOOL ret = FALSE;

    if( !pLine || !pBool || !ParamName )
    {
        return ret;
    }
    
    CcspTraceWarning(("%s::ParamName:%s\n", __FUNCTION__, ParamName));
    if (strcmp(ParamName, "CallerIDEnable") == 0)
    {
        *pBool = pLine->LineCallingFeaturesObj.CallerIDEnable;
        ret = TRUE;
    }
    else if (strcmp(ParamName, "AnonymousCallBlockEnable") == 0)
    {
        *pBool = pLine->LineCallingFeaturesObj.AnonymousCallBlockEnable;
        ret = TRUE;
    }
    else if (strcmp(ParamName, "AnonymousCalEnable") == 0)
    {
        *pBool = pLine->LineCallingFeaturesObj.AnonymousCalEnable;
        ret = TRUE;
    }
    else if (strcmp(ParamName, "DoNotDisturbEnable") == 0)
    {
        *pBool =  pLine->LineCallingFeaturesObj.DoNotDisturbEnable;
        ret = TRUE;
    }
    else if (strcmp(ParamName, "CallReturnEnable") == 0)
    {
        *pBool = pLine->LineCallingFeaturesObj.CallReturnEnable;
        ret = TRUE;
    }
    else if (strcmp(ParamName, "RepeatDialEnable") == 0)
    {
        *pBool = pLine->LineCallingFeaturesObj.RepeatDialEnable;
        ret = TRUE;
    }
    else if (strcmp(ParamName, "CallForwardOnNoAnswerEnable") == 0)
    {
        *pBool = pLine->LineCallingFeaturesObj.CallForwardOnNoAnswerEnable;
        ret = TRUE;
    }
    else if (strcmp(ParamName, "CallTransferEnable") == 0)
    {
        *pBool = pLine->LineCallingFeaturesObj.CallTransferEnable;
        ret = TRUE;
    }
    else if (strcmp(ParamName, "MessageWaiting") == 0)
    {
        *pBool = pLine->LineCallingFeaturesObj.MessageWaiting;
        ret = TRUE;
    }
    else if (strcmp(ParamName, "CallForwardUnconditionalEnable") == 0)
    {
        *pBool = pLine->LineCallingFeaturesObj.CallForwardUnconditionalEnable;
        ret = TRUE;
    }
    else if (strcmp(ParamName, "CallerIDNameEnable") == 0)
    {
        *pBool = pLine->LineCallingFeaturesObj.CallerIDNameEnable;
        ret = TRUE;
    }
    else if (strcmp(ParamName, "CallForwardOnBusyEnable") == 0)
    {
        *pBool = pLine->LineCallingFeaturesObj.CallForwardOnBusyEnable;
        ret = TRUE;
    }
    else if (strcmp(ParamName, "CallWaitingEnable") == 0)
    {
        *pBool = pLine->LineCallingFeaturesObj.CallWaitingEnable;
        ret = TRUE;
    }
    else if (strcmp(ParamName, "MWIEnable") == 0)
    {
        *pBool = pLine->LineCallingFeaturesObj.MWIEnable;
        ret = TRUE;
    }
    else if (strcmp(ParamName, "X_RDK-Central_COM_ConferenceCallingEnable") == 0)
    {
        * pBool = pLine->LineCallingFeaturesObj.ConferenceCallingEnable;
        ret = TRUE;
    }
    else if (strcmp(ParamName, "X_RDK-Central_COM_HoldEnable") == 0)
    {
        * pBool = pLine->LineCallingFeaturesObj.HoldEnable;
        ret = TRUE;
    }
    else if (strcmp(ParamName, "X_RDK-Central_COM_PhoneCallerIDEnable") == 0)
    {
        * pBool = pLine->LineCallingFeaturesObj.PhoneCallerIDEnable;
        ret = TRUE;
    }
    else
    {
        CcspTraceWarning(("%s::Unknown_a ParamName:%s\n", __FUNCTION__, ParamName));
        ret = FALSE;
    } 
    return ret;
}

/**********************************************************************

    caller:     owner of this object

    prototype:

        BOOL CallingFeatures_SetParamBoolValue(ANSC_HANDLE hInsContext, char* ParamName, BOOL bValue);

    description:

        This function is called to retrieve ULONG parameter value;

    argument:   ANSC_HANDLE                 hInsContext,
                The instance handle;

                char*                       ParamName,
                The parameter name;

                BOOL                      bValue
                The buffer of returned pBool;

    return:     TRUE if succeeded.

**********************************************************************/


BOOL CallingFeatures_SetParamBoolValue(ANSC_HANDLE hInsContext, char* ParamName, BOOL bValue)
{
    DML_LINE_CTRL_T* pTelcoVoiceMgrCtrl = (DML_LINE_CTRL_T*) hInsContext;
    PTELCOVOICEMGR_DML_PROFILE pVoiceProfile = NULL;
    PTELCOVOICEMGR_DML_VOICESERVICE pVoiceService = NULL;
    TELCOVOICEMGR_VOICE_CALL_FEATURE_TYPE_ENUM eFeature;
    BOOL bStatus = FALSE;
    ULONG uVsIndex = 0;
    ULONG uVpIndex = 0;
    ULONG uLineIndex = 0;
    CcspTraceWarning(("%s::ParamName:%s\n", __FUNCTION__, ParamName));

    if(pTelcoVoiceMgrCtrl != NULL)
    {
        TELCOVOICEMGR_DML_DATA* pTelcoVoiceMgrDmlData = TelcoVoiceMgrDmlGetDataLocked();
        if(pTelcoVoiceMgrDmlData != NULL)
        {
            TELCOVOICEMGR_DML_LINE* pLine = &(pTelcoVoiceMgrCtrl->dml);
            if (pLine)
            {
                pVoiceProfile = (PTELCOVOICEMGR_DML_PROFILE) pLine->pParentVoiceProfile;
                if (pVoiceProfile)
                {
                    pVoiceService = pVoiceProfile->pParentVoiceService;
                }
            }

            if (pVoiceService && pVoiceProfile && pLine)
            {
                uVsIndex = pVoiceService->InstanceNumber;
                uVpIndex = pVoiceProfile->InstanceNumber;
                uLineIndex = pLine->InstanceNumber;
                TelcoVoiceMgrDmlGetDataRelease(pTelcoVoiceMgrDmlData);
                if (strcmp(ParamName, "CallWaitingEnable") == 0)
                {
                    eFeature = VOICE_CALLING_FEATURE_CALL_WAITING;
                    if(ANSC_STATUS_SUCCESS == TelcoVoiceMgrDmlSetLineCallingFeatures(uVsIndex,
                                                                    uVpIndex,
                                                                    uLineIndex,
                                                                    eFeature,
                                                                    bValue))
                    {
                        TELCOVOICEMGR_DML_DATA* pTelcoVoiceMgrDmlData = TelcoVoiceMgrDmlGetDataLocked();
                        if(pTelcoVoiceMgrDmlData != NULL)
                        {
                           pLine->LineCallingFeaturesObj.CallWaitingEnable = bValue;
                            TelcoVoiceMgrDmlGetDataRelease(pTelcoVoiceMgrDmlData);
                            return TRUE;
                        }
                    }
                }
                else if (strcmp(ParamName, "MWIEnable") == 0)
                {
                    eFeature = VOICE_CALLING_FEATURE_MSG_WAIT_INDICATOR;
                    if(ANSC_STATUS_SUCCESS == TelcoVoiceMgrDmlSetLineCallingFeatures(uVsIndex,
                                                                    uVpIndex,
                                                                    uLineIndex,
                                                                    eFeature,
                                                                    bValue))
                    {
                        TELCOVOICEMGR_DML_DATA* pTelcoVoiceMgrDmlData = TelcoVoiceMgrDmlGetDataLocked();
                        if(pTelcoVoiceMgrDmlData != NULL)
                        {
                            pLine->LineCallingFeaturesObj.MWIEnable = bValue;
                            TelcoVoiceMgrDmlGetDataRelease(pTelcoVoiceMgrDmlData);
                            return TRUE;
                        }
                    }
                }
                else if (strcmp(ParamName, "X_RDK-Central_COM_ConferenceCallingEnable") == 0)
                {
                    eFeature = VOICE_CALLING_FEATURE_CONF_CALL;
                    if(ANSC_STATUS_SUCCESS == TelcoVoiceMgrDmlSetLineCallingFeatures(uVsIndex,
                                                                    uVpIndex,
                                                                    uLineIndex,
                                                                    eFeature,
                                                                    bValue))
                    {
                        TELCOVOICEMGR_DML_DATA* pTelcoVoiceMgrDmlData = TelcoVoiceMgrDmlGetDataLocked();
                        if(pTelcoVoiceMgrDmlData != NULL)
                        {
                            pLine->LineCallingFeaturesObj.ConferenceCallingEnable = bValue;
                            TelcoVoiceMgrDmlGetDataRelease(pTelcoVoiceMgrDmlData);
                            return TRUE;
                        }
                    }
                }
                else if (strcmp(ParamName, "X_RDK-Central_COM_HoldEnable") == 0)
                {
                    eFeature = VOICE_CALLING_FEATURE_HOLD;
                    if(ANSC_STATUS_SUCCESS == TelcoVoiceMgrDmlSetLineCallingFeatures(uVsIndex,
                                                                    uVpIndex,
                                                                    uLineIndex,
                                                                    eFeature,
                                                                    bValue))
                    {
                        TELCOVOICEMGR_DML_DATA* pTelcoVoiceMgrDmlData = TelcoVoiceMgrDmlGetDataLocked();
                        if(pTelcoVoiceMgrDmlData != NULL)
                        {
                            pLine->LineCallingFeaturesObj.HoldEnable = bValue;
                            TelcoVoiceMgrDmlGetDataRelease(pTelcoVoiceMgrDmlData);
                            return TRUE;
                        }
                    }
                }
                else if (strcmp(ParamName, "X_RDK-Central_COM_PhoneCallerIDEnable") == 0)
                {
                    eFeature = VOICE_CALLING_FEATURE_CALLER_ID;
                    if(ANSC_STATUS_SUCCESS == TelcoVoiceMgrDmlSetLineCallingFeatures(uVsIndex,
                                                                    uVpIndex,
                                                                    uLineIndex,
                                                                    eFeature,
                                                                    bValue))
                    {
                        TELCOVOICEMGR_DML_DATA* pTelcoVoiceMgrDmlData = TelcoVoiceMgrDmlGetDataLocked();
                        if(pTelcoVoiceMgrDmlData != NULL)
                        {
                            pLine->LineCallingFeaturesObj.PhoneCallerIDEnable = bValue;
                            TelcoVoiceMgrDmlGetDataRelease(pTelcoVoiceMgrDmlData);
                            return TRUE;
                        }
                    }
                }
                else
                {
                    CcspTraceWarning(("%s::Unknown ParamName:%s\n", __FUNCTION__, ParamName));
                    bStatus = FALSE;
                }
            }
            else
            {
                TelcoVoiceMgrDmlGetDataRelease(pTelcoVoiceMgrDmlData);
            }
        }
    }
    return bStatus;
}


/**********************************************************************

    caller:     owner of this object

    prototype:

        BOOL CallingFeatures_Validate(ANSC_HANDLE hInsContext);

    description:

        This function is called to validate the update.

    argument:   ANSC_HANDLE                 hInsContext,
                The instance handle;

    return:     0 if there's no issue.

**********************************************************************/
BOOL CallingFeatures_Validate(ANSC_HANDLE hInsContext)
{
    CcspTraceWarning(("%s::Enter\n", __FUNCTION__));
    return TRUE;
}

/**********************************************************************

    caller:     owner of this object

    prototype:

        ULONG CallingFeatures_Commit(ANSC_HANDLEhInsContext);

    description:

        This function is called to validate the update.

    argument:   ANSC_HANDLE                 hInsContext,
                The instance handle;

    return:     0 if there's no issue.

**********************************************************************/

ULONG CallingFeatures_Commit(ANSC_HANDLE hInsContext)
{
    CcspTraceWarning(("%s::Enter\n", __FUNCTION__));
    return 0;
}

/**********************************************************************

    caller:     owner of this object

    prototype:

        ULONG CallingFeatures_Rollback(ANSC_HANDLEhInsContext);

    description:

        This function is called to validate the update.

    argument:   ANSC_HANDLE                 hInsContext,
                The instance handle;

    return:     0 if there's no issue.

**********************************************************************/
ULONG CallingFeatures_Rollback(ANSC_HANDLE hInsContext)
{
    CcspTraceWarning(("%s::Enter\n", __FUNCTION__));
    return 0;
}


/***********************************************************************

 APIs for Object:

    Services.VoiceService.{i}.VoiceProfile.{i}.Line.{i}.SIP

    *  LineSIP_GetParamStringValue
    *  LineSIP_SetParamStringValue

***********************************************************************/

/**********************************************************************

    caller:     owner of this object

    prototype:

        LONG LineSIP_GetParamStringValue(ANSC_HANDLE hInsContext, char* ParamName, char* pValue, ULONG* pUlSize);

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

   return:     0 if succeeded;
               1 if short of buffer size; (*pUlSize = required size)
               -1 if not supported.

**********************************************************************/
LONG LineSIP_GetParamStringValue(ANSC_HANDLE hInsContext, char* ParamName, char* pValue, ULONG* pUlSize)
{
    DML_LINE_CTRL_T* pTelcoVoiceMgrCtrl = (DML_LINE_CTRL_T*) hInsContext;
    PTELCOVOICEMGR_DML_PROFILE pVoiceProfile = NULL;
    PTELCOVOICEMGR_DML_VOICESERVICE pVoiceService = NULL;
    PTELCOVOICEMGR_DML_LINE pLine = NULL;
    char    buf[1024] = {0};
    LONG ret = -1;

    CcspTraceWarning(("%s::ParamName:%s\n", __FUNCTION__, ParamName));

    if(pTelcoVoiceMgrCtrl != NULL)
    {
        TELCOVOICEMGR_DML_DATA* pTelcoVoiceMgrDmlData = TelcoVoiceMgrDmlGetDataLocked();
        if(pTelcoVoiceMgrDmlData != NULL)
        {
            TELCOVOICEMGR_DML_LINE* pLine = &(pTelcoVoiceMgrCtrl->dml);
            if (pLine && pValue && pUlSize)
            {
                pVoiceProfile = (PTELCOVOICEMGR_DML_PROFILE) pLine->pParentVoiceProfile;
                if (pVoiceProfile)
                {
                    pVoiceService = pVoiceProfile->pParentVoiceService;
                }
                if (pVoiceService && pVoiceProfile && pLine)
                {
                    if (strcmp(ParamName, "AuthUserName") == 0)
                    {
                        snprintf(buf, sizeof(buf), "%s", pLine->LineSipObj.AuthUserName);
                        if ( AnscSizeOfString(buf) < *pUlSize)
                        {
                            AnscCopyString(pValue, buf);
                            ret = 0;
                        }
                        else
                        {
                            *pUlSize = AnscSizeOfString(pValue);
                            ret = 1;
                        }
                    }
                    else if (strcmp(ParamName, "AuthPassword") == 0)
                    {
                        //Avoid returning password in dmcli get.
                        ret = 0;
                    }
                    else if (strcmp(ParamName, "URI") == 0)
                    {
                        snprintf(buf, sizeof(buf), "%s", pLine->LineSipObj.URI);
                        if ( AnscSizeOfString(buf) < *pUlSize)
                        {
                            AnscCopyString(pValue, buf);
                            ret = 0;
                        }
                        else
                        {
                            *pUlSize = AnscSizeOfString(pValue);
                            ret = 1;
                        }
                    }
                    else
                    {
                        CcspTraceWarning(("%s::Unknown ParamName:%s\n", __FUNCTION__, ParamName));
                        ret = -1;
                    }
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

        BOOL LineSIP_SetParamStringValue(ANSC_HANDLE hInsContext, char* ParamName, char* pString);

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

BOOL LineSIP_SetParamStringValue(ANSC_HANDLE hInsContext, char* ParamName, char* pString)
{
    DML_LINE_CTRL_T* pTelcoVoiceMgrCtrl = (DML_LINE_CTRL_T*) hInsContext;
    PTELCOVOICEMGR_DML_PROFILE pVoiceProfile = NULL;
    PTELCOVOICEMGR_DML_VOICESERVICE pVoiceService = NULL;
    PTELCOVOICEMGR_DML_LINE pLine = NULL;
    BOOL ret = FALSE;
    ULONG uVsIndex = 0;
    ULONG uVpIndex = 0;
    ULONG uLineIndex = 0;

    CcspTraceWarning(("%s::ParamName:%s, Value:%s\n", __FUNCTION__, ParamName, pString));
    if(pTelcoVoiceMgrCtrl != NULL)
    {
        TELCOVOICEMGR_DML_DATA* pTelcoVoiceMgrDmlData = TelcoVoiceMgrDmlGetDataLocked();
        if(pTelcoVoiceMgrDmlData != NULL)
        {
            TELCOVOICEMGR_DML_LINE* pLine = &(pTelcoVoiceMgrCtrl->dml);
            if (pLine && pString)
            {
                pVoiceProfile = (PTELCOVOICEMGR_DML_PROFILE) pLine->pParentVoiceProfile;
                if (pVoiceProfile)
                {
                    pVoiceService = pVoiceProfile->pParentVoiceService;
                }
                if (pVoiceService && pVoiceProfile && pLine)
                {
                    uVsIndex = pVoiceService->InstanceNumber;
                    uVpIndex = pVoiceProfile->InstanceNumber;
                    uLineIndex = pLine->InstanceNumber;
                    TelcoVoiceMgrDmlGetDataRelease(pTelcoVoiceMgrDmlData);
                    if (strcmp(ParamName, "AuthUserName") == 0)
                    {
                        if(ANSC_STATUS_SUCCESS == TelcoVoiceMgrDmlSetLineSIPAuthCredentials(uVsIndex,
                                                                    uVpIndex,
                                                                    pLine->InstanceNumber,
                                                                    VOICE_HAL_AUTH_UNAME,
                                                                    pString))
                        {
                            TELCOVOICEMGR_DML_DATA* pTelcoVoiceMgrDmlData = TelcoVoiceMgrDmlGetDataLocked();
                            if(pTelcoVoiceMgrDmlData != NULL)
                            {
                                AnscCopyString(pLine->LineSipObj.AuthUserName, pString);
                                TelcoVoiceMgrDmlGetDataRelease(pTelcoVoiceMgrDmlData);
                                return TRUE;
                            }
                        }
                    }
                    else if (strcmp(ParamName, "AuthPassword") == 0)
                    {
                        if(ANSC_STATUS_SUCCESS == TelcoVoiceMgrDmlSetLineSIPAuthCredentials(uVsIndex,
                                                                    uVpIndex,
                                                                    uLineIndex,
                                                                    VOICE_HAL_AUTH_PWD,
                                                                    pString))
                        {
                            TELCOVOICEMGR_DML_DATA* pTelcoVoiceMgrDmlData = TelcoVoiceMgrDmlGetDataLocked();
                            if(pTelcoVoiceMgrDmlData != NULL)
                            {
                                AnscCopyString(pLine->LineSipObj.AuthPassword, pString);
                                TelcoVoiceMgrDmlGetDataRelease(pTelcoVoiceMgrDmlData);
                                return TRUE;
                            }
                        }
                    }
                    else if (strcmp(ParamName, "URI") == 0)
                    {
                        if(ANSC_STATUS_SUCCESS == TelcoVoiceMgrDmlSetLineSipURI(uVsIndex,
                                                                    uVpIndex,
                                                                    uLineIndex,
                                                                    pString))
                        {
                            TELCOVOICEMGR_DML_DATA* pTelcoVoiceMgrDmlData = TelcoVoiceMgrDmlGetDataLocked();
                            if(pTelcoVoiceMgrDmlData != NULL)
                            {
                                AnscCopyString(pLine->LineSipObj.URI, pString);
                                TelcoVoiceMgrDmlGetDataRelease(pTelcoVoiceMgrDmlData);
                                return TRUE;
                            }
                        }
                    }
                    else
                    {
                        CcspTraceWarning(("%s::Unknown ParamName:%s\n", __FUNCTION__, ParamName));
                        ret = FALSE;
                    }
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
        BOOL Event_GetParamUlongValue(ANSC_HANDLE hInsContext, char* ParamName, ULONG* pValue);

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

BOOL Event_GetParamUlongValue(ANSC_HANDLE hInsContext, char* ParamName, ULONG* pValue)
{
    BOOL ret = FALSE;

    if (strcmp(ParamName, "Event_GetParamUlongValue") == 0)
    {
        *pValue = 0;
        ret = TRUE;
    }
    if (strcmp(ParamName, "RingID") == 0)
    {
        *pValue = 0;
        ret = TRUE;
    }
    else
    {
        CcspTraceWarning(("%s::Unknown ParamName:%s\n", __FUNCTION__, ParamName));
    }
    return ret;
}

/**********************************************************************

    caller:     owner of this object

    prototype:

        BOOL Event_SetParamUlongValue(ANSC_HANDLE hInsContext, char* ParamName, char* pValue, ULONG* pUlSize);

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

    return:     TRUE if succeeded.
                FALSE if not

**********************************************************************/

BOOL Event_SetParamUlongValue(ANSC_HANDLE hInsContext, char* ParamName, char* pValue, ULONG* pUlSize)
{
    
    if (strcmp(ParamName, "Alias") == 0)
    {
        return TRUE;
    }
    else
    {
        CcspTraceWarning(("%s::Unknown ParamName:%s\n", __FUNCTION__, ParamName));
        return FALSE;
    }
    
}

/**********************************************************************

    caller:     owner of this object

    prototype:

        LONG Event_GetParamStringValue(ANSC_HANDLE hInsContext, char* ParamName, char* pValue, ULONG* pUlSize);

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

LONG Event_GetParamStringValue(ANSC_HANDLE hInsContext, char* ParamName, char* pValue, ULONG* pUlSize)
{
    LONG ret = -1;
    if (strcmp(ParamName, "Alias") == 0)
    {
        AnscCopyString(pValue, "");
        return 0;
    }
    else if (strcmp(ParamName, "Function") == 0)
    {
        AnscCopyString(pValue, "");
        return 0;
    }
    else
    {
        CcspTraceWarning(("%s::Unknown ParamName:%s\n", __FUNCTION__, ParamName));
    }
    return ret;
}

/**********************************************************************

    caller:     owner of this object

    prototype:

        BOOL Event_SetParamStringValue(ANSC_HANDLE hInsContext, char* ParamName, char* pString);

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
BOOL Event_SetParamStringValue(ANSC_HANDLE hInsContext, char* ParamName, char* pString)
{
    BOOL ret = FALSE;
    if (strcmp(ParamName, "Alias") == 0)
    {
        ret = TRUE;
    }
    else
    {
        CcspTraceWarning(("%s::Unknown ParamName:%s\n", __FUNCTION__, ParamName));
    }
    return ret;
}

/**********************************************************************

    caller:     owner of this object

    prototype:
        BOOL Description_GetParamUlongValue(ANSC_HANDLE hInsContext, char* ParamName, ULONG* pValue);

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
BOOL Description_SetParamStringValue(ANSC_HANDLE hInsContext, char* ParamName, char* pString)
{
    CcspTraceWarning(("%s::Enter\n", __FUNCTION__));
    return TRUE;
}
BOOL Description_SetParamUlongValue(ANSC_HANDLE hInsContext, char* ParamName, char* pValue, ULONG* pUlSize)
{
    CcspTraceWarning(("%s::Enter\n", __FUNCTION__));
    return TRUE;
}
BOOL Description_GetParamUlongValue(ANSC_HANDLE hInsContext, char* ParamName, ULONG* pValue)
{
    BOOL ret = FALSE;

    if (strcmp(ParamName, "EntryID") == 0)
    {
        *pValue = 0;
        ret = TRUE;
    }
    else if (strcmp(ParamName, "RingPattern") == 0)
    {
        *pValue = 0;
        ret = TRUE;
    }
    else if (strcmp(ParamName, "RingEnable") == 0)
    {
        *pValue = 0;
        ret = TRUE;
    }
    else
    {
        CcspTraceWarning(("%s::Unknown ParamName:%s\n", __FUNCTION__, ParamName));
    }
    return ret;
}
BOOL Description_GetParamBoolValue(ANSC_HANDLE hInsContext, char* ParamName, BOOL* pBool)
{
    BOOL ret = FALSE;
    if (strcmp(ParamName, "RingEnable") == 0)
    {
        *pBool = TRUE;
        ret = TRUE;
    }
    else
    {
        CcspTraceWarning(("%s::Unknown ParamName:%s\n", __FUNCTION__, ParamName));
    }
    return ret;
}
BOOL Description_SetParamBoolValue(ANSC_HANDLE hInsContext, char* ParamName, BOOL bValue)
{
    return TRUE;
}

/**********************************************************************

    caller:     owner of this object

    prototype:

        LONG Description_GetParamStringValue(ANSC_HANDLE hInsContext, char* ParamName, char* pValue, ULONG* pUlSize);

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

LONG Description_GetParamStringValue(ANSC_HANDLE hInsContext, char* ParamName, char* pValue, ULONG* pUlSize)
{
    LONG ret = -1;
    if (strcmp(ParamName, "Alias") == 0)
    {
        AnscCopyString(pValue, "");
        return 0;
    }
    else if (strcmp(ParamName, "RingName") == 0)
    {
        AnscCopyString(pValue, "");
        return 0;
    }
    else if (strcmp(ParamName, "RingFile") == 0)
    {
        AnscCopyString(pValue, "");
        return 0;
    }
    else
    {
        CcspTraceWarning(("%s::Unknown ParamName:%s\n", __FUNCTION__, ParamName));
    }
    return ret;
}


/**********************************************************************

    caller:     owner of this object

    prototype:
        BOOL List_GetParamUlongValue(ANSC_HANDLE hInsContext, char* ParamName, ULONG* pValue);

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

BOOL List_GetParamUlongValue(ANSC_HANDLE hInsContext, char* ParamName, ULONG* pValue)
{
    BOOL ret = FALSE;

    if (strcmp(ParamName, "EntryID") == 0)
    {
        *pValue = 0;
        ret = TRUE;
    }
    else if (strcmp(ParamName, "BitRate") == 0)
    {
        *pValue = 0;
        ret = TRUE;
    }
    else if (strcmp(ParamName, "Priority") == 0)
    {
        *pValue = 0;
        ret = TRUE;
    }
    else
    {
        CcspTraceWarning(("%s::Unknown ParamName:%s\n", __FUNCTION__, ParamName));
    }
    return ret;
}

/**********************************************************************

        caller:     owner of this object

        prototype:

    BOOL List_GetParamBoolValue(ANSC_HANDLE hInsContext, char* ParamName, BOOL* pBool);

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
BOOL List_GetParamBoolValue(ANSC_HANDLE hInsContext, char* ParamName, BOOL* pBool)
{
        BOOL ret = FALSE;
        if (strcmp(ParamName, "SilenceSuppression") == 0)
        {
            ret = TRUE;
        }
        else if (strcmp(ParamName, "Enable") == 0)
        {
            ret = TRUE;
        }
        else
        {
            CcspTraceWarning(("%s::Unknown ParamName:%s\n", __FUNCTION__, ParamName));
        }
        return ret;
}
BOOL List_SetParamBoolValue(ANSC_HANDLE hInsContext, char* ParamName, BOOL bValue)
{
    BOOL    bStatus = FALSE;

    CcspTraceWarning(("%s::Exit\n", __FUNCTION__));
    return TRUE;
}


/**********************************************************************

    caller:     owner of this object

    prototype:

        BOOL List_SetParamUlongValue(ANSC_HANDLE hInsContext, char* ParamName, int iValue);

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
BOOL List_SetParamUlongValue(ANSC_HANDLE hInsContext, char* ParamName, int iValue)
{
    BOOL ret = FALSE;
    if (strcmp(ParamName, "Priority") == 0)
    {
        ret = TRUE;
    }
    else
    {
        CcspTraceWarning(("%s::Unknown ParamName:%s\n", __FUNCTION__, ParamName));
    }
    return ret;
}

/**********************************************************************

    caller:     owner of this object

    prototype:

        LONG List_GetParamStringValue(ANSC_HANDLE hInsContext, char* ParamName, char* pValue, ULONG* pUlSize);

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

LONG List_GetParamStringValue(ANSC_HANDLE hInsContext, char* ParamName, char* pValue, ULONG* pUlSize)
{
    LONG ret = -1;
    if (strcmp(ParamName, "Alias") == 0)
    {
        AnscCopyString(pValue, "");
        return 0;
    }
    else if (strcmp(ParamName, "Codec") == 0)
    {
        AnscCopyString(pValue, "");
        return 0;
    }
    else if (strcmp(ParamName, "PacketizationPeriod") == 0)
    {
        AnscCopyString(pValue, "");
        return 0;
    }
    else
    {
        CcspTraceWarning(("%s::Unknown ParamName:%s\n", __FUNCTION__, ParamName));
    }
    return ret;
}

/**********************************************************************

    caller:     owner of this object

    prototype:

        BOOL List_SetParamStringValue(ANSC_HANDLE hInsContext, char* ParamName, char* pString);

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
BOOL List_SetParamStringValue(ANSC_HANDLE hInsContext, char* ParamName, char* pString)
{
    BOOL ret = FALSE;
    if (strcmp(ParamName, "PacketizationPeriod") == 0)
    {
        ret = TRUE;
    }
    else if (strcmp(ParamName, "Alias") == 0)
    {
        ret = TRUE;
    }
    else
    {
        CcspTraceWarning(("%s::Unknown ParamName:%s\n", __FUNCTION__, ParamName));
    }
    return ret;
}


/**********************************************************************

    caller:     owner of this object

    prototype:
        BOOL Pattern_GetParamUlongValue(ANSC_HANDLE hInsContext, char* ParamName, ULONG* pValue);

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
BOOL Pattern_SetParamStringValue(ANSC_HANDLE hInsContext, char* ParamName, char* pString)
{
    CcspTraceWarning(("%s::Enter\n", __FUNCTION__));
    return TRUE;
}
BOOL Pattern_GetParamUlongValue(ANSC_HANDLE hInsContext, char* ParamName, ULONG* pValue)
{
    BOOL ret = FALSE;

    if (strcmp(ParamName, "Duration") == 0)
    {
        ret = TRUE;
    }
    else if (strcmp(ParamName, "NextEntryID") == 0)
    {
        ret = TRUE;
    }
    else if (strcmp(ParamName, "EntryID") == 0)
    {
        ret = TRUE;
    }
    else
    {
        CcspTraceWarning(("%s::Unknown ParamName:%s\n", __FUNCTION__, ParamName));
    }
    return ret;
}

/**********************************************************************

    caller:     owner of this object

    prototype:

        BOOL Pattern_SetParamUlongValue(ANSC_HANDLE hInsContext, char* ParamName, char* pString);

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
BOOL Pattern_SetParamUlongValue(ANSC_HANDLE hInsContext, char* ParamName, ULONG uValue)
{
    BOOL ret = FALSE;
    if (strcmp(ParamName, "EntryID") == 0)
    {
        ret = TRUE;
    }
    else if (strcmp(ParamName, "Duration") == 0)
    {
        ret = TRUE;
    }
    else if (strcmp(ParamName, "NextEntryID") == 0)
    {
        ret = TRUE;
    }
    else
    {
        CcspTraceWarning(("%s::Unknown ParamName:%s\n", __FUNCTION__, ParamName));
    }
    return ret;
}

/**********************************************************************

    caller:     owner of this object

    prototype:

        LONG Pattern_GetParamStringValue(ANSC_HANDLE hInsContext, char* ParamName, char* pValue, ULONG* pUlSize);

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

LONG Pattern_GetParamStringValue(ANSC_HANDLE hInsContext, char* ParamName, char* pValue, ULONG* pUlSize)
{
    ULONG ret = 1;
    if (strcmp(ParamName, "Alias") == 0)
    {
        AnscCopyString(pValue, "");
        return 0;
    }
    else
    {
        CcspTraceWarning(("%s::Unknown ParamName:%s\n", __FUNCTION__, ParamName));
        return -1; 
    }
    return ret;
}


/**********************************************************************

    caller:     owner of this object

    prototype:

    BOOL Pattern_GetParamBoolValue(ANSC_HANDLE hInsContext, char* ParamName, BOOL* pBool);

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
BOOL Pattern_GetParamBoolValue(ANSC_HANDLE hInsContext, char* ParamName, BOOL* pBool)
{
        BOOL ret = FALSE;
        if (strcmp(ParamName, "RingerOn") == 0)
        {
            ret = TRUE;
        }
        else
        {
            CcspTraceWarning(("%s::Unknown ParamName:%s\n", __FUNCTION__, ParamName));
        }
        return ret;
}

/**********************************************************************

    caller:     owner of this object

    prototype:

        BOOL Pattern_SetParamBoolValue(ANSC_HANDLE hInsContext, char* ParamName, char* pString);

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
BOOL Pattern_SetParamBoolValue(ANSC_HANDLE hInsContext, char* ParamName, BOOL bValue)
{
    BOOL ret = FALSE;
    if (strcmp(ParamName, "RingerOn") == 0)
    {
        ret = FALSE;
    }
    else
    {
        CcspTraceWarning(("%s::Unknown ParamName:%s\n", __FUNCTION__, ParamName));
    }
    return ret;
}

/**********************************************************************

        caller:     owner of this object

        prototype:

    BOOL LineCodec_GetParamBoolValue(ANSC_HANDLE hInsContext, char* ParamName, BOOL* pBool);

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
BOOL LineCodec_GetParamBoolValue(ANSC_HANDLE hInsContext, char* ParamName, BOOL* pBool)
{
        BOOL ret = FALSE;
        if (strcmp(ParamName, "TransmitSilenceSuppression") == 0)
        {
            ret = TRUE;
        }
        else if (strcmp(ParamName, "ReceiveSilenceSuppression") == 0)
        {
            ret = TRUE;
        }
        else
        {
            CcspTraceWarning(("%s::Unknown ParamName:%s\n", __FUNCTION__, ParamName));
        }
        return ret;
}

/**********************************************************************

    caller:     owner of this object

    prototype:
        BOOL LineCodec_GetParamUlongValue(ANSC_HANDLE hInsContext, char* ParamName, ULONG* pValue);

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

BOOL LineCodec_GetParamUlongValue(ANSC_HANDLE hInsContext, char* ParamName, ULONG* pValue)
{
    BOOL ret = FALSE;

    if (strcmp(ParamName, "TransmitBitRate") == 0)
    {
        *pValue = 0;
        ret = TRUE;
    }
    else if (strcmp(ParamName, "ReceiveBitRate") == 0)
    {
        *pValue = 0;
        ret = TRUE;
    }
    else if (strcmp(ParamName, "TransmitPacketizationPeriod") == 0)
    {
        *pValue = 0;
        ret = TRUE;
    }
    else
    {
        CcspTraceWarning(("%s::Unknown ParamName:%s\n", __FUNCTION__, ParamName));
    }
    return ret;
}

/**********************************************************************

    caller:     owner of this object

    prototype:

        LONG LineCodec_GetParamStringValue(ANSC_HANDLE hInsContext, char* ParamName, char* pValue, ULONG* pUlSize);

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

LONG LineCodec_GetParamStringValue(ANSC_HANDLE hInsContext, char* ParamName, char* pValue, ULONG* pUlSize)
{
    LONG ret = -1;
    if (strcmp(ParamName, "TransmitCodec") == 0)
    {
        AnscCopyString(pValue, "");
        return 0;
    }
    else if (strcmp(ParamName, "ReceiveCodec") == 0)
    {
        AnscCopyString(pValue, "");
        return 0;
    }
    else
    {
        CcspTraceWarning(("%s::Unknown ParamName:%s\n", __FUNCTION__, ParamName));
    }
    return ret;
}

/**********************************************************************

    caller:     owner of this object

    prototype:

        BOOL EventSubscribe_SetParamStringValue(ANSC_HANDLE hInsContext, char* ParamName, char* pString);

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
BOOL EventSubscribe_SetParamStringValue(ANSC_HANDLE hInsContext, char* ParamName, char* pString)
{
    BOOL ret = FALSE;
    if (strcmp(ParamName, "Alias") == 0)
    {
        ret = TRUE;
    }
    else if (strcmp(ParamName, "AuthUserName") == 0)
    {
        ret = TRUE;
    }
    else if (strcmp(ParamName, "AuthPassword") == 0)
    {
        ret = TRUE;
    }
    else
    {
        CcspTraceWarning(("%s::Unknown ParamName:%s\n", __FUNCTION__, ParamName));
    }
    return ret;
}

/**********************************************************************

    caller:     owner of this object

    prototype:

        LONG EventSubscribe_GetParamStringValue(ANSC_HANDLE hInsContext, char* ParamName, char* pValue, ULONG* pUlSize);

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

LONG EventSubscribe_GetParamStringValue(ANSC_HANDLE hInsContext, char* ParamName, char* pValue, ULONG* pUlSize)
{
    LONG ret = -1;
    if (strcmp(ParamName, "Alias") == 0)
    {
        AnscCopyString(pValue, "");
        ret  = 0;
    }
    else if (strcmp(ParamName, "Event") == 0)
    {
        AnscCopyString(pValue, "");
        ret = 0;
    }
    else if (strcmp(ParamName, "AuthUserName") == 0)
    {
        AnscCopyString(pValue, "");
        ret = 0;
    }
    else if (strcmp(ParamName, "AuthPassword") == 0)
    {
        AnscCopyString(pValue, "");
        ret = 0;
    }
    else
    {
        CcspTraceWarning(("%s::Unknown ParamName:%s\n", __FUNCTION__, ParamName));
    }
    return ret;
}


/**********************************************************************

    caller:     owner of this object

    prototype:

        BOOL Session_GetParamUlongValue(ANSC_HANDLE hInsContext, char* ParamName, char* pValue, ULONG* pUlSize);

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

    return:     

**********************************************************************/

BOOL Session_GetParamUlongValue(ANSC_HANDLE hInsContext, char* ParamName, ULONG* puLong)
{
    BOOL ret = FALSE;
    if (strcmp(ParamName, "SessionDuration") == 0)
    {
        *puLong = 0;
        ret = TRUE;
    }
    else if (strcmp(ParamName, "FarEndUDPPort") == 0)
    {
        *puLong = 0;
        ret = TRUE;
    }
    else if (strcmp(ParamName, "LocalUDPPort") == 0)
    {
        *puLong = 0;
        ret = TRUE;
    }
    else
    {
        CcspTraceWarning(("%s::Unknown ParamName:%s\n", __FUNCTION__, ParamName));
    }
    return ret;
}


/**********************************************************************

    caller:     owner of this object

    prototype:

        LONG Session_GetParamStringValue(ANSC_HANDLE hInsContext, char* ParamName, char* pValue, ULONG* pUlSize);

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

LONG Session_GetParamStringValue(ANSC_HANDLE hInsContext, char* ParamName, char* pValue, ULONG* pUlSize)
{
    LONG ret = -1;

    if (strcmp(ParamName, "SessionStartTime") == 0)
    {
        AnscCopyString(pValue, "");
        ret = 0;
    }
    else if (strcmp(ParamName, "FarEndIPAddress") == 0)
    {
        AnscCopyString(pValue, "");
        ret = 0;
    }
    else
    {
        CcspTraceWarning(("%s::Unknown ParamName:%s\n", __FUNCTION__, ParamName));
    }
    return ret;
}

LONG LineMGCP_GetParamStringValue(ANSC_HANDLE hInsContext, char* ParamName, char* pValue, ULONG* pUlSize)
{
    LONG ret = -1;
    PTELCOVOICEMGR_DML_LINE_SESSION pSession = NULL;
    if (strcmp(ParamName, "LineName") == 0)
    {
        AnscCopyString(pValue, "");
        ret = 0;
    }
    else
    {
        CcspTraceWarning(("%s::Unknown ParamName:%s\n", __FUNCTION__, ParamName));
    }
    return ret;
}
BOOL LineMGCP_SetParamStringValue(ANSC_HANDLE hInsContext, char* ParamName, char* pString)
{
    BOOL ret = FALSE;
    CcspTraceWarning(("%s::Unknown ParamName:%s\n", __FUNCTION__, ParamName));
        
    return ret;
}
LONG LineH323_GetParamStringValue(ANSC_HANDLE hInsContext, char* ParamName, char* pValue, ULONG* pUlSize)
{
    LONG ret = -1;
    if (strcmp(ParamName, "LineName") == 0)
    {
        AnscCopyString(pValue, "");
        ret = 0;
    }
    else if (strcmp(ParamName, "H323ID") == 0)
    {
        AnscCopyString(pValue, "");
        ret = 0;
    }
    else
    {
        CcspTraceWarning(("%s::Unknown ParamName:%s\n", __FUNCTION__, ParamName));
    }
    return ret;
}
BOOL LineH323_SetParamStringValue(ANSC_HANDLE hInsContext, char* ParamName, char* pString)
{
    BOOL ret = FALSE;

    CcspTraceWarning(("%s::Unknown ParamName:%s\n", __FUNCTION__, ParamName));
        
    return ret;
}

BOOL LineRinger_GetParamUlongValue(ANSC_HANDLE hInsContext, char* ParamName, ULONG* pValue)
{
    CcspTraceWarning(("%s::Unknown ParamName:%s\n", __FUNCTION__, ParamName));
    return FALSE;
}

/**********************************************************************

    caller:     owner of this object

    prototype:

        BOOL List_Validate(ANSC_HANDLE hInsContext);

    description:

        This function is called to validate the update.

    argument:   ANSC_HANDLE                 hInsContext,
                The instance handle;

    return:     TRUE if there's no issue.

**********************************************************************/
BOOL List_Validate(ANSC_HANDLE hInsContext)
{
    return TRUE;
}

/**********************************************************************

    caller:     owner of this object

    prototype:

        BOOL List_Commit(ANSC_HANDLE hInsContext);

    description:

        This function is called to validate the update.

    argument:   ANSC_HANDLE                 hInsContext,
                The instance handle;

    return:     0 if there's no issue.

**********************************************************************/

ULONG List_Commit(ANSC_HANDLE hInsContext)
{
    return 0;
}

/**********************************************************************

    caller:     owner of this object

    prototype:

        BOOL List_Rollback(ANSC_HANDLE hInsContext);

    description:

        This function is called to validate the update.

    argument:   ANSC_HANDLE                 hInsContext,
                The instance handle;

    return:     0 if there's no issue.

**********************************************************************/
ULONG List_Rollback(ANSC_HANDLE hInsContext)
{
    return 0;
}

/**********************************************************************

    caller:     owner of this object

    prototype:

        BOOL Session_Validate(ANSC_HANDLE hInsContext);

    description:

        This function is called to validate the update.

    argument:   ANSC_HANDLE                 hInsContext,
                The instance handle;

    return:     TRUE if there's no issue.

**********************************************************************/
BOOL Session_Validate(ANSC_HANDLE hInsContext)
{
    return TRUE;
}

/**********************************************************************

    caller:     owner of this object

    prototype:

        BOOL Session_Commit(ANSC_HANDLE hInsContext);

    description:

        This function is called to validate the update.

    argument:   ANSC_HANDLE                 hInsContext,
                The instance handle;

    return:     0 if there's no issue.

**********************************************************************/

ULONG Session_Commit(ANSC_HANDLE hInsContext)
{
    return 0;
}

/**********************************************************************

    caller:     owner of this object

    prototype:

        BOOL Session_Rollback(ANSC_HANDLE hInsContext);

    description:

        This function is called to validate the update.

    argument:   ANSC_HANDLE                 hInsContext,
                The instance handle;

    return:     0 if there's no issue.

**********************************************************************/
ULONG Session_Rollback(ANSC_HANDLE hInsContext)
{
    return 0;
}
