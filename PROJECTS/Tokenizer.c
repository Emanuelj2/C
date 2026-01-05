#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//argc: contains the count
//argv: contains the vector of strings
int main(int argc, char **argv)
{
    if(argc < 2)
    {
        printf("There is no input");
        return 1;
    }

    int token_count = 0;

    for(int i = 1; i < argc; i++)
    {
        printf("Token: %s\n", argv[i]);
        token_count++;
    }

    printf("# of tokens: %d", token_count);
    return 0;

}