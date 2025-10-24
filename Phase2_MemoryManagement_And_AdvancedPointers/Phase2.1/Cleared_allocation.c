#include <stdlib.h>
#include <stdio.h>


int main()
{
    int *arr1 = (int*)malloc(10 * sizeof(int)); //allocate garbage vlas
    int *arr2 = (int*)calloc(10, sizeof(int)); //all zeros

    if(arr1 == NULL || arr2 == NULL)
    {
        printf("Allocation failed for arr1 or arr2");
        exit(1);
    }

    for(int i = 0; i < 10; i++)
    {
        printf("%d ", arr1[i]); //this is going to print out garbage values
    }
    printf("\n");

    for(int i = 0; i < 10; i++)
    {
        printf("%d ", arr2[i]);
    }

    free(arr1);
    free(arr2);


    return 0;
}