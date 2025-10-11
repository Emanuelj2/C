#include <stdio.h>
#include <stdlib.h>

int sum(int *arr, int size) {
    int total = 0;
    for (int i = 0; i < size; i++)
        total += arr[i];
    return total;
}

int* square_array(int *arr, int size) {
    int *res = malloc(size * sizeof(int));
    if (!res) return NULL;

    for (int i = 0; i < size; i++)
        res[i] = arr[i] * arr[i];
    return res;
}

// apply_operation for int-returning functions
int apply_operation_int(int *arr, int size, int (*op)(int*, int)) {
    return op(arr, size);
}

// apply_operation for int*-returning functions
int* apply_operation_array(int *arr, int size, int* (*op)(int*, int)) {
    return op(arr, size);
}

int main() {
    int arr[] = {10, 20, 30, 40, 50};
    int size = sizeof(arr) / sizeof(arr[0]);

    int res = apply_operation_int(arr, size, sum);
    printf("The sum of the array is: %d\n", res);

    int *squared = apply_operation_array(arr, size, square_array);
    if (!squared) {
        printf("Memory allocation failed\n");
        return 1;
    }

    printf("Squared array: ");
    for (int i = 0; i < size; i++)
        printf("%d ", squared[i]);
    printf("\n");

    free(squared); // free allocated memory
    return 0;
}


/*
op → the name of the pointer.

(*op) → the * indicates it’s a pointer to a function.

(int*, int) → the function pointed to by op takes two parameters:

an int* (pointer to an array), and

an int (size of the array).

int at the beginning → the function returns an int.
*/
