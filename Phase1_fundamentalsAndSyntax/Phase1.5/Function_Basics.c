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

int main()
{
    int res = add(2, 4);
    printf("%d\n", res);

    int res2 = subtract(2, 4);
    printf("%d\n", res2);
    return 0;
}