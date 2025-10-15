#include <stdio.h>
#include <stdlib.h>

// function declarations
int strlen_manual(const char *str);
char* strcpy_manual(char *dest, const char *src);

int main()
{   
    char string[] = "Emanuel";

    int length_of_string = strlen_manual(string);
    printf("The word %s is %d letters long\n", string, length_of_string);

    char source[] = "APPLE";
    char destination[10];

    char* copy_str = strcpy_manual(destination, source);

    printf("destination: %s, source: %s, copy_str: %s\n", destination, source, copy_str);

    return 0;
}

// return the number of characters in a given string
int strlen_manual(const char *str)
{
    int count = 0;
    while (*str)
    {
        count++;
        str++;
    }
    return count;
}

// copy a string
char* strcpy_manual(char *dest, const char *src)
{
    char *original_dest = dest; // keep pointer to start of dest

    while (*src != '\0')
    {
        *dest = *src;
        dest++;
        src++;
    }

    *dest = '\0'; // add null terminator
    return original_dest;
}
