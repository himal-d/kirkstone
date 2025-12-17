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

#include "mlt_malloc.h"
#include "procInfo.h"
#include "debugRecord.h"

#if USE_SYSRES_MLT

int testmemalign()
{
	int err=0;
	struct structProcStat * procStat1 = NULL;
	struct structProcStat * procStat2 = NULL;
	WDR("testmemalign: memalign: sizeof(struct structProcStat) = %d\n", sizeof(struct structProcStat));
	procStat1 = (struct structProcStat *) memalign (64, sizeof(struct structProcStat));
	WDR("testmemalign: memalign = %p\n", procStat1);

	WDR("testmemalign: posix_memalign: sizeof(struct structProcStat) = %d\n", sizeof(struct structProcStat));
	err=posix_memalign ((void **)&procStat2, 64, sizeof(struct structProcStat));
	WDR("testmemalign: posix_memalign = %p error = %d\n", procStat2, err);

	mlt_analyze(0);
	free(procStat1);
	free(procStat2);
	mlt_analyze(0);

	return 0;
}

#endif
