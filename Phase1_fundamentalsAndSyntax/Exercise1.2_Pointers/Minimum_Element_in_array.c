#include <stdio.h>
#include <stdlib.h>

int Max_Num(int arr[], int n)
{
    
    int *ptr = arr; //points to the first element in thee arr
    int max = *ptr; //initialize max to first element

    for(int i = 1; i < n; i++) //start from the second element
    {
        ptr++;
        if(*ptr > max)
        {
            max = *ptr;
        }
    }

    return max;
}

int main()
{
    int arr[] = {10, 20, 60, 400, 50};
    int n = sizeof(arr)/ sizeof(arr[0]); // get the size of the array

    int result = Max_Num(arr, n);

    printf("Maximum number: %d\n", result);
    return 0;
}