#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

//fuction
void *say_hello(void* arg)
{
    printf("Hello from thread\n");
    return NULL;
}

int main()
{

    pthread_t thread;
    pthread_create(&thread, NULL, say_hello, NULL);
    pthread_join(thread, NULL);
    printf("Main thread finished\n");
    return 0;
}