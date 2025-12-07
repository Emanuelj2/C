#include <stdio.h>
#include <stdlib.h>   
#include <pthread.h>
#include <semaphore.h>

// node struct
typedef struct __node_t {
    int key;
    struct __node_t *next;
} node_t;

// list structure
typedef struct __list_t {
    node_t *head;
    pthread_mutex_t lock;
} list_t;

// initialize the list
void list_init(list_t *l) {
    l->head = NULL;
    pthread_mutex_init(&l->lock, NULL);
}

int list_insert(list_t *l, int key) {
    node_t *new_node = malloc(sizeof(node_t));
    if (new_node == NULL) {
        perror("malloc");
        return -1;
    }

    new_node->key = key;   

    pthread_mutex_lock(&l->lock);

    // CRITICAL SECTION
    new_node->next = l->head;
    l->head = new_node;

    pthread_mutex_unlock(&l->lock);

    return 0;
}

int list_lookup(list_t *l, int key) {
    int rv = -1;
    pthread_mutex_lock(&l->lock);

    node_t *curr = l->head;
    while (curr) {
        if (curr->key == key) {
            rv = 0;
            break;
        }
        curr = curr->next;
    }

    pthread_mutex_unlock(&l->lock);
    return rv;
}

// free all nodes
void list_destroy(list_t *l) {
    pthread_mutex_lock(&l->lock);
    node_t *curr = l->head;
    while (curr) {
        node_t *tmp = curr;
        curr = curr->next;
        free(tmp);
    }
    l->head = NULL;
    pthread_mutex_unlock(&l->lock);
    pthread_mutex_destroy(&l->lock);
}

int main(int argc, char **argv) {
    list_t mylist;
    list_init(&mylist);

    list_insert(&mylist, 10);
    list_insert(&mylist, 20);

    printf("Lookup 10: %s\n", list_lookup(&mylist, 10) == 0 ? "Found" : "Not Found");
    printf("Lookup 30: %s\n", list_lookup(&mylist, 30) == 0 ? "Found" : "Not Found");

    list_destroy(&mylist);
    return 0;
}