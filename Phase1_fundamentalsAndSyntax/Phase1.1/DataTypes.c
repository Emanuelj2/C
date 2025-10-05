#include <stdio.h>
#include <stdlib.h>

int main() {

    printf("size of a char: %zu bytes\n", sizeof(char)); //has a byte size of 1
    printf("size of an int: %zu bytes\n", sizeof(int)); //has a byte size of 4
    printf("size of a float: %zu bytes\n", sizeof(float)); //has a byte size of 4
    printf("size of a double: %zu bytes\n", sizeof(double)); //has a byte size of 8
    printf("size of a long %zu bytes\n", sizeof(long)); //has a byte size of 8
    printf("size of a long long %zu bytes\n", sizeof(long long)); //has a byte size of 8
    printf("size of a short %zu bytes\n", sizeof(short)); //has a byte size of 2
    
    return 0;
}