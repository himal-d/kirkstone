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
#ifndef	CMAS_MFC_HANDLER_H
#define CMAS_MFC_HANDLER_H

#include "cmastats.h"
#include "backtraceHandler.h"

typedef struct
{
	unsigned long		caller;
	unsigned long		fcount;
	CmaStats 		*cmaStats;
}MfcGroup;

class CmasMfcHandler
{
public:
	CmasMfcHandler(char *filename=0);
	~CmasMfcHandler() {}
	void 		setFilename(const char *postfix, const char *ext);
	void		init(AVLTree<int, CmaStats> &maStats);
	void		schedule_log(AVLTree<int, CmaStats> &maStats);
	void		deinit(AVLTree<int, CmaStats> &maStats);
	void 		collect(unsigned int caller, bool alloc);

private:
	MfcGroup 		**groups;
	BacktraceHandler	mabtHandler;
	BacktraceHandler	mdbtHandler;
};

#endif // CMAS_MFC_HANDLER_H

