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
#include <string.h>

#include "logFileDescr.h"
#include "sysresLogger.h"
#include "procInfo.h"
#include "zmalloc.h"
#include "debugRecord.h"

#define DEBUG_SRL_ENABLE	1

#if DEBUG_SRL_ENABLE
#define	DBG_SRL(x)	x
#else
#define	DBG_SRL(x)
#endif

int SysResLogger::counter = 0;

SysResLogger::SysResLogger(size_t _bufferLength, char *filename) : bufferLength(_bufferLength)
{
	DBG_SRL(WDR("SysResLogger::SysResLogger: bufferLength = %d filename = %s\n", bufferLength, filename));
	int length=0;
	logBuffer=(char*)zmalloc(bufferLength);	
	if (filename && (length=strlen(filename)))
	{
		this->filename=(char*)zmalloc(length+1);
		strncpy(this->filename, filename, length+1);
	}
	else
	{
		this->filename=(char*)zmalloc(LOG_FILENAME_LENGTH);
		sprintf(logBuffer, ".%d", counter);
		proc_filename(LOG_FILE_DEFAULT_PATH, "", logBuffer, this->filename);
		++counter;
	}

	DBG_SRL(WDR("SysResLogger::SysResLogger: bufferLength = %d logBuffer = %p filename = %s\n", bufferLength, logBuffer, this->filename));
}

void SysResLogger::SetFilename(const char *postfix, const char *ext)
{
	zfree(filename);
	filename=(char*)zmalloc(LOG_FILENAME_LENGTH);
	*filename='\0';
	proc_filename(LOG_FILE_DEFAULT_PATH, postfix, ext, filename);
	DBG_SRL(WDR("SysResLogger::SetFilename: postfix = %s ext = %s filename = %s\n", postfix, ext, filename));
}

void SysResLogger::Log(size_t length, char *filename)
{
	FILE *file = 0;
	if (filename) file=fopen (filename, "a");
	else file=fopen (this->filename, "a");
	fwrite ((char*)logBuffer, 1, length, file);
	fclose (file);
}

