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


// This file needs to be overwritten by oem/soc layer for device specific changes.
#include "bridge_util_hal.h"
#include <netinet/in.h>
#include <arpa/inet.h>

#define BUF_4096        4096
#define BUF_512         512
#define BUF_256         256
#define BUF_32          32
#define MAC_ADDR_LEN    6
#define MAC_STR_LEN     18
#define MAC_LENGTH      64

#define RETURN_OK   0
#define RETURN_ERR -1
#define SUCCESS     1

#define PRIVATE_LANBRIDGE "brlan0"
#define OVS_ENABLED    "/sys/module/openvswitch"

#define PSM_IP_CONFIG    "dmsb.l3net.4.V4Addr"
#define PSM_MASK_CONFIG  "dmsb.l3net.4.V4SubnetMask"
#define UINT8 unsigned char

/*********************************************************************************************
 *                                 Function Declarations
 * *******************************************************************************************/

/*********************************************************************************************

    caller:  AssignMacForLanBridge
    prototype:

        int
        GetBaseMacAddress
           (
        char *baseMac
       );
    description :
        This function capture the base mac address of the CPE.

    Argument :
        char *baseMac   -- String to hold base mac address
    return : When success returns RETURN_OK
***********************************************************************************************/
static int GetBaseMacAddress (char *baseMac);

/*********************************************************************************************

    caller:  AssignMacForLanBridge,
    prototype:

        int
        GetUpdatedMacAddress
           (
        char *baseMac,
        int offset,
        char *updatedMac
       );
    description :
        This function calculates new mac address based on base mac using offset passed.

    Argument :
        char *baseMac   -- base mac address
        int offset  -- Offset needs to be added.
        char *updatedMac -- String to store updated mac
    return : When success returns RETURN_OK
***********************************************************************************************/
static int GetUpdatedMacAddress (const char* baseMac, const int offset, char *updatedMac);

/*********************************************************************************************

    caller:  AssignMacForLanBridge
    prototype:

        int
        SetMacAddress
           (
        const char *ifname,
        const char* mac
       );
    description :
        This function assign mac address to  the interface.

    Argument :
        char *ifname   -- Interface name
        const char* mac -- Mac address
    return : When success returns RETURN_OK
***********************************************************************************************/
static int SetMacAddress (const char *ifname, const char* mac);

/*********************************************************************************************

    caller:  HandlePreConfigVendor,GetBaseMacAddress,SetIpAddress
    prototype:

        int
        GetCmdOutput
           (
        const char *cmd,
        char *outStr,
        const int outStrLength
       );
    description :
        This function execute the command in the device shell using popen and store output to string.

    Argument :
        const char *cmd   -- Command needs to be executed
        char* outStr -- String to hold the output.
        const int outStrLength - Length of the output string
    return : When success returns RETURN_OK
***********************************************************************************************/
static int GetCmdOutput (const char* cmd, char* outStr,const int outStrLength);

/*********************************************************************************************

    caller:  HandlePostConfigVendor
    prototype:

        int
        AssignMacForLanBridge
           (
        const char *bridgeName,
        const int macOffset
       );
    description :
        This function calculate mac address based on offset and assign to the system.

    Argument :
        const char *bridgeName   -- Bridge name
        const int macOffset -- Mac offset needs to be add to the base mac
    return : When success returns RETURN_OK
***********************************************************************************************/
static int AssignMacForLanBridge(const char* bridgeName, const int macOffset);

/*********************************************************************************************

    caller:  HandlePostConfigVendor
    prototype:

        int
        SetIpAddress
           (
        const char *ifName,
       );
    description :
        This function set ip address for the interface

    Argument :
        const char *ifname   -- interface name
    return : When success returns RETURN_OK
***********************************************************************************************/
static int SetIpAddress (const char* ifName);

/*********************************************************************************************
    caller:  HandlePostConfigVendor
    prototype:
        int
        EnableIPForward
        (
            void
        );
    description :
        This function enable /proc entries for IP forwarding.
    Argument : None
    return : Returns RETURN_OK if successful.
***********************************************************************************************/
static int EnableIPForward (void);

/**********************************************************************************************
caller:  GetBaseMacAddress
    prototype:

        int
        isFileExistsAccess
           (
        const char *path,
       );
    description :
        This function check for file exists

    Argument :
        const char *path   -- path of the file
    return : When success returns SUCCESS
***********************************************************************************************/
static int isFileExistsAccess(const char *path);

/***********************************************************************************************
 *                          Function Definitions
 ***********************************************************************************************/

