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
#include <malloc.h>

#include "procInfo.h"
#include "mlt_malloc.h"
#include "debugRecord.h"

#if USE_SYSRES_MLT

int testcalloc2()
{
	int i=0;
	WDR("sizeof(struct structProcStat) = %d\n", sizeof(struct structProcStat));
	struct structProcStat * procStat1 = (struct structProcStat *) calloc (1, sizeof(struct structProcStat));
	for (i=0; i<MLT_INCREASE_THRESHOLD+2; i++)
	{
		struct structProcStat * __attribute__((unused)) procStat = (struct structProcStat *) calloc (1, sizeof(struct structProcStat));	// Simulate a memory leak!
		mlt_analyze(0);												// Analyze the simulated memory leak
	}
	free(procStat1);

	WDR("sizeof(struct structProcStat [4]) = %d\n", sizeof(struct structProcStat [4]));
	struct structProcStat ** procStat2 = (struct structProcStat **) calloc (4, sizeof(struct structProcStat));
	for (i=0; i<MLT_INCREASE_THRESHOLD+2; i++)
	{
		struct structProcStat ** __attribute__((unused)) procStat = (struct structProcStat **) calloc (4, sizeof(struct structProcStat));	// Simulate a memory leak!
		mlt_analyze(0);												// Analyze the simulated memory leak
	}
	free(procStat2);

	return 0;
}

#endif
