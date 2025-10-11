/*
Create a function that returns a dynamically
 allocated string (the caller must free it).
 Demonstrate proper memory management.
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* create_greeting(const char* name)
{
    //find the size of the length of th string
    int size_of_name = strlen(name) + strlen("Hello, ") + 1;

    //allocate the memory
    char* greeting = (char*)malloc(size_of_name * sizeof(char));
    if(greeting == NULL)
    {
        printf("Memory allocation fail");
    }

    strcpy(greeting, "Hello, ");
    strcat(greeting, name);

    return greeting;
}

int main()
{
    char name[50];

    printf("Enter your name: ");
    scanf("%49s", name);

    char* greeting = create_greeting(name);

    if(greeting != NULL){
        printf("%s\n", greeting);

        free(greeting);
    }
    return 0;
}