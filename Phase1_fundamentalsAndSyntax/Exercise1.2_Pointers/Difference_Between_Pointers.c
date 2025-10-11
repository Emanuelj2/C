#include <stdlib.h>
#include <stdio.h>

int main()
{
    int arr[] = {10, 20, 30};
    int *ptr = arr; // pointer to first element

    
    printf("Original array: %d %d %d\n", arr[0], arr[1], arr[2]);

    // 1. ptr++
    printf("\nUsing ptr++:\n");
    printf("Pointer points to: %d\n", *ptr);
    ptr++; // move pointer
    printf("Pointer after ptr++ points to: %d\n", *ptr);
    // reset pointer
    ptr = arr;

    // 2. (*ptr)++
    printf("\nUsing (*ptr)++:\n");
    printf("Value before (*ptr)++: %d\n", *ptr);
    (*ptr)++; // increment value
    printf("Value after (*ptr)++: %d\n", *ptr);
    printf("Pointer still points to: %d\n", *ptr);

    // 3. *(ptr++)
    ptr = arr; // reset pointer
    printf("\nUsing *(ptr++):\n");
    printf("Value before *(ptr++): %d\n", *ptr);
    *(ptr++); // access value, then increment pointer
    printf("Pointer now points to: %d\n", *ptr); // next element
    printf("Value at previous element: %d\n", arr[0]);
    return 0;
}