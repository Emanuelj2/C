#include <stdio.h>
#include <stdbool.h> // for using bool, true, false
//Create a program that checks if a number is prime.
int main()
{
    unsigned int num; //only positive numbers
    printf("Enter a number: ");
    //&num gives scanf() the memory address of the variable num so it can store the input there.
    //%u tells scanf() and printf() to treat the value as unsigned.
    scanf("%u", &num);

    //base case numbers less than 2 are not prime 
    if(num < 2)
    {
        printf("Number %u is not prime.");
    }
    
    bool isPrime = true;

    //check divisibility from 2 to  sqrt(num)
    for(unsigned int i = 2; i * i <= num; i++){
        if(num % i == 0){
            isPrime = false;
            break;
        }
    }
    
    if (isPrime)
        printf("%u is a prime number.\n", num);
    else
        printf("%u is not a prime number.\n", num);

    return 0;
}