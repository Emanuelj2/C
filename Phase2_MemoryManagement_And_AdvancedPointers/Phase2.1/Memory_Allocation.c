#include <stdlib.h>
#include <stdio.h>


int main()
{
    //allocate memory for a single digit
    int *ptr = (int*)malloc(sizeof(int));

    //Always check is allocation was successful
    if(ptr == NULL)
    {
        fprintf(stderr, "Memory allocation failed");
        return 1;
    }

    *ptr = 42;
    printf("Value: %d", *ptr);

    free(ptr);
    ptr = NULL;
    return 0;
}