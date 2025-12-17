/*
 * If not stated otherwise in this file or this component's Licenses.txt file the
 * following copyright and licenses apply:
 *
 * Copyright 2018 RDK Management
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
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <sys/types.h>
#include <sys/stat.h>
#include "ccsp_trace.h"
#include "cosa_rbus_handler_apis.h"
#include "cm_hal.h"
#include "cosa_apis.h"
#include <sysevent/sysevent.h>
#include "syscfg/syscfg.h"

#if defined (WAN_FAILOVER_SUPPORTED)
rbusHandle_t cm_rbus_handle;
CmAgent_Link_Status cmAgent_Link_Status;
unsigned int gSubscribersCount = 0;

BOOL
Rbus_CMAgent_SetParamUintValue
    (
       void*                 hInsContext,
       char*                       pParamName,
       uint                        uValue
    );
BOOL
Rbus_CMAgent_SetParamBoolValue
    (
        void*                 hInsContext,
        char*                       pParamName,
        BOOL                        bValue
    );
unsigned int g_CMRfSigStatSubCount = 0;

#define NUM_OF_RBUS_PARAMS sizeof(cmAgentRbusDataElements)/sizeof(cmAgentRbusDataElements[0])
/***********************************************************************

  Data Elements declaration:

 ***********************************************************************/
rbusDataElement_t cmAgentRbusDataElements[] = {
	{DOCSIS_LINK_STATUS_TR181, RBUS_ELEMENT_TYPE_EVENT, {getBoolHandler, NULL, NULL, NULL, eventSubHandler, NULL}},
	{DOCSIS_LINKDOWN_TR181, RBUS_ELEMENT_TYPE_EVENT, {getBoolHandler, SetBoolHandler, NULL, NULL, NULL, NULL}},
	{DOCSIS_LINKDOWNTIMEOUT_TR181, RBUS_ELEMENT_TYPE_EVENT, {getuintHandler, SetUintHandler, NULL, NULL, NULL, NULL}},
	{CABLE_MODEM_RF_SIGNAL_STATUS, RBUS_ELEMENT_TYPE_EVENT, {getBoolHandler, NULL, NULL, NULL, eventSubHandler, NULL}},   
};
#endif

#if defined (ENABLE_LLD_SUPPORT)

rbusHandle_t cm_lld_rbus_handle;

#define NUM_OF_LLD_RBUS_PARAMS sizeof(cmAgentLldRbusDataElements)/sizeof(cmAgentLldRbusDataElements[0])
/***********************************************************************

  Data Elements declaration:

 ***********************************************************************/
rbusDataElement_t cmAgentLldRbusDataElements[] = {

        {LLD_ENABLE_TR181, RBUS_ELEMENT_TYPE_EVENT, {getLLDBoolHandler, setLLDEnableBoolHandler, NULL, NULL, lldEventSubHandler, NULL}},
};


BOOL
Rbus_LLDEnabled_SetParamBoolValue
    (
        void*                 hInsContext,
        char*                       pParamName,
        BOOL                        bValue
    );


CmAgent_LLDEnable cmAgent_Lld_Enable;

#endif

#if defined (WAN_FAILOVER_SUPPORTED)

/***********************************************************************

  Get Handler APIs for objects of type RBUS_BOOL:

 ***********************************************************************/
rbusError_t getBoolHandler(rbusHandle_t handle, rbusProperty_t property, rbusGetHandlerOptions_t *opts)
{
	char const *name = rbusProperty_GetName(property);
	(void)handle;
	(void)opts;
	rbusValue_t value;
	rbusValue_Init(&value);

	if (strcmp(name, DOCSIS_LINK_STATUS_TR181) == 0)
	{
		CcspTraceWarning(("Getting DOCSIS link status value, new value = '%d'\n", cmAgent_Link_Status.DocsisLinkStatus));
		rbusValue_SetBoolean(value, cmAgent_Link_Status.DocsisLinkStatus);
	}
	else if (strcmp(name, CABLE_MODEM_RF_SIGNAL_STATUS) == 0)
       {
                  CcspTraceWarning(("Getting DOCSIS link status value, new value = '%s'\n", cmAgent_Link_Status.CableModemRfSignalStatus?"true":"false"));
                  rbusValue_SetBoolean(value, cmAgent_Link_Status.CableModemRfSignalStatus);
       }

	else if(strcmp(name, DOCSIS_LINKDOWN_TR181) == 0)
	{
		CcspTraceWarning(("Getting DOCSIS link Down value, new value = '%d'\n", cmAgent_Link_Status.DocsisLinkDown));
		rbusValue_SetBoolean(value, cmAgent_Link_Status.DocsisLinkDown);
	}
	else
	{
		CcspTraceWarning(("CMAgent rbus get handler invalid input\n"));
		return RBUS_ERROR_INVALID_INPUT;
	}
	rbusProperty_SetValue(property, value);
	rbusValue_Release(value);

	return RBUS_ERROR_SUCCESS;
}
/***********************************************************************

 Set Handler API for objects of type RBUS_BOOLEAN for objects:

***********************************************************************/

