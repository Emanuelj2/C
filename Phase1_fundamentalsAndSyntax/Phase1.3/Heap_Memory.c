#include <stdlib.h>
#include <stdio.h>

int main()
{
    int *ptr = (int*)malloc(sizeof(int)); // Allocate 4 bytes
    if(ptr == NULL)
    {
        fprintf(stderr, "Memory allocation failed.");
        return 1;
    }

    *ptr = 45;
    printf("%d\n", *ptr);


    //must manually free 
    free(ptr);
    ptr = NULL; //good practice: this avoids dangling pointer


    //allocate array in the heap
    int *arr = (int*)malloc(100 * sizeof(int));
    if(arr == NULL)
    {
        fprintf(stderr, "Memory allocation failed");
    }

    for(int i = 0; i < 100; i++)
    {
        arr[i] = i;
    }

    //free array
    free(arr);
    arr = NULL;
    return 0;
}