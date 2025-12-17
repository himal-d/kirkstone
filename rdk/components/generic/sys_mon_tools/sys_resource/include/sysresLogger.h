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
#ifndef	SYSRES_LOGGER_H
#define SYSRES_LOGGER_H

#include <stdlib.h>

#include "zmalloc.h"

class SysResLogger
{
public:
	SysResLogger(size_t bufferLength, char *filename=0);
	~SysResLogger() { zfree(logBuffer); zfree(filename); }

	void 		SetFilename(const char *postfix, const char *ext);
	void		Log(size_t length, char *filename=0);

protected:
	char		*logBuffer;
	size_t 		bufferLength;
	char 		*filename;

private:
	static int	counter;
};

#endif // SYSRES_LOGGER_H

