#include <stdio.h>

//prototype
void printBits(unsigned int num); //VOID PRINTS
unsigned int reverseBits(unsigned int num); //RETRUNS A VALUE

int main()
{
    unsigned int num = 5; // binary: 00000000 00000000 00000000 00000101

    printf("Original:      ");
    printBits(num);

    unsigned int reversed = reverseBits(num);
    printf("Reversed bits: ");
    printBits(reversed);

    printf("Reversed value: %u\n", reversed);
    return 0;
}

void printBits(unsigned int num)
{
    for(int i = 31; i >= 0; i--)
    {
        printf("%d", (num >> i) & 1);
        if(i % 8 == 0){
            printf(" "); // add a space every 8 bits
        }
    }
    printf("\n");
}

unsigned int reverseBits(unsigned int num)
{
    unsigned int res = 0;

    int bits = 32; //assuming 32-bit

    for(int i = 0 ; i < bits; i++)
    {
        // Shift result to the left to make room for next bit
        res << 1;

        // Get the last bit of num and add it to result
        res |= (num & 1);

        // Shift num to the right to process the next bit
        num >>= 1;
    }
    return res;

}