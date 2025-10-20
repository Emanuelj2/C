#include <stdlib.h>
#include <stdio.h>

struct Point
{
    int x;
    int y;
};


int main()
{
    //create and use struct
    struct Point p1;
    p1.x = 10;
    p1.y = 20;

    //initialize struct
    struct Point p2 = {30, 40};
    printf("p1: (%d, %d)\n", p1.x, p1.y);
    struct Point p3 = { .y = 10, .x = 60};

    //struct pointer
    struct Point *ptr = &p1;
    ptr->x = 100; //arrow opperator
    (*ptr).y = 100; //same as the arrow operator

    printf("p1: (%d, %d)\n", p1.x, p1.y);
    
    return 0;
}