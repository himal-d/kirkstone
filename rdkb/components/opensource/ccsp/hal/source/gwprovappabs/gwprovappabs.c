/*
 * If not stated otherwise in this file or this component's Licenses.txt file the
 * following copyright and licenses apply:
 *
 * Copyright 2023 RDK Management
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
#include <stdbool.h>
#include <sys/types.h>

int GWP_InitDB (void)
{
	return 0;
}

int sendPseudoBridgeModeMessage (unsigned char enable)
{
	return 0;
}

void eSafeDevice_Enable (int enableMode)
{
}

void eSafeDevice_Initialize (unsigned char *macAddr)
{
}

void eSafeDevice_AddeRouterPhysicalNetworkInterface (char *devName, bool addDel)
{
}

void eSafeDevice_SetErouterOperationMode (int operMode)
{
}

void eSafeDevice_SetProvisioningStatusProgress (int StatusProgress)
{
}

void eSafeDevice_GetErouterOperationMode (void *operMode)
{
}

void eSafeDevice_SetServiceIntImpact (void)
{
}

void eSafeDevice_SetErouterOperStatus (int operStatus)
{
}

void getNetworkDeviceMacAddress (unsigned char *macAddr)
{
}

void getMultiCastGroupAddress (unsigned char *inetAddr, unsigned char *inetMcgrpAddr)
{
}

void setNetworkDeviceMacAddress (const char *devName, unsigned char *macAddr)
{
}

void getInterfaceLinkLocalAddress (const char *ifname, unsigned char *linkLocalAddr)
{
}

void connectLocalBridge (bool a)
{
}

void notifyDocsisInitializedResponse (void)
{
}

void registerDocsisInitEvents (void)
{
}

int startDocsisCfgParsing (void)
{
}

void initializeDocsisInterface (void)
{
}

void registerDocsisEvents (void)
{
}

void SME_CreateEventHandler (void *pAppCallBack)
{
}

void  notificationReply_CfgFileForEsafe (void)
{
}

void getDocsisDbFactoryMode (unsigned int *factoryMode)
{
}

void getWanMacAddress (unsigned char *macAddr)
{
}

void startWebUIProcess (void)
{
}

void sendProcessReadySignal (void)
{
}

void registerProcessExceptionHandlers (char *name)
{
}

int parseTlv (unsigned char *confFileBuff, unsigned int confFileBuffLen)
{
}

int sendTLV11toSnmpAgent (void *Snmp_Tlv11Buf, int Snmp_Tlv11BufLen)
{
	return 0;
}