static int GetCmdOutput (const char* cmd, char* outStr, const int outStrLength)
{
    FILE *fp = NULL;
    char strBuf[BUF_256] = {0};
    char *cBufPtr = NULL;

    if (NULL == cmd || NULL == outStr) {
        bridge_util_log("[%s] - Invalid argument \n",__FUNCTION__);
        return RETURN_ERR;
    }

    fp = popen (cmd, "r");
    if (fp) {
        fgets (strBuf, sizeof(strBuf), fp);

        // Remove \n char in buffer.
        if ((cBufPtr = strchr(strBuf, '\n')))
           *cBufPtr = 0;

        strncpy (outStr, strBuf, outStrLength - 1);
        pclose (fp);
    }else {
        bridge_util_log("[%s] - popen error \n", __FUNCTION__);
        return RETURN_ERR;
    }

    return RETURN_OK;
}

static int isFileExistsAccess(const char *path)
{
    // Check for file existence
    if (access(path, F_OK) == -1)
        return RETURN_OK;
    else
        return SUCCESS;
}

static int GetBaseMacAddress (char *baseMac)
{
    if (baseMac == NULL)
    {
        bridge_util_log("Invalid argument \n");
        return RETURN_ERR;
    }

    char macStr[MAC_LENGTH] = {'\0'}; 
    char file_path[BUF_32] = {'\0'};
    /**
     * Get base mac address.
     */
    if(isFileExistsAccess("/sys/class/net/erouter0/address")) //Ensure the path exists
        strcpy(file_path,"cat /sys/class/net/erouter0/address");
    else
        strcpy(file_path,"cat /sys/class/net/eth0/address");

    if (GetCmdOutput(file_path,macStr,sizeof(macStr)) != RETURN_OK)
    {
        bridge_util_log("[%s] - Failed to get base mac \n", __FUNCTION__);
        return RETURN_ERR;
    }

    snprintf(baseMac, sizeof(macStr), "%s", macStr);
    return RETURN_OK;
}

static int GetUpdatedMacAddress (const char* baseMac, const int macOffset, char *updatedMac)
{
    if (NULL == baseMac) {
        bridge_util_log("[%s] - Invalid argument \n", __FUNCTION__);
        return RETURN_ERR;
    }

    char macStr[MAC_STR_LEN] = {0};
    char macNum[MAC_ADDR_LEN] = {0};

    //convert mac string into numbers
    sscanf(baseMac, "%2hhx:%2hhx:%2hhx:%2hhx:%2hhx:%2hhx",
          &(macNum[0]), &(macNum[1]), &(macNum[2]), &(macNum[3]), &(macNum[4]), &(macNum[5]));

    macNum[5] += macOffset;

    /* convert Mac number into string */
    sprintf(macStr, "%02x:%02x:%02x:%02x:%02x:%02x",
           (UINT8) macNum[0], (UINT8) macNum[1], (UINT8) macNum[2],
           (UINT8) macNum[3], (UINT8) macNum[4], (UINT8) macNum[5]);

    strncpy(updatedMac, macStr, strlen(macStr));
    return RETURN_OK;
}

static int SetMacAddress (const char *ifname, const char* macStr)
{
    char baseMac[MAC_LENGTH] = {'\0'};
    char syscmd[BUF_256] = {'\0'};

    if (ifname == NULL || macStr == NULL)
    {
        bridge_util_log("[%s] - Invalid argument \n",__FUNCTION__);
        return RETURN_ERR;
    }

    if( access(OVS_ENABLED, F_OK) == 0)  {
        snprintf(syscmd, sizeof(syscmd),"ovs-vsctl set bridge %s other-config:hwaddr=%s other-config:mac-aging-time=3",ifname,macStr);
    }else {
        snprintf(syscmd, sizeof(syscmd), "ip link set dev %s address %s", ifname, macStr);
    }

    system(syscmd);

    return RETURN_OK;
}

