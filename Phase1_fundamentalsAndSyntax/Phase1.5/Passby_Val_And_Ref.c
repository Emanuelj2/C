#include <stdio.h>
#include <stdlib.h>


//pass by value
void pass_by_val(int x)
{
    x = 100;
    printf("Inside function: %d\n", x);
}

void pass_by_ref(int *x)
{
    *x = 100;
    printf("Inside function: %d\n", *x);
}

//pass by val swaping
void swap(int *x, int *y)
{
    int temp = *x;
    *x = *y;
    *y = temp;
}

int main()
{
    int num = 10;
    printf("---pass by val---\n");
    pass_by_val(num);
    printf("Outside function: %d\n", num);

    printf("---pass by ref---\n");
    pass_by_ref(&num);
    printf("Outside function: %d\n", num); 

    printf("---swap---\n");
    int x = 5, y = 10;
    printf("Before: x=%d y=%d\n", x, y);
    swap(&x, &y);
    printf("After: x=%d, y=%d\n", x, y); 

    return 0;
}