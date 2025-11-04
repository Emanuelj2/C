#include <stdlib.h>
#include <pthread.h>
#include <stdio.h>

//range of numbers 
#define RANGE 100

//create the strucutre of the thread
typedef struct
{
    int id;
    int start;
    int end;
    long partial_sum;
}Thread;

//partial sum function
void* partial_sum(void *arg)
{
    Thread* data = (Thread*) arg;
    data->partial_sum = 0;

    for(int i = data->start; i <= data->end; i++)
    {
        data->partial_sum += i;
    }
    printf("thread: %d\nrange: %d-%d\npartial_sum: %ld\n", data->id, data->start, data->end, data->partial_sum);
    printf("===============\n");
    return NULL;
}


int main()
{
    //ask the user for the number of threads that they want
    int N;
    printf("Enter the number of threads you want to create: ");
    scanf("%d", &N);

    //make the thread
    pthread_t threads[N];
    Thread thread[N];

    //create therads
    for(int i = 0; i < N; i++)
    {
        thread[i].id = i + 1;
        thread[i].start = i * RANGE + 1;
        thread[i].end = (i + 1) * RANGE;
        pthread_create(&threads[i], NULL, partial_sum, &thread[i]);
    }

    long sum = 0;
    for(int i = 0; i < N; i++)
    {
        pthread_join(threads[i], NULL);
        sum += thread[i].partial_sum;
    }

    printf("\ntotal sum from all threads: %ld\n", sum);

    return 0;
}