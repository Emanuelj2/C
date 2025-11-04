#include <stdlib.h>
#include <pthread.h>
#include <stdio.h>

#define RANGE 100
#define NUM_ITERATIONS 10000

// Shared global counter
int counter = 0;
pthread_mutex_t lock;

typedef struct {
    int id;
    int start;
    int end;
    long partial_sum;
    int use_lock; // 1 = use mutex, 0 = no lock
} Thread;

void* partial_sum(void *arg) {
    Thread* data = (Thread*) arg;
    data->partial_sum = 0;

    // Compute partial sum
    for (int i = data->start; i <= data->end; i++) {
        data->partial_sum += i;
    }

    // Increment shared counter
    for (int i = 0; i < NUM_ITERATIONS; i++) {
        if (data->use_lock) {
            pthread_mutex_lock(&lock);
            counter++;
            pthread_mutex_unlock(&lock);
        } else {
            counter++; // Unsafe increment
        }
    }

    printf("thread: %d\nrange: %d-%d\npartial_sum: %ld\n", data->id, data->start, data->end, data->partial_sum);
    printf("===============\n");
    return NULL;
}

int main() {
    int N;
    printf("Enter the number of threads you want to create: ");
    scanf("%d", &N);

    int use_lock;
    printf("Use mutex lock for shared counter? (1 = yes, 0 = no): ");
    scanf("%d", &use_lock);

    pthread_t threads[N];
    Thread thread[N];

    if (use_lock) {
        pthread_mutex_init(&lock, NULL);
    }

    for (int i = 0; i < N; i++) {
        thread[i].id = i + 1;
        thread[i].start = i * RANGE + 1;
        thread[i].end = (i + 1) * RANGE;
        thread[i].use_lock = use_lock;
        pthread_create(&threads[i], NULL, partial_sum, &thread[i]);
    }

    long sum = 0;
    for (int i = 0; i < N; i++) {
        pthread_join(threads[i], NULL);
        sum += thread[i].partial_sum;
    }

    if (use_lock) {
        pthread_mutex_destroy(&lock);
    }

    printf("\ntotal sum from all threads: %ld\n", sum);
    printf("final shared counter value: %d\n", counter);
    printf("expected counter value: %d\n", N * NUM_ITERATIONS);

    return 0;
}