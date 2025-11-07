#include <stdio.h>
#include <stdlib.h>

//Given an array nums containing n distinct numbers in the range [0, n], return the one number that is missing from the array.


int missing_number(int *nums, int num_size)
{
    for(int i = 0;i < num_size; i++)
    {
        if(nums[i] != i)
        {
            return i;
        }
    }
    return num_size; // if all match
}

int main()
{
    int arr[] = {0, 1, 2, 3, 4, 5, 7, 8, 9};
    int num_size = 8;
    int missing = missing_number(arr, num_size);
    printf("the missing number in the array is %d",missing);

    return 0;
}