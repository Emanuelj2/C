/*
 Write a program that allocates an array on the heap,
 fills it with values, and then reallocates it to a
 larger size without losing data.
*/
#include <stdio.h>
#include <stdlib.h>

#define ARRAY_SIZE 10
#define NEW_ARRAY_SIZE 15

int main()
{
    //allocate memory
    int *arr = (int*)malloc(ARRAY_SIZE * sizeof(int));
    if (arr == NULL) {
        printf("Memory allocation failed!\n");
        return 1;
    }

    //fill in the array
    for(int i = 0; i < ARRAY_SIZE; i++)
    {
        arr[i] = i;
    }

    //print the array
    printf("Original array: ");
    for(int i = 0; i < ARRAY_SIZE; i++)
    {
        printf("%d, ", arr[i]);
    }
    printf("\n");

    //reallocate the memory
    int *temp = (int*)realloc(arr, NEW_ARRAY_SIZE * sizeof(int));
    if(temp == NULL)
    {
        printf("Memory allocation fail");
        free(arr);
        return 1;
    }

    arr = temp;

    // Fill the new elements
    for (int i = ARRAY_SIZE; i < NEW_ARRAY_SIZE; i++) {
        arr[i] = i + 1;
    }

    printf("New array: ");
    //print the new array
    for(int i = 0; i < NEW_ARRAY_SIZE; i++)
    {
        printf("%d, ", arr[i]);
    }
    printf("\n");

    free(arr);
    return 0;
}