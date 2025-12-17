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
#include <cstring>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>
#include <libgen.h>

#include "procInfo.h"
#include "backtraceHandler.h"
#include "dbgMLT.h"
#include "debugRecord.h"

#define	BT_FILENAME_LENGTH	64

void BacktraceHandler::setFilename(const char *postfix, const char *ext)
{
	DBG_BTRC(WDR("btl::setFilename: postfix = %s ext = %s\n", postfix, ext));
	SysResLogger::SetFilename(postfix, ext);
	DBG_BTRC(WDR("btl::setFilename: postfix = %s ext = %s ...done\n", postfix, ext));
}

void BacktraceHandler::schedule_log(unsigned int caller, unsigned int cpart)
{
	AVLNode<int, Backtrace>* btNode=0;
	if (bt.Insert(caller, btNode) == false)
	{
		btStatus_t btStat=log(btNode, caller, cpart);
		if (btStat == btsAdded) ++btCollected;
		else if (btStat == btsNotAvailable) btUpdate=true;
	}
	else
		btUpdate=true;

	// Second check for a not default btCollect case; it's always false for the default one. 
	if (bt.getSize() <= btCollected || (btCollect <= btCollected && btUpdate == false))
		btEnable=false;
	else
		btEnable=true;
}

void BacktraceHandler::collect(unsigned int caller)
{
	AVLNode<int, Backtrace>* btNode=0;
	if (btEnable && bt.Find(caller, btNode) && btNode)
	{
		Backtrace *backtrace=btNode->GetDataPtr();
		if (backtrace && backtrace->GetSize() == 0)
			backtrace->Init();
	}
}

BacktraceHandler::btStatus_t BacktraceHandler::log(AVLNode<int, Backtrace>* btNode, unsigned int caller, unsigned int cpart)
{
	int size=0;
	Backtrace *backtrace=btNode->GetDataPtr();
	if (backtrace && (size=backtrace->GetSize()))
	{
		char file[BT_FILENAME_LENGTH]={0};
		if (cpart) 
			sprintf(file, "%s.%8.8p.%8.8p", filename, (void*)cpart, (void*)caller);
		else
			sprintf(file, "%s.%8.8p", filename, (void*)caller);
		if (!fileExists(file))
		{
			int  len=0;
			unsigned int *bt=backtrace->GetBacktrace();
			for (int i=0; i<size; i++) len+=sprintf(logBuffer+len,"%p\n", (void*)bt[i]);

			// create and write to backtrace file
			DBG_BTRC(WDR("btl: caller = %p bt adding = %s\n", (void*)caller, file));
			Log(len, file);

			// append backtrace file name to the backtrace log file
			sprintf(logBuffer, "%s\n", basename(file));
			sprintf(file, "%s.log", filename);
			DBG_BTRC(WDR("btl: bt log file name = %s : bt file = %s\n", file, logBuffer));
			Log(strlen(logBuffer), file);

			return btsAdded;
		}
		else
		{
			//DBG_BTRC(WDR("btl: caller = %p bt already exists = %s\n", caller, file));
			return btsExists;
		}
	}
	else
	{
		DBG_BTRC(WDR("btl: caller = %p bt is not available yet\n", (void*)caller));
		return btsNotAvailable;
	}
}