rbusError_t SetBoolHandler(rbusHandle_t handle, rbusProperty_t property, rbusSetHandlerOptions_t* opts)
{
    (void)handle;
    (void)opts;
    
    bool rc = false;
    char const* propName = rbusProperty_GetName(property);
    char* param = strdup(GetParamName(propName));
    rbusValue_t value = rbusProperty_GetValue(property);

    CcspTraceWarning(("%s called for param='%s'\n", __FUNCTION__, param));
 
    if(value)
    {
        if(rbusValue_GetType(value) == RBUS_BOOLEAN)
        {
            rc = Rbus_CMAgent_SetParamBoolValue(NULL,param,rbusValue_GetBoolean(value));
            free(param);
            if(!rc)
            {
                CcspTraceWarning(("Set_DocsisTr181Link_Param DOCSIS_LINKDOWN_TR181 failed\n"));
                return RBUS_ERROR_BUS_ERROR;
            }
            return RBUS_ERROR_SUCCESS;
        }
	else
	{
            CcspTraceWarning(("%s result:FAIL error:'unexpected type %d'\n", __FUNCTION__, rbusValue_GetType(value)));
	}
    }
    else
    {
        CcspTraceWarning(("%s result:FAIL value=NULL param='%s'\n", __FUNCTION__, param));
    }
    free(param);
    return RBUS_ERROR_BUS_ERROR;
}
/***********************************************************************

  Get Handler APIs for objects of type RBUS_UINT:

 ***********************************************************************/
rbusError_t getuintHandler(rbusHandle_t handle, rbusProperty_t property, rbusGetHandlerOptions_t *opts)
{
	char const *name = rbusProperty_GetName(property);
	char ParamValue[16];
	(void)handle;
	(void)opts;
	rbusValue_t value;
	rbusValue_Init(&value);

	if (strcmp(name, DOCSIS_LINKDOWNTIMEOUT_TR181) == 0)
	{
		syscfg_get(NULL, DOCSISLINKDOWNTIMEOUT, ParamValue, sizeof(ParamValue));
		cmAgent_Link_Status.DocsisLinkDownTimeOut=atoi(ParamValue);
		CcspTraceWarning(("Getting DOCSIS link Down TimeOut value, new value = '%d'\n", cmAgent_Link_Status.DocsisLinkDownTimeOut));
		rbusValue_SetUInt32(value, cmAgent_Link_Status.DocsisLinkDownTimeOut);
	}
	else
	{
		CcspTraceWarning(("CMAgent rbus get handler invalid input\n"));
		return RBUS_ERROR_INVALID_INPUT;
	}
	rbusProperty_SetValue(property, value);
	rbusValue_Release(value);

	return RBUS_ERROR_SUCCESS;
}
/***********************************************************************

 Set Handler API for objects of type RBUS_UINT for objects:

***********************************************************************/
rbusError_t SetUintHandler(rbusHandle_t handle, rbusProperty_t property, rbusSetHandlerOptions_t* opts)
{
    (void)handle;
    (void)opts;
    
    bool rc = false;
    char const* propName = rbusProperty_GetName(property);
    char* param = strdup(GetParamName(propName));
    rbusValue_t value = rbusProperty_GetValue(property);

    CcspTraceWarning(("%s called for param='%s'\n", __FUNCTION__, param));
 
    if(value)
    {
        if(rbusValue_GetType(value) == RBUS_UINT32)
        {
            rc = Rbus_CMAgent_SetParamUintValue(NULL,param,(uint)rbusValue_GetUInt32(value));
            free(param);
            if(!rc)
            {
                CcspTraceWarning(("Set_DocsisTr181Link_Param DOCSIS_LINKDOWNTIMEOUT_TR181 failed\n"));
                return RBUS_ERROR_BUS_ERROR;
            }
            return RBUS_ERROR_SUCCESS;
        }
	else
        {
            CcspTraceWarning(("%s result:FAIL error:'unexpected type %d'\n", __FUNCTION__, rbusValue_GetType(value)));
        }
    }
    else
    {
        CcspTraceWarning(("%s result:FAIL value=NULL param='%s'\n", __FUNCTION__, param));
    }
    free(param);
    return RBUS_ERROR_BUS_ERROR;
}

