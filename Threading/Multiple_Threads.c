#include <pthread.h>
#include <stdio.h>

#define NTHREADS 3

void *print_num(void* arg)
{
    int num = *(int*)arg; //cast int to arg
    printf("Thread %d is rumming\n", num);
    return NULL;
}

int main()
{
    //initilaze the thread
    pthread_t thread[NTHREADS];
    
    int ids[NTHREADS];

    for(int i = 0; i < NTHREADS; i++)
    {
        ids[i] = i + 1;
        pthread_create(&thread[i], NULL, print_num, &ids[i]);
    }

    for(int i = 0; i < NTHREADS; i++)
    {
        pthread_join(thread[i], NULL);
    }

    return 0;
}