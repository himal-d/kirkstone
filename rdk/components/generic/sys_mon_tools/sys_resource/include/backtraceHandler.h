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
#ifndef	BACKTRACE_HANDLER_H
#define BACKTRACE_HANDLER_H

#include <stdio.h>
#include <limits.h>

#include "sysresLogger.h"
#include "backtrace.h"
#include "avlTree.h"

class BacktraceHandler : public SysResLogger
{
public:
	BacktraceHandler(size_t size, char *filename=0, const int collect=INT_MAX) : SysResLogger(size, filename), bt(), btEnable(false), btUpdate(false), btCollect(collect), btCollected(0) {}
	~BacktraceHandler() {}

	void setFilename(const char *postfix, const char *ext);
	void resetUpdate() { btUpdate=false; }
	void schedule_log(unsigned int caller, unsigned int cpart=0);
	void collect(unsigned int caller);

	int  getSize() const { return bt.getSize(); }
	int  getCollected() const { return btCollected; }
	bool getEnable() const { return btEnable; }
	bool getUpdate() const  { return btUpdate; }

private:
	enum   btStatus_t	{ btsNotAvailable = 0, btsAdded = 1, btsExists = 2 };
	AVLTree<int, Backtrace>	bt;
 	bool 			btEnable;
 	bool 			btUpdate;
	const int 		btCollect;
	int  			btCollected;

	btStatus_t 		log(AVLNode<int, Backtrace>* btNode, unsigned int caller, unsigned int cpart);
};

#endif // BACKTRACE_HANDLER_H

