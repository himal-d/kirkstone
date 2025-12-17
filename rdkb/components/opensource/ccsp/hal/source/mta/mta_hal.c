/*
 * If not stated otherwise in this file or this component's Licenses.txt file the
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

/**********************************************************************

    module: mta_hal.h

        For CCSP Component:  CcspMtaAgent

    ---------------------------------------------------------------

    description:

        This header file gives the function call prototypes and 
        structure definitions used for the RDK-Broadband 
        hardware abstraction layer for Cable Modem

        NOTE:
        THIS VERSION IS AN EARLY DRAFT INTENDED TO GET COMMENTS FROM COMCAST.
        TESTING HAS NOT YET BEEN COMPLETED.  
       
    ---------------------------------------------------------------

    environment:

        This HAL layer is intended to support cable modem drivers 
        through an open API.  
        Changes may be needed to support different hardware enviornments.

    ---------------------------------------------------------------

    author:

        Cisco

**********************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "mta_hal.h"
#include "safec_lib.h"

#define _ERROR_ "NOT SUPPORTED"

// COSA_DML_MTA_LOG MtaLog = { TRUE, TRUE };

int mta_hal_InitDB (void)
{
    /*
       Note that this init function may get called more than once.
       The code should ensure that that doesn't cause problems.
    */
    static int initdone = 0;

    if (initdone) {
        return RETURN_OK;
    }

    initdone = 1;

    return RETURN_OK;
}

INT   mta_hal_GetDHCPInfo(PMTAMGMT_MTA_DHCP_INFO pInfo) {

    errno_t rc = -1;
    rc = memset_s(pInfo, sizeof(MTAMGMT_MTA_DHCP_INFO), 0, sizeof(MTAMGMT_MTA_DHCP_INFO));
    ERR_CHK(rc);

    pInfo->LeaseTimeRemaining = 6;

    pInfo->PrimaryDHCPServer.Value = 0x06060606U;
    pInfo->SecondaryDHCPServer.Value = 0x06060606U;

    pInfo->IPAddress.Value = 0x06060606U;
    pInfo->SubnetMask.Value = 0x06060606U;
    pInfo->Gateway.Value = 0x06060606U;
    pInfo->PrimaryDNS.Value = 0x06060606U;
    pInfo->SecondaryDNS.Value = 0x06060606U;

    strcpy_s(pInfo->BootFileName, sizeof(pInfo->BootFileName) , "BootFileName");
    ERR_CHK(rc);
    strcpy_s(pInfo->FQDN, sizeof(pInfo->FQDN) ,"FQDN");
    ERR_CHK(rc);
    strcpy_s(pInfo->RebindTimeRemaining, sizeof(pInfo->RebindTimeRemaining) ,"RebindTimeRemaining");
    ERR_CHK(rc);
    strcpy_s(pInfo->RenewTimeRemaining, sizeof(pInfo->RenewTimeRemaining) ,"RenewTimeRemaining");
    ERR_CHK(rc);
    strcpy_s(pInfo->DHCPOption3, sizeof(pInfo->DHCPOption3) ,"DHCPOption3");
    ERR_CHK(rc);
    strcpy_s(pInfo->DHCPOption6, sizeof(pInfo->DHCPOption6) , "DHCPOption6");
    ERR_CHK(rc);
    strcpy_s(pInfo->DHCPOption7, sizeof(pInfo->DHCPOption7) ,"DHCPOption7");
    ERR_CHK(rc);
    strcpy_s(pInfo->DHCPOption8, sizeof(pInfo->DHCPOption8) ,"DHCPOption8");
    ERR_CHK(rc);
    strcpy_s(pInfo->PCVersion, sizeof(pInfo->PCVersion) , "PCVersion");
    ERR_CHK(rc);
    strcpy_s(pInfo->MACAddress, sizeof(pInfo->MACAddress) ,"66:66:66:66:66:66");
    ERR_CHK(rc);

    return RETURN_OK;
}

