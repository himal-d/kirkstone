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

#include "cmastats.h"
#include "zmalloc.h"

CmaStats::CmaStats(unsigned int asize, char *_file, int _line) : count(1), cpcount(0), maxDiff(1), cparts(false), asizes(false), file(_file), line(_line)
{
	asizes.Insert(asize);
	if (_file)
	{
		int len = strlen(_file)+1;
		file = (char*)zmalloc(len);
		strncpy(file, _file, len);
	}
}

CmaStats::~CmaStats()
{
	zfree(file);
}

void* CmaStats::operator new (size_t size)
{
	return zmalloc(size);
}

void CmaStats::operator delete (void *p)
{
	zfree(p);
}

CmaStats &CmaStats::operator= (const CmaStats &rhs)
{
	if (this == &rhs)
		return *this;

	zfree(file);
	file=rhs.file;
	line=rhs.line;
	return *this;
}

void CmaStats::Insert(unsigned int acpart)
{
	++cpcount;
	cparts.Insert(acpart);
}

bool CmaStats::Insert(unsigned int asize, char *file, int line)
{
	++count;
	AVLNode<int, int>*	node=0;
	if (file && !this->file && !this->line)
	{
		int len = strlen(file)+1;
		this->file = (char*)zmalloc(len);
		strncpy(this->file, file, len);
		this->line=line;
	}
	if (maxDiff < count - cpcount) ++maxDiff;
	return asizes.Insert(asize, node);
}
