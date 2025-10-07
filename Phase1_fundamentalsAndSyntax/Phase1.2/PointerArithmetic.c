#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    int arr[] = {10, 20, 30, 40, 50};
    int *ptr = arr; //points to the first element in the array
    /*
    Note:
        int *ptr = &arr //this gets the addresss of the entire array
    */

    printf("%d\n", *ptr);       //points to the value 10
    printf("%d\n", ptr);        //points to the address of 10

    //get the second element in the array
    printf("%d\n", *(ptr + 1)); //this will get 20
    printf("%d\n", (ptr + 1));  //this will get address of 20
    printf("%d\n", *(ptr + 3));  //this will get 40

    ptr++; //move to the next element
    printf("%d\n", *ptr);       //*ptr will now be 20

    ptr--; //move back
    printf("%d\n", *ptr);       //*ptr will now be 10 again

    //pointer subtraction
    int *p1 = &arr[4];          //this is value 50
    int *p2 = &arr[0];          //this is value 10

    //subtraction
    int subtraction = *p1 - *p2;
    printf("subtratction of %d %d is %d\n", *p1, *p2, subtraction);

    int addition = *p1 + *p2;
    printf("Addition of %d %d is %d\n", *p1, *p2, addition);

    ptrdiff_t diff = p1 - p2; //this number of ellements between p1 and p2
    printf("number of elements in between p1 and p2: %d\n", diff);


    return 0;
}