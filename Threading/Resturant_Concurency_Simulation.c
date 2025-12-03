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
int in = 0; out = 0;

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

