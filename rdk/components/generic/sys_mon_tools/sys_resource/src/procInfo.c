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
#include <stdlib.h>
#include <sys/stat.h>
#include <dirent.h>
#include <unistd.h>
#include <string.h>
#include <linux/kernel.h>

#include "procInfo.h"

#define	PROCSTAT_STR_LENGTH_MAX		1024
#define	PROCSTATM_STR_LENGTH_MAX	 128
#define	PROCMEMINFO_STR_LENGTH_MAX	 256

#ifdef TEST_DEADCODESTRIP
extern int deadCodeLibRefedInitDataFileData;
int deadCodeFunctionLib()
{
	printf ("deadCodeFunctionLib: deadCodeLibRefedDataFileFunction = %d\n", deadCodeLibRefedInitDataFileData);
	return 0;
}
#endif

static int getFileStream(char *fileName, char *buffer, int bufferLen)
{
	int	error = 0;
  	FILE 	*fp = NULL;

	if (-1 == access (fileName, R_OK)) 
	{
		printf( "Error: accessing file = %s\n", fileName);
		return -1;
	}

	if ((fp = fopen (fileName, "r")) == NULL)
	{
		printf( "Error: opening file = %s\n", fileName);
		return -1;
	}
		  
	if ((fgets (buffer, bufferLen, fp)) == NULL) 
	{
		printf( "Error: reading file = %s stream\n", fileName);
		error = -1;
	}

	fclose (fp);
	return error;
}

void procFilename(const char *directory, const char *postfix, const char *ext, char *filename)
{
	#define PROCNAMELEN	64
	char	processName[PROCNAMELEN];
	pid_t	processId=0;
#ifdef RDK_BROADBAND
	char 	*dir="/rdklogs/logs/";
#else
	char 	*dir="/opt/logs/";
#endif
	char 	*pf="PFN";

	if (directory && strlen(directory))
		dir = (char *)directory;
	if (postfix && strlen(postfix))
		pf = (char *)postfix;

	processId = getpid();
	procName(processId, processName);

	strcpy(filename, dir);
	strncat(filename, processName, PROCNAMELEN);
	strncat(filename, pf, PROCNAMELEN);
	if (ext && strlen(ext)) strncat(filename, ext, PROCNAMELEN);
	printf("procFilename: filename = %s\n", filename);
}

int procStat(char *processName, struct structProcStat *pstat)
{
	int	error = -1;
	struct 	dirent* dirent = NULL;
	DIR* 	dir = NULL;
	int 	pid = 0;
	char	*s = NULL, *e = NULL;
	char 	fileName[_POSIX_PATH_MAX], statString [PROCSTAT_STR_LENGTH_MAX];

	memset ((void *)pstat, 0, sizeof (struct structProcStat));
	dir = opendir( "/proc" );
	while((dirent = readdir(dir)) != NULL)
	{
		pid = atoi( dirent->d_name );
		if (!pid)
			continue;

	  	sprintf (fileName, "/proc/%u/stat", (unsigned) pid);

		if ((getFileStream(fileName, statString, PROCSTAT_STR_LENGTH_MAX)) == -1)
			break;

		s = strchr (statString, '(') + 1;
		e = strchr (statString, ')');

		if ((strncmp(s, processName, e - s)) == 0)
		{
					//    0  1  2  3  4  5  6  7  8   9  10  11  12  13  14  15  16  17  18 19 20  21  22  23  24  25  26  27  28  29  30  31  32  33  34  35  36 37 38 39 40   41  42  43
			sscanf (statString, "%d %s %c %d %d %d %d %d %u %lu %lu %lu %lu %lu %lu %ld %ld %ld %ld %d %d %llu %lu %ld %lu %lu %lu %lu %lu %lu %lu %lu %lu %lu %lu %lu %lu %d %d %u %u %llu %lu %ld",
			&pstat->pid, pstat->comm, &pstat->state, &pstat->ppid, &pstat->pgrp, &pstat->session, &pstat->tty_nr, &pstat->tpgid, &pstat->flags,
			&pstat->minflt, &pstat->cminflt, &pstat->majflt, &pstat->cmajflt, &pstat->utime, &pstat->stime, &pstat->cutime, &pstat->cstime, &pstat->priority, 
			&pstat->nice, &pstat->num_threads, &pstat->itrealvalue, &pstat->starttime, &pstat->vsize, &pstat->rss, &pstat->rsslim, &pstat->startcode, &pstat->endcode,
			&pstat->startstack, &pstat->kstkesp, &pstat->kstkeip, &pstat->signal, &pstat->blocked, &pstat->sigignore, &pstat->sigcatch, &pstat->wchan, &pstat->nswap, 
			&pstat->cnswap, &pstat->exit_signal, &pstat->processor, &pstat->rt_priority, &pstat->policy, &pstat->delayacct_blkio_ticks, &pstat->guest_time, &pstat->cguest_time);
			error = 0;
			break;
		}
	}
	closedir( dir );
	if (error)
		printf( "procStat: processName \"%s\" not found\n", processName);
	return error;
}

int procPid(char *processName, int *pid)
{
	struct structProcStat pstat;

	*pid = -1;
	if ((procStat(processName, &pstat)))
		return -1;

	*pid = pstat.pid;
	return 0;
}

int procName(int pid, char *name)
{
	char 	*s, *e, fileName[_POSIX_PATH_MAX], statString [PROCSTAT_STR_LENGTH_MAX];

	*name='\0';
  	sprintf (fileName, "/proc/%u/stat", (unsigned) pid);
	if ((getFileStream(fileName, statString, PROCSTAT_STR_LENGTH_MAX)) == -1)
		return -1;

	s = strchr (statString, '(') + 1;
	e = strchr (statString, ')');
	strncpy(name, s, e - s);
	name[e-s] = '\0';

	return 0;
}

int procStatm(char *processName, int pid, struct structProcStatm *pstatm)
{
	struct  structProcStat pstat;
	char 	fileName[_POSIX_PATH_MAX], statmString [PROCSTATM_STR_LENGTH_MAX];

	if (pid == -1)
	{
		if ((procStat(processName, &pstat)))
			return -1;
		pid = pstat.pid;
	}

  	sprintf (fileName, "/proc/%u/statm", (unsigned) pid);

	if ((getFileStream(fileName, statmString, PROCSTATM_STR_LENGTH_MAX)) == -1)
		return -1;

	sscanf (statmString, "%d %d %d %d %d %d %d", &pstatm->size, &pstatm->resident, &pstatm->share, &pstatm->text, &pstatm->lib, &pstatm->data, &pstatm->dt);
	return 0;
}

int procMemInfo(struct structProcMemInfo *pminfo)
{
	char 	meminfoString [PROCMEMINFO_STR_LENGTH_MAX];

	if ((getFileStream("/proc/meminfo", meminfoString, PROCMEMINFO_STR_LENGTH_MAX)) == -1)
		return -1;
	sscanf (meminfoString,    "MemTotal:       %8lu kB", &pminfo->totalram); 
	return 0;
}

char *proc_filename(const char *directory, const char *postfix, const char *ext, char *filename)
{
	if (filename && strlen(filename))
		return filename;
	
	procFilename(directory, postfix, ext, filename);
	printf("proc_filename: %s log filename = %s\n", postfix, filename);

	return filename;
}

int fileExists(char *name)
{
	struct stat buffer;   
	return (stat (name, &buffer) == 0); 
}

