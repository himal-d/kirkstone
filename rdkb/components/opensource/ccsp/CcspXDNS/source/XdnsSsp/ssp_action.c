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

    module: ssp_action.c

        For CCSP XDNS Module

    ---------------------------------------------------------------

    description:

        SSP implementation of the XDNS module.

        *   ssp_create_xdns
        *   ssp_engage_xdns
        *   ssp_cancel_xdns
        *   ssp_XdnsCCDmGetComponentName
        *   ssp_XdnsCCDmGetComponentVersion
        *   ssp_XdnsCCDmGetComponentAuthor
        *   ssp_XdnsCCDmGetComponentHealth
        *   ssp_XdnsCCDmGetComponentState
        *   ssp_XdnsCCDmGetLoggingEnabled
        *   ssp_XdnsCCDmSetLoggingEnabled
        *   ssp_XdnsCCDmGetLoggingLevel
        *   ssp_XdnsCCDmSetLoggingLevel
        *   ssp_XdnsCCDmGetMemMaxUsage
        *   ssp_XdnsCCDmGetMemMinUsage
        *   ssp_XdnsCCDmGetMemConsumed

    ---------------------------------------------------------------

    environment:

        Embedded Linux

    ---------------------------------------------------------------

    author:

        Tom Chang

    ---------------------------------------------------------------

    revision:

        06/15/2011  initial revision.

**********************************************************************/

#include "ssp_global.h"
#include "ccsp_trace.h"
#include <time.h>
#include "cosa_plugin_api.h"
#include "dm_pack_create_func.h"
#include "safec_lib_common.h"

extern ULONG                            g_ulAllocatedSizePeak;

extern  PDSLH_CPE_CONTROLLER_OBJECT     pDslhCpeController;
extern  PDSLH_DATAMODEL_AGENT_OBJECT    g_DslhDataModelAgent;
extern  PCOMPONENT_COMMON_DM            g_pComponent_Common_Dm;
extern  PCCSP_FC_CONTEXT                 pXdnsFcContext;
extern  PCCSP_CCD_INTERFACE              pXdnsCcdIf;
extern  ANSC_HANDLE                     bus_handle;
extern  char                            g_Subsystem[32];
ANSC_HANDLE
COSAAcquireFunction
    (
        char*                       pApiName
    );
//static  COMPONENT_COMMON_DM             CommonDm = {0};

#define  COSA_PLUGIN_XML_FILE           "/usr/ccsp/xdns/CcspXdns_dm.xml"

COSAGetParamValueByPathNameProc     g_GetParamValueByPathNameProc   = NULL;


ANSC_STATUS
ssp_create_xdns
    (
    )
{
    /* Create component common data model object */

    g_pComponent_Common_Dm = (PCOMPONENT_COMMON_DM)AnscAllocateMemory(sizeof(COMPONENT_COMMON_DM));

    if ( !g_pComponent_Common_Dm )
    {
        return ANSC_STATUS_RESOURCES;
    }

    ComponentCommonDmInit(g_pComponent_Common_Dm);

    g_pComponent_Common_Dm->Name     = AnscCloneString(CCSP_COMPONENT_NAME_XDNS);
    g_pComponent_Common_Dm->Version  = 1;
    g_pComponent_Common_Dm->Author   = AnscCloneString("Shubham Baheti");
    errno_t                 rc       = -1;

    /* Create ComponentCommonDatamodel interface*/
    if ( !pXdnsCcdIf )
    {
        pXdnsCcdIf = (PCCSP_CCD_INTERFACE)AnscAllocateMemory(sizeof(CCSP_CCD_INTERFACE));

        if ( !pXdnsCcdIf )
        {
            return ANSC_STATUS_RESOURCES;
        }
        else
        {
            rc = strcpy_s(pXdnsCcdIf->Name,sizeof(pXdnsCcdIf->Name) ,CCSP_CCD_INTERFACE_NAME);
            if (rc != EOK)
            {
                ERR_CHK(rc);
                free(pXdnsCcdIf);
                return ANSC_STATUS_FAILURE;
            }

            pXdnsCcdIf->InterfaceId              = CCSP_CCD_INTERFACE_ID;
            pXdnsCcdIf->hOwnerContext            = NULL;
            pXdnsCcdIf->Size                     = sizeof(CCSP_CCD_INTERFACE);

            pXdnsCcdIf->GetComponentName         = ssp_XdnsCCDmGetComponentName;
            pXdnsCcdIf->GetComponentVersion      = ssp_XdnsCCDmGetComponentVersion;
            pXdnsCcdIf->GetComponentAuthor       = ssp_XdnsCCDmGetComponentAuthor;
            pXdnsCcdIf->GetComponentHealth       = ssp_XdnsCCDmGetComponentHealth;
            pXdnsCcdIf->GetComponentState        = ssp_XdnsCCDmGetComponentState;
            pXdnsCcdIf->GetLoggingEnabled        = ssp_XdnsCCDmGetLoggingEnabled;
            pXdnsCcdIf->SetLoggingEnabled        = ssp_XdnsCCDmSetLoggingEnabled;
            pXdnsCcdIf->GetLoggingLevel          = ssp_XdnsCCDmGetLoggingLevel;
            pXdnsCcdIf->SetLoggingLevel          = ssp_XdnsCCDmSetLoggingLevel;
            pXdnsCcdIf->GetMemMaxUsage           = ssp_XdnsCCDmGetMemMaxUsage;
            pXdnsCcdIf->GetMemMinUsage           = ssp_XdnsCCDmGetMemMinUsage;
            pXdnsCcdIf->GetMemConsumed           = ssp_XdnsCCDmGetMemConsumed;
            pXdnsCcdIf->ApplyChanges             = ssp_XdnsCCDmApplyChanges;
        }
    }

    /* Create context used by data model */
    pXdnsFcContext = (PCCSP_FC_CONTEXT)AnscAllocateMemory(sizeof(CCSP_FC_CONTEXT));

    if ( !pXdnsFcContext )
    {
        return ANSC_STATUS_RESOURCES;
    }
    else
    {
        AnscZeroMemory(pXdnsFcContext, sizeof(CCSP_FC_CONTEXT));
    }

    pDslhCpeController = DslhCreateCpeController(NULL, NULL, NULL);

    if ( !pDslhCpeController )
    {
        CcspTraceWarning(("CANNOT Create pDslhCpeController... Exit!\n"));

        return ANSC_STATUS_RESOURCES;
    }

    return ANSC_STATUS_SUCCESS;
}


