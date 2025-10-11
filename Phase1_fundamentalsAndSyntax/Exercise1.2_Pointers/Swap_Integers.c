#include <stdlib.h>
#include <stdio.h>

void Swap(int *a, int *b)
{
    int temp = *a; //store the val pointed by a
    *a = *b;        //assign val pointed by b to a 
    *b = temp;      //assign the stored val to b
}

int main()
{
    int x = 5;
    int y = 10;

    printf("Before swap: x = %d, y = %d\n", x, y);

    Swap(&x, &y); //pass the addresses of x and y

    printf("After swap:  x = %d, y = %d\n", x, y);
    return 0;
}