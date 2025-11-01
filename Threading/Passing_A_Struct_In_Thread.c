#include <pthread.h>
#include <stdlib.h>
#include <stdlib.h>

//create a basic struct

typedef struct
{
    int A;
    int B;
}my_args;


void* myargsfunction(void *arg)
{
    my_args *args = (my_args *) arg; //perfrom a static cast
    printf("%d %d\n", args->A, args->B);
    return NULL;
}

int main()
{
    //make a thread
    pthread_t p;
    my_args args = {10 , 20};

    int rc = pthread_create(&p, NULL, myargsfunction, &args);
    return 0;
}