ANSC_STATUS
ssp_engage_xdns
    (
    )
{
	ANSC_STATUS					    returnStatus                                         = ANSC_STATUS_SUCCESS;
        char                                                CrName[256];
   ANSC_HANDLE tempIf = NULL;

    g_pComponent_Common_Dm->Health = CCSP_COMMON_COMPONENT_HEALTH_Yellow;

    if ( pXdnsCcdIf )
    {
        pXdnsFcContext->hCcspCcdIf = (ANSC_HANDLE)pXdnsCcdIf;
        pXdnsFcContext->hMessageBus = bus_handle;
    }

    g_DslhDataModelAgent->SetFcContext((ANSC_HANDLE)g_DslhDataModelAgent, (ANSC_HANDLE)pXdnsFcContext);
    /*Coverity Fix CID:73793 RESOURCE_LEAK */
    tempIf = MsgHelper_CreateCcdMbiIf((void*)bus_handle, g_Subsystem);
    pDslhCpeController->AddInterface((ANSC_HANDLE)pDslhCpeController,tempIf);
    pDslhCpeController->AddInterface((ANSC_HANDLE)pDslhCpeController, (ANSC_HANDLE)pXdnsCcdIf);
    pDslhCpeController->SetDbusHandle((ANSC_HANDLE)pDslhCpeController, bus_handle);
    pDslhCpeController->Engage((ANSC_HANDLE)pDslhCpeController);
    
    
    if ( g_Subsystem[0] != 0 )
    {
           /* Coverity Fix CID:58058  DC.STRING_BUFFER */
        snprintf(CrName,sizeof(CrName), "%s%s", g_Subsystem, CCSP_DBUS_INTERFACE_CR);
    }
    else
    {
             /* Coverity Fix CID:58058  DC.STRING_BUFFER */
        snprintf(CrName,sizeof(CrName), "%s",CCSP_DBUS_INTERFACE_CR);
    }

    
    
 

    if ( g_GetParamValueByPathNameProc == NULL )
    {
        g_GetParamValueByPathNameProc = 
            (COSAGetParamValueByPathNameProc)COSAAcquireFunction("COSAGetParamValueByPathName");

        if ( !g_GetParamValueByPathNameProc )
        {
            printf("XDNS - failed to load the function COSAGetParamValueByPathName!\n");
        }
    }

    returnStatus =
        pDslhCpeController->RegisterCcspDataModel2
            (
                (ANSC_HANDLE)pDslhCpeController,
                CrName, /*CCSP_DBUS_INTERFACE_CR,*/             /* CCSP CR ID */
                DMPackCreateDataModelXML,            /* Comcast generated code to create XML. */
                CCSP_COMPONENT_NAME_XDNS,            /* Component Name    */
                CCSP_COMPONENT_VERSION_XDNS,         /* Component Version */
                CCSP_COMPONENT_PATH_XDNS,            /* Component Path    */
                g_Subsystem                         /* Component Prefix  */
            );

    if ( returnStatus == ANSC_STATUS_SUCCESS || CCSP_SUCCESS == returnStatus)
    {
        /* System is fully initialized */
        g_pComponent_Common_Dm->Health = CCSP_COMMON_COMPONENT_HEALTH_Green;
    }

    free(tempIf);
    return ANSC_STATUS_SUCCESS;
}


