#include <stdlib.h>
#include <stdio.h>

void print_array(int arr[], int size)
{
    for(int i = 0; i < size; i++)
    {
        printf("%d", arr[i]);
    }
    printf("\n");
}

void print_array2(int *arr, int size)
{
    for(int i = 0; i < size; i++){
        printf("%d", arr[i]);
    }
    printf("\n");
}

//NOTE: Equivalent notation for the array functions


//2D array (matrix)
void print_matrix(int rows, int cols, int matrix[rows][cols])
{
    for(int i = 0; i < rows; i++)
    {
        for(int j = 0; j < cols; j++)
        {
            printf("%d", matrix[i][j]);
        }
        printf("\n");
    }
}
int main()
{
    int arr[] = {1, 2, 3, 4, 5};
    print_array2(arr, 5);

    printf("\n");
    printf("print matrix");
    int matrix[3][3] = {{1,2,3}, {4,5,6}, {7,8,9}};
    print_matrix(3, 3, matrix);

    return 0;
}