/***********************************************************************

  Event subscribe handler API for objects:

 ***********************************************************************/
rbusError_t eventSubHandler(rbusHandle_t handle, rbusEventSubAction_t action, const char *eventName, rbusFilter_t filter, int32_t interval, bool *autoPublish)
{
	(void)handle;
	(void)filter;
	(void)interval;

	*autoPublish = false;

	if (!strcmp(DOCSIS_LINK_STATUS_TR181, eventName))
	{
		if (action == RBUS_EVENT_ACTION_SUBSCRIBE)
		{
			gSubscribersCount += 1;
		}
		else
		{
			if (gSubscribersCount > 0)
			{
				gSubscribersCount -= 1;
			}
		}
		CcspTraceWarning(("Subscribers count changed, new value=%d\n", gSubscribersCount));
	}
	else if (!strcmp(CABLE_MODEM_RF_SIGNAL_STATUS, eventName))
	{
		if (action == RBUS_EVENT_ACTION_SUBSCRIBE)
		{
			g_CMRfSigStatSubCount += 1;
		}
		else
		{
			if (g_CMRfSigStatSubCount > 0)
			{
				g_CMRfSigStatSubCount -= 1;
			}
		}
		CcspTraceWarning(("Cable Modem Rf Signal Status Subscribers count changed, new value=%d\n", g_CMRfSigStatSubCount));
	}
	else
	{
		CcspTraceWarning(("provider: eventSubHandler unexpected eventName %s\n", eventName));
	}
	return RBUS_ERROR_SUCCESS;
}

/*******************************************************************************

  initLinkStatus(): Initialize CmAgent_Link_Status struct with default values

 ********************************************************************************/
void initLinkStatus()
{
	char ParamValue[16];
	cmAgent_Link_Status.DocsisLinkStatus = false;
	CcspTraceWarning(("Initialized DOCSIS link status with default values.\n"));
	cmAgent_Link_Status.DocsisLinkDown = false;
	if(!syscfg_get(NULL, DOCSISLINKDOWNTIMEOUT, ParamValue, sizeof(ParamValue)))
	{
		cmAgent_Link_Status.DocsisLinkDownTimeOut=atoi(ParamValue);
		CcspTraceWarning(("Initialized DOCSIS cmAgent_Link_Status.DocsisLinkDownTimeOut:%d\n",cmAgent_Link_Status.DocsisLinkDownTimeOut));
	}
	
	/* fetch and set cable modem RF signal status */
	//CID 330325 : Unchecked return value
	if (ANSC_STATUS_SUCCESS == docsis_IsEnergyDetected(&cmAgent_Link_Status.CableModemRfSignalStatus))
        {
	    CcspTraceWarning(("Initialized Cable modem Rf signal status with value='%s'.\n", cmAgent_Link_Status.CableModemRfSignalStatus?"true":"false"));

	    CcspTraceWarning(("Initializing CM agent link status with default values.\n"));
	}
}
/*******************************************************************************

  publishDocsisLinkStatus(): publish DocsisLinkStatus event after event value gets updated

 ********************************************************************************/
 
