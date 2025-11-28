#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

//need to push to github the rest of the add and commit were done.

//make a global buff var
#define CIRCULAR_BUFFER 5

int buff[CIRCULAR_BUFFER];
int in = 0;
int out = 0;

sem_t empty;
sem_t full;
pthread_mutex_t mutex;


//gemerates number 1 - 20
void *producer_therad(void *arg)
{
    
    for(int item = 1; item <= 20; item++)
    {
        //first check if there is an empty slot
        sem_wait(&empty);
        pthread_mutex_lock(&mutex);

        buff[in] = item;
        printf("Producer: %d\n", item);
        in = (in + 1) % CIRCULAR_BUFFER;

        //insert them
        pthread_mutex_unlock(&mutex); //unlock buff
        sem_wait(&full); //check if it is full
    }
    return NULL;
}

//prints each consumed value
void *consumer_therad(void *arg)
{
    for(int i = 0; i < 20; i++)
    {
        sem_wait(&full);
        pthread_mutex_lock(&mutex);

        int item = buff[out];
        printf("Consumer: %d\n", item);
        out = (out + 1) % CIRCULAR_BUFFER;

        pthread_mutex_unlock(&mutex);
        sem_wait(&empty);
    }
    return NULL;
}

int main()
{
    return 0;
}