INT mta_hal_GetDHCPV6Info(PMTAMGMT_MTA_DHCPv6_INFO pInfo)
{
    memset(pInfo, 0, sizeof(MTAMGMT_MTA_DHCPv6_INFO));

    return RETURN_OK;
}

/*
COSA_MTA_PKTC g_mta_pktc = {FALSE,6,6,6,6,6,6,6,6,6,6};

ANSC_STATUS
CosaDmlMTAGetPktc
    (
        ANSC_HANDLE                 hContext,
        PCOSA_MTA_PKTC              pPktc
    )
{
    AnscCopyMemory(pPktc, &g_mta_pktc, sizeof(COSA_MTA_PKTC));
    return ANSC_STATUS_SUCCESS;
}

ANSC_STATUS
CosaDmlMTASetPktc
    (
        ANSC_HANDLE                 hContext,
        PCOSA_MTA_PKTC              pPktc
    )
{
    AnscCopyMemory(&g_mta_pktc, pPktc, sizeof(COSA_MTA_PKTC));
    return ANSC_STATUS_SUCCESS;
}
*/

ULONG mta_hal_LineTableGetNumberOfEntries() { return 1; }

INT   mta_hal_LineTableGetEntry(ULONG Index, PMTAMGMT_MTA_LINETABLE_INFO pEntry) {

    errno_t rc = -1;
    rc = memset_s(pEntry, sizeof(MTAMGMT_MTA_LINETABLE_INFO), 0, sizeof(MTAMGMT_MTA_LINETABLE_INFO));
    ERR_CHK(rc);

	pEntry->InstanceNumber = Index + 1;	

    pEntry->LineNumber = 6;
    pEntry->Status = 1;
    pEntry->CAPort = 6;
    pEntry->MWD = 6;

    rc = strcpy_s(pEntry->ForeignEMF, sizeof(pEntry->ForeignEMF) , "ForeignEMF");
    ERR_CHK(rc);
    rc = strcpy_s(pEntry->HazardousPotential, sizeof(pEntry->HazardousPotential) , "HazardousPotential");
    ERR_CHK(rc);
    rc = strcpy_s(pEntry->ResistiveFaults, sizeof(pEntry->ResistiveFaults) ,"ResistiveFaults");
    ERR_CHK(rc);
    rc = strcpy_s(pEntry->ReceiverOffHook, sizeof(pEntry->ReceiverOffHook) ,"ReceiverOffHook");
    ERR_CHK(rc);
    rc = strcpy_s(pEntry->RingerEquivalency, sizeof(pEntry->RingerEquivalency) ,"RingerEquivalency");
    ERR_CHK(rc);
    rc = strcpy_s(pEntry->CAName, sizeof(pEntry->CAName) ,"CAName");
    ERR_CHK(rc);

    return RETURN_OK;
}

INT   mta_hal_TriggerDiagnostics(ULONG Index) { return RETURN_OK; }

INT   mta_hal_GetServiceFlow(ULONG* Count, PMTAMGMT_MTA_SERVICE_FLOW *ppCfg) {

    *Count = 1;
    errno_t rc = -1;

    *ppCfg = (PMTAMGMT_MTA_SERVICE_FLOW)malloc(sizeof(MTAMGMT_MTA_SERVICE_FLOW));
    rc = memset_s(*ppCfg, sizeof(MTAMGMT_MTA_SERVICE_FLOW), 0, sizeof(MTAMGMT_MTA_SERVICE_FLOW));
    ERR_CHK(rc);

    /* ppcfg is a pointer pointing to an array of size 16 */
    rc = strcpy_s((*ppCfg)->Direction, 16 , "upstream");
    ERR_CHK(rc);
    (*ppCfg)->MaxTrafficBurst = 6;
    (*ppCfg)->MaxTrafficRate = 6;
    (*ppCfg)->MinReservedPkt = 6;
    (*ppCfg)->MinReservedRate = 6;
    (*ppCfg)->NomGrantInterval = 6;
    (*ppCfg)->NomPollInterval = 6;
    (*ppCfg)->ScheduleType = 6;
    (*ppCfg)->SFID = 6;
    (*ppCfg)->TolGrantJitter = 6;
    (*ppCfg)->UnsolicitGrantSize = 6;

    return RETURN_OK;
}

