#include <stdio.h>

int main()
{
    signed int temp = -50; //Can be negative

    printf("This is the degree in F: %d\n", temp);

    double celsius  = (temp - 32) * (5.0/9.0); 

    printf("This is the degree in C: %.2f\n", celsius );

    //back to Fahrenheit 

    double fahrenheit =  (celsius * (9.0/5.0)) + 32;

    printf("This is the degree back to fahrenheit from celsius: %2.0f", fahrenheit);

    return 0;
}