void publishDocsisLinkStatus(bool link_status)
{	
	rbusError_t ret = RBUS_ERROR_SUCCESS;
	bool oldDocsisLinkStatus = cmAgent_Link_Status.DocsisLinkStatus;
	//update DocsisLinkStatus with new value
	cmAgent_Link_Status.DocsisLinkStatus = link_status;
	CcspTraceInfo(("Publishing DOCSIS link status with updated value=%s\n", cmAgent_Link_Status.DocsisLinkStatus ? "true" : "false"));
	if (gSubscribersCount > 0)
	{
		ret = sendBoolUpdateEvent(cm_rbus_handle,DOCSIS_LINK_STATUS_TR181, cmAgent_Link_Status.DocsisLinkStatus, oldDocsisLinkStatus);
		if(ret == RBUS_ERROR_SUCCESS) {
			CcspTraceInfo(("Published DOCSIS link status with updated value.\n"));
		}
	}
}

/*******************************************************************************

Set CM agent bool parameters

 ********************************************************************************/

BOOL
Rbus_CMAgent_SetParamBoolValue
    (
        void*                 hInsContext,
        char*                       pParamName,
        BOOL                        bValue
    )
{
	UNREFERENCED_PARAMETER(hInsContext);
	if (strcmp(pParamName, "LinkDown") == 0)
	{
		if(cmAgent_Link_Status.DocsisLinkDown!=bValue)
		{
			cmAgent_Link_Status.DocsisLinkDown= bValue;
			//SendSignalConditionalPthread();
                        if(cmAgent_Link_Status.pDocsisLinkdowSignal!=NULL)
			{
				cmAgent_Link_Status.pDocsisLinkdowSignal();
			}
			else
			{
				CcspTraceInfo(("%s in this function address not assigned to pDocsisLinkdowSignal function pointer\n",__FUNCTION__));
			}
			CcspTraceInfo(("%s : parameter name = '%s', value = '%d'\n",__FUNCTION__,pParamName,cmAgent_Link_Status.DocsisLinkDown));
			return TRUE;
		}
		else
		{
		 	CcspTraceInfo(("%s : trying to set same value for parameter '%s', value is '%d'\n",__FUNCTION__,pParamName,cmAgent_Link_Status.DocsisLinkDown));
			return FALSE;
		}
	}
	CcspTraceInfo(("Unsupported parameter '%s'\n", pParamName));
	 return FALSE;
}
/*******************************************************************************

 set the CM agent uint parameters

 ********************************************************************************/
BOOL
Rbus_CMAgent_SetParamUintValue
    (
       void*                 hInsContext,
       char*                       pParamName,
       uint                        uValue
    )
{
	UNREFERENCED_PARAMETER(hInsContext); 
	if (strcmp(pParamName, "LinkDownTimeout") == 0)
	{
	 	if(cmAgent_Link_Status.DocsisLinkDownTimeOut!=uValue)
		{ 
			cmAgent_Link_Status.DocsisLinkDownTimeOut= uValue;
			syscfg_set_u_commit( NULL, DOCSISLINKDOWNTIMEOUT,cmAgent_Link_Status.DocsisLinkDownTimeOut);
			CcspTraceInfo(("%s : parameter name ='%s', value = '%d'\n", __FUNCTION__,pParamName,cmAgent_Link_Status.DocsisLinkDownTimeOut));
			return TRUE;
		 }
		else
		{
			CcspTraceWarning(("%s trying to set same value for parameter '%s', value is '%d' \n",__FUNCTION__, pParamName,cmAgent_Link_Status.DocsisLinkDownTimeOut));
			return FALSE;
 		}
	}
	CcspTraceInfo(("Unsupported parameter '%s'\n", pParamName));
	return FALSE;
}

/*******************************************************************************

 SetDocsisLinkdowSignalfunc is used to assigned function to function pointer
 
 ********************************************************************************/
BOOL SetDocsisLinkdowSignalfunc(fpDocsisLinkdownSignal CreateThreadandSendCondSignalToPthreadfunc)
{
	if(CreateThreadandSendCondSignalToPthreadfunc==NULL)
	{
		CcspTraceInfo(("%s Received NULL pointer, assigning pDocsisLinkdowSignal to NULL\n",__FUNCTION__));
          	cmAgent_Link_Status.pDocsisLinkdowSignal = NULL;
		return FALSE;
	}
	cmAgent_Link_Status.pDocsisLinkdowSignal=CreateThreadandSendCondSignalToPthreadfunc;
	return TRUE;
}

/*******************************************************************************
  publishCableModemRfSignalStatus(): publish CableModemRfSignalStatus event after event value gets updated

 ********************************************************************************/
