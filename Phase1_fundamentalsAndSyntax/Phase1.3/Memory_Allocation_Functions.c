#include <stdlib.h>
#include <stdio.h>


int main()
{
    // malloc: allocate uninitialized memory
    int *arr1 = (int*)malloc(10 * sizeof(int)); //allocate 40 bytes

    // calloc: allocate and zero-initialize
    int *arr2 = (int*)calloc(10, sizeof(int)); // All elements are 0

    // realloc: resize allocated memory
    arr1 = (int*)realloc(arr1, 10 * sizeof(int));

    if(arr1 == NULL)
    {
        printf("Allocation fail");
    }

    free(arr1);
    free(arr2);
    return 0;
}