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
#ifndef PROC_STATM_H
#define PROC_STATM_H

class ProcStatmS
{
public:
	ProcStatmS() : size(0), resident(0), share(0) { }
	~ProcStatmS() { }

private:
	int	size;				// 0. total program size (same as VmSize in /proc/[pid]/status)
	int	resident;			// 1. resident set size  (same as VmRSS in /proc/[pid]/status)
	int	share;				// 2. shared pages (from shared mappings)
};

#endif //PROC_STATM_H