INT   mta_hal_DectGetEnable(BOOLEAN *pBool) { *pBool = FALSE; return RETURN_OK; }


INT mta_hal_DectSetEnable(BOOLEAN bBool)
{
	return RETURN_OK;
}


INT mta_hal_DectGetRegistrationMode(BOOLEAN* pBool)
{
	return RETURN_OK;
}

INT mta_hal_DectSetRegistrationMode(BOOLEAN bBool)
{
	return RETURN_OK;
}

INT mta_hal_DectDeregisterDectHandset(ULONG uValue)
{
	return RETURN_OK;
}

INT mta_hal_GetDect(PMTAMGMT_MTA_DECT pDect)
{
	return RETURN_OK;
}

INT mta_hal_GetDectPIN(char* pPINString)
{
	return RETURN_OK;
}

INT mta_hal_SetDectPIN(char* pPINString)
{
	return RETURN_OK;
}

INT mta_hal_GetHandsets(ULONG* pulCount, PMTAMGMT_MTA_HANDSETS_INFO* ppHandsets)
{
	return RETURN_OK;
}


/*
COSA_MTA_DECT g_mta_dect = {6,6, "Hardware", "RFPI", "Software"};

ANSC_STATUS
CosaDmlMTAGetDect
    (
        ANSC_HANDLE                 hContext,
        PCOSA_MTA_DECT              pDect
    )
{
    AnscCopyMemory(pDect, &g_mta_dect, sizeof(COSA_MTA_DECT));
    return ANSC_STATUS_SUCCESS;
}

ANSC_STATUS
CosaDmlMTASetDect
    (
        ANSC_HANDLE                 hContext,
        PCOSA_MTA_DECT              pDect
    )
{
    AnscCopyMemory(&g_mta_dect, pDect, sizeof(COSA_MTA_DECT));
    return ANSC_STATUS_SUCCESS;
}

ULONG
CosaDmlMTAHandsetsGetNumberOfEntries
    (
        ANSC_HANDLE                 hContext
    )
{
    return 1;
}

ANSC_STATUS
CosaDmlMTAHandsetsGetEntry
    (
        ANSC_HANDLE                 hContext,
        ULONG                       ulIndex,
        PCOSA_MTA_HANDSETS_INFO     pEntry
    )
{
    pEntry->Status = FALSE;
    strcpy(pEntry->HandsetFirmware, "HandsetFirmware");
    strcpy(pEntry->HandsetName, "HandsetName");
    strcpy(pEntry->LastActiveTime, "LastActiveTime");

    return ANSC_STATUS_SUCCESS;
}

*/

INT   mta_hal_GetCalls(ULONG InstanceNumber, ULONG *pulCount, PMTAMGMT_MTA_CALLS *ppCfg) {

    *pulCount = 1;
    errno_t rc = -1;

    *ppCfg = (PMTAMGMT_MTA_CALLS)malloc(sizeof(MTAMGMT_MTA_CALLS));
    rc = memset_s(*ppCfg, sizeof(MTAMGMT_MTA_CALLS), 0, sizeof(MTAMGMT_MTA_CALLS));
    ERR_CHK(rc);

    /*ppCfg is a pointer pointing to an array of size 64 */
    rc = strcpy_s((*ppCfg)->CallEndTime, 64 , "2000-01-01");
    ERR_CHK(rc);
    rc = strcpy_s((*ppCfg)->CallStartTime, 64 ,"2000-01-01");
    ERR_CHK(rc);
    rc = strcpy_s((*ppCfg)->PktLossConcealment, 16 ,"Standard");
    ERR_CHK(rc);
    rc = strcpy_s((*ppCfg)->CWErrorRate, 16 ,"CWErrorRate");
    ERR_CHK(rc);

	rc = strcpy_s((*ppCfg)->CWErrors, 16 , "CWErrors");
    ERR_CHK(rc);
	rc = strcpy_s((*ppCfg)->SNR, 16 , "122");
	ERR_CHK(rc);
    rc = strcpy_s((*ppCfg)->DownstreamPower, 16 , "5.1");	
	ERR_CHK(rc);
    rc = strcpy_s((*ppCfg)->RemoteJBAbsMaxDelay, 16 ,"20.2");
    ERR_CHK(rc);

    return RETURN_OK;
}

