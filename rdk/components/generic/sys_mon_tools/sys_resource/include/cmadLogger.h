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
#ifndef	CMAD_LOGGER_H
#define CMAD_LOGGER_H

#include "LinkedList.h"
#include "IpCmaNode.h"
#include "sysresLogger.h"

class CmadLogger : public SysResLogger
{
public:
	CmadLogger(int threshold, size_t bufferLength, char *filename=0);
	~CmadLogger() {}

protected:
	void 	Build(size_t &bufoff, SLL<IpCmaNode> &cmad);
	void 	Log(size_t bufoff, SLL<IpCmaNode> &cmad);

private:
	int	threshold;
};

#endif // CMAD_LOGGER_H

