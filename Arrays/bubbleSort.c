#include <stdlib.h>
#include <stdio.h>

int *BubbleSort(int *arr, int size);

int main()
{

    int arr[10] = {1, 2, 31, 4, 5, 0, 17, 8, 90, 10};
    int size = 10;

    int* bubblesortres = BubbleSort(arr, size);

    printf("Original array: ");
    for (int i = 0; i < size; i++)
    {
        printf("%d ", arr[i]);
    }

    printf("\nSorted array: ");
    for (int i = 0; i < size; i++)
    {
        printf("%d ", bubblesortres[i]);
    }
    printf("\n");

    free(bubblesortres); // Free allocated memory
    
    return 0;
}

int *BubbleSort(int *arr, int size)
{
    //allocate memory for the array
    int* sortedArray = (int*)malloc(size * sizeof(int));

    if(sortedArray == NULL)
    {
        printf("allocation fail");
    }

    //copy the elements from the original array to the new array
    for(int i = 0; i < size; i++)
    {
        sortedArray[i] = arr[i];
    }
    
    //apply bubble sort to the new array
    for(int i = 0; i < size- 1; i++)
    {
        for(int j = 0; j < size - 1 - i; j++)
        {
            if (sortedArray[j] > sortedArray[j + 1])
            {
                int temp = sortedArray[j];
                sortedArray[j] = sortedArray[j + 1];
                sortedArray[j + 1] = temp;
            }
        }
    }
    return sortedArray;
}