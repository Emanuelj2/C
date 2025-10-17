#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

//#define NTHREAD 3

//make a struct for args
typedef struct
{
    int id;
    long start;
    long end;
}ThreadArg;

static const int NTHREAD = 3;

static int started = 0;
static pthread_mutex_t m = PTHREAD_MUTEX_INITIALIZER;  
static pthread_cond_t cv = PTHREAD_COND_INITIALIZER;

static void* worker(void* vp)
{

    //-----critical section-----
    ThreadArg* args = (ThreadArg*) vp; //casting

    pthread_mutex_lock(&m); //lock
    started++;
    pthread_cond_signal(&cv);
    pthread_mutex_unlock(&m); //unlock
    //--------------------------

    long long* ret = malloc(sizeof(long long));
    *ret = 0;
    for(long i = args->start; i < args->end; i++)
    {
        *ret += 1;
    }

    return ret;
}


int main()
{
    pthread_t th[NTHREAD]; //defined three threads
    ThreadArg args[NTHREAD];

    long chunk = 100;

    //create the worker threads
    for(int t = 0; t < NTHREAD; t++)
    {
        args[t] = (ThreadArg) {t, 1+t*chunk, (t+1) * chunk};
        pthread_create(&th[t], NULL, worker, &args[t]);
    }

    pthread_mutex_lock(&m);
    while(started < NTHREAD)
    {
        pthread_cond_wait(&cv, &m);
    }
    pthread_mutex_unlock(&m);

    printf("main: all workers started\n");

    long long total = 0;

    //join the threads
    for(int t= 0; t < NTHREAD; t++)
    {
        long long* part = NULL;
        pthread_join(th[t], (void**) &part);
        printf("Joined T%d -> %lld\n", t, *part);
        total += *part; //total is the vlaue of the part
        free(part);
    }

    printf("Total is %lld", total);

    return 0;
}