/*
 * If not stated otherwise in this file or this component's Licenses.txt file the
 * following copyright and licenses apply:
 *
 * Copyright 2018 RDK Management
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
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <inttypes.h>

void read_config(int argc, char ** argv);
void create_threads();
void collect_threads();
void print_results();


// struct for storing configuration collected from command line arguments
struct Configuration
{
    // if run_till_death is true, total_alloc_size will have no effect
    // usefull for finding the limits of the system. In most of the benchmark cases we might not
    // want to get killed, as we need system performance also at those alloations.
    int run_till_death                    = 0;

    // waits for user key input before colleting the threads
    // might be helpfull when looking at stressed system
    int wait_after_finish                 = 0;

    // number of threads used
    int num_threads                       = 1;

    // total amount of memory to be allocated
    // unsigned long long total_alloc_size   = 70*1024L*1024L; // eg 70mb
    unsigned long long total_alloc_size   = 20673280L; //aprox 20m

    // size of memory allocated with each call to malloc
    size_t alloc_block_size               = 1*1024*1024; // 1 MB/allocation

    // if we need to insert some delay after each allocation
    unsigned int sleep_bw_ops                      = 0; // us zero means don't sleep

    unsigned int keep_mem_hot                      = 0; // us zero means don't keep it hot, number will keep it hot with delay between every read.

    unsigned int write_random_data                 = 1; // default writes random numbers

    // need to think of introducing some entropy in the way we keep memory hot
    // const int randomness                     = 0;
    // end of configuration parameters
};


// struct for tracking stats
struct Alloc_stats {
    unsigned int       index;       // index in the array here it will be stored
    pthread_t          tid;         // thread id
    unsigned long long size;        // accumulation of allocated memory
    clock_t            ticks_taken; // time taken to do its task
    clock_t            hot_ticks_taken; // processor time taken while keeping the memory hot
};

// array where we keep our threads
Alloc_stats *thread_tracker;

Configuration config; // global config

// condition variables so that the threads can signal that they are done.
// If we don't want to straight away collect all of them and exit. this will
// give a nice pause point to see what was the system state at the peak of
// our allocation
pthread_mutex_t cond_var_lock =  PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond_var       = PTHREAD_COND_INITIALIZER;


// main thread doing the job. beviour depends on config collected from
// command line arguments
void* worker_thread(void *arg)
{
    pthread_t id = pthread_self();
    clock_t starttime = clock();

    printf("thread id is : %lu\n", id);

    // allocation loop
    long long loop_size = config.total_alloc_size/config.num_threads/config.alloc_block_size;

    printf("loop size is %lld with each alloation %lu MB\n", loop_size, config.alloc_block_size/1024/1024);

    unsigned long long int allocation_counter = 0;
    srand(time(NULL));  // init random number generator

    // need to allocate some memory to keep track of our allocated block
    // we are not accounting for memory allocated for this tracker.
    // this might impact measurement results when using smaller alloc sizes.
     void ** memory_tracker = (void **)calloc(loop_size, sizeof(void *));


    for( int i = 0; i < loop_size; i++)
    {
        // preprae for loop till death
        if (config.run_till_death) {
            i--; // loop will run forever
        }

        void * mem = malloc(config.alloc_block_size);
        if(!mem) {
            printf("are we out of memory? shouldn't default overcommit policy allow for always non zero and oom lateron?");
            fflush(stdout);
            exit(-1);
        }

        // track allocated memory for later hot loop
        memory_tracker[i] = mem;


        // we need memset because just like malloc, calloc also cheats and will succeed even if we
        // don't have that memory. As we will be testing compressed memory/swap options, lets take
        // this opporitunity to fill it with random numbers.
        // zero or constant fill has too little entropy and will have insanely large compression ratio
        // real data will be closer to random that a bunch of zeros
        if (config.write_random_data) {
            unsigned int int_counts = config.alloc_block_size/4;
            int *write_ptr=(int*)mem;
            for (unsigned int i = 0; i < int_counts; i++)
            {
                *write_ptr = rand();
                write_ptr++;
            }
        } else {
            memset(mem, 'a', config.alloc_block_size);
        }

        allocation_counter += config.alloc_block_size;

        if (config.run_till_death) {
            printf("%llu\n",allocation_counter);
            fflush(stdout);
        }

        // yeild after every allocation, so that all threads are roughly moving at the same pace.
        // we can have configurtion per thread if we ever need differene allocation speeds
        if (config.sleep_bw_ops)
            usleep(config.sleep_bw_ops);
        else
            pthread_yield();
    }


    // store the stats in this threads struct
    unsigned int thread_index = *((unsigned int *)arg);
    thread_tracker[thread_index].ticks_taken = clock() - starttime;
    thread_tracker[thread_index].size = allocation_counter;



    // keep the memory hot
    if (config.keep_mem_hot) {
        while(1) { // keep hot forever
            clock_t hot_timer_start = clock();
            for( int i = 0; i < loop_size; i++)
            {
                if (config.write_random_data) {
                    unsigned int int_counts = config.alloc_block_size/4;
                    int *write_ptr=(int*)memory_tracker[i];
                    for (unsigned int i = 0; i < int_counts; i++)
                    {
                        *write_ptr = rand();
                        write_ptr++;
                    }
                } else {
                    memset(memory_tracker[i], 'a', config.alloc_block_size);
                }
                usleep(config.keep_mem_hot);
            }
            thread_tracker[thread_index].hot_ticks_taken = clock() - hot_timer_start;
            float time_in_secs = ((long double)thread_tracker[thread_index].hot_ticks_taken)/CLOCKS_PER_SEC;
            printf("HOT mem(bytes):%llu time(secs):%f speed(mbps):%f\n",
                   thread_tracker[thread_index].size, time_in_secs, thread_tracker[thread_index].size/1024/1024/time_in_secs);
        }
    }


    // signal the main thread that we are done
    pthread_mutex_lock(&cond_var_lock);
    pthread_cond_signal(&cond_var);
    pthread_mutex_unlock(&cond_var_lock);


    return NULL;
}

int main(int argc, char** argv)
{
    setlinebuf(stdout); // ensure fflush at line end

    read_config(argc,argv);

    create_threads();

    pthread_mutex_lock(&cond_var_lock);
    pthread_cond_wait(&cond_var, &cond_var_lock);
    pthread_mutex_unlock(&cond_var_lock);

    if (config.wait_after_finish) {
        char key;
        printf("we didn't get oom yet and atleast on thread is done. press any key to join the thraeds\n");
        scanf("%c", &key);
    }

    collect_threads();

    print_results();

    return 0;
}

void read_config(int argc, char ** argv)
{
    int index;
    int c;

    opterr = 0;

    while ((c = getopt (argc, argv, "rwn:t:b:s:k:a:")) != -1)
        switch (c)
        {
        case 'r':
            config.run_till_death = 1;
            break;
        case 'w':
            config.wait_after_finish = 1;
            break;
        case 'n':
            config.num_threads = strtoimax(optarg, NULL, 10);
            break;
        case 't':
            config.total_alloc_size = strtoull(optarg, NULL, 10);
            break;
        case 'b':
            config.alloc_block_size = strtoul(optarg, NULL, 10);
            break;
        case 's':
            config.sleep_bw_ops = strtoul(optarg, NULL, 10);
            break;
        case 'k':
            config.keep_mem_hot = strtoul(optarg, NULL, 10);
            break;
        case 'a':
            config.write_random_data = strtoul(optarg, NULL, 10);
            break;
        case '?':
            fprintf (stderr, "problem with either option or option argument\n");
            abort();
            return;
        default:
            abort ();
        }


      for (index = optind; index < argc; index++)
        printf ("Non-option argument %s\n", argv[index]);


      printf("arguments are : %d, %d, %u, %llu, %lu, %u, %u, %u\n",
             config.run_till_death, config.wait_after_finish,
             config.num_threads, config.total_alloc_size,
             config.alloc_block_size, config.sleep_bw_ops,
             config.keep_mem_hot, config.write_random_data);
}

void create_threads()
{
    int i = 0;
    int err = 0;

    thread_tracker = (Alloc_stats *) calloc(config.num_threads, sizeof(Alloc_stats));


    while(i < config.num_threads)
    {
        thread_tracker[i].index = i;
        err = pthread_create(&(thread_tracker[i].tid), NULL,
                             &worker_thread, (void *) &(thread_tracker[i].index) );
        if (err != 0)
            printf("can't create thread :[%s]\n", strerror(err));
        else
            printf("Thread created successfully\n");

        i++;
    }
}

void collect_threads()
{
    int i = 0;
    int err = 0;
    void *res;

    while(i < config.num_threads)
    {
        err = pthread_join(thread_tracker[i].tid, &res);
        if (err != 0)
            printf("failed to join thread: [%s]\n", strerror(err));
        else
            printf("joined thread successfully\n");

        i++;
    }
}

void print_results()
{
    // collect totals
    unsigned long long totalSize = 0 ;
    clock_t totalTime = 0;
    int i = 0;
    while (i < config.num_threads)
    {
            totalTime += thread_tracker[i].ticks_taken;
            totalSize += thread_tracker[i].size;
            i++;
    }


    float time_in_secs = ((long double)totalTime)/CLOCKS_PER_SEC;
    printf("mem(bytes):%llu time(secs):%f speed(mbps):%f\n",
           totalSize, time_in_secs, totalSize/1024/1024/time_in_secs);
}
