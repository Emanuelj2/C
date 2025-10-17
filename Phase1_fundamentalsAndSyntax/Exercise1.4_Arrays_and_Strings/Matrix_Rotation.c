#include <stdlib.h>
#include <stdio.h>

#define N 3 //size of the square matrix

void rotate90_clockwise(int arr[N][N], int res[N][N])
{
    for(int row = 0; row < N; row++)
    {
        for(int col = 0; col < N; col++)
        {
            res[col][N - 1 - row] = arr[row][col];
        }
    }
}

void printMatrix(int arr[N][N])
{
    for(int i = 0; i < N; i++)
    {
        for(int j = 0; j < N; j++)
        {
            printf("%d", arr[i][j]);
        }
        printf("\n");
    }
}


int main()
{
    int arr[N][N] = {
        {1, 2, 3},
        {4, 5, 6},
        {7, 8, 9}
    };

    int rotated[N][N];

    printf("Original matrix:\n");
    printMatrix(arr);

    rotate90_clockwise(arr, rotated);

    printf("\nRotated 90 degrees clockwise:\n");
    printMatrix(rotated);
    return 0;
}