#include <stdio.h>
#include <stdlib.h>
void print_array(int arr[], int size);
int find_max(int arr[], int size);
int find_max_optimized(int arr[], int size);
int count_evens(int arr[], int size);
int* reverse_array(int *arr, int size);
int binary_search(int arr[], int size, int target);
void bubble_sort(int arr[], int size);
int* ryans_function(int *arr, int size, int target);
int is_sorted(int arr[], int size);

int main()
{
    int arr[] = {1, 2, 3, 6, 8, 2, 1};
    int size = 7;

    int max_val_res = find_max(arr, size);
    printf("The maz value in the array is: %d\n", max_val_res);
    int max_val_res2 = find_max_optimized(arr, size);
    printf("The max value in the array is: %d\n", max_val_res2);
    int even_count_res = count_evens(arr, size);
    printf("Number of even numbers in the arr: %d\n", even_count_res);
    int *reverse_array_res = reverse_array(arr, size);
    printf("reveres array: ");
    print_array(reverse_array_res, size);
    free(reverse_array_res);
    bubble_sort(arr, size);
    printf("Sorted array (bubble sort): ");
    print_array(arr, size);
    int target = 6;
    int binary_search_res = binary_search(arr, size, target);
    printf("binary search for number %d fount at index : %d\n", target, binary_search_res);
    int* ryans_function_res = ryans_function(arr, size, target);
    printf("Ryans function: ");
    print_array(ryans_function_res, size - 1);
    free(ryans_function_res);
    
    int arr2[] = {1, 4, 6, 2, 8, 4, 6};
    int is_sorted_res = is_sorted(arr2, size);
    printf("is array sorted (1 = true, 0 = false): %d\n", is_sorted_res);
    
    return 0;
}
void print_array(int arr[], int size)
{
    for(int i = 0; i < size; i++)
    {
        printf("%d ", arr[i]);
    }
    printf("\n");
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

int* reverse_array(int *arr, int size)
{
    //allocate memory for the new array
    int* res = (int*)malloc(size * sizeof(int));

    //check if malloc succeeded
    if(res == NULL)
    {
        return NULL;
    }

    int left = 0;
    int right = size - 1;

    while(left < size)
    {
        res[left] = arr[right];
        left++;
        right--;

    }

    return res;
}

int binary_search(int arr[], int size, int target)
{
    //binary search
    //note the array is already sorted
    int low = 0;
    int high = size - 1;

    while(low <= high)
    {
        int middle = low + (high - low)/2;

        if(arr[middle] == target)
        {
            return middle;
        }

        if(arr[middle] > target)
        {
            high = middle - 1;
        }
        else
        {
            low = middle + 1;
        }
    }
    return - 1;
}

void bubble_sort(int arr[], int size)
{
    for(int i = 0; i < size - 1; i++)
    {
        for(int j = 0; j < size - i - 1; j++)
        {
            if(arr[j] > arr[j + 1])
            {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}


int* ryans_function(int *arr, int size, int target)
{
    int *res = malloc((size - 1) * sizeof(int));
    if(res == NULL)
    {
        return NULL;
    }

    int res_index = 0;
    for(int i = 0; i < size; i++)
    {
        if(arr[i] == target)
        {
            continue; //skip the number
        }
        res[res_index++] = arr[i];
        
    }
    return res;
}

int is_sorted(int arr[], int size)
{
    for(int i = 1; i < size; i++)
    {
        //skips the duplicates
        if(arr[i] == arr[i - 1])
        {
            continue;
        }
        if(arr[i] < arr[i - 1])
        {
            return 0;
        }

    }
    return 1;
}