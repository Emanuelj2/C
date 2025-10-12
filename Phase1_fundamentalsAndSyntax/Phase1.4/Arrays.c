#include <stdio.h>
#include <stdlib.h>

int main()
{
    int arr[5]; //uninitialized (contains garbage values)
    int arr2[5] = {1, 2, 3, 4, 5}; //fully initialized array
    int arr3[5] = {1, 2};  // Partially initialized: {1, 2, 0, 0, 0}
    int arr4[] = {1, 2, 3};  // Size inferred: 3 elements

    printf("First array: ");
    int size_of_arr = sizeof(arr)/ sizeof(arr[0]);
    for(int i = 0; i < size_of_arr; i ++){
        printf("%d, ", arr[i]);
    }
    printf("\n");

    printf("Second array: ");
    int size_of_arr2 = sizeof(arr2)/ sizeof(arr2[0]);
    for(int i = 0; i < size_of_arr2; i ++){
        printf("%d, ", arr2[i]);
    }
    printf("\n");

    printf("Third array: ");
    int size_of_arr3 = sizeof(arr3)/ sizeof(arr3[0]);
    for(int i = 0; i < size_of_arr3; i ++){
        printf("%d, ", arr3[i]);
    }
    printf("\n");
    printf("Third array: ");
    int size_of_arr4 = sizeof(arr4)/ sizeof(arr4[0]);
    for(int i = 0; i < size_of_arr4; i ++){
        printf("%d, ", arr4[i]);
    }
    printf("\n");

    //array and pointer relationship
    int arr_for_pointer_demonstration[5] = {1, 2, 3, 4, 5};
    int *ptr = arr_for_pointer_demonstration;

    printf("First element of the array: %d\n", *ptr);
    printf("Address of first element of the array: %d\n", ptr);
    printf("%d\n", *(ptr+1)); // 2
    printf("%d\n", ptr[2]);   // 3 (ptr[i] is equivalent to *(ptr+i))

    return 0;
}