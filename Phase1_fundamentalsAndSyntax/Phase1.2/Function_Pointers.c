#include <stdio.h>
#include <stdlib.h>


int
add( int a, int b)
{
    return a + b;
}

int
sub(int a, int b)
{
    return a - b;
}

//function pointer dlecloration
int (*operation) (int, int);


int main()
{

    operation = add;
    printf("%d\n", operation(5, 3));

    operation = sub;
    printf("%d\n", operation(5, 3));

    
    return 0;
}