ANSC_STATUS
ssp_cancel_xdns
    (
    )
{
    pDslhCpeController->Cancel((ANSC_HANDLE)pDslhCpeController);
    AnscFreeMemory(pDslhCpeController);

    return ANSC_STATUS_SUCCESS;
}


char*
ssp_XdnsCCDmGetComponentName
    (
        ANSC_HANDLE                     hThisObject
    )
{
    UNREFERENCED_PARAMETER(hThisObject);
    return g_pComponent_Common_Dm->Name;
}


ULONG
ssp_XdnsCCDmGetComponentVersion
    (
        ANSC_HANDLE                     hThisObject
    )
{
    UNREFERENCED_PARAMETER(hThisObject);
    return g_pComponent_Common_Dm->Version;
}


char*
ssp_XdnsCCDmGetComponentAuthor
    (
        ANSC_HANDLE                     hThisObject
    )
{
    UNREFERENCED_PARAMETER(hThisObject);
    return g_pComponent_Common_Dm->Author;
}


ULONG
ssp_XdnsCCDmGetComponentHealth
    (
        ANSC_HANDLE                     hThisObject
    )
{
    UNREFERENCED_PARAMETER(hThisObject);
    return g_pComponent_Common_Dm->Health;
}


ULONG
ssp_XdnsCCDmGetComponentState
    (
        ANSC_HANDLE                     hThisObject
    )
{
    UNREFERENCED_PARAMETER(hThisObject);
    return g_pComponent_Common_Dm->State;
}



BOOL
ssp_XdnsCCDmGetLoggingEnabled
    (
        ANSC_HANDLE                     hThisObject
    )
{
    UNREFERENCED_PARAMETER(hThisObject);
    return g_pComponent_Common_Dm->LogEnable;
}


ANSC_STATUS
ssp_XdnsCCDmSetLoggingEnabled
    (
        ANSC_HANDLE                     hThisObject,
        BOOL                            bEnabled
    )
{
    UNREFERENCED_PARAMETER(hThisObject);
    /*CommonDm.LogEnable = bEnabled;*/
    if(g_pComponent_Common_Dm->LogEnable == bEnabled) return ANSC_STATUS_SUCCESS;
    g_pComponent_Common_Dm->LogEnable = bEnabled;

    if (!bEnabled)
        AnscSetTraceLevel(CCSP_TRACE_INVALID_LEVEL);
    else
        AnscSetTraceLevel(g_pComponent_Common_Dm->LogLevel);

    return ANSC_STATUS_SUCCESS;
}


ULONG
ssp_XdnsCCDmGetLoggingLevel
    (
        ANSC_HANDLE                     hThisObject
    )
{
    UNREFERENCED_PARAMETER(hThisObject);
    return g_pComponent_Common_Dm->LogLevel;
}


ANSC_STATUS
ssp_XdnsCCDmSetLoggingLevel
    (
        ANSC_HANDLE                     hThisObject,
        ULONG                           LogLevel
    )
{
    UNREFERENCED_PARAMETER(hThisObject);
    /*CommonDm.LogLevel = LogLevel;*/
    if(g_pComponent_Common_Dm->LogLevel == LogLevel) return ANSC_STATUS_SUCCESS;
    g_pComponent_Common_Dm->LogLevel = LogLevel;

    if (g_pComponent_Common_Dm->LogEnable)
        AnscSetTraceLevel(LogLevel);        

    return ANSC_STATUS_SUCCESS;
}


ULONG
ssp_XdnsCCDmGetMemMaxUsage
    (
        ANSC_HANDLE                     hThisObject
    )
{
    UNREFERENCED_PARAMETER(hThisObject);
    return g_ulAllocatedSizePeak;
}


ULONG
ssp_XdnsCCDmGetMemMinUsage
    (
        ANSC_HANDLE                     hThisObject
    )
{
    UNREFERENCED_PARAMETER(hThisObject);
    return g_pComponent_Common_Dm->MemMinUsage;
}


ULONG
ssp_XdnsCCDmGetMemConsumed
    (
        ANSC_HANDLE                     hThisObject
    )
{
    UNREFERENCED_PARAMETER(hThisObject);
    LONG             size = 0;

    size = AnscGetComponentMemorySize(CCSP_COMPONENT_NAME_XDNS);
    if (size == -1 )
        size = 0;

    return size;
}


ANSC_STATUS
ssp_XdnsCCDmApplyChanges
    (
        ANSC_HANDLE                     hThisObject
    )
{
    UNREFERENCED_PARAMETER(hThisObject);
    ANSC_STATUS                         returnStatus    = ANSC_STATUS_SUCCESS;
    /* Assume the parameter settings are committed immediately. */
    /*g_pComponent_Common_Dm->LogEnable = CommonDm.LogEnable;
    g_pComponent_Common_Dm->LogLevel  = CommonDm.LogLevel;

    AnscSetTraceLevel((INT)g_pComponent_Common_Dm->LogLevel);*/

    return returnStatus;
}


