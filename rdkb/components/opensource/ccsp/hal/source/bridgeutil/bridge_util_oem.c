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
	/* This is platform specific code to handle platform specific operation for given config post bridge creation */
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

char *getVendorIfaces()
{
	return NULL;
}