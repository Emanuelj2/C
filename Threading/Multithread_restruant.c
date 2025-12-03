#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define MAX_ORDERS 5 // this is the max amountof orders that can be taken

sem_t tables;
sem_t empty, full;

pthread_mutex_t order_lock = PTHREAD_MUTEX_INITIALIZER;
pthread_spinlock_t log_lock;


//make the queue
int order_queue[MAX_ORDERS];
int in =0; int out = 0; //this keeps track of how many orders are in and out

void log_msg(char* msg)
{
    pthread_spin_lock(&log_lock);
    printf("%s\n", msg);
    pthread_spin_unlock(&log_lock);
}

void* chef(void *arg)
{
    while(1)
    {
        sem_wait(&full);
        pthread_mutex_lock(&order_lock);

        int order = order_queue[out];
        out = (out + 1) % MAX_ORDERS;

        pthread_mutex_unlock(&order_lock);
        
        log_msg("Chef is cooking an order");
        sleep(1);
    }
}

void* customer(void* arg)
{
    int id = *(int*)arg;

    sem_wait(&tables);
    char buffer[50];
    sprintf(buffer, "Customer %d seted", id);
    log_msg(buffer);

    sem_wait(&empty);
    pthread_mutex_lock(&order_lock);

    order_queue[in] = id;
    in = (in + 1) % MAX_ORDERS;

    pthread_mutex_unlock(&order_lock);
    sem_post(&full);

    sleep(2);
    sprintf(buffer, "customer %d finished eating", id);
    log_msg(buffer);

    sem_post(&tables);

    return NULL;
    
}

int main()
{
    pthread_t chefs[2], customer_threads[5];
    int ids[5];

    sem_init(&tables, 0, 3); //there are three tables
    sem_init(&empty, 0, MAX_ORDERS);
    sem_init(&full, 0, 0);
    pthread_spin_init(&log_lock, PTHREAD_PROCESS_PRIVATE);

    for(int i = 0; i < 2; i++)
    {
        pthread_create(&chefs[i], NULL, chef, NULL);
    }

    for(int i = 0; i < 5; i++)
    {
        ids[i] = i + 1;
        pthread_create(&customer_threads[i], NULL, customer, &ids[i]);
    }

    for(int i = 0; i < 5; i++)
    {
        pthread_join(customer_threads[i], NULL);
    }

    return 0;
}