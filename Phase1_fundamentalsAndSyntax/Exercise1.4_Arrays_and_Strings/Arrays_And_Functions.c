#include <stdio.h>
#include <stdlib.h>
int find_max(int arr[], int size);
int find_max_optimized(int arr[], int size);
int count_evens(int arr[], int size);

int main()
{
    int arr[] = {1, 2, 3, 6, 8, 2, 1};
    int size = 7;

    int max_val_res = find_max(arr, size);
    printf("The maz value in the array is: %d\n", max_val_res);
    int max_val_res2 = find_max_optimized(arr, size);
    printf("The max value in the array is: %d\n", max_val_res2);
    int even_count_res = count_evens(arr, size);
    printf("NUmber of even numbers in the arr: %d", even_count_res);

    return 0;
}

//O(n) time complexity
int find_max(int arr[], int size)
{
    int max = arr[0];
    for(int i = 0; i < size; i++){
        if(arr[i] > max)
        {
            max = arr[i];
        }
    }
    return max;
}

int find_max_optimized(int arr[], int size)
{
    int max = arr[0];
    int left = 0;
    int right = size - 1;

    while(left <= right)
    {
        if(arr[left] > max)
            max = arr[left];
        if(arr[right] > max)
            max = arr[right];

        left++;
        right--;
    }
    return max;
}

int count_evens(int arr[], int size)
{
    int num_of_evens = 0;

    for(int i = 0; i < size; i++)
    {
        if(arr[i] % 2 == 0)
        {
            num_of_evens++;
        }
    }

    return num_of_evens;
}