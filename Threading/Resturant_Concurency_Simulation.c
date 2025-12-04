#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <time.h>
#include <stdbool.h>
#include <unistd.h>


//constraints
#define MAX_ORDERS 5
#define MAX_TABLES 3
#define NUM_CHEFS 2
#define NUM_CUSTOMERS 10
#define COOKING_TIME 2
#define EATING_TIME 3

//syncronization primatives
sem_t tables;
sem_t empty, full;
pthread_mutex_t order_lock = PTHREAD_MUTEX_INITIALIZER;
pthread_spinlock_t log_lock;
pthread_mutex_t stats_lock = PTHREAD_MUTEX_INITIALIZER;


//order queue 
typedef struct
{
    int cust_id;
    time_t order_time;
}Order;

Order order_queue[MAX_ORDERS];
int in = 0, out = 0;

//statistics tracking
typedef struct
{
    int total_order_cooked;
    int total_customers_serverd;
    int orders_in_progress;
    time_t start_time;
}Statistics;

Statistics stats = {0,0,0,0};

//volitile flag used for graceful shutdown
volatile bool shutdown_flag = false;

void log_msg(char* msg)
{
    pthread_spin_lock(&log_lock); // the thread “spins” in a loop, repeatedly checking until the lock becomes free

    time_t now = time(NULL);
    struct tm* t = localtime(&now);
    printf("\n%02d:%02d:%02d      %s", t->tm_hour, t->tm_min, t->tm_sec, msg);
    fflush(stdout);

    pthread_spin_unlock(&log_lock);
}

void update_stats(int orders_cooked, int custs_served, int orders_delta)
{
    pthread_mutex_lock(&stats_lock); //ensure that only one thread at a time can access a shared resource

    stats.total_order_cooked += orders_cooked;
    stats.total_customers_serverd += custs_served;
    stats.orders_in_progress += orders_delta;

    pthread_mutex_unlock(&stats_lock);
}

void print_stats()
{
    pthread_mutex_lock(&stats_lock);
    time_t now = time(NULL);
    double elapsed = difftime(now, stats.start_time);

    printf("\nstatistics\n");
    printf("Elapsed time: %.0f\n", elapsed);
    printf("Total orders cooked: %d\n", stats.total_order_cooked);
    printf("Total customers serves: %d\n", stats.total_customers_serverd);
    printf("Orders in progres: %d\n", stats.orders_in_progress);
    printf("\n");

    pthread_mutex_unlock(&stats_lock);
}

void *chef(void* arg) // the void* arg is a generic pointer meaning that it can point to any datatype (you must cast it before use)
{
    int chef_id = *(int*)arg; //casting the arg to an int
    char buffer[100];

    sprintf(buffer, "Chaef %d started working", chef_id);
    log_msg(buffer);

    while(!shutdown_flag)
    {
        struct timespec ts;
        clock_gettime(CLOCK_REALTIME, &ts);
        ts.tv_sec += 1;

        if(sem_timedwait(&full, &ts) == 0) // this functions only wait until a certain time limit before giving up.
        {
            pthread_mutex_lock(&order_lock);
            Order order = order_queue[out];
            out = (out + 1) % MAX_ORDERS;
            pthread_mutex_unlock(&order_lock);

            //signal the the slot is now empty
            sem_post(&empty);
            update_stats(0, 0, 1); //order in progress 

            sprintf(buffer, "Chef %d is cooking the order for customer %d", chef_id, order.cust_id);

            log_msg(buffer);

            sleep(COOKING_TIME);

            sprintf(buffer, "Chef %d finished cooking for customer %d", chef_id, order.cust_id);
            log_msg(buffer);

            update_stats(1, 0, -1); //order compleat
        }
    }
    sprintf(buffer, "Chef %d finished shift", chef_id);
    log_msg(buffer);
    return NULL;
}

void* customer(void* arg)
{
    int cust_id = *(int*)arg;
    char buffer[100];

    sprintf(buffer, "customer %d arrived to the resturant", cust_id);
    log_msg(buffer);

    //wait for a table
    sem_wait(&tables);
    sprintf(buffer, "Customer %d seated at table", cust_id);
    log_msg(buffer);

    //simulate time for the customer to brows a menue
    sleep(rand() % 2 + 1);

    //wait for empty slot in order queue
    sem_wait(&empty);

    pthread_mutex_lock(&order_lock);
    order_queue[in].cust_id = cust_id;
    order_queue[in].order_time = time(NULL);
    in = (in + 1) % MAX_ORDERS;
    pthread_mutex_unlock(&order_lock);

    sprintf(buffer, "Customer %d placed an order", cust_id);
    log_msg(buffer);

    //signal that the order is ready for the chef
    sem_post(&full);

    //wait for food to be cooked and eat
    sleep(COOKING_TIME + EATING_TIME);

    sprintf(buffer, "Customer %d finished eating and leaving", cust_id);
    log_msg(buffer);

    sem_post(&tables); //free the tables

    update_stats(0, 1, 0);

    free(arg);
    return NULL;

}


void *monitor(void* arg)
{
    while(!shutdown_flag)
    {
        sleep(5);
        print_stats();
    }
    return NULL;
}

int main()
{
    pthread_t chefs[NUM_CHEFS];
    pthread_t customers_thread[NUM_CUSTOMERS];
    pthread_t monitor_thread;
    int chef_ids[NUM_CHEFS];


    sem_init(&tables, 0, MAX_TABLES);
    sem_init(&empty, 0, MAX_ORDERS);
    sem_init(&full, 0, 0);
    pthread_spin_init(&log_lock, PTHREAD_PROCESS_PRIVATE);

    stats.start_time = time(NULL);

    //create the chef threads
    for(int i = 0; i < NUM_CHEFS; i++)
    {
        chef_ids[i] = i + 1;
        pthread_create(&chefs[i], NULL, chef, &chef_ids[i]);
    }

    //create the pthread monitor thread
    pthread_create(&monitor_thread, NULL, monitor, NULL);

    //create cust thread
    for(int i = 0; i < NUM_CUSTOMERS; i++)
    {
        int* id = malloc(sizeof(int));
        *id = i + 1;
        pthread_create(&customers_thread[i], NULL, customer, id);
        usleep(500000);
    }

    //wait for all customers to finish
    for(int i = 0; i < NUM_CUSTOMERS; i++)
    {
        pthread_join(customers_thread[i], NULL);
    }
    log_msg("All customers have been served!");

    //signal to shut down and wait a bit for chefs to finish current orders
    shutdown_flag = true;
    sleep(3);

    print_stats();

    //cancel chef therads if in an infinate loop
    for(int i = 0; i < NUM_CHEFS; i++)
    {
        pthread_cancel(chefs[i]);
    }

    pthread_cancel(monitor_thread);

    sem_destroy(&tables);
    sem_destroy(&empty);
    sem_destroy(&full);
    pthread_spin_destroy(&log_lock);
    pthread_mutex_destroy(&order_lock);
    pthread_mutex_destroy(&stats_lock);

    printf("Resturant closed");
    return 0;
}