#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
    int size = 100;
    int *arr = (int*)malloc(size * sizeof(int));

    if(arr == NULL)
    {
        perror("malloc error");
        exit(1);
    }

    //initilaize the arr
    for(int i = 0; i < size; i++)
    {
        arr[i] = i * 10;
    }
    
    //use arr (get the val at index 50)
    printf("%d ", arr[50]);

    //free the array
    free(arr);
    arr = NULL;

    //allcocate 2D array
    int rows = 10;
    int cols = 20;
    int *matrix = (int*)malloc(rows * cols * sizeof(int)); //The array is stored contiguously in memory, just like a 1D array

    //access matrix[i * cols + j]

    free(matrix);

    //allocate 2d array (Non-contiguous (many blocks))
    int **matrix2= (int**)malloc(rows * sizeof(int));
    for (int i = 0; i < rows; i++)
    {
        matrix2[i] = (int*)malloc(cols * sizeof(int));
    }
    // Access: matrix2[i][j]


    for(int i = 0; i < rows; i++)
    {
        free(matrix2[i]);
    }
    free(matrix2);

    typedef struct
    {
        char name[50];
        int age;
    }Person;

    Person *p = (Person*)malloc(sizeof(Person));

    if(p == NULL)
    {
        perror("malloc fail");
        exit(1);
    }

    strcpy(p->name, "Jhon");
    p->age = 30;
    free(p);

    return 0;
}