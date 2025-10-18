#include <stdlib.h>
#include <stdio.h>


int add(int a, int b)
{
    return a + b;
}

int subtract(int a, int b)
{
    return a - b;
}

//void not retrun value
void print_message(const char *msg)
{
    printf("%s\n", msg);
}
int main()
{
    int res = add(2, 4);
    printf("%d\n", res);

    int res2 = subtract(2, 4);
    printf("%d\n", res2);
    print_message("Hello");
    return 0;
}