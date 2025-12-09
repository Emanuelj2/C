#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <assert.h>
#include <unistd.h>

#define NUM_PRODUCERS 2
#define NUM_CONSUMERS 2
#define ITEMS_PER_PRODUCER 10



typedef struct __node_t
{
    int value;
    struct __node_t *next;
} node_t;

typedef struct __queue_t
{
    node_t *head;
    node_t *tail;
    pthread_mutex_t head_lock, tail_lock;
} queue_t;



queue_t q;
int items_left = NUM_PRODUCERS * ITEMS_PER_PRODUCER;

pthread_mutex_t count_lock = PTHREAD_MUTEX_INITIALIZER;



void Queue_Init(queue_t *q)
{
    node_t *temp = malloc(sizeof(node_t));
    temp->value = 0;
    temp->next = NULL;
    q->head = q->tail = temp;

    pthread_mutex_init(&q->head_lock, NULL);
    pthread_mutex_init(&q->tail_lock, NULL);
}

void Queue_Enqueue(queue_t *q, int value)
{
    node_t *temp = malloc(sizeof(node_t));
    assert(temp != NULL);

    temp->value = value;
    temp->next = NULL;

    pthread_mutex_lock(&q->tail_lock);
        q->tail->next = temp;
        q->tail = temp;
    pthread_mutex_unlock(&q->tail_lock);
}

int Queue_Dequeue(queue_t *q, int *value)
{
    pthread_mutex_lock(&q->head_lock);
        node_t *temp = q->head;
        node_t *new_head = temp->next;
        if(new_head == NULL)
        {
            pthread_mutex_unlock(&q->head_lock);
            return -1;
        }
        *value = new_head->value;
        q->head = new_head;
    pthread_mutex_unlock(&q->head_lock);

    free(temp);
    return 0;
}

void Queue_free(queue_t *q)
{
    node_t *curr = q->head;
    while(curr != NULL)
    {
        node_t *next = curr->next;
        free(curr);
        curr = next;
    }

    pthread_mutex_destroy(&q->head_lock);
    pthread_mutex_destroy(&q->tail_lock);
}


void* producer(void *arg)
{
    int id = *(int*)arg;

    for (int i = 0; i < ITEMS_PER_PRODUCER; i++)
    {
        int value = id * 100 + i;
        Queue_Enqueue(&q, value);
        printf("[Producer %d] Enqueued %d\n", id, value);
        usleep(10000);
    }
    return NULL;
}

void* consumer(void *arg)
{
    int id = *(int*)arg;
    int value;

    while (1)
    {
        if (Queue_Dequeue(&q, &value) == 0)
        {
            pthread_mutex_lock(&count_lock);
                items_left--;
                printf("    [Consumer %d] Dequeued %d (remaining: %d)\n",
                        id, value, items_left);
            pthread_mutex_unlock(&count_lock);

            if (items_left == 0)
                break;
        }
        else
        {
            usleep(5000);
        }
    }
    return NULL;
}

int main()
{
    Queue_Init(&q);

    pthread_t prod[NUM_PRODUCERS];
    pthread_t cons[NUM_CONSUMERS];

    int prod_ids[NUM_PRODUCERS];
    int cons_ids[NUM_CONSUMERS];

    // Start consumers
    for (int i = 0; i < NUM_CONSUMERS; i++)
    {
        cons_ids[i] = i;
        pthread_create(&cons[i], NULL, consumer, &cons_ids[i]);
    }

    // Start producers
    for (int i = 0; i < NUM_PRODUCERS; i++)
    {
        prod_ids[i] = i;
        pthread_create(&prod[i], NULL, producer, &prod_ids[i]);
    }

    // Wait for producers
    for (int i = 0; i < NUM_PRODUCERS; i++)
        pthread_join(prod[i], NULL);

    // Wait for consumers
    for (int i = 0; i < NUM_CONSUMERS; i++)
        pthread_join(cons[i], NULL);

    printf("\nAll work complete.\n");

    Queue_free(&q);
    return 0;
}