void publishCableModemRfSignalStatus() {
	/* fetch current and previous cable modem rf signal status value */
    BOOL currentRfSignalStatus, prevRfSignalStatus;
    if (ANSC_STATUS_SUCCESS == docsis_IsEnergyDetected(&currentRfSignalStatus)) {
        prevRfSignalStatus = cmAgent_Link_Status.CableModemRfSignalStatus;
	CcspTraceInfo(("Current RF Signal Value=%s\n", currentRfSignalStatus? "true" : "false"));
        /* publish the cable modem rf signal status value if valu changed */
        if (prevRfSignalStatus != currentRfSignalStatus) {

	    CcspTraceInfo(("Current RF Signal value is not equal to previous Value\n"));
	    cmAgent_Link_Status.CableModemRfSignalStatus = currentRfSignalStatus;
            publishCableModemRfSignalStatusValue(currentRfSignalStatus);
        }
    }
    else {
        CcspTraceError((" Failed to get RfSignalStatus \n"));
    }
}

void publishCableModemRfSignalStatusValue(bool link_status)
{	
	rbusError_t ret = RBUS_ERROR_SUCCESS;
	bool oldCableModemRfSignalStatus = cmAgent_Link_Status.CableModemRfSignalStatus;
	//update DocsisLinkStatus with new value
	cmAgent_Link_Status.DocsisLinkStatus = link_status;
	CcspTraceInfo(("Publishing cable modem Rf signal status with updated value=%s\n", cmAgent_Link_Status.CableModemRfSignalStatus ? "true" : "false"));
	if (g_CMRfSigStatSubCount > 0)
	{
		ret = sendBoolUpdateEvent(cm_rbus_handle,CABLE_MODEM_RF_SIGNAL_STATUS, cmAgent_Link_Status.CableModemRfSignalStatus, oldCableModemRfSignalStatus);
		if(ret == RBUS_ERROR_SUCCESS) {
			CcspTraceInfo(("Published cable modem Rf signal status with updated value.\n"));
		}
	}
}
/***********************************************************************

  cmAgentRbusInit(): Initialize Rbus and data elements

 ***********************************************************************/
rbusError_t cmAgentRbusInit()
{
    int rc = RBUS_ERROR_SUCCESS;
    if(RBUS_ENABLED != rbus_checkStatus())
    {
        CcspTraceWarning(("%s: RBUS not available. Events are not supported\n", __FUNCTION__));
        return RBUS_ERROR_BUS_ERROR;
    }
    rc = rbus_open(&cm_rbus_handle, RBUS_COMPONENT_NAME);
    if (rc != RBUS_ERROR_SUCCESS)
    {
        CcspTraceWarning(("CMAgent rbus initialization failed\n"));
        rc = RBUS_ERROR_NOT_INITIALIZED;
        return rc;
    }
    
    // Register data elements
    rc = rbus_regDataElements(cm_rbus_handle, NUM_OF_RBUS_PARAMS, cmAgentRbusDataElements);

    if (rc != RBUS_ERROR_SUCCESS)
    {
        CcspTraceWarning(("rbus register data elements failed\n"));
        rc = rbus_close(cm_rbus_handle);
        return rc;
    }

    //Initialize CmAgent_Link_Status struct with default values 
    initLinkStatus();
    return rc;
}
#endif

/*******************************************************************************

  sendUpdateEvent(): publish event after event value gets updated

 ********************************************************************************/
rbusError_t sendBoolUpdateEvent(rbusHandle_t cm_handle, char* event_name , bool eventNewData, bool eventOldData)
{
    rbusEvent_t event;
    rbusObject_t data;
    rbusValue_t value;
    rbusValue_t oldVal;
    rbusValue_t byVal;
    rbusError_t ret = RBUS_ERROR_SUCCESS; 
    
    //initialize and set previous value for the event
    rbusValue_Init(&oldVal);
    rbusValue_SetBoolean(oldVal, eventOldData);
    //initialize and set new value for the event
    rbusValue_Init(&value);
    rbusValue_SetBoolean(value, eventNewData);
    //initialize and set responsible component name for value change
    rbusValue_Init(&byVal);
    rbusValue_SetString(byVal, RBUS_COMPONENT_NAME);
    //initialize and set rbusObject with desired values
    rbusObject_Init(&data, NULL);
    rbusObject_SetValue(data, "value", value);
    rbusObject_SetValue(data, "oldValue", oldVal);
    rbusObject_SetValue(data, "by", byVal);
    //set data to be transferred
    event.name = event_name;
    event.data = data;
    event.type = RBUS_EVENT_VALUE_CHANGED;
    //publish the event
    ret = rbusEvent_Publish(cm_handle, &event);
    if(ret != RBUS_ERROR_SUCCESS) {
        CcspTraceWarning(("rbusEvent_Publish for %s failed: %d\n", event_name, ret));
    }
    //release all initialized rbusValue objects
    rbusValue_Release(value);
    rbusValue_Release(oldVal);
    rbusValue_Release(byVal);
    rbusObject_Release(data);
    return ret;
}


