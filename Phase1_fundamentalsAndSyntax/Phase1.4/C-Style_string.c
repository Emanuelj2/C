#include <stdio.h>
#include <stdlib.h>


int strcomp_manual(const char *s1, const char *s2);
int num_of_common_chars(const char* str1, const char* str2);
int num_of_common_chars_unordered(const char* str1, const char* str2);
void strcat_manual( char* dest, const char* src);




int main()
{

    char str1[] = "Hello"; //{'H'. 'e', 'l', 'l', 'o'} (this is an array of chars)
    char str2[10] = "Hello"; //the rest will be filled with '\0'
    char *str3 = "World";    // String literal (read-only memory)

    printf("str1:" );
    for(int i = 0; i < sizeof(str1); i++)
    {
        printf("%c ", str1[i]);
    }
    printf("\n");


    printf("str2: ");
    for(int i = 0; i < 10; i++)
    {
        printf("%c ", str2[i]);
    }
    printf("\n");
    
    //find the length of string 1
    int length = 0;
    while(str1[length] != '\0')
    {
        length++;
    }
    printf("length of string1: %d", length);

    printf("\n");

    //string comparison
    char string1[] = "helloqwertsyuiop ";
    char string2[] = "hellfdfsddo";

    int res = strcomp_manual(string1, string2);
    int res2 = num_of_common_chars(string1, string2);
    int res3 = num_of_common_chars_unordered(string1, string2);
    printf("num_of_common_chars %d\n", res2);
    printf("num_of_common_chars_unordered %d\n", res3);
    strcat_manual( string1, string2);
    printf("%s\n", string1);


    printf("\n");
    
    return 0;
}

int strcomp_manual(const char *s1, const char *s2)
{
    while(*s1 && (*s1 == *s2))
    {
        s1++;
        s2++;
    }
    return *(unsigned char*)s1 - *(unsigned char*)s2;
}

int num_of_common_chars(const char* str1, const char* str2)
{
    int common_char_count = 0;
    while(*str1 && *str2 && (*str1 == *str2))
    {
        common_char_count++;
        str1++;
        str2++;
    }
    return common_char_count;
}

int num_of_common_chars_unordered(const char* str1, const char* str2) 
{
    int freq1[256] = {0};
    int freq2[256] = {0};
    int common_count = 0;

    //frequency of str1
    while(*str1)
    {
        freq1[(unsigned char)*str1]++;
        str1++;
    }
    //frequency of str2
    while(*str2 )
    {
        freq2[(unsigned char)*str2]++;
        str2++;
    }

    for(int i = 0; i < 256; i++)
    {
        if(freq1[i] > 0 && freq2[i] > 0)
        {
            common_count += (freq1[i] < freq2[i]) ? freq1[i] : freq2[i];
        }
    }
    return common_count;

}


//string concatenation
void strcat_manual( char* dest, const char* src)
{
    while(*dest) //move to the end of dest
    {
        dest++;
    }

    //copy src to dest
    while(*src != '\0')
    {
        *dest = *src;
        dest++;
        src++; 
    }
    *dest = '\0';
}