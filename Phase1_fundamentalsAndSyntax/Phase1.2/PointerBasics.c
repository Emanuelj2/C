#include <stdio.h>
#include <stdlib.h>


int main()
{
    int x = 20;
    int *ptr = &x; //ptr stores the address of x

    printf("The value of x is %d\n", x);
    printf("The value of x is %d\n", *ptr);
    printf("The addres of x is %d\n", ptr);
    printf("The address of x is %d\n", &x);
    printf("The address of x is %d\n", (void*)&x);


    return 0;
}