static int SetIpAddress (const char* ifName)
{
    if (NULL == ifName) {
        bridge_util_log("[%s] - Invalid memory \n",__FUNCTION__);
        return RETURN_ERR;
    }

    if (strncmp (ifName, PRIVATE_LANBRIDGE, strlen(PRIVATE_LANBRIDGE)) == 0) {
        char ipAddr[BUF_256] = {0};
        char netMask[BUF_256] = {0};
        char bcastAddr[BUF_256] = {0};
        char cmd[BUF_512] = {0};
	struct in_addr ip;
        struct in_addr subnetMask;
        struct in_addr bCast;

        //IP Address
        snprintf(cmd, sizeof(cmd), "psmcli get %s", PSM_IP_CONFIG);
        if (RETURN_OK != GetCmdOutput(cmd,ipAddr,sizeof(ipAddr))) {
            bridge_util_log("[%s] - Failed to get ipaddress from psm \n",__FUNCTION__);
            return RETURN_ERR;
        }

        //Subnet Address
        memset(cmd, 0, sizeof(cmd));
        snprintf(cmd, sizeof(cmd), "psmcli get %s", PSM_MASK_CONFIG);
        if (RETURN_OK != GetCmdOutput(cmd,netMask,sizeof(netMask))) {
            bridge_util_log("[%s] - Failed to get netmask address from psm \n",__FUNCTION__);
            return RETURN_ERR;
        }

	//broadcast address.
	ip.s_addr = inet_addr(ipAddr);
        subnetMask.s_addr = inet_addr(netMask);
        bCast.s_addr = ip.s_addr | ~subnetMask.s_addr;
        strcpy(bcastAddr, inet_ntoa(bCast));

	//Assign IP address.
        bridge_util_log("[%s] - Interface = [%s], IP = %s, MASK = %s, BCAST = %s \n", __FUNCTION__, ifName, ipAddr, netMask, bcastAddr);
        memset(cmd, 0, sizeof(cmd));
        snprintf(cmd, sizeof(cmd), "ip addr add %s/%s broadcast %s dev %s",ipAddr,netMask,bcastAddr,ifName);
        system(cmd);
    }
    return RETURN_OK;
}

static int AssignMacForLanBridge(const char* bridgeName, const int macOffset)
{
    char baseMac[MAC_LENGTH] = {0};
    char updatedMac[MAC_STR_LEN] = {0};

    if (RETURN_OK != GetBaseMacAddress (baseMac)) {
        bridge_util_log("[%s] - Failed to get base mac \n", __FUNCTION__);
        return RETURN_ERR;
    }

    if (RETURN_OK != GetUpdatedMacAddress(baseMac, macOffset, updatedMac)) {
        bridge_util_log("[%s] - Failed to get updated MAC \n", __FUNCTION__);
        return RETURN_ERR;
    }

    if (RETURN_OK != SetMacAddress(bridgeName,updatedMac)) {
        bridge_util_log("[%s] - Failed to set updated MAC for the bridge %s \n", __FUNCTION__,bridgeName);
        return RETURN_ERR;
    }

    bridge_util_log("[%s] - Successfully updated Mac = %s for the interface %s\n",__FUNCTION__,updatedMac, bridgeName);

    return RETURN_OK;
}

static int EnableIPForward (void)
{
    char cmd[BUF_512] = {0};
    snprintf(cmd, sizeof(cmd), "echo 1 > /proc/sys/net/ipv4/ip_forward");
    system(cmd);
    memset (cmd, 0 , sizeof(cmd));
    snprintf(cmd, sizeof(cmd), "echo 1 > /proc/sys/net/ipv4/ip_dynaddr");
    system(cmd);
    memset (cmd, 0 , sizeof(cmd));
    snprintf(cmd, sizeof(cmd), "echo 1 > /proc/sys/net/ipv6/conf/all/forwarding");
    system(cmd);
    return RETURN_OK;
}

/*********************************************************************************************

    caller:  CreateBrInterface,DeleteBrInterface,SyncBrInterfaces
    prototype:

        int
        HandlePreConfigVendor
            (
				bridgeDetails *bridgeInfo,
				int InstanceNumber 
			);
    description :
			This function has OEM/SOC specific changes which needs to be configured before 
			creating/updating/deleting bridge. 

	Argument : 
			bridgeDetails *bridgeInfo,   -- Bridge info
			int InstanceNumber 			-- Instance number
	return : When success returns 0 
***********************************************************************************************/


