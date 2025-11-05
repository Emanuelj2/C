#include <stdlib.h>
#include <stdio.h>
// ============================================
// PROBLEM 1: TWO SUM (Easy)
// Given an array and a target, find two numbers that add up to target
// Return indices of the two numbers
// ============================================

//manual hash map
typedef struct
{
    int key;
    int value;
}HashMap;


int* two_sum(int* nums, int numSize, int target, int* returnSize)
{
    HashMap* hash_table = malloc(sizeof(HashMap) * numSize);
    int* result = malloc(sizeof(int) * 2); //multiply by two because we are returning two vals
    *returnSize = 2;

    for(int i = 0; i < numSize; i++)
    {
        int compliment = target - nums[i];
        for(int j = 0; j < i; j++)
        {
            if(hash_table[j].key == compliment)
            {
                result[0] = hash_table[j].value;
                result[1] = i;
                free(hash_table);
                return result;
            }
        }
        hash_table[i].key = nums[i];
        hash_table[i].value = i;
    }
    free(hash_table);
    *returnSize = 0;
    return NULL;

}

int main()
{
    int nums[] = {2, 7, 11, 15};
    int target = 9;
    int returnSize;
    int* result = two_sum(nums, 4, target, &returnSize);

    if (result != NULL) {
        printf("Indices: %d, %d\n", result[0], result[1]);
        free(result);
    } else {
        printf("No solution found.\n");
    }

    return 0;

}