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
#include "telcovoicemgr_dml_v2.h"
#include "ccsp_trace.h"
#include "ccsp_syslog.h"
#include "telcovoicemgr_dml_hal_param_v2.h"

static char *bTrueStr = "true", *bFalseStr = "false";
/**********************************************************************

    caller:     owner of this object

    prototype:

        BOOL TelcoVoiceMgrDml_CallControl_GetParamUlongValue(ANSC_HANDLE hInsContext, char* ParamName, ULONG* puLong);

    description:

        This function is called to retrieve ULONG parameter value;

    argument:   ANSC_HANDLE                 hInsContext,
                The instance handle;

                char*                       ParamName,
                The parameter name;

                ULONG*                      puLong
                The buffer of returned ULONG value;

    return:     TRUE if succeeded.

**********************************************************************/

BOOL TelcoVoiceMgrDml_CallControl_GetParamUlongValue(ANSC_HANDLE hInsContext, char* ParamName, ULONG* puLong)
{
    BOOL ret = FALSE;

    if(ParamName == NULL || puLong == NULL)
    {
        CcspTraceWarning(("%s: Invalid Input Parameter [NULL]\n", __func__));
        return ret;
    }

    TELCOVOICEMGR_LOCK_OR_EXIT()

    PDML_VOICE_SERVICE_CTRL_T  pDmlVoiceServiceCtrl = (PDML_VOICE_SERVICE_CTRL_T)hInsContext;

    PTELCOVOICEMGR_DML_VOICESERVICE pDmlVoiceService = &(pDmlVoiceServiceCtrl->dml);

    PDML_CALLCONTROL pHEAD = &(pDmlVoiceService->CallControl_obj);

    if (strcmp(ParamName, "MaxNumberOfLines") == 0)
    {
        *puLong = pHEAD->MaxNumberOfLines;
        ret = TRUE;
    }
    else if (strcmp(ParamName, "MaxNumberOfExtensions") == 0)
    {
        *puLong = pHEAD->MaxNumberOfExtensions;
        ret = TRUE;
    }
    else
    {
        CcspTraceWarning(("%s: Unsupported parameter '%s'\n", __func__,ParamName));
    }

    TELCOVOICEMGR_UNLOCK()

    return ret;
}

/**********************************************************************

    caller:     owner of this object

    prototype:

        BOOL TelcoVoiceMgrDml_CallControl_SetParamUlongValue(ANSC_HANDLE hInsContext, char* ParamName, ULONG uValue);

    description:

        This function is called to set ULONG parameter value;

    argument:   ANSC_HANDLE                 hInsContext,
                The instance handle;

                char*                       ParamName,
                The parameter name;

                ULONG                       uValue
                The updated ULONG value;

    return:     TRUE if succeeded.

**********************************************************************/

BOOL TelcoVoiceMgrDml_CallControl_SetParamUlongValue(ANSC_HANDLE hInsContext, char* ParamName, ULONG uValue)
{
    BOOL ret = FALSE;

    ULONG uVsIndex = 0;

    char HalName[MAX_STR_LEN] = {0};

    if(ParamName == NULL)
    {
        CcspTraceWarning(("%s: Invalid Input Parameter [NULL]\n", __func__));
        return ret;
    }

    TELCOVOICEMGR_LOCK_OR_EXIT()

    PDML_VOICE_SERVICE_CTRL_T  pDmlVoiceServiceCtrl = (PDML_VOICE_SERVICE_CTRL_T)hInsContext;

    PTELCOVOICEMGR_DML_VOICESERVICE pDmlVoiceService = &(pDmlVoiceServiceCtrl->dml);

    PDML_CALLCONTROL pHEAD = &(pDmlVoiceService->CallControl_obj);

    if (pHEAD == NULL )
    {
        TELCOVOICEMGR_UNLOCK()

        CcspTraceError(("%s:%d:: pHEAD or pString NULL\n", __FUNCTION__, __LINE__));

        return ret;
    }

    uVsIndex = pDmlVoiceService->InstanceNumber;

    TELCOVOICEMGR_UNLOCK()

    if (strcmp(ParamName, "MaxNumberOfLines") == 0)
    {
        snprintf(HalName, MAX_STR_LEN, "Device.Services.VoiceService.%d.CallControl.MaxNumberOfLines",uVsIndex);

        if (TelcoVoiceMgrHal_SetParamULong(HalName,uValue) == ANSC_STATUS_SUCCESS)
        {
            TELCOVOICEMGR_LOCK_OR_EXIT()

            pHEAD->MaxNumberOfLines = uValue;

            TELCOVOICEMGR_UNLOCK()

            ret = TRUE;
        }
    }
    else if (strcmp(ParamName, "MaxNumberOfExtensions") == 0)
    {
        snprintf(HalName, MAX_STR_LEN, "Device.Services.VoiceService.%d.CallControl.MaxNumberOfExtensions",uVsIndex);

        if (TelcoVoiceMgrHal_SetParamULong(HalName,uValue) == ANSC_STATUS_SUCCESS)
        {
            TELCOVOICEMGR_LOCK_OR_EXIT()

            pHEAD->MaxNumberOfExtensions = uValue;

            TELCOVOICEMGR_UNLOCK()

            ret = TRUE;
        }
    }
    else
    {
        CcspTraceWarning(("%s: Unsupported parameter '%s'\n", __func__,ParamName));
    }

    return ret;
}

/**********************************************************************

    caller:     owner of this object

    prototype:

        BOOL TelcoVoiceMgrDml_CallControl_LineList_IsUpdated(ANSC_HANDLE hInsContext);

    description:

        This function is checking whether the table is updated or not.

    argument:   ANSC_HANDLE                 hInsContext,
                The instance handle;

    return:     TRUE or FALSE.

**********************************************************************/

BOOL TelcoVoiceMgrDml_CallControl_LineList_IsUpdated(ANSC_HANDLE hInsContext)
{
    return TRUE;
}

/**********************************************************************

    caller:     owner of this object

    prototype:

        ULONG TelcoVoiceMgrDml_CallControl_LineList_Synchronize(ANSC_HANDLE hInsContext);

    description:

        This function is called to synchronize the table.

    argument:   ANSC_HANDLE                 hInsContext,
                The instance handle;

    return:     The status of the operation.

**********************************************************************/

ULONG TelcoVoiceMgrDml_CallControl_LineList_Synchronize(ANSC_HANDLE hInsContext)
{
    return 0;
}

/**********************************************************************

    caller:     owner of this object

    prototype:

        ULONG TelcoVoiceMgrDml_CallControl_LineList_GetEntryCount(ANSC_HANDLE hInsContext);

    description:

        This function is called to retrieve the count of the table.

    argument:   ANSC_HANDLE                 hInsContext,
                The instance handle;

    return:     The count of the table

**********************************************************************/
ULONG TelcoVoiceMgrDml_CallControl_LineList_GetEntryCount(ANSC_HANDLE hInsContext)
{
    ULONG ret = 0;

    TELCOVOICEMGR_LOCK_OR_EXIT()

    DML_VOICE_SERVICE_CTRL_T* pVoiceService = (DML_VOICE_SERVICE_CTRL_T*) hInsContext;

    PTELCOVOICEMGR_DML_VOICESERVICE pDmlVoiceService = &(pVoiceService->dml);

    PDML_CALLCONTROL_LINE_LIST_T pCallControlLineList = &(pDmlVoiceService->CallControl_obj.Line);

    if(pCallControlLineList != NULL)
    {
        ret = pCallControlLineList->ulQuantity;
    }

    TELCOVOICEMGR_UNLOCK()

    return ret;
}

/**********************************************************************

    caller:     owner of this object

    prototype:

        ANSC_HANDLE TelcoVoiceMgrDml_CallControl_LineList_GetEntry(ANSC_HANDLE hInsContext, ULONG nIndex, ULONG* pInsNumber);

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
ANSC_HANDLE TelcoVoiceMgrDml_CallControl_LineList_GetEntry(ANSC_HANDLE hInsContext, ULONG nIndex, ULONG* pInsNumber)
{
    ANSC_HANDLE ret = NULL;

    TELCOVOICEMGR_LOCK_OR_EXIT()

    PDML_VOICE_SERVICE_CTRL_T pVoiceService = (PDML_VOICE_SERVICE_CTRL_T) hInsContext;

    PTELCOVOICEMGR_DML_VOICESERVICE pDmlVoiceService = &(pVoiceService->dml);

    PDML_CALLCONTROL_LINE_LIST_T pLineList = &(pDmlVoiceService->CallControl_obj.Line);

    if(pLineList != NULL)
    {
        if(nIndex < pLineList->ulQuantity)
        {
            PDML_CALLCONTROL_LINE_CTRL_T pLineCtrl = pLineList->pdata[nIndex];
            if(pLineCtrl != NULL)
            {
               *pInsNumber = nIndex + 1;
               ret = (ANSC_HANDLE) pLineCtrl;
            }
        }
    }

    TELCOVOICEMGR_UNLOCK()

    return ret;
}

/**********************************************************************

    caller:     owner of this object

    prototype:

        BOOL TelcoVoiceMgrDml_CallControl_LineList_GetParamUlongValue(ANSC_HANDLE hInsContext, char* ParamName, ULONG* puLong);

    description:

        This function is called to retrieve ULONG parameter value;

    argument:   ANSC_HANDLE                 hInsContext,
                The instance handle;

                char*                       ParamName,
                The parameter name;

                ULONG*                      puLong
                The buffer of returned ULONG value;

    return:     TRUE if succeeded.

**********************************************************************/

BOOL TelcoVoiceMgrDml_CallControl_LineList_GetParamUlongValue(ANSC_HANDLE hInsContext, char* ParamName, ULONG* puLong)
{
    BOOL ret = FALSE;
    ULONG uVsIndex  = 0;
    ULONG uCCLineIndex = 0;
    PTELCOVOICEMGR_DML_VOICESERVICE pDmlVoiceService = NULL;
 
    TELCOVOICEMGR_LINE_STATUS_ENUM lineStatus = VOICE_LINE_STATE_DISABLED;
    TELCOVOICEMGR_CALL_STATE_ENUM  callStatus = VOICE_CALL_STATE_IDLE;

    if(ParamName == NULL || puLong == NULL)
    {
        CcspTraceWarning(("%s: Invalid Input Parameter [NULL]\n", __func__));
        return ret;
    }

    TELCOVOICEMGR_LOCK_OR_EXIT()

    PDML_CALLCONTROL_LINE_CTRL_T pCallCtrlLineCtrl = (PDML_CALLCONTROL_LINE_CTRL_T)hInsContext;

    PDML_CALLCONTROL_LINE pHEAD = &(pCallCtrlLineCtrl->dml);

    if(pHEAD != NULL)
    {
        pDmlVoiceService = (PTELCOVOICEMGR_DML_VOICESERVICE)pHEAD->pParentVoiceService;
    }

    if (pHEAD == NULL  || pDmlVoiceService == NULL)
    {
        TELCOVOICEMGR_UNLOCK()

        CcspTraceError(("%s:%d:: pHEAD or pDmlVoiceService NULL\n", __FUNCTION__, __LINE__));

        return ret;
    }

    uVsIndex = pDmlVoiceService->InstanceNumber;

    uCCLineIndex = pHEAD->uInstanceNumber;

    TELCOVOICEMGR_UNLOCK()

    if (strcmp(ParamName, "Status") == 0)
    {

        if(ANSC_STATUS_SUCCESS == TelcoVoiceMgrDmlGetLineStatus(uVsIndex, TELCOVOICEMGR_DML_NUMBER_OF_VOIP_PROFILE,
                                             uCCLineIndex, &lineStatus))
        {
            TELCOVOICEMGR_LOCK_OR_EXIT()

            pHEAD->Status = lineStatus;
            *puLong = pHEAD->Status;

            TELCOVOICEMGR_UNLOCK()

            ret = TRUE;
        }
    }
    else if (strcmp(ParamName, "Origin") == 0)
    {
        *puLong = pHEAD->Origin;
        ret = TRUE;
    }
    else if (strcmp(ParamName, "CallStatus") == 0)
    {
        //Fetch status from voice stack
        if(ANSC_STATUS_SUCCESS == TelcoVoiceMgrDmlGetLineCallState(uVsIndex, TELCOVOICEMGR_DML_NUMBER_OF_VOIP_PROFILE,
                                             uCCLineIndex, &callStatus))
        {
            TELCOVOICEMGR_LOCK_OR_EXIT()

            pHEAD->CallStatus = callStatus;
            *puLong = pHEAD->CallStatus;

            TELCOVOICEMGR_UNLOCK()

            ret = TRUE;
        }
        else
        {
            CcspTraceError(("%s:%d:: Status:get failed \n", __FUNCTION__, __LINE__));
            ret = FALSE;
        }
    }
    else
    {
        CcspTraceWarning(("%s: Unsupported parameter '%s'\n", __func__,ParamName));
    }

    return ret;
}

/**********************************************************************

    caller:     owner of this object

    prototype:

        ULONG TelcoVoiceMgrDml_CallControl_LineList_GetParamStringValue(ANSC_HANDLE hInsContext, char* ParamName, char* pValue, ULONG* pulSize);

    description:

        This function is called to retrieve string parameter value;

    argument:   ANSC_HANDLE                 hInsContext,
                The instance handle;

                char*                       ParamName,
                The parameter name;

                char*                       pValue,
                The string value buffer;

                ULONG*                      pUlSize
                The buffer of length of string value;
                Usually size of 1023 will be used.
                If it's not big enough, put required size here and return 1;

    return:     0 if succeeded;
                1 if short of buffer size; (*pUlSize = required size)
                -1 if not supported.

**********************************************************************/

ULONG TelcoVoiceMgrDml_CallControl_LineList_GetParamStringValue(ANSC_HANDLE hInsContext, char* ParamName, char* pValue, ULONG* pulSize)
{
    ULONG ret = 1;

    if(ParamName == NULL || pValue == NULL || pulSize == NULL)
    {
        CcspTraceWarning(("%s: Invalid Input Parameter [NULL]\n", __func__));
        return ret;
    }

    TELCOVOICEMGR_LOCK_OR_EXIT()

    PDML_CALLCONTROL_LINE_CTRL_T pCallCtrlLineCtrl = (PDML_CALLCONTROL_LINE_CTRL_T)hInsContext;

    PDML_CALLCONTROL_LINE pHEAD = &(pCallCtrlLineCtrl->dml);

    if (strcmp(ParamName, "Provider") == 0)
    {
        AnscCopyString(pValue,pHEAD->Provider);
        ret = 0;
    }
    else if (strcmp(ParamName, "DirectoryNumber") == 0)
    {
        AnscCopyString(pValue,pHEAD->DirectoryNumber);
        ret = 0;
    }
    else if (strcmp(ParamName, "CallingFeatures") == 0)
    {
        AnscCopyString(pValue,pHEAD->CallingFeatures);
        ret = 0;
    }
    else if (strcmp(ParamName, "Alias") == 0)
    {
        AnscCopyString(pValue,pHEAD->Alias);
        ret = 0;
    }
    else
    {
        CcspTraceWarning(("%s: Unsupported parameter '%s'\n", __func__,ParamName));
    }

    TELCOVOICEMGR_UNLOCK()

    return ret;
}

/**********************************************************************

    caller:     owner of this object

    prototype:

        BOOL TelcoVoiceMgrDml_CallControl_LineList_SetParamStringValue(ANSC_HANDLE hInsContext, char* ParamName, char* pString);

    description:

        This function is called to set string parameter value;

    argument:   ANSC_HANDLE                 hInsContext,
                The instance handle;

                char*                       ParamName,
                The parameter name;

                char*                       pString
                The updated string value;

    return:     TRUE if succeeded.

**********************************************************************/

BOOL TelcoVoiceMgrDml_CallControl_LineList_SetParamStringValue(ANSC_HANDLE hInsContext, char* ParamName, char* pString)
{
    BOOL ret = FALSE;
    ULONG uVsIndex  = 0;
    ULONG uLineIndex = 0;
    char HalName[MAX_STR_LEN] = {0};

    PTELCOVOICEMGR_DML_VOICESERVICE pDmlVoiceService = NULL;

    if(ParamName == NULL)
    {
        CcspTraceWarning(("%s: Invalid Input Parameter [NULL]\n", __func__));
        return ret;
    }

    TELCOVOICEMGR_LOCK_OR_EXIT()

    PDML_CALLCONTROL_LINE_CTRL_T pCallCtrlLineCtrl = (PDML_CALLCONTROL_LINE_CTRL_T)hInsContext;

    PDML_CALLCONTROL_LINE pHEAD = &(pCallCtrlLineCtrl->dml);

    if(pHEAD != NULL)
    {
        pDmlVoiceService = (PTELCOVOICEMGR_DML_VOICESERVICE)pHEAD->pParentVoiceService;
    }

    if (pHEAD == NULL  || pDmlVoiceService == NULL)
    {
        TELCOVOICEMGR_UNLOCK()

        CcspTraceError(("%s:%d:: pHEAD or pDmlVoiceService NULL\n", __FUNCTION__, __LINE__));

        return ret;
    }

    uVsIndex = pDmlVoiceService->InstanceNumber;

    uLineIndex = pHEAD->uInstanceNumber;

    TELCOVOICEMGR_UNLOCK()

    if (strcmp(ParamName, "Provider") == 0)
    {
        snprintf(HalName, MAX_STR_LEN, "Device.Services.VoiceService.%d.CallControl.Line.%d.Provider",uVsIndex,uLineIndex);

        if (TelcoVoiceMgrHal_SetParamString(HalName,pString) == ANSC_STATUS_SUCCESS)
        {
            TELCOVOICEMGR_LOCK_OR_EXIT()

            AnscCopyString(pHEAD->Provider,pString);

            TELCOVOICEMGR_UNLOCK()

            ret = TRUE;
        }
    }
    else if (strcmp(ParamName, "DirectoryNumber") == 0)
    {
        snprintf(HalName, MAX_STR_LEN, "Device.Services.VoiceService.%d.CallControl.Line.%d.DirectoryNumber",uVsIndex,uLineIndex);

        if (TelcoVoiceMgrHal_SetParamString(HalName,pString) == ANSC_STATUS_SUCCESS)
        {
            TELCOVOICEMGR_LOCK_OR_EXIT()

            AnscCopyString(pHEAD->DirectoryNumber,pString);

            TELCOVOICEMGR_UNLOCK()

            ret = TRUE;
        }
    }
    else if (strcmp(ParamName, "CallingFeatures") == 0)
    {
        snprintf(HalName, MAX_STR_LEN, "Device.Services.VoiceService.%d.CallControl.Line.%d.CallingFeatures",uVsIndex,uLineIndex);

        if (TelcoVoiceMgrHal_SetParamString(HalName,pString) == ANSC_STATUS_SUCCESS)
        {
            TELCOVOICEMGR_LOCK_OR_EXIT()

            AnscCopyString(pHEAD->CallingFeatures,pString);

            TELCOVOICEMGR_UNLOCK()

            ret = TRUE;
        }
    }
    else if (strcmp(ParamName, "Alias") == 0)
    {
        TELCOVOICEMGR_LOCK_OR_EXIT()

        AnscCopyString(pHEAD->Alias,pString);

        TELCOVOICEMGR_UNLOCK()

        ret = TRUE;
    }
    else
    {
        CcspTraceWarning(("%s: Unsupported parameter '%s'\n", __func__,ParamName));
    }

    return ret;

}

/**********************************************************************

    caller:     owner of this object

    prototype:

        BOOL TelcoVoiceMgrDml_CallControl_LineList_GetParamBoolValue(ANSC_HANDLE hInsContext, char* ParamName, BOOL* pBool);

    description:

        This function is called to retrieve Boolean parameter value;

    argument:   ANSC_HANDLE                 hInsContext,
                The instance handle;

                char*                       ParamName,
                The parameter name;

                BOOL*                       pBool
                The buffer of returned boolean value;

    return:     TRUE if succeeded.

**********************************************************************/

BOOL TelcoVoiceMgrDml_CallControl_LineList_GetParamBoolValue(ANSC_HANDLE hInsContext, char* ParamName, BOOL* pBool)
{
    BOOL ret = FALSE;

    if(ParamName == NULL || pBool == NULL)
    {
        CcspTraceWarning(("%s: Invalid Input Parameter [NULL]\n", __func__));
        return ret;
    }

    TELCOVOICEMGR_LOCK_OR_EXIT()

    PDML_CALLCONTROL_LINE_CTRL_T pCallCtrlLineCtrl = (PDML_CALLCONTROL_LINE_CTRL_T)hInsContext;

    PDML_CALLCONTROL_LINE pHEAD = &(pCallCtrlLineCtrl->dml);

    if (strcmp(ParamName, "QuiescentMode") == 0)
    {
        *pBool = pHEAD->QuiescentMode;
        ret = TRUE;
    }
    else if (strcmp(ParamName, "Enable") == 0)
    {
        *pBool = pHEAD->Enable;
        ret = TRUE;
    }
    else
    {
        CcspTraceWarning(("%s: Unsupported parameter '%s'\n", __func__,ParamName));
    }

    TELCOVOICEMGR_UNLOCK()

    return ret;
}

/**********************************************************************

    caller:     owner of this object

    prototype:

        BOOL TelcoVoiceMgrDml_CallControl_LineList_SetParamBoolValue(ANSC_HANDLE hInsContext, char* ParamName, BOOL bValue);

    description:

        This function is called to set BOOL parameter value;

    argument:   ANSC_HANDLE                 hInsContext,
                The instance handle;

                char*                       ParamName,
                The parameter name;

                BOOL                        bValue
                The updated BOOL value;

    return:     TRUE if succeeded.

**********************************************************************/

BOOL TelcoVoiceMgrDml_CallControl_LineList_SetParamBoolValue(ANSC_HANDLE hInsContext, char* ParamName, BOOL bValue)
{
    BOOL ret = FALSE;
    ULONG uVsIndex  = 0;
    ULONG uLineIndex = 0;
    char HalName[MAX_STR_LEN] = {0};

    PTELCOVOICEMGR_DML_VOICESERVICE pDmlVoiceService = NULL;

    if(ParamName == NULL)
    {
        CcspTraceWarning(("%s: Invalid Input Parameter [NULL]\n", __func__));
        return ret;
    }

    TELCOVOICEMGR_LOCK_OR_EXIT()

    PDML_CALLCONTROL_LINE_CTRL_T pCallCtrlLineCtrl = (PDML_CALLCONTROL_LINE_CTRL_T)hInsContext;

    PDML_CALLCONTROL_LINE pHEAD = &(pCallCtrlLineCtrl->dml);

    if(pHEAD != NULL)
    {
        pDmlVoiceService = (PTELCOVOICEMGR_DML_VOICESERVICE)pHEAD->pParentVoiceService;
    }

    if (pHEAD == NULL  || pDmlVoiceService == NULL)
    {
        TELCOVOICEMGR_UNLOCK()

        CcspTraceError(("%s:%d:: pHEAD or pDmlVoiceService NULL\n", __FUNCTION__, __LINE__));

        return ret;
    }

    uVsIndex = pDmlVoiceService->InstanceNumber;

    uLineIndex = pHEAD->uInstanceNumber;

    TELCOVOICEMGR_UNLOCK()

    if (strcmp(ParamName, "QuiescentMode") == 0)
    {
        snprintf(HalName, MAX_STR_LEN, "Device.Services.VoiceService.%d.CallControl.Line.%d.QuiescentMode",uVsIndex,uLineIndex);

        if (TelcoVoiceMgrHal_SetParamBool(HalName,bValue) == ANSC_STATUS_SUCCESS)
        {
            TELCOVOICEMGR_LOCK_OR_EXIT()

            pHEAD->QuiescentMode = bValue;

            TELCOVOICEMGR_UNLOCK()

            ret = TRUE;
        }
    }
    else if (strcmp(ParamName, "Enable") == 0)
    {
        snprintf(HalName, MAX_STR_LEN, "Device.Services.VoiceService.%d.CallControl.Line.%d.Enable",uVsIndex,uLineIndex);

        if (TelcoVoiceMgrHal_SetParamBool(HalName,bValue) == ANSC_STATUS_SUCCESS)
        {
            TELCOVOICEMGR_LOCK_OR_EXIT()

            pHEAD->Enable = bValue;

            TELCOVOICEMGR_UNLOCK()

            ret = TRUE;
        }
    }
    else
    {
        CcspTraceWarning(("%s: Unsupported parameter '%s'\n", __func__,ParamName));
    }

    return ret;

}

/**********************************************************************

    caller:     owner of this object

    prototype:

        BOOL TelcoVoiceMgrDml_CallControl_LineList_Validate(ANSC_HANDLE hInsContext);

    description:

        This function is called to validate the update.

    argument:   ANSC_HANDLE                 hInsContext,
                The instance handle;

    return:     TRUE if there's no issue.

**********************************************************************/

BOOL TelcoVoiceMgrDml_CallControl_LineList_Validate(ANSC_HANDLE hInsContext)
{
    return TRUE;
}

/**********************************************************************

    caller:     owner of this object

    prototype:

        BOOL TelcoVoiceMgrDml_CallControl_LineList_Commit(ANSC_HANDLE hInsContext);

    description:

        This function is called to commit the update.

    argument:   ANSC_HANDLE                 hInsContext,
                The instance handle;

    return:     0 if there's no issue.

**********************************************************************/

BOOL TelcoVoiceMgrDml_CallControl_LineList_Commit(ANSC_HANDLE hInsContext)
{
    return 0;
}

/**********************************************************************

    caller:     owner of this object

    prototype:

        BOOL TelcoVoiceMgrDml_CallControl_LineList_Rollback(ANSC_HANDLE hInsContext);

    description:

        This function is called to rollback the update.

    argument:   ANSC_HANDLE                 hInsContext,
                The instance handle;

    return:     0 if there's no issue.

**********************************************************************/

BOOL TelcoVoiceMgrDml_CallControl_LineList_Rollback(ANSC_HANDLE hInsContext)
{
    return 0;
}

/**********************************************************************

    caller:     owner of this object

    prototype:

        BOOL TelcoVoiceMgrDml_CallControl_LineList_stats_InCalls_GetParamUlongValue(ANSC_HANDLE hInsContext, char* ParamName, ULONG* puLong);

    description:

        This function is called to retrieve ULONG parameter value;

    argument:   ANSC_HANDLE                 hInsContext,
                The instance handle;

                char*                       ParamName,
                The parameter name;

                ULONG*                      puLong
                The buffer of returned ULONG value;

    return:     TRUE if succeeded.

**********************************************************************/

BOOL TelcoVoiceMgrDml_CallControl_LineList_stats_InCalls_GetParamUlongValue(ANSC_HANDLE hInsContext, char* ParamName, ULONG* puLong)
{
    BOOL ret = FALSE;
    ULONG uVsIndex  = 0;
    char HalName[MAX_STR_LEN] = {0};
    BOOL bIsUpdated   = FALSE;
    TELCOVOICEMGR_DML_VOICESERVICE_STATS  stVoiceStats;
    PTELCOVOICEMGR_DML_VOICESERVICE pDmlVoiceService = NULL;

    if(ParamName == NULL || puLong == NULL)
    {
        CcspTraceWarning(("%s: Invalid Input Parameter [NULL]\n", __func__));
        return ret;
    }

    TELCOVOICEMGR_LOCK_OR_EXIT()

    PDML_CALLCONTROL_LINE_CTRL_T pCallCtrlLineCtrl = (PDML_CALLCONTROL_LINE_CTRL_T)hInsContext;

    PDML_CALLCONTROL_LINE pDmlCallCtrlLine = &(pCallCtrlLineCtrl->dml);

    PDML_CALLCONTROL_STATS_INCALLS  pHEAD = &(pDmlCallCtrlLine->Stats.IncomingCalls);

    pDmlVoiceService = (PTELCOVOICEMGR_DML_VOICESERVICE)pDmlCallCtrlLine->pParentVoiceService;
    uVsIndex = pDmlVoiceService->InstanceNumber;

    if ( ( AnscGetTickInSeconds() - pCallCtrlLineCtrl->PreviousVisitTimeOfLine) < 10 )
    {
        bIsUpdated  = TRUE;
    }
    else
    {
        pCallCtrlLineCtrl->PreviousVisitTimeOfLine =  AnscGetTickInSeconds();
        bIsUpdated  = FALSE;
    }

    if(!bIsUpdated)
    {
        TELCOVOICEMGR_UNLOCK()

        snprintf(HalName, MAX_STR_LEN, "Device.Services.VoiceService.%d.CallControl.Line.%d.Stats.", uVsIndex, pDmlCallCtrlLine->uInstanceNumber);
        TelcoVoiceHal_GetLineStats(HalName, &stVoiceStats);

        TELCOVOICEMGR_LOCK_OR_EXIT()

        TelcoVoiceMgrDml_MapLineStats(pDmlCallCtrlLine, &stVoiceStats);
    }
    if (strcmp(ParamName, "TotalCallTime") == 0)
    {
        *puLong = pHEAD->TotalCallTime;
        ret = TRUE;
    }
    else if (strcmp(ParamName, "CallsReceived") == 0)
    {
        *puLong = pHEAD->CallsReceived;
        ret = TRUE;
    }
    else if (strcmp(ParamName, "CallsFailed") == 0)
    {
        *puLong = pHEAD->CallsFailed;
        ret = TRUE;
    }
    else if (strcmp(ParamName, "CallsDropped") == 0)
    {
        *puLong = pHEAD->CallsDropped;
        ret = TRUE;
    }
    else if (strcmp(ParamName, "CallsConnected") == 0)
    {
        *puLong = pHEAD->CallsConnected;
        ret = TRUE;
    }
    else
    {
        CcspTraceWarning(("%s: Unsupported parameter '%s'\n", __func__,ParamName));
    }

    TELCOVOICEMGR_UNLOCK()

    return ret;
}

/**********************************************************************

    caller:     owner of this object

    prototype:

        BOOL TelcoVoiceMgrDml_CallControl_LineList_stats_OutCalls_GetParamUlongValue(ANSC_HANDLE hInsContext, char* ParamName, ULONG* puLong);

    description:

        This function is called to retrieve ULONG parameter value;

    argument:   ANSC_HANDLE                 hInsContext,
                The instance handle;

                char*                       ParamName,
                The parameter name;

                ULONG*                      puLong
                The buffer of returned ULONG value;

    return:     TRUE if succeeded.

**********************************************************************/

BOOL TelcoVoiceMgrDml_CallControl_LineList_stats_OutCalls_GetParamUlongValue(ANSC_HANDLE hInsContext, char* ParamName, ULONG* puLong)
{
    BOOL ret = FALSE;
    ULONG uVsIndex  = 0;
    char HalName[MAX_STR_LEN] = {0};
    BOOL bIsUpdated   = FALSE;
    TELCOVOICEMGR_DML_VOICESERVICE_STATS  stVoiceStats;
    PTELCOVOICEMGR_DML_VOICESERVICE pDmlVoiceService = NULL;

    if(ParamName == NULL || puLong == NULL)
    {
        CcspTraceWarning(("%s: Invalid Input Parameter [NULL]\n", __func__));
        return ret;
    }

    TELCOVOICEMGR_LOCK_OR_EXIT()

    PDML_CALLCONTROL_LINE_CTRL_T pCallCtrlLineCtrl = (PDML_CALLCONTROL_LINE_CTRL_T)hInsContext;

    PDML_CALLCONTROL_LINE pDmlCallCtrlLine = &(pCallCtrlLineCtrl->dml);

    PDML_CALLCONTROL_STATS_OUTCALLS  pHEAD = &(pDmlCallCtrlLine->Stats.OutgoingCalls);

    pDmlVoiceService = (PTELCOVOICEMGR_DML_VOICESERVICE)pDmlCallCtrlLine->pParentVoiceService;
    uVsIndex = pDmlVoiceService->InstanceNumber;

    if ( ( AnscGetTickInSeconds() - pCallCtrlLineCtrl->PreviousVisitTimeOfLine) < 10 )
    {
        bIsUpdated  = TRUE;
    }
    else
    {
        pCallCtrlLineCtrl->PreviousVisitTimeOfLine =  AnscGetTickInSeconds();
        bIsUpdated  = FALSE;
    }

    if(!bIsUpdated)
    {
        TELCOVOICEMGR_UNLOCK()

        snprintf(HalName, MAX_STR_LEN, "Device.Services.VoiceService.%d.CallControl.Line.%d.Stats.", uVsIndex, pDmlCallCtrlLine->uInstanceNumber);
        TelcoVoiceHal_GetLineStats(HalName, &stVoiceStats);

        TELCOVOICEMGR_LOCK_OR_EXIT()

        TelcoVoiceMgrDml_MapLineStats(pDmlCallCtrlLine, &stVoiceStats);        CcspTraceWarning(("%s: %d\n", __func__, __LINE__));
    }

    if (strcmp(ParamName, "TotalCallTime") == 0)
    {
        *puLong = pHEAD->TotalCallTime;
        ret = TRUE;
    }
    else if (strcmp(ParamName, "CallsFailed") == 0)
    {
        *puLong = pHEAD->CallsFailed;
        ret = TRUE;
    }
    else if (strcmp(ParamName, "CallsDropped") == 0)
    {
        *puLong = pHEAD->CallsDropped;
        ret = TRUE;
    }
    else if (strcmp(ParamName, "CallsConnected") == 0)
    {
        *puLong = pHEAD->CallsConnected;
        ret = TRUE;
    }
    else if (strcmp(ParamName, "CallsAttempted") == 0)
    {
        *puLong = pHEAD->CallsAttempted;
        ret = TRUE;
    }
    else
    {
        CcspTraceWarning(("%s: Unsupported parameter '%s'\n", __func__,ParamName));
    }


    TELCOVOICEMGR_UNLOCK()

    return ret;
}

/**********************************************************************

    caller:     owner of this object

    prototype:

        BOOL TelcoVoiceMgrDml_CallControl_LineList_stats_RTP_GetParamUlongValue(ANSC_HANDLE hInsContext, char* ParamName, ULONG* puLong);

    description:

        This function is called to retrieve ULONG parameter value;

    argument:   ANSC_HANDLE                 hInsContext,
                The instance handle;

                char*                       ParamName,
                The parameter name;

                ULONG*                      puLong
                The buffer of returned ULONG value;

    return:     TRUE if succeeded.

**********************************************************************/

BOOL TelcoVoiceMgrDml_CallControl_LineList_stats_RTP_GetParamUlongValue(ANSC_HANDLE hInsContext, char* ParamName, ULONG* puLong)
{
    BOOL ret = FALSE;
    ULONG uVsIndex  = 0;
    char HalName[MAX_STR_LEN] = {0};
    BOOL bIsUpdated   = FALSE;
    TELCOVOICEMGR_DML_VOICESERVICE_STATS  stVoiceStats;
    PTELCOVOICEMGR_DML_VOICESERVICE pDmlVoiceService = NULL;

    if(ParamName == NULL || puLong == NULL)
    {
        CcspTraceWarning(("%s: Invalid Input Parameter [NULL]\n", __func__));
        return ret;
    }

    TELCOVOICEMGR_LOCK_OR_EXIT()

    PDML_CALLCONTROL_LINE_CTRL_T pCallCtrlLineCtrl = (PDML_CALLCONTROL_LINE_CTRL_T)hInsContext;

    PDML_CALLCONTROL_LINE pDmlCallCtrlLine = &(pCallCtrlLineCtrl->dml);

    PDML_CALLCONTROL_STATS_RTP  pHEAD = &(pDmlCallCtrlLine->Stats.RTP);

    pDmlVoiceService = (PTELCOVOICEMGR_DML_VOICESERVICE)pDmlCallCtrlLine->pParentVoiceService;
    uVsIndex = pDmlVoiceService->InstanceNumber;

    if ( ( AnscGetTickInSeconds() - pCallCtrlLineCtrl->PreviousVisitTimeOfLine) < 10 )
    {
        bIsUpdated  = TRUE;
    }
    else
    {
        pCallCtrlLineCtrl->PreviousVisitTimeOfLine =  AnscGetTickInSeconds();
        bIsUpdated  = FALSE;
    }

    if(!bIsUpdated)
    {
        TELCOVOICEMGR_UNLOCK()

        snprintf(HalName, MAX_STR_LEN, "Device.Services.VoiceService.%d.CallControl.Line.%d.Stats.", uVsIndex, pDmlCallCtrlLine->uInstanceNumber);
        TelcoVoiceHal_GetLineStats(HalName, &stVoiceStats);

        TELCOVOICEMGR_LOCK_OR_EXIT()

        TelcoVoiceMgrDml_MapLineStats(pDmlCallCtrlLine, &stVoiceStats);
    }

    if (strcmp(ParamName, "PacketsSent") == 0)
    {
        *puLong = pHEAD->PacketsSent;
        ret = TRUE;
    }
    else if (strcmp(ParamName, "PacketsReceived") == 0)
    {
        *puLong = pHEAD->PacketsReceived;
        ret = TRUE;
    }
    else if (strcmp(ParamName, "PacketsLost") == 0)
    {
        *puLong = pHEAD->PacketsLost;
        ret = TRUE;
    }
    else if (strcmp(ParamName, "BytesSent") == 0)
    {
        *puLong = pHEAD->BytesSent;
        ret = TRUE;
    }
    else if (strcmp(ParamName, "BytesReceived") == 0)
    {
        *puLong = pHEAD->BytesReceived;
        ret = TRUE;
    }
    else
    {
        CcspTraceWarning(("%s: Unsupported parameter '%s'\n", __func__,ParamName));
    }
    TELCOVOICEMGR_UNLOCK()

    return ret;
}

/**********************************************************************

    caller:     owner of this object

    prototype:

        BOOL TelcoVoiceMgrDml_CallControl_LineList_stats_DSP_GetParamUlongValue(ANSC_HANDLE hInsContext, char* ParamName, ULONG* puLong);

    description:

        This function is called to retrieve ULONG parameter value;

    argument:   ANSC_HANDLE                 hInsContext,
                The instance handle;

                char*                       ParamName,
                The parameter name;

                ULONG*                      puLong
                The buffer of returned ULONG value;

    return:     TRUE if succeeded.

**********************************************************************/

BOOL TelcoVoiceMgrDml_CallControl_LineList_stats_DSP_GetParamUlongValue(ANSC_HANDLE hInsContext, char* ParamName, ULONG* puLong)
{
    BOOL ret = FALSE;
    ULONG uVsIndex  = 0;
    char HalName[MAX_STR_LEN] = {0};
    BOOL bIsUpdated   = FALSE;
    TELCOVOICEMGR_DML_VOICESERVICE_STATS  stVoiceStats;
    PTELCOVOICEMGR_DML_VOICESERVICE pDmlVoiceService = NULL;

    if(ParamName == NULL || puLong == NULL)
    {
        CcspTraceWarning(("%s: Invalid Input Parameter [NULL]\n", __func__));
        return ret;
    }

    TELCOVOICEMGR_LOCK_OR_EXIT()

    PDML_CALLCONTROL_LINE_CTRL_T pCallCtrlLineCtrl = (PDML_CALLCONTROL_LINE_CTRL_T)hInsContext;

    PDML_CALLCONTROL_LINE pDmlCallCtrlLine = &(pCallCtrlLineCtrl->dml);

    PDML_CALLCONTROL_STATS_DSP  pHEAD = &(pDmlCallCtrlLine->Stats.DSP);

    pDmlVoiceService = (PTELCOVOICEMGR_DML_VOICESERVICE)pDmlCallCtrlLine->pParentVoiceService;
    uVsIndex = pDmlVoiceService->InstanceNumber;

    if ( ( AnscGetTickInSeconds() - pCallCtrlLineCtrl->PreviousVisitTimeOfLine) < 10 )
    {
        bIsUpdated  = TRUE;

    }
    else
    {
        pCallCtrlLineCtrl->PreviousVisitTimeOfLine =  AnscGetTickInSeconds();
        bIsUpdated  = FALSE;
    }

    if(!bIsUpdated)
    {
        TELCOVOICEMGR_UNLOCK()

        snprintf(HalName, MAX_STR_LEN, "Device.Services.VoiceService.%d.CallControl.Line.%d.Stats.", uVsIndex, pDmlCallCtrlLine->uInstanceNumber);
        TelcoVoiceHal_GetLineStats(HalName, &stVoiceStats);

        TELCOVOICEMGR_LOCK_OR_EXIT()

        TelcoVoiceMgrDml_MapLineStats(pDmlCallCtrlLine, &stVoiceStats);
    }

    if (strcmp(ParamName, "Underruns") == 0)
    {
        *puLong = pHEAD->Underruns;
        ret = TRUE;
    }
    else if (strcmp(ParamName, "Overruns") == 0)
    {
        *puLong = pHEAD->Overruns;
        ret = TRUE;
    }
    else
    {
        CcspTraceWarning(("%s: Unsupported parameter '%s'\n", __func__,ParamName));
    }

    TELCOVOICEMGR_UNLOCK()

    return ret;
}

/**********************************************************************

    caller:     owner of this object

    prototype:

        BOOL TelcoVoiceMgrDml_CallControl_ExtensionList_IsUpdated(ANSC_HANDLE hInsContext);

    description:

        This function is checking whether the table is updated or not.

    argument:   ANSC_HANDLE                 hInsContext,
                The instance handle;

    return:     TRUE or FALSE.

**********************************************************************/

BOOL TelcoVoiceMgrDml_CallControl_ExtensionList_IsUpdated(ANSC_HANDLE hInsContext)
{
    return TRUE;
}

/**********************************************************************

    caller:     owner of this object

    prototype:

        ULONG TelcoVoiceMgrDml_CallControl_ExtensionList_Synchronize(ANSC_HANDLE hInsContext);

    description:

        This function is called to synchronize the table.

    argument:   ANSC_HANDLE                 hInsContext,
                The instance handle;

    return:     The status of the operation.

**********************************************************************/

ULONG TelcoVoiceMgrDml_CallControl_ExtensionList_Synchronize(ANSC_HANDLE hInsContext)
{
    return 0;
}

/**********************************************************************

    caller:     owner of this object

    prototype:

        ULONG TelcoVoiceMgrDml_CallControl_ExtensionList_GetEntryCount(ANSC_HANDLE hInsContext);

    description:

        This function is called to retrieve the count of the table.

    argument:   ANSC_HANDLE                 hInsContext,
                The instance handle;

    return:     The count of the table

**********************************************************************/
ULONG TelcoVoiceMgrDml_CallControl_ExtensionList_GetEntryCount(ANSC_HANDLE hInsContext)
{
    ULONG ret = 0;

    TELCOVOICEMGR_LOCK_OR_EXIT()

    DML_VOICE_SERVICE_CTRL_T* pVoiceService = (DML_VOICE_SERVICE_CTRL_T*) hInsContext;

    PTELCOVOICEMGR_DML_VOICESERVICE pDmlVoiceService = &(pVoiceService->dml);

    PDML_CALLCONTROL_EXTENSION_LIST_T pCallCtrlExtList = &(pDmlVoiceService->CallControl_obj.Extension);

    if(pCallCtrlExtList != NULL)
    {
        ret = pCallCtrlExtList->ulQuantity;
    }

    TELCOVOICEMGR_UNLOCK()

    return ret;
}

/**********************************************************************

    caller:     owner of this object

    prototype:

        ANSC_HANDLE TelcoVoiceMgrDml_CallControl_ExtensionList_GetEntry(ANSC_HANDLE hInsContext, ULONG nIndex, ULONG* pInsNumber);

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
ANSC_HANDLE TelcoVoiceMgrDml_CallControl_ExtensionList_GetEntry(ANSC_HANDLE hInsContext, ULONG nIndex, ULONG* pInsNumber)
{

    ANSC_HANDLE ret = NULL;

    TELCOVOICEMGR_LOCK_OR_EXIT()

    PDML_VOICE_SERVICE_CTRL_T pVoiceService = (PDML_VOICE_SERVICE_CTRL_T) hInsContext;

    PTELCOVOICEMGR_DML_VOICESERVICE pDmlVoiceService = &(pVoiceService->dml);

    PDML_CALLCONTROL_EXTENSION_LIST_T pExtensionList = &(pDmlVoiceService->CallControl_obj.Extension);

    if(pExtensionList != NULL)
    {
        if(nIndex < pExtensionList->ulQuantity)
        {
            PDML_CALLCONTROL_EXTENSION_CTRL_T pExtensionCtrl = pExtensionList->pdata[nIndex];
            if(pExtensionCtrl != NULL)
            {
               *pInsNumber = nIndex + 1;
               ret = (ANSC_HANDLE) pExtensionCtrl;
            }
        }
    }

    TELCOVOICEMGR_UNLOCK()

    return ret;
}

/**********************************************************************

    caller:     owner of this object

    prototype:

        BOOL TelcoVoiceMgrDml_CallControl_ExtensionList_GetParamUlongValue(ANSC_HANDLE hInsContext, char* ParamName, ULONG* puLong);

    description:

        This function is called to retrieve ULONG parameter value;

    argument:   ANSC_HANDLE                 hInsContext,
                The instance handle;

                char*                       ParamName,
                The parameter name;

                ULONG*                      puLong
                The buffer of returned ULONG value;

    return:     TRUE if succeeded.

**********************************************************************/

BOOL TelcoVoiceMgrDml_CallControl_ExtensionList_GetParamUlongValue(ANSC_HANDLE hInsContext, char* ParamName, ULONG* puLong)
{
    BOOL ret = FALSE;
    ULONG uVsIndex  = 0;
    ULONG uCCExtIndex = 0;
    PTELCOVOICEMGR_DML_VOICESERVICE pDmlVoiceService = NULL;

    if(ParamName == NULL || puLong == NULL)
    {
        CcspTraceWarning(("%s: Invalid Input Parameter [NULL]\n", __func__));
        return ret;
    }

    TELCOVOICEMGR_LOCK_OR_EXIT()

    PDML_CALLCONTROL_EXTENSION_CTRL_T pCallCtrlExtCtrl = (PDML_CALLCONTROL_EXTENSION_CTRL_T)hInsContext;

    PDML_CALLCONTROL_EXTENSION pHEAD = &(pCallCtrlExtCtrl->dml);

    if(pHEAD != NULL)
    {
        pDmlVoiceService = (PTELCOVOICEMGR_DML_VOICESERVICE)pHEAD->pParentVoiceService;
    }

    if (pHEAD == NULL  || pDmlVoiceService == NULL)
    {
        TELCOVOICEMGR_UNLOCK()

        CcspTraceError(("%s:%d:: pHEAD or pDmlVoiceService NULL\n", __FUNCTION__, __LINE__));

        return ret;
    }

    uVsIndex = pDmlVoiceService->InstanceNumber;

    uCCExtIndex = pHEAD->uInstanceNumber;

    if (strcmp(ParamName, "Status") == 0)
    {
        //Fetch status from voice stack
        hal_param_t req_param;
        memset(&req_param, 0, sizeof(req_param));
        snprintf(req_param.name, sizeof(req_param.name), DML_VOICESERVICE_CALLCONTROL_EXTENSION_PARAM_NAME"%s", uVsIndex, uCCExtIndex, "Status");
        if (ANSC_STATUS_SUCCESS == TelcoVoiceHal_GetSingleParameter(&req_param))
        {
            *puLong = strtoul(req_param.value,NULL,10);
            ret = TRUE;
        }
        else
        {
            CcspTraceError(("%s:%d:: Status:get failed \n", __FUNCTION__, __LINE__));
            *puLong = CALLCTRL_CALLSTATUS_DISABLED;
            ret = FALSE;
        }
    }
    else if (strcmp(ParamName, "Origin") == 0)
    {
        *puLong = pHEAD->Origin;
        ret = TRUE;
    }
    else if (strcmp(ParamName, "ConferenceCallingStatus") == 0)
    {
        //Fetch status from voice stack
        hal_param_t req_param;
        memset(&req_param, 0, sizeof(req_param));
        snprintf(req_param.name, sizeof(req_param.name), DML_VOICESERVICE_CALLCONTROL_EXTENSION_PARAM_NAME"%s", uVsIndex, 
                  uCCExtIndex, "ConferenceCallingStatus");
        if (ANSC_STATUS_SUCCESS == TelcoVoiceHal_GetSingleParameter(&req_param))
        {
            *puLong = strtoul(req_param.value,NULL,10);
            ret = TRUE;
        }
        else
        {
            CcspTraceError(("%s:%d:: Status:get failed \n", __FUNCTION__, __LINE__));
            ret = FALSE;
        }
    }
    else if (strcmp(ParamName, "ConferenceCallingSessionCount") == 0)
    {
        *puLong = pHEAD->ConferenceCallingSessionCount;
        ret = TRUE;
    }
    else if (strcmp(ParamName, "X_RDK_FacilityActionResult") == 0)
    {
        *puLong = pHEAD->X_RDK_FacilityActionResult;
        ret = TRUE;
    }
    else if (strcmp(ParamName, "CallWaitingStatus") == 0)
    {
        //Fetch status from voice stack
        hal_param_t req_param;
        memset(&req_param, 0, sizeof(req_param));
        snprintf(req_param.name, sizeof(req_param.name), DML_VOICESERVICE_CALLCONTROL_EXTENSION_PARAM_NAME"%s", uVsIndex, uCCExtIndex, "CallWaitingStatus");
        if (ANSC_STATUS_SUCCESS == TelcoVoiceHal_GetSingleParameter(&req_param))
        {
            *puLong = strtoul(req_param.value,NULL,10);
            ret = TRUE;
        }
        else
        {
            CcspTraceError(("%s:%d:: Status:get failed \n", __FUNCTION__, __LINE__));
            ret = FALSE;
        }
    }
    else if (strcmp(ParamName, "CallStatus") == 0)
    {
        //Fetch status from voice stack
        hal_param_t req_param;
        memset(&req_param, 0, sizeof(req_param));
        snprintf(req_param.name, sizeof(req_param.name), DML_VOICESERVICE_CALLCONTROL_EXTENSION_PARAM_NAME"%s", uVsIndex, uCCExtIndex, "CallStatus");
        if (ANSC_STATUS_SUCCESS == TelcoVoiceHal_GetSingleParameter(&req_param))
        {
            *puLong = strtoul(req_param.value,NULL,10);
            ret = TRUE;
        }
        else
        {
            CcspTraceError(("%s:%d:: Status:get failed \n", __FUNCTION__, __LINE__));
            ret = FALSE;
        }
    }
    else
    {
        CcspTraceWarning(("%s: Unsupported parameter '%s'\n", __func__,ParamName));
    }


    TELCOVOICEMGR_UNLOCK()

    return ret;
}

/**********************************************************************

    caller:     owner of this object

    prototype:

        ULONG TelcoVoiceMgrDml_CallControl_ExtensionList_GetParamStringValue(ANSC_HANDLE hInsContext, char* ParamName, char* pValue, ULONG* pulSize);

    description:

        This function is called to retrieve string parameter value;

    argument:   ANSC_HANDLE                 hInsContext,
                The instance handle;

                char*                       ParamName,
                The parameter name;

                char*                       pValue,
                The string value buffer;

                ULONG*                      pUlSize
                The buffer of length of string value;
                Usually size of 1023 will be used.
                If it's not big enough, put required size here and return 1;

    return:     0 if succeeded;
                1 if short of buffer size; (*pUlSize = required size)
                -1 if not supported.

**********************************************************************/

ULONG TelcoVoiceMgrDml_CallControl_ExtensionList_GetParamStringValue(ANSC_HANDLE hInsContext, char* ParamName, char* pValue, ULONG* pulSize)
{
    ULONG ret = 1;

    if(ParamName == NULL || pValue == NULL || pulSize == NULL)
    {
        CcspTraceWarning(("%s: Invalid Input Parameter [NULL]\n", __func__));
        return ret;
    }

    TELCOVOICEMGR_LOCK_OR_EXIT()

    PDML_CALLCONTROL_EXTENSION_CTRL_T pCallCtrlExtCtrl = (PDML_CALLCONTROL_EXTENSION_CTRL_T)hInsContext;

    PDML_CALLCONTROL_EXTENSION pHEAD = &(pCallCtrlExtCtrl->dml);

    if (strcmp(ParamName, "VoiceMail") == 0)
    {
        AnscCopyString(pValue,pHEAD->VoiceMail);
        ret = 0;
    }
    else if (strcmp(ParamName, "Provider") == 0)
    {
        AnscCopyString(pValue,pHEAD->Provider);
        ret = 0;
    }
    else if (strcmp(ParamName, "NumberingPlan") == 0)
    {
        AnscCopyString(pValue,pHEAD->NumberingPlan);
        ret = 0;
    }
    else if (strcmp(ParamName, "X_RDK_FacilityAction") == 0)
    {
          AnscCopyString(pValue, pHEAD->X_RDK_FacilityAction);
          ret = 0;
    }
    else if (strcmp(ParamName, "X_RDK_FacilityActionArgument") == 0)
    {
          AnscCopyString(pValue, pHEAD->X_RDK_FacilityActionArgument);
          ret = 0;
    }
    else if (strcmp(ParamName, "Name") == 0)
    {
        AnscCopyString(pValue,pHEAD->Name);
        ret = 0;
    }
    else if (strcmp(ParamName, "ExtensionNumber") == 0)
    {
        AnscCopyString(pValue,pHEAD->ExtensionNumber);
        ret = 0;
    }
    else if (strcmp(ParamName, "CallingFeatures") == 0)
    {
        AnscCopyString(pValue,pHEAD->CallingFeatures);
        ret = 0;
    }
    else if (strcmp(ParamName, "Alias") == 0)
    {
        AnscCopyString(pValue,pHEAD->Alias);
        ret = 0;
    }
    else
    {
        CcspTraceWarning(("%s: Unsupported parameter '%s'\n", __func__,ParamName));
    }

    TELCOVOICEMGR_UNLOCK()

    return ret;
}

/**********************************************************************

    caller:     owner of this object

    prototype:

        BOOL TelcoVoiceMgrDml_CallControl_ExtensionList_SetParamStringValue(ANSC_HANDLE hInsContext, char* ParamName, char* pString);

    description:

        This function is called to set string parameter value;

    argument:   ANSC_HANDLE                 hInsContext,
                The instance handle;

                char*                       ParamName,
                The parameter name;

                char*                       pString
                The updated string value;

    return:     TRUE if succeeded.

**********************************************************************/

BOOL TelcoVoiceMgrDml_CallControl_ExtensionList_SetParamStringValue(ANSC_HANDLE hInsContext, char* ParamName, char* pString)
{
    BOOL ret = FALSE;
    ULONG uVsIndex  = 0;
    ULONG uExtensionIndex = 0;
    char HalName[MAX_STR_LEN] = {0};

    PTELCOVOICEMGR_DML_VOICESERVICE pDmlVoiceService = NULL;

    if(ParamName == NULL)
    {
        CcspTraceWarning(("%s: Invalid Input Parameter [NULL]\n", __func__));
        return ret;
    }

    TELCOVOICEMGR_LOCK_OR_EXIT()

    PDML_CALLCONTROL_EXTENSION_CTRL_T pCallCtrlExtCtrl = (PDML_CALLCONTROL_EXTENSION_CTRL_T)hInsContext;

    PDML_CALLCONTROL_EXTENSION pHEAD = &(pCallCtrlExtCtrl->dml);

    if(pHEAD != NULL)
    {
        pDmlVoiceService = (PTELCOVOICEMGR_DML_VOICESERVICE)pHEAD->pParentVoiceService;
    }

    if (pHEAD == NULL  || pDmlVoiceService == NULL)
    {
        TELCOVOICEMGR_UNLOCK()

        CcspTraceError(("%s:%d:: pHEAD or pDmlVoiceService NULL\n", __FUNCTION__, __LINE__));

        return ret;
    }

    uVsIndex = pDmlVoiceService->InstanceNumber;

    uExtensionIndex = pHEAD->uInstanceNumber;

    TELCOVOICEMGR_UNLOCK()

    if (strcmp(ParamName, "VoiceMail") == 0)
    {
        snprintf(HalName, MAX_STR_LEN, "Device.Services.VoiceService.%d.CallControl.Extension.%d.VoiceMail",uVsIndex,uExtensionIndex);

        if (TelcoVoiceMgrHal_SetParamString(HalName,pString) == ANSC_STATUS_SUCCESS)
        {
            TELCOVOICEMGR_LOCK_OR_EXIT()

            AnscCopyString(pHEAD->VoiceMail,pString);

            TELCOVOICEMGR_UNLOCK()

            ret = TRUE;
        }
    }
    else if (strcmp(ParamName, "Provider") == 0)
    {
        snprintf(HalName, MAX_STR_LEN, "Device.Services.VoiceService.%d.CallControl.Extension.%d.Provider",uVsIndex,uExtensionIndex);

        if (TelcoVoiceMgrHal_SetParamString(HalName,pString) == ANSC_STATUS_SUCCESS)
        {
            TELCOVOICEMGR_LOCK_OR_EXIT()

            AnscCopyString(pHEAD->Provider,pString);

            TELCOVOICEMGR_UNLOCK()

            ret = TRUE;
        }
    }
    else if (strcmp(ParamName, "NumberingPlan") == 0)
    {
        snprintf(HalName, MAX_STR_LEN, "Device.Services.VoiceService.%d.CallControl.Extension.%d.NumberingPlan",uVsIndex,uExtensionIndex);

        if (TelcoVoiceMgrHal_SetParamString(HalName,pString) == ANSC_STATUS_SUCCESS)
        {
            TELCOVOICEMGR_LOCK_OR_EXIT()

            AnscCopyString(pHEAD->NumberingPlan,pString);

            TELCOVOICEMGR_UNLOCK()

            ret = TRUE;
        }
    }
    else if (strcmp(ParamName, "X_RDK_FacilityAction") == 0)
    {
        snprintf(HalName, MAX_STR_LEN, "Device.Services.VoiceService.%d.CallControl.Extension.%d.X_RDK_FacilityAction",
                                       uVsIndex, uExtensionIndex);

        if (TelcoVoiceMgrHal_SetParamString(HalName, pString) == ANSC_STATUS_SUCCESS)
        {
            TELCOVOICEMGR_LOCK_OR_EXIT()

            AnscCopyString(pHEAD->X_RDK_FacilityAction, pString);

            TELCOVOICEMGR_UNLOCK()

            ret = TRUE;
        }
    }
    else if (strcmp(ParamName, "X_RDK_FacilityActionArgument") == 0)
    {
        snprintf(HalName, MAX_STR_LEN, "Device.Services.VoiceService.%d.CallControl.Extension.%d.X_RDK_FacilityActionArgument",
                                       uVsIndex, uExtensionIndex);

        if (TelcoVoiceMgrHal_SetParamString(HalName, pString) == ANSC_STATUS_SUCCESS)
        {
            TELCOVOICEMGR_LOCK_OR_EXIT()

            AnscCopyString(pHEAD->X_RDK_FacilityActionArgument, pString);

            TELCOVOICEMGR_UNLOCK()

            ret = TRUE;
       }
    }
    else if (strcmp(ParamName, "Name") == 0)
    {
        snprintf(HalName, MAX_STR_LEN, "Device.Services.VoiceService.%d.CallControl.Extension.%d.Name",uVsIndex,uExtensionIndex);

        if (TelcoVoiceMgrHal_SetParamString(HalName,pString) == ANSC_STATUS_SUCCESS)
        {
            TELCOVOICEMGR_LOCK_OR_EXIT()

            AnscCopyString(pHEAD->Name,pString);

            TELCOVOICEMGR_UNLOCK()

            ret = TRUE;
        }
    }
    else if (strcmp(ParamName, "ExtensionNumber") == 0)
    {
        snprintf(HalName, MAX_STR_LEN, "Device.Services.VoiceService.%d.CallControl.Extension.%d.ExtensionNumber",uVsIndex,uExtensionIndex);

        if (TelcoVoiceMgrHal_SetParamString(HalName,pString) == ANSC_STATUS_SUCCESS)
        {
            TELCOVOICEMGR_LOCK_OR_EXIT()

            AnscCopyString(pHEAD->ExtensionNumber,pString);

            TELCOVOICEMGR_UNLOCK()

            ret = TRUE;
        }
    }
    else if (strcmp(ParamName, "CallingFeatures") == 0)
    {
        snprintf(HalName, MAX_STR_LEN, "Device.Services.VoiceService.%d.CallControl.Extension.%d.CallingFeatures",uVsIndex,uExtensionIndex);

        if (TelcoVoiceMgrHal_SetParamString(HalName,pString) == ANSC_STATUS_SUCCESS)
        {
            TELCOVOICEMGR_LOCK_OR_EXIT()

            AnscCopyString(pHEAD->CallingFeatures,pString);

            TELCOVOICEMGR_UNLOCK()

            ret = TRUE;
        }
    }
    else if (strcmp(ParamName, "Alias") == 0)
    {
        TELCOVOICEMGR_LOCK_OR_EXIT()

        AnscCopyString(pHEAD->Alias,pString);

        TELCOVOICEMGR_UNLOCK()

        ret = TRUE;
    }
    else
    {
        CcspTraceWarning(("%s: Unsupported parameter '%s'\n", __func__,ParamName));
    }

    return ret;

}

/**********************************************************************

    caller:     owner of this object

    prototype:

        BOOL TelcoVoiceMgrDml_CallControl_ExtensionList_GetParamBoolValue(ANSC_HANDLE hInsContext, char* ParamName, BOOL* pBool);

    description:

        This function is called to retrieve Boolean parameter value;

    argument:   ANSC_HANDLE                 hInsContext,
                The instance handle;

                char*                       ParamName,
                The parameter name;

                BOOL*                       pBool
                The buffer of returned boolean value;

    return:     TRUE if succeeded.

**********************************************************************/

BOOL TelcoVoiceMgrDml_CallControl_ExtensionList_GetParamBoolValue(ANSC_HANDLE hInsContext, char* ParamName, BOOL* pBool)
{
    BOOL ret = FALSE;

    if(ParamName == NULL || pBool == NULL)
    {
        CcspTraceWarning(("%s: Invalid Input Parameter [NULL]\n", __func__));
        return ret;
    }

    TELCOVOICEMGR_LOCK_OR_EXIT()

    PDML_CALLCONTROL_EXTENSION_CTRL_T pCallCtrlExtCtrl = (PDML_CALLCONTROL_EXTENSION_CTRL_T)hInsContext;

    PDML_CALLCONTROL_EXTENSION pHEAD = &(pCallCtrlExtCtrl->dml);

    if (strcmp(ParamName, "QuiescentMode") == 0)
    {
        *pBool = pHEAD->QuiescentMode;
        ret = TRUE;
    }
    else if (strcmp(ParamName, "Enable") == 0)
    {
        *pBool = pHEAD->Enable;
        ret = TRUE;
    }
    else
    {
        CcspTraceWarning(("%s: Unsupported parameter '%s'\n", __func__,ParamName));
    }

    TELCOVOICEMGR_UNLOCK()

    return ret;
}

/**********************************************************************

    caller:     owner of this object

    prototype:

        BOOL TelcoVoiceMgrDml_CallControl_ExtensionList_SetParamBoolValue(ANSC_HANDLE hInsContext, char* ParamName, BOOL bValue);

    description:

        This function is called to set BOOL parameter value;

    argument:   ANSC_HANDLE                 hInsContext,
                The instance handle;

                char*                       ParamName,
                The parameter name;

                BOOL                        bValue
                The updated BOOL value;

    return:     TRUE if succeeded.

**********************************************************************/

BOOL TelcoVoiceMgrDml_CallControl_ExtensionList_SetParamBoolValue(ANSC_HANDLE hInsContext, char* ParamName, BOOL bValue)
{
    BOOL ret = FALSE;
    ULONG uVsIndex  = 0;
    ULONG uExtensionIndex = 0;
    char HalName[MAX_STR_LEN] = {0};

    PTELCOVOICEMGR_DML_VOICESERVICE pDmlVoiceService = NULL;

    if(ParamName == NULL)
    {
        CcspTraceWarning(("%s: Invalid Input Parameter [NULL]\n", __func__));
        return ret;
    }

    TELCOVOICEMGR_LOCK_OR_EXIT()

    PDML_CALLCONTROL_EXTENSION_CTRL_T pCallCtrlExtCtrl = (PDML_CALLCONTROL_EXTENSION_CTRL_T)hInsContext;

    PDML_CALLCONTROL_EXTENSION pHEAD = &(pCallCtrlExtCtrl->dml);

    if(pHEAD != NULL)
    {
        pDmlVoiceService = (PTELCOVOICEMGR_DML_VOICESERVICE)pHEAD->pParentVoiceService;
    }

    if (pHEAD == NULL  || pDmlVoiceService == NULL)
    {
        TELCOVOICEMGR_UNLOCK()

        CcspTraceError(("%s:%d:: pHEAD or pDmlVoiceService NULL\n", __FUNCTION__, __LINE__));

        return ret;
    }

    uVsIndex = pDmlVoiceService->InstanceNumber;

    uExtensionIndex = pHEAD->uInstanceNumber;

    TELCOVOICEMGR_UNLOCK()

    if (strcmp(ParamName, "QuiescentMode") == 0)
    {
        snprintf(HalName, MAX_STR_LEN, "Device.Services.VoiceService.%d.CallControl.Extension.%d.QuiescentMode",uVsIndex,uExtensionIndex);

        if (TelcoVoiceMgrHal_SetParamBool(HalName,bValue) == ANSC_STATUS_SUCCESS)
        {
            TELCOVOICEMGR_LOCK_OR_EXIT()

            pHEAD->QuiescentMode = bValue;

            TELCOVOICEMGR_UNLOCK()

            ret = TRUE;
        }
    }
    else if (strcmp(ParamName, "Enable") == 0)
    {
        snprintf(HalName, MAX_STR_LEN, "Device.Services.VoiceService.%d.CallControl.Extension.%d.Enable",uVsIndex,uExtensionIndex);

        if (TelcoVoiceMgrHal_SetParamBool(HalName,bValue) == ANSC_STATUS_SUCCESS)
        {
            TELCOVOICEMGR_LOCK_OR_EXIT()

            pHEAD->Enable = bValue;

            TELCOVOICEMGR_UNLOCK()

            ret = TRUE;
        }
    }
    else
    {
        CcspTraceWarning(("%s: Unsupported parameter '%s'\n", __func__,ParamName));
    }

    return ret;
}

/**********************************************************************

    caller:     owner of this object

    prototype:

        BOOL TelcoVoiceMgrDml_CallControl_ExtensionList_Validate(ANSC_HANDLE hInsContext);

    description:

        This function is called to validate the update.

    argument:   ANSC_HANDLE                 hInsContext,
                The instance handle;

    return:     TRUE if there's no issue.

**********************************************************************/

BOOL TelcoVoiceMgrDml_CallControl_ExtensionList_Validate(ANSC_HANDLE hInsContext)
{
    return TRUE;
}

/**********************************************************************

    caller:     owner of this object

    prototype:

        BOOL TelcoVoiceMgrDml_CallControl_ExtensionList_Commit(ANSC_HANDLE hInsContext);

    description:

        This function is called to commit the update.

    argument:   ANSC_HANDLE                 hInsContext,
                The instance handle;

    return:     0 if there's no issue.

**********************************************************************/

BOOL TelcoVoiceMgrDml_CallControl_ExtensionList_Commit(ANSC_HANDLE hInsContext)
{
    return 0;
}

/**********************************************************************

    caller:     owner of this object

    prototype:

        BOOL TelcoVoiceMgrDml_CallControl_ExtensionList_Rollback(ANSC_HANDLE hInsContext);

    description:

        This function is called to rollback the update.

    argument:   ANSC_HANDLE                 hInsContext,
                The instance handle;

    return:     0 if there's no issue.

**********************************************************************/

BOOL TelcoVoiceMgrDml_CallControl_ExtensionList_Rollback(ANSC_HANDLE hInsContext)
{
    return 0;
}

/**********************************************************************

    caller:     owner of this object

    prototype:

        BOOL TelcoVoiceMgrDml_CallControl_ExtensionList_Stats_InCalls_GetParamUlongValue(ANSC_HANDLE hInsContext, char* ParamName, ULONG* puLong);

    description:

        This function is called to retrieve ULONG parameter value;

    argument:   ANSC_HANDLE                 hInsContext,
                The instance handle;

                char*                       ParamName,
                The parameter name;

                ULONG*                      puLong
                The buffer of returned ULONG value;

    return:     TRUE if succeeded.

**********************************************************************/

BOOL TelcoVoiceMgrDml_CallControl_ExtensionList_Stats_InCalls_GetParamUlongValue(ANSC_HANDLE hInsContext, char* ParamName, ULONG* puLong)
{
    BOOL ret = FALSE;

    if(ParamName == NULL || puLong == NULL)
    {
        CcspTraceWarning(("%s: Invalid Input Parameter [NULL]\n", __func__));
        return ret;
    }

    TELCOVOICEMGR_LOCK_OR_EXIT()

    PDML_CALLCONTROL_EXTENSION_CTRL_T pCallCtrlExtCtrl = (PDML_CALLCONTROL_EXTENSION_CTRL_T)hInsContext;

    PDML_CALLCONTROL_EXTENSION pDmlCallCtrlExt = &(pCallCtrlExtCtrl->dml);

    PDML_CALLCONTROL_STATS_INCALLS pHEAD = &(pDmlCallCtrlExt->Stats.IncomingCalls);

    if (strcmp(ParamName, "TotalCallTime") == 0)
    {
        *puLong = pHEAD->TotalCallTime;
        ret = TRUE;
    }
    else if (strcmp(ParamName, "CallsReceived") == 0)
    {
        *puLong = pHEAD->CallsReceived;
        ret = TRUE;
    }
    else if (strcmp(ParamName, "CallsFailed") == 0)
    {
        *puLong = pHEAD->CallsFailed;
        ret = TRUE;
    }
    else if (strcmp(ParamName, "CallsDropped") == 0)
    {
        *puLong = pHEAD->CallsDropped;
        ret = TRUE;
    }
    else if (strcmp(ParamName, "CallsConnected") == 0)
    {
        *puLong = pHEAD->CallsConnected;
        ret = TRUE;
    }
    else
    {
        CcspTraceWarning(("%s: Unsupported parameter '%s'\n", __func__,ParamName));
    }


    TELCOVOICEMGR_UNLOCK()

    return ret;
}

/**********************************************************************

    caller:     owner of this object

    prototype:

        BOOL TelcoVoiceMgrDml_CallControl_ExtensionList_Stats_OutCalls_GetParamUlongValue(ANSC_HANDLE hInsContext, char* ParamName, ULONG* puLong);

    description:

        This function is called to retrieve ULONG parameter value;

    argument:   ANSC_HANDLE                 hInsContext,
                The instance handle;

                char*                       ParamName,
                The parameter name;

                ULONG*                      puLong
                The buffer of returned ULONG value;

    return:     TRUE if succeeded.

**********************************************************************/

BOOL TelcoVoiceMgrDml_CallControl_ExtensionList_Stats_OutCalls_GetParamUlongValue(ANSC_HANDLE hInsContext, char* ParamName, ULONG* puLong)
{
    BOOL ret = FALSE;

    if(ParamName == NULL || puLong == NULL)
    {
        CcspTraceWarning(("%s: Invalid Input Parameter [NULL]\n", __func__));
        return ret;
    }

    TELCOVOICEMGR_LOCK_OR_EXIT()

    PDML_CALLCONTROL_EXTENSION_CTRL_T pCallCtrlExtCtrl = (PDML_CALLCONTROL_EXTENSION_CTRL_T)hInsContext;

    PDML_CALLCONTROL_EXTENSION pDmlCallCtrlExt = &(pCallCtrlExtCtrl->dml);

    PDML_CALLCONTROL_STATS_OUTCALLS pHEAD = &(pDmlCallCtrlExt->Stats.OutgoingCalls);

    if (strcmp(ParamName, "TotalCallTime") == 0)
    {
        *puLong = pHEAD->TotalCallTime;
        ret = TRUE;
    }
    else if (strcmp(ParamName, "CallsFailed") == 0)
    {
        *puLong = pHEAD->CallsFailed;
        ret = TRUE;
    }
    else if (strcmp(ParamName, "CallsDropped") == 0)
    {
        *puLong = pHEAD->CallsDropped;
        ret = TRUE;
    }
    else if (strcmp(ParamName, "CallsConnected") == 0)
    {
        *puLong = pHEAD->CallsConnected;
        ret = TRUE;
    }
    else if (strcmp(ParamName, "CallsAttempted") == 0)
    {
        *puLong = pHEAD->CallsAttempted;
        ret = TRUE;
    }
    else
    {
        CcspTraceWarning(("%s: Unsupported parameter '%s'\n", __func__,ParamName));
    }

    TELCOVOICEMGR_UNLOCK()

    return ret;
}

/**********************************************************************

    caller:     owner of this object

    prototype:

        BOOL TelcoVoiceMgrDml_CallControl_ExtensionList_Stats_RTP_GetParamUlongValue(ANSC_HANDLE hInsContext, char* ParamName, ULONG* puLong);

    description:

        This function is called to retrieve ULONG parameter value;

    argument:   ANSC_HANDLE                 hInsContext,
                The instance handle;

                char*                       ParamName,
                The parameter name;

                ULONG*                      puLong
                The buffer of returned ULONG value;

    return:     TRUE if succeeded.

**********************************************************************/

BOOL TelcoVoiceMgrDml_CallControl_ExtensionList_Stats_RTP_GetParamUlongValue(ANSC_HANDLE hInsContext, char* ParamName, ULONG* puLong)
{
    BOOL ret = FALSE;

    if(ParamName == NULL || puLong == NULL)
    {
        CcspTraceWarning(("%s: Invalid Input Parameter [NULL]\n", __func__));
        return ret;
    }

    TELCOVOICEMGR_LOCK_OR_EXIT()

    PDML_CALLCONTROL_EXTENSION_CTRL_T pCallCtrlExtCtrl = (PDML_CALLCONTROL_EXTENSION_CTRL_T)hInsContext;

    PDML_CALLCONTROL_EXTENSION pDmlCallCtrlExt = &(pCallCtrlExtCtrl->dml);

    PDML_CALLCONTROL_STATS_RTP pHEAD = &(pDmlCallCtrlExt->Stats.RTP);

    if (strcmp(ParamName, "PacketsSent") == 0)
    {
        *puLong = pHEAD->PacketsSent;
        ret = TRUE;
    }
    else if (strcmp(ParamName, "PacketsReceived") == 0)
    {
        *puLong = pHEAD->PacketsReceived;
        ret = TRUE;
    }
    else if (strcmp(ParamName, "PacketsLost") == 0)
    {
        *puLong = pHEAD->PacketsLost;
        ret = TRUE;
    }
    else if (strcmp(ParamName, "BytesSent") == 0)
    {
        *puLong = pHEAD->BytesSent;
        ret = TRUE;
    }
    else if (strcmp(ParamName, "BytesReceived") == 0)
    {
        *puLong = pHEAD->BytesReceived;
        ret = TRUE;
    }
    else
    {
        CcspTraceWarning(("%s: Unsupported parameter '%s'\n", __func__,ParamName));
    }



    TELCOVOICEMGR_UNLOCK()

    return ret;
}

/**********************************************************************

    caller:     owner of this object

    prototype:

        BOOL TelcoVoiceMgrDml_CallControl_ExtensionList_Stats_DSP_GetParamUlongValue(ANSC_HANDLE hInsContext, char* ParamName, ULONG* puLong);

    description:

        This function is called to retrieve ULONG parameter value;

    argument:   ANSC_HANDLE                 hInsContext,
                The instance handle;

                char*                       ParamName,
                The parameter name;

                ULONG*                      puLong
                The buffer of returned ULONG value;

    return:     TRUE if succeeded.

**********************************************************************/

BOOL TelcoVoiceMgrDml_CallControl_ExtensionList_Stats_DSP_GetParamUlongValue(ANSC_HANDLE hInsContext, char* ParamName, ULONG* puLong)
{
    BOOL ret = FALSE;

    if(ParamName == NULL || puLong == NULL)
    {
        CcspTraceWarning(("%s: Invalid Input Parameter [NULL]\n", __func__));
        return ret;
    }

    TELCOVOICEMGR_LOCK_OR_EXIT()

    PDML_CALLCONTROL_EXTENSION_CTRL_T pCallCtrlExtCtrl = (PDML_CALLCONTROL_EXTENSION_CTRL_T)hInsContext;

    PDML_CALLCONTROL_EXTENSION pDmlCallCtrlExt = &(pCallCtrlExtCtrl->dml);

    PDML_CALLCONTROL_STATS_DSP pHEAD = &(pDmlCallCtrlExt->Stats.DSP);

    if (strcmp(ParamName, "Underruns") == 0)
    {
        *puLong = pHEAD->Underruns;
        ret = TRUE;
    }
    else if (strcmp(ParamName, "Overruns") == 0)
    {
        *puLong = pHEAD->Overruns;
        ret = TRUE;
    }
    else
    {
        CcspTraceWarning(("%s: Unsupported parameter '%s'\n", __func__,ParamName));
    }

    TELCOVOICEMGR_UNLOCK()

    return ret;
}

/**********************************************************************

    caller:     owner of this object

    prototype:

        BOOL TelcoVoiceMgrDml_CallControl_GroupList_IsUpdated(ANSC_HANDLE hInsContext);

    description:

        This function is checking whether the table is updated or not.

    argument:   ANSC_HANDLE                 hInsContext,
                The instance handle;

    return:     TRUE or FALSE.

**********************************************************************/

BOOL TelcoVoiceMgrDml_CallControl_GroupList_IsUpdated(ANSC_HANDLE hInsContext)
{
    return TRUE;
}

/**********************************************************************

    caller:     owner of this object

    prototype:

        ULONG TelcoVoiceMgrDml_CallControl_GroupList_Synchronize(ANSC_HANDLE hInsContext);

    description:

        This function is called to synchronize the table.

    argument:   ANSC_HANDLE                 hInsContext,
                The instance handle;

    return:     The status of the operation.

**********************************************************************/

ULONG TelcoVoiceMgrDml_CallControl_GroupList_Synchronize(ANSC_HANDLE hInsContext)
{
    return 0;
}

/**********************************************************************

    caller:     owner of this object

    prototype:

        ULONG TelcoVoiceMgrDml_CallControl_GroupList_GetEntryCount(ANSC_HANDLE hInsContext);

    description:

        This function is called to retrieve the count of the table.

    argument:   ANSC_HANDLE                 hInsContext,
                The instance handle;

    return:     The count of the table

**********************************************************************/
ULONG TelcoVoiceMgrDml_CallControl_GroupList_GetEntryCount(ANSC_HANDLE hInsContext)
{
    ULONG ret = 0;

    TELCOVOICEMGR_LOCK_OR_EXIT()

    DML_VOICE_SERVICE_CTRL_T* pVoiceService = (DML_VOICE_SERVICE_CTRL_T*) hInsContext;

    PTELCOVOICEMGR_DML_VOICESERVICE pDmlVoiceService = &(pVoiceService->dml);

    PDML_CALLCONTROL_GROUP_LIST_T pCallCtrlGrpList = &(pDmlVoiceService->CallControl_obj.Group);

    if(pCallCtrlGrpList != NULL)
    {
        ret = pCallCtrlGrpList->ulQuantity;
    }

    TELCOVOICEMGR_UNLOCK()

    return ret;
}

/**********************************************************************

    caller:     owner of this object

    prototype:

        ANSC_HANDLE TelcoVoiceMgrDml_CallControl_GroupList_GetEntry(ANSC_HANDLE hInsContext, ULONG nIndex, ULONG* pInsNumber);

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
ANSC_HANDLE TelcoVoiceMgrDml_CallControl_GroupList_GetEntry(ANSC_HANDLE hInsContext, ULONG nIndex, ULONG* pInsNumber)
{

    ANSC_HANDLE ret = NULL;

    TELCOVOICEMGR_LOCK_OR_EXIT()

    PDML_VOICE_SERVICE_CTRL_T pVoiceService = (PDML_VOICE_SERVICE_CTRL_T) hInsContext;

    PTELCOVOICEMGR_DML_VOICESERVICE pDmlVoiceService = &(pVoiceService->dml);

    PDML_CALLCONTROL_GROUP_LIST_T pGroupList = &(pDmlVoiceService->CallControl_obj.Group);

    if(pGroupList != NULL)
    {
        if(nIndex < pGroupList->ulQuantity)
        {
            PDML_CALLCONTROL_GROUP_CTRL_T pGroupCtrl = pGroupList->pdata[nIndex];
            if(pGroupCtrl != NULL)
            {
               *pInsNumber = nIndex + 1;
               ret = (ANSC_HANDLE) pGroupCtrl;
            }
        }
    }

    TELCOVOICEMGR_UNLOCK()

    return ret;
}

/**********************************************************************

    caller:     owner of this object

    prototype:

        BOOL TelcoVoiceMgrDml_CallControl_GroupList_GetParamUlongValue(ANSC_HANDLE hInsContext, char* ParamName, ULONG* puLong);

    description:

        This function is called to retrieve ULONG parameter value;

    argument:   ANSC_HANDLE                 hInsContext,
                The instance handle;

                char*                       ParamName,
                The parameter name;

                ULONG*                      puLong
                The buffer of returned ULONG value;

    return:     TRUE if succeeded.

**********************************************************************/

BOOL TelcoVoiceMgrDml_CallControl_GroupList_GetParamUlongValue(ANSC_HANDLE hInsContext, char* ParamName, ULONG* puLong)
{
    BOOL ret = FALSE;

    if(ParamName == NULL || puLong == NULL)
    {
        CcspTraceWarning(("%s: Invalid Input Parameter [NULL]\n", __func__));
        return ret;
    }

    TELCOVOICEMGR_LOCK_OR_EXIT()

    PDML_CALLCONTROL_GROUP_CTRL_T pCallCtrlGrpCtrl = (PDML_CALLCONTROL_GROUP_CTRL_T)hInsContext;

    PDML_CALLCONTROL_GROUP pHEAD = &(pCallCtrlGrpCtrl->dml);

    if (strcmp(ParamName, "RingType") == 0)
    {
        *puLong = pHEAD->RingType;
        ret = TRUE;
    }
    else if (strcmp(ParamName, "RingTimeout") == 0)
    {
        *puLong = pHEAD->RingTimeout;
        ret = TRUE;
    }
    else
    {
        CcspTraceWarning(("%s: Unsupported parameter '%s'\n", __func__,ParamName));
    }

    TELCOVOICEMGR_UNLOCK()

    return ret;
}

/**********************************************************************

    caller:     owner of this object

    prototype:

        BOOL TelcoVoiceMgrDml_CallControl_GroupList_SetParamUlongValue(ANSC_HANDLE hInsContext, char* ParamName, ULONG uValue);

    description:

        This function is called to set ULONG parameter value;

    argument:   ANSC_HANDLE                 hInsContext,
                The instance handle;

                char*                       ParamName,
                The parameter name;

                ULONG                       uValue
                The updated ULONG value;

    return:     TRUE if succeeded.

**********************************************************************/

BOOL TelcoVoiceMgrDml_CallControl_GroupList_SetParamUlongValue(ANSC_HANDLE hInsContext, char* ParamName, ULONG uValue)
{
    BOOL ret = FALSE;
    ULONG uVsIndex  = 0;
    ULONG uGroupIndex = 0;
    char HalName[MAX_STR_LEN] = {0};

    PTELCOVOICEMGR_DML_VOICESERVICE pDmlVoiceService = NULL;

    if(ParamName == NULL)
    {
        CcspTraceWarning(("%s: Invalid Input Parameter [NULL]\n", __func__));
        return ret;
    }

    TELCOVOICEMGR_LOCK_OR_EXIT()

    PDML_CALLCONTROL_GROUP_CTRL_T pCallCtrlGrpCtrl = (PDML_CALLCONTROL_GROUP_CTRL_T)hInsContext;

    PDML_CALLCONTROL_GROUP pHEAD = &(pCallCtrlGrpCtrl->dml);

    if(pHEAD != NULL)
    {
        pDmlVoiceService = (PTELCOVOICEMGR_DML_VOICESERVICE)pHEAD->pParentVoiceService;
    }

    if (pHEAD == NULL  || pDmlVoiceService == NULL)
    {
        TELCOVOICEMGR_UNLOCK()

        CcspTraceError(("%s:%d:: pHEAD or pDmlVoiceService NULL\n", __FUNCTION__, __LINE__));

        return ret;
    }

    uVsIndex = pDmlVoiceService->InstanceNumber;

    uGroupIndex = pHEAD->uInstanceNumber;

    TELCOVOICEMGR_UNLOCK()

    if (strcmp(ParamName, "RingType") == 0)
    {
        char enumValue[][STR_LEN_32]={"Simultaneous","Hierarchical","Cyclic"};

        snprintf(HalName, MAX_STR_LEN, "Device.Services.VoiceService.%d.CallControl.Group.%d.RingType",uVsIndex,uGroupIndex);

        if (TelcoVoiceMgrHal_SetParamString(HalName,enumValue[uValue]) == ANSC_STATUS_SUCCESS)
        {
            TELCOVOICEMGR_LOCK_OR_EXIT()

            pHEAD->RingType = uValue;

            TELCOVOICEMGR_UNLOCK()

            ret = TRUE;
        }
    }
    else if (strcmp(ParamName, "RingTimeout") == 0)
    {
        snprintf(HalName, MAX_STR_LEN, "Device.Services.VoiceService.%d.CallControl.Group.%d.RingTimeout",uVsIndex,uGroupIndex);

        if (TelcoVoiceMgrHal_SetParamULong(HalName,uValue) == ANSC_STATUS_SUCCESS)
        {
            TELCOVOICEMGR_LOCK_OR_EXIT()

            pHEAD->RingTimeout = uValue;

            TELCOVOICEMGR_UNLOCK()

            ret = TRUE;
        }
    }
    else
    {
        CcspTraceWarning(("%s: Unsupported parameter '%s'\n", __func__,ParamName));
    }

    return ret;

}

/**********************************************************************

    caller:     owner of this object

    prototype:

        ULONG TelcoVoiceMgrDml_CallControl_GroupList_GetParamStringValue(ANSC_HANDLE hInsContext, char* ParamName, char* pValue, ULONG* pulSize);

    description:

        This function is called to retrieve string parameter value;

    argument:   ANSC_HANDLE                 hInsContext,
                The instance handle;

                char*                       ParamName,
                The parameter name;

                char*                       pValue,
                The string value buffer;

                ULONG*                      pUlSize
                The buffer of length of string value;
                Usually size of 1023 will be used.
                If it's not big enough, put required size here and return 1;

    return:     0 if succeeded;
                1 if short of buffer size; (*pUlSize = required size)
                -1 if not supported.

**********************************************************************/

ULONG TelcoVoiceMgrDml_CallControl_GroupList_GetParamStringValue(ANSC_HANDLE hInsContext, char* ParamName, char* pValue, ULONG* pulSize)
{
    ULONG ret = 1;

    if(ParamName == NULL || pValue == NULL || pulSize == NULL)
    {
        CcspTraceWarning(("%s: Invalid Input Parameter [NULL]\n", __func__));
        return ret;
    }

    TELCOVOICEMGR_LOCK_OR_EXIT()

    PDML_CALLCONTROL_GROUP_CTRL_T pCallCtrlGrpCtrl = (PDML_CALLCONTROL_GROUP_CTRL_T)hInsContext;

    PDML_CALLCONTROL_GROUP pHEAD = &(pCallCtrlGrpCtrl->dml);

    if (strcmp(ParamName, "Extensions") == 0)
    {
        AnscCopyString(pValue,pHEAD->Extensions);
        ret = 0;
    }
    else if (strcmp(ParamName, "Alias") == 0)
    {
        AnscCopyString(pValue,pHEAD->Alias);
        ret = 0;
    }
    else
    {
        CcspTraceWarning(("%s: Unsupported parameter '%s'\n", __func__,ParamName));
    }

    TELCOVOICEMGR_UNLOCK()

    return ret ;
}

/**********************************************************************

    caller:     owner of this object

    prototype:

        BOOL TelcoVoiceMgrDml_CallControl_GroupList_SetParamStringValue(ANSC_HANDLE hInsContext, char* ParamName, char* pString);

    description:

        This function is called to set string parameter value;

    argument:   ANSC_HANDLE                 hInsContext,
                The instance handle;

                char*                       ParamName,
                The parameter name;

                char*                       pString
                The updated string value;

    return:     TRUE if succeeded.

**********************************************************************/

BOOL TelcoVoiceMgrDml_CallControl_GroupList_SetParamStringValue(ANSC_HANDLE hInsContext, char* ParamName, char* pString)
{
    BOOL ret = FALSE;
    ULONG uVsIndex  = 0;
    ULONG uGroupIndex = 0;
    char HalName[MAX_STR_LEN] = {0};

    PTELCOVOICEMGR_DML_VOICESERVICE pDmlVoiceService = NULL;

    if(ParamName == NULL)
    {
        CcspTraceWarning(("%s: Invalid Input Parameter [NULL]\n", __func__));
        return ret;
    }

    TELCOVOICEMGR_LOCK_OR_EXIT()

    PDML_CALLCONTROL_GROUP_CTRL_T pCallCtrlGrpCtrl = (PDML_CALLCONTROL_GROUP_CTRL_T)hInsContext;

    PDML_CALLCONTROL_GROUP pHEAD = &(pCallCtrlGrpCtrl->dml);

    if(pHEAD != NULL)
    {
        pDmlVoiceService = (PTELCOVOICEMGR_DML_VOICESERVICE)pHEAD->pParentVoiceService;
    }

    if (pHEAD == NULL  || pDmlVoiceService == NULL)
    {
        TELCOVOICEMGR_UNLOCK()

        CcspTraceError(("%s:%d:: pHEAD or pDmlVoiceService NULL\n", __FUNCTION__, __LINE__));

        return ret;
    }

    uVsIndex = pDmlVoiceService->InstanceNumber;

    uGroupIndex = pHEAD->uInstanceNumber;

    TELCOVOICEMGR_UNLOCK()

    if (strcmp(ParamName, "Extensions") == 0)
    {
        snprintf(HalName, MAX_STR_LEN, "Device.Services.VoiceService.%d.CallControl.Group.%d.Extensions",uVsIndex,uGroupIndex);

        if (TelcoVoiceMgrHal_SetParamString(HalName,pString) == ANSC_STATUS_SUCCESS)
        {
            TELCOVOICEMGR_LOCK_OR_EXIT()

            AnscCopyString(pHEAD->Extensions,pString);

            TELCOVOICEMGR_UNLOCK()

            ret = TRUE;
        }
    }
    else if (strcmp(ParamName, "Alias") == 0)
    {
        TELCOVOICEMGR_LOCK_OR_EXIT()

        AnscCopyString(pHEAD->Alias,pString);

        TELCOVOICEMGR_UNLOCK()

        ret = TRUE;
    }
    else
    {
        CcspTraceWarning(("%s: Unsupported parameter '%s'\n", __func__,ParamName));
    }

    return ret ;

}

/**********************************************************************

    caller:     owner of this object

    prototype:

        BOOL TelcoVoiceMgrDml_CallControl_GroupList_Validate(ANSC_HANDLE hInsContext);

    description:

        This function is called to validate the update.

    argument:   ANSC_HANDLE                 hInsContext,
                The instance handle;

    return:     TRUE if there's no issue.

**********************************************************************/

BOOL TelcoVoiceMgrDml_CallControl_GroupList_Validate(ANSC_HANDLE hInsContext)
{
    return TRUE;
}

/**********************************************************************

    caller:     owner of this object

    prototype:

        BOOL TelcoVoiceMgrDml_CallControl_GroupList_Commit(ANSC_HANDLE hInsContext);

    description:

        This function is called to commit the update.

    argument:   ANSC_HANDLE                 hInsContext,
                The instance handle;

    return:     0 if there's no issue.

**********************************************************************/

BOOL TelcoVoiceMgrDml_CallControl_GroupList_Commit(ANSC_HANDLE hInsContext)
{
    return 0;
}

/**********************************************************************

    caller:     owner of this object

    prototype:

        BOOL TelcoVoiceMgrDml_CallControl_GroupList_Rollback(ANSC_HANDLE hInsContext);

    description:

        This function is called to rollback the update.

    argument:   ANSC_HANDLE                 hInsContext,
                The instance handle;

    return:     0 if there's no issue.

**********************************************************************/

BOOL TelcoVoiceMgrDml_CallControl_GroupList_Rollback(ANSC_HANDLE hInsContext)
{
    return 0;
}

/**********************************************************************

    caller:     owner of this object

    prototype:

        BOOL TelcoVoiceMgrDml_CallControl_MailboxList_IsUpdated(ANSC_HANDLE hInsContext);

    description:

        This function is checking whether the table is updated or not.

    argument:   ANSC_HANDLE                 hInsContext,
                The instance handle;

    return:     TRUE or FALSE.

**********************************************************************/

BOOL TelcoVoiceMgrDml_CallControl_MailboxList_IsUpdated(ANSC_HANDLE hInsContext)
{
    return TRUE;
}

/**********************************************************************

    caller:     owner of this object

    prototype:

        ULONG TelcoVoiceMgrDml_CallControl_MailboxList_Synchronize(ANSC_HANDLE hInsContext);

    description:

        This function is called to synchronize the table.

    argument:   ANSC_HANDLE                 hInsContext,
                The instance handle;

    return:     The status of the operation.

**********************************************************************/

ULONG TelcoVoiceMgrDml_CallControl_MailboxList_Synchronize(ANSC_HANDLE hInsContext)
{
    return 0;
}

/**********************************************************************

    caller:     owner of this object

    prototype:

        ULONG TelcoVoiceMgrDml_CallControl_MailboxList_GetEntryCount(ANSC_HANDLE hInsContext);

    description:

        This function is called to retrieve the count of the table.

    argument:   ANSC_HANDLE                 hInsContext,
                The instance handle;

    return:     The count of the table

**********************************************************************/
ULONG TelcoVoiceMgrDml_CallControl_MailboxList_GetEntryCount(ANSC_HANDLE hInsContext)
{
    ULONG ret = 0;

    TELCOVOICEMGR_LOCK_OR_EXIT()

    DML_VOICE_SERVICE_CTRL_T* pVoiceService = (DML_VOICE_SERVICE_CTRL_T*) hInsContext;

    PTELCOVOICEMGR_DML_VOICESERVICE pDmlVoiceService = &(pVoiceService->dml);

    PDML_CALLCONTROL_MAILBOX_LIST_T pCallCtrlMailBoxList = &(pDmlVoiceService->CallControl_obj.Mailbox);

    if(pCallCtrlMailBoxList != NULL)
    {
        ret = pCallCtrlMailBoxList->ulQuantity;
    }

    TELCOVOICEMGR_UNLOCK()

    return ret;
}

/**********************************************************************

    caller:     owner of this object

    prototype:

        ANSC_HANDLE TelcoVoiceMgrDml_CallControl_MailboxList_GetEntry(ANSC_HANDLE hInsContext, ULONG nIndex, ULONG* pInsNumber);

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
ANSC_HANDLE TelcoVoiceMgrDml_CallControl_MailboxList_GetEntry(ANSC_HANDLE hInsContext, ULONG nIndex, ULONG* pInsNumber)
{
    ANSC_HANDLE ret = NULL;

    TELCOVOICEMGR_LOCK_OR_EXIT()

    PDML_VOICE_SERVICE_CTRL_T pVoiceService = (PDML_VOICE_SERVICE_CTRL_T) hInsContext;

    PTELCOVOICEMGR_DML_VOICESERVICE pDmlVoiceService = &(pVoiceService->dml);

    PDML_CALLCONTROL_MAILBOX_LIST_T pMailboxList = &(pDmlVoiceService->CallControl_obj.Mailbox);

    if(pMailboxList != NULL)
    {
        if(nIndex < pMailboxList->ulQuantity)
        {
            PDML_CALLCONTROL_MAILBOX_CTRL_T pMailboxCtrl = pMailboxList->pdata[nIndex];
            if(pMailboxCtrl != NULL)
            {
               *pInsNumber = nIndex + 1;
               ret = (ANSC_HANDLE) pMailboxCtrl;
            }
        }
    }

    TELCOVOICEMGR_UNLOCK()

    return ret;
}

/**********************************************************************

    caller:     owner of this object

    prototype:

        BOOL TelcoVoiceMgrDml_CallControl_MailboxList_GetParamUlongValue(ANSC_HANDLE hInsContext, char* ParamName, ULONG* puLong);

    description:

        This function is called to retrieve ULONG parameter value;

    argument:   ANSC_HANDLE                 hInsContext,
                The instance handle;

                char*                       ParamName,
                The parameter name;

                ULONG*                      puLong
                The buffer of returned ULONG value;

    return:     TRUE if succeeded.

**********************************************************************/

BOOL TelcoVoiceMgrDml_CallControl_MailboxList_GetParamUlongValue(ANSC_HANDLE hInsContext, char* ParamName, ULONG* puLong)
{
    BOOL ret = FALSE;

    if(ParamName == NULL || puLong == NULL)
    {
        CcspTraceWarning(("%s: Invalid Input Parameter [NULL]\n", __func__));
        return ret;
    }

    TELCOVOICEMGR_LOCK_OR_EXIT()

    PDML_CALLCONTROL_MAILBOX_CTRL_T pCallCtrlMailBoxCtrl = (PDML_CALLCONTROL_MAILBOX_CTRL_T)hInsContext;

    PDML_CALLCONTROL_MAILBOX pHEAD = &(pCallCtrlMailBoxCtrl->dml);

    if (strcmp(ParamName, "SMTPServerPort") == 0)
    {
        *puLong = pHEAD->SMTPServerPort;
        ret = TRUE;
    }
    else if (strcmp(ParamName, "SMTPAuthenticationType") == 0)
    {
        *puLong = pHEAD->SMTPAuthenticationType;
        ret = TRUE;
    }
    else if (strcmp(ParamName, "MinSize") == 0)
    {
        *puLong = pHEAD->MinSize;
        ret = TRUE;
    }
    else if (strcmp(ParamName, "MaxMsg") == 0)
    {
        *puLong = pHEAD->MaxMsg;
        ret = TRUE;
    }
    else if (strcmp(ParamName, "MaxMessageTime") == 0)
    {
        *puLong = pHEAD->MaxMessageTime;
        ret = TRUE;
    }
    else
    {
        CcspTraceWarning(("%s: Unsupported parameter '%s'\n", __func__,ParamName));
    }

    TELCOVOICEMGR_UNLOCK()

    return ret;
}

/**********************************************************************

    caller:     owner of this object

    prototype:

        BOOL TelcoVoiceMgrDml_CallControl_MailboxList_SetParamUlongValue(ANSC_HANDLE hInsContext, char* ParamName, ULONG uValue);

    description:

        This function is called to set ULONG parameter value;

    argument:   ANSC_HANDLE                 hInsContext,
                The instance handle;

                char*                       ParamName,
                The parameter name;

                ULONG                       uValue
                The updated ULONG value;

    return:     TRUE if succeeded.

**********************************************************************/

BOOL TelcoVoiceMgrDml_CallControl_MailboxList_SetParamUlongValue(ANSC_HANDLE hInsContext, char* ParamName, ULONG uValue)
{
    BOOL ret = FALSE;
    ULONG uVsIndex  = 0;
    ULONG uMailboxIndex = 0;
    char HalName[MAX_STR_LEN] = {0};

    PTELCOVOICEMGR_DML_VOICESERVICE pDmlVoiceService = NULL;

    if(ParamName == NULL)
    {
        CcspTraceWarning(("%s: Invalid Input Parameter [NULL]\n", __func__));
        return ret;
    }

    TELCOVOICEMGR_LOCK_OR_EXIT()

    PDML_CALLCONTROL_MAILBOX_CTRL_T pCallCtrlMailBoxCtrl = (PDML_CALLCONTROL_MAILBOX_CTRL_T)hInsContext;

    PDML_CALLCONTROL_MAILBOX pHEAD = &(pCallCtrlMailBoxCtrl->dml);

    if(pHEAD != NULL)
    {
        pDmlVoiceService = (PTELCOVOICEMGR_DML_VOICESERVICE)pHEAD->pParentVoiceService;
    }

    if (pHEAD == NULL  || pDmlVoiceService == NULL)
    {
        TELCOVOICEMGR_UNLOCK()

        CcspTraceError(("%s:%d:: pHEAD or pDmlVoiceService NULL\n", __FUNCTION__, __LINE__));

        return ret;
    }

    uVsIndex = pDmlVoiceService->InstanceNumber;

    uMailboxIndex = pHEAD->uInstanceNumber;

    TELCOVOICEMGR_UNLOCK()

    if (strcmp(ParamName, "SMTPServerPort") == 0)
    {
        snprintf(HalName, MAX_STR_LEN, "Device.Services.VoiceService.%d.CallControl.Mailbox.%d.SMTPServerPort",uVsIndex,uMailboxIndex);

        if (TelcoVoiceMgrHal_SetParamULong(HalName,uValue) == ANSC_STATUS_SUCCESS)
        {
            TELCOVOICEMGR_LOCK_OR_EXIT()

            pHEAD->SMTPServerPort = uValue;

            TELCOVOICEMGR_UNLOCK()

            ret = TRUE;
        }
    }
    else if (strcmp(ParamName, "SMTPAuthenticationType") == 0)
    {
        char enumValue[][STR_LEN_32]={"None","SSL","TLS","Auto"};

        snprintf(HalName, MAX_STR_LEN, "Device.Services.VoiceService.%d.CallControl.Mailbox.%d.SMTPAuthenticationType",uVsIndex,uMailboxIndex);

        if (TelcoVoiceMgrHal_SetParamString(HalName,enumValue[uValue]) == ANSC_STATUS_SUCCESS)
        {
            TELCOVOICEMGR_LOCK_OR_EXIT()

            pHEAD->SMTPAuthenticationType = uValue;

            TELCOVOICEMGR_UNLOCK()

            ret = TRUE;
        }
    }
    else if (strcmp(ParamName, "MinSize") == 0)
    {
        snprintf(HalName, MAX_STR_LEN, "Device.Services.VoiceService.%d.CallControl.Mailbox.%d.MinSize",uVsIndex,uMailboxIndex);

        if (TelcoVoiceMgrHal_SetParamULong(HalName,uValue) == ANSC_STATUS_SUCCESS)
        {
            TELCOVOICEMGR_LOCK_OR_EXIT()

            pHEAD->MinSize = uValue;

            TELCOVOICEMGR_UNLOCK()

            ret = TRUE;
        }
    }
    else if (strcmp(ParamName, "MaxMsg") == 0)
    {
        snprintf(HalName, MAX_STR_LEN, "Device.Services.VoiceService.%d.CallControl.Mailbox.%d.MaxMsg",uVsIndex,uMailboxIndex);

        if (TelcoVoiceMgrHal_SetParamULong(HalName,uValue) == ANSC_STATUS_SUCCESS)
        {
            TELCOVOICEMGR_LOCK_OR_EXIT()

            pHEAD->MaxMsg = uValue;

            TELCOVOICEMGR_UNLOCK()

            ret = TRUE;
        }
    }
    else if (strcmp(ParamName, "MaxMessageTime") == 0)
    {
        snprintf(HalName, MAX_STR_LEN, "Device.Services.VoiceService.%d.CallControl.Mailbox.%d.MaxMessageTime",uVsIndex,uMailboxIndex);

        if (TelcoVoiceMgrHal_SetParamULong(HalName,uValue) == ANSC_STATUS_SUCCESS)
        {
            TELCOVOICEMGR_LOCK_OR_EXIT()

            pHEAD->MaxMessageTime = uValue;

            TELCOVOICEMGR_UNLOCK()

            ret = TRUE;
        }
    }
    else
    {
        CcspTraceWarning(("%s: Unsupported parameter '%s'\n", __func__,ParamName));
    }

    return ret;

}

/**********************************************************************

    caller:     owner of this object

    prototype:

        ULONG TelcoVoiceMgrDml_CallControl_MailboxList_GetParamStringValue(ANSC_HANDLE hInsContext, char* ParamName, char* pValue, ULONG* pulSize);

    description:

        This function is called to retrieve string parameter value;

    argument:   ANSC_HANDLE                 hInsContext,
                The instance handle;

                char*                       ParamName,
                The parameter name;

                char*                       pValue,
                The string value buffer;

                ULONG*                      pUlSize
                The buffer of length of string value;
                Usually size of 1023 will be used.
                If it's not big enough, put required size here and return 1;

    return:     0 if succeeded;
                1 if short of buffer size; (*pUlSize = required size)
                -1 if not supported.

**********************************************************************/

ULONG TelcoVoiceMgrDml_CallControl_MailboxList_GetParamStringValue(ANSC_HANDLE hInsContext, char* ParamName, char* pValue, ULONG* pulSize)
{
    ULONG ret = 1;

    if(ParamName == NULL || pValue == NULL || pulSize == NULL)
    {
        CcspTraceWarning(("%s: Invalid Input Parameter [NULL]\n", __func__));
        return ret;
    }

    TELCOVOICEMGR_LOCK_OR_EXIT()

    PDML_CALLCONTROL_MAILBOX_CTRL_T pCallCtrlMailBoxCtrl = (PDML_CALLCONTROL_MAILBOX_CTRL_T)hInsContext;

    PDML_CALLCONTROL_MAILBOX pHEAD = &(pCallCtrlMailBoxCtrl->dml);

    if (strcmp(ParamName, "SMTPUser") == 0)
    {
        AnscCopyString(pValue,pHEAD->SMTPUser);
        ret = 0;
    }
    else if (strcmp(ParamName, "SMTPServerAddress") == 0)
    {
        AnscCopyString(pValue,pHEAD->SMTPServerAddress);
        ret = 0;
    }
    else if (strcmp(ParamName, "SMTPPassword") == 0)
    {
        AnscCopyString(pValue,pHEAD->SMTPPassword);
        ret = 0;
    }
    else if (strcmp(ParamName, "SMTPFrom") == 0)
    {
        AnscCopyString(pValue,pHEAD->SMTPFrom);
        ret = 0;
    }
    else if (strcmp(ParamName, "Alias") == 0)
    {
        AnscCopyString(pValue,pHEAD->Alias);
        ret = 0;
    }
    else
    {
        CcspTraceWarning(("%s: Unsupported parameter '%s'\n", __func__,ParamName));
    }


    TELCOVOICEMGR_UNLOCK()

    return ret;
}

/**********************************************************************

    caller:     owner of this object

    prototype:

        BOOL TelcoVoiceMgrDml_CallControl_MailboxList_SetParamStringValue(ANSC_HANDLE hInsContext, char* ParamName, char* pString);

    description:

        This function is called to set string parameter value;

    argument:   ANSC_HANDLE                 hInsContext,
                The instance handle;

                char*                       ParamName,
                The parameter name;

                char*                       pString
                The updated string value;

    return:     TRUE if succeeded.

**********************************************************************/

BOOL TelcoVoiceMgrDml_CallControl_MailboxList_SetParamStringValue(ANSC_HANDLE hInsContext, char* ParamName, char* pString)
{
    BOOL ret = FALSE;
    ULONG uVsIndex  = 0;
    ULONG uMailboxIndex = 0;
    char HalName[MAX_STR_LEN] = {0};

    PTELCOVOICEMGR_DML_VOICESERVICE pDmlVoiceService = NULL;

    if(ParamName == NULL)
    {
        CcspTraceWarning(("%s: Invalid Input Parameter [NULL]\n", __func__));
        return ret;
    }

    TELCOVOICEMGR_LOCK_OR_EXIT()

    PDML_CALLCONTROL_MAILBOX_CTRL_T pCallCtrlMailBoxCtrl = (PDML_CALLCONTROL_MAILBOX_CTRL_T)hInsContext;

    PDML_CALLCONTROL_MAILBOX pHEAD = &(pCallCtrlMailBoxCtrl->dml);

    if(pHEAD != NULL)
    {
        pDmlVoiceService = (PTELCOVOICEMGR_DML_VOICESERVICE)pHEAD->pParentVoiceService;
    }

    if (pHEAD == NULL  || pDmlVoiceService == NULL)
    {
        TELCOVOICEMGR_UNLOCK()

        CcspTraceError(("%s:%d:: pHEAD or pDmlVoiceService NULL\n", __FUNCTION__, __LINE__));

        return ret;
    }

    uVsIndex = pDmlVoiceService->InstanceNumber;

    uMailboxIndex = pHEAD->uInstanceNumber;

    TELCOVOICEMGR_UNLOCK()

    if (strcmp(ParamName, "SMTPUser") == 0)
    {
        snprintf(HalName, MAX_STR_LEN, "Device.Services.VoiceService.%d.CallControl.Mailbox.%d.SMTPUser",uVsIndex,uMailboxIndex);

        if (TelcoVoiceMgrHal_SetParamString(HalName,pString) == ANSC_STATUS_SUCCESS)
        {
            TELCOVOICEMGR_LOCK_OR_EXIT()

            AnscCopyString(pHEAD->SMTPUser, pString);

            TELCOVOICEMGR_UNLOCK()

            ret = TRUE;
        }
    }
    else if (strcmp(ParamName, "SMTPServerAddress") == 0)
    {
        snprintf(HalName, MAX_STR_LEN, "Device.Services.VoiceService.%d.CallControl.Mailbox.%d.SMTPServerAddress",uVsIndex,uMailboxIndex);

        if (TelcoVoiceMgrHal_SetParamString(HalName,pString) == ANSC_STATUS_SUCCESS)
        {
            TELCOVOICEMGR_LOCK_OR_EXIT()

            AnscCopyString(pHEAD->SMTPServerAddress, pString);

            TELCOVOICEMGR_UNLOCK()

            ret = TRUE;
        }
    }
    else if (strcmp(ParamName, "SMTPPassword") == 0)
    {
        snprintf(HalName, MAX_STR_LEN, "Device.Services.VoiceService.%d.CallControl.Mailbox.%d.SMTPPassword",uVsIndex,uMailboxIndex);

        if (TelcoVoiceMgrHal_SetParamString(HalName,pString) == ANSC_STATUS_SUCCESS)
        {
            TELCOVOICEMGR_LOCK_OR_EXIT()

            AnscCopyString(pHEAD->SMTPPassword, pString);

            TELCOVOICEMGR_UNLOCK()

            ret = TRUE;
        }
    }
    else if (strcmp(ParamName, "SMTPFrom") == 0)
    {
        snprintf(HalName, MAX_STR_LEN, "Device.Services.VoiceService.%d.CallControl.Mailbox.%d.SMTPFrom",uVsIndex,uMailboxIndex);

        if (TelcoVoiceMgrHal_SetParamString(HalName,pString) == ANSC_STATUS_SUCCESS)
        {
            TELCOVOICEMGR_LOCK_OR_EXIT()

            AnscCopyString(pHEAD->SMTPFrom, pString);

            TELCOVOICEMGR_UNLOCK()

            ret = TRUE;
        }
    }
    else if (strcmp(ParamName, "Alias") == 0)
    {
        TELCOVOICEMGR_LOCK_OR_EXIT()

        AnscCopyString(pHEAD->Alias, pString);

        TELCOVOICEMGR_UNLOCK()

        ret = TRUE;
    }
    else
    {
        CcspTraceWarning(("%s: Unsupported parameter '%s'\n", __func__,ParamName));
    }

    return ret;

}

/**********************************************************************

    caller:     owner of this object

    prototype:

        BOOL TelcoVoiceMgrDml_CallControl_MailboxList_GetParamBoolValue(ANSC_HANDLE hInsContext, char* ParamName, BOOL* pBool);

    description:

        This function is called to retrieve Boolean parameter value;

    argument:   ANSC_HANDLE                 hInsContext,
                The instance handle;

                char*                       ParamName,
                The parameter name;

                BOOL*                       pBool
                The buffer of returned boolean value;

    return:     TRUE if succeeded.

**********************************************************************/

BOOL TelcoVoiceMgrDml_CallControl_MailboxList_GetParamBoolValue(ANSC_HANDLE hInsContext, char* ParamName, BOOL* pBool)
{
    BOOL ret = FALSE;

    if(ParamName == NULL || pBool == NULL)
    {
        CcspTraceWarning(("%s: Invalid Input Parameter [NULL]\n", __func__));
        return ret;
    }

    TELCOVOICEMGR_LOCK_OR_EXIT()

    PDML_CALLCONTROL_MAILBOX_CTRL_T pCallCtrlMailBoxCtrl = (PDML_CALLCONTROL_MAILBOX_CTRL_T)hInsContext;

    PDML_CALLCONTROL_MAILBOX pHEAD = &(pCallCtrlMailBoxCtrl->dml);

    if (strcmp(ParamName, "Enable") == 0)
    {
        *pBool = pHEAD->Enable;
        ret = TRUE;
    }
    else
    {
        CcspTraceWarning(("%s: Unsupported parameter '%s'\n", __func__,ParamName));
    }

    TELCOVOICEMGR_UNLOCK()

    return ret;
}

/**********************************************************************

    caller:     owner of this object

    prototype:

        BOOL TelcoVoiceMgrDml_CallControl_MailboxList_SetParamBoolValue(ANSC_HANDLE hInsContext, char* ParamName, BOOL bValue);

    description:

        This function is called to set BOOL parameter value;

    argument:   ANSC_HANDLE                 hInsContext,
                The instance handle;

                char*                       ParamName,
                The parameter name;

                BOOL                        bValue
                The updated BOOL value;

    return:     TRUE if succeeded.

**********************************************************************/

BOOL TelcoVoiceMgrDml_CallControl_MailboxList_SetParamBoolValue(ANSC_HANDLE hInsContext, char* ParamName, BOOL bValue)
{
    BOOL ret = FALSE;
    ULONG uVsIndex  = 0;
    ULONG uMailboxIndex = 0;
    char HalName[MAX_STR_LEN] = {0};

    PTELCOVOICEMGR_DML_VOICESERVICE pDmlVoiceService = NULL;

    if(ParamName == NULL)
    {
        CcspTraceWarning(("%s: Invalid Input Parameter [NULL]\n", __func__));
        return ret;
    }

    TELCOVOICEMGR_LOCK_OR_EXIT()

    PDML_CALLCONTROL_MAILBOX_CTRL_T pCallCtrlMailBoxCtrl = (PDML_CALLCONTROL_MAILBOX_CTRL_T)hInsContext;

    PDML_CALLCONTROL_MAILBOX pHEAD = &(pCallCtrlMailBoxCtrl->dml);

    if(pHEAD != NULL)
    {
        pDmlVoiceService = (PTELCOVOICEMGR_DML_VOICESERVICE)pHEAD->pParentVoiceService;
    }

    if (pHEAD == NULL  || pDmlVoiceService == NULL)
    {
        TELCOVOICEMGR_UNLOCK()

        CcspTraceError(("%s:%d:: pHEAD or pDmlVoiceService NULL\n", __FUNCTION__, __LINE__));

        return ret;
    }

    uVsIndex = pDmlVoiceService->InstanceNumber;

    uMailboxIndex = pHEAD->uInstanceNumber;

    TELCOVOICEMGR_UNLOCK()

    if (strcmp(ParamName, "Enable") == 0)
    {
        snprintf(HalName, MAX_STR_LEN, "Device.Services.VoiceService.%d.CallControl.Mailbox.%d.Enable",uVsIndex,uMailboxIndex);

        if (TelcoVoiceMgrHal_SetParamBool(HalName,bValue) == ANSC_STATUS_SUCCESS)
        {
            TELCOVOICEMGR_LOCK_OR_EXIT()

            pHEAD->Enable = bValue;

            TELCOVOICEMGR_UNLOCK()

            ret = TRUE;
        }
    }
    else
    {
        CcspTraceWarning(("%s: Unsupported parameter '%s'\n", __func__,ParamName));
    }

    return ret;

}

/**********************************************************************

    caller:     owner of this object

    prototype:

        BOOL TelcoVoiceMgrDml_CallControl_MailboxList_Validate(ANSC_HANDLE hInsContext);

    description:

        This function is called to validate the update.

    argument:   ANSC_HANDLE                 hInsContext,
                The instance handle;

    return:     TRUE if there's no issue.

**********************************************************************/

BOOL TelcoVoiceMgrDml_CallControl_MailboxList_Validate(ANSC_HANDLE hInsContext)
{
    return TRUE;
}

/**********************************************************************

    caller:     owner of this object

    prototype:

        BOOL TelcoVoiceMgrDml_CallControl_MailboxList_Commit(ANSC_HANDLE hInsContext);

    description:

        This function is called to commit the update.

    argument:   ANSC_HANDLE                 hInsContext,
                The instance handle;

    return:     0 if there's no issue.

**********************************************************************/

BOOL TelcoVoiceMgrDml_CallControl_MailboxList_Commit(ANSC_HANDLE hInsContext)
{
    return 0;
}

/**********************************************************************

    caller:     owner of this object

    prototype:

        BOOL TelcoVoiceMgrDml_CallControl_MailboxList_Rollback(ANSC_HANDLE hInsContext);

    description:

        This function is called to rollback the update.

    argument:   ANSC_HANDLE                 hInsContext,
                The instance handle;

    return:     0 if there's no issue.

**********************************************************************/

BOOL TelcoVoiceMgrDml_CallControl_MailboxList_Rollback(ANSC_HANDLE hInsContext)
{
    return 0;
}

/**********************************************************************

    caller:     owner of this object

    prototype:

        BOOL TelcoVoiceMgrDml_CallControl_IncomingMapList_IsUpdated(ANSC_HANDLE hInsContext);

    description:

        This function is checking whether the table is updated or not.

    argument:   ANSC_HANDLE                 hInsContext,
                The instance handle;

    return:     TRUE or FALSE.

**********************************************************************/

BOOL TelcoVoiceMgrDml_CallControl_IncomingMapList_IsUpdated(ANSC_HANDLE hInsContext)
{
    return TRUE;
}

/**********************************************************************

    caller:     owner of this object

    prototype:

        ULONG TelcoVoiceMgrDml_CallControl_IncomingMapList_Synchronize(ANSC_HANDLE hInsContext);

    description:

        This function is called to synchronize the table.

    argument:   ANSC_HANDLE                 hInsContext,
                The instance handle;

    return:     The status of the operation.

**********************************************************************/

ULONG TelcoVoiceMgrDml_CallControl_IncomingMapList_Synchronize(ANSC_HANDLE hInsContext)
{
    return 0;
}

/**********************************************************************

    caller:     owner of this object

    prototype:

        ULONG TelcoVoiceMgrDml_CallControl_IncomingMapList_GetEntryCount(ANSC_HANDLE hInsContext);

    description:

        This function is called to retrieve the count of the table.

    argument:   ANSC_HANDLE                 hInsContext,
                The instance handle;

    return:     The count of the table

**********************************************************************/
ULONG TelcoVoiceMgrDml_CallControl_IncomingMapList_GetEntryCount(ANSC_HANDLE hInsContext)
{
    ULONG ret = 0;

    TELCOVOICEMGR_LOCK_OR_EXIT()

    DML_VOICE_SERVICE_CTRL_T* pVoiceService = (DML_VOICE_SERVICE_CTRL_T*) hInsContext;

    PTELCOVOICEMGR_DML_VOICESERVICE pDmlVoiceService = &(pVoiceService->dml);

    PDML_CALLCONTROL_INCOMINGMAP_LIST_T pCallCtrlInMapList = &(pDmlVoiceService->CallControl_obj.IncommingMap);

    if(pCallCtrlInMapList)
    {
        ret = pCallCtrlInMapList->ulQuantity;
    }

    TELCOVOICEMGR_UNLOCK()

    return ret;
}

/**********************************************************************

    caller:     owner of this object

    prototype:

        ANSC_HANDLE TelcoVoiceMgrDml_CallControl_IncomingMapList_GetEntry(ANSC_HANDLE hInsContext, ULONG nIndex, ULONG* pInsNumber);

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
ANSC_HANDLE TelcoVoiceMgrDml_CallControl_IncomingMapList_GetEntry(ANSC_HANDLE hInsContext, ULONG nIndex, ULONG* pInsNumber)
{

    ANSC_HANDLE ret = NULL;

    TELCOVOICEMGR_LOCK_OR_EXIT()

    PDML_VOICE_SERVICE_CTRL_T pVoiceService = (PDML_VOICE_SERVICE_CTRL_T) hInsContext;

    PTELCOVOICEMGR_DML_VOICESERVICE pDmlVoiceService = &(pVoiceService->dml);

    PDML_CALLCONTROL_INCOMINGMAP_LIST_T pInmapList = &(pDmlVoiceService->CallControl_obj.IncommingMap);

    if(pInmapList != NULL)
    {
        if(nIndex < pInmapList->ulQuantity)
        {
            PDML_CALLCONTROL_INCOMINGMAP_CTRL_T pInmapCtrl = pInmapList->pdata[nIndex];
            if(pInmapCtrl != NULL)
            {
               *pInsNumber = nIndex + 1;
               ret = (ANSC_HANDLE) pInmapCtrl;
            }
        }
    }

    TELCOVOICEMGR_UNLOCK()

    return ret;
}

/**********************************************************************

    caller:     owner of this object

    prototype:

        BOOL TelcoVoiceMgrDml_CallControl_IncomingMapList_GetParamUlongValue(ANSC_HANDLE hInsContext, char* ParamName, ULONG* puLong);

    description:

        This function is called to retrieve ULONG parameter value;

    argument:   ANSC_HANDLE                 hInsContext,
                The instance handle;

                char*                       ParamName,
                The parameter name;

                ULONG*                      puLong
                The buffer of returned ULONG value;

    return:     TRUE if succeeded.

**********************************************************************/

BOOL TelcoVoiceMgrDml_CallControl_IncomingMapList_GetParamUlongValue(ANSC_HANDLE hInsContext, char* ParamName, ULONG* puLong)
{
    BOOL ret = FALSE;

    if(ParamName == NULL || puLong == NULL)
    {
        CcspTraceWarning(("%s: Invalid Input Parameter [NULL]\n", __func__));
        return ret;
    }

    TELCOVOICEMGR_LOCK_OR_EXIT()

    PDML_CALLCONTROL_INCOMINGMAP_CTRL_T pCallCtrlInMapCtrl = (PDML_CALLCONTROL_INCOMINGMAP_CTRL_T)hInsContext;

    PDML_CALLCONTROL_INCOMINGMAP pHEAD = &(pCallCtrlInMapCtrl->dml);

    if (strcmp(ParamName, "Timeout") == 0)
    {
        *puLong = pHEAD->Timeout;
        ret = TRUE;
    }
    else if (strcmp(ParamName, "Order") == 0)
    {
        *puLong = pHEAD->Order;
        ret = TRUE;
    }
    else
    {
        CcspTraceWarning(("%s: Unsupported parameter '%s'\n", __func__,ParamName));
    }


    TELCOVOICEMGR_UNLOCK()

    return ret;
}

/**********************************************************************

    caller:     owner of this object

    prototype:

        BOOL TelcoVoiceMgrDml_CallControl_IncomingMapList_SetParamUlongValue(ANSC_HANDLE hInsContext, char* ParamName, ULONG uValue);

    description:

        This function is called to set ULONG parameter value;

    argument:   ANSC_HANDLE                 hInsContext,
                The instance handle;

                char*                       ParamName,
                The parameter name;

                ULONG                       uValue
                The updated ULONG value;

    return:     TRUE if succeeded.

**********************************************************************/

BOOL TelcoVoiceMgrDml_CallControl_IncomingMapList_SetParamUlongValue(ANSC_HANDLE hInsContext, char* ParamName, ULONG uValue)
{
    BOOL ret = FALSE;
    ULONG uVsIndex  = 0;
    ULONG uInMapIndex = 0;
    char HalName[MAX_STR_LEN] = {0};

    PTELCOVOICEMGR_DML_VOICESERVICE pDmlVoiceService = NULL;

    if(ParamName == NULL)
    {
        CcspTraceWarning(("%s: Invalid Input Parameter [NULL]\n", __func__));
        return ret;
    }

    TELCOVOICEMGR_LOCK_OR_EXIT()

    PDML_CALLCONTROL_INCOMINGMAP_CTRL_T pCallCtrlInMapCtrl = (PDML_CALLCONTROL_INCOMINGMAP_CTRL_T)hInsContext;

    PDML_CALLCONTROL_INCOMINGMAP pHEAD = &(pCallCtrlInMapCtrl->dml);

    if(pHEAD != NULL)
    {
        pDmlVoiceService = (PTELCOVOICEMGR_DML_VOICESERVICE)pHEAD->pParentVoiceService;
    }

    if (pHEAD == NULL  || pDmlVoiceService == NULL)
    {
        TELCOVOICEMGR_UNLOCK()

        CcspTraceError(("%s:%d:: pHEAD or pDmlVoiceService NULL\n", __FUNCTION__, __LINE__));

        return ret;
    }

    uVsIndex = pDmlVoiceService->InstanceNumber;

    uInMapIndex = pHEAD->uInstanceNumber;

    TELCOVOICEMGR_UNLOCK()

    if (strcmp(ParamName, "Timeout") == 0)
    {
        snprintf(HalName, MAX_STR_LEN, "Device.Services.VoiceService.%d.CallControl.IncomingMap.%d.Timeout",uVsIndex,uInMapIndex);

        if (TelcoVoiceMgrHal_SetParamULong(HalName,uValue) == ANSC_STATUS_SUCCESS)
        {
            TELCOVOICEMGR_LOCK_OR_EXIT()

            pHEAD->Timeout = uValue;

            TELCOVOICEMGR_UNLOCK()

            ret = TRUE;
        }
    }
    else if (strcmp(ParamName, "Order") == 0)
    {
        snprintf(HalName, MAX_STR_LEN, "Device.Services.VoiceService.%d.CallControl.IncomingMap.%d.Order",uVsIndex,uInMapIndex);

        if (TelcoVoiceMgrHal_SetParamULong(HalName,uValue) == ANSC_STATUS_SUCCESS)
        {
            TELCOVOICEMGR_LOCK_OR_EXIT()

            pHEAD->Order = uValue;

            TELCOVOICEMGR_UNLOCK()

            ret = TRUE;
        }
    }
    else
    {
        CcspTraceWarning(("%s: Unsupported parameter '%s'\n", __func__,ParamName));
    }

    return ret;
}

/**********************************************************************

    caller:     owner of this object

    prototype:

        ULONG TelcoVoiceMgrDml_CallControl_IncomingMapList_GetParamStringValue(ANSC_HANDLE hInsContext, char* ParamName, char* pValue, ULONG* pulSize);

    description:

        This function is called to retrieve string parameter value;

    argument:   ANSC_HANDLE                 hInsContext,
                The instance handle;

                char*                       ParamName,
                The parameter name;

                char*                       pValue,
                The string value buffer;

                ULONG*                      pUlSize
                The buffer of length of string value;
                Usually size of 1023 will be used.
                If it's not big enough, put required size here and return 1;

    return:     0 if succeeded;
                1 if short of buffer size; (*pUlSize = required size)
                -1 if not supported.

**********************************************************************/

ULONG TelcoVoiceMgrDml_CallControl_IncomingMapList_GetParamStringValue(ANSC_HANDLE hInsContext, char* ParamName, char* pValue, ULONG* pulSize)
{
    ULONG ret = 1;

    if(ParamName == NULL || pValue == NULL || pulSize == NULL)
    {
        CcspTraceWarning(("%s: Invalid Input Parameter [NULL]\n", __func__));
        return ret;
    }

    TELCOVOICEMGR_LOCK_OR_EXIT()

    PDML_CALLCONTROL_INCOMINGMAP_CTRL_T pCallCtrlInMapCtrl = (PDML_CALLCONTROL_INCOMINGMAP_CTRL_T)hInsContext;

    PDML_CALLCONTROL_INCOMINGMAP pHEAD = &(pCallCtrlInMapCtrl->dml);

    if (strcmp(ParamName, "Line") == 0)
    {
        AnscCopyString(pValue,pHEAD->Line);
        ret = 0;
    }
    else if (strcmp(ParamName, "Extension") == 0)
    {
        AnscCopyString(pValue,pHEAD->Extension);
        ret = 0;
    }
    else if (strcmp(ParamName, "Alias") == 0)
    {
        AnscCopyString(pValue,pHEAD->Alias);
        ret = 0;
    }
    else
    {
        CcspTraceWarning(("%s: Unsupported parameter '%s'\n", __func__,ParamName));
    }

    TELCOVOICEMGR_UNLOCK()

    return ret;
}

/**********************************************************************

    caller:     owner of this object

    prototype:

        BOOL TelcoVoiceMgrDml_CallControl_IncomingMapList_SetParamStringValue(ANSC_HANDLE hInsContext, char* ParamName, char* pString);

    description:

        This function is called to set string parameter value;

    argument:   ANSC_HANDLE                 hInsContext,
                The instance handle;

                char*                       ParamName,
                The parameter name;

                char*                       pString
                The updated string value;

    return:     TRUE if succeeded.

**********************************************************************/

BOOL TelcoVoiceMgrDml_CallControl_IncomingMapList_SetParamStringValue(ANSC_HANDLE hInsContext, char* ParamName, char* pString)
{
    BOOL ret = FALSE;
    ULONG uVsIndex  = 0;
    ULONG uInMapIndex = 0;
    char HalName[MAX_STR_LEN] = {0};

    PTELCOVOICEMGR_DML_VOICESERVICE pDmlVoiceService = NULL;

    if(ParamName == NULL)
    {
        CcspTraceWarning(("%s: Invalid Input Parameter [NULL]\n", __func__));
        return ret;
    }

    TELCOVOICEMGR_LOCK_OR_EXIT()

    PDML_CALLCONTROL_INCOMINGMAP_CTRL_T pCallCtrlInMapCtrl = (PDML_CALLCONTROL_INCOMINGMAP_CTRL_T)hInsContext;

    PDML_CALLCONTROL_INCOMINGMAP pHEAD = &(pCallCtrlInMapCtrl->dml);

    if(pHEAD != NULL)
    {
        pDmlVoiceService = (PTELCOVOICEMGR_DML_VOICESERVICE)pHEAD->pParentVoiceService;
    }

    if (pHEAD == NULL  || pDmlVoiceService == NULL)
    {
        TELCOVOICEMGR_UNLOCK()

        CcspTraceError(("%s:%d:: pHEAD or pDmlVoiceService NULL\n", __FUNCTION__, __LINE__));

        return ret;
    }

    uVsIndex = pDmlVoiceService->InstanceNumber;

    uInMapIndex = pHEAD->uInstanceNumber;

    TELCOVOICEMGR_UNLOCK()

    if (strcmp(ParamName, "Line") == 0)
    {
        snprintf(HalName, MAX_STR_LEN, "Device.Services.VoiceService.%d.CallControl.IncomingMap.%d.Line",uVsIndex,uInMapIndex);

        if (TelcoVoiceMgrHal_SetParamString(HalName,pString) == ANSC_STATUS_SUCCESS)
        {
            TELCOVOICEMGR_LOCK_OR_EXIT()

            AnscCopyString(pHEAD->Line,pString);

            TELCOVOICEMGR_UNLOCK()

            ret = TRUE;
        }
    }
    else if (strcmp(ParamName, "Extension") == 0)
    {
        snprintf(HalName, MAX_STR_LEN, "Device.Services.VoiceService.%d.CallControl.IncomingMap.%d.Extension",uVsIndex,uInMapIndex);

        if (TelcoVoiceMgrHal_SetParamString(HalName,pString) == ANSC_STATUS_SUCCESS)
        {
            TELCOVOICEMGR_LOCK_OR_EXIT()

            AnscCopyString(pHEAD->Extension,pString);

            TELCOVOICEMGR_UNLOCK()

            ret = TRUE;
        }
    }
    else if (strcmp(ParamName, "Alias") == 0)
    {
            TELCOVOICEMGR_LOCK_OR_EXIT()

            AnscCopyString(pHEAD->Alias,pString);

            TELCOVOICEMGR_UNLOCK()

            ret = TRUE;
    }
    else
    {
        CcspTraceWarning(("%s: Unsupported parameter '%s'\n", __func__,ParamName));
    }

    return ret;

}

/**********************************************************************

    caller:     owner of this object

    prototype:

        BOOL TelcoVoiceMgrDml_CallControl_IncomingMapList_GetParamBoolValue(ANSC_HANDLE hInsContext, char* ParamName, BOOL* pBool);

    description:

        This function is called to retrieve Boolean parameter value;

    argument:   ANSC_HANDLE                 hInsContext,
                The instance handle;

                char*                       ParamName,
                The parameter name;

                BOOL*                       pBool
                The buffer of returned boolean value;

    return:     TRUE if succeeded.

**********************************************************************/

BOOL TelcoVoiceMgrDml_CallControl_IncomingMapList_GetParamBoolValue(ANSC_HANDLE hInsContext, char* ParamName, BOOL* pBool)
{
    BOOL ret = FALSE;

    if(ParamName == NULL || pBool == NULL)
    {
        CcspTraceWarning(("%s: Invalid Input Parameter [NULL]\n", __func__));
        return ret;
    }

    TELCOVOICEMGR_LOCK_OR_EXIT()

    PDML_CALLCONTROL_INCOMINGMAP_CTRL_T pCallCtrlInMapCtrl = (PDML_CALLCONTROL_INCOMINGMAP_CTRL_T)hInsContext;

    PDML_CALLCONTROL_INCOMINGMAP pHEAD = &(pCallCtrlInMapCtrl->dml);

    if (strcmp(ParamName, "Enable") == 0)
    {
        *pBool = pHEAD->Enable;
        ret = TRUE;
    }
    else
    {
        CcspTraceWarning(("%s: Unsupported parameter '%s'\n", __func__,ParamName));
    }

    TELCOVOICEMGR_UNLOCK()

    return ret;
}

/**********************************************************************

    caller:     owner of this object

    prototype:

        BOOL TelcoVoiceMgrDml_CallControl_IncomingMapList_SetParamBoolValue(ANSC_HANDLE hInsContext, char* ParamName, BOOL bValue);

    description:

        This function is called to set BOOL parameter value;

    argument:   ANSC_HANDLE                 hInsContext,
                The instance handle;

                char*                       ParamName,
                The parameter name;

                BOOL                        bValue
                The updated BOOL value;

    return:     TRUE if succeeded.

**********************************************************************/

BOOL TelcoVoiceMgrDml_CallControl_IncomingMapList_SetParamBoolValue(ANSC_HANDLE hInsContext, char* ParamName, BOOL bValue)
{
    BOOL ret = FALSE;
    ULONG uVsIndex  = 0;
    ULONG uInMapIndex = 0;
    char HalName[MAX_STR_LEN] = {0};

    PTELCOVOICEMGR_DML_VOICESERVICE pDmlVoiceService = NULL;

    if(ParamName == NULL)
    {
        CcspTraceWarning(("%s: Invalid Input Parameter [NULL]\n", __func__));
        return ret;
    }

    TELCOVOICEMGR_LOCK_OR_EXIT()

    PDML_CALLCONTROL_INCOMINGMAP_CTRL_T pCallCtrlInMapCtrl = (PDML_CALLCONTROL_INCOMINGMAP_CTRL_T)hInsContext;

    PDML_CALLCONTROL_INCOMINGMAP pHEAD = &(pCallCtrlInMapCtrl->dml);

    if(pHEAD != NULL)
    {
        pDmlVoiceService = (PTELCOVOICEMGR_DML_VOICESERVICE)pHEAD->pParentVoiceService;
    }

    if (pHEAD == NULL  || pDmlVoiceService == NULL)
    {
        TELCOVOICEMGR_UNLOCK()

        CcspTraceError(("%s:%d:: pHEAD or pDmlVoiceService NULL\n", __FUNCTION__, __LINE__));

        return ret;
    }

    uVsIndex = pDmlVoiceService->InstanceNumber;

    uInMapIndex = pHEAD->uInstanceNumber;

    TELCOVOICEMGR_UNLOCK()

    if (strcmp(ParamName, "Enable") == 0)
    {
        snprintf(HalName, MAX_STR_LEN, "Device.Services.VoiceService.%d.CallControl.IncomingMap.%d.Enable",uVsIndex,uInMapIndex);

        if (TelcoVoiceMgrHal_SetParamBool(HalName,bValue) == ANSC_STATUS_SUCCESS)
        {
            TELCOVOICEMGR_LOCK_OR_EXIT()

            pHEAD->Enable = bValue;

            TELCOVOICEMGR_UNLOCK()

            ret = TRUE;
        }
    }
    else
    {
        CcspTraceWarning(("%s: Unsupported parameter '%s'\n", __func__,ParamName));
    }

    return ret;

}

/**********************************************************************

    caller:     owner of this object

    prototype:

        BOOL TelcoVoiceMgrDml_CallControl_IncomingMapList_Validate(ANSC_HANDLE hInsContext);

    description:

        This function is called to validate the update.

    argument:   ANSC_HANDLE                 hInsContext,
                The instance handle;

    return:     TRUE if there's no issue.

**********************************************************************/

BOOL TelcoVoiceMgrDml_CallControl_IncomingMapList_Validate(ANSC_HANDLE hInsContext)
{
    return TRUE;
}

/**********************************************************************

    caller:     owner of this object

    prototype:

        BOOL TelcoVoiceMgrDml_CallControl_IncomingMapList_Commit(ANSC_HANDLE hInsContext);

    description:

        This function is called to commit the update.

    argument:   ANSC_HANDLE                 hInsContext,
                The instance handle;

    return:     0 if there's no issue.

**********************************************************************/

BOOL TelcoVoiceMgrDml_CallControl_IncomingMapList_Commit(ANSC_HANDLE hInsContext)
{
    return 0;
}

/**********************************************************************

    caller:     owner of this object

    prototype:

        BOOL TelcoVoiceMgrDml_CallControl_IncomingMapList_Rollback(ANSC_HANDLE hInsContext);

    description:

        This function is called to rollback the update.

    argument:   ANSC_HANDLE                 hInsContext,
                The instance handle;

    return:     0 if there's no issue.

**********************************************************************/

BOOL TelcoVoiceMgrDml_CallControl_IncomingMapList_Rollback(ANSC_HANDLE hInsContext)
{
    return 0;
}

/**********************************************************************

    caller:     owner of this object

    prototype:

        BOOL TelcoVoiceMgrDml_CallControl_OutgoingMapList_IsUpdated(ANSC_HANDLE hInsContext);

    description:

        This function is checking whether the table is updated or not.

    argument:   ANSC_HANDLE                 hInsContext,
                The instance handle;

    return:     TRUE or FALSE.

**********************************************************************/

BOOL TelcoVoiceMgrDml_CallControl_OutgoingMapList_IsUpdated(ANSC_HANDLE hInsContext)
{
    return TRUE;
}

/**********************************************************************

    caller:     owner of this object

    prototype:

        ULONG TelcoVoiceMgrDml_CallControl_OutgoingMapList_Synchronize(ANSC_HANDLE hInsContext);

    description:

        This function is called to synchronize the table.

    argument:   ANSC_HANDLE                 hInsContext,
                The instance handle;

    return:     The status of the operation.

**********************************************************************/

ULONG TelcoVoiceMgrDml_CallControl_OutgoingMapList_Synchronize(ANSC_HANDLE hInsContext)
{
    return 0;
}

/**********************************************************************

    caller:     owner of this object

    prototype:

        ULONG TelcoVoiceMgrDml_CallControl_OutgoingMapList_GetEntryCount(ANSC_HANDLE hInsContext);

    description:

        This function is called to retrieve the count of the table.

    argument:   ANSC_HANDLE                 hInsContext,
                The instance handle;

    return:     The count of the table

**********************************************************************/
ULONG TelcoVoiceMgrDml_CallControl_OutgoingMapList_GetEntryCount(ANSC_HANDLE hInsContext)
{
    ULONG ret = 0;

    TELCOVOICEMGR_LOCK_OR_EXIT()

    DML_VOICE_SERVICE_CTRL_T* pVoiceService = (DML_VOICE_SERVICE_CTRL_T*) hInsContext;

    PTELCOVOICEMGR_DML_VOICESERVICE pDmlVoiceService = &(pVoiceService->dml);

    PDML_CALLCONTROL_OUTGOINGMAP_LIST_T pCallCtrlOutMapList = &(pDmlVoiceService->CallControl_obj.OutgoingMap);

    if(pCallCtrlOutMapList != NULL)
    {
        ret = pCallCtrlOutMapList->ulQuantity;
    }

    TELCOVOICEMGR_UNLOCK()

    return ret;
}

/**********************************************************************

    caller:     owner of this object

    prototype:

        ANSC_HANDLE TelcoVoiceMgrDml_CallControl_OutgoingMapList_GetEntry(ANSC_HANDLE hInsContext, ULONG nIndex, ULONG* pInsNumber);

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
ANSC_HANDLE TelcoVoiceMgrDml_CallControl_OutgoingMapList_GetEntry(ANSC_HANDLE hInsContext, ULONG nIndex, ULONG* pInsNumber)
{

    ANSC_HANDLE ret = NULL;

    TELCOVOICEMGR_LOCK_OR_EXIT()

    PDML_VOICE_SERVICE_CTRL_T pVoiceService = (PDML_VOICE_SERVICE_CTRL_T) hInsContext;

    PTELCOVOICEMGR_DML_VOICESERVICE pDmlVoiceService = &(pVoiceService->dml);

    PDML_CALLCONTROL_OUTGOINGMAP_LIST_T pOutmapList = &(pDmlVoiceService->CallControl_obj.OutgoingMap);

    if(pOutmapList != NULL)
    {
        if(nIndex < pOutmapList->ulQuantity)
        {
            PDML_CALLCONTROL_OUTGOINGMAP_CTRL_T pOutmapCtrl = pOutmapList->pdata[nIndex];
            if(pOutmapCtrl != NULL)
            {
               *pInsNumber = nIndex + 1;
               ret = (ANSC_HANDLE) pOutmapCtrl;
            }
        }
    }

    TELCOVOICEMGR_UNLOCK()
    return ret;
}

/********************************************************************

    caller:     owner of this object

    prototype:

        ANSC_HANDLE TelcoVoiceMgrDml_CallControl_OutgoingMapList_AddEntry(ANSC_HANDLE hInsContext, ULONG* pInsNumber);

    description:

        This function is called to add a new entry.

    argument:   ANSC_HANDLE                 hInsContext,
                The instance handle;

                ULONG*                      pInsNumber
                The output instance number;

    return:     The handle of new added entry.

*********************************************************************/

ANSC_HANDLE TelcoVoiceMgrDml_CallControl_OutgoingMapList_AddEntry(ANSC_HANDLE hInsContext, ULONG* pInsNumber)
{
    ANSC_HANDLE ret = NULL;

    TELCOVOICEMGR_LOCK_OR_EXIT()

    DML_VOICE_SERVICE_CTRL_T* pVoiceService = (DML_VOICE_SERVICE_CTRL_T*) hInsContext;

    PTELCOVOICEMGR_DML_VOICESERVICE pDmlVoiceService = &(pVoiceService->dml);

    PDML_CALLCONTROL_OUTGOINGMAP_LIST_T pOutmapList = &(pDmlVoiceService->CallControl_obj.OutgoingMap);

    if(pOutmapList != NULL)
    {
        ret = TelcoVoiceMgrHal_AddCallCtrlOutMap((ANSC_HANDLE)pDmlVoiceService,pInsNumber,(ANSC_HANDLE)pOutmapList); // use to set alias/status/origin
        if( ret == NULL)
        {
                CcspTraceError(("%s:%d:: Add CallControl.OutgoingMap failed\n", __FUNCTION__, __LINE__));
        }
    }

    TELCOVOICEMGR_UNLOCK()

        return ret;
}

/*********************************************************************

    caller:     owner of this object

    prototype:

        ULONG TelcoVoiceMgrDml_CallControl_OutgoingMapList_DelEntry(ANSC_HANDLE hInsContext, ANSC_HANDLE hInstance);

    description:

        This function is called to delete an exist entry.

    argument:   ANSC_HANDLE                 hInsContext,
                The instance handle;

                ANSC_HANDLE                 hInstance
                The exist entry handle;

    return:     The status of the operation.

*********************************************************************/

ULONG TelcoVoiceMgrDml_CallControl_OutgoingMapList_DelEntry(ANSC_HANDLE hInsContext, ANSC_HANDLE hInstance)
{
    ANSC_STATUS ret = ANSC_STATUS_SUCCESS;
    ULONG uVsIndex  = 0;
    ULONG uOutgoingMapIndex = 0;
    char HalName[MAX_STR_LEN] = {0};

    TELCOVOICEMGR_LOCK_OR_EXIT()

    PDML_VOICE_SERVICE_CTRL_T pVoiceService = (PDML_VOICE_SERVICE_CTRL_T) hInsContext;

    PTELCOVOICEMGR_DML_VOICESERVICE pDmlVoiceService = &(pVoiceService->dml);

    PDML_CALLCONTROL_OUTGOINGMAP_LIST_T pOutmapList = &(pDmlVoiceService->CallControl_obj.OutgoingMap);

    PDML_CALLCONTROL_OUTGOINGMAP_CTRL_T pCallCtrlOutMapCtrl = (PDML_CALLCONTROL_OUTGOINGMAP_CTRL_T) hInstance;

    if(pOutmapList != NULL && pCallCtrlOutMapCtrl!= NULL)
    {
        uVsIndex = pDmlVoiceService->InstanceNumber;
        uOutgoingMapIndex = pCallCtrlOutMapCtrl->dml.uInstanceNumber;
        snprintf(HalName, MAX_STR_LEN, DML_VOICESERVICE_CALLCONTROL_OUTGOINGMAP_PARAM_NAME, uVsIndex,uOutgoingMapIndex);


                if (TelcoVoiceMgrHal_DelParam(HalName) == ANSC_STATUS_SUCCESS)
                {
                        if(pOutmapList->pdata[uOutgoingMapIndex-1] != NULL)
                        {
                                AnscFreeMemory((ANSC_HANDLE) pOutmapList->pdata[uOutgoingMapIndex-1]);
                                pOutmapList->pdata[uOutgoingMapIndex-1]=NULL;
                                pOutmapList->ulQuantity--;
                        }
                }
    }
    TELCOVOICEMGR_UNLOCK()

   (void)deleteObject(HalName);

    return ret;
}


/**********************************************************************

    caller:     owner of this object

    prototype:

        BOOL TelcoVoiceMgrDml_CallControl_OutgoingMapList_GetParamUlongValue(ANSC_HANDLE hInsContext, char* ParamName, ULONG* puLong);

    description:

        This function is called to retrieve ULONG parameter value;

    argument:   ANSC_HANDLE                 hInsContext,
                The instance handle;

                char*                       ParamName,
                The parameter name;

                ULONG*                      puLong
                The buffer of returned ULONG value;

    return:     TRUE if succeeded.

**********************************************************************/

BOOL TelcoVoiceMgrDml_CallControl_OutgoingMapList_GetParamUlongValue(ANSC_HANDLE hInsContext, char* ParamName, ULONG* puLong)
{
    BOOL ret = FALSE;

    if(ParamName == NULL || puLong == NULL)
    {
        CcspTraceWarning(("%s: Invalid Input Parameter [NULL]\n", __func__));
        return ret;
    }

    TELCOVOICEMGR_LOCK_OR_EXIT()

    PDML_CALLCONTROL_OUTGOINGMAP_CTRL_T pCallCtrlOutMapCtrl = (PDML_CALLCONTROL_OUTGOINGMAP_CTRL_T)hInsContext;

    PDML_CALLCONTROL_OUTGOINGMAP pHEAD = &(pCallCtrlOutMapCtrl->dml);

    if (strcmp(ParamName, "Order") == 0)
    {
        *puLong = pHEAD->Order;
        ret = TRUE;
    }
    else
    {
        CcspTraceWarning(("%s: Unsupported parameter '%s'\n", __func__,ParamName));
    }

    TELCOVOICEMGR_UNLOCK()

    return ret;
}

/**********************************************************************

    caller:     owner of this object

    prototype:

        BOOL TelcoVoiceMgrDml_CallControl_OutgoingMapList_SetParamUlongValue(ANSC_HANDLE hInsContext, char* ParamName, ULONG uValue);

    description:

        This function is called to set ULONG parameter value;

    argument:   ANSC_HANDLE                 hInsContext,
                The instance handle;

                char*                       ParamName,
                The parameter name;

                ULONG                       uValue
                The updated ULONG value;

    return:     TRUE if succeeded.

**********************************************************************/

BOOL TelcoVoiceMgrDml_CallControl_OutgoingMapList_SetParamUlongValue(ANSC_HANDLE hInsContext, char* ParamName, ULONG uValue)
{
    BOOL ret = FALSE;
    ULONG uVsIndex  = 0;
    ULONG uOutMapIndex = 0;
    char HalName[MAX_STR_LEN] = {0};

    PTELCOVOICEMGR_DML_VOICESERVICE pDmlVoiceService = NULL;

    if(ParamName == NULL)
    {
        CcspTraceWarning(("%s: Invalid Input Parameter [NULL]\n", __func__));
        return ret;
    }

    TELCOVOICEMGR_LOCK_OR_EXIT()

    PDML_CALLCONTROL_OUTGOINGMAP_CTRL_T pCallCtrlOutMapCtrl = (PDML_CALLCONTROL_OUTGOINGMAP_CTRL_T)hInsContext;

    PDML_CALLCONTROL_OUTGOINGMAP pHEAD = &(pCallCtrlOutMapCtrl->dml);

    if(pHEAD != NULL)
    {
        pDmlVoiceService = (PTELCOVOICEMGR_DML_VOICESERVICE)pHEAD->pParentVoiceService;
    }

    if (pHEAD == NULL  || pDmlVoiceService == NULL)
    {
        TELCOVOICEMGR_UNLOCK()

        CcspTraceError(("%s:%d:: pHEAD or pDmlVoiceService NULL\n", __FUNCTION__, __LINE__));

        return ret;
    }

    uVsIndex = pDmlVoiceService->InstanceNumber;

    uOutMapIndex = pHEAD->uInstanceNumber;

    TELCOVOICEMGR_UNLOCK()

    if (strcmp(ParamName, "Order") == 0)
    {
        snprintf(HalName, MAX_STR_LEN, "Device.Services.VoiceService.%d.CallControl.OutgoingMap.%d.Order",uVsIndex,uOutMapIndex);

        if (TelcoVoiceMgrHal_SetParamULong(HalName,uValue) == ANSC_STATUS_SUCCESS)
        {
            TELCOVOICEMGR_LOCK_OR_EXIT()

            pHEAD->Order = uValue;

            TELCOVOICEMGR_UNLOCK()

            ret = TRUE;
        }
    }
    else
    {
        CcspTraceWarning(("%s: Unsupported parameter '%s'\n", __func__,ParamName));
    }

    return ret;
}

/**********************************************************************

    caller:     owner of this object

    prototype:

        ULONG TelcoVoiceMgrDml_CallControl_OutgoingMapList_GetParamStringValue(ANSC_HANDLE hInsContext, char* ParamName, char* pValue, ULONG* pulSize);

    description:

        This function is called to retrieve string parameter value;

    argument:   ANSC_HANDLE                 hInsContext,
                The instance handle;

                char*                       ParamName,
                The parameter name;

                char*                       pValue,
                The string value buffer;

                ULONG*                      pUlSize
                The buffer of length of string value;
                Usually size of 1023 will be used.
                If it's not big enough, put required size here and return 1;

    return:     0 if succeeded;
                1 if short of buffer size; (*pUlSize = required size)
                -1 if not supported.

**********************************************************************/

ULONG TelcoVoiceMgrDml_CallControl_OutgoingMapList_GetParamStringValue(ANSC_HANDLE hInsContext, char* ParamName, char* pValue, ULONG* pulSize)
{
    ULONG ret = 1;

    if(ParamName == NULL || pValue == NULL || pulSize == NULL)
    {
        CcspTraceWarning(("%s: Invalid Input Parameter [NULL]\n", __func__));
        return ret;
    }

    TELCOVOICEMGR_LOCK_OR_EXIT()

    PDML_CALLCONTROL_OUTGOINGMAP_CTRL_T pCallCtrlOutMapCtrl = (PDML_CALLCONTROL_OUTGOINGMAP_CTRL_T)hInsContext;

    PDML_CALLCONTROL_OUTGOINGMAP pHEAD = &(pCallCtrlOutMapCtrl->dml);

    if (strcmp(ParamName, "Line") == 0)
    {
        AnscCopyString(pValue,pHEAD->Line);
        ret = 0;
    }
    else if (strcmp(ParamName, "Extension") == 0)
    {
        AnscCopyString(pValue,pHEAD->Extension);
        ret = 0;
    }
    else if (strcmp(ParamName, "CLIPNoScreeningNumber") == 0)
    {
        AnscCopyString(pValue,pHEAD->CLIPNoScreeningNumber);
        ret = 0;
    }
    else if (strcmp(ParamName, "Alias") == 0)
    {
        AnscCopyString(pValue,pHEAD->Alias);
        ret = 0;
    }

    TELCOVOICEMGR_UNLOCK()

    return ret;
}

/**********************************************************************

    caller:     owner of this object

    prototype:

        BOOL TelcoVoiceMgrDml_CallControl_OutgoingMapList_SetParamStringValue(ANSC_HANDLE hInsContext, char* ParamName, char* pString);

    description:

        This function is called to set string parameter value;

    argument:   ANSC_HANDLE                 hInsContext,
                The instance handle;

                char*                       ParamName,
                The parameter name;

                char*                       pString
                The updated string value;

    return:     TRUE if succeeded.

**********************************************************************/

BOOL TelcoVoiceMgrDml_CallControl_OutgoingMapList_SetParamStringValue(ANSC_HANDLE hInsContext, char* ParamName, char* pString)
{
    BOOL ret = FALSE;
    ULONG uVsIndex  = 0;
    ULONG uOutMapIndex = 0;
    char HalName[MAX_STR_LEN] = {0};

    PTELCOVOICEMGR_DML_VOICESERVICE pDmlVoiceService = NULL;

    if(ParamName == NULL)
    {
        CcspTraceWarning(("%s: Invalid Input Parameter [NULL]\n", __func__));
        return ret;
    }

    TELCOVOICEMGR_LOCK_OR_EXIT()

    PDML_CALLCONTROL_OUTGOINGMAP_CTRL_T pCallCtrlOutMapCtrl = (PDML_CALLCONTROL_OUTGOINGMAP_CTRL_T)hInsContext;

    PDML_CALLCONTROL_OUTGOINGMAP pHEAD = &(pCallCtrlOutMapCtrl->dml);

    if(pHEAD != NULL)
    {
        pDmlVoiceService = (PTELCOVOICEMGR_DML_VOICESERVICE)pHEAD->pParentVoiceService;
    }

    if (pHEAD == NULL  || pDmlVoiceService == NULL)
    {
        TELCOVOICEMGR_UNLOCK()

        CcspTraceError(("%s:%d:: pHEAD or pDmlVoiceService NULL\n", __FUNCTION__, __LINE__));

        return ret;
    }

    uVsIndex = pDmlVoiceService->InstanceNumber;

    uOutMapIndex = pHEAD->uInstanceNumber;

    TELCOVOICEMGR_UNLOCK()

    if (strcmp(ParamName, "Line") == 0)
    {
        snprintf(HalName, MAX_STR_LEN, "Device.Services.VoiceService.%d.CallControl.OutgoingMap.%d.Line",uVsIndex,uOutMapIndex);

        if (TelcoVoiceMgrHal_SetParamString(HalName,pString) == ANSC_STATUS_SUCCESS)
        {
            TELCOVOICEMGR_LOCK_OR_EXIT()

            AnscCopyString(pHEAD->Line,pString);

            TELCOVOICEMGR_UNLOCK()

            ret = TRUE;
        }
    }
    else if (strcmp(ParamName, "Extension") == 0)
    {
        snprintf(HalName, MAX_STR_LEN, "Device.Services.VoiceService.%d.CallControl.OutgoingMap.%d.Extension",uVsIndex,uOutMapIndex);

        if (TelcoVoiceMgrHal_SetParamString(HalName,pString) == ANSC_STATUS_SUCCESS)
        {
            TELCOVOICEMGR_LOCK_OR_EXIT()

            AnscCopyString(pHEAD->Extension,pString);

            TELCOVOICEMGR_UNLOCK()

            ret = TRUE;
        }
    }
    else if (strcmp(ParamName, "CLIPNoScreeningNumber") == 0)
    {
        snprintf(HalName, MAX_STR_LEN, "Device.Services.VoiceService.%d.CallControl.OutgoingMap.%d.CLIPNoScreeningNumber",uVsIndex,uOutMapIndex);

        if (TelcoVoiceMgrHal_SetParamString(HalName,pString) == ANSC_STATUS_SUCCESS)
        {
            TELCOVOICEMGR_LOCK_OR_EXIT()

            AnscCopyString(pHEAD->CLIPNoScreeningNumber,pString);

            TELCOVOICEMGR_UNLOCK()

            ret = TRUE;
        }
    }
    else if (strcmp(ParamName, "Alias") == 0)
    {
        TELCOVOICEMGR_LOCK_OR_EXIT()

        AnscCopyString(pHEAD->Alias,pString);

        TELCOVOICEMGR_UNLOCK()

        ret = TRUE;
    }

    else
    {
        CcspTraceWarning(("%s: Unsupported parameter '%s'\n", __func__,ParamName));
    }

    return ret;
}

/**********************************************************************

    caller:     owner of this object

    prototype:

        BOOL TelcoVoiceMgrDml_CallControl_OutgoingMapList_GetParamBoolValue(ANSC_HANDLE hInsContext, char* ParamName, BOOL* pBool);

    description:

        This function is called to retrieve Boolean parameter value;

    argument:   ANSC_HANDLE                 hInsContext,
                The instance handle;

                char*                       ParamName,
                The parameter name;

                BOOL*                       pBool
                The buffer of returned boolean value;

    return:     TRUE if succeeded.

**********************************************************************/

BOOL TelcoVoiceMgrDml_CallControl_OutgoingMapList_GetParamBoolValue(ANSC_HANDLE hInsContext, char* ParamName, BOOL* pBool)
{
    BOOL ret = FALSE;

    if(ParamName == NULL || pBool == NULL)
    {
        CcspTraceWarning(("%s: Invalid Input Parameter [NULL]\n", __func__));
        return ret;
    }

    TELCOVOICEMGR_LOCK_OR_EXIT()

    PDML_CALLCONTROL_OUTGOINGMAP_CTRL_T pCallCtrlOutMapCtrl = (PDML_CALLCONTROL_OUTGOINGMAP_CTRL_T)hInsContext;

    PDML_CALLCONTROL_OUTGOINGMAP pHEAD = &(pCallCtrlOutMapCtrl->dml);

    if (strcmp(ParamName, "Enable") == 0)
    {
        *pBool = pHEAD->Enable;
        ret = TRUE;
    }
    else
    {
        CcspTraceWarning(("%s: Unsupported parameter '%s'\n", __func__,ParamName));
    }

    TELCOVOICEMGR_UNLOCK()

    return ret;
}

/**********************************************************************

    caller:     owner of this object

    prototype:

        BOOL TelcoVoiceMgrDml_CallControl_OutgoingMapList_SetParamBoolValue(ANSC_HANDLE hInsContext, char* ParamName, BOOL bValue);

    description:

        This function is called to set BOOL parameter value;

    argument:   ANSC_HANDLE                 hInsContext,
                The instance handle;

                char*                       ParamName,
                The parameter name;

                BOOL                        bValue
                The updated BOOL value;

    return:     TRUE if succeeded.

**********************************************************************/

BOOL TelcoVoiceMgrDml_CallControl_OutgoingMapList_SetParamBoolValue(ANSC_HANDLE hInsContext, char* ParamName, BOOL bValue)
{
    BOOL ret = FALSE;
    ULONG uVsIndex  = 0;
    ULONG uOutMapIndex = 0;
    char HalName[MAX_STR_LEN] = {0};

    PTELCOVOICEMGR_DML_VOICESERVICE pDmlVoiceService = NULL;

    if(ParamName == NULL)
    {
        CcspTraceWarning(("%s: Invalid Input Parameter [NULL]\n", __func__));
        return ret;
    }

    TELCOVOICEMGR_LOCK_OR_EXIT()

    PDML_CALLCONTROL_OUTGOINGMAP_CTRL_T pCallCtrlOutMapCtrl = (PDML_CALLCONTROL_OUTGOINGMAP_CTRL_T)hInsContext;

    PDML_CALLCONTROL_OUTGOINGMAP pHEAD = &(pCallCtrlOutMapCtrl->dml);

    if(pHEAD != NULL)
    {
        pDmlVoiceService = (PTELCOVOICEMGR_DML_VOICESERVICE)pHEAD->pParentVoiceService;
    }

    if (pHEAD == NULL  || pDmlVoiceService == NULL)
    {
        TELCOVOICEMGR_UNLOCK()

        CcspTraceError(("%s:%d:: pHEAD or pDmlVoiceService NULL\n", __FUNCTION__, __LINE__));

        return ret;
    }

    uVsIndex = pDmlVoiceService->InstanceNumber;

    uOutMapIndex = pHEAD->uInstanceNumber;

    TELCOVOICEMGR_UNLOCK()

    if (strcmp(ParamName, "Enable") == 0)
    {
        snprintf(HalName, MAX_STR_LEN, "Device.Services.VoiceService.%d.CallControl.OutgoingMap.%d.Enable",uVsIndex,uOutMapIndex);

        if (TelcoVoiceMgrHal_SetParamBool(HalName,bValue) == ANSC_STATUS_SUCCESS)
        {
            TELCOVOICEMGR_LOCK_OR_EXIT()

            pHEAD->Enable = bValue;

            TELCOVOICEMGR_UNLOCK()

            ret = TRUE;
        }
    }
    else
    {
        CcspTraceWarning(("%s: Unsupported parameter '%s'\n", __func__,ParamName));
    }

    return ret;
}

/**********************************************************************

    caller:     owner of this object

    prototype:

        BOOL TelcoVoiceMgrDml_CallControl_OutgoingMapList_Validate(ANSC_HANDLE hInsContext);

    description:

        This function is called to validate the update.

    argument:   ANSC_HANDLE                 hInsContext,
                The instance handle;

    return:     TRUE if there's no issue.

**********************************************************************/

BOOL TelcoVoiceMgrDml_CallControl_OutgoingMapList_Validate(ANSC_HANDLE hInsContext)
{
    return TRUE;
}

/**********************************************************************

    caller:     owner of this object

    prototype:

        BOOL TelcoVoiceMgrDml_CallControl_OutgoingMapList_Commit(ANSC_HANDLE hInsContext);

    description:

        This function is called to commit the update.

    argument:   ANSC_HANDLE                 hInsContext,
                The instance handle;

    return:     0 if there's no issue.

**********************************************************************/

BOOL TelcoVoiceMgrDml_CallControl_OutgoingMapList_Commit(ANSC_HANDLE hInsContext)
{
    return 0;
}

/**********************************************************************

    caller:     owner of this object

    prototype:

        BOOL TelcoVoiceMgrDml_CallControl_OutgoingMapList_Rollback(ANSC_HANDLE hInsContext);

    description:

        This function is called to rollback the update.

    argument:   ANSC_HANDLE                 hInsContext,
                The instance handle;

    return:     0 if there's no issue.

**********************************************************************/

BOOL TelcoVoiceMgrDml_CallControl_OutgoingMapList_Rollback(ANSC_HANDLE hInsContext)
{
    return 0;
}

/**********************************************************************

    caller:     owner of this object

    prototype:

        BOOL TelcoVoiceMgrDml_CallControl_NumberingPlanList_IsUpdated(ANSC_HANDLE hInsContext);

    description:

        This function is checking whether the table is updated or not.

    argument:   ANSC_HANDLE                 hInsContext,
                The instance handle;

    return:     TRUE or FALSE.

**********************************************************************/

BOOL TelcoVoiceMgrDml_CallControl_NumberingPlanList_IsUpdated(ANSC_HANDLE hInsContext)
{
    return TRUE;
}

/**********************************************************************

    caller:     owner of this object

    prototype:

        ULONG TelcoVoiceMgrDml_CallControl_NumberingPlanList_Synchronize(ANSC_HANDLE hInsContext);

    description:

        This function is called to synchronize the table.

    argument:   ANSC_HANDLE                 hInsContext,
                The instance handle;

    return:     The status of the operation.

**********************************************************************/

ULONG TelcoVoiceMgrDml_CallControl_NumberingPlanList_Synchronize(ANSC_HANDLE hInsContext)
{
    return 0;
}

/**********************************************************************

    caller:     owner of this object

    prototype:

        ULONG TelcoVoiceMgrDml_CallControl_NumberingPlanList_GetEntryCount(ANSC_HANDLE hInsContext);

    description:

        This function is called to retrieve the count of the table.

    argument:   ANSC_HANDLE                 hInsContext,
                The instance handle;

    return:     The count of the table

**********************************************************************/
ULONG TelcoVoiceMgrDml_CallControl_NumberingPlanList_GetEntryCount(ANSC_HANDLE hInsContext)
{
    ULONG ret = 0;

    TELCOVOICEMGR_LOCK_OR_EXIT()

    DML_VOICE_SERVICE_CTRL_T* pVoiceService = (DML_VOICE_SERVICE_CTRL_T*) hInsContext;

    PTELCOVOICEMGR_DML_VOICESERVICE pDmlVoiceService = &(pVoiceService->dml);

    PDML_CALLCONTROL_NUMBERINGPLAN_LIST_T pCallCtrlNumPlanList = &(pDmlVoiceService->CallControl_obj.NumberingPlan);

    if(pCallCtrlNumPlanList != NULL)
    {
        ret = pCallCtrlNumPlanList->ulQuantity;
    }

    TELCOVOICEMGR_UNLOCK()

    return ret;
}

/**********************************************************************

    caller:     owner of this object

    prototype:

        ANSC_HANDLE TelcoVoiceMgrDml_CallControl_NumberingPlanList_GetEntry(ANSC_HANDLE hInsContext, ULONG nIndex, ULONG* pInsNumber);

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
ANSC_HANDLE TelcoVoiceMgrDml_CallControl_NumberingPlanList_GetEntry(ANSC_HANDLE hInsContext, ULONG nIndex, ULONG* pInsNumber)
{

    ANSC_HANDLE ret = NULL;

    TELCOVOICEMGR_LOCK_OR_EXIT()

    PDML_VOICE_SERVICE_CTRL_T pVoiceService = (PDML_VOICE_SERVICE_CTRL_T) hInsContext;

    PTELCOVOICEMGR_DML_VOICESERVICE pDmlVoiceService = &(pVoiceService->dml);

    PDML_CALLCONTROL_NUMBERINGPLAN_LIST_T pNumPlanList = &(pDmlVoiceService->CallControl_obj.NumberingPlan);

    if(pNumPlanList != NULL)
    {
        if(nIndex < pNumPlanList->ulQuantity)
        {
            PDML_CALLCONTROL_NUMBERINGPLAN_CTRL_T pNumPlanCtrl = pNumPlanList->pdata[nIndex];
            if(pNumPlanCtrl != NULL)
            {
               *pInsNumber = nIndex + 1;
               ret = (ANSC_HANDLE) pNumPlanCtrl;
            }
        }
    }

    TELCOVOICEMGR_UNLOCK()

    return ret;
}

/********************************************************************

    caller:     owner of this object

    prototype:

        ANSC_HANDLE TelcoVoiceMgrDml_CallControl_NumberingPlanList_AddEntry(ANSC_HANDLE hInsContext, ULONG* pInsNumber);
    description:
       This function is called to add a new entry.

    argument:   ANSC_HANDLE                 hInsContext,+                The instance handle;
                ULONG*                      pInsNumber
                The output instance number;

    return:     The handle of new added entry.

*********************************************************************/
ANSC_HANDLE TelcoVoiceMgrDml_CallControl_NumberingPlanList_AddEntry(ANSC_HANDLE hInsContext, ULONG* pInsNumber)
{
    ANSC_HANDLE ret = NULL;

    TELCOVOICEMGR_LOCK_OR_EXIT()

    DML_VOICE_SERVICE_CTRL_T* pVoiceService = (DML_VOICE_SERVICE_CTRL_T*) hInsContext;

    PTELCOVOICEMGR_DML_VOICESERVICE pDmlVoiceService = &(pVoiceService->dml);

    PDML_CALLCONTROL_NUMBERINGPLAN_LIST_T pNumPlanList = &(pDmlVoiceService->CallControl_obj.NumberingPlan);

    if(pNumPlanList != NULL)
    {
        ret = TelcoVoiceMgrHal_AddCallCtrlNumberingPlan((ANSC_HANDLE)pDmlVoiceService,pInsNumber,(ANSC_HANDLE)pNumPlanList); // use to set alias/status/origin
        if( ret == NULL)
        {
                CcspTraceError(("%s:%d:: Add CallControl.NumberingPlan failed\n", __FUNCTION__, __LINE__));
        }
    }

    TELCOVOICEMGR_UNLOCK()

        return ret;
}

/*********************************************************************

    caller:     owner of this object

    prototype:

        ULONG TelcoVoiceMgrDml_CallControl_NumberingPlanList_DelEntry(ANSC_HANDLE hInsContext, ANSC_HANDLE hInstance);

    description:

        This function is called to delete an exist entry.

    argument:   ANSC_HANDLE                 hInsContext,
                The instance handle;

                ANSC_HANDLE                 hInstance
                The exist entry handle;

    return:     The status of the operation.

*********************************************************************/
ULONG TelcoVoiceMgrDml_CallControl_NumberingPlanList_DelEntry(ANSC_HANDLE hInsContext, ANSC_HANDLE hInstance)
{
    ANSC_STATUS ret = ANSC_STATUS_SUCCESS;
    ULONG uVsIndex  = 0;
    ULONG uNumPlanIndex = 0;
    char HalName[MAX_STR_LEN] = {0};

    TELCOVOICEMGR_LOCK_OR_EXIT()

    PDML_VOICE_SERVICE_CTRL_T pVoiceService = (PDML_VOICE_SERVICE_CTRL_T) hInsContext;

    PTELCOVOICEMGR_DML_VOICESERVICE pDmlVoiceService = &(pVoiceService->dml);

    PDML_CALLCONTROL_NUMBERINGPLAN_LIST_T pNumPlanList = &(pDmlVoiceService->CallControl_obj.NumberingPlan);

    PDML_CALLCONTROL_NUMBERINGPLAN_CTRL_T pCallCtrlNumPlanCtrl = (PDML_CALLCONTROL_NUMBERINGPLAN_CTRL_T) hInstance;

    if(pNumPlanList != NULL && pCallCtrlNumPlanCtrl!= NULL)
    {
        uVsIndex = pDmlVoiceService->InstanceNumber;
        uNumPlanIndex = pCallCtrlNumPlanCtrl->dml.uInstanceNumber;
        snprintf(HalName, MAX_STR_LEN, DML_VOICESERVICE_CALLCONTROL_NUMPLAN_PARAM_NAME, uVsIndex,uNumPlanIndex);


                if (TelcoVoiceMgrHal_DelParam(HalName) == ANSC_STATUS_SUCCESS)
                {
                        if(pNumPlanList->pdata[uNumPlanIndex-1] != NULL)
                        {
                                AnscFreeMemory((ANSC_HANDLE) pNumPlanList->pdata[uNumPlanIndex-1]);
                                pNumPlanList->pdata[uNumPlanIndex-1]=NULL;
                                pNumPlanList->ulQuantity--;
                        }
                }
    }
    TELCOVOICEMGR_UNLOCK()

   (void)deleteObject(HalName);

    return ret;
}

/**********************************************************************

    caller:     owner of this object

    prototype:

        BOOL TelcoVoiceMgrDml_CallControl_NumberingPlanList_GetParamUlongValue(ANSC_HANDLE hInsContext, char* ParamName, ULONG* puLong);

    description:

        This function is called to retrieve ULONG parameter value;

    argument:   ANSC_HANDLE                 hInsContext,
                The instance handle;

                char*                       ParamName,
                The parameter name;

                ULONG*                      puLong
                The buffer of returned ULONG value;

    return:     TRUE if succeeded.

**********************************************************************/

BOOL TelcoVoiceMgrDml_CallControl_NumberingPlanList_GetParamUlongValue(ANSC_HANDLE hInsContext, char* ParamName, ULONG* puLong)
{
    BOOL ret = FALSE;

    if(ParamName == NULL || puLong == NULL)
    {
        CcspTraceWarning(("%s: Invalid Input Parameter [NULL]\n", __func__));
        return ret;
    }

    TELCOVOICEMGR_LOCK_OR_EXIT()

    PDML_CALLCONTROL_NUMBERINGPLAN_CTRL_T pCallCtrlNumPlanCtrl = (PDML_CALLCONTROL_NUMBERINGPLAN_CTRL_T)hInsContext;

    PDML_CALLCONTROL_NUMBERINGPLAN pHEAD = &(pCallCtrlNumPlanCtrl->dml);

    if (strcmp(ParamName, "PrefixInfoMaxEntries") == 0)
    {
        *puLong = pHEAD->PrefixInfoMaxEntries;
        ret = TRUE;
    }
    else if (strcmp(ParamName, "MinimumNumberOfDigits") == 0)
    {
        *puLong = pHEAD->MinimumNumberOfDigits;
        ret = TRUE;
    }
    else if (strcmp(ParamName, "MaximumNumberOfDigits") == 0)
    {
        *puLong = pHEAD->MaximumNumberOfDigits;
        ret = TRUE;
    }
    else if (strcmp(ParamName, "InterDigitTimerStd") == 0)
    {
        *puLong = pHEAD->InterDigitTimerStd;
        ret = TRUE;
    }
    else if (strcmp(ParamName, "InterDigitTimerOpen") == 0)
    {
        *puLong = pHEAD->InterDigitTimerOpen;
        ret = TRUE;
    }
    else
    {
        CcspTraceWarning(("%s: Unsupported parameter '%s'\n", __func__,ParamName));
    }

    TELCOVOICEMGR_UNLOCK()

    return ret;
}

/**********************************************************************

    caller:     owner of this object

    prototype:

        BOOL TelcoVoiceMgrDml_CallControl_NumberingPlanList_SetParamUlongValue(ANSC_HANDLE hInsContext, char* ParamName, ULONG uValue);

    description:

        This function is called to set ULONG parameter value;

    argument:   ANSC_HANDLE                 hInsContext,
                The instance handle;

                char*                       ParamName,
                The parameter name;

                ULONG                       uValue
                The updated ULONG value;

    return:     TRUE if succeeded.

**********************************************************************/

BOOL TelcoVoiceMgrDml_CallControl_NumberingPlanList_SetParamUlongValue(ANSC_HANDLE hInsContext, char* ParamName, ULONG uValue)
{
    BOOL ret = FALSE;
    ULONG uVsIndex  = 0;
    ULONG uNumPlanIndex = 0;
    char HalName[MAX_STR_LEN] = {0};

    PTELCOVOICEMGR_DML_VOICESERVICE pDmlVoiceService = NULL;

    if(ParamName == NULL)
    {
        CcspTraceWarning(("%s: Invalid Input Parameter [NULL]\n", __func__));
        return ret;
    }

    TELCOVOICEMGR_LOCK_OR_EXIT()

    PDML_CALLCONTROL_NUMBERINGPLAN_CTRL_T pCallCtrlNumPlanCtrl = (PDML_CALLCONTROL_NUMBERINGPLAN_CTRL_T)hInsContext;

    PDML_CALLCONTROL_NUMBERINGPLAN pHEAD = &(pCallCtrlNumPlanCtrl->dml);

    if(pHEAD != NULL)
    {
        pDmlVoiceService = (PTELCOVOICEMGR_DML_VOICESERVICE)pHEAD->pParentVoiceService;
    }

    if (pHEAD == NULL  || pDmlVoiceService == NULL)
    {
        TELCOVOICEMGR_UNLOCK()

        CcspTraceError(("%s:%d:: pHEAD or pDmlVoiceService NULL\n", __FUNCTION__, __LINE__));

        return ret;
    }

    uVsIndex = pDmlVoiceService->InstanceNumber;

    uNumPlanIndex = pHEAD->uInstanceNumber;

    TELCOVOICEMGR_UNLOCK()

    if (strcmp(ParamName, "MinimumNumberOfDigits") == 0)
    {
        snprintf(HalName, MAX_STR_LEN, "Device.Services.VoiceService.%d.CallControl.NumberingPlan.%d.MinimumNumberOfDigits",uVsIndex,uNumPlanIndex);

        if (TelcoVoiceMgrHal_SetParamULong(HalName,uValue) == ANSC_STATUS_SUCCESS)
        {
            TELCOVOICEMGR_LOCK_OR_EXIT()

            pHEAD->MinimumNumberOfDigits = uValue;

            TELCOVOICEMGR_UNLOCK()

            ret = TRUE;
        }
    }
    else if (strcmp(ParamName, "MaximumNumberOfDigits") == 0)
    {
        snprintf(HalName, MAX_STR_LEN, "Device.Services.VoiceService.%d.CallControl.NumberingPlan.%d.MaximumNumberOfDigits",uVsIndex,uNumPlanIndex);

        if (TelcoVoiceMgrHal_SetParamULong(HalName,uValue) == ANSC_STATUS_SUCCESS)
        {
            TELCOVOICEMGR_LOCK_OR_EXIT()

            pHEAD->MaximumNumberOfDigits = uValue;

            TELCOVOICEMGR_UNLOCK()

            ret = TRUE;
        }
    }
    else if (strcmp(ParamName, "InterDigitTimerStd") == 0)
    {
        snprintf(HalName, MAX_STR_LEN, "Device.Services.VoiceService.%d.CallControl.NumberingPlan.%d.InterDigitTimerStd",uVsIndex,uNumPlanIndex);

        if (TelcoVoiceMgrHal_SetParamULong(HalName,uValue) == ANSC_STATUS_SUCCESS)
        {
            TELCOVOICEMGR_LOCK_OR_EXIT()

            pHEAD->InterDigitTimerStd = uValue;

            TELCOVOICEMGR_UNLOCK()

            ret = TRUE;
        }
    }
    else if (strcmp(ParamName, "InterDigitTimerOpen") == 0)
    {
        snprintf(HalName, MAX_STR_LEN, "Device.Services.VoiceService.%d.CallControl.NumberingPlan.%d.InterDigitTimerOpen",uVsIndex,uNumPlanIndex);

        if (TelcoVoiceMgrHal_SetParamULong(HalName,uValue) == ANSC_STATUS_SUCCESS)
        {
            TELCOVOICEMGR_LOCK_OR_EXIT()

            pHEAD->InterDigitTimerOpen = uValue;

            TELCOVOICEMGR_UNLOCK()

            ret = TRUE;
        }
    }
    else
    {
        CcspTraceWarning(("%s: Unsupported parameter '%s'\n", __func__,ParamName));
    }

    return ret;
}

/**********************************************************************

    caller:     owner of this object

    prototype:

        ULONG TelcoVoiceMgrDml_CallControl_NumberingPlanList_GetParamStringValue(ANSC_HANDLE hInsContext, char* ParamName, char* pValue, ULONG* pulSize);

    description:

        This function is called to retrieve string parameter value;

    argument:   ANSC_HANDLE                 hInsContext,
                The instance handle;

                char*                       ParamName,
                The parameter name;

                char*                       pValue,
                The string value buffer;

                ULONG*                      pUlSize
                The buffer of length of string value;
                Usually size of 1023 will be used.
                If it's not big enough, put required size here and return 1;

    return:     0 if succeeded;
                1 if short of buffer size; (*pUlSize = required size)
                -1 if not supported.

**********************************************************************/

ULONG TelcoVoiceMgrDml_CallControl_NumberingPlanList_GetParamStringValue(ANSC_HANDLE hInsContext, char* ParamName, char* pValue, ULONG* pulSize)
{
    ULONG ret = 1;

    if(ParamName == NULL || pValue == NULL || pulSize == NULL)
    {
        CcspTraceWarning(("%s: Invalid Input Parameter [NULL]\n", __func__));
        return ret;
    }

    TELCOVOICEMGR_LOCK_OR_EXIT()

    PDML_CALLCONTROL_NUMBERINGPLAN_CTRL_T pCallCtrlNumPlanCtrl = (PDML_CALLCONTROL_NUMBERINGPLAN_CTRL_T)hInsContext;

    PDML_CALLCONTROL_NUMBERINGPLAN pHEAD = &(pCallCtrlNumPlanCtrl->dml);

    if (strcmp(ParamName, "TerminationDigit") == 0)
    {
        AnscCopyString(pValue,pHEAD->TerminationDigit);
        ret = 0;
    }
    else if (strcmp(ParamName, "InvalidNumberTone") == 0)
    {
        AnscCopyString(pValue,pHEAD->InvalidNumberTone);
        ret = 0;
    }
    else if (strcmp(ParamName, "Alias") == 0)
    {
        AnscCopyString(pValue,pHEAD->Alias);
        ret = 0;
    }
    else
    {
        CcspTraceWarning(("%s: Unsupported parameter '%s'\n", __func__,ParamName));
    }

    TELCOVOICEMGR_UNLOCK()

    return ret;
}

/**********************************************************************

    caller:     owner of this object

    prototype:

        BOOL TelcoVoiceMgrDml_CallControl_NumberingPlanList_SetParamStringValue(ANSC_HANDLE hInsContext, char* ParamName, char* pString);

    description:

        This function is called to set string parameter value;

    argument:   ANSC_HANDLE                 hInsContext,
                The instance handle;

                char*                       ParamName,
                The parameter name;

                char*                       pString
                The updated string value;

    return:     TRUE if succeeded.

**********************************************************************/

BOOL TelcoVoiceMgrDml_CallControl_NumberingPlanList_SetParamStringValue(ANSC_HANDLE hInsContext, char* ParamName, char* pString)
{
    BOOL ret = FALSE;
    ULONG uVsIndex  = 0;
    ULONG uNumPlanIndex = 0;
    char HalName[MAX_STR_LEN] = {0};

    PTELCOVOICEMGR_DML_VOICESERVICE pDmlVoiceService = NULL;

    if(ParamName == NULL)
    {
        CcspTraceWarning(("%s: Invalid Input Parameter [NULL]\n", __func__));
        return ret;
    }

    TELCOVOICEMGR_LOCK_OR_EXIT()

    PDML_CALLCONTROL_NUMBERINGPLAN_CTRL_T pCallCtrlNumPlanCtrl = (PDML_CALLCONTROL_NUMBERINGPLAN_CTRL_T)hInsContext;

    PDML_CALLCONTROL_NUMBERINGPLAN pHEAD = &(pCallCtrlNumPlanCtrl->dml);

    if(pHEAD != NULL)
    {
        pDmlVoiceService = (PTELCOVOICEMGR_DML_VOICESERVICE)pHEAD->pParentVoiceService;
    }

    if (pHEAD == NULL  || pDmlVoiceService == NULL)
    {
        TELCOVOICEMGR_UNLOCK()

        CcspTraceError(("%s:%d:: pHEAD or pDmlVoiceService NULL\n", __FUNCTION__, __LINE__));

        return ret;
    }

    uVsIndex = pDmlVoiceService->InstanceNumber;

    uNumPlanIndex = pHEAD->uInstanceNumber;

    TELCOVOICEMGR_UNLOCK()

    if (strcmp(ParamName, "TerminationDigit") == 0)
    {
        snprintf(HalName, MAX_STR_LEN, "Device.Services.VoiceService.%d.CallControl.NumberingPlan.%d.TerminationDigit",uVsIndex,uNumPlanIndex);

        if (TelcoVoiceMgrHal_SetParamString(HalName,pString) == ANSC_STATUS_SUCCESS)
        {
            TELCOVOICEMGR_LOCK_OR_EXIT()

            AnscCopyString(pHEAD->TerminationDigit,pString);

            TELCOVOICEMGR_UNLOCK()

            ret = TRUE;
        }
    }
    else if (strcmp(ParamName, "InvalidNumberTone") == 0)
    {
        snprintf(HalName, MAX_STR_LEN, "Device.Services.VoiceService.%d.CallControl.NumberingPlan.%d.InvalidNumberTone",uVsIndex,uNumPlanIndex);

        if (TelcoVoiceMgrHal_SetParamString(HalName,pString) == ANSC_STATUS_SUCCESS)
        {
            TELCOVOICEMGR_LOCK_OR_EXIT()

            AnscCopyString(pHEAD->InvalidNumberTone,pString);

            TELCOVOICEMGR_UNLOCK()

            ret = TRUE;
        }
    }
    else if (strcmp(ParamName, "Alias") == 0)
    {
        TELCOVOICEMGR_LOCK_OR_EXIT()

        AnscCopyString(pHEAD->Alias,pString);

        TELCOVOICEMGR_UNLOCK()

        ret = TRUE;
    }
    else
    {
        CcspTraceWarning(("%s: Unsupported parameter '%s'\n", __func__,ParamName));
    }

    return ret;

}

/**********************************************************************

    caller:     owner of this object

    prototype:

        BOOL TelcoVoiceMgrDml_CallControl_NumberingPlanList_Validate(ANSC_HANDLE hInsContext);

    description:

        This function is called to validate the update.

    argument:   ANSC_HANDLE                 hInsContext,
                The instance handle;

    return:     TRUE if there's no issue.

**********************************************************************/

BOOL TelcoVoiceMgrDml_CallControl_NumberingPlanList_Validate(ANSC_HANDLE hInsContext)
{
    return TRUE;
}

/**********************************************************************

    caller:     owner of this object

    prototype:

        BOOL TelcoVoiceMgrDml_CallControl_NumberingPlanList_Commit(ANSC_HANDLE hInsContext);

    description:

        This function is called to commit the update.

    argument:   ANSC_HANDLE                 hInsContext,
                The instance handle;

    return:     0 if there's no issue.

**********************************************************************/

BOOL TelcoVoiceMgrDml_CallControl_NumberingPlanList_Commit(ANSC_HANDLE hInsContext)
{
    return 0;
}

/**********************************************************************

    caller:     owner of this object

    prototype:

        BOOL TelcoVoiceMgrDml_CallControl_NumberingPlanList_Rollback(ANSC_HANDLE hInsContext);

    description:

        This function is called to rollback the update.

    argument:   ANSC_HANDLE                 hInsContext,
                The instance handle;

    return:     0 if there's no issue.

**********************************************************************/

BOOL TelcoVoiceMgrDml_CallControl_NumberingPlanList_Rollback(ANSC_HANDLE hInsContext)
{
    return 0;
}

/**********************************************************************

    caller:     owner of this object

    prototype:

        BOOL TelcoVoiceMgrDml_CallControl_NumberingPlanList_PrefixInfoList_IsUpdated(ANSC_HANDLE hInsContext);

    description:

        This function is checking whether the table is updated or not.

    argument:   ANSC_HANDLE                 hInsContext,
                The instance handle;

    return:     TRUE or FALSE.

**********************************************************************/

BOOL TelcoVoiceMgrDml_CallControl_NumberingPlanList_PrefixInfoList_IsUpdated(ANSC_HANDLE hInsContext)
{
    return TRUE;
}

/**********************************************************************

    caller:     owner of this object

    prototype:

        ULONG TelcoVoiceMgrDml_CallControl_NumberingPlanList_PrefixInfoList_Synchronize(ANSC_HANDLE hInsContext);

    description:

        This function is called to synchronize the table.

    argument:   ANSC_HANDLE                 hInsContext,
                The instance handle;

    return:     The status of the operation.

**********************************************************************/

ULONG TelcoVoiceMgrDml_CallControl_NumberingPlanList_PrefixInfoList_Synchronize(ANSC_HANDLE hInsContext)
{
    return 0;
}

/**********************************************************************

    caller:     owner of this object

    prototype:

        ULONG TelcoVoiceMgrDml_CallControl_NumberingPlanList_PrefixInfoList_GetEntryCount(ANSC_HANDLE hInsContext);

    description:

        This function is called to retrieve the count of the table.

    argument:   ANSC_HANDLE                 hInsContext,
                The instance handle;

    return:     The count of the table

**********************************************************************/
ULONG TelcoVoiceMgrDml_CallControl_NumberingPlanList_PrefixInfoList_GetEntryCount(ANSC_HANDLE hInsContext)
{
    ULONG ret = 0;

    TELCOVOICEMGR_LOCK_OR_EXIT()

    DML_CALLCONTROL_NUMBERINGPLAN_CTRL_T* pCallCtrlNumPlanCtrl = (DML_CALLCONTROL_NUMBERINGPLAN_CTRL_T*) hInsContext;

    PDML_CALLCONTROL_NUMBERINGPLAN pDmlCallCtrlNumPlanCtrl = &(pCallCtrlNumPlanCtrl->dml);

    PDML_CALLCONTROL_NUMBERINGPLAN_PREFIXINFO_LIST_T pCallCtrlNumPlanPrefixInfoList = &(pDmlCallCtrlNumPlanCtrl->PrefixInfo);

    if(pCallCtrlNumPlanPrefixInfoList != NULL)
    {
        ret = pCallCtrlNumPlanPrefixInfoList->ulQuantity;
    }

    TELCOVOICEMGR_UNLOCK()

    return ret;
}

/**********************************************************************

    caller:     owner of this object

    prototype:

        ANSC_HANDLE TelcoVoiceMgrDml_CallControl_NumberingPlanList_PrefixInfoList_GetEntry(ANSC_HANDLE hInsContext, ULONG nIndex, ULONG* pInsNumber);

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
ANSC_HANDLE TelcoVoiceMgrDml_CallControl_NumberingPlanList_PrefixInfoList_GetEntry(ANSC_HANDLE hInsContext, ULONG nIndex, ULONG* pInsNumber)
{

    ANSC_HANDLE ret = NULL;

    TELCOVOICEMGR_LOCK_OR_EXIT()

    PDML_CALLCONTROL_NUMBERINGPLAN_CTRL_T pNumPlanCtrl = (PDML_CALLCONTROL_NUMBERINGPLAN_CTRL_T) hInsContext;

    PDML_CALLCONTROL_NUMBERINGPLAN pDmlNumPlan = &(pNumPlanCtrl->dml);

    PDML_CALLCONTROL_NUMBERINGPLAN_PREFIXINFO_LIST_T pPrefixInfoList = &(pDmlNumPlan->PrefixInfo);

    if(pPrefixInfoList != NULL)
    {
        if(nIndex < pPrefixInfoList->ulQuantity)
        {
            PDML_CALLCONTROL_NUMBERINGPLAN_PREFIXINFO_CTRL_T pPrefixInfoCtrl = pPrefixInfoList->pdata[nIndex];
            if(pPrefixInfoCtrl != NULL)
            {
               *pInsNumber = nIndex + 1;
               ret = (ANSC_HANDLE) pPrefixInfoCtrl;
            }
        }
    }

    TELCOVOICEMGR_UNLOCK()

    return ret;
}

/**********************************************************************

    caller:     owner of this object

    prototype:

        BOOL TelcoVoiceMgrDml_CallControl_NumberingPlanList_PrefixInfoList_GetParamUlongValue(ANSC_HANDLE hInsContext, char* ParamName, ULONG* puLong);

    description:

        This function is called to retrieve ULONG parameter value;

    argument:   ANSC_HANDLE                 hInsContext,
                The instance handle;

                char*                       ParamName,
                The parameter name;

                ULONG*                      puLong
                The buffer of returned ULONG value;

    return:     TRUE if succeeded.

**********************************************************************/

BOOL TelcoVoiceMgrDml_CallControl_NumberingPlanList_PrefixInfoList_GetParamUlongValue(ANSC_HANDLE hInsContext, char* ParamName, ULONG* puLong)
{
    BOOL ret = FALSE;

    if(ParamName == NULL || puLong == NULL)
    {
        CcspTraceWarning(("%s: Invalid Input Parameter [NULL]\n", __func__));
        return ret;
    }

    TELCOVOICEMGR_LOCK_OR_EXIT()

    PDML_CALLCONTROL_NUMBERINGPLAN_PREFIXINFO_CTRL_T pCallCtrlNUmPlanPreInfoCtrl = (PDML_CALLCONTROL_NUMBERINGPLAN_PREFIXINFO_CTRL_T)hInsContext;

    PDML_CALLCONTROL_NUMBERINGPLAN_PREFIXINFO pHEAD = &(pCallCtrlNUmPlanPreInfoCtrl->dml);

    if (strcmp(ParamName, "PrefixMinNumberOfDigits") == 0)
    {
        *puLong = pHEAD->PrefixMinNumberOfDigits;
        ret = TRUE;
    }
    else if (strcmp(ParamName, "PrefixMaxNumberOfDigits") == 0)
    {
        *puLong = pHEAD->PrefixMaxNumberOfDigits;
        ret = TRUE;
    }
    else if (strcmp(ParamName, "PosOfDigitsToRemove") == 0)
    {
        *puLong = pHEAD->PosOfDigitsToRemove;
        ret = TRUE;
    }
    else if (strcmp(ParamName, "NumberOfDigitsToRemove") == 0)
    {
        *puLong = pHEAD->NumberOfDigitsToRemove;
        ret = TRUE;
    }
    else
    {
        CcspTraceWarning(("%s: Unsupported parameter '%s'\n", __func__,ParamName));
    }

    TELCOVOICEMGR_UNLOCK()

    return ret;
}

/**********************************************************************

    caller:     owner of this object

    prototype:

        BOOL TelcoVoiceMgrDml_CallControl_NumberingPlanList_PrefixInfoList_SetParamUlongValue(ANSC_HANDLE hInsContext, char* ParamName, ULONG uValue);

    description:

        This function is called to set ULONG parameter value;

    argument:   ANSC_HANDLE                 hInsContext,
                The instance handle;

                char*                       ParamName,
                The parameter name;

                ULONG                       uValue
                The updated ULONG value;

    return:     TRUE if succeeded.

**********************************************************************/

BOOL TelcoVoiceMgrDml_CallControl_NumberingPlanList_PrefixInfoList_SetParamUlongValue(ANSC_HANDLE hInsContext, char* ParamName, ULONG uValue)
{
    BOOL ret = FALSE;
    ULONG uVsIndex  = 0;
    ULONG uNumPlanIndex = 0;
    ULONG uPrefixInfoIndex = 0;
    char HalName[MAX_STR_LEN] = {0};

    PTELCOVOICEMGR_DML_VOICESERVICE pDmlVoiceService = NULL;

    PDML_CALLCONTROL_NUMBERINGPLAN pDmlNumPlan = NULL;

    if(ParamName == NULL)
    {
        CcspTraceWarning(("%s: Invalid Input Parameter [NULL]\n", __func__));
        return ret;
    }

    TELCOVOICEMGR_LOCK_OR_EXIT()

    PDML_CALLCONTROL_NUMBERINGPLAN_PREFIXINFO_CTRL_T pCallCtrlNUmPlanPreInfoCtrl = (PDML_CALLCONTROL_NUMBERINGPLAN_PREFIXINFO_CTRL_T)hInsContext;

    PDML_CALLCONTROL_NUMBERINGPLAN_PREFIXINFO pHEAD = &(pCallCtrlNUmPlanPreInfoCtrl->dml);

    if(pHEAD != NULL)
    {
        pDmlNumPlan = (PDML_CALLCONTROL_NUMBERINGPLAN)pHEAD->pParentCallCtrlNumPlan;
    }

    if(pDmlNumPlan != NULL)
    {
        pDmlVoiceService = (PTELCOVOICEMGR_DML_VOICESERVICE)pDmlNumPlan->pParentVoiceService;
    }

    if (pHEAD == NULL  || pDmlNumPlan == NULL || pDmlVoiceService == NULL)
    {
        TELCOVOICEMGR_UNLOCK()

        CcspTraceError(("%s:%d:: pHEAD or pDmlNumPlan or pDmlVoiceService NULL\n", __FUNCTION__, __LINE__));

        return ret;
    }

    uVsIndex = pDmlVoiceService->InstanceNumber;

    uNumPlanIndex = pDmlNumPlan->uInstanceNumber;

    uPrefixInfoIndex = pHEAD->uInstanceNumber;

    TELCOVOICEMGR_UNLOCK()

    if (strcmp(ParamName, "PrefixMinNumberOfDigits") == 0)
    {
        snprintf(HalName, MAX_STR_LEN, "Device.Services.VoiceService.%d.CallControl.NumberingPlan.%d.PrefixInfo.%d.PrefixMinNumberOfDigits",uVsIndex,uNumPlanIndex,uPrefixInfoIndex);

        if (TelcoVoiceMgrHal_SetParamULong(HalName,uValue) == ANSC_STATUS_SUCCESS)
        {
            TELCOVOICEMGR_LOCK_OR_EXIT()

            pHEAD->PrefixMinNumberOfDigits = uValue;

            TELCOVOICEMGR_UNLOCK()

            ret = TRUE;
        }
    }
    else if (strcmp(ParamName, "PrefixMaxNumberOfDigits") == 0)
    {
        snprintf(HalName, MAX_STR_LEN, "Device.Services.VoiceService.%d.CallControl.NumberingPlan.%d.PrefixInfo.%d.PrefixMaxNumberOfDigits",uVsIndex,uNumPlanIndex,uPrefixInfoIndex);

        if (TelcoVoiceMgrHal_SetParamULong(HalName,uValue) == ANSC_STATUS_SUCCESS)
        {
            TELCOVOICEMGR_LOCK_OR_EXIT()

            pHEAD->PrefixMaxNumberOfDigits = uValue;

            TELCOVOICEMGR_UNLOCK()

            ret = TRUE;
        }
    }
    else if (strcmp(ParamName, "PosOfDigitsToRemove") == 0)
    {
        snprintf(HalName, MAX_STR_LEN, "Device.Services.VoiceService.%d.CallControl.NumberingPlan.%d.PrefixInfo.%d.PosOfDigitsToRemove",uVsIndex,uNumPlanIndex,uPrefixInfoIndex);

        if (TelcoVoiceMgrHal_SetParamULong(HalName,uValue) == ANSC_STATUS_SUCCESS)
        {
            TELCOVOICEMGR_LOCK_OR_EXIT()

            pHEAD->PosOfDigitsToRemove = uValue;

            TELCOVOICEMGR_UNLOCK()

            ret = TRUE;
        }
    }
    else if (strcmp(ParamName, "NumberOfDigitsToRemove") == 0)
    {
        snprintf(HalName, MAX_STR_LEN, "Device.Services.VoiceService.%d.CallControl.NumberingPlan.%d.PrefixInfo.%d.NumberOfDigitsToRemove",uVsIndex,uNumPlanIndex,uPrefixInfoIndex);

        if (TelcoVoiceMgrHal_SetParamULong(HalName,uValue) == ANSC_STATUS_SUCCESS)
        {
            TELCOVOICEMGR_LOCK_OR_EXIT()

            pHEAD->NumberOfDigitsToRemove = uValue;

            TELCOVOICEMGR_UNLOCK()

            ret = TRUE;
        }
    }
    else
    {
        CcspTraceWarning(("%s: Unsupported parameter '%s'\n", __func__,ParamName));
    }

    return ret;
}

/**********************************************************************

    caller:     owner of this object

    prototype:

        ULONG TelcoVoiceMgrDml_CallControl_NumberingPlanList_PrefixInfoList_GetParamStringValue(ANSC_HANDLE hInsContext, char* ParamName, char* pValue, ULONG* pulSize);

    description:

        This function is called to retrieve string parameter value;

    argument:   ANSC_HANDLE                 hInsContext,
                The instance handle;

                char*                       ParamName,
                The parameter name;

                char*                       pValue,
                The string value buffer;

                ULONG*                      pUlSize
                The buffer of length of string value;
                Usually size of 1023 will be used.
                If it's not big enough, put required size here and return 1;

    return:     0 if succeeded;
                1 if short of buffer size; (*pUlSize = required size)
                -1 if not supported.

**********************************************************************/

ULONG TelcoVoiceMgrDml_CallControl_NumberingPlanList_PrefixInfoList_GetParamStringValue(ANSC_HANDLE hInsContext, char* ParamName, char* pValue, ULONG* pulSize)
{
    ULONG ret = 1;

    if(ParamName == NULL || pValue == NULL || pulSize == NULL)
    {
        CcspTraceWarning(("%s: Invalid Input Parameter [NULL]\n", __func__));
        return ret;
    }

    TELCOVOICEMGR_LOCK_OR_EXIT()

    PDML_CALLCONTROL_NUMBERINGPLAN_PREFIXINFO_CTRL_T pCallCtrlNUmPlanPreInfoCtrl = (PDML_CALLCONTROL_NUMBERINGPLAN_PREFIXINFO_CTRL_T)hInsContext;

    PDML_CALLCONTROL_NUMBERINGPLAN_PREFIXINFO pHEAD = &(pCallCtrlNUmPlanPreInfoCtrl->dml);

    if (strcmp(ParamName, "PrefixRange") == 0)
    {
        AnscCopyString(pValue,pHEAD->PrefixRange);
        ret = 0;
    }
    else if (strcmp(ParamName, "FacilityActionArgument") == 0)
    {
        AnscCopyString(pValue,pHEAD->FacilityActionArgument);
        ret = 0;
    }
    else if (strcmp(ParamName, "FacilityAction") == 0)
    {
        AnscCopyString(pValue,pHEAD->FacilityAction);
        ret = 0;
    }
    else if (strcmp(ParamName, "DialTone") == 0)
    {
        AnscCopyString(pValue,pHEAD->DialTone);
        ret = 0;
    }
    else if (strcmp(ParamName, "Alias") == 0)
    {
        AnscCopyString(pValue,pHEAD->Alias);
        ret = 0;
    }
    else
    {
        CcspTraceWarning(("%s: Unsupported parameter '%s'\n", __func__,ParamName));
    }

    TELCOVOICEMGR_UNLOCK()

    return ret;
}

/**********************************************************************

    caller:     owner of this object

    prototype:

        BOOL TelcoVoiceMgrDml_CallControl_NumberingPlanList_PrefixInfoList_SetParamStringValue(ANSC_HANDLE hInsContext, char* ParamName, char* pString);

    description:

        This function is called to set string parameter value;

    argument:   ANSC_HANDLE                 hInsContext,
                The instance handle;

                char*                       ParamName,
                The parameter name;

                char*                       pString
                The updated string value;

    return:     TRUE if succeeded.

**********************************************************************/

BOOL TelcoVoiceMgrDml_CallControl_NumberingPlanList_PrefixInfoList_SetParamStringValue(ANSC_HANDLE hInsContext, char* ParamName, char* pString)
{
    BOOL ret = FALSE;
    ULONG uVsIndex  = 0;
    ULONG uNumPlanIndex = 0;
    ULONG uPrefixInfoIndex = 0;
    char HalName[MAX_STR_LEN] = {0};

    PTELCOVOICEMGR_DML_VOICESERVICE pDmlVoiceService = NULL;

    PDML_CALLCONTROL_NUMBERINGPLAN pDmlNumPlan = NULL;

    if(ParamName == NULL)
    {
        CcspTraceWarning(("%s: Invalid Input Parameter [NULL]\n", __func__));
        return ret;
    }

    TELCOVOICEMGR_LOCK_OR_EXIT()

    PDML_CALLCONTROL_NUMBERINGPLAN_PREFIXINFO_CTRL_T pCallCtrlNUmPlanPreInfoCtrl = (PDML_CALLCONTROL_NUMBERINGPLAN_PREFIXINFO_CTRL_T)hInsContext;

    PDML_CALLCONTROL_NUMBERINGPLAN_PREFIXINFO pHEAD = &(pCallCtrlNUmPlanPreInfoCtrl->dml);

    if(pHEAD != NULL)
    {
        pDmlNumPlan = (PDML_CALLCONTROL_NUMBERINGPLAN)pHEAD->pParentCallCtrlNumPlan;
    }

    if(pDmlNumPlan != NULL)
    {
        pDmlVoiceService = (PTELCOVOICEMGR_DML_VOICESERVICE)pDmlNumPlan->pParentVoiceService;
    }

    if (pHEAD == NULL  || pDmlNumPlan == NULL || pDmlVoiceService == NULL)
    {
        TELCOVOICEMGR_UNLOCK()

        CcspTraceError(("%s:%d:: pHEAD or pDmlNumPlan or pDmlVoiceService NULL\n", __FUNCTION__, __LINE__));

        return ret;
    }

    uVsIndex = pDmlVoiceService->InstanceNumber;

    uNumPlanIndex = pDmlNumPlan->uInstanceNumber;

    uPrefixInfoIndex = pHEAD->uInstanceNumber;

    TELCOVOICEMGR_UNLOCK()

    if (strcmp(ParamName, "PrefixRange") == 0)
    {
        snprintf(HalName, MAX_STR_LEN, "Device.Services.VoiceService.%d.CallControl.NumberingPlan.%d.PrefixInfo.%d.PrefixRange",uVsIndex,uNumPlanIndex,uPrefixInfoIndex);

        if (TelcoVoiceMgrHal_SetParamString(HalName,pString) == ANSC_STATUS_SUCCESS)
        {
            TELCOVOICEMGR_LOCK_OR_EXIT()

            AnscCopyString(pHEAD->PrefixRange,pString);

            TELCOVOICEMGR_UNLOCK()

            ret = TRUE;
        }
    }
    else if (strcmp(ParamName, "FacilityActionArgument") == 0)
    {
        snprintf(HalName, MAX_STR_LEN, "Device.Services.VoiceService.%d.CallControl.NumberingPlan.%d.PrefixInfo.%d.FacilityActionArgument",uVsIndex,uNumPlanIndex,uPrefixInfoIndex);

        if (TelcoVoiceMgrHal_SetParamString(HalName,pString) == ANSC_STATUS_SUCCESS)
        {
            TELCOVOICEMGR_LOCK_OR_EXIT()

            AnscCopyString(pHEAD->FacilityActionArgument,pString);

            TELCOVOICEMGR_UNLOCK()

            ret = TRUE;
        }
    }
    else if (strcmp(ParamName, "FacilityAction") == 0)
    {
        snprintf(HalName, MAX_STR_LEN, "Device.Services.VoiceService.%d.CallControl.NumberingPlan.%d.PrefixInfo.%d.FacilityAction",uVsIndex,uNumPlanIndex,uPrefixInfoIndex);

        if (TelcoVoiceMgrHal_SetParamString(HalName,pString) == ANSC_STATUS_SUCCESS)
        {
            TELCOVOICEMGR_LOCK_OR_EXIT()

            AnscCopyString(pHEAD->FacilityAction,pString);

            TELCOVOICEMGR_UNLOCK()

            ret = TRUE;
        }
    }
    else if (strcmp(ParamName, "DialTone") == 0)
    {
        snprintf(HalName, MAX_STR_LEN, "Device.Services.VoiceService.%d.CallControl.NumberingPlan.%d.PrefixInfo.%d.DialTone",uVsIndex,uNumPlanIndex,uPrefixInfoIndex);

        if (TelcoVoiceMgrHal_SetParamString(HalName,pString) == ANSC_STATUS_SUCCESS)
        {
            TELCOVOICEMGR_LOCK_OR_EXIT()

            AnscCopyString(pHEAD->DialTone,pString);

            TELCOVOICEMGR_UNLOCK()

            ret = TRUE;
        }
    }
    else if (strcmp(ParamName, "Alias") == 0)
    {
        TELCOVOICEMGR_LOCK_OR_EXIT()

        AnscCopyString(pHEAD->Alias,pString);

        TELCOVOICEMGR_UNLOCK()

        ret = TRUE;
    }
    else
    {
        CcspTraceWarning(("%s: Unsupported parameter '%s'\n", __func__,ParamName));
    }

    return ret;

}

/**********************************************************************

    caller:     owner of this object

    prototype:

        BOOL TelcoVoiceMgrDml_CallControl_NumberingPlanList_PrefixInfoList_GetParamBoolValue(ANSC_HANDLE hInsContext, char* ParamName, BOOL* pBool);

    description:

        This function is called to retrieve Boolean parameter value;

    argument:   ANSC_HANDLE                 hInsContext,
                The instance handle;

                char*                       ParamName,
                The parameter name;

                BOOL*                       pBool
                The buffer of returned boolean value;

    return:     TRUE if succeeded.

**********************************************************************/

BOOL TelcoVoiceMgrDml_CallControl_NumberingPlanList_PrefixInfoList_GetParamBoolValue(ANSC_HANDLE hInsContext, char* ParamName, BOOL* pBool)
{
    BOOL ret = FALSE;

    if(ParamName == NULL || pBool == NULL)
    {
        CcspTraceWarning(("%s: Invalid Input Parameter [NULL]\n", __func__));
        return ret;
    }

    TELCOVOICEMGR_LOCK_OR_EXIT()

    PDML_CALLCONTROL_NUMBERINGPLAN_PREFIXINFO_CTRL_T pCallCtrlNUmPlanPreInfoCtrl = (PDML_CALLCONTROL_NUMBERINGPLAN_PREFIXINFO_CTRL_T)hInsContext;

    PDML_CALLCONTROL_NUMBERINGPLAN_PREFIXINFO pHEAD = &(pCallCtrlNUmPlanPreInfoCtrl->dml);

    if (strcmp(ParamName, "Enable") == 0)
    {
        *pBool = pHEAD->Enable;
        ret = TRUE;
    }
    else
    {
        CcspTraceWarning(("%s: Unsupported parameter '%s'\n", __func__,ParamName));
    }

    TELCOVOICEMGR_UNLOCK()

    return ret;
}

/**********************************************************************

    caller:     owner of this object

    prototype:

        BOOL TelcoVoiceMgrDml_CallControl_NumberingPlanList_PrefixInfoList_SetParamBoolValue(ANSC_HANDLE hInsContext, char* ParamName, BOOL bValue);

    description:

        This function is called to set BOOL parameter value;

    argument:   ANSC_HANDLE                 hInsContext,
                The instance handle;

                char*                       ParamName,
                The parameter name;

                BOOL                        bValue
                The updated BOOL value;

    return:     TRUE if succeeded.

**********************************************************************/

BOOL TelcoVoiceMgrDml_CallControl_NumberingPlanList_PrefixInfoList_SetParamBoolValue(ANSC_HANDLE hInsContext, char* ParamName, BOOL bValue)
{
    BOOL ret = FALSE;
    ULONG uVsIndex  = 0;
    ULONG uNumPlanIndex = 0;
    ULONG uPrefixInfoIndex = 0;
    char HalName[MAX_STR_LEN] = {0};

    PTELCOVOICEMGR_DML_VOICESERVICE pDmlVoiceService = NULL;

    PDML_CALLCONTROL_NUMBERINGPLAN pDmlNumPlan = NULL;

    if(ParamName == NULL)
    {
        CcspTraceWarning(("%s: Invalid Input Parameter [NULL]\n", __func__));
        return ret;
    }

    TELCOVOICEMGR_LOCK_OR_EXIT()

    PDML_CALLCONTROL_NUMBERINGPLAN_PREFIXINFO_CTRL_T pCallCtrlNUmPlanPreInfoCtrl = (PDML_CALLCONTROL_NUMBERINGPLAN_PREFIXINFO_CTRL_T)hInsContext;

    PDML_CALLCONTROL_NUMBERINGPLAN_PREFIXINFO pHEAD = &(pCallCtrlNUmPlanPreInfoCtrl->dml);

    if(pHEAD != NULL)
    {
        pDmlNumPlan = (PDML_CALLCONTROL_NUMBERINGPLAN)pHEAD->pParentCallCtrlNumPlan;
    }

    if(pDmlNumPlan != NULL)
    {
        pDmlVoiceService = (PTELCOVOICEMGR_DML_VOICESERVICE)pDmlNumPlan->pParentVoiceService;
    }

    if (pHEAD == NULL  || pDmlNumPlan == NULL || pDmlVoiceService == NULL)
    {
        TELCOVOICEMGR_UNLOCK()

        CcspTraceError(("%s:%d:: pHEAD or pDmlNumPlan or pDmlVoiceService NULL\n", __FUNCTION__, __LINE__));

        return ret;
    }

    uVsIndex = pDmlVoiceService->InstanceNumber;

    uNumPlanIndex = pDmlNumPlan->uInstanceNumber;

    uPrefixInfoIndex = pHEAD->uInstanceNumber;

    TELCOVOICEMGR_UNLOCK()

    if (strcmp(ParamName, "Enable") == 0)
    {
        snprintf(HalName, MAX_STR_LEN, "Device.Services.VoiceService.%d.CallControl.NumberingPlan.%d.PrefixInfo.%d.Enable",uVsIndex,uNumPlanIndex,uPrefixInfoIndex);

        if (TelcoVoiceMgrHal_SetParamBool(HalName,bValue) == ANSC_STATUS_SUCCESS)
        {
            TELCOVOICEMGR_LOCK_OR_EXIT()

            pHEAD->Enable = bValue;

            TELCOVOICEMGR_UNLOCK()

            ret = TRUE;
        }
    }
    else
    {
        CcspTraceWarning(("%s: Unsupported parameter '%s'\n", __func__,ParamName));
    }

    return ret;
}

/**********************************************************************

    caller:     owner of this object

    prototype:

        BOOL TelcoVoiceMgrDml_CallControl_NumberingPlanList_PrefixInfoList_Validate(ANSC_HANDLE hInsContext);

    description:

        This function is called to validate the update.

    argument:   ANSC_HANDLE                 hInsContext,
                The instance handle;

    return:     TRUE if there's no issue.

**********************************************************************/

BOOL TelcoVoiceMgrDml_CallControl_NumberingPlanList_PrefixInfoList_Validate(ANSC_HANDLE hInsContext)
{
    return TRUE;
}

/**********************************************************************

    caller:     owner of this object

    prototype:

        BOOL TelcoVoiceMgrDml_CallControl_NumberingPlanList_PrefixInfoList_Commit(ANSC_HANDLE hInsContext);

    description:

        This function is called to commit the update.

    argument:   ANSC_HANDLE                 hInsContext,
                The instance handle;

    return:     0 if there's no issue.

**********************************************************************/

BOOL TelcoVoiceMgrDml_CallControl_NumberingPlanList_PrefixInfoList_Commit(ANSC_HANDLE hInsContext)
{
    return 0;
}

/**********************************************************************

    caller:     owner of this object

    prototype:

        BOOL TelcoVoiceMgrDml_CallControl_NumberingPlanList_PrefixInfoList_Rollback(ANSC_HANDLE hInsContext);

    description:

        This function is called to rollback the update.

    argument:   ANSC_HANDLE                 hInsContext,
                The instance handle;

    return:     0 if there's no issue.

**********************************************************************/

BOOL TelcoVoiceMgrDml_CallControl_NumberingPlanList_PrefixInfoList_Rollback(ANSC_HANDLE hInsContext)
{
    return 0;
}

/**********************************************************************

    caller:     owner of this object

    prototype:

        BOOL TelcoVoiceMgrDml_CallControl_CallingFeatures_SetList_IsUpdated(ANSC_HANDLE hInsContext);

    description:

        This function is checking whether the table is updated or not.

    argument:   ANSC_HANDLE                 hInsContext,
                The instance handle;

    return:     TRUE or FALSE.

**********************************************************************/

BOOL TelcoVoiceMgrDml_CallControl_CallingFeatures_SetList_IsUpdated(ANSC_HANDLE hInsContext)
{
    return TRUE;
}

/**********************************************************************

    caller:     owner of this object

    prototype:

        ULONG TelcoVoiceMgrDml_CallControl_CallingFeatures_SetList_Synchronize(ANSC_HANDLE hInsContext);

    description:

        This function is called to synchronize the table.

    argument:   ANSC_HANDLE                 hInsContext,
                The instance handle;

    return:     The status of the operation.

**********************************************************************/

ULONG TelcoVoiceMgrDml_CallControl_CallingFeatures_SetList_Synchronize(ANSC_HANDLE hInsContext)
{
    return 0;
}

/**********************************************************************

    caller:     owner of this object

    prototype:

        ULONG TelcoVoiceMgrDml_CallControl_CallingFeatures_SetList_GetEntryCount(ANSC_HANDLE hInsContext);

    description:

        This function is called to retrieve the count of the table.

    argument:   ANSC_HANDLE                 hInsContext,
                The instance handle;

    return:     The count of the table

**********************************************************************/
ULONG TelcoVoiceMgrDml_CallControl_CallingFeatures_SetList_GetEntryCount(ANSC_HANDLE hInsContext)
{
    ULONG ret = 0;

    TELCOVOICEMGR_LOCK_OR_EXIT()

    DML_VOICE_SERVICE_CTRL_T* pVoiceService = (DML_VOICE_SERVICE_CTRL_T*) hInsContext;

    PTELCOVOICEMGR_DML_VOICESERVICE pDmlVoiceService = &(pVoiceService->dml);

    PDML_CALLCONTROL_CALLINGFEATURES_SET_LIST_T pCallFeaturesSetList = &(pDmlVoiceService->CallControl_obj.CallingFeatures.Set);

    if(pCallFeaturesSetList != NULL)
    {
        ret = pCallFeaturesSetList->ulQuantity;
    }
    TELCOVOICEMGR_UNLOCK()

    return ret;
}

/**********************************************************************

    caller:     owner of this object

    prototype:

        ANSC_HANDLE TelcoVoiceMgrDml_CallControl_CallingFeatures_SetList_GetEntry(ANSC_HANDLE hInsContext, ULONG nIndex, ULONG* pInsNumber);

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
ANSC_HANDLE TelcoVoiceMgrDml_CallControl_CallingFeatures_SetList_GetEntry(ANSC_HANDLE hInsContext, ULONG nIndex, ULONG* pInsNumber)
{
    ANSC_HANDLE ret = NULL;

    TELCOVOICEMGR_LOCK_OR_EXIT()

    DML_VOICE_SERVICE_CTRL_T* pVoiceService = (DML_VOICE_SERVICE_CTRL_T*) hInsContext;

    PTELCOVOICEMGR_DML_VOICESERVICE pDmlVoiceService = &(pVoiceService->dml);

    PDML_CALLCONTROL_CALLINGFEATURES_SET_LIST_T pCallFeaturesSetList = &(pDmlVoiceService->CallControl_obj.CallingFeatures.Set);

    if(pCallFeaturesSetList != NULL)
    {
        if(nIndex < pCallFeaturesSetList->ulQuantity)
        {
            PDML_CALLCONTROL_CALLINGFEATURES_SET_CTRL_T pCallFeaturesSetCtrl = pCallFeaturesSetList->pdata[nIndex];
            if(pCallFeaturesSetCtrl != NULL)
            {
               *pInsNumber = nIndex + 1;
               ret = (ANSC_HANDLE) pCallFeaturesSetCtrl;
            }
        }
    }

    TELCOVOICEMGR_UNLOCK()

    return ret;
}

/**********************************************************************

    caller:     owner of this object

    prototype:

        BOOL TelcoVoiceMgrDml_CallControl_CallingFeatures_SetList_GetParamUlongValue(ANSC_HANDLE hInsContext, char* ParamName, ULONG* puLong);

    description:

        This function is called to retrieve ULONG parameter value;

    argument:   ANSC_HANDLE                 hInsContext,
                The instance handle;

                char*                       ParamName,
                The parameter name;

                ULONG*                      puLong
                The buffer of returned ULONG value;

    return:     TRUE if succeeded.

**********************************************************************/

BOOL TelcoVoiceMgrDml_CallControl_CallingFeatures_SetList_GetParamUlongValue(ANSC_HANDLE hInsContext, char* ParamName, ULONG* puLong)
{
    BOOL ret = FALSE;

    if(ParamName == NULL || puLong == NULL)
    {
        CcspTraceWarning(("%s: Invalid Input Parameter [NULL]\n", __func__));
        return ret;
    }

    TELCOVOICEMGR_LOCK_OR_EXIT()

    PDML_CALLCONTROL_CALLINGFEATURES_SET_CTRL_T pCallFeaturesSetCtrl = (PDML_CALLCONTROL_CALLINGFEATURES_SET_CTRL_T)hInsContext;

    PDML_CALLCONTROL_CALLINGFEATURES_SET pHEAD = &(pCallFeaturesSetCtrl->dml);

    if (strcmp(ParamName, "LineMessagesWaiting") == 0)
    {
        *puLong = pHEAD->LineMessagesWaiting;
        ret = TRUE;
    }
    else if (strcmp(ParamName, "CallForwardOnNoAnswerRingTimeout") == 0)
    {
        *puLong = pHEAD->CallForwardOnNoAnswerRingTimeout;
        ret = TRUE;
    }
    else if (strcmp(ParamName, "CallForwardOnBusyRingTimeout") == 0)
    {
        *puLong = pHEAD->CallForwardOnBusyRingTimeout;
        ret = TRUE;
    }
    else
    {
        CcspTraceWarning(("%s: Unsupported parameter '%s'\n", __func__,ParamName));
    }

    TELCOVOICEMGR_UNLOCK()

    return ret;
}

/**********************************************************************

    caller:     owner of this object

    prototype:

        BOOL TelcoVoiceMgrDml_CallControl_CallingFeatures_SetList_SetParamUlongValue(ANSC_HANDLE hInsContext, char* ParamName, ULONG uValue);

    description:

        This function is called to set ULONG parameter value;

    argument:   ANSC_HANDLE                 hInsContext,
                The instance handle;

                char*                       ParamName,
                The parameter name;

                ULONG                       uValue
                The updated ULONG value;

    return:     TRUE if succeeded.

**********************************************************************/

BOOL TelcoVoiceMgrDml_CallControl_CallingFeatures_SetList_SetParamUlongValue(ANSC_HANDLE hInsContext, char* ParamName, ULONG uValue)
{
    BOOL ret = FALSE;
    ULONG uVsIndex  = 0;
    ULONG uSetIndex = 0;
    char HalName[MAX_STR_LEN] = {0};

    PTELCOVOICEMGR_DML_VOICESERVICE pDmlVoiceService = NULL;

    if(ParamName == NULL)
    {
        CcspTraceWarning(("%s: Invalid Input Parameter [NULL]\n", __func__));
        return ret;
    }

    TELCOVOICEMGR_LOCK_OR_EXIT()

    PDML_CALLCONTROL_CALLINGFEATURES_SET_CTRL_T pCallFeaturesSetCtrl = (PDML_CALLCONTROL_CALLINGFEATURES_SET_CTRL_T)hInsContext;

    PDML_CALLCONTROL_CALLINGFEATURES_SET pHEAD = &(pCallFeaturesSetCtrl->dml);

    if(pHEAD != NULL)
    {
        pDmlVoiceService = (PTELCOVOICEMGR_DML_VOICESERVICE)pHEAD->pParentVoiceService;
    }

    if (pHEAD == NULL  || pDmlVoiceService == NULL)
    {
        TELCOVOICEMGR_UNLOCK()

        CcspTraceError(("%s:%d:: pHEAD or pDmlVoiceService NULL\n", __FUNCTION__, __LINE__));

        return ret;
    }

    uVsIndex = pDmlVoiceService->InstanceNumber;

    uSetIndex = pHEAD->uInstanceNumber;

    TELCOVOICEMGR_UNLOCK()

    if (strcmp(ParamName, "CallForwardOnNoAnswerRingTimeout") == 0)
    {
        snprintf(HalName, MAX_STR_LEN, "Device.Services.VoiceService.%d.CallControl.CallingFeatures.Set.%d.CallForwardOnNoAnswerRingTimeout",uVsIndex,uSetIndex);

        if (TelcoVoiceMgrHal_SetParamULong(HalName,uValue) == ANSC_STATUS_SUCCESS)
        {
            TELCOVOICEMGR_LOCK_OR_EXIT()

            pHEAD->CallForwardOnNoAnswerRingTimeout = uValue;

            TELCOVOICEMGR_UNLOCK()

            ret = TRUE;
        }
    }
    else if (strcmp(ParamName, "CallForwardOnBusyRingTimeout") == 0)
    {
        snprintf(HalName, MAX_STR_LEN, "Device.Services.VoiceService.%d.CallControl.CallingFeatures.Set.%d.CallForwardOnBusyRingTimeout",uVsIndex,uSetIndex);

        if (TelcoVoiceMgrHal_SetParamULong(HalName,uValue) == ANSC_STATUS_SUCCESS)
        {
            TELCOVOICEMGR_LOCK_OR_EXIT()

            pHEAD->CallForwardOnBusyRingTimeout = uValue;

            TELCOVOICEMGR_UNLOCK()

            ret = TRUE;
        }
    }
    else
    {
        CcspTraceWarning(("%s: Unsupported parameter '%s'\n", __func__,ParamName));
    }

    TELCOVOICEMGR_UNLOCK()

    return ret;

}

/**********************************************************************

    caller:     owner of this object

    prototype:

        ULONG TelcoVoiceMgrDml_CallControl_CallingFeatures_SetList_GetParamStringValue(ANSC_HANDLE hInsContext, char* ParamName, char* pValue, ULONG* pulSize);

    description:

        This function is called to retrieve string parameter value;

    argument:   ANSC_HANDLE                 hInsContext,
                The instance handle;

                char*                       ParamName,
                The parameter name;

                char*                       pValue,
                The string value buffer;

                ULONG*                      pUlSize
                The buffer of length of string value;
                Usually size of 1023 will be used.
                If it's not big enough, put required size here and return 1;

    return:     0 if succeeded;
                1 if short of buffer size; (*pUlSize = required size)
                -1 if not supported.

**********************************************************************/

ULONG TelcoVoiceMgrDml_CallControl_CallingFeatures_SetList_GetParamStringValue(ANSC_HANDLE hInsContext, char* ParamName, char* pValue, ULONG* pulSize)
{
    ULONG ret = 1;

    if(ParamName == NULL || pValue == NULL || pulSize == NULL)
    {
        CcspTraceWarning(("%s: Invalid Input Parameter [NULL]\n", __func__));
        return ret;
    }

    TELCOVOICEMGR_LOCK_OR_EXIT()

    PDML_CALLCONTROL_CALLINGFEATURES_SET_CTRL_T pCallFeaturesSetCtrl = (PDML_CALLCONTROL_CALLINGFEATURES_SET_CTRL_T)hInsContext;

    PDML_CALLCONTROL_CALLINGFEATURES_SET pHEAD = &(pCallFeaturesSetCtrl->dml);

    if (strcmp(ParamName, "CallForwardUnconditionalNumber") == 0)
    {
        AnscCopyString(pValue,pHEAD->CallForwardUnconditionalNumber);
        ret = 0;
    }
    else if (strcmp(ParamName, "CallForwardOnNoAnswerNumber") == 0)
    {
        AnscCopyString(pValue,pHEAD->CallForwardOnNoAnswerNumber);
        ret = 0;
    }
    else if (strcmp(ParamName, "CallForwardOnBusyNumber") == 0)
    {
        AnscCopyString(pValue,pHEAD->CallForwardOnBusyNumber);
        ret = 0;
    }
    else if (strcmp(ParamName, "Alias") == 0)
    {
        AnscCopyString(pValue,pHEAD->Alias);
        ret = 0;
    }
    else
    {
        CcspTraceWarning(("%s: Unsupported parameter '%s'\n", __func__,ParamName));
    }

    TELCOVOICEMGR_UNLOCK()

    return ret;
}

/**********************************************************************

    caller:     owner of this object

    prototype:

        BOOL TelcoVoiceMgrDml_CallControl_CallingFeatures_SetList_SetParamStringValue(ANSC_HANDLE hInsContext, char* ParamName, char* pString);

    description:

        This function is called to set string parameter value;

    argument:   ANSC_HANDLE                 hInsContext,
                The instance handle;

                char*                       ParamName,
                The parameter name;

                char*                       pString
                The updated string value;

    return:     TRUE if succeeded.

**********************************************************************/

BOOL TelcoVoiceMgrDml_CallControl_CallingFeatures_SetList_SetParamStringValue(ANSC_HANDLE hInsContext, char* ParamName, char* pString)
{
    BOOL ret = FALSE;
    ULONG uVsIndex  = 0;
    ULONG uSetIndex = 0;
    char HalName[MAX_STR_LEN] = {0};

    PTELCOVOICEMGR_DML_VOICESERVICE pDmlVoiceService = NULL;

    if(ParamName == NULL)
    {
        CcspTraceWarning(("%s: Invalid Input Parameter [NULL]\n", __func__));
        return ret;
    }

    TELCOVOICEMGR_LOCK_OR_EXIT()

    PDML_CALLCONTROL_CALLINGFEATURES_SET_CTRL_T pCallFeaturesSetCtrl = (PDML_CALLCONTROL_CALLINGFEATURES_SET_CTRL_T)hInsContext;

    PDML_CALLCONTROL_CALLINGFEATURES_SET pHEAD = &(pCallFeaturesSetCtrl->dml);

    if(pHEAD != NULL)
    {
        pDmlVoiceService = (PTELCOVOICEMGR_DML_VOICESERVICE)pHEAD->pParentVoiceService;
    }

    if (pHEAD == NULL  || pDmlVoiceService == NULL)
    {
        TELCOVOICEMGR_UNLOCK()

        CcspTraceError(("%s:%d:: pHEAD or pDmlVoiceService NULL\n", __FUNCTION__, __LINE__));

        return ret;
    }

    uVsIndex = pDmlVoiceService->InstanceNumber;

    uSetIndex = pHEAD->uInstanceNumber;

    TELCOVOICEMGR_UNLOCK()

    if (strcmp(ParamName, "CallForwardUnconditionalNumber") == 0)
    {
        snprintf(HalName, MAX_STR_LEN, "Device.Services.VoiceService.%d.CallControl.CallingFeatures.Set.%d.CallForwardUnconditionalNumber",uVsIndex,uSetIndex);

        if (TelcoVoiceMgrHal_SetParamString(HalName,pString) == ANSC_STATUS_SUCCESS)
        {
            TELCOVOICEMGR_LOCK_OR_EXIT()

            AnscCopyString(pHEAD->CallForwardUnconditionalNumber,pString);

            TELCOVOICEMGR_UNLOCK()

            ret = TRUE;
        }
    }
    else if (strcmp(ParamName, "CallForwardOnNoAnswerNumber") == 0)
    {
        snprintf(HalName, MAX_STR_LEN, "Device.Services.VoiceService.%d.CallControl.CallingFeatures.Set.%d.CallForwardOnNoAnswerNumber",uVsIndex,uSetIndex);

        if (TelcoVoiceMgrHal_SetParamString(HalName,pString) == ANSC_STATUS_SUCCESS)
        {
            TELCOVOICEMGR_LOCK_OR_EXIT()

            AnscCopyString(pHEAD->CallForwardOnNoAnswerNumber,pString);

            TELCOVOICEMGR_UNLOCK()

            ret = TRUE;
        }
    }
    else if (strcmp(ParamName, "CallForwardOnBusyNumber") == 0)
    {
        snprintf(HalName, MAX_STR_LEN, "Device.Services.VoiceService.%d.CallControl.CallingFeatures.Set.%d.CallForwardOnBusyNumber",uVsIndex,uSetIndex);

        if (TelcoVoiceMgrHal_SetParamString(HalName,pString) == ANSC_STATUS_SUCCESS)
        {
            TELCOVOICEMGR_LOCK_OR_EXIT()

            AnscCopyString(pHEAD->CallForwardOnBusyNumber,pString);

            TELCOVOICEMGR_UNLOCK()

            ret = TRUE;
        }
    }
    else if (strcmp(ParamName, "Alias") == 0)
    {
        TELCOVOICEMGR_LOCK_OR_EXIT()

        AnscCopyString(pHEAD->Alias,pString);

        TELCOVOICEMGR_UNLOCK()

        ret = TRUE;
    }
    else
    {
        CcspTraceWarning(("%s: Unsupported parameter '%s'\n", __func__,ParamName));
    }

    return ret;

}

/**********************************************************************

    caller:     owner of this object

    prototype:

        BOOL TelcoVoiceMgrDml_CallControl_CallingFeatures_SetList_GetParamBoolValue(ANSC_HANDLE hInsContext, char* ParamName, BOOL* pBool);

    description:

        This function is called to retrieve Boolean parameter value;

    argument:   ANSC_HANDLE                 hInsContext,
                The instance handle;

                char*                       ParamName,
                The parameter name;

                BOOL*                       pBool
                The buffer of returned boolean value;

    return:     TRUE if succeeded.

**********************************************************************/

BOOL TelcoVoiceMgrDml_CallControl_CallingFeatures_SetList_GetParamBoolValue(ANSC_HANDLE hInsContext, char* ParamName, BOOL* pBool)
{
    BOOL ret = FALSE;

    if(ParamName == NULL || pBool == NULL)
    {
        CcspTraceWarning(("%s: Invalid Input Parameter [NULL]\n", __func__));
        return ret;
    }

    TELCOVOICEMGR_LOCK_OR_EXIT()

    PDML_CALLCONTROL_CALLINGFEATURES_SET_CTRL_T pCallFeaturesSetCtrl = (PDML_CALLCONTROL_CALLINGFEATURES_SET_CTRL_T)hInsContext;

    PDML_CALLCONTROL_CALLINGFEATURES_SET pHEAD = &(pCallFeaturesSetCtrl->dml);

    if (strcmp(ParamName, "X_RDK-Central_COM_PhoneCallerIDEnable") == 0)
    {
        *pBool = pHEAD->X_RDK_Central_COM_PhoneCallerIDEnable;
        ret = TRUE;
    }
    else if (strcmp(ParamName, "X_RDK-Central_COM_HoldEnable") == 0)
    {
        *pBool = pHEAD->X_RDK_Central_COM_HoldEnable;
        ret = TRUE;
    }
    else if (strcmp(ParamName, "X_RDK-Central_COM_ConferenceCallingEnable") == 0)
    {
        *pBool = pHEAD->X_RDK_Central_COM_ConferenceCallingEnable;
        ret = TRUE;
    }
    else if (strcmp(ParamName, "VoiceMailEnable") == 0)
    {
        *pBool = pHEAD->VoiceMailEnable;
        ret = TRUE;
    }
    else if (strcmp(ParamName, "VMWIEnable") == 0)
    {
        *pBool = pHEAD->VMWIEnable;
        ret = TRUE;
    }
    else if (strcmp(ParamName, "SecretForwarderEnable") == 0)
    {
        *pBool = pHEAD->SecretForwarderEnable;
        ret = TRUE;
    }
    else if (strcmp(ParamName, "RepeatDialEnable") == 0)
    {
        *pBool = pHEAD->RepeatDialEnable;
        ret = TRUE;
    }
    else if (strcmp(ParamName, "MWIEnable") == 0)
    {
        *pBool = pHEAD->MWIEnable;
        ret = TRUE;
    }
    else if (strcmp(ParamName, "IIFCEnable") == 0)
    {
        *pBool = pHEAD->IIFCEnable;
        ret = TRUE;
    }
    else if (strcmp(ParamName, "FollowMeEnable") == 0)
    {
        *pBool = pHEAD->FollowMeEnable;
        ret = TRUE;
    }
    else if (strcmp(ParamName, "DoNotDisturbEnable") == 0)
    {
        *pBool = pHEAD->DoNotDisturbEnable;
        ret = TRUE;
    }
    else if (strcmp(ParamName, "CCBSEnable") == 0)
    {
        *pBool = pHEAD->CCBSEnable;
        ret = TRUE;
    }
    else if (strcmp(ParamName, "CallWaitingEnable") == 0)
    {
        *pBool = pHEAD->CallWaitingEnable;
        ret = TRUE;
    }
    else if (strcmp(ParamName, "CallTransferEnable") == 0)
    {
        *pBool = pHEAD->CallTransferEnable;
        ret = TRUE;
    }
    else if (strcmp(ParamName, "CallPickUpEnable") == 0)
    {
        *pBool = pHEAD->CallPickUpEnable;
        ret = TRUE;
    }
    else if (strcmp(ParamName, "CallForwardUnconditionalEnable") == 0)
    {
        *pBool = pHEAD->CallForwardUnconditionalEnable;
        ret = TRUE;
    }
    else if (strcmp(ParamName, "CallForwardOnNoAnswerEnable") == 0)
    {
        *pBool = pHEAD->CallForwardOnNoAnswerEnable;
        ret = TRUE;
    }
    else if (strcmp(ParamName, "CallForwardOnBusyEnable") == 0)
    {
        *pBool = pHEAD->CallForwardOnBusyEnable;
        ret = TRUE;
    }
    else if (strcmp(ParamName, "CallerIDNameEnable") == 0)
    {
        *pBool = pHEAD->CallerIDNameEnable;
        ret = TRUE;
    }
    else if (strcmp(ParamName, "CallerIDEnable") == 0)
    {
        *pBool = pHEAD->CallerIDEnable;
        ret = TRUE;
    }
    else if (strcmp(ParamName, "BlockForwardEnable") == 0)
    {
        *pBool = pHEAD->BlockForwardEnable;
        ret = TRUE;
    }
    else if (strcmp(ParamName, "AnonymousCallRejectionEnable") == 0)
    {
        *pBool = pHEAD->AnonymousCallRejectionEnable;
        ret = TRUE;
    }
    else if (strcmp(ParamName, "AnonymousCallEnable") == 0)
    {
        *pBool = pHEAD->AnonymousCallEnable;
        ret = TRUE;
    }
    else
    {
        CcspTraceWarning(("%s: Unsupported parameter '%s'\n", __func__,ParamName));
    }

    TELCOVOICEMGR_UNLOCK()

    return ret;
}

/**********************************************************************

    caller:     owner of this object

    prototype:

        BOOL TelcoVoiceMgrDml_CallControl_CallingFeatures_SetList_SetParamBoolValue(ANSC_HANDLE hInsContext, char* ParamName, BOOL bValue);

    description:

        This function is called to set BOOL parameter value;

    argument:   ANSC_HANDLE                 hInsContext,
                The instance handle;

                char*                       ParamName,
                The parameter name;

                BOOL                        bValue
                The updated BOOL value;

    return:     TRUE if succeeded.

**********************************************************************/

BOOL TelcoVoiceMgrDml_CallControl_CallingFeatures_SetList_SetParamBoolValue(ANSC_HANDLE hInsContext, char* ParamName, BOOL bValue)
{
    BOOL ret = FALSE;
    ULONG uVsIndex  = 0;
    ULONG uSetIndex = 0;
    char HalName[MAX_STR_LEN] = {0};

    PTELCOVOICEMGR_DML_VOICESERVICE pDmlVoiceService = NULL;

    if(ParamName == NULL)
    {
        CcspTraceWarning(("%s: Invalid Input Parameter [NULL]\n", __func__));
        return ret;
    }

    TELCOVOICEMGR_LOCK_OR_EXIT()

    PDML_CALLCONTROL_CALLINGFEATURES_SET_CTRL_T pCallFeaturesSetCtrl = (PDML_CALLCONTROL_CALLINGFEATURES_SET_CTRL_T)hInsContext;

    PDML_CALLCONTROL_CALLINGFEATURES_SET pHEAD = &(pCallFeaturesSetCtrl->dml);

    if(pHEAD != NULL)
    {
        pDmlVoiceService = (PTELCOVOICEMGR_DML_VOICESERVICE)pHEAD->pParentVoiceService;
    }

    if (pHEAD == NULL  || pDmlVoiceService == NULL)
    {
        TELCOVOICEMGR_UNLOCK()

        CcspTraceError(("%s:%d:: pHEAD or pDmlVoiceService NULL\n", __FUNCTION__, __LINE__));

        return ret;
    }

    uVsIndex = pDmlVoiceService->InstanceNumber;

    uSetIndex = pHEAD->uInstanceNumber;

    TELCOVOICEMGR_UNLOCK()

    if (strcmp(ParamName, "X_RDK-Central_COM_PhoneCallerIDEnable") == 0)
    {
        snprintf(HalName, MAX_STR_LEN, "Device.Services.VoiceService.%d.CallControl.CallingFeatures.Set.%d.X_RDK-Central_COM_PhoneCallerIDEnable",uVsIndex,uSetIndex);

        if (TelcoVoiceMgrHal_SetParamBool(HalName,bValue) == ANSC_STATUS_SUCCESS)
        {
            TELCOVOICEMGR_LOCK_OR_EXIT()

            pHEAD->X_RDK_Central_COM_PhoneCallerIDEnable = bValue;

            TELCOVOICEMGR_UNLOCK()

            ret = TRUE;
        }
    }
    else if (strcmp(ParamName, "X_RDK-Central_COM_HoldEnable") == 0)
    {
        snprintf(HalName, MAX_STR_LEN, "Device.Services.VoiceService.%d.CallControl.CallingFeatures.Set.%d.X_RDK-Central_COM_HoldEnable",uVsIndex,uSetIndex);

        if (TelcoVoiceMgrHal_SetParamBool(HalName,bValue) == ANSC_STATUS_SUCCESS)
        {
            TELCOVOICEMGR_LOCK_OR_EXIT()

            pHEAD->X_RDK_Central_COM_HoldEnable = bValue;

            TELCOVOICEMGR_UNLOCK()

            ret = TRUE;
        }
    }
    else if (strcmp(ParamName, "X_RDK-Central_COM_ConferenceCallingEnable") == 0)
    {
        snprintf(HalName, MAX_STR_LEN, "Device.Services.VoiceService.%d.CallControl.CallingFeatures.Set.%d.X_RDK-Central_COM_ConferenceCallingEnable",uVsIndex,uSetIndex);

        if (TelcoVoiceMgrHal_SetParamBool(HalName,bValue) == ANSC_STATUS_SUCCESS)
        {
            TELCOVOICEMGR_LOCK_OR_EXIT()

            pHEAD->X_RDK_Central_COM_ConferenceCallingEnable = bValue;

            TELCOVOICEMGR_UNLOCK()

            ret = TRUE;
        }
    }
    else if (strcmp(ParamName, "VoiceMailEnable") == 0)
    {
        snprintf(HalName, MAX_STR_LEN, "Device.Services.VoiceService.%d.CallControl.CallingFeatures.Set.%d.VoiceMailEnable",uVsIndex,uSetIndex);

        if (TelcoVoiceMgrHal_SetParamBool(HalName,bValue) == ANSC_STATUS_SUCCESS)
        {
            TELCOVOICEMGR_LOCK_OR_EXIT()

            pHEAD->VoiceMailEnable = bValue;

            TELCOVOICEMGR_UNLOCK()

            ret = TRUE;
        }
    }
    else if (strcmp(ParamName, "VMWIEnable") == 0)
    {
        snprintf(HalName, MAX_STR_LEN, "Device.Services.VoiceService.%d.CallControl.CallingFeatures.Set.%d.VMWIEnable",uVsIndex,uSetIndex);

        if (TelcoVoiceMgrHal_SetParamBool(HalName,bValue) == ANSC_STATUS_SUCCESS)
        {
            TELCOVOICEMGR_LOCK_OR_EXIT()

            pHEAD->VMWIEnable = bValue;

            TELCOVOICEMGR_UNLOCK()

            ret = TRUE;
        }
    }
    else if (strcmp(ParamName, "SecretForwarderEnable") == 0)
    {
        snprintf(HalName, MAX_STR_LEN, "Device.Services.VoiceService.%d.CallControl.CallingFeatures.Set.%d.SecretForwarderEnable",uVsIndex,uSetIndex);

        if (TelcoVoiceMgrHal_SetParamBool(HalName,bValue) == ANSC_STATUS_SUCCESS)
        {
            TELCOVOICEMGR_LOCK_OR_EXIT()

            pHEAD->SecretForwarderEnable = bValue;

            TELCOVOICEMGR_UNLOCK()

            ret = TRUE;
        }
    }
    else if (strcmp(ParamName, "RepeatDialEnable") == 0)
    {
        snprintf(HalName, MAX_STR_LEN, "Device.Services.VoiceService.%d.CallControl.CallingFeatures.Set.%d.RepeatDialEnable",uVsIndex,uSetIndex);

        if (TelcoVoiceMgrHal_SetParamBool(HalName,bValue) == ANSC_STATUS_SUCCESS)
        {
            TELCOVOICEMGR_LOCK_OR_EXIT()

            pHEAD->RepeatDialEnable = bValue;

            TELCOVOICEMGR_UNLOCK()

            ret = TRUE;
        }
    }
    else if (strcmp(ParamName, "MWIEnable") == 0)
    {
        snprintf(HalName, MAX_STR_LEN, "Device.Services.VoiceService.%d.CallControl.CallingFeatures.Set.%d.MWIEnable",uVsIndex,uSetIndex);

        if (TelcoVoiceMgrHal_SetParamBool(HalName,bValue) == ANSC_STATUS_SUCCESS)
        {
            TELCOVOICEMGR_LOCK_OR_EXIT()

            pHEAD->MWIEnable = bValue;

            TELCOVOICEMGR_UNLOCK()

            ret = TRUE;
        }
    }
    else if (strcmp(ParamName, "IIFCEnable") == 0)
    {
        snprintf(HalName, MAX_STR_LEN, "Device.Services.VoiceService.%d.CallControl.CallingFeatures.Set.%d.IIFCEnable",uVsIndex,uSetIndex);

        if (TelcoVoiceMgrHal_SetParamBool(HalName,bValue) == ANSC_STATUS_SUCCESS)
        {
            TELCOVOICEMGR_LOCK_OR_EXIT()

            pHEAD->IIFCEnable = bValue;

            TELCOVOICEMGR_UNLOCK()

            ret = TRUE;
        }
    }
    else if (strcmp(ParamName, "FollowMeEnable") == 0)
    {
        snprintf(HalName, MAX_STR_LEN, "Device.Services.VoiceService.%d.CallControl.CallingFeatures.Set.%d.FollowMeEnable",uVsIndex,uSetIndex);

        if (TelcoVoiceMgrHal_SetParamBool(HalName,bValue) == ANSC_STATUS_SUCCESS)
        {
            TELCOVOICEMGR_LOCK_OR_EXIT()

            pHEAD->FollowMeEnable = bValue;

            TELCOVOICEMGR_UNLOCK()

            ret = TRUE;
        }
    }
    else if (strcmp(ParamName, "DoNotDisturbEnable") == 0)
    {
        snprintf(HalName, MAX_STR_LEN, "Device.Services.VoiceService.%d.CallControl.CallingFeatures.Set.%d.DoNotDisturbEnable",uVsIndex,uSetIndex);

        if (TelcoVoiceMgrHal_SetParamBool(HalName,bValue) == ANSC_STATUS_SUCCESS)
        {
            TELCOVOICEMGR_LOCK_OR_EXIT()

            pHEAD->DoNotDisturbEnable = bValue;

            TELCOVOICEMGR_UNLOCK()

            ret = TRUE;
        }
    }
    else if (strcmp(ParamName, "CCBSEnable") == 0)
    {
        snprintf(HalName, MAX_STR_LEN, "Device.Services.VoiceService.%d.CallControl.CallingFeatures.Set.%d.CCBSEnable",uVsIndex,uSetIndex);

        if (TelcoVoiceMgrHal_SetParamBool(HalName,bValue) == ANSC_STATUS_SUCCESS)
        {
            TELCOVOICEMGR_LOCK_OR_EXIT()

            pHEAD->CCBSEnable = bValue;

            TELCOVOICEMGR_UNLOCK()

            ret = TRUE;
        }
    }
    else if (strcmp(ParamName, "CallWaitingEnable") == 0)
    {
        snprintf(HalName, MAX_STR_LEN, "Device.Services.VoiceService.%d.CallControl.CallingFeatures.Set.%d.CallWaitingEnable",uVsIndex,uSetIndex);

        if (TelcoVoiceMgrHal_SetParamBool(HalName,bValue) == ANSC_STATUS_SUCCESS)
        {
            TELCOVOICEMGR_LOCK_OR_EXIT()

            pHEAD->CallWaitingEnable = bValue;

            TELCOVOICEMGR_UNLOCK()

            ret = TRUE;
        }
    }
    else if (strcmp(ParamName, "CallTransferEnable") == 0)
    {
        snprintf(HalName, MAX_STR_LEN, "Device.Services.VoiceService.%d.CallControl.CallingFeatures.Set.%d.CallTransferEnable",uVsIndex,uSetIndex);

        if (TelcoVoiceMgrHal_SetParamBool(HalName,bValue) == ANSC_STATUS_SUCCESS)
        {
            TELCOVOICEMGR_LOCK_OR_EXIT()

            pHEAD->CallTransferEnable = bValue;

            TELCOVOICEMGR_UNLOCK()

            ret = TRUE;
        }
    }
    else if (strcmp(ParamName, "CallPickUpEnable") == 0)
    {
        snprintf(HalName, MAX_STR_LEN, "Device.Services.VoiceService.%d.CallControl.CallingFeatures.Set.%d.CallPickUpEnable",uVsIndex,uSetIndex);

        if (TelcoVoiceMgrHal_SetParamBool(HalName,bValue) == ANSC_STATUS_SUCCESS)
        {
            TELCOVOICEMGR_LOCK_OR_EXIT()

            pHEAD->CallPickUpEnable = bValue;

            TELCOVOICEMGR_UNLOCK()

            ret = TRUE;
        }
    }
    else if (strcmp(ParamName, "CallForwardUnconditionalEnable") == 0)
    {
        snprintf(HalName, MAX_STR_LEN, "Device.Services.VoiceService.%d.CallControl.CallingFeatures.Set.%d.CallForwardUnconditionalEnable",uVsIndex,uSetIndex);

        if (TelcoVoiceMgrHal_SetParamBool(HalName,bValue) == ANSC_STATUS_SUCCESS)
        {
            TELCOVOICEMGR_LOCK_OR_EXIT()

            pHEAD->CallForwardUnconditionalEnable = bValue;

            TELCOVOICEMGR_UNLOCK()

            ret = TRUE;
        }
    }
    else if (strcmp(ParamName, "CallForwardOnNoAnswerEnable") == 0)
    {
        snprintf(HalName, MAX_STR_LEN, "Device.Services.VoiceService.%d.CallControl.CallingFeatures.Set.%d.CallForwardOnNoAnswerEnable",uVsIndex,uSetIndex);

        if (TelcoVoiceMgrHal_SetParamBool(HalName,bValue) == ANSC_STATUS_SUCCESS)
        {
            TELCOVOICEMGR_LOCK_OR_EXIT()

            pHEAD->CallForwardOnNoAnswerEnable = bValue;

            TELCOVOICEMGR_UNLOCK()

            ret = TRUE;
        }
    }
    else if (strcmp(ParamName, "CallForwardOnBusyEnable") == 0)
    {
        snprintf(HalName, MAX_STR_LEN, "Device.Services.VoiceService.%d.CallControl.CallingFeatures.Set.%d.CallForwardOnBusyEnable",uVsIndex,uSetIndex);

        if (TelcoVoiceMgrHal_SetParamBool(HalName,bValue) == ANSC_STATUS_SUCCESS)
        {
            TELCOVOICEMGR_LOCK_OR_EXIT()

            pHEAD->CallForwardOnBusyEnable = bValue;

            TELCOVOICEMGR_UNLOCK()

            ret = TRUE;
        }
    }
    else if (strcmp(ParamName, "CallerIDNameEnable") == 0)
    {
        snprintf(HalName, MAX_STR_LEN, "Device.Services.VoiceService.%d.CallControl.CallingFeatures.Set.%d.CallerIDNameEnable",uVsIndex,uSetIndex);

        if (TelcoVoiceMgrHal_SetParamBool(HalName,bValue) == ANSC_STATUS_SUCCESS)
        {
            TELCOVOICEMGR_LOCK_OR_EXIT()

            pHEAD->CallerIDNameEnable = bValue;

            TELCOVOICEMGR_UNLOCK()

            ret = TRUE;
        }
    }
    else if (strcmp(ParamName, "CallerIDEnable") == 0)
    {
        snprintf(HalName, MAX_STR_LEN, "Device.Services.VoiceService.%d.CallControl.CallingFeatures.Set.%d.CallerIDEnable",uVsIndex,uSetIndex);

        if (TelcoVoiceMgrHal_SetParamBool(HalName,bValue) == ANSC_STATUS_SUCCESS)
        {
            TELCOVOICEMGR_LOCK_OR_EXIT()

            pHEAD->CallerIDEnable = bValue;

            TELCOVOICEMGR_UNLOCK()

            ret = TRUE;
        }
    }
    else if (strcmp(ParamName, "BlockForwardEnable") == 0)
    {
        snprintf(HalName, MAX_STR_LEN, "Device.Services.VoiceService.%d.CallControl.CallingFeatures.Set.%d.BlockForwardEnable",uVsIndex,uSetIndex);

        if (TelcoVoiceMgrHal_SetParamBool(HalName,bValue) == ANSC_STATUS_SUCCESS)
        {
            TELCOVOICEMGR_LOCK_OR_EXIT()

            pHEAD->BlockForwardEnable = bValue;

            TELCOVOICEMGR_UNLOCK()

            ret = TRUE;
        }
    }
    else if (strcmp(ParamName, "AnonymousCallRejectionEnable") == 0)
    {
        snprintf(HalName, MAX_STR_LEN, "Device.Services.VoiceService.%d.CallControl.CallingFeatures.Set.%d.AnonymousCallRejectionEnable",uVsIndex,uSetIndex);

        if (TelcoVoiceMgrHal_SetParamBool(HalName,bValue) == ANSC_STATUS_SUCCESS)
        {
            TELCOVOICEMGR_LOCK_OR_EXIT()

            pHEAD->AnonymousCallRejectionEnable = bValue;

            TELCOVOICEMGR_UNLOCK()

            ret = TRUE;
        }
    }
    else if (strcmp(ParamName, "AnonymousCallEnable") == 0)
    {
        snprintf(HalName, MAX_STR_LEN, "Device.Services.VoiceService.%d.CallControl.CallingFeatures.Set.%d.AnonymousCallEnable",uVsIndex,uSetIndex);

        if (TelcoVoiceMgrHal_SetParamBool(HalName,bValue) == ANSC_STATUS_SUCCESS)
        {
            TELCOVOICEMGR_LOCK_OR_EXIT()

            pHEAD->AnonymousCallEnable = bValue;

            TELCOVOICEMGR_UNLOCK()

            ret = TRUE;
        }
    }
    else
    {
        CcspTraceWarning(("%s: Unsupported parameter '%s'\n", __func__,ParamName));
    }

    return ret;

}

/**********************************************************************

    caller:     owner of this object

    prototype:

        BOOL TelcoVoiceMgrDml_CallControl_CallingFeatures_SetList_Validate(ANSC_HANDLE hInsContext);

    description:

        This function is called to validate the update.

    argument:   ANSC_HANDLE                 hInsContext,
                The instance handle;

    return:     TRUE if there's no issue.

**********************************************************************/

BOOL TelcoVoiceMgrDml_CallControl_CallingFeatures_SetList_Validate(ANSC_HANDLE hInsContext)
{
    return TRUE;
}

/**********************************************************************

    caller:     owner of this object

    prototype:

        BOOL TelcoVoiceMgrDml_CallControl_CallingFeatures_SetList_Commit(ANSC_HANDLE hInsContext);

    description:

        This function is called to commit the update.

    argument:   ANSC_HANDLE                 hInsContext,
                The instance handle;

    return:     0 if there's no issue.

**********************************************************************/

BOOL TelcoVoiceMgrDml_CallControl_CallingFeatures_SetList_Commit(ANSC_HANDLE hInsContext)
{
    return 0;
}

/**********************************************************************

    caller:     owner of this object

    prototype:

        BOOL TelcoVoiceMgrDml_CallControl_CallingFeatures_SetList_Rollback(ANSC_HANDLE hInsContext);

    description:

        This function is called to rollback the update.

    argument:   ANSC_HANDLE                 hInsContext,
                The instance handle;

    return:     0 if there's no issue.

**********************************************************************/

BOOL TelcoVoiceMgrDml_CallControl_CallingFeatures_SetList_Rollback(ANSC_HANDLE hInsContext)
{
    return 0;
}

/**********************************************************************

    caller:     owner of this object

    prototype:

        BOOL TelcoVoiceMgrDml_CallControl_CallingFeatures_SetList_CFTList_IsUpdated(ANSC_HANDLE hInsContext);

    description:

        This function is checking whether the table is updated or not.

    argument:   ANSC_HANDLE                 hInsContext,
                The instance handle;

    return:     TRUE or FALSE.

**********************************************************************/

BOOL TelcoVoiceMgrDml_CallControl_CallingFeatures_SetList_CFTList_IsUpdated(ANSC_HANDLE hInsContext)
{
    return TRUE;
}

/**********************************************************************

    caller:     owner of this object

    prototype:

        ULONG TelcoVoiceMgrDml_CallControl_CallingFeatures_SetList_CFTList_Synchronize(ANSC_HANDLE hInsContext);

    description:

        This function is called to synchronize the table.

    argument:   ANSC_HANDLE                 hInsContext,
                The instance handle;

    return:     The status of the operation.

**********************************************************************/

ULONG TelcoVoiceMgrDml_CallControl_CallingFeatures_SetList_CFTList_Synchronize(ANSC_HANDLE hInsContext)
{
    return 0;
}

/**********************************************************************

    caller:     owner of this object

    prototype:

        ULONG TelcoVoiceMgrDml_CallControl_CallingFeatures_SetList_CFTList_GetEntryCount(ANSC_HANDLE hInsContext);

    description:

        This function is called to retrieve the count of the table.

    argument:   ANSC_HANDLE                 hInsContext,
                The instance handle;

    return:     The count of the table

**********************************************************************/
ULONG TelcoVoiceMgrDml_CallControl_CallingFeatures_SetList_CFTList_GetEntryCount(ANSC_HANDLE hInsContext)
{
    ULONG ret = 0;

    TELCOVOICEMGR_LOCK_OR_EXIT()

    DML_CALLCONTROL_CALLINGFEATURES_SET_CTRL_T* pCallFeaturesSetCtrl = (DML_CALLCONTROL_CALLINGFEATURES_SET_CTRL_T*) hInsContext;

    PDML_CALLCONTROL_CALLINGFEATURES_SET pDmlCallFeaturesSet = &(pCallFeaturesSetCtrl->dml);

    PDML_CALLCONTROL_CALLINGFEATURES_SET_CFT_LIST_T pCallFeaturesSetCFTList = &(pDmlCallFeaturesSet->CFT);

    if(pCallFeaturesSetCFTList != NULL)
    {
        ret = pCallFeaturesSetCFTList->ulQuantity;
    }

    TELCOVOICEMGR_UNLOCK()

    return ret;
}

/**********************************************************************

    caller:     owner of this object

    prototype:

        ANSC_HANDLE TelcoVoiceMgrDml_CallControl_CallingFeatures_SetList_CFTList_GetEntry(ANSC_HANDLE hInsContext, ULONG nIndex, ULONG* pInsNumber);

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
ANSC_HANDLE TelcoVoiceMgrDml_CallControl_CallingFeatures_SetList_CFTList_GetEntry(ANSC_HANDLE hInsContext, ULONG nIndex, ULONG* pInsNumber)
{
    ANSC_HANDLE ret = NULL;

    TELCOVOICEMGR_LOCK_OR_EXIT()

    PDML_CALLCONTROL_CALLINGFEATURES_SET_CTRL_T pSetCtrl = (PDML_CALLCONTROL_CALLINGFEATURES_SET_CTRL_T) hInsContext;

    PDML_CALLCONTROL_CALLINGFEATURES_SET pDmlSet = &(pSetCtrl->dml);

    PDML_CALLCONTROL_CALLINGFEATURES_SET_CFT_LIST_T pCFTList = &(pDmlSet->CFT);

    if(pCFTList != NULL)
    {
        if(nIndex < pCFTList->ulQuantity)
        {
            PDML_CALLCONTROL_CALLINGFEATURES_SET_CFT_CTRL_T pCFTCtrl = pCFTList->pdata[nIndex];
            if(pCFTCtrl != NULL)
            {
               *pInsNumber = nIndex + 1;
               ret = (ANSC_HANDLE) pCFTCtrl;
            }
        }
    }

    TELCOVOICEMGR_UNLOCK()

    return ret;
}

/**********************************************************************

    caller:     owner of this object

    prototype:

        ULONG TelcoVoiceMgrDml_CallControl_CallingFeatures_SetList_CFTList_GetParamStringValue(ANSC_HANDLE hInsContext, char* ParamName, char* pValue, ULONG* pulSize);

    description:

        This function is called to retrieve string parameter value;

    argument:   ANSC_HANDLE                 hInsContext,
                The instance handle;

                char*                       ParamName,
                The parameter name;

                char*                       pValue,
                The string value buffer;

                ULONG*                      pUlSize
                The buffer of length of string value;
                Usually size of 1023 will be used.
                If it's not big enough, put required size here and return 1;

    return:     0 if succeeded;
                1 if short of buffer size; (*pUlSize = required size)
                -1 if not supported.

**********************************************************************/

ULONG TelcoVoiceMgrDml_CallControl_CallingFeatures_SetList_CFTList_GetParamStringValue(ANSC_HANDLE hInsContext, char* ParamName, char* pValue, ULONG* pulSize)
{
    ULONG ret = 1;

    if(ParamName == NULL || pValue == NULL || pulSize == NULL)
    {
        CcspTraceWarning(("%s: Invalid Input Parameter [NULL]\n", __func__));
        return ret;
    }

    TELCOVOICEMGR_LOCK_OR_EXIT()

    PDML_CALLCONTROL_CALLINGFEATURES_SET_CFT_CTRL_T pCallCtrlCFSetCFLCtrl = (PDML_CALLCONTROL_CALLINGFEATURES_SET_CFT_CTRL_T)hInsContext;

    PDML_CALLCONTROL_CALLINGFEATURES_SET_CFT pHEAD = &(pCallCtrlCFSetCFLCtrl->dml);

    if (strcmp(ParamName, "StartTime") == 0)
    {
        AnscCopyString(pValue,pHEAD->StartTime);
        ret = 0;
    }
    else if (strcmp(ParamName, "ForwardedToNumber") == 0)
    {
        AnscCopyString(pValue,pHEAD->ForwardedToNumber);
        ret = 0;
    }
    else if (strcmp(ParamName, "EndTime") == 0)
    {
        AnscCopyString(pValue,pHEAD->EndTime);
        ret = 0;
    }
    else if (strcmp(ParamName, "Day") == 0)
    {
        AnscCopyString(pValue, "Monday");
        ret = 0;
    }
    else if (strcmp(ParamName, "Alias") == 0)
    {
        AnscCopyString(pValue,pHEAD->Alias);
        ret = 0;
    }
    else
    {
        CcspTraceWarning(("%s: Unsupported parameter '%s'\n", __func__,ParamName));
    }

    TELCOVOICEMGR_UNLOCK()

    return ret;
}

/**********************************************************************

    caller:     owner of this object

    prototype:

        BOOL TelcoVoiceMgrDml_CallControl_CallingFeatures_SetList_CFTList_SetParamStringValue(ANSC_HANDLE hInsContext, char* ParamName, char* pString);

    description:

        This function is called to set string parameter value;

    argument:   ANSC_HANDLE                 hInsContext,
                The instance handle;

                char*                       ParamName,
                The parameter name;

                char*                       pString
                The updated string value;

    return:     TRUE if succeeded.

**********************************************************************/

BOOL TelcoVoiceMgrDml_CallControl_CallingFeatures_SetList_CFTList_SetParamStringValue(ANSC_HANDLE hInsContext, char* ParamName, char* pString)
{
    BOOL ret = FALSE;
    ULONG uVsIndex  = 0;
    ULONG uSetIndex = 0;
    ULONG uCFTIndex = 0;
    char HalName[MAX_STR_LEN] = {0};

    PTELCOVOICEMGR_DML_VOICESERVICE pDmlVoiceService = NULL;

    PDML_CALLCONTROL_CALLINGFEATURES_SET pDmlSet = NULL;

    if(ParamName == NULL)
    {
        CcspTraceWarning(("%s: Invalid Input Parameter [NULL]\n", __func__));
        return ret;
    }

    TELCOVOICEMGR_LOCK_OR_EXIT()

    PDML_CALLCONTROL_CALLINGFEATURES_SET_CFT_CTRL_T pCallCtrlCFSetCFLCtrl = (PDML_CALLCONTROL_CALLINGFEATURES_SET_CFT_CTRL_T)hInsContext;

    PDML_CALLCONTROL_CALLINGFEATURES_SET_CFT pHEAD = &(pCallCtrlCFSetCFLCtrl->dml);

    if(pHEAD != NULL)
    {
        pDmlSet = (PDML_CALLCONTROL_CALLINGFEATURES_SET)pHEAD->pParentCallCtrlSet;
    }

    if(pDmlSet != NULL)
    {
        pDmlVoiceService = (PTELCOVOICEMGR_DML_VOICESERVICE)pDmlSet->pParentVoiceService;
    }

    if (pHEAD == NULL  || pDmlSet == NULL || pDmlVoiceService == NULL)
    {
        TELCOVOICEMGR_UNLOCK()

        CcspTraceError(("%s:%d:: pHEAD or pDmlSet or pDmlVoiceService NULL\n", __FUNCTION__, __LINE__));

        return ret;
    }

    uVsIndex = pDmlVoiceService->InstanceNumber;

    uSetIndex = pDmlSet->uInstanceNumber;

    uCFTIndex = pHEAD->uInstanceNumber;

    TELCOVOICEMGR_UNLOCK()

    if (strcmp(ParamName, "StartTime") == 0)
    {
        snprintf(HalName, MAX_STR_LEN, "Device.Services.VoiceService.%d.CallControl.CallingFeatures.Set.%d.CFT.%d.StartTime",uVsIndex,uSetIndex,uCFTIndex);

        if (TelcoVoiceMgrHal_SetParamString(HalName,pString) == ANSC_STATUS_SUCCESS)
        {
            TELCOVOICEMGR_LOCK_OR_EXIT()

            AnscCopyString(pHEAD->StartTime,pString);

            TELCOVOICEMGR_UNLOCK()

            ret = TRUE;
        }
    }
    else if (strcmp(ParamName, "ForwardedToNumber") == 0)
    {
        snprintf(HalName, MAX_STR_LEN, "Device.Services.VoiceService.%d.CallControl.CallingFeatures.Set.%d.CFT.%d.ForwardedToNumber",uVsIndex,uSetIndex,uCFTIndex);

        if (TelcoVoiceMgrHal_SetParamString(HalName,pString) == ANSC_STATUS_SUCCESS)
        {
            TELCOVOICEMGR_LOCK_OR_EXIT()

            AnscCopyString(pHEAD->ForwardedToNumber,pString);

            TELCOVOICEMGR_UNLOCK()

            ret = TRUE;
        }
    }
    else if (strcmp(ParamName, "EndTime") == 0)
    {
        snprintf(HalName, MAX_STR_LEN, "Device.Services.VoiceService.%d.CallControl.CallingFeatures.Set.%d.CFT.%d.EndTime",uVsIndex,uSetIndex,uCFTIndex);

        if (TelcoVoiceMgrHal_SetParamString(HalName,pString) == ANSC_STATUS_SUCCESS)
        {
            TELCOVOICEMGR_LOCK_OR_EXIT()

            AnscCopyString(pHEAD->EndTime,pString);

            TELCOVOICEMGR_UNLOCK()

            ret = TRUE;
        }
    }
    else if (strcmp(ParamName, "Day") == 0)
    {
        char enumValue[][STR_LEN_32]={"Monday","Tuesday","Wednesday","Thursday","Friday","Saturday","Sunday","All"};

        snprintf(HalName, MAX_STR_LEN, "Device.Services.VoiceService.%d.CallControl.CallingFeatures.Set.%d.CFT.%d.Day",uVsIndex,uSetIndex,uCFTIndex);

        if (TelcoVoiceMgrHal_SetParamString(HalName,pString) == ANSC_STATUS_SUCCESS)
        {
            TELCOVOICEMGR_LOCK_OR_EXIT()

            //AnscCopyString(pHEAD->Day,pString);

            TELCOVOICEMGR_UNLOCK()

            ret = TRUE;
        }
    }
    else if (strcmp(ParamName, "Alias") == 0)
    {
        TELCOVOICEMGR_LOCK_OR_EXIT()

        AnscCopyString(pHEAD->Alias,pString);

        TELCOVOICEMGR_UNLOCK()

        ret = TRUE;
    }
    else
    {
        CcspTraceWarning(("%s: Unsupported parameter '%s'\n", __func__,ParamName));
    }

    return ret;
}

/**********************************************************************

    caller:     owner of this object

    prototype:

        BOOL TelcoVoiceMgrDml_CallControl_CallingFeatures_SetList_CFTList_GetParamBoolValue(ANSC_HANDLE hInsContext, char* ParamName, BOOL* pBool);

    description:

        This function is called to retrieve Boolean parameter value;

    argument:   ANSC_HANDLE                 hInsContext,
                The instance handle;

                char*                       ParamName,
                The parameter name;

                BOOL*                       pBool
                The buffer of returned boolean value;

    return:     TRUE if succeeded.

**********************************************************************/

BOOL TelcoVoiceMgrDml_CallControl_CallingFeatures_SetList_CFTList_GetParamBoolValue(ANSC_HANDLE hInsContext, char* ParamName, BOOL* pBool)
{
    BOOL ret = FALSE;

    if(ParamName == NULL || pBool == NULL)
    {
        CcspTraceWarning(("%s: Invalid Input Parameter [NULL]\n", __func__));
        return ret;
    }

    TELCOVOICEMGR_LOCK_OR_EXIT()

    PDML_CALLCONTROL_CALLINGFEATURES_SET_CFT_CTRL_T pCallCtrlCFSetCFLCtrl = (PDML_CALLCONTROL_CALLINGFEATURES_SET_CFT_CTRL_T)hInsContext;

    PDML_CALLCONTROL_CALLINGFEATURES_SET_CFT pHEAD = &(pCallCtrlCFSetCFLCtrl->dml);

    if (strcmp(ParamName, "Enable") == 0)
    {
        *pBool = pHEAD->Enable;
        ret = TRUE;
    }
    else
    {
        CcspTraceWarning(("%s: Unsupported parameter '%s'\n", __func__,ParamName));
    }

    TELCOVOICEMGR_UNLOCK()

    return ret;
}

/**********************************************************************

    caller:     owner of this object

    prototype:

        BOOL TelcoVoiceMgrDml_CallControl_CallingFeatures_SetList_CFTList_SetParamBoolValue(ANSC_HANDLE hInsContext, char* ParamName, BOOL bValue);

    description:

        This function is called to set BOOL parameter value;

    argument:   ANSC_HANDLE                 hInsContext,
                The instance handle;

                char*                       ParamName,
                The parameter name;

                BOOL                        bValue
                The updated BOOL value;

    return:     TRUE if succeeded.

**********************************************************************/

BOOL TelcoVoiceMgrDml_CallControl_CallingFeatures_SetList_CFTList_SetParamBoolValue(ANSC_HANDLE hInsContext, char* ParamName, BOOL bValue)
{
    BOOL ret = FALSE;
    ULONG uVsIndex  = 0;
    ULONG uSetIndex = 0;
    ULONG uCFTIndex = 0;
    char HalName[MAX_STR_LEN] = {0};

    PTELCOVOICEMGR_DML_VOICESERVICE pDmlVoiceService = NULL;

    PDML_CALLCONTROL_CALLINGFEATURES_SET pDmlSet = NULL;

    if(ParamName == NULL)
    {
        CcspTraceWarning(("%s: Invalid Input Parameter [NULL]\n", __func__));
        return ret;
    }

    TELCOVOICEMGR_LOCK_OR_EXIT()

    PDML_CALLCONTROL_CALLINGFEATURES_SET_CFT_CTRL_T pCallCtrlCFSetCFLCtrl = (PDML_CALLCONTROL_CALLINGFEATURES_SET_CFT_CTRL_T)hInsContext;

    PDML_CALLCONTROL_CALLINGFEATURES_SET_CFT pHEAD = &(pCallCtrlCFSetCFLCtrl->dml);

    if(pHEAD != NULL)
    {
        pDmlSet = (PDML_CALLCONTROL_CALLINGFEATURES_SET)pHEAD->pParentCallCtrlSet;
    }

    if(pDmlSet != NULL)
    {
        pDmlVoiceService = (PTELCOVOICEMGR_DML_VOICESERVICE)pDmlSet->pParentVoiceService;
    }

    if (pHEAD == NULL  || pDmlSet == NULL || pDmlVoiceService == NULL)
    {
        TELCOVOICEMGR_UNLOCK()

        CcspTraceError(("%s:%d:: pHEAD or pDmlSet or pDmlVoiceService NULL\n", __FUNCTION__, __LINE__));

        return ret;
    }

    uVsIndex = pDmlVoiceService->InstanceNumber;

    uSetIndex = pDmlSet->uInstanceNumber;

    uCFTIndex = pHEAD->uInstanceNumber;

    TELCOVOICEMGR_UNLOCK()

    if (strcmp(ParamName, "Enable") == 0)
    {
        snprintf(HalName, MAX_STR_LEN, "Device.Services.VoiceService.%d.CallControl.CallingFeatures.Set.%d.CFT.%d.Enable",uVsIndex,uSetIndex,uCFTIndex);

        if (TelcoVoiceMgrHal_SetParamBool(HalName,bValue) == ANSC_STATUS_SUCCESS)
        {
            TELCOVOICEMGR_LOCK_OR_EXIT()

            pHEAD->Enable = bValue;

            TELCOVOICEMGR_UNLOCK()

            ret = TRUE;
        }
    }
    else
    {
        CcspTraceWarning(("%s: Unsupported parameter '%s'\n", __func__,ParamName));
    }

    return ret;
}

/**********************************************************************

    caller:     owner of this object

    prototype:

        BOOL TelcoVoiceMgrDml_CallControl_CallingFeatures_SetList_CFTList_Validate(ANSC_HANDLE hInsContext);

    description:

        This function is called to validate the update.

    argument:   ANSC_HANDLE                 hInsContext,
                The instance handle;

    return:     TRUE if there's no issue.

**********************************************************************/

BOOL TelcoVoiceMgrDml_CallControl_CallingFeatures_SetList_CFTList_Validate(ANSC_HANDLE hInsContext)
{
    return TRUE;
}

/**********************************************************************

    caller:     owner of this object

    prototype:

        BOOL TelcoVoiceMgrDml_CallControl_CallingFeatures_SetList_CFTList_Commit(ANSC_HANDLE hInsContext);

    description:

        This function is called to commit the update.

    argument:   ANSC_HANDLE                 hInsContext,
                The instance handle;

    return:     0 if there's no issue.

**********************************************************************/

BOOL TelcoVoiceMgrDml_CallControl_CallingFeatures_SetList_CFTList_Commit(ANSC_HANDLE hInsContext)
{
    return 0;
}

/**********************************************************************

    caller:     owner of this object

    prototype:

        BOOL TelcoVoiceMgrDml_CallControl_CallingFeatures_SetList_CFTList_Rollback(ANSC_HANDLE hInsContext);

    description:

        This function is called to rollback the update.

    argument:   ANSC_HANDLE                 hInsContext,
                The instance handle;

    return:     0 if there's no issue.

**********************************************************************/

BOOL TelcoVoiceMgrDml_CallControl_CallingFeatures_SetList_CFTList_Rollback(ANSC_HANDLE hInsContext)
{
    return 0;
}

/**********************************************************************

    caller:     owner of this object

    prototype:

        BOOL TelcoVoiceMgrDml_CallControl_CallingFeatures_SetList_SCFList_IsUpdated(ANSC_HANDLE hInsContext);

    description:

        This function is checking whether the table is updated or not.

    argument:   ANSC_HANDLE                 hInsContext,
                The instance handle;

    return:     TRUE or FALSE.

**********************************************************************/

BOOL TelcoVoiceMgrDml_CallControl_CallingFeatures_SetList_SCFList_IsUpdated(ANSC_HANDLE hInsContext)
{
    return TRUE;
}

/**********************************************************************

    caller:     owner of this object

    prototype:

        ULONG TelcoVoiceMgrDml_CallControl_CallingFeatures_SetList_SCFList_Synchronize(ANSC_HANDLE hInsContext);

    description:

        This function is called to synchronize the table.

    argument:   ANSC_HANDLE                 hInsContext,
                The instance handle;

    return:     The status of the operation.

**********************************************************************/

ULONG TelcoVoiceMgrDml_CallControl_CallingFeatures_SetList_SCFList_Synchronize(ANSC_HANDLE hInsContext)
{
    return 0;
}

/**********************************************************************

    caller:     owner of this object

    prototype:

        ULONG TelcoVoiceMgrDml_CallControl_CallingFeatures_SetList_SCFList_GetEntryCount(ANSC_HANDLE hInsContext);

    description:

        This function is called to retrieve the count of the table.

    argument:   ANSC_HANDLE                 hInsContext,
                The instance handle;

    return:     The count of the table

**********************************************************************/
ULONG TelcoVoiceMgrDml_CallControl_CallingFeatures_SetList_SCFList_GetEntryCount(ANSC_HANDLE hInsContext)
{
    ULONG ret = 0;

    TELCOVOICEMGR_LOCK_OR_EXIT()

    DML_CALLCONTROL_CALLINGFEATURES_SET_CTRL_T* pCallFeaturesSetCtrl = (DML_CALLCONTROL_CALLINGFEATURES_SET_CTRL_T*) hInsContext;

    PDML_CALLCONTROL_CALLINGFEATURES_SET pDmlCallFeaturesSet = &(pCallFeaturesSetCtrl->dml);

    PDML_CALLCONTROL_CALLINGFEATURES_SET_SCF_LIST_T pCallFeaturesSetSCFList = &(pDmlCallFeaturesSet->SCF);

    if(pCallFeaturesSetSCFList != NULL)
    {
        ret = pCallFeaturesSetSCFList->ulQuantity;
    }
    TELCOVOICEMGR_UNLOCK()

    return ret;
}

/**********************************************************************

    caller:     owner of this object

    prototype:

        ANSC_HANDLE TelcoVoiceMgrDml_CallControl_CallingFeatures_SetList_SCFList_GetEntry(ANSC_HANDLE hInsContext, ULONG nIndex, ULONG* pInsNumber);

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
ANSC_HANDLE TelcoVoiceMgrDml_CallControl_CallingFeatures_SetList_SCFList_GetEntry(ANSC_HANDLE hInsContext, ULONG nIndex, ULONG* pInsNumber)
{
    ANSC_HANDLE ret = NULL;

    TELCOVOICEMGR_LOCK_OR_EXIT()

    PDML_CALLCONTROL_CALLINGFEATURES_SET_CTRL_T pSetCtrl = (PDML_CALLCONTROL_CALLINGFEATURES_SET_CTRL_T) hInsContext;

    PDML_CALLCONTROL_CALLINGFEATURES_SET pDmlSet = &(pSetCtrl->dml);

    PDML_CALLCONTROL_CALLINGFEATURES_SET_SCF_LIST_T pSCFList = &(pDmlSet->SCF);

    if(pSCFList != NULL)
    {
        if(nIndex < pSCFList->ulQuantity)
        {
            PDML_CALLCONTROL_CALLINGFEATURES_SET_SCF_CTRL_T pSCFCtrl = pSCFList->pdata[nIndex];
            if(pSCFCtrl != NULL)
            {
               *pInsNumber = nIndex + 1;
               ret = (ANSC_HANDLE) pSCFCtrl;
            }
        }
    }

    TELCOVOICEMGR_UNLOCK()

    return ret;
}

/**********************************************************************

    caller:     owner of this object

    prototype:

        ULONG TelcoVoiceMgrDml_CallControl_CallingFeatures_SetList_SCFList_GetParamStringValue(ANSC_HANDLE hInsContext, char* ParamName, char* pValue, ULONG* pulSize);

    description:

        This function is called to retrieve string parameter value;

    argument:   ANSC_HANDLE                 hInsContext,
                The instance handle;

                char*                       ParamName,
                The parameter name;

                char*                       pValue,
                The string value buffer;

                ULONG*                      pUlSize
                The buffer of length of string value;
                Usually size of 1023 will be used.
                If it's not big enough, put required size here and return 1;

    return:     0 if succeeded;
                1 if short of buffer size; (*pUlSize = required size)
                -1 if not supported.

**********************************************************************/

ULONG TelcoVoiceMgrDml_CallControl_CallingFeatures_SetList_SCFList_GetParamStringValue(ANSC_HANDLE hInsContext, char* ParamName, char* pValue, ULONG* pulSize)
{
    ULONG ret = 1;

    if(ParamName == NULL || pValue == NULL || pulSize == NULL)
    {
        CcspTraceWarning(("%s: Invalid Input Parameter [NULL]\n", __func__));
        return ret;
    }

    TELCOVOICEMGR_LOCK_OR_EXIT()

    PDML_CALLCONTROL_CALLINGFEATURES_SET_SCF_CTRL_T pCallCtrlCFSetSCFCtrl = (PDML_CALLCONTROL_CALLINGFEATURES_SET_SCF_CTRL_T)hInsContext;

    PDML_CALLCONTROL_CALLINGFEATURES_SET_SCF pHEAD = &(pCallCtrlCFSetSCFCtrl->dml);

    if (strcmp(ParamName, "ForwardedToNumber") == 0)
    {
        AnscCopyString(pValue,pHEAD->ForwardedToNumber);
        ret = 0;
    }
    else if (strcmp(ParamName, "CallingNumber") == 0)
    {
        AnscCopyString(pValue,pHEAD->CallingNumber);
        ret = 0;
    }
    else if (strcmp(ParamName, "Alias") == 0)
    {
        AnscCopyString(pValue,pHEAD->Alias);
        ret = 0;
    }
    else
    {
        CcspTraceWarning(("%s: Unsupported parameter '%s'\n", __func__,ParamName));
    }

    TELCOVOICEMGR_UNLOCK()

    return ret;
}

/**********************************************************************

    caller:     owner of this object

    prototype:

        BOOL TelcoVoiceMgrDml_CallControl_CallingFeatures_SetList_SCFList_SetParamStringValue(ANSC_HANDLE hInsContext, char* ParamName, char* pString);

    description:

        This function is called to set string parameter value;

    argument:   ANSC_HANDLE                 hInsContext,
                The instance handle;

                char*                       ParamName,
                The parameter name;

                char*                       pString
                The updated string value;

    return:     TRUE if succeeded.

**********************************************************************/

BOOL TelcoVoiceMgrDml_CallControl_CallingFeatures_SetList_SCFList_SetParamStringValue(ANSC_HANDLE hInsContext, char* ParamName, char* pString)
{
    BOOL ret = FALSE;
    ULONG uVsIndex  = 0;
    ULONG uSetIndex = 0;
    ULONG uSCFIndex = 0;
    char HalName[MAX_STR_LEN] = {0};

    PTELCOVOICEMGR_DML_VOICESERVICE pDmlVoiceService = NULL;

    PDML_CALLCONTROL_CALLINGFEATURES_SET pDmlSet = NULL;

    if(ParamName == NULL)
    {
        CcspTraceWarning(("%s: Invalid Input Parameter [NULL]\n", __func__));
        return ret;
    }

    TELCOVOICEMGR_LOCK_OR_EXIT()

    PDML_CALLCONTROL_CALLINGFEATURES_SET_SCF_CTRL_T pCallCtrlCFSetCFLCtrl = (PDML_CALLCONTROL_CALLINGFEATURES_SET_SCF_CTRL_T)hInsContext;

    PDML_CALLCONTROL_CALLINGFEATURES_SET_SCF pHEAD = &(pCallCtrlCFSetCFLCtrl->dml);

    if(pHEAD != NULL)
    {
        pDmlSet = (PDML_CALLCONTROL_CALLINGFEATURES_SET)pHEAD->pParentCallCtrlSet;
    }

    if(pDmlSet != NULL)
    {
        pDmlVoiceService = (PTELCOVOICEMGR_DML_VOICESERVICE)pDmlSet->pParentVoiceService;
    }

    if (pHEAD == NULL  || pDmlSet == NULL || pDmlVoiceService == NULL)
    {
        TELCOVOICEMGR_UNLOCK()

        CcspTraceError(("%s:%d:: pHEAD or pDmlSet or pDmlVoiceService NULL\n", __FUNCTION__, __LINE__));

        return ret;
    }

    uVsIndex = pDmlVoiceService->InstanceNumber;

    uSetIndex = pDmlSet->uInstanceNumber;

    uSCFIndex = pHEAD->uInstanceNumber;

    TELCOVOICEMGR_UNLOCK()

    if (strcmp(ParamName, "ForwardedToNumber") == 0)
    {
        snprintf(HalName, MAX_STR_LEN, "Device.Services.VoiceService.%d.CallControl.CallingFeatures.Set.%d.SCF.%d.ForwardedToNumber",uVsIndex,uSetIndex,uSCFIndex);

        if (TelcoVoiceMgrHal_SetParamString(HalName,pString) == ANSC_STATUS_SUCCESS)
        {
            TELCOVOICEMGR_LOCK_OR_EXIT()

            AnscCopyString(pHEAD->ForwardedToNumber,pString);

            TELCOVOICEMGR_UNLOCK()

            ret = TRUE;
        }
    }
    else if (strcmp(ParamName, "CallingNumber") == 0)
    {
        snprintf(HalName, MAX_STR_LEN, "Device.Services.VoiceService.%d.CallControl.CallingFeatures.Set.%d.SCF.%d.CallingNumber",uVsIndex,uSetIndex,uSCFIndex);

        if (TelcoVoiceMgrHal_SetParamString(HalName,pString) == ANSC_STATUS_SUCCESS)
        {
            TELCOVOICEMGR_LOCK_OR_EXIT()

            AnscCopyString(pHEAD->CallingNumber,pString);

            TELCOVOICEMGR_UNLOCK()

            ret = TRUE;
        }
    }
    else if (strcmp(ParamName, "Alias") == 0)
    {
        TELCOVOICEMGR_LOCK_OR_EXIT()

        AnscCopyString(pHEAD->Alias,pString);

        TELCOVOICEMGR_UNLOCK()

        ret = TRUE;
    }

    else
    {
        CcspTraceWarning(("%s: Unsupported parameter '%s'\n", __func__,ParamName));
    }

    return ret;
}

/**********************************************************************

    caller:     owner of this object

    prototype:

        BOOL TelcoVoiceMgrDml_CallControl_CallingFeatures_SetList_SCFList_GetParamBoolValue(ANSC_HANDLE hInsContext, char* ParamName, BOOL* pBool);

    description:

        This function is called to retrieve Boolean parameter value;

    argument:   ANSC_HANDLE                 hInsContext,
                The instance handle;

                char*                       ParamName,
                The parameter name;

                BOOL*                       pBool
                The buffer of returned boolean value;

    return:     TRUE if succeeded.

**********************************************************************/

BOOL TelcoVoiceMgrDml_CallControl_CallingFeatures_SetList_SCFList_GetParamBoolValue(ANSC_HANDLE hInsContext, char* ParamName, BOOL* pBool)
{
    BOOL ret = FALSE;

    if(ParamName == NULL || pBool == NULL)
    {
        CcspTraceWarning(("%s: Invalid Input Parameter [NULL]\n", __func__));
        return ret;
    }

    TELCOVOICEMGR_LOCK_OR_EXIT()

    PDML_CALLCONTROL_CALLINGFEATURES_SET_SCF_CTRL_T pCallCtrlCFSetSCFCtrl = (PDML_CALLCONTROL_CALLINGFEATURES_SET_SCF_CTRL_T)hInsContext;

    PDML_CALLCONTROL_CALLINGFEATURES_SET_SCF pHEAD = &(pCallCtrlCFSetSCFCtrl->dml);

    if (strcmp(ParamName, "Enable") == 0)
    {
        *pBool = pHEAD->Enable;
        ret = TRUE;
    }
    else
    {
        CcspTraceWarning(("%s: Unsupported parameter '%s'\n", __func__,ParamName));
    }

    TELCOVOICEMGR_UNLOCK()

    return ret;
}

/**********************************************************************

    caller:     owner of this object

    prototype:

        BOOL TelcoVoiceMgrDml_CallControl_CallingFeatures_SetList_SCFList_SetParamBoolValue(ANSC_HANDLE hInsContext, char* ParamName, BOOL bValue);

    description:

        This function is called to set BOOL parameter value;

    argument:   ANSC_HANDLE                 hInsContext,
                The instance handle;

                char*                       ParamName,
                The parameter name;

                BOOL                        bValue
                The updated BOOL value;

    return:     TRUE if succeeded.

**********************************************************************/

BOOL TelcoVoiceMgrDml_CallControl_CallingFeatures_SetList_SCFList_SetParamBoolValue(ANSC_HANDLE hInsContext, char* ParamName, BOOL bValue)
{
    BOOL ret = FALSE;
    ULONG uVsIndex  = 0;
    ULONG uSetIndex = 0;
    ULONG uSCFIndex = 0;
    char HalName[MAX_STR_LEN] = {0};

    PTELCOVOICEMGR_DML_VOICESERVICE pDmlVoiceService = NULL;

    PDML_CALLCONTROL_CALLINGFEATURES_SET pDmlSet = NULL;

    if(ParamName == NULL)
    {
        CcspTraceWarning(("%s: Invalid Input Parameter [NULL]\n", __func__));
        return ret;
    }

    TELCOVOICEMGR_LOCK_OR_EXIT()

    PDML_CALLCONTROL_CALLINGFEATURES_SET_SCF_CTRL_T pCallCtrlCFSetCFLCtrl = (PDML_CALLCONTROL_CALLINGFEATURES_SET_SCF_CTRL_T)hInsContext;

    PDML_CALLCONTROL_CALLINGFEATURES_SET_SCF pHEAD = &(pCallCtrlCFSetCFLCtrl->dml);

    if(pHEAD != NULL)
    {
        pDmlSet = (PDML_CALLCONTROL_CALLINGFEATURES_SET)pHEAD->pParentCallCtrlSet;
    }

    if(pDmlSet != NULL)
    {
        pDmlVoiceService = (PTELCOVOICEMGR_DML_VOICESERVICE)pDmlSet->pParentVoiceService;
    }

    if (pHEAD == NULL  || pDmlSet == NULL || pDmlVoiceService == NULL)
    {
        TELCOVOICEMGR_UNLOCK()

        CcspTraceError(("%s:%d:: pHEAD or pDmlSet or pDmlVoiceService NULL\n", __FUNCTION__, __LINE__));

        return ret;
    }

    uVsIndex = pDmlVoiceService->InstanceNumber;

    uSetIndex = pDmlSet->uInstanceNumber;

    uSCFIndex = pHEAD->uInstanceNumber;

    TELCOVOICEMGR_UNLOCK()

    if (strcmp(ParamName, "Enable") == 0)
    {
        snprintf(HalName, MAX_STR_LEN, "Device.Services.VoiceService.%d.CallControl.CallingFeatures.Set.%d.SCF.%d.Enable",uVsIndex,uSetIndex,uSCFIndex);

        if (TelcoVoiceMgrHal_SetParamBool(HalName,bValue) == ANSC_STATUS_SUCCESS)
        {
            TELCOVOICEMGR_LOCK_OR_EXIT()

            pHEAD->Enable = bValue;

            TELCOVOICEMGR_UNLOCK()

            ret = TRUE;
        }
    }
    else
    {
        CcspTraceWarning(("%s: Unsupported parameter '%s'\n", __func__,ParamName));
    }

    return ret;
}

/**********************************************************************

    caller:     owner of this object

    prototype:

        BOOL TelcoVoiceMgrDml_CallControl_CallingFeatures_SetList_SCFList_Validate(ANSC_HANDLE hInsContext);

    description:

        This function is called to validate the update.

    argument:   ANSC_HANDLE                 hInsContext,
                The instance handle;

    return:     TRUE if there's no issue.

**********************************************************************/

BOOL TelcoVoiceMgrDml_CallControl_CallingFeatures_SetList_SCFList_Validate(ANSC_HANDLE hInsContext)
{
    return TRUE;
}

/**********************************************************************

    caller:     owner of this object

    prototype:

        BOOL TelcoVoiceMgrDml_CallControl_CallingFeatures_SetList_SCFList_Commit(ANSC_HANDLE hInsContext);

    description:

        This function is called to commit the update.

    argument:   ANSC_HANDLE                 hInsContext,
                The instance handle;

    return:     0 if there's no issue.

**********************************************************************/

BOOL TelcoVoiceMgrDml_CallControl_CallingFeatures_SetList_SCFList_Commit(ANSC_HANDLE hInsContext)
{
    return 0;
}

/**********************************************************************

    caller:     owner of this object

    prototype:

        BOOL TelcoVoiceMgrDml_CallControl_CallingFeatures_SetList_SCFList_Rollback(ANSC_HANDLE hInsContext);

    description:

        This function is called to rollback the update.

    argument:   ANSC_HANDLE                 hInsContext,
                The instance handle;

    return:     0 if there's no issue.

**********************************************************************/

BOOL TelcoVoiceMgrDml_CallControl_CallingFeatures_SetList_SCFList_Rollback(ANSC_HANDLE hInsContext)
{
    return 0;
}

/**********************************************************************

    caller:     owner of this object

    prototype:

        BOOL TelcoVoiceMgrDml_CallControl_CallingFeatures_SetList_SCREJList_IsUpdated(ANSC_HANDLE hInsContext);

    description:

        This function is checking whether the table is updated or not.

    argument:   ANSC_HANDLE                 hInsContext,
                The instance handle;

    return:     TRUE or FALSE.

**********************************************************************/

BOOL TelcoVoiceMgrDml_CallControl_CallingFeatures_SetList_SCREJList_IsUpdated(ANSC_HANDLE hInsContext)
{
    return TRUE;
}

/**********************************************************************

    caller:     owner of this object

    prototype:

        ULONG TelcoVoiceMgrDml_CallControl_CallingFeatures_SetList_SCREJList_Synchronize(ANSC_HANDLE hInsContext);

    description:

        This function is called to synchronize the table.

    argument:   ANSC_HANDLE                 hInsContext,
                The instance handle;

    return:     The status of the operation.

**********************************************************************/

ULONG TelcoVoiceMgrDml_CallControl_CallingFeatures_SetList_SCREJList_Synchronize(ANSC_HANDLE hInsContext)
{
    return 0;
}

/**********************************************************************

    caller:     owner of this object

    prototype:

        ULONG TelcoVoiceMgrDml_CallControl_CallingFeatures_SetList_SCREJList_GetEntryCount(ANSC_HANDLE hInsContext);

    description:

        This function is called to retrieve the count of the table.

    argument:   ANSC_HANDLE                 hInsContext,
                The instance handle;

    return:     The count of the table

**********************************************************************/
ULONG TelcoVoiceMgrDml_CallControl_CallingFeatures_SetList_SCREJList_GetEntryCount(ANSC_HANDLE hInsContext)
{
    ULONG ret = 0;

    TELCOVOICEMGR_LOCK_OR_EXIT()

    DML_CALLCONTROL_CALLINGFEATURES_SET_CTRL_T* pCallFeaturesSetCtrl = (DML_CALLCONTROL_CALLINGFEATURES_SET_CTRL_T*) hInsContext;

    PDML_CALLCONTROL_CALLINGFEATURES_SET pDmlCallFeaturesSet = &(pCallFeaturesSetCtrl->dml);

    PDML_CALLCONTROL_CALLINGFEATURES_SET_SCREJ_LIST_T pCallFeaturesSeSCREJList = &(pDmlCallFeaturesSet->SCREJ);

    if(pCallFeaturesSeSCREJList != NULL)
    {
        ret = pCallFeaturesSeSCREJList->ulQuantity;
    }
    TELCOVOICEMGR_UNLOCK()

    return ret;
}

/**********************************************************************

    caller:     owner of this object

    prototype:

        ANSC_HANDLE TelcoVoiceMgrDml_CallControl_CallingFeatures_SetList_SCREJList_GetEntry(ANSC_HANDLE hInsContext, ULONG nIndex, ULONG* pInsNumber);

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
ANSC_HANDLE TelcoVoiceMgrDml_CallControl_CallingFeatures_SetList_SCREJList_GetEntry(ANSC_HANDLE hInsContext, ULONG nIndex, ULONG* pInsNumber)
{

    ANSC_HANDLE ret = NULL;

    TELCOVOICEMGR_LOCK_OR_EXIT()

    PDML_CALLCONTROL_CALLINGFEATURES_SET_CTRL_T pSetCtrl = (PDML_CALLCONTROL_CALLINGFEATURES_SET_CTRL_T) hInsContext;

    PDML_CALLCONTROL_CALLINGFEATURES_SET pDmlSet = &(pSetCtrl->dml);

    PDML_CALLCONTROL_CALLINGFEATURES_SET_SCREJ_LIST_T pSCREJList = &(pDmlSet->SCREJ);

    if(pSCREJList != NULL)
    {
        if(nIndex < pSCREJList->ulQuantity)
        {
            PDML_CALLCONTROL_CALLINGFEATURES_SET_SCREJ_CTRL_T pSCREJCtrl = pSCREJList->pdata[nIndex];
            if(pSCREJCtrl != NULL)
            {
               *pInsNumber = nIndex + 1;
               ret = (ANSC_HANDLE) pSCREJCtrl;
            }
        }
    }

    TELCOVOICEMGR_UNLOCK()

    return ret;
}

/**********************************************************************

    caller:     owner of this object

    prototype:

        ULONG TelcoVoiceMgrDml_CallControl_CallingFeatures_SetList_SCREJList_GetParamStringValue(ANSC_HANDLE hInsContext, char* ParamName, char* pValue, ULONG* pulSize);

    description:

        This function is called to retrieve string parameter value;

    argument:   ANSC_HANDLE                 hInsContext,
                The instance handle;

                char*                       ParamName,
                The parameter name;

                char*                       pValue,
                The string value buffer;

                ULONG*                      pUlSize
                The buffer of length of string value;
                Usually size of 1023 will be used.
                If it's not big enough, put required size here and return 1;

    return:     0 if succeeded;
                1 if short of buffer size; (*pUlSize = required size)
                -1 if not supported.

**********************************************************************/

ULONG TelcoVoiceMgrDml_CallControl_CallingFeatures_SetList_SCREJList_GetParamStringValue(ANSC_HANDLE hInsContext, char* ParamName, char* pValue, ULONG* pulSize)
{
    ULONG ret = 1;

    if(ParamName == NULL || pValue == NULL || pulSize == NULL)
    {
        CcspTraceWarning(("%s: Invalid Input Parameter [NULL]\n", __func__));
        return ret;
    }

    TELCOVOICEMGR_LOCK_OR_EXIT()

    PDML_CALLCONTROL_CALLINGFEATURES_SET_SCREJ_CTRL_T pCallCtrlCFSetSCFCtrl = (PDML_CALLCONTROL_CALLINGFEATURES_SET_SCREJ_CTRL_T)hInsContext;

    PDML_CALLCONTROL_CALLINGFEATURES_SET_SCREJ pHEAD = &(pCallCtrlCFSetSCFCtrl->dml);

    if (strcmp(ParamName, "CallingNumber") == 0)
    {
        AnscCopyString(pValue,pHEAD->CallingNumber);
        ret = 0;
    }
    else if (strcmp(ParamName, "Alias") == 0)
    {
        AnscCopyString(pValue,pHEAD->Alias);
        ret = 0;
    }
    else
    {
        CcspTraceWarning(("%s: Unsupported parameter '%s'\n", __func__,ParamName));
    }

    TELCOVOICEMGR_UNLOCK()

    return ret;
}

/**********************************************************************

    caller:     owner of this object

    prototype:

        BOOL TelcoVoiceMgrDml_CallControl_CallingFeatures_SetList_SCREJList_SetParamStringValue(ANSC_HANDLE hInsContext, char* ParamName, char* pString);

    description:

        This function is called to set string parameter value;

    argument:   ANSC_HANDLE                 hInsContext,
                The instance handle;

                char*                       ParamName,
                The parameter name;

                char*                       pString
                The updated string value;

    return:     TRUE if succeeded.

**********************************************************************/

BOOL TelcoVoiceMgrDml_CallControl_CallingFeatures_SetList_SCREJList_SetParamStringValue(ANSC_HANDLE hInsContext, char* ParamName, char* pString)
{
    BOOL ret = FALSE;
    ULONG uVsIndex  = 0;
    ULONG uSetIndex = 0;
    ULONG uSCREJIndex = 0;
    char HalName[MAX_STR_LEN] = {0};

    PTELCOVOICEMGR_DML_VOICESERVICE pDmlVoiceService = NULL;

    PDML_CALLCONTROL_CALLINGFEATURES_SET pDmlSet = NULL;

    if(ParamName == NULL)
    {
        CcspTraceWarning(("%s: Invalid Input Parameter [NULL]\n", __func__));
        return ret;
    }

    TELCOVOICEMGR_LOCK_OR_EXIT()

    PDML_CALLCONTROL_CALLINGFEATURES_SET_SCREJ_CTRL_T pCallCtrlCFSetCFLCtrl = (PDML_CALLCONTROL_CALLINGFEATURES_SET_SCREJ_CTRL_T)hInsContext;

    PDML_CALLCONTROL_CALLINGFEATURES_SET_SCREJ pHEAD = &(pCallCtrlCFSetCFLCtrl->dml);

    if(pHEAD != NULL)
    {
        pDmlSet = (PDML_CALLCONTROL_CALLINGFEATURES_SET)pHEAD->pParentCallCtrlSet;
    }

    if(pDmlSet != NULL)
    {
        pDmlVoiceService = (PTELCOVOICEMGR_DML_VOICESERVICE)pDmlSet->pParentVoiceService;
    }

    if (pHEAD == NULL  || pDmlSet == NULL || pDmlVoiceService == NULL)
    {
        TELCOVOICEMGR_UNLOCK()

        CcspTraceError(("%s:%d:: pHEAD or pDmlSet or pDmlVoiceService NULL\n", __FUNCTION__, __LINE__));

        return ret;
    }

    uVsIndex = pDmlVoiceService->InstanceNumber;

    uSetIndex = pDmlSet->uInstanceNumber;

    uSCREJIndex = pHEAD->uInstanceNumber;

    TELCOVOICEMGR_UNLOCK()

    if (strcmp(ParamName, "CallingNumber") == 0)
    {
        snprintf(HalName, MAX_STR_LEN, "Device.Services.VoiceService.%d.CallControl.CallingFeatures.Set.%d.SCREJ.%d.CallingNumber",uVsIndex,uSetIndex,uSCREJIndex);

        if (TelcoVoiceMgrHal_SetParamString(HalName,pString) == ANSC_STATUS_SUCCESS)
        {
            TELCOVOICEMGR_LOCK_OR_EXIT()

            AnscCopyString(pHEAD->CallingNumber,pString);

            TELCOVOICEMGR_UNLOCK()

            ret = TRUE;
        }
    }
    else if (strcmp(ParamName, "Alias") == 0)
    {
        TELCOVOICEMGR_LOCK_OR_EXIT()

        AnscCopyString(pHEAD->Alias,pString);

        TELCOVOICEMGR_UNLOCK()

        ret = TRUE;
    }
    else
    {
        CcspTraceWarning(("%s: Unsupported parameter '%s'\n", __func__,ParamName));
    }

    return ret;
}

/**********************************************************************

    caller:     owner of this object

    prototype:

        BOOL TelcoVoiceMgrDml_CallControl_CallingFeatures_SetList_SCREJList_GetParamBoolValue(ANSC_HANDLE hInsContext, char* ParamName, BOOL* pBool);

    description:

        This function is called to retrieve Boolean parameter value;

    argument:   ANSC_HANDLE                 hInsContext,
                The instance handle;

                char*                       ParamName,
                The parameter name;

                BOOL*                       pBool
                The buffer of returned boolean value;

    return:     TRUE if succeeded.

**********************************************************************/

BOOL TelcoVoiceMgrDml_CallControl_CallingFeatures_SetList_SCREJList_GetParamBoolValue(ANSC_HANDLE hInsContext, char* ParamName, BOOL* pBool)
{
    BOOL ret = FALSE;

    if(ParamName == NULL || pBool == NULL)
    {
        CcspTraceWarning(("%s: Invalid Input Parameter [NULL]\n", __func__));
        return ret;
    }

    TELCOVOICEMGR_LOCK_OR_EXIT()

    PDML_CALLCONTROL_CALLINGFEATURES_SET_SCREJ_CTRL_T pCallCtrlCFSetSCFCtrl = (PDML_CALLCONTROL_CALLINGFEATURES_SET_SCREJ_CTRL_T)hInsContext;

    PDML_CALLCONTROL_CALLINGFEATURES_SET_SCREJ pHEAD = &(pCallCtrlCFSetSCFCtrl->dml);

    if (strcmp(ParamName, "Enable") == 0)
    {
        *pBool = pHEAD->Enable;
        ret = TRUE;
    }
    else
    {
        CcspTraceWarning(("%s: Unsupported parameter '%s'\n", __func__,ParamName));
    }

    TELCOVOICEMGR_UNLOCK()

    return ret;
}

/**********************************************************************

    caller:     owner of this object

    prototype:

        BOOL TelcoVoiceMgrDml_CallControl_CallingFeatures_SetList_SCREJList_SetParamBoolValue(ANSC_HANDLE hInsContext, char* ParamName, BOOL bValue);

    description:

        This function is called to set BOOL parameter value;

    argument:   ANSC_HANDLE                 hInsContext,
                The instance handle;

                char*                       ParamName,
                The parameter name;

                BOOL                        bValue
                The updated BOOL value;

    return:     TRUE if succeeded.

**********************************************************************/

BOOL TelcoVoiceMgrDml_CallControl_CallingFeatures_SetList_SCREJList_SetParamBoolValue(ANSC_HANDLE hInsContext, char* ParamName, BOOL bValue)
{
    BOOL ret = FALSE;
    ULONG uVsIndex  = 0;
    ULONG uSetIndex = 0;
    ULONG uSCREJIndex = 0;
    char HalName[MAX_STR_LEN] = {0};

    PTELCOVOICEMGR_DML_VOICESERVICE pDmlVoiceService = NULL;

    PDML_CALLCONTROL_CALLINGFEATURES_SET pDmlSet = NULL;

    if(ParamName == NULL)
    {
        CcspTraceWarning(("%s: Invalid Input Parameter [NULL]\n", __func__));
        return ret;
    }

    TELCOVOICEMGR_LOCK_OR_EXIT()

    PDML_CALLCONTROL_CALLINGFEATURES_SET_SCREJ_CTRL_T pCallCtrlCFSetCFLCtrl = (PDML_CALLCONTROL_CALLINGFEATURES_SET_SCREJ_CTRL_T)hInsContext;

    PDML_CALLCONTROL_CALLINGFEATURES_SET_SCREJ pHEAD = &(pCallCtrlCFSetCFLCtrl->dml);

    if(pHEAD != NULL)
    {
        pDmlSet = (PDML_CALLCONTROL_CALLINGFEATURES_SET)pHEAD->pParentCallCtrlSet;
    }

    if(pDmlSet != NULL)
    {
        pDmlVoiceService = (PTELCOVOICEMGR_DML_VOICESERVICE)pDmlSet->pParentVoiceService;
    }

    if (pHEAD == NULL  || pDmlSet == NULL || pDmlVoiceService == NULL)
    {
        TELCOVOICEMGR_UNLOCK()

        CcspTraceError(("%s:%d:: pHEAD or pDmlSet or pDmlVoiceService NULL\n", __FUNCTION__, __LINE__));

        return ret;
    }

    uVsIndex = pDmlVoiceService->InstanceNumber;

    uSetIndex = pDmlSet->uInstanceNumber;

    uSCREJIndex = pHEAD->uInstanceNumber;

    TELCOVOICEMGR_UNLOCK()

    if (strcmp(ParamName, "Enable") == 0)
    {
        snprintf(HalName, MAX_STR_LEN, "Device.Services.VoiceService.%d.CallControl.CallingFeatures.Set.%d.SCREJ.%d.Enable",uVsIndex,uSetIndex,uSCREJIndex);

        if (TelcoVoiceMgrHal_SetParamBool(HalName,bValue) == ANSC_STATUS_SUCCESS)
        {
            TELCOVOICEMGR_LOCK_OR_EXIT()

            pHEAD->Enable = bValue;

            TELCOVOICEMGR_UNLOCK()

            ret = TRUE;
        }
    }
    else
    {
        CcspTraceWarning(("%s: Unsupported parameter '%s'\n", __func__,ParamName));
    }

    return ret;
}

/**********************************************************************

    caller:     owner of this object

    prototype:

        BOOL TelcoVoiceMgrDml_CallControl_CallingFeatures_SetList_SCREJList_Validate(ANSC_HANDLE hInsContext);

    description:

        This function is called to validate the update.

    argument:   ANSC_HANDLE                 hInsContext,
                The instance handle;

    return:     TRUE if there's no issue.

**********************************************************************/

BOOL TelcoVoiceMgrDml_CallControl_CallingFeatures_SetList_SCREJList_Validate(ANSC_HANDLE hInsContext)
{
    return TRUE;
}

/**********************************************************************

    caller:     owner of this object

    prototype:

        BOOL TelcoVoiceMgrDml_CallControl_CallingFeatures_SetList_SCREJList_Commit(ANSC_HANDLE hInsContext);

    description:

        This function is called to commit the update.

    argument:   ANSC_HANDLE                 hInsContext,
                The instance handle;

    return:     0 if there's no issue.

**********************************************************************/

BOOL TelcoVoiceMgrDml_CallControl_CallingFeatures_SetList_SCREJList_Commit(ANSC_HANDLE hInsContext)
{
    return 0;
}

/**********************************************************************

    caller:     owner of this object

    prototype:

        BOOL TelcoVoiceMgrDml_CallControl_CallingFeatures_SetList_SCREJList_Rollback(ANSC_HANDLE hInsContext);

    description:

        This function is called to rollback the update.

    argument:   ANSC_HANDLE                 hInsContext,
                The instance handle;

    return:     0 if there's no issue.

**********************************************************************/

BOOL TelcoVoiceMgrDml_CallControl_CallingFeatures_SetList_SCREJList_Rollback(ANSC_HANDLE hInsContext)
{
    return 0;
}

/**********************************************************************

    caller:     owner of this object

    prototype:

        BOOL TelcoVoiceMgrDml_CallControl_CallingFeatures_SetList_FollowMeList_IsUpdated(ANSC_HANDLE hInsContext);

    description:

        This function is checking whether the table is updated or not.

    argument:   ANSC_HANDLE                 hInsContext,
                The instance handle;

    return:     TRUE or FALSE.

**********************************************************************/

BOOL TelcoVoiceMgrDml_CallControl_CallingFeatures_SetList_FollowMeList_IsUpdated(ANSC_HANDLE hInsContext)
{
    return TRUE;
}

/**********************************************************************

    caller:     owner of this object

    prototype:

        ULONG TelcoVoiceMgrDml_CallControl_CallingFeatures_SetList_FollowMeList_Synchronize(ANSC_HANDLE hInsContext);

    description:

        This function is called to synchronize the table.

    argument:   ANSC_HANDLE                 hInsContext,
                The instance handle;

    return:     The status of the operation.

**********************************************************************/

ULONG TelcoVoiceMgrDml_CallControl_CallingFeatures_SetList_FollowMeList_Synchronize(ANSC_HANDLE hInsContext)
{
    return 0;
}

/**********************************************************************

    caller:     owner of this object

    prototype:

        ULONG TelcoVoiceMgrDml_CallControl_CallingFeatures_SetList_FollowMeList_GetEntryCount(ANSC_HANDLE hInsContext);

    description:

        This function is called to retrieve the count of the table.

    argument:   ANSC_HANDLE                 hInsContext,
                The instance handle;

    return:     The count of the table

**********************************************************************/
ULONG TelcoVoiceMgrDml_CallControl_CallingFeatures_SetList_FollowMeList_GetEntryCount(ANSC_HANDLE hInsContext)
{
    ULONG ret = 0;

    TELCOVOICEMGR_LOCK_OR_EXIT()

    DML_CALLCONTROL_CALLINGFEATURES_SET_CTRL_T* pCallFeaturesSetCtrl = (DML_CALLCONTROL_CALLINGFEATURES_SET_CTRL_T*) hInsContext;

    PDML_CALLCONTROL_CALLINGFEATURES_SET pDmlCallFeaturesSet = &(pCallFeaturesSetCtrl->dml);

    PDML_CALLCONTROL_CALLINGFEATURES_SET_FOLLOWME_LIST_T pCallFeaturesSetFMList = &(pDmlCallFeaturesSet->FollowMe);

    if(pCallFeaturesSetFMList != NULL)
    {
        ret = pCallFeaturesSetFMList->ulQuantity;
    }
    TELCOVOICEMGR_UNLOCK()

    return ret;
}

/**********************************************************************

    caller:     owner of this object

    prototype:

        ANSC_HANDLE TelcoVoiceMgrDml_CallControl_CallingFeatures_SetList_FollowMeList_GetEntry(ANSC_HANDLE hInsContext, ULONG nIndex, ULONG* pInsNumber);

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
ANSC_HANDLE TelcoVoiceMgrDml_CallControl_CallingFeatures_SetList_FollowMeList_GetEntry(ANSC_HANDLE hInsContext, ULONG nIndex, ULONG* pInsNumber)
{

    ANSC_HANDLE ret = NULL;

    TELCOVOICEMGR_LOCK_OR_EXIT()

    PDML_CALLCONTROL_CALLINGFEATURES_SET_CTRL_T pSetCtrl = (PDML_CALLCONTROL_CALLINGFEATURES_SET_CTRL_T) hInsContext;

    PDML_CALLCONTROL_CALLINGFEATURES_SET pDmlSet = &(pSetCtrl->dml);

    PDML_CALLCONTROL_CALLINGFEATURES_SET_FOLLOWME_LIST_T pFollowMeList = &(pDmlSet->FollowMe);

    if(pFollowMeList != NULL)
    {
        if(nIndex < pFollowMeList->ulQuantity)
        {
            PDML_CALLCONTROL_CALLINGFEATURES_SET_FOLLOWME_CTRL_T pFollowMeCtrl = pFollowMeList->pdata[nIndex];
            if(pFollowMeCtrl != NULL)
            {
               *pInsNumber = nIndex + 1;
               ret = (ANSC_HANDLE) pFollowMeCtrl;
            }
        }
    }

    TELCOVOICEMGR_UNLOCK()

    return ret;
}

/**********************************************************************

    caller:     owner of this object

    prototype:

        BOOL TelcoVoiceMgrDml_CallControl_CallingFeatures_SetList_FollowMeList_GetParamUlongValue(ANSC_HANDLE hInsContext, char* ParamName, ULONG* puLong);

    description:

        This function is called to retrieve ULONG parameter value;

    argument:   ANSC_HANDLE                 hInsContext,
                The instance handle;

                char*                       ParamName,
                The parameter name;

                ULONG*                      puLong
                The buffer of returned ULONG value;

    return:     TRUE if succeeded.

**********************************************************************/

BOOL TelcoVoiceMgrDml_CallControl_CallingFeatures_SetList_FollowMeList_GetParamUlongValue(ANSC_HANDLE hInsContext, char* ParamName, ULONG* puLong)
{
    BOOL ret = FALSE;

    if(ParamName == NULL || puLong == NULL)
    {
        CcspTraceWarning(("%s: Invalid Input Parameter [NULL]\n", __func__));
        return ret;
    }

    TELCOVOICEMGR_LOCK_OR_EXIT()

    PDML_CALLCONTROL_CALLINGFEATURES_SET_FOLLOWME_CTRL_T pCallCtrlCFSetFMCtrl = (PDML_CALLCONTROL_CALLINGFEATURES_SET_FOLLOWME_CTRL_T)hInsContext;

    PDML_CALLCONTROL_CALLINGFEATURES_SET_FOLLOWME pHEAD = &(pCallCtrlCFSetFMCtrl->dml);

    if (strcmp(ParamName, "Order") == 0)
    {
        *puLong = pHEAD->Order;
        ret = TRUE;
    }
    else if (strcmp(ParamName, "Delay") == 0)
    {
        *puLong = pHEAD->Delay;
        ret = TRUE;
    }
    else
    {
        CcspTraceWarning(("%s: Unsupported parameter '%s'\n", __func__,ParamName));
    }

    TELCOVOICEMGR_UNLOCK()

    return ret;
}

/**********************************************************************

    caller:     owner of this object

    prototype:

        BOOL TelcoVoiceMgrDml_CallControl_CallingFeatures_SetList_FollowMeList_SetParamUlongValue(ANSC_HANDLE hInsContext, char* ParamName, ULONG uValue);

    description:

        This function is called to set ULONG parameter value;

    argument:   ANSC_HANDLE                 hInsContext,
                The instance handle;

                char*                       ParamName,
                The parameter name;

                ULONG                       uValue
                The updated ULONG value;

    return:     TRUE if succeeded.

**********************************************************************/

BOOL TelcoVoiceMgrDml_CallControl_CallingFeatures_SetList_FollowMeList_SetParamUlongValue(ANSC_HANDLE hInsContext, char* ParamName, ULONG uValue)
{
    BOOL ret = FALSE;
    ULONG uVsIndex  = 0;
    ULONG uSetIndex = 0;
    ULONG uFollowMeIndex = 0;
    char HalName[MAX_STR_LEN] = {0};

    PTELCOVOICEMGR_DML_VOICESERVICE pDmlVoiceService = NULL;

    PDML_CALLCONTROL_CALLINGFEATURES_SET pDmlSet = NULL;

    if(ParamName == NULL)
    {
        CcspTraceWarning(("%s: Invalid Input Parameter [NULL]\n", __func__));
        return ret;
    }

    TELCOVOICEMGR_LOCK_OR_EXIT()

    PDML_CALLCONTROL_CALLINGFEATURES_SET_FOLLOWME_CTRL_T pCallCtrlCFSetFMCtrl = (PDML_CALLCONTROL_CALLINGFEATURES_SET_FOLLOWME_CTRL_T)hInsContext;

    PDML_CALLCONTROL_CALLINGFEATURES_SET_FOLLOWME pHEAD = &(pCallCtrlCFSetFMCtrl->dml);

    if(pHEAD != NULL)
    {
        pDmlSet = (PDML_CALLCONTROL_CALLINGFEATURES_SET)pHEAD->pParentCallCtrlSet;
    }

    if(pDmlSet != NULL)
    {
        pDmlVoiceService = (PTELCOVOICEMGR_DML_VOICESERVICE)pDmlSet->pParentVoiceService;
    }

    if (pHEAD == NULL  || pDmlSet == NULL || pDmlVoiceService == NULL)
    {
        TELCOVOICEMGR_UNLOCK()

        CcspTraceError(("%s:%d:: pHEAD or pDmlSet or pDmlVoiceService NULL\n", __FUNCTION__, __LINE__));

        return ret;
    }

    uVsIndex = pDmlVoiceService->InstanceNumber;

    uSetIndex = pDmlSet->uInstanceNumber;

    uFollowMeIndex = pHEAD->uInstanceNumber;

    TELCOVOICEMGR_UNLOCK()

    if (strcmp(ParamName, "Order") == 0)
    {
        snprintf(HalName, MAX_STR_LEN, "Device.Services.VoiceService.%d.CallControl.CallingFeatures.Set.%d.FollowMe.%d.Order",uVsIndex,uSetIndex,uFollowMeIndex);

        if (TelcoVoiceMgrHal_SetParamULong(HalName,uValue) == ANSC_STATUS_SUCCESS)
        {
            TELCOVOICEMGR_LOCK_OR_EXIT()

            pHEAD->Order = uValue;

            TELCOVOICEMGR_UNLOCK()

            ret = TRUE;
        }
    }
    else if (strcmp(ParamName, "Delay") == 0)
    {
        snprintf(HalName, MAX_STR_LEN, "Device.Services.VoiceService.%d.CallControl.CallingFeatures.Set.%d.FollowMe.%d.Delay",uVsIndex,uSetIndex,uFollowMeIndex);

        if (TelcoVoiceMgrHal_SetParamULong(HalName,uValue) == ANSC_STATUS_SUCCESS)
        {
            TELCOVOICEMGR_LOCK_OR_EXIT()

            pHEAD->Delay = uValue;

            TELCOVOICEMGR_UNLOCK()

            ret = TRUE;
        }
    }
    else
    {
        CcspTraceWarning(("%s: Unsupported parameter '%s'\n", __func__,ParamName));
    }

    return ret;
}

/**********************************************************************

    caller:     owner of this object

    prototype:

        ULONG TelcoVoiceMgrDml_CallControl_CallingFeatures_SetList_FollowMeList_GetParamStringValue(ANSC_HANDLE hInsContext, char* ParamName, char* pValue, ULONG* pulSize);

    description:

        This function is called to retrieve string parameter value;

    argument:   ANSC_HANDLE                 hInsContext,
                The instance handle;

                char*                       ParamName,
                The parameter name;

                char*                       pValue,
                The string value buffer;

                ULONG*                      pUlSize
                The buffer of length of string value;
                Usually size of 1023 will be used.
                If it's not big enough, put required size here and return 1;

    return:     0 if succeeded;
                1 if short of buffer size; (*pUlSize = required size)
                -1 if not supported.

**********************************************************************/

ULONG TelcoVoiceMgrDml_CallControl_CallingFeatures_SetList_FollowMeList_GetParamStringValue(ANSC_HANDLE hInsContext, char* ParamName, char* pValue, ULONG* pulSize)
{
    ULONG ret = 1;

    if(ParamName == NULL || pValue == NULL || pulSize == NULL)
    {
        CcspTraceWarning(("%s: Invalid Input Parameter [NULL]\n", __func__));
        return ret;
    }

    TELCOVOICEMGR_LOCK_OR_EXIT()

    PDML_CALLCONTROL_CALLINGFEATURES_SET_FOLLOWME_CTRL_T pCallCtrlCFSetFMCtrl = (PDML_CALLCONTROL_CALLINGFEATURES_SET_FOLLOWME_CTRL_T)hInsContext;

    PDML_CALLCONTROL_CALLINGFEATURES_SET_FOLLOWME pHEAD = &(pCallCtrlCFSetFMCtrl->dml);

    if (strcmp(ParamName, "Number") == 0)
    {
        AnscCopyString(pValue,pHEAD->Number);
        ret = 0;
    }
    else if (strcmp(ParamName, "Alias") == 0)
    {
        AnscCopyString(pValue,pHEAD->Alias);
        ret = 0;
    }
    else
    {
        CcspTraceWarning(("%s: Unsupported parameter '%s'\n", __func__,ParamName));
    }

    TELCOVOICEMGR_UNLOCK()

    return ret;
}

/**********************************************************************

    caller:     owner of this object

    prototype:

        BOOL TelcoVoiceMgrDml_CallControl_CallingFeatures_SetList_FollowMeList_SetParamStringValue(ANSC_HANDLE hInsContext, char* ParamName, char* pString);

    description:

        This function is called to set string parameter value;

    argument:   ANSC_HANDLE                 hInsContext,
                The instance handle;

                char*                       ParamName,
                The parameter name;

                char*                       pString
                The updated string value;

    return:     TRUE if succeeded.

**********************************************************************/

BOOL TelcoVoiceMgrDml_CallControl_CallingFeatures_SetList_FollowMeList_SetParamStringValue(ANSC_HANDLE hInsContext, char* ParamName, char* pString)
{
    BOOL ret = FALSE;
    ULONG uVsIndex  = 0;
    ULONG uSetIndex = 0;
    ULONG uFollowMeIndex = 0;
    char HalName[MAX_STR_LEN] = {0};

    PTELCOVOICEMGR_DML_VOICESERVICE pDmlVoiceService = NULL;

    PDML_CALLCONTROL_CALLINGFEATURES_SET pDmlSet = NULL;

    if(ParamName == NULL)
    {
        CcspTraceWarning(("%s: Invalid Input Parameter [NULL]\n", __func__));
        return ret;
    }

    TELCOVOICEMGR_LOCK_OR_EXIT()

    PDML_CALLCONTROL_CALLINGFEATURES_SET_FOLLOWME_CTRL_T pCallCtrlCFSetFMCtrl = (PDML_CALLCONTROL_CALLINGFEATURES_SET_FOLLOWME_CTRL_T)hInsContext;

    PDML_CALLCONTROL_CALLINGFEATURES_SET_FOLLOWME pHEAD = &(pCallCtrlCFSetFMCtrl->dml);

    if(pHEAD != NULL)
    {
        pDmlSet = (PDML_CALLCONTROL_CALLINGFEATURES_SET)pHEAD->pParentCallCtrlSet;
    }

    if(pDmlSet != NULL)
    {
        pDmlVoiceService = (PTELCOVOICEMGR_DML_VOICESERVICE)pDmlSet->pParentVoiceService;
    }

    if (pHEAD == NULL  || pDmlSet == NULL || pDmlVoiceService == NULL)
    {
        TELCOVOICEMGR_UNLOCK()

        CcspTraceError(("%s:%d:: pHEAD or pDmlSet or pDmlVoiceService NULL\n", __FUNCTION__, __LINE__));

        return ret;
    }

    uVsIndex = pDmlVoiceService->InstanceNumber;

    uSetIndex = pDmlSet->uInstanceNumber;

    uFollowMeIndex = pHEAD->uInstanceNumber;

    TELCOVOICEMGR_UNLOCK()

    if (strcmp(ParamName, "Number") == 0)
    {
        snprintf(HalName, MAX_STR_LEN, "Device.Services.VoiceService.%d.CallControl.CallingFeatures.Set.%d.FollowMe.%d.Number",uVsIndex,uSetIndex,uFollowMeIndex);

        if (TelcoVoiceMgrHal_SetParamString(HalName,pString) == ANSC_STATUS_SUCCESS)
        {
            TELCOVOICEMGR_LOCK_OR_EXIT()

            AnscCopyString(pHEAD->Number,pString);

            TELCOVOICEMGR_UNLOCK()

            ret = TRUE;
        }
    }
    else if (strcmp(ParamName, "Alias") == 0)
    {
        TELCOVOICEMGR_LOCK_OR_EXIT()

        AnscCopyString(pHEAD->Alias,pString);

        TELCOVOICEMGR_UNLOCK()

        ret = TRUE;
    }
    else
    {
        CcspTraceWarning(("%s: Unsupported parameter '%s'\n", __func__,ParamName));
    }

    return ret;
}

/**********************************************************************

    caller:     owner of this object

    prototype:

        BOOL TelcoVoiceMgrDml_CallControl_CallingFeatures_SetList_FollowMeList_GetParamBoolValue(ANSC_HANDLE hInsContext, char* ParamName, BOOL* pBool);

    description:

        This function is called to retrieve Boolean parameter value;

    argument:   ANSC_HANDLE                 hInsContext,
                The instance handle;

                char*                       ParamName,
                The parameter name;

                BOOL*                       pBool
                The buffer of returned boolean value;

    return:     TRUE if succeeded.

**********************************************************************/

BOOL TelcoVoiceMgrDml_CallControl_CallingFeatures_SetList_FollowMeList_GetParamBoolValue(ANSC_HANDLE hInsContext, char* ParamName, BOOL* pBool)
{
    BOOL ret = FALSE;

    if(ParamName == NULL || pBool == NULL)
    {
        CcspTraceWarning(("%s: Invalid Input Parameter [NULL]\n", __func__));
        return ret;
    }

    TELCOVOICEMGR_LOCK_OR_EXIT()

    PDML_CALLCONTROL_CALLINGFEATURES_SET_FOLLOWME_CTRL_T pCallCtrlCFSetFMCtrl = (PDML_CALLCONTROL_CALLINGFEATURES_SET_FOLLOWME_CTRL_T)hInsContext;

    PDML_CALLCONTROL_CALLINGFEATURES_SET_FOLLOWME pHEAD = &(pCallCtrlCFSetFMCtrl->dml);

    if (strcmp(ParamName, "Enable") == 0)
    {
        *pBool = pHEAD->Enable;
        ret = TRUE;
    }
    else
    {
        CcspTraceWarning(("%s: Unsupported parameter '%s'\n", __func__,ParamName));
    }

    TELCOVOICEMGR_UNLOCK()

    return ret;
}

/**********************************************************************

    caller:     owner of this object

    prototype:

        BOOL TelcoVoiceMgrDml_CallControl_CallingFeatures_SetList_FollowMeList_SetParamBoolValue(ANSC_HANDLE hInsContext, char* ParamName, BOOL bValue);

    description:

        This function is called to set BOOL parameter value;

    argument:   ANSC_HANDLE                 hInsContext,
                The instance handle;

                char*                       ParamName,
                The parameter name;

                BOOL                        bValue
                The updated BOOL value;

    return:     TRUE if succeeded.

**********************************************************************/

BOOL TelcoVoiceMgrDml_CallControl_CallingFeatures_SetList_FollowMeList_SetParamBoolValue(ANSC_HANDLE hInsContext, char* ParamName, BOOL bValue)
{
    BOOL ret = FALSE;
    ULONG uVsIndex  = 0;
    ULONG uSetIndex = 0;
    ULONG uFollowMeIndex = 0;
    char HalName[MAX_STR_LEN] = {0};

    PTELCOVOICEMGR_DML_VOICESERVICE pDmlVoiceService = NULL;

    PDML_CALLCONTROL_CALLINGFEATURES_SET pDmlSet = NULL;

    if(ParamName == NULL)
    {
        CcspTraceWarning(("%s: Invalid Input Parameter [NULL]\n", __func__));
        return ret;
    }

    TELCOVOICEMGR_LOCK_OR_EXIT()

    PDML_CALLCONTROL_CALLINGFEATURES_SET_FOLLOWME_CTRL_T pCallCtrlCFSetFMCtrl = (PDML_CALLCONTROL_CALLINGFEATURES_SET_FOLLOWME_CTRL_T)hInsContext;

    PDML_CALLCONTROL_CALLINGFEATURES_SET_FOLLOWME pHEAD = &(pCallCtrlCFSetFMCtrl->dml);

    if(pHEAD != NULL)
    {
        pDmlSet = (PDML_CALLCONTROL_CALLINGFEATURES_SET)pHEAD->pParentCallCtrlSet;
    }

    if(pDmlSet != NULL)
    {
        pDmlVoiceService = (PTELCOVOICEMGR_DML_VOICESERVICE)pDmlSet->pParentVoiceService;
    }

    if (pHEAD == NULL  || pDmlSet == NULL || pDmlVoiceService == NULL)
    {
        TELCOVOICEMGR_UNLOCK()

        CcspTraceError(("%s:%d:: pHEAD or pDmlSet or pDmlVoiceService NULL\n", __FUNCTION__, __LINE__));

        return ret;
    }

    uVsIndex = pDmlVoiceService->InstanceNumber;

    uSetIndex = pDmlSet->uInstanceNumber;

    uFollowMeIndex = pHEAD->uInstanceNumber;

    TELCOVOICEMGR_UNLOCK()

    if (strcmp(ParamName, "Enable") == 0)
    {
        snprintf(HalName, MAX_STR_LEN, "Device.Services.VoiceService.%d.CallControl.CallingFeatures.Set.%d.FollowMe.%d.Enable",uVsIndex,uSetIndex,uFollowMeIndex);

        if (TelcoVoiceMgrHal_SetParamBool(HalName,bValue) == ANSC_STATUS_SUCCESS)
        {
            TELCOVOICEMGR_LOCK_OR_EXIT()

            pHEAD->Enable = bValue;

            TELCOVOICEMGR_UNLOCK()

            ret = TRUE;
        }
    }
    else
    {
        CcspTraceWarning(("%s: Unsupported parameter '%s'\n", __func__,ParamName));
    }

    return ret;
}

/**********************************************************************

    caller:     owner of this object

    prototype:

        BOOL TelcoVoiceMgrDml_CallControl_CallingFeatures_SetList_FollowMeList_Validate(ANSC_HANDLE hInsContext);

    description:

        This function is called to validate the update.

    argument:   ANSC_HANDLE                 hInsContext,
                The instance handle;

    return:     TRUE if there's no issue.

**********************************************************************/

BOOL TelcoVoiceMgrDml_CallControl_CallingFeatures_SetList_FollowMeList_Validate(ANSC_HANDLE hInsContext)
{
    return TRUE;
}

/**********************************************************************

    caller:     owner of this object

    prototype:

        BOOL TelcoVoiceMgrDml_CallControl_CallingFeatures_SetList_FollowMeList_Commit(ANSC_HANDLE hInsContext);

    description:

        This function is called to commit the update.

    argument:   ANSC_HANDLE                 hInsContext,
                The instance handle;

    return:     0 if there's no issue.

**********************************************************************/

BOOL TelcoVoiceMgrDml_CallControl_CallingFeatures_SetList_FollowMeList_Commit(ANSC_HANDLE hInsContext)
{
    return 0;
}

/**********************************************************************

    caller:     owner of this object

    prototype:

        BOOL TelcoVoiceMgrDml_CallControl_CallingFeatures_SetList_FollowMeList_Rollback(ANSC_HANDLE hInsContext);

    description:

        This function is called to rollback the update.

    argument:   ANSC_HANDLE                 hInsContext,
                The instance handle;

    return:     0 if there's no issue.

**********************************************************************/

BOOL TelcoVoiceMgrDml_CallControl_CallingFeatures_SetList_FollowMeList_Rollback(ANSC_HANDLE hInsContext)
{
    return 0;
}

/**********************************************************************

    caller:     owner of this object

    prototype:

        BOOL TelcoVoiceMgrDml_CallControl_CallingFeatures_SetList_Voice2Mail_GetParamUlongValue(ANSC_HANDLE hInsContext, char* ParamName, ULONG* puLong);

    description:

        This function is called to retrieve ULONG parameter value;

    argument:   ANSC_HANDLE                 hInsContext,
                The instance handle;

                char*                       ParamName,
                The parameter name;

                ULONG*                      puLong
                The buffer of returned ULONG value;

    return:     TRUE if succeeded.

**********************************************************************/

BOOL TelcoVoiceMgrDml_CallControl_CallingFeatures_SetList_Voice2Mail_GetParamUlongValue(ANSC_HANDLE hInsContext, char* ParamName, ULONG* puLong)
{
    BOOL ret = FALSE;

    if(ParamName == NULL || puLong == NULL)
    {
        CcspTraceWarning(("%s: Invalid Input Parameter [NULL]\n", __func__));
        return ret;
    }

    TELCOVOICEMGR_LOCK_OR_EXIT()

    PDML_CALLCONTROL_CALLINGFEATURES_SET_CTRL_T pCallCtrlCFSetCtrl = (PDML_CALLCONTROL_CALLINGFEATURES_SET_CTRL_T)hInsContext;

    PDML_CALLCONTROL_CALLINGFEATURES_SET pDmlCallCtrlCFSetCtrl = &(pCallCtrlCFSetCtrl->dml);

    PDML_CALLCONTROL_CALLINGFEATURES_SET_VOICE2MAIL pHEAD = &(pDmlCallCtrlCFSetCtrl->Voice2Mail);

    if (strcmp(ParamName, "MaxMessageLength") == 0)
    {
        *puLong = pHEAD->MaxMessageLength;
        ret = TRUE;
    }
    else
    {
        CcspTraceWarning(("%s: Unsupported parameter '%s'\n", __func__,ParamName));
    }


    TELCOVOICEMGR_UNLOCK()

    return ret;
}

/**********************************************************************

    caller:     owner of this object

    prototype:

        BOOL TelcoVoiceMgrDml_CallControl_CallingFeatures_SetList_Voice2Mail_SetParamUlongValue(ANSC_HANDLE hInsContext, char* ParamName, ULONG uValue);

    description:

        This function is called to set ULONG parameter value;

    argument:   ANSC_HANDLE                 hInsContext,
                The instance handle;

                char*                       ParamName,
                The parameter name;

                ULONG                       uValue
                The updated ULONG value;

    return:     TRUE if succeeded.

**********************************************************************/

BOOL TelcoVoiceMgrDml_CallControl_CallingFeatures_SetList_Voice2Mail_SetParamUlongValue(ANSC_HANDLE hInsContext, char* ParamName, ULONG uValue)
{
    BOOL ret = FALSE;
    ULONG uVsIndex  = 0;
    ULONG uSetIndex = 0;
    char HalName[MAX_STR_LEN] = {0};

    PTELCOVOICEMGR_DML_VOICESERVICE pDmlVoiceService = NULL;

    if(ParamName == NULL)
    {
        CcspTraceWarning(("%s: Invalid Input Parameter [NULL]\n", __func__));
        return ret;
    }

    TELCOVOICEMGR_LOCK_OR_EXIT()

    PDML_CALLCONTROL_CALLINGFEATURES_SET_CTRL_T pCallCtrlCFSetCtrl = (PDML_CALLCONTROL_CALLINGFEATURES_SET_CTRL_T)hInsContext;

    PDML_CALLCONTROL_CALLINGFEATURES_SET pDmlCallCtrlCFSet = &(pCallCtrlCFSetCtrl->dml);

    PDML_CALLCONTROL_CALLINGFEATURES_SET_VOICE2MAIL pHEAD = &(pDmlCallCtrlCFSet->Voice2Mail);

    if(pDmlCallCtrlCFSet != NULL && pHEAD != NULL)
    {
        pDmlVoiceService = (PTELCOVOICEMGR_DML_VOICESERVICE)pDmlCallCtrlCFSet->pParentVoiceService;
    }

    if (pHEAD == NULL  || pDmlVoiceService == NULL)
    {
        TELCOVOICEMGR_UNLOCK()

        CcspTraceError(("%s:%d:: pHEAD or pDmlVoiceService NULL\n", __FUNCTION__, __LINE__));

        return ret;
    }

    uVsIndex = pDmlVoiceService->InstanceNumber;

    uSetIndex = pDmlCallCtrlCFSet->uInstanceNumber;

    TELCOVOICEMGR_UNLOCK()

    if (strcmp(ParamName, "MaxMessageLength") == 0)
    {
        snprintf(HalName, MAX_STR_LEN, "Device.Services.VoiceService.%d.CallControl.CallingFeatures.Set.%d.Voice2Mail.MaxMessageLength",uVsIndex,uSetIndex);

        if (TelcoVoiceMgrHal_SetParamULong(HalName,uValue) == ANSC_STATUS_SUCCESS)
        {
            TELCOVOICEMGR_LOCK_OR_EXIT()

            pHEAD->MaxMessageLength = uValue;

            TELCOVOICEMGR_UNLOCK()

            ret = TRUE;
        }
    }
    else
    {
        CcspTraceWarning(("%s: Unsupported parameter '%s'\n", __func__,ParamName));
    }

    return ret;

}

/**********************************************************************

    caller:     owner of this object

    prototype:

        ULONG TelcoVoiceMgrDml_CallControl_CallingFeatures_SetList_Voice2Mail_GetParamStringValue(ANSC_HANDLE hInsContext, char* ParamName, char* pValue, ULONG* pulSize);

    description:

        This function is called to retrieve string parameter value;

    argument:   ANSC_HANDLE                 hInsContext,
                The instance handle;

                char*                       ParamName,
                The parameter name;

                char*                       pValue,
                The string value buffer;

                ULONG*                      pUlSize
                The buffer of length of string value;
                Usually size of 1023 will be used.
                If it's not big enough, put required size here and return 1;

    return:     0 if succeeded;
                1 if short of buffer size; (*pUlSize = required size)
                -1 if not supported.

**********************************************************************/

ULONG TelcoVoiceMgrDml_CallControl_CallingFeatures_SetList_Voice2Mail_GetParamStringValue(ANSC_HANDLE hInsContext, char* ParamName, char* pValue, ULONG* pulSize)
{
    ULONG ret = 1;

    if(ParamName == NULL || pValue == NULL || pulSize == NULL)
    {
        CcspTraceWarning(("%s: Invalid Input Parameter [NULL]\n", __func__));
        return ret;
    }

    TELCOVOICEMGR_LOCK_OR_EXIT()

    PDML_CALLCONTROL_CALLINGFEATURES_SET_CTRL_T pCallCtrlCFSetCtrl = (PDML_CALLCONTROL_CALLINGFEATURES_SET_CTRL_T)hInsContext;

    PDML_CALLCONTROL_CALLINGFEATURES_SET pDmlCallCtrlCFSetCtrl = &(pCallCtrlCFSetCtrl->dml);

    PDML_CALLCONTROL_CALLINGFEATURES_SET_VOICE2MAIL pHEAD = &(pDmlCallCtrlCFSetCtrl->Voice2Mail);

    if (strcmp(ParamName, "EMailAddress") == 0)
    {
        AnscCopyString(pValue,pHEAD->EMailAddress);
        ret = 0;
    }
    else
    {
        CcspTraceWarning(("%s: Unsupported parameter '%s'\n", __func__,ParamName));
    }

    TELCOVOICEMGR_UNLOCK()

    return ret;
}

/**********************************************************************

    caller:     owner of this object

    prototype:

        BOOL TelcoVoiceMgrDml_CallControl_CallingFeatures_SetList_Voice2Mail_SetParamStringValue(ANSC_HANDLE hInsContext, char* ParamName, char* pString);

    description:

        This function is called to set string parameter value;

    argument:   ANSC_HANDLE                 hInsContext,
                The instance handle;

                char*                       ParamName,
                The parameter name;

                char*                       pString
                The updated string value;

    return:     TRUE if succeeded.

**********************************************************************/

BOOL TelcoVoiceMgrDml_CallControl_CallingFeatures_SetList_Voice2Mail_SetParamStringValue(ANSC_HANDLE hInsContext, char* ParamName, char* pString)
{
    BOOL ret = FALSE;
    ULONG uVsIndex  = 0;
    ULONG uSetIndex = 0;
    char HalName[MAX_STR_LEN] = {0};

    PTELCOVOICEMGR_DML_VOICESERVICE pDmlVoiceService = NULL;

    if(ParamName == NULL)
    {
        CcspTraceWarning(("%s: Invalid Input Parameter [NULL]\n", __func__));
        return ret;
    }

    TELCOVOICEMGR_LOCK_OR_EXIT()

    PDML_CALLCONTROL_CALLINGFEATURES_SET_CTRL_T pCallCtrlCFSetCtrl = (PDML_CALLCONTROL_CALLINGFEATURES_SET_CTRL_T)hInsContext;

    PDML_CALLCONTROL_CALLINGFEATURES_SET pDmlCallCtrlCFSet = &(pCallCtrlCFSetCtrl->dml);

    PDML_CALLCONTROL_CALLINGFEATURES_SET_VOICE2MAIL pHEAD = &(pDmlCallCtrlCFSet->Voice2Mail);

    if(pDmlCallCtrlCFSet != NULL && pHEAD != NULL)
    {
        pDmlVoiceService = (PTELCOVOICEMGR_DML_VOICESERVICE)pDmlCallCtrlCFSet->pParentVoiceService;
    }

    if (pHEAD == NULL  || pDmlVoiceService == NULL)
    {
        TELCOVOICEMGR_UNLOCK()

        CcspTraceError(("%s:%d:: pHEAD or pDmlVoiceService NULL\n", __FUNCTION__, __LINE__));

        return ret;
    }

    uVsIndex = pDmlVoiceService->InstanceNumber;

    uSetIndex = pDmlCallCtrlCFSet->uInstanceNumber;

    TELCOVOICEMGR_UNLOCK()

    if (strcmp(ParamName, "EMailAddress") == 0)
    {
        snprintf(HalName, MAX_STR_LEN, "Device.Services.VoiceService.%d.CallControl.CallingFeatures.Set.%d.Voice2Mail.EMailAddress",uVsIndex,uSetIndex);

        if (TelcoVoiceMgrHal_SetParamString(HalName,pString) == ANSC_STATUS_SUCCESS)
        {
            TELCOVOICEMGR_LOCK_OR_EXIT()

            AnscCopyString(pHEAD->EMailAddress,pString);

            TELCOVOICEMGR_UNLOCK()

            ret = TRUE;
        }
    }
    else
    {
        CcspTraceWarning(("%s: Unsupported parameter '%s'\n", __func__,ParamName));
    }

    return ret;
}

/**********************************************************************

    caller:     owner of this object

    prototype:

        BOOL TelcoVoiceMgrDml_CallControl_CallingFeatures_SetList_Voice2Mail_GetParamBoolValue(ANSC_HANDLE hInsContext, char* ParamName, BOOL* pBool);

    description:

        This function is called to retrieve Boolean parameter value;

    argument:   ANSC_HANDLE                 hInsContext,
                The instance handle;

                char*                       ParamName,
                The parameter name;

                BOOL*                       pBool
                The buffer of returned boolean value;

    return:     TRUE if succeeded.

**********************************************************************/

BOOL TelcoVoiceMgrDml_CallControl_CallingFeatures_SetList_Voice2Mail_GetParamBoolValue(ANSC_HANDLE hInsContext, char* ParamName, BOOL* pBool)
{
    BOOL ret = FALSE;

    if(ParamName == NULL || pBool == NULL)
    {
        CcspTraceWarning(("%s: Invalid Input Parameter [NULL]\n", __func__));
        return ret;
    }

    TELCOVOICEMGR_LOCK_OR_EXIT()

    PDML_CALLCONTROL_CALLINGFEATURES_SET_CTRL_T pCallCtrlCFSetCtrl = (PDML_CALLCONTROL_CALLINGFEATURES_SET_CTRL_T)hInsContext;

    PDML_CALLCONTROL_CALLINGFEATURES_SET pDmlCallCtrlCFSetCtrl = &(pCallCtrlCFSetCtrl->dml);

    PDML_CALLCONTROL_CALLINGFEATURES_SET_VOICE2MAIL pHEAD = &(pDmlCallCtrlCFSetCtrl->Voice2Mail);

    if (strcmp(ParamName, "KeepLocal") == 0)
    {
        *pBool = pHEAD->KeepLocal;
        ret = TRUE;
    }
    else if (strcmp(ParamName, "Enable") == 0)
    {
        *pBool = pHEAD->Enable;
        ret = TRUE;
    }
    else if (strcmp(ParamName, "Attach") == 0)
    {
        *pBool = pHEAD->Attach;
        ret = TRUE;
    }
    else
    {
        CcspTraceWarning(("%s: Unsupported parameter '%s'\n", __func__,ParamName));
    }

    TELCOVOICEMGR_UNLOCK()

    return ret;
}

/**********************************************************************

    caller:     owner of this object

    prototype:

        BOOL TelcoVoiceMgrDml_CallControl_CallingFeatures_SetList_Voice2Mail_SetParamBoolValue(ANSC_HANDLE hInsContext, char* ParamName, BOOL bValue);

    description:

        This function is called to set BOOL parameter value;

    argument:   ANSC_HANDLE                 hInsContext,
                The instance handle;

                char*                       ParamName,
                The parameter name;

                BOOL                        bValue
                The updated BOOL value;

    return:     TRUE if succeeded.

**********************************************************************/

BOOL TelcoVoiceMgrDml_CallControl_CallingFeatures_SetList_Voice2Mail_SetParamBoolValue(ANSC_HANDLE hInsContext, char* ParamName, BOOL bValue)
{
    BOOL ret = FALSE;
    ULONG uVsIndex  = 0;
    ULONG uSetIndex = 0;
    char HalName[MAX_STR_LEN] = {0};

    PTELCOVOICEMGR_DML_VOICESERVICE pDmlVoiceService = NULL;

    if(ParamName == NULL)
    {
        CcspTraceWarning(("%s: Invalid Input Parameter [NULL]\n", __func__));
        return ret;
    }

    TELCOVOICEMGR_LOCK_OR_EXIT()

    PDML_CALLCONTROL_CALLINGFEATURES_SET_CTRL_T pCallCtrlCFSetCtrl = (PDML_CALLCONTROL_CALLINGFEATURES_SET_CTRL_T)hInsContext;

    PDML_CALLCONTROL_CALLINGFEATURES_SET pDmlCallCtrlCFSet = &(pCallCtrlCFSetCtrl->dml);

    PDML_CALLCONTROL_CALLINGFEATURES_SET_VOICE2MAIL pHEAD = &(pDmlCallCtrlCFSet->Voice2Mail);

    if(pDmlCallCtrlCFSet != NULL && pHEAD != NULL)
    {
        pDmlVoiceService = (PTELCOVOICEMGR_DML_VOICESERVICE)pDmlCallCtrlCFSet->pParentVoiceService;
    }

    if (pHEAD == NULL  || pDmlVoiceService == NULL)
    {
        TELCOVOICEMGR_UNLOCK()

        CcspTraceError(("%s:%d:: pHEAD or pDmlVoiceService NULL\n", __FUNCTION__, __LINE__));

        return ret;
    }

    uVsIndex = pDmlVoiceService->InstanceNumber;

    uSetIndex = pDmlCallCtrlCFSet->uInstanceNumber;

    TELCOVOICEMGR_UNLOCK()

    if (strcmp(ParamName, "KeepLocal") == 0)
    {
        snprintf(HalName, MAX_STR_LEN, "Device.Services.VoiceService.%d.CallControl.CallingFeatures.Set.%d.Voice2Mail.KeepLocal",uVsIndex,uSetIndex);

        if (TelcoVoiceMgrHal_SetParamBool(HalName,bValue) == ANSC_STATUS_SUCCESS)
        {
            TELCOVOICEMGR_LOCK_OR_EXIT()

            pHEAD->KeepLocal = bValue;

            TELCOVOICEMGR_UNLOCK()

            ret = TRUE;
        }
    }
    else if (strcmp(ParamName, "Enable") == 0)
    {
        snprintf(HalName, MAX_STR_LEN, "Device.Services.VoiceService.%d.CallControl.CallingFeatures.Set.%d.Voice2Mail.Enable",uVsIndex,uSetIndex);

        if (TelcoVoiceMgrHal_SetParamBool(HalName,bValue) == ANSC_STATUS_SUCCESS)
        {
            TELCOVOICEMGR_LOCK_OR_EXIT()

            pHEAD->Enable = bValue;

            TELCOVOICEMGR_UNLOCK()

            ret = TRUE;
        }
    }
    else if (strcmp(ParamName, "Attach") == 0)
    {
        snprintf(HalName, MAX_STR_LEN, "Device.Services.VoiceService.%d.CallControl.CallingFeatures.Set.%d.Voice2Mail.Attach",uVsIndex,uSetIndex);

        if (TelcoVoiceMgrHal_SetParamBool(HalName,bValue) == ANSC_STATUS_SUCCESS)
        {
            TELCOVOICEMGR_LOCK_OR_EXIT()

            pHEAD->Attach = bValue;

            TELCOVOICEMGR_UNLOCK()

            ret = TRUE;
        }
    }
    else
    {
        CcspTraceWarning(("%s: Unsupported parameter '%s'\n", __func__,ParamName));
    }

    return ret;
}
