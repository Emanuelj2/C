#include <stdio.h>
#include <stdlib.h>

#define ARRAYSIZE 10
int find_targrt(int arr[], int target);

int main()
{
    int arr[ARRAYSIZE] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 0};
    int target = 10;

    int arr_result = find_targrt(arr, target);

    if(arr_result == -1)
    {
        printf("target not found");
    }
    else{
        printf("the target is found at index: %d", arr_result);
    }

    return 0;
}

int find_targrt(int arr[], int target)
{
    for(int i = 0; i < ARRAYSIZE; i++)
    {
        if(arr[i] == target)
        {
            return i;
        }
    }
    return -1;
}