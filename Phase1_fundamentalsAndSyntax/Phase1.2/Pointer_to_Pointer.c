#include <stdio.h>
#include <stdlib.h>

// Common use case: modifying a pointer in a function
void allocate_memory(int **ptr)
{
    *ptr = (int*)malloc(sizeof(int));
    **ptr = 42;
}


int main(){
    int value = 100;
    int *valptr1 = &value;       //pointer to int
    int **valptr2 = &valptr1;   //pointer to pointer to int

    printf("value: %d\n", value);      //value 
    printf("address of value: %d\n", valptr1);    //address of value
    printf("value of the address: %d\n", *valptr1);     //value of the address
    printf("addres of the pointer of the value %d\n", valptr2); 
    printf("value of the pointer of the value: %d\n", **valptr2);   //addres of the pointer of the value

    int *p = NULL;
    allocate_memory(&p);
    printf("%d\n", *p);
    free(p);


    return 0;
}