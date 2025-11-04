#include <stdlib.h>
#include <pthread.h>
#include <stdio.h>

// range of numbers
#define RANGE 100


long global_sum = 0;

// create the structure for the thread
typedef struct
{
    int id;
    int start;
    int end;
} Thread;

// mutex for protecting shared data
pthread_mutex_t lock;

// partial sum function
void* partial_sum(void *arg)
{
    Thread* data = (Thread*) arg;
    long local_sum = 0;

    for (int i = data->start; i <= data->end; i++)
    {
        local_sum += i;
    }

    // Lock before modifying shared data
    pthread_mutex_lock(&lock);
    global_sum += local_sum;
    pthread_mutex_unlock(&lock);

    printf("thread: %d\nrange: %d-%d\npartial_sum: %ld\n", 
           data->id, data->start, data->end, local_sum);
    printf("===============\n");

    return NULL;
}

int main()
{
    // ask the user for number of threads
    int N;
    printf("Enter the number of threads you want to create: ");
    scanf("%d", &N);

    pthread_t threads[N];
    Thread thread[N];

    // initialize the mutex
    pthread_mutex_init(&lock, NULL);

    // create threads
    for (int i = 0; i < N; i++)
    {
        thread[i].id = i + 1;
        thread[i].start = i * RANGE + 1;
        thread[i].end = (i + 1) * RANGE;
        pthread_create(&threads[i], NULL, partial_sum, &thread[i]);
    }

    // wait for threads to finish
    for (int i = 0; i < N; i++)
    {
        pthread_join(threads[i], NULL);
    }

    // destroy mutex
    pthread_mutex_destroy(&lock);

    printf("\ntotal sum from all threads: %ld\n", global_sum);
    return 0;
}
