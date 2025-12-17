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
#ifndef	CMAS_MFC_ANALYZER_H
#define CMAS_MFC_ANALYZER_H

#include "cmastats.h"
#include "backtraceHandler.h"

class	MfcGroup
{
public:
	MfcGroup () : caller(0), fcount(0), cmaStats(0) {}

	unsigned long		caller;
	unsigned long		fcount;
	CmaStats 		*cmaStats;

	void 	Init(unsigned long caller, unsigned long fcount, CmaStats *cmaStats) 
	{
		this->caller=caller; this->fcount=fcount; this->cmaStats=cmaStats;
	}
};

class CmasMfcAnalyzer
{
public:
	CmasMfcAnalyzer(char *_filename=0) : groups(0), filename(_filename) {}
	~CmasMfcAnalyzer() {}
	void		init(int size);
	void		schedule_log();
	void		deinit();

	void* 		operator new [] (size_t size) { return malloc(size); }
	void  		operator delete [] (void*p) { free(p); }

private:

	MfcGroup 		**groups;
	char 			*filename;
	BacktraceHandler	mabtHandler;
	BacktraceHandler	mdbtHandler;
};

#endif // CMAS_MFC_ANALYZER_H

