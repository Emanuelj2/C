#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

static const char *positive_words[] = {};
static const char *negative_words[] = {};
static const char *nutral_word[] = {};
static const char *stop_words[] = {};

//count of the words in the dictinarys 
const int positive_count = sizeof(positive_words) / sizeof(positive_words[0]);


//convert string to lowecase
void to_lower(char *str)
{
    for(int i = 0; str[i]; i++)
    {
        str[i] = tolower(str[i]);
    }
}

//function to remove punctualtion
void remove_punctuation(char *word)
{
    int len = strlen(word);
    while(len > 0 && ispunct(word[len -1]))
    {
        word[len - 1] = '\0';
        len--;
    }
}

//check if word is positive word is in the dictionary
int is_positive(const char *word)
{
    for (int i = 0; i < positive_count; i++)
    {
        if(strcmp(word, positive_words[i]) == 0)
        {
            return 1;
        }
    }
    return 0;
}

//check if negative word is in the dictionary

//check if nutral word is in the dictionary

//check if stop word is in the dictionary


int main()
{
    return 0;
}