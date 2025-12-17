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
#include <stdarg.h>
#include <pthread.h>
#include <signal.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>

#include "sysres_ctor.h"
#include "procInfo.h"
#include "debugRecord.h"

#if USE_FILE_WDR

#define ARRAY_SIZE		(1*1024*1024)
#define MAX_STRING_SIZE 	1024
#define	WDR_FILENAME_LENGTH	64

#ifdef RDK_BROADBAND
#define	WDR_FILE_DEFAULT_PATH	"/rdklogs/logs/"
#else
#define	WDR_FILE_DEFAULT_PATH	"/opt/logs/"
#endif

#define USE_DR_ATTR_CTOR

#ifdef USE_DR_ATTR_CTOR
#define __dr_attr_init  __attribute__((constructor (__DR_CTOR_PRIORITY)))
#define __dr_attr_close  __attribute__((destructor (__DR_DTOR_PRIORITY)))
#else
#define __dr_attr_init
#define __dr_attr_close
#endif

static FILE 		*file = NULL;
static bool 		drInitialized=false;
static int 		totalCharsLogged = 0;
static char		debugArray[ARRAY_SIZE];
static char 		*RecordPtr = debugArray;
static pthread_mutex_t 	drMutex;
static char		filename[WDR_FILENAME_LENGTH] = {0};

static void 		drReset();
static char 		*drFilename(const char *directory, const char *postfix, const char *ext, char *filename);
static void 		drSignalHandler(int signal);

#define lock()		pthread_mutex_lock(&drMutex);
#define unlock()	pthread_mutex_unlock(&drMutex);

static void __dr_attr_init drInitialize ()
{
	pthread_mutexattr_t attr;

	printf("drInitialize: thread = %p\n", pthread_self());
	if (drInitialized)
	{
		printf("drInitialize: Already initialized! Return\n");
		return;
	}

	signal(SIGSEGV,  drSignalHandler);
	signal(SIGTSTP,  drSignalHandler);

	pthread_mutexattr_init(&attr);
	pthread_mutexattr_settype(&attr, PTHREAD_MUTEX_RECURSIVE);
	pthread_mutex_init(&drMutex, &attr);
	pthread_mutexattr_destroy(&attr);

	lock();
	if ((file = fopen(drFilename(WDR_FILE_DEFAULT_PATH, "WDR", "", filename), "w")) != NULL)
	{
		printf("drInitialize: thread = %p file = %p : init success!\n", pthread_self(), file);
		drInitialized=true;
	}
	else
	{
		printf("drInitialize: Error opening file = %s !\n", filename);
	}
	unlock();
}

static void __dr_attr_close drClose ()
{
	lock();
	if (file)
	{
		drWriteToFile();
		fflush(file);
		fclose (file);
		file=0;
	}
	drReset();
	filename[0]=0;
	drInitialized=false;
	unlock();
}

static void drSignalHandler( int signum ) 
{
	printf("drSignalHandler: thread = %p signal = %d\n", pthread_self(), signum);
	if (signum == SIGTSTP || signum == SIGSEGV)
		drWriteToFile();

	signal(signum, SIG_DFL);	// restore default handler
	kill(getpid(), signum); 	// invoke default handler
}
 
static void drReset()
{
	totalCharsLogged = 0;
	RecordPtr = debugArray;
}

static char *drFilename(const char *directory, const char *postfix, const char *ext, char *filename)
{
	if (strlen(filename))
		return filename;
	
	procFilename(directory, postfix, ext, filename);
	printf("drFilename  : %s log filename = %s\n", postfix, filename);

	return filename;
}

void drWrite (const char * szFormat, ...)
{
	va_list arguments;
	va_start (arguments, szFormat);
	char string[MAX_STRING_SIZE];
	vsprintf(string, szFormat, arguments);
	va_end (arguments);

	int size = strlen (string);

	lock();
	if (totalCharsLogged + size + 1 > ARRAY_SIZE)
		drWriteToFile();

	if (totalCharsLogged + size + 1 < ARRAY_SIZE)
	{
		char *src = string;
		while (*RecordPtr++ = *src++);
		RecordPtr--;
		totalCharsLogged += size;
	}
	unlock();
}

void drWriteToFile ()
{
	lock();

	if (!totalCharsLogged)
	{
		printf("drWriteToFile: totalCharsLogged == 0 \n");
		unlock();
		return;
	}

	if (strlen(filename))
	{
		printf("drWriteToFile: Writing %d chars to file = %s\n", totalCharsLogged, filename);
	}
	else
	{
		printf("drWriteToFile: Writing %d chars to file = %s failed! Wrong filename!\n", totalCharsLogged, filename);
//		drFilename(WDR_FILE_DEFAULT_PATH, "WDR", "", filename);
		unlock();
		return;
	}

	if (file)
	{
		fwrite ((char*)debugArray, 1, totalCharsLogged, file);
		fflush(file);
		printf("drWriteToFile: Writing %d chars to the file = %s...done\n", totalCharsLogged, filename);
		drReset();
	}
	else
	{
		printf("drWriteToFile: Writing %d chars to the file = %s failed! Error opening file!\n", totalCharsLogged, filename);
	}

	unlock();
}

#endif //USE_FILE_WDR
