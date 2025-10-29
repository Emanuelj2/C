#include <stdio.h>
#include <stdlib.h>

typedef struct
{
    int* data;
    size_t size;     // current number of elements
    size_t capacity; // total allocated space
} DynamicArray;

DynamicArray* da_create(size_t initial_capacity)
{
    DynamicArray *da = (DynamicArray*)malloc(sizeof(DynamicArray));
    if (da == NULL)
        return NULL;

    da->data = (int*)malloc(initial_capacity * sizeof(int));
    if (da->data == NULL)
    {
        free(da);
        return NULL;
    }

    da->size = 0;
    da->capacity = initial_capacity;
    return da;
}

void da_resize(DynamicArray *da)
{
    size_t new_capacity = da->capacity * 2; // double the previous capacity
    int* temp = (int*)realloc(da->data, new_capacity * sizeof(int));
    if (temp == NULL)
    {
        printf("resize allocation fail\n");
        return;
    }
    da->data = temp;
    da->capacity = new_capacity;
}

void da_push(DynamicArray *da, int value)
{
    if (da->size >= da->capacity)
        da_resize(da);

    da->data[da->size++] = value;
}

void da_pop_target(DynamicArray* da, size_t index)
{
    if (da->size == 0)
    {
        printf("Array is empty\n");
        return;
    }

    if (index >= da->size)
    {
        printf("Index out of bounds\n");
        return;
    }

    // Shift all elements left from target+1 onward
    for (size_t i = index; i < da->size - 1; i++)
        da->data[i] = da->data[i + 1];

    da->size--;
}

int da_find(DynamicArray *da, int target)
{
    for (int i = 0; i < da->size; i++)
    {
        if (da->data[i] == target)
            return i; // found -> return index
    }
    return -1; // not found
}

int da_get(DynamicArray *da, size_t index)
{
    if (index >= da->size)
    {
        printf("Index out of bounds\n");
        exit(1);
    }
    return da->data[index];
}

void da_destroy(DynamicArray *da)
{
    if (da != NULL)
    {
        free(da->data);
        free(da);
    }
}

int main()
{
    DynamicArray *arr = da_create(2);

    da_push(arr, 10);
    da_push(arr, 20);
    da_push(arr, 30); // triggers resize

    printf("Array after pushes: ");
    for (size_t i = 0; i < arr->size; i++)
        printf("%d ", da_get(arr, i));
    printf("\n");

    int idx = da_find(arr, 20);
    if (idx != -1)
        printf("Found 20 at index %d\n", idx);
    else
        printf("20 not found\n");

    da_pop_target(arr, 1); // remove the element at index 1 (value 20)
    printf("Array after pop: ");
    for (size_t i = 0; i < arr->size; i++)
        printf("%d ", da_get(arr, i));
    printf("\n");

    da_destroy(arr);
    return 0;
}
