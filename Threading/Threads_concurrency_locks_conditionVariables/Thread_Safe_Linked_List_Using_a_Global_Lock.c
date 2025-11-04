#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

typedef struct Node {
    int value;
    struct Node* next;
} Node;

Node* head = NULL;                  // shared linked list head
pthread_mutex_t lock;              // single global lock

void* insert(void* arg) {
    int val = *(int*)arg;

    pthread_mutex_lock(&lock);     // lock the whole list

    Node* newNode = malloc(sizeof(Node));
    newNode->value = val;
    newNode->next = head;
    head = newNode;

    pthread_mutex_unlock(&lock);   // unlock
    return NULL;
}

int main() {
    pthread_t threads[5];
    int values[5] = {10, 20, 30, 40, 50};

    pthread_mutex_init(&lock, NULL);

    for (int i = 0; i < 5; i++) {
        pthread_create(&threads[i], NULL, insert, &values[i]);
    }

    for (int i = 0; i < 5; i++) {
        pthread_join(threads[i], NULL);
    }

    pthread_mutex_destroy(&lock);

    printf("List contents:\n");
    Node* curr = head;
    while (curr != NULL) {
        printf("%d ", curr->value);
        curr = curr->next;
    }
    printf("\n");

    return 0;
}