INT   mta_hal_GetCALLP(ULONG LineNumber, PMTAMGMT_MTA_CALLP pCallp) {
    errno_t rc = -1;

    rc = strcpy_s(pCallp->LCState, sizeof(pCallp->LCState) ,"Idle");
    ERR_CHK(rc);
    rc = strcpy_s(pCallp->CallPState, sizeof(pCallp->CallPState) ,"Idle");
    ERR_CHK(rc);
    rc = strcpy_s(pCallp->LoopCurrent, sizeof(pCallp->LoopCurrent) , "Normal");
    ERR_CHK(rc);

    return RETURN_OK;
}

INT   mta_hal_GetDSXLogs(ULONG *Count, PMTAMGMT_MTA_DSXLOG *ppDSXLog) { *Count = 0; *ppDSXLog = NULL; return RETURN_OK; }
INT   mta_hal_GetDSXLogEnable(BOOLEAN *pBool) { *pBool = FALSE; return RETURN_OK; }
INT   mta_hal_SetDSXLogEnable(BOOLEAN Bool) { return RETURN_OK; }


MTAMGMT_MTA_MTALOG_FULL MtaLog[] = 
{
    { 1, 1, "1", "1998-05-14", "this is a log for matLog1"},
    { 2, 2, "2", "1998-05-14", "this is a log for matLog2"}
};

INT   mta_hal_GetMtaLog(ULONG *Count, PMTAMGMT_MTA_MTALOG_FULL *ppConf) {

    ULONG              i = 0;

    *Count = 2;
    errno_t rc = -1;

    *ppConf = (PMTAMGMT_MTA_MTALOG_FULL)malloc(sizeof(MTAMGMT_MTA_MTALOG_FULL)*2);
    rc = memset_s(*ppConf, sizeof(MTAMGMT_MTA_MTALOG_FULL)*2, 0, sizeof(MTAMGMT_MTA_MTALOG_FULL)*2);
    ERR_CHK(rc);

    rc = memcpy_s(*ppConf, sizeof(MTAMGMT_MTA_MTALOG_FULL) , &MtaLog, sizeof(MtaLog) );
    ERR_CHK(rc);

    for ( i=0; i<2; i++)
    {
        if ( MtaLog[i].pDescription ) {
            (*ppConf)[i].pDescription = (CHAR*)malloc(sizeof(CHAR)*(strlen(MtaLog[i].pDescription) + 1));
            rc = strcpy_s((*ppConf)[i].pDescription, 64 ,MtaLog[i].pDescription);
            ERR_CHK(rc);
        }
        else
            (*ppConf)[i].pDescription = NULL;
    }

    return RETURN_OK;
}

INT mta_hal_ClearDSXLog(BOOLEAN Bool)
{
	 return RETURN_OK; 
}

INT mta_hal_GetCallSignallingLogEnable(BOOLEAN *pBool) 
{ 
	*pBool = FALSE; 
	return RETURN_OK; 
}

INT mta_hal_SetCallSignallingLogEnable(BOOLEAN Bool) 
{ 
	return RETURN_OK;
}
 
INT mta_hal_ClearCallSignallingLog(BOOLEAN Bool) 
{ 
	return RETURN_OK;
}

/*
COSA_DML_DECTLOG_FULL DectLog[] = 
{
    { 1, 1, 1, "1998-05-14", "this is a log for dectLog1"},
    { 2, 2, 2, "1998-05-14", "this is a log for dectLog2"}
};

ANSC_STATUS
CosaDmlMtaGetDectLog
    (
        ANSC_HANDLE                 hContext,
        PULONG                      pulCount,
        PCOSA_DML_DECTLOG_FULL      *ppConf        
    )    
{
    *pulCount = 2;
    *ppConf = (PCOSA_DML_DECTLOG_FULL)AnscAllocateMemory( sizeof(DectLog) );

    AnscCopyMemory(*ppConf, &DectLog, sizeof(DectLog) );

    return ANSC_STATUS_SUCCESS;
}
*/

