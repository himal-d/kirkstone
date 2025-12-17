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

#include "ccsp_hal_ethsw.h"

typedef enum _ETH_FUNC
{
	ETH_GET_ASSOC_DEVICE = 0,
	ETH_LAST_FUNCTION	
} ETH_FUNC_t;

typedef struct _eth_functions
{
	ETH_FUNC_t index;
	char* name;
	char* usage;
	int num_inputs;
} eth_functions_t;

static const eth_functions_t eth_fuction_array[] = {
	{ETH_GET_ASSOC_DEVICE,                         "CcspHalExtSw_getAssociatedDevice",                        "", 0},
};

static void print_functions_usages()
{
	int i;
	printf("lib eth function test console help:\n");
	printf("Usage: eth_api <function> \n");
	printf("list of functions: \n");

	for (i=0; i<ETH_LAST_FUNCTION; i++)
	{
		printf("\t%s\t%s\n", eth_fuction_array[i].name, eth_fuction_array[i].usage);
	}
}


int main(int argc, char** argv)
{
	int i, j, retval = 0;
	ULONG output_array_size = 0;
	eth_device_t *output_struct  = NULL;

	if (argc < 2 )
	{
		print_functions_usages();
		return 1;
	}

	for (i=0; i<ETH_LAST_FUNCTION; i++)
	{
		if(strcmp(argv[1], eth_fuction_array[i].name)==0)
		{
			break;
		}
	}

	if (i == ETH_LAST_FUNCTION) 
	{
		printf("function not found\n");
		return 1;
	}

	argc-=2; // eliminate eth_api <function>
	if ( argc < eth_fuction_array[i].num_inputs)
	{
		printf("not enough inputs\n");
		printf("%s\t%s\n",eth_fuction_array[i].name, eth_fuction_array[i].usage);
		return 1;
	}

	switch(i)
	{
		case ETH_GET_ASSOC_DEVICE:
			retval = CcspHalExtSw_getAssociatedDevice(&output_array_size, &output_struct);
			printf("Total_ETH: %d \n", output_array_size);
			for(j=0;j<output_array_size;j++)
			{ 
				printf("\teth_%d: eth_devMacAddress = %02X:%02X:%02X:%02X:%02X:%02X \n", j+1	, 
					output_struct[j].eth_devMacAddress[0], output_struct[j].eth_devMacAddress[1],
					output_struct[j].eth_devMacAddress[2], output_struct[j].eth_devMacAddress[3],
					output_struct[j].eth_devMacAddress[4], output_struct[j].eth_devMacAddress[5]
					);
				printf("\teth_%d: eth_port = %d \n", j+1, output_struct[j].eth_port);
				printf("\teth_%d: eth_vlanid = %d \n", j+1, output_struct[j].eth_vlanid);
				printf("\teth_%d: eth_devTxRate = %d \n", j+1, output_struct[j].eth_devTxRate);
				printf("\teth_%d: eth_devRxRate = %d \n", j+1, output_struct[j].eth_devRxRate);
				printf("\teth_%d: eth_Active = %d \n", j+1, output_struct[j].eth_Active);
			}

			if(output_struct)
				free(output_struct);
			break;
	}

}