int HandlePreConfigVendor(bridgeDetails *bridgeInfo,int InstanceNumber)
{
//Remove the Mesh bridges if its being already created via brctl in case of ovs enabled.
    if (NULL == bridgeInfo) {
        printf("Invalid memory \n");
        return RETURN_ERR;
    }
    char cmd[BUF_4096] = { 0 };
    char outStr[BUF_512] = { 0 };
    if( access(OVS_ENABLED, F_OK) == 0) { 
	    memset(outStr, 0, sizeof(outStr));
	    snprintf(cmd, sizeof(cmd), "brctl show | grep brlan0 | awk '{print $1}'");
	    bridge_util_log("[%s] - cmd = %s \n", __FUNCTION__,cmd);
	    if (RETURN_OK == GetCmdOutput(cmd, outStr, sizeof(outStr))) {
		    bridge_util_log("[%s] - output = %s \n", __FUNCTION__,outStr);
		    if (strncmp(outStr, bridgeInfo->bridgeName, strlen(bridgeInfo->bridgeName)) == 0) {
			    memset(outStr, 0, sizeof(outStr));
			    snprintf(cmd, sizeof(cmd), "ifconfig brlan0 down;brctl delbr brlan0");
			    bridge_util_log("[%s] - cmd = %s \n", __FUNCTION__,cmd);
			    if (RETURN_OK != GetCmdOutput(cmd, outStr, sizeof(outStr))) {
				    bridge_util_log(" [%s] Failed to execute [%s] \n", __FUNCTION__,cmd);
			    }
		    }
	    }
    }

		/* This is platform specific code to handle platform specific operation for given config pre bridge creation*/
		switch(InstanceNumber)
		{
				case PRIVATE_LAN:
									break;

				case HOME_SECURITY:
									break;

				case HOTSPOT_2G:
									break;

				case HOTSPOT_5G:
									break;

				case LOST_N_FOUND:
									break;

				case HOTSPOT_SECURE_2G:
									break;	

				case HOTSPOT_SECURE_5G:
									break;

				case MOCA_ISOLATION:
									break;	

				case MESH:
									break;

				case MESH_BACKHAUL:
									break;	
				case ETH_BACKHAUL:
									break;	

				default :
						printf("Default case\n");

		}
		return 0;
}


/*********************************************************************************************

    caller:  CreateBrInterface,DeleteBrInterface,SyncBrInterfaces
    prototype:

        int
        HandlePostConfigVendor
            (
				bridgeDetails *bridgeInfo,
				int InstanceNumber 
			);
    description :
			This function has OEM/SOC specific changes which needs to be configured after 
			creating/updating/deleting bridge

	Argument : 
			bridgeDetails *bridgeInfo,   -- Bridge info
			int InstanceNumber 			-- Instance number
	return : When success returns 0 
***********************************************************************************************/

int HandlePostConfigVendor(bridgeDetails *bridgeInfo,int InstanceNumber)
{
	char cmd[BUF_4096] = {0};
	if (bridgeInfo == NULL)
	{
		bridge_util_log("%s : bridgeInfo is NULL\n", __FUNCTION__);
		return RETURN_ERR;
	}

	/* This is platform specific code to handle platform specific operation for given config post bridge creation */
	switch(InstanceNumber)
	{
				case PRIVATE_LAN:
					if ( BridgeOprInPropgress == CREATE_BRIDGE ) {
						/* brlan0 case. Update MAC address and enable bridge.
						 * brlan0 MAC - base mac + 1
						 */
						if (AssignMacForLanBridge(bridgeInfo->bridgeName, 1) != RETURN_OK) {
							bridge_util_log("[%s] - Failed to set MAC address for the bridge interface [%s] \n", __FUNCTION__, bridgeInfo->bridgeName);
						}

						/* Set Ip address. */
						if (SetIpAddress(bridgeInfo->bridgeName) != RETURN_OK) {
							bridge_util_log("[%s] - Failed to set IP  address for the bridge interface [%s] \n", __FUNCTION__, bridgeInfo->bridgeName);
						}else {
							bridge_util_log("[%s] - Successfully set IP  address for the bridge interface [%s] \n", __FUNCTION__, bridgeInfo->bridgeName);
						}

						/* Enable bridge interface. */
						memset(cmd,0,sizeof(cmd));
						snprintf(cmd, sizeof(cmd), "ip link set dev %s up",bridgeInfo->bridgeName);
						system(cmd);
					        //For LAN Port configurtion
						system("ifconfig eth1 up");
						if( access(OVS_ENABLED, F_OK) == 0) {
							/* Set eth1 as LAN port */
						        system("ovs-vsctl add-port brlan0 eth1");	
						}
						else {
						        system("brctl addif brlan0 eth1");  	
						}
						/* Enable IP Forwarding. */
                                                if ( EnableIPForward() < RETURN_OK ) {
                                                        bridge_util_log("[%s] - Failed to enable IP forwarding \n", __FUNCTION__);
                                                }else{
                                                        bridge_util_log("[%s] - Successfully enabled IP forwarding \n", __FUNCTION__);
                                                }
					    }

									break;

				case HOME_SECURITY:
									break;	

				case HOTSPOT_2G:
									break;

				case HOTSPOT_5G:
									break;	
				
				case LOST_N_FOUND:
									break;

				case HOTSPOT_SECURE_2G:
									break;	

				case HOTSPOT_SECURE_5G:
									break;

				case MOCA_ISOLATION:

									break;	

				case MESH:
									break;

				case MESH_BACKHAUL:
									break;	
				case ETH_BACKHAUL:
									break;	

				default :
						printf("Default case\n");

	}
	return 0;
}

char *getVendorIfaces()
{
	return NULL;
}
