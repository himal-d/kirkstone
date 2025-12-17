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
#include	<stdio.h>
#include	<string.h>

#include	"IMemoryPartition.h"
#include	"fixedSizePartition.h"
#include	"heapPartition.h"
#include	"procStatmS.h"

#ifdef SIMPLE_FMP_TEST
#define FMP_SAPI			1
#define SFMP_PARTITION_BLOCKS		4
#define SFMP_PARTITION_BLOCK_SIZE	28
#endif

#ifdef USE_CMAT_SSTATS
#include <sys/time.h>
#include "simpleStats.h"
#include "elapsedTime.h"

#define FMAT_PARTITION_BLOCKS		(1000*1000)
#define FMAT_PARTITION_BLOCK_SIZE	28

#define	CMAT_SSTATS(x)			x
#define	fmatBufferLength		(16*1024)
#define	fmatDistrRange			1000
#define	fmatDistrBin			100	// 1 - 1nsec; 10 - 10nsec; 100 - 100nsec; 1000 - 1usec; 10000 - 10usec; 100000 - 1000usec.
SimpleDistribution<float, int> 		fmatAddTD(fmatDistrRange);
SimpleDistribution<float, int> 		fmatDelTD(fmatDistrRange);
ElapsedTime 				fmatElapsedTime;
char					fmatBuffer[fmatBufferLength];
#else
#define	CMAT_SSTATS(x)
#endif

void	testfixedSizePartition()
{
	printf("testfixedSizePartition:\n");
#ifdef SIMPLE_FMP_TEST
	void	*fs[SFMP_PARTITION_BLOCKS+1];
	int 	size=sizeof (ProcStatmS);

#if USE_CUSTOM_MM && USE_FIXED_SIZE_PARTITION
	size=SFMP_PARTITION_BLOCK_SIZE;
	IMemoryPartition *partition = (IMemoryPartition *) new FixedSizePartition (SFMP_PARTITION_BLOCKS, SFMP_PARTITION_BLOCK_SIZE);
#elif USE_CUSTOM_MM
	IMemoryPartition *partition = (IMemoryPartition *) new HeapPartition ();
#else
	IMemoryPartition *partition = 0;
#endif
	printf("USE_CUSTOM_MM = %d : USE_FIXED_SIZE_PARTITION = %d : FMP_SAPI = %d : partition = %p\n", USE_CUSTOM_MM, USE_FIXED_SIZE_PARTITION, FMP_SAPI, partition);

	printf("allocations:\n");
	for (int i=0; i<SFMP_PARTITION_BLOCKS+1; i++)
	{
#if FMP_SAPI
#if USE_FIXED_SIZE_PARTITION
		printf("%p %d\n", fs[i]= create<ProcStatmS>(partition), ((FixedSizePartition*)partition)->blocksAvailable());
#else
		printf("%p\n", fs[i]= create<ProcStatmS>(partition));
#endif

#else //FMP_SAPI
#if USE_CUSTOM_MM && USE_FIXED_SIZE_PARTITION
		printf("%p %d\n", fs[i]= new (partition) ProcStatmS(), ((FixedSizePartition*)partition)->blocksAvailable());
#elif USE_CUSTOM_MM
		printf("%p\n", fs[i]= new (partition) ProcStatmS());
#else
		printf("%p\n", fs[i]= new ProcStatmS());
#endif

#endif //FMP_SAPI
		if (fs[i])
		{
			memset (fs[i], i, size);
			for (int j=0; j<size; j++) printf("%d ", *(char*)fs[i]);
			printf("\n");
		}
	}
	printf("deallocations:\n");

	for (int i=0; i<SFMP_PARTITION_BLOCKS+1; i++)
	{
		printf("%p ", fs[i]);
#if FMP_SAPI
		destroy<ProcStatmS>((ProcStatmS*)fs[i], partition);
#else  //FMP_SAPI

#if USE_CUSTOM_MM
		//((ProcStatmS*)fs[i])->~ProcStatmS();
		//operator delete (fs[i], partition);
		destroy<ProcStatmS>((ProcStatmS*)fs[i], partition);
#else
		delete fs[i];
#endif

#endif //FMP_SAPI


#if USE_CUSTOM_MM && USE_FIXED_SIZE_PARTITION
		printf("%d\n", ((FixedSizePartition*)partition)->blocksAvailable());
#endif
		printf("\n");
	}

	delete partition;
#endif //SIMPLE_FMP_TEST

#ifdef	USE_CMAT_SSTATS
	void	*fmat[FMAT_PARTITION_BLOCKS];
	FixedSizePartition fmatPartition(FMAT_PARTITION_BLOCKS, FMAT_PARTITION_BLOCK_SIZE);
	printf("allocations:\n");
	for (int i=0; i<FMAT_PARTITION_BLOCKS; i++)
	{
		CMAT_SSTATS(fmatElapsedTime.start());
		fmat[i]=fmatPartition.allocate(FMAT_PARTITION_BLOCK_SIZE);
		CMAT_SSTATS(fmatAddTD.accumulate(fmatElapsedTime.enddiffnsec()/fmatDistrBin));
	}
	printf("deallocations:\n");
	for (int i=0; i<FMAT_PARTITION_BLOCKS; i++)
	{
		CMAT_SSTATS(fmatElapsedTime.start());
		fmatPartition.deallocate(fmat[i]);
		CMAT_SSTATS(fmatDelTD.accumulate(fmatElapsedTime.enddiffnsec()/fmatDistrBin));
	}

	{
		const char *filenameFMAT = "FixedMemoryAllocations.log";
		SimpleStats<float, int> fmatAddStats = fmatAddTD.getStats();
		SimpleStats<float, int> fmatDelStats = fmatDelTD.getStats();
		int bufoff=0;
		bufoff=sprintf(fmatBuffer, "FMAT: distribution range = 0-%d / 0-%d usec : bin size = %d nsec\n", fmatDistrRange, (fmatDistrRange*fmatDistrBin)/1000, fmatDistrBin);

		bufoff+=sprintf(fmatBuffer+bufoff, "FMAT: add/del : mean = %f/%f sd = %f/%f: min = %d/%d: max = %d/%d: size = %d/%d outOfRange = %d/%d maxOut = %d/%d\n",
			fmatAddStats.mean, fmatDelStats.mean, fmatAddStats.sd, fmatDelStats.sd, fmatAddStats.min, fmatDelStats.min, 
			fmatAddStats.max, fmatDelStats.max, fmatAddStats.size, fmatDelStats.size, fmatAddStats.outOfRange, fmatDelStats.outOfRange, fmatAddStats.maxOut, fmatDelStats.maxOut);
		int	*fmatAddDistr=fmatAddTD.getDistribution();
		for (int i=0; i<fmatAddTD.getRange(); i++) bufoff+=sprintf(fmatBuffer+bufoff,"%2d ", fmatAddDistr[i]);
		bufoff+=sprintf(fmatBuffer+bufoff, "\n");
		int	*fmatDelDistr=fmatDelTD.getDistribution();
		for (int i=0; i<fmatDelTD.getRange(); i++) bufoff+=sprintf(fmatBuffer+bufoff,"%2d ", fmatDelDistr[i]);
		bufoff+=sprintf(fmatBuffer+bufoff, "\n");
		bufoff+=sprintf(fmatBuffer+bufoff, "FMAT: buffer length = %d\n", bufoff);
		FILE *file = fopen (filenameFMAT, "a");
		fwrite ((char*)fmatBuffer, 1, bufoff, file);
		fclose (file);
	}
#endif	//USE_CMAT_SSTATS
	printf("testfixedSizePartition: exit.\n");
}
