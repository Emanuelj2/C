#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXCHARS 100

void options()
{
    printf("\n=== MAIN MENU ===\n");
    printf("1. Tokenize string\n");
    printf("2. Math operations\n");
    printf("3. Quit\n");
}

void math_menu()
{
    printf("\n--- Math Menu ---\n");
    printf("a. Add\n");
    printf("b. Subtract\n");
    printf("c. Multiply\n");
    printf("d. Divide\n");
    printf("e. Back to main menu\n");
}

void tokenize_string()
{
    char buffer[MAXCHARS];

    printf("Enter a string to tokenize: ");
    if (fgets(buffer, sizeof(buffer), stdin) == NULL)
        return;

    buffer[strcspn(buffer, "\n")] = '\0';  // strip newline

    printf("Tokens:\n");
    char *token = strtok(buffer, " ");
    while (token != NULL)
    {
        printf(" - %s\n", token);
        token = strtok(NULL, " ");
    }
}

void math_operations()
{
    char choice[10];
    double a, b;

    while (1)
    {
        math_menu();
        printf(">> ");
        if (!fgets(choice, sizeof(choice), stdin))
            return;

        switch (choice[0])
        {
        case 'a':
            printf("Enter two numbers: ");
            if (scanf("%lf %lf", &a, &b) == 2)
                printf("Result: %.2f\n", a + b);
            break;

        case 'b':
            printf("Enter two numbers: ");
            if (scanf("%lf %lf", &a, &b) == 2)
                printf("Result: %.2f\n", a - b);
            break;

        case 'c':
            printf("Enter two numbers: ");
            if (scanf("%lf %lf", &a, &b) == 2)
                printf("Result: %.2f\n", a * b);
            break;

        case 'd':
            printf("Enter two numbers: ");
            if (scanf("%lf %lf", &a, &b) == 2)
            {
                if (b != 0)
                    printf("Result: %.2f\n", a / b);
                else
                    printf("Error: division by zero\n");
            }
            break;

        case 'e':
            while (getchar() != '\n'); // clear leftover input
            return;

        default:
            printf("Invalid option\n");
        }

        while (getchar() != '\n'); // clear input buffer
    }
}

int main()
{
    char input[MAXCHARS];
    int running = 1;

    while (running)
    {
        options();
        printf(">> ");

        if (!fgets(input, sizeof(input), stdin))
            break;

        switch (input[0])
        {
        case '1':
            tokenize_string();
            break;

        case '2':
            math_operations();
            break;

        case '3':
            running = 0;
            break;

        default:
            printf("Invalid selection\n");
        }
    }

    printf("Program terminated.\n");
    return 0;
}