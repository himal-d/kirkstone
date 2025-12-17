/*
 * If not stated otherwise in this file or this component's Licenses.txt file the
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
#include <stdio.h>

#include "sysResource.h"
#include "procInfo.h"
#include "rpl_new.h"
#include "mlt_malloc.h"
#include "debugRecord.h"

#if USE_SYSRES_MLT

int testnew()
{
	WDR("sizeof(struct structProcStatm) = %d\n", sizeof(struct structProcStatm));
	struct structProcStatm * procStatm1 = new struct structProcStatm;
	printf("testnew: procStatm1 = %p\n", procStatm1);
	for (int i=0; i<MLT_INCREASE_THRESHOLD+2; i++)
	{
		struct structProcStatm * procStatm = new struct structProcStatm;	// Simulate a memory leak!
		struct structProcStatm * procStatm2= new struct structProcStatm;
		printf("testnew: procStatm  = %p procStatm2 = %p\n", procStatm, procStatm2);
		mlt_analyze(0);								// Analyze the simulated memory leak
		delete(procStatm2);
	}
	delete(procStatm1);

	WDR("sizeof(struct structProcStatm [8]) = %d\n", sizeof(struct structProcStatm [8]));
	struct structProcStatm * procStatm2 = new struct structProcStatm [2];
	printf("testnew: procStatm2 = %p\n", procStatm2);
	for (int i=0; i<MLT_INCREASE_THRESHOLD+2; i++)
	{
		struct structProcStatm * procStatm = new struct structProcStatm [8];	// Simulate a memory leak!
		struct structProcStatm * procStatm3= new struct structProcStatm [8];
		printf("testnew: procStatm  = %p procStatm3 = %p\n", procStatm, procStatm3);
		mlt_analyze(0);								// Analyze the simulated memory leak
		delete(procStatm3);
	}
	delete(procStatm2);

	return 0;
}

#endif

