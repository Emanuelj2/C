#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// function declarations
int strlen_manual(const char *str);
char* strcpy_manual(char *dest, const char *src);
char* concatstr_manual(const char* str1, const char* str2);
bool ispalindrome(const char *str);
char* reversestring_manual(const char* str);
int wordcount_manual(const char* str);


int main()
{   
    char string[] = "Emanuel";

    int length_of_string = strlen_manual(string);
    printf("The word %s is %d letters long\n", string, length_of_string);

    char source[] = "APPLE";
    char destination[10];

    char* copy_str = strcpy_manual(destination, source);

    printf("destination: %s, source: %s, copy_str: %s\n", destination, source, copy_str);

    char * result = concatstr_manual("Hello ", "world");
    printf("%s\n", result);
    free(result);

    // TEST THE IS PALINDROME FUNCTION
    const char *test_strings[] = {
        "racecar",
        "hello",
        "madam",
        "abcba",
        "abba",
        "apple",
        "a",       // single char = palindrome
        ""         // empty string = palindrome
    };

    int num_tests = sizeof(test_strings) / sizeof(test_strings[0]);

    for (int i = 0; i < num_tests; i++)
    {
        if (ispalindrome(test_strings[i]))
        {
            printf("\"%s\" is a palindrome ✅\n", test_strings[i]);
        }
        else
        {
            printf("\"%s\" is NOT a palindrome ❌\n", test_strings[i]);
        }
    }

    char* rev = reversestring_manual("Emanuel");
    printf("%s\n", rev);
    free(rev);

    //word count function test
    const char* sentence = "C programming is fun";
    int count = wordcount_manual(sentence);

    printf("Sentence: \"%s\"\n", sentence);
    printf("Word count: %d\n", count);

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

//conactinate two strings
char* concatstr_manual(const char* str1, const char* str2)
{
    int len1 = strlen_manual(str1);
    int len2 = strlen_manual(str2);

    //allocate memoey
    char *res = malloc((len1 * len2 + 1) * sizeof(char));
    if(res == NULL)
    {
        return NULL;
    }

    //copy the first string
    int i = 0;
    // copy str1
    while (str1[i] != '\0')
    {
        res[i] = str1[i];
        i++;
    }

    int j = 0;
    // copy str2
    while (str2[j] != '\0')
    {
        res[i + j] = str2[j];
        j++;
    }

    // null terminator
    res[i + j] = '\0';

    return res;
}

//is palindrome function
bool ispalindrome(const char *str)
{
    int l = 0;
    int r = strlen_manual(str) -1;

    while(l < r)
    {
        if(str[l] != str[r])
        {
            return false;
        }
        l++;
        r--;
    }
    return true;
}

//reverse a string
char* reversestring_manual(const char* str)
{
    //allocate momory for the new string
    int n = strlen_manual(str);
    char *result = malloc((n + 1) * sizeof(char));
    int start = 0;

    for(int i = n-1; i >= 0; i--)
    {
        result[start] = str[i]; 
        start++;
    }

    //add null trminator
    result[start] = '\0';

    return result;
}

//count words in a sentece
int wordcount_manual(const char* str)
{
    //find the length of the string
    int n = strlen_manual(str);
    int word_count = 0;

    if(n == 0) return 0;

    for(int i = 0; i < n; i++)
    {
        if(str[i] != ' ' && (i == 0 || str[i - 1] == ' '))
        {
            word_count++;
        }
    }

    return word_count;
}



