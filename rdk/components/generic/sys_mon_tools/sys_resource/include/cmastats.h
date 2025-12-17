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
#ifndef	CMASTATS_H
#define CMASTATS_H

#include <stdio.h>

#include "avlTree.h"

class CmaStats
{
public:
	CmaStats() : count(0), cpcount(0), maxDiff(0), cparts(false), asizes(false), file(0), line(0)  {};
	CmaStats(unsigned int asize, char *file, int line);
	~CmaStats();

	void* operator new(size_t);
	void  operator delete(void*);

	//CmaStats(const CmaStats &rhs);
	CmaStats& operator= (const CmaStats& rhs);

	const int GetCount() const { return count; }
	const int GetCPCount() const { return cpcount; }
	const int GetMaxDiff() const { return maxDiff; }

	char *GetFile() const { return file; }
	int   GetLine() const { return line; }
	AVLTree<int, int>* GetSizes() { return &asizes; }
	AVLTree<int, int>* GetCParts() { return &cparts; }

	void Insert(unsigned int cpart);
	bool Insert(unsigned int asize, char *file, int line);

private:
	int			count;
	int			cpcount;
	int			maxDiff;
	AVLTree<int, int>	cparts;
	AVLTree<int, int>	asizes;
	char			*file;
	int			line;
};

#endif // CMASTATS_H