/*******************************************************************************

 GetParamName from arg and return parameter name

 ********************************************************************************/
char const* GetParamName(char const* path)
{
    char const* p = path + strlen(path);
    while(p > path && *(p-1) != '.')
        p--;
    return p;
}

#if defined (ENABLE_LLD_SUPPORT)

rbusError_t cmAgentLldRbusInit()
{
    int rc = RBUS_ERROR_SUCCESS;
    if(RBUS_ENABLED != rbus_checkStatus())
    {
        CcspTraceWarning(("%s: RBUS not available. Events are not supported\n", __FUNCTION__));
        return RBUS_ERROR_BUS_ERROR;
    }
    rc = rbus_open(&cm_lld_rbus_handle, "CMAgentLLDEnable");
    if (rc != RBUS_ERROR_SUCCESS)
    {
        CcspTraceWarning(("CMAgent rbus initialization failed\n"));
        rc = RBUS_ERROR_NOT_INITIALIZED;
        return rc;
    }
    
    // Register data elements
    rc = rbus_regDataElements(cm_lld_rbus_handle, NUM_OF_LLD_RBUS_PARAMS, cmAgentLldRbusDataElements);

    if (rc != RBUS_ERROR_SUCCESS)
    {
        CcspTraceWarning(("LLD rbus register data elements failed\n"));
        rc = rbus_close(cm_lld_rbus_handle);
        return rc;
    }
    initLLDEnable();
    return rc;
}

void initLLDEnable()
{
    char LLDEnable[16];
    if(!syscfg_get(NULL, LLDENABLE, LLDEnable, sizeof(LLDEnable)))
    {
        CcspTraceInfo(("Initialized LLD Enable with %s values.\n",LLDEnable));
        if(strcmp(LLDEnable,"true") == 0)
        {
            cmAgent_Lld_Enable.lldenable = true;
        }
        else
        {
            cmAgent_Lld_Enable.lldenable = false;
        }
    }
}

void publishLLDEnableValueChange(bool newValue)
{
    rbusError_t ret = RBUS_ERROR_SUCCESS;
    bool oldValue = cmAgent_Lld_Enable.lldenable;
    //update DocsisLinkStatus with new value
    cmAgent_Lld_Enable.lldenable = newValue;
    
    if( syscfg_set( NULL, LLDENABLE, cmAgent_Lld_Enable.lldenable? "true":"false" ) != 0 )
    {
        CcspTraceWarning(("syscfg_set failed '%s'\n",__FUNCTION__));
    }
		
    CcspTraceInfo(("Publishing LLDEnable status updated value=%s\n", cmAgent_Lld_Enable.lldenable? "true" : "false"));

    ret = sendBoolUpdateEvent(cm_lld_rbus_handle, LLD_ENABLE_TR181, cmAgent_Lld_Enable.lldenable, oldValue);
    if(ret == RBUS_ERROR_SUCCESS) {
        CcspTraceInfo(("Published LLDEnable with updated value.\n"));
    }
}

/***********************************************************************

  Event subscribe handler API for objects:

 ***********************************************************************/
