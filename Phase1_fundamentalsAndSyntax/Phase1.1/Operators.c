#include <stdio.h>
#include <stdlib.h>

// function prototype
void printDashes(int n);

int main() {
    int a = 10;
    int b = 3;

    int sum = a + b;
    int subtraction = a - b;
    int product = a * b;
    int quot = a / b;
    double quot2 = (double)a / b;
    int rem = a % b;

    printDashes(20);

    printf("Sum of a and b: %d\n", sum);
    printf("Subtraction of a and b: %d\n", subtraction);
    printf("Product of a and b: %d\n", product);
    printf("Quotient of a and b: %d\n", quot);
    printf("Quotient of a and b (decimal): %f\n", quot2);
    printf("Modulo of a and b: %d\n", rem);

    printDashes(20);
    //Increment/Decrement
    int x = 5;
    printf("x: %d\n", x);
    x++;    // post-increment: use then increment (x becomes 6)
    printf("x: %d\n", x);
    ++x;    // pre-increment: increment then use (x becomes 7)
    printf("x: %d\n", x);
    x--;    // post-decrement
    printf("x: %d\n", x);
    --x;    // pre-decrement
    printf("x: %d\n", x);

    printDashes(20);

    //Relational
    printf("1(true)     0(false)\n"); 
    printf("(a > b): %d\n", (a > b)); //true
    printf("(a < b): %d\n", (a < b)); //false
    printf("(a >= b): %d\n", (a >= b)); //true
    printf("(a <= b): %d\n", (a <= b)); //false
    printf("(a == b): %d\n", (a == b)); //false
    printf("(a != b): %d\n", (a != b)); //true

    
    return 0;
}

// function definition
void printDashes(int n) {
    for(int i = 0; i < n; i++) {
        putchar('-');
    }
    putchar('\n');
}