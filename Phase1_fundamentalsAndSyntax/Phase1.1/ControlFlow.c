#include <stdio.h>
#include<stdlib.h>


int main(){

    int age = 20;

    if(age >= 18)
    {
        printf("Adult\n");
    }
    else if(age >= 13)
    {
        printf("Teenager\n");
    }
    else
    {
        printf("Child\n");
    }

    //while loop
    int i  = 0;
    while (i < 5)
    {
        printf("%d ", i);
        i++;
    }
    printf("\n");
    
    // do-while loop (executes at least once)
    int j = 0;
    do {
        printf("%d ", j);
        j++;
    } while (j < 5);

    printf("\n");

    // for loop
    for (int k = 0; k < 5; k++) {
        printf("%d ", k);
    }

    printf("\n");

    // break and continue
    for (int n = 0; n < 10; n++) {
        if (n == 3) continue;  // skip 3
        if (n == 7) break;     // stop at 7
        printf("%d ", n);      // prints: 0 1 2 4 5 6
    }
    return 0;
}