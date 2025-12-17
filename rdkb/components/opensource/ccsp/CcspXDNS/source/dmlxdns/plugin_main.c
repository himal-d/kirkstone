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

/***********************************************************************

    module: plugin_main.c

        Implement COSA Data Model Library Init and Unload apis.

    ---------------------------------------------------------------

    author:

        COSA XML TOOL CODE GENERATOR 1.0

    ---------------------------------------------------------------

    revision:

        01/14/2011    initial revision.

**********************************************************************/

#include "ansc_platform.h"
#include "ansc_load_library.h"
#include "cosa_plugin_api.h"
#include "plugin_main.h"

#include "plugin_main_apis.h"
#include "cosa_xdns_dml.h"
#include "cosa_xdns_webconfig_api.h"


PCOSA_BACKEND_MANAGER_OBJECT g_pCosaBEManager;
void *                       g_pDslhDmlAgent; 
extern ANSC_HANDLE     g_MessageBusHandle_Irep;
extern char            g_SubSysPrefix_Irep[32];

#define THIS_PLUGIN_VERSION                         1

int ANSC_EXPORT_API
COSA_Init
    (
        ULONG                       uMaxVersionSupported,
        void*                       hCosaPlugInfo         /* PCOSA_PLUGIN_INFO passed in by the caller */
    )
{
    PCOSA_PLUGIN_INFO               pPlugInfo                   = (PCOSA_PLUGIN_INFO                 )hCosaPlugInfo;
    COSAGetParamValueStringProc     pGetStringProc              = (COSAGetParamValueStringProc       )NULL;
    COSAGetParamValueUlongProc      pGetParamValueUlongProc     = (COSAGetParamValueUlongProc        )NULL;
    COSAValidateHierarchyInterfaceProc
                                    pValInterfaceProc           = (COSAValidateHierarchyInterfaceProc)NULL;
    COSAGetHandleProc               pGetRegistryRootFolder      = (COSAGetHandleProc                 )NULL;
    COSAGetInstanceNumberByIndexProc
                                    pGetInsNumberByIndexProc    = (COSAGetInstanceNumberByIndexProc  )NULL;
    COSAGetInterfaceByNameProc      pGetInterfaceByNameProc     = (COSAGetInterfaceByNameProc        )NULL;


    if ( uMaxVersionSupported < THIS_PLUGIN_VERSION )
    {
      /* this version is not supported */
        return -1;
    }

    pPlugInfo->uPluginVersion       = THIS_PLUGIN_VERSION;
    g_pDslhDmlAgent                 = pPlugInfo->hDmlAgent;

    /* register the back-end apis for the data model */

    pPlugInfo->RegisterFunction(pPlugInfo->hContext, "XDNS_GetParamStringValue",  XDNS_GetParamStringValue);
    pPlugInfo->RegisterFunction(pPlugInfo->hContext, "XDNS_SetParamStringValue",  XDNS_SetParamStringValue);
    pPlugInfo->RegisterFunction(pPlugInfo->hContext, "XDNS_GetParamBoolValue", XDNS_GetParamBoolValue);
    pPlugInfo->RegisterFunction(pPlugInfo->hContext, "XDNS_SetParamBoolValue", XDNS_SetParamBoolValue);
    pPlugInfo->RegisterFunction(pPlugInfo->hContext, "XDNS_Validate",  XDNS_Validate);
    pPlugInfo->RegisterFunction(pPlugInfo->hContext, "XDNS_Commit",  XDNS_Commit);
    pPlugInfo->RegisterFunction(pPlugInfo->hContext, "XDNS_Rollback",  XDNS_Rollback);   
    
    pGetStringProc = (COSAGetParamValueStringProc)pPlugInfo->AcquireFunction("COSAGetParamValueString");

    if( pGetStringProc != NULL)
    {
        g_GetParamValueString = pGetStringProc;
    }
    else
    {
        goto EXIT;
    }

    pGetParamValueUlongProc = (COSAGetParamValueUlongProc)pPlugInfo->AcquireFunction("COSAGetParamValueUlong");

    if( pGetParamValueUlongProc != NULL)
    {
        g_GetParamValueUlong = pGetParamValueUlongProc;
    }
    else
    {
        goto EXIT;
    }

    pValInterfaceProc = (COSAValidateHierarchyInterfaceProc)pPlugInfo->AcquireFunction("COSAValidateHierarchyInterface");

    if ( pValInterfaceProc )
    {
        g_ValidateInterface = pValInterfaceProc;
    }
    else
    {
        goto EXIT;
    }

#ifdef _SOFTWAREMODULES_SUPPORT_NAF
    CosaSoftwareModulesInit(hCosaPlugInfo);
#endif

    pGetRegistryRootFolder = (COSAGetHandleProc)pPlugInfo->AcquireFunction("COSAGetRegistryRootFolder");

    if ( pGetRegistryRootFolder != NULL )
    {
        g_GetRegistryRootFolder = pGetRegistryRootFolder;
    }
    else
    {
        printf("!!! haha, catcha !!!\n");
        goto EXIT;
    }

    pGetInsNumberByIndexProc = (COSAGetInstanceNumberByIndexProc)pPlugInfo->AcquireFunction("COSAGetInstanceNumberByIndex");

    if ( pGetInsNumberByIndexProc != NULL )
    {
        g_GetInstanceNumberByIndex = pGetInsNumberByIndexProc;
    }
    else
    {
        goto EXIT;
    }

    pGetInterfaceByNameProc = (COSAGetInterfaceByNameProc)pPlugInfo->AcquireFunction("COSAGetInterfaceByName");

    if ( pGetInterfaceByNameProc != NULL )
    {
        g_GetInterfaceByName = pGetInterfaceByNameProc;
    }
    else
    {
        goto EXIT;
    }

    g_pXdnsCcdIf = g_GetInterfaceByName(g_pDslhDmlAgent, CCSP_CCD_INTERFACE_NAME);

    if ( !g_pXdnsCcdIf )
    {
        CcspTraceError(("g_pXdnsCcdIf is NULL !\n"));

        goto EXIT;
    }

    /* Get Message Bus Handle */
    g_GetMessageBusHandle = (COSAGetHandleProc)pPlugInfo->AcquireFunction("COSAGetMessageBusHandle");
    if ( g_GetMessageBusHandle == NULL )
    {
        goto EXIT;
    }

    g_MessageBusHandle = (ANSC_HANDLE)g_GetMessageBusHandle(g_pDslhDmlAgent);
    if ( g_MessageBusHandle == NULL )
    {
        goto EXIT;
    }
    g_MessageBusHandle_Irep = g_MessageBusHandle;

    g_GetSubsystemPrefix = (COSAGetSubsystemPrefixProc)pPlugInfo->AcquireFunction("COSAGetSubsystemPrefix");
    if ( g_GetSubsystemPrefix != NULL )
    {
        char*  tmpSubsystemPrefix;

        if (( tmpSubsystemPrefix = g_GetSubsystemPrefix(g_pDslhDmlAgent) ))
        {
            AnscCopyString(g_SubSysPrefix_Irep, tmpSubsystemPrefix);
        }
    }

    /* Create backend framework */
    g_pCosaBEManager = (PCOSA_BACKEND_MANAGER_OBJECT)CosaBackEndManagerCreate();

    if ( g_pCosaBEManager && g_pCosaBEManager->Initialize )
    {
        g_pCosaBEManager->hCosaPluginInfo = pPlugInfo;

        g_pCosaBEManager->Initialize   ((ANSC_HANDLE)g_pCosaBEManager);
    }

    /* Intialixing cache first time */
                clear_xdns_cache(&XDNS_Data_Cache);
                clear_xdns_cache(&XDNS_tmp_bck);


                init_xdns_cache(&XDNS_Data_Cache);


    return  0;

EXIT:

    return -1;

}

