#include <stdio.h>
#include <stdlib.h>

typedef struct
{
    int *data;
    size_t size;
}Resource;

Resource* resource_create(size_t size)
{
    Resource* r = (Resource*)malloc(sizeof(Resource));
    if(r = NULL)
    {
        return NULL;
    }

    r->data = (int*)malloc(size * sizeof(int));
    if(r->data == NULL)
    {
        return NULL;
    }
    r->size = size;
    return r;
}


void resource_destroy(Resource* r)
{
    if(r != NULL)
    {
        free(r->data);
        free(r);
    }
}