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
#ifndef	ELAPSEDTIME_H
#define ELAPSEDTIME_H

#include <sys/time.h>

#include "tdiff.h"

class ElapsedTime
{
public:
	ElapsedTime(int _id=CLOCK_MONOTONIC) : id(_id)
	{
		stt.tv_sec=endt.tv_sec=0;
		stt.tv_nsec=endt.tv_nsec=0; 
	}
	~ElapsedTime() {}

	int 		start() { return clock_gettime(id, &stt); }
	int 		end()   { return clock_gettime(id, &endt); }
	struct timespec enddiff()  { clock_gettime(id, &endt); return clock_getdiff(&stt, &endt); }
	struct timespec diff()  { return clock_getdiff(&stt, &endt); }
	long 		diffnsec() { struct timespec temp=clock_getdiff(&stt, &endt); return temp.tv_nsec; }
	long 		enddiffnsec() { clock_gettime(id, &endt); struct timespec temp=clock_getdiff(&stt, &endt); return temp.tv_nsec; }

private:
	int 		id;
	struct timespec stt;
	struct timespec endt;
};

#endif // ELAPSEDTIME_H

