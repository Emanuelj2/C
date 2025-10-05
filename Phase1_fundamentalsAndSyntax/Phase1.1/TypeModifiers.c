#include <stdio.h>
#include <stdlib.h>

int main()
{
    signed int si = -100; // Can be negative (default for int)
    unsigned int ui = 100; // Only positive values
    const int MAX = 100; // Cannot be modified
    char c = 'A'; //single character
    volatile int sensor_val;  // Value may change unexpectedly (hardware)

    //unlike C++ or C# that have a string data type built in, c uses an array of chars
    char name[] = "Bob";


    printf("signed int: %d\n", si); //when printing a signed int use %d or %i
    printf("unsigned int: %u\n", ui); //when printing an unsigned int use %u
    printf("constant MAX: %d\n", MAX);
    printf("char: %c\n", c); //when printing a char use %c
    printf("ASCII for car 'A': %d\n", c); //NOTE: if you use %d on a char you will get the ASCII number
    printf("string: %s\n", name); //when printing out a string use %s
    printf("indexing on strings: %c", name[0]); //NOTE: string start at zero
    
    return 0;
}