#if 0
int ANSC_EXPORT_API
COSA_Async_Init
    (
        ULONG                       uMaxVersionSupported,
        void*                       hCosaPlugInfo         /* PCOSA_PLUGIN_INFO passed in by the caller */
    )
{
    PCOSA_PLUGIN_INFO               pPlugInfo      = (PCOSA_PLUGIN_INFO)hCosaPlugInfo;

#if 0
    if (g_pCosaBEManager)
    {
#ifdef _COSA_SIM_
        COSAGetHandleProc         pProc          = (COSAGetHandleProc       )NULL;
        ULONG                     ulRole         = 0;

        pProc = (COSAGetHandleProc)pPlugInfo->AcquireFunction("COSAGetLPCRole");

        if ( pProc )
        {
            ulRole = (ULONG)(*pProc)();
        }

        /*for simulation, LPC manager to reset Wifi, LPC party to reset Moca*/
        if ( ulRole == LPC_ROLE_MANAGER )
        {
            PCOSA_DATAMODEL_WIFI pWifi = g_pCosaBEManager->hWifi;
            pWifi->Remove(pWifi);
            g_pCosaBEManager->hWifi = (ANSC_HANDLE)CosaWifiCreate();
        }
        else if ( ulRole == LPC_ROLE_PARTY )
        {
            PCOSA_DATAMODEL_MOCA pMoca = g_pCosaBEManager->hMoCA;
            pMoca->Remove(pMoca);
            g_pCosaBEManager->hMoCA = (ANSC_HANDLE)CosaMoCACreate();
        }
#endif

    }
    else
    {
        return -1;
    }

#endif
    return 0;
}

#endif

BOOL ANSC_EXPORT_API
COSA_IsObjSupported
    (
        char*                        pObjName
    )
{
    UNREFERENCED_PARAMETER(pObjName);
    /* COSA XML file will be generated based on standard TR-xxx data model definition.
     * By default, all the objects are expected to supported in the libraray.
     * Realistically, we will have certain ones cannot be supported at the early stage of development.
     * We can rule them out by return FALSE even if they're defined in COSA XML file.
     */

#if 0

    if (strcmp(pObjName, "InternetGatewayDevice.UserInterface.") == 0)
    {
        /* all the objects/parameters under "UserInterface" will not be populated in Data Model Tree. */
        return FALSE;
    }

#endif

    return TRUE;
}

void ANSC_EXPORT_API
COSA_Unload
    (
        void
    )
{
    ANSC_STATUS                     returnStatus            = ANSC_STATUS_SUCCESS;

    /* unload the memory here */
    returnStatus  =  CosaBackEndManagerRemove(g_pCosaBEManager);

    if ( returnStatus == ANSC_STATUS_SUCCESS )
    {
        g_pCosaBEManager = NULL;
    }
    else
    {
        /* print error trace*/
        g_pCosaBEManager = NULL;
    }
}

void ANSC_EXPORT_API
COSA_MemoryCheck
    (
        void
    )
{
    ANSC_STATUS                     returnStatus            = ANSC_STATUS_SUCCESS;
    PCOSA_PLUGIN_INFO               pPlugInfo               = (PCOSA_PLUGIN_INFO)g_pCosaBEManager->hCosaPluginInfo;

    /* unload the memory here */

    returnStatus  =  CosaBackEndManagerRemove(g_pCosaBEManager);

    if ( returnStatus == ANSC_STATUS_SUCCESS )
    {
        g_pCosaBEManager = NULL;
    }
    else
    {
        g_pCosaBEManager = NULL;
    }

    COSA_MemoryUsage();
    COSA_MemoryTable();

    g_pCosaBEManager = (PCOSA_BACKEND_MANAGER_OBJECT)CosaBackEndManagerCreate();

    if ( g_pCosaBEManager && g_pCosaBEManager->Initialize )
    {
        g_pCosaBEManager->hCosaPluginInfo = pPlugInfo;

        g_pCosaBEManager->Initialize   ((ANSC_HANDLE)g_pCosaBEManager);
    }
}

void ANSC_EXPORT_API
COSA_MemoryUsage
    (
        void
    )
{
    /*AnscTraceMemoryUsage();*/
}

void ANSC_EXPORT_API
COSA_MemoryTable
    (
        void
    )
{
    /*AnscTraceMemoryTable();*/
}
