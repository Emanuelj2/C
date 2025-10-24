#include <stdlib.h>
#include <stdio.h>

int main()
{

    //init memory allocation
    int *arr = (int*)malloc(5 * sizeof(int)); //allocated 5 garbage values

    //check if the allocation good
    if(arr == NULL)
    {
        printf("Allocation Fail!");
        exit(1);
    }

    //print out the array
    for(int i = 0; i < 5; i++)
    {
        arr[i] = i;
    }
    printf("\n");


    // Need more space - resize to 10 elements
    int *temp = (int*)realloc(arr, 10 * sizeof(int));
    if (temp == NULL) {
        // Realloc failed, original memory still valid
        fprintf(stderr, "Realloc failed\n");
        free(arr);
        exit(1);
    }
    arr = temp;  // Update pointer

    for (int i = 5; i < 10; i++) {
    arr[i] = i;
    }

    // Can also shrink
    arr = (int*)realloc(arr, 7 * sizeof(int));

    free(arr);
    return 0;
}