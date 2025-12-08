#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

//a conditional variable lets threads wait for a condition.
int done = 0;
pthread_mutex_t m = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t c = PTHREAD_COND_INITIALIZER;
//pthread_cond_wait() -> releases lock, sleeps, reacquires when signaled
//pthread_cond_signal() -> wakes one waiting thread.

void thr_exit()
{
    pthread_mutex_lock(&m);
        done = 1;
        pthread_cond_signal(&c);
    pthread_mutex_unlock(&m);
}

void* child(void* arg)
{
    printf("child\n");
    thr_exit();
    return NULL;
}

void thr_join()
{
    pthread_mutex_lock(&m);
        while( done == 0)
        {
            pthread_cond_wait(&c, &m);
        }
    pthread_mutex_unlock(&m);
}

int main()
{
    printf("parent: begin\n");
    pthread_t p;
    pthread_create(&p, NULL, child, NULL);
    thr_join();
    printf("parent: end\n");
    return 0;
}