rbusError_t lldEventSubHandler(rbusHandle_t handleLld, rbusEventSubAction_t action, const char *eventName, rbusFilter_t filter, int32_t interval, bool *autoPublishLld)
{
    (void)handleLld;
    (void)filter;
    (void)interval;

    *autoPublishLld = false;
    if (!strcmp(LLD_ENABLE_TR181, eventName))
    {
        if (action == RBUS_EVENT_ACTION_SUBSCRIBE)
        {
            CcspTraceInfo(("Subscribers count increased for event [%s] \n", eventName));
        }
        else if (action == RBUS_EVENT_ACTION_UNSUBSCRIBE)
	{
            CcspTraceInfo(("Subscribers count decreased for event [%s] \n", eventName));
        }       
    }
    else
    {
        CcspTraceWarning(("provider: eventSubHandler unexpected eventName %s\n", eventName));
    }
    return RBUS_ERROR_SUCCESS;
}

/*******************************************************************************

Set CM agent bool parameters

********************************************************************************/
BOOL
Rbus_LLDEnabled_SetParamBoolValue
    (
        void*                 hInsContext,
        char*                 pParamName,
        BOOL                  bValue
    )
{
    UNREFERENCED_PARAMETER(hInsContext);
    if (strcmp(pParamName, "Enable") == 0)
    {
        if(cmAgent_Lld_Enable.lldenable != bValue)
        {
            publishLLDEnableValueChange(bValue);	
            return TRUE;
        }
        else
        {
            CcspTraceWarning(("%s trying to set same value for parameter '%s', value is '%d'\n",__FUNCTION__, pParamName,cmAgent_Lld_Enable.lldenable));
            return FALSE;
        }
    }
    CcspTraceInfo(("Unsupported parameter '%s'\n", pParamName));
    return FALSE;
}

/***********************************************************************

  Get Handler APIs for objects of type RBUS_BOOL:

 ***********************************************************************/
rbusError_t getLLDBoolHandler(rbusHandle_t handleLld, rbusProperty_t property, rbusGetHandlerOptions_t *opts)
{
    char const *name = rbusProperty_GetName(property);
    (void)handleLld;
    (void)opts;
    rbusValue_t value;
    char LLDEnable[16] = {0};
    rbusValue_Init(&value);
    if(strcmp(name, LLD_ENABLE_TR181) == 0)
    {
        if(!syscfg_get(NULL, LLDENABLE, LLDEnable, sizeof(LLDEnable)))
        {  
            if(strcmp(LLDEnable,"true") == 0)
            {
                cmAgent_Lld_Enable.lldenable = true;
           
            }
            else
            {
                cmAgent_Lld_Enable.lldenable = false;
            }
        }
        CcspTraceInfo(("Getting LLDEnable value, new value = '%d'\n", cmAgent_Lld_Enable.lldenable));
        rbusValue_SetBoolean(value, cmAgent_Lld_Enable.lldenable);
    }
    else
    {
        CcspTraceWarning(("CMAgentLLD rbus get handler invalid input\n"));
	return RBUS_ERROR_INVALID_INPUT;
    }
    rbusProperty_SetValue(property, value);
    rbusValue_Release(value);

    return RBUS_ERROR_SUCCESS;
}

/***********************************************************************

 Set Handler API for objects of type RBUS_BOOLEAN for objects:

***********************************************************************/

rbusError_t setLLDEnableBoolHandler(rbusHandle_t handleLld, rbusProperty_t property, rbusSetHandlerOptions_t* opts)
{
    (void)handleLld;
    (void)opts;
    
    bool rc = false;
    char const* propName = rbusProperty_GetName(property);
    char* param = strdup(GetParamName(propName));
    rbusValue_t value = rbusProperty_GetValue(property);

    CcspTraceWarning(("%s called for param='%s'\n", __FUNCTION__, param));
 
    if(value)
    {
        if(rbusValue_GetType(value) == RBUS_BOOLEAN)
        {
            rc = Rbus_LLDEnabled_SetParamBoolValue(NULL,param,rbusValue_GetBoolean(value));
            free(param);
            if(!rc)
            {
                CcspTraceWarning((" setting of %s failed\n",param));
                return RBUS_ERROR_BUS_ERROR;
            }
            return RBUS_ERROR_SUCCESS;
        }
        else
        {
            CcspTraceWarning(("%s result:FAIL error:'unexpected type %d'\n", __FUNCTION__, rbusValue_GetType(value)));
        }
    }
    else
    {
        CcspTraceWarning(("%s result:FAIL value=NULL param='%s'\n", __FUNCTION__, param));
    }
    free(param);
    return RBUS_ERROR_BUS_ERROR;
}
#endif