INT mta_hal_BatteryGetInstalled(BOOLEAN* Val)     { *Val = TRUE; return RETURN_OK; }
INT mta_hal_BatteryGetTotalCapacity(ULONG* Val)   { *Val = 1500; return RETURN_OK; }
INT mta_hal_BatteryGetActualCapacity(ULONG* Val)  { *Val = 1600; return RETURN_OK; }
INT mta_hal_BatteryGetRemainingCharge(ULONG* Val) { *Val = 1300; return RETURN_OK; }
INT mta_hal_BatteryGetRemainingTime(ULONG* Val)   { *Val = 1;    return RETURN_OK; }
INT mta_hal_BatteryGetNumberofCycles(ULONG* Val)  { *Val = 4321; return RETURN_OK; }

INT mta_hal_BatteryGetPowerStatus(CHAR *Val, ULONG *len)
{
    errno_t rc = -1;
    /* Val is a pointer pointing to 32 bytes of data */
    rc = strcpy_s(Val, *len ,"Battery");
    ERR_CHK(rc);
    *len=strlen(Val)+1; 
    return RETURN_OK; 
}
INT mta_hal_BatteryGetCondition(CHAR *Val, ULONG *len)
{
    errno_t rc = -1;
    rc = strcpy_s(Val, *len ,"Good");
    ERR_CHK(rc);
    *len=strlen(Val)+1;
    return RETURN_OK;
}
INT mta_hal_BatteryGetStatus(CHAR* Val, ULONG *len)
{
    errno_t rc = -1;
    rc = strcpy_s(Val, *len ,"Discharging");
    ERR_CHK(rc);
    *len=strlen(Val)+1;
    return RETURN_OK;
}
INT mta_hal_BatteryGetLife(CHAR* Val, ULONG *len)
{
    errno_t rc = -1;
    rc = strcpy_s(Val, *len ,"Need Replacement");
    ERR_CHK(rc);
    *len=strlen(Val)+1;
    return RETURN_OK;
}

INT mta_hal_BatteryGetInfo(PMTAMGMT_MTA_BATTERY_INFO pInfo)
{
    errno_t rc = -1;

    rc = strcpy_s(pInfo->ModelNumber,  sizeof(pInfo->ModelNumber)  , "ModelNumber1.0");
    ERR_CHK(rc);
    rc = strcpy_s(pInfo->SerialNumber, sizeof(pInfo->SerialNumber)  ,  "SerialNumber1.0");
    ERR_CHK(rc);
    rc = strcpy_s(pInfo->PartNumber,  sizeof(pInfo->PartNumber)  ,   "PartNumber1.0");
    ERR_CHK(rc);
    rc = strcpy_s(pInfo->ChargerFirmwareRevision, sizeof(pInfo->ChargerFirmwareRevision), "ChargerFirmwareRevision1.0");
    ERR_CHK(rc);

    return RETURN_OK;
}

INT mta_hal_Get_MTAResetCount(ULONG *resetcnt)
{
    if (resetcnt == NULL)
    {
        return RETURN_ERR;
    }
    else
    {
		*resetcnt = 4;
        return RETURN_OK;
    }
}

INT mta_hal_Get_LineResetCount(ULONG *resetcnt)
{
    if (resetcnt == NULL)
    {
        return RETURN_ERR;
    }
    else
    { 
		*resetcnt = 5;
        return RETURN_OK;
    }
}

INT mta_hal_ClearCalls(ULONG InstanceNumber)
{
	return RETURN_OK;
}

INT mta_hal_BatteryGetPowerSavingModeStatus(ULONG *pValue) { *pValue = 2; return RETURN_OK; }

