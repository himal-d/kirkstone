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
#include "telcovoicemgr_dml_tone_v1.h"
#include "telcovoicemgr_services_apis_v1.h"
#include "ccsp_trace.h"
#include "ccsp_syslog.h"

/**********************************************************************

    caller:     owner of this object

    prototype:

        ULONG ToneEvent_GetEntryCount(ANSC_HANDLE hInsContext);

    description:

        This function is called to retrieve the count of the table.

    argument:   ANSC_HANDLE                 hInsContext,
                The instance handle;

    return:     The count of the table

**********************************************************************/
ULONG ToneEvent_GetEntryCount(ANSC_HANDLE hInsContext)
{
    return 0;
}
/**********************************************************************
    caller:     owner of this object

    prototype:

        ANSC_HANDLE ToneEvent_GetEntry(ANSC_HANDLE hInsContext, ULONG nIndex, ULONG* pInsNumber);

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
ANSC_HANDLE ToneEvent_GetEntry(ANSC_HANDLE hInsContext, ULONG nIndex, ULONG* pInsNumber)
{
  
    ANSC_HANDLE pDmlEntry = NULL;
    return pDmlEntry;
}
/**********************************************************************

    caller:     owner of this object

    prototype:

        BOOL ToneEvent_SetParamUlongValue(ANSC_HANDLE hInsContext, char* ParamName, ULONG uValue);

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
BOOL ToneEvent_SetParamUlongValue(ANSC_HANDLE hInsContext, char* ParamName, ULONG uValue)
{
    BOOL ret = FALSE;
    if (strcmp(ParamName, "ToneID") == 0)
    {
        ret = TRUE;
    }
    return ret;
}

/**********************************************************************

    caller:     owner of this object

    prototype:

        BOOL ToneEvent_SetParamStringValue(ANSC_HANDLE hInsContext, char* ParamName, char* pString);

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
BOOL ToneEvent_SetParamStringValue(ANSC_HANDLE hInsContext, char* ParamName, char* pString)
{
    BOOL ret = FALSE;
    if (strcmp(ParamName, "Alias") == 0)
    {
        return TRUE;
    }
    return ret;
}

/**********************************************************************

    caller:     owner of this object

    prototype:

        LONG ToneEvent_GetParamStringValue(ANSC_HANDLE hInsContext, char* ParamName, char* pValue, ULONG* pUlSize);

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

LONG ToneEvent_GetParamStringValue(ANSC_HANDLE hInsContext, char* ParamName, char* pValue, ULONG* pUlSize)
{
    ULONG ret = 1;
    if (strcmp(ParamName, "Alias") == 0)
    {
        return 0;
    }
    else if (strcmp(ParamName, "Function") == 0)
    {
        return 0;
    }
    return ret;
}
/**********************************************************************

    caller:     owner of this object

    prototype:
        BOOL ToneEvent_GetParamUlongValue(ANSC_HANDLE hInsContext, char* ParamName, ULONG* pValue);

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

BOOL ToneEvent_GetParamUlongValue(ANSC_HANDLE hInsContext, char* ParamName, ULONG* pValue)
{
    BOOL ret = FALSE;

    if (strcmp(ParamName, "ToneID") == 0)
    {
        ret = TRUE;
    }

    return ret;
}

/**********************************************************************

    caller:     owner of this object

    prototype:

        ULONG ToneDescription_GetEntryCount(ANSC_HANDLE hInsContext);

    description:

        This function is called to retrieve the count of the table.

    argument:   ANSC_HANDLE                 hInsContext,
                The instance handle;

    return:     The count of the table

**********************************************************************/
ULONG ToneDescription_GetEntryCount(ANSC_HANDLE hInsContext)
{
    return 0;
}
/**********************************************************************
    caller:     owner of this object

    prototype:

        ANSC_HANDLE ToneDescription_GetEntry(ANSC_HANDLE hInsContext, ULONG nIndex, ULONG* pInsNumber);

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
ANSC_HANDLE ToneDescription_GetEntry(ANSC_HANDLE hInsContext, ULONG nIndex, ULONG* pInsNumber)
{
  
    ANSC_HANDLE pDmlEntry = NULL;
    return pDmlEntry;
}
/**********************************************************************

    caller:     owner of this object

    prototype:
        BOOL ToneDescription_GetParamUlongValue(ANSC_HANDLE hInsContext, char* ParamName, ULONG* pValue);

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

BOOL ToneDescription_GetParamUlongValue(ANSC_HANDLE hInsContext, char* ParamName, ULONG* pValue)
{
    BOOL ret = FALSE;

    if (strcmp(ParamName, "EntryID") == 0)
    {
        ret = TRUE;
    }
    else if (strcmp(ParamName, "TonePattern") == 0)
    {
        ret = TRUE;
    }
    else if (strcmp(ParamName, "ToneRepetitions") == 0)
    {
        ret = TRUE;
    }
    return ret;
}

/**********************************************************************

    caller:     owner of this object

    prototype:

        BOOL ToneDescription_SetParamBoolValue(ANSC_HANDLE hInsContext, char* ParamName, char* pString);

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
BOOL ToneDescription_SetParamBoolValue(ANSC_HANDLE hInsContext, char* ParamName, BOOL bValue)
{
    BOOL ret = FALSE;
    if (strcmp(ParamName, "ToneEnable") == 0)
    {
        ret = FALSE;
    }
    return ret;
}

/**********************************************************************

    caller:     owner of this object

    prototype:

        LONG ToneDescription_GetParamStringValue(ANSC_HANDLE hInsContext, char* ParamName, char* pValue, ULONG* pUlSize);

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

LONG ToneDescription_GetParamStringValue(ANSC_HANDLE hInsContext, char* ParamName, char* pValue, ULONG* pUlSize)
{
    ULONG ret = 1;
    if (strcmp(ParamName, "Alias") == 0)
    {
        return 0;
    }
    else if (strcmp(ParamName, "ToneName") == 0)
    {
        return 0;
    }
    else if (strcmp(ParamName, "ToneFile") == 0)
    {
        return 0;
    }
    else if (strcmp(ParamName, "ToneText") == 0)
    {
        return 0;
    }
    return ret;
}

/**********************************************************************

    caller:     owner of this object

    prototype:

        BOOL ToneDescription_SetParamUlongValue(ANSC_HANDLE hInsContext, char* ParamName, ULONG uValue);

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
BOOL ToneDescription_SetParamUlongValue(ANSC_HANDLE hInsContext, char* ParamName, ULONG uValue)
{
    BOOL ret = FALSE;
    if (strcmp(ParamName, "TonePattern") == 0)
    {
        ret = TRUE;
    }
    else if (strcmp(ParamName, "ToneRepetitions") == 0)
    {
        ret = TRUE;
    }
    return ret;
}

/**********************************************************************

    caller:     owner of this object

    prototype:

        BOOL ToneDescription_SetParamStringValue(ANSC_HANDLE hInsContext, char* ParamName, char* pString);

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
BOOL ToneDescription_SetParamStringValue(ANSC_HANDLE hInsContext, char* ParamName, char* pString)
{
    BOOL ret = FALSE;
    if (strcmp(ParamName, "Alias") == 0)
    {
        return TRUE;
    }
    else if (strcmp(ParamName, "ToneName") == 0)
    {
        return TRUE;
    }
    else if (strcmp(ParamName, "ToneFile") == 0)
    {
        return TRUE;
    }
    else if (strcmp(ParamName, "ToneText") == 0)
    {
        return TRUE;
    }
    return ret;
}

/**********************************************************************

    caller:     owner of this object

    prototype:

        ULONG TonePattern_GetEntryCount(ANSC_HANDLE hInsContext);

    description:

        This function is called to retrieve the count of the table.

    argument:   ANSC_HANDLE                 hInsContext,
                The instance handle;

    return:     The count of the table

**********************************************************************/
ULONG TonePattern_GetEntryCount(ANSC_HANDLE hInsContext)
{
    return 0;
}
/**********************************************************************
    caller:     owner of this object

    prototype:

        ANSC_HANDLE TonePattern_GetEntry(ANSC_HANDLE hInsContext, ULONG nIndex, ULONG* pInsNumber);

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
ANSC_HANDLE TonePattern_GetEntry(ANSC_HANDLE hInsContext, ULONG nIndex, ULONG* pInsNumber)
{
  
    ANSC_HANDLE pDmlEntry = NULL;
    return pDmlEntry;
}

/*********************************************************************:

    caller:     owner of this object

    prototype:
        BOOL TonePattern_GetParamUlongValue(ANSC_HANDLE hInsContext, char* ParamName, ULONG* pValue);

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

BOOL TonePattern_GetParamUlongValue(ANSC_HANDLE hInsContext, char* ParamName, ULONG* pValue)
{
    BOOL ret = FALSE;

    if (strcmp(ParamName, "EntryID") == 0)
    {
        ret = TRUE;
    }
    else if (strcmp(ParamName, "Frequency1") == 0)
    {
        ret = TRUE;
    }
    else if (strcmp(ParamName, "Frequency2") == 0)
    {
        ret = TRUE;
    }
    else if (strcmp(ParamName, "Frequency3") == 0)
    {
        ret = TRUE;
    }
    else if (strcmp(ParamName, "Frequency4") == 0)
    {
        ret = TRUE;
    }
    else if (strcmp(ParamName, "ModulationFrequency") == 0)
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
    
    return ret;
}

/**********************************************************************

        caller:     owner of this object

        prototype:

    BOOL TonePattern_GetParamBoolValue(ANSC_HANDLE hInsContext, char* ParamName, BOOL* pBool);

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
BOOL TonePattern_GetParamBoolValue(ANSC_HANDLE hInsContext, char* ParamName, BOOL* pBool)
{
    BOOL ret = FALSE;

    if (strcmp(ParamName, "ToneOn") == 0)
    {
        ret = TRUE;
    }
    else if (strcmp(ParamName, "X_RDK_FactoryReset") == 0)
    {
        ret = TRUE;
    }

    return ret;
}

/**********************************************************************

    caller:     owner of this object

    prototype:

        LONG TonePattern_GetParamStringValue(ANSC_HANDLE hInsContext, char* ParamName, char* pValue, ULONG* pUlSize);

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

LONG TonePattern_GetParamStringValue(ANSC_HANDLE hInsContext, char* ParamName, char* pValue, ULONG* pUlSize)
{
    ULONG ret = 1;
    if (strcmp(ParamName, "Alias") == 0)
    {
        return 0;
    }
    return ret;
}


/**********************************************************************

    caller:     owner of this object

    prototype:

        BOOL  TonePattern_GetParamIntValue(ANSC_HANDLE hInsContext, char* ParamName, int* pInt)

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
BOOL TonePattern_GetParamIntValue(ANSC_HANDLE hInsContext, char* ParamName, int* pInt)
{
    BOOL ret = FALSE;
    if (strcmp(ParamName, "Power1") == 0)
    {
        ret = TRUE;
    }
    else if (strcmp(ParamName, "Power2") == 0)
    {
        ret = TRUE;
    }
    else if (strcmp(ParamName, "Power3") == 0)
    {
        ret = TRUE;
    }
    else if (strcmp(ParamName, "Power4") == 0)
    {
        ret = TRUE;
    }
    else if (strcmp(ParamName, "ModulationPower") == 0)
    {
        ret = TRUE;
    }
    return ret;
}

/**********************************************************************

    caller:     owner of this object

    prototype:

        BOOL TonePattern_SetParamIntValue(ANSC_HANDLE hInsContext, char* ParamName, int iValue);

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
BOOL TonePattern_SetParamIntValue(ANSC_HANDLE hInsContext, char* ParamName, int iValue)
{
    BOOL ret = FALSE;
    if (strcmp(ParamName, "Power1") == 0)
    {
        ret = FALSE;
    }
    else if (strcmp(ParamName, "Power2") == 0)
    {
        ret = FALSE;
    }
    else if (strcmp(ParamName, "Power3") == 0)
    {
        ret = FALSE;
    }
    else if (strcmp(ParamName, "Power4") == 0)
    {
        ret = FALSE;
    }
    else if (strcmp(ParamName, "ModulationPower") == 0)
    {
        ret = FALSE;
    }
    return ret;
}   

/**********************************************************************

    caller:     owner of this object

    prototype:

        BOOL TonePattern_SetParamUlongValue(ANSC_HANDLE hInsContext, char* ParamName, ULONG uValue);

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
BOOL TonePattern_SetParamUlongValue(ANSC_HANDLE hInsContext, char* ParamName, ULONG uValue)
{
    BOOL ret = FALSE;

    if (strcmp(ParamName, "EntryID") == 0)
    {
        ret = TRUE;
    }
    else if (strcmp(ParamName, "ToneRepetitions") == 0)
    {
        ret = TRUE;
    }
    else if (strcmp(ParamName, "Frequency1") == 0)
    {
        ret = TRUE;
    }
    else if (strcmp(ParamName, "Frequency2") == 0)
    {
        ret = TRUE;
    }
    else if (strcmp(ParamName, "Frequency3") == 0)
    {
        ret = TRUE;
    }
    else if (strcmp(ParamName, "Frequency4") == 0)
    {
        ret = TRUE;
    }
    else if (strcmp(ParamName, "ModulationFrequency") == 0)
    {
        ret = TRUE;
    }
    else if (strcmp(ParamName, "ModulationPower") == 0)
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
    return ret;
}


/**********************************************************************

        caller:     owner of this object

        prototype:

    BOOL ToneDescription_GetParamBoolValue(ANSC_HANDLE hInsContext, char* ParamName, BOOL* pBool);

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
BOOL ToneDescription_GetParamBoolValue(ANSC_HANDLE hInsContext, char* ParamName, BOOL* pBool)
{
    BOOL ret = FALSE;

    if (strcmp(ParamName, "ToneEnable") == 0)
    {
        ret = TRUE;
    }

    return ret;
}
