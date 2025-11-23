#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_TEXT_LENGTH 1000
#define MAX_WORD_LENGTH 50
#define MAX_WORDS 200

static const char *positive_words[] = {};
static const char *negative_words[] = {};
static const char *nutral_word[] = {};
static const char *stop_words[] = {};

//count of the words in the dictinarys 
const int positive_count = sizeof(positive_words) / sizeof(positive_words[0]);
const int negative_count = sizeof(negative_words) / sizeof(negative_words[0]);
const int nutral_count = sizeof(nutral_word) / sizeof(nutral_word[0]);
const int stop_word_count = sizeof(stop_words) / sizeof(stop_words[0]);


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
/*
NOTES:
- strcmp means string compare
- int strcmp(const char *str1, const char *str2);
    - 0 → if both strings are equal.
    - Negative value → if str1 is lexicographically less than str2.
    - Positive value → if str1 is lexicographically greater than str2.
- strcmp() is case-sensitive: "Hello" and "hello" are considered different
*/

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
int is_negative(const char *word)
{
    for(int i = 0; i < negative_count; i++)
    {
        if(strcmp(word, negative_words[i]) == 0)
        {
            return 1;
        }
    }
    return 0;
}

//check if nutral word is in the dictionary
int is_nutral(const char *word)
{
    for(int i = 0 ; i < nutral_count; i++)
    {
        if(strmcp(word, negative_words[i]) == 0)
        {
            return 1;
        }
    }
    return 0;
}

//check if stop word is in the dictionary
int is_stop_word(const char *word)
{
    for(int i = 0; i < stop_word_count; i++)
    {
        if(strcmp(word, stop_words[i]) == 0)
        {
            return 1;
        }
    }
    return 0;
}

//create the structuer for the sentiment score
typedef struct
{
    int positive_score;
    int negative_score;
    int nutral_score;
    float sentiment_ratio;
    char sentiment;
}SentimentResult;


SentimentResult analyze_sentiment(const char* text)
{
    SentimentResult result = {0, 0, 0, 0.0, ""};
    char text_copy[MAX_TEXT_LENGTH];
    char word[MAX_WORD_LENGTH];

    //preprocessing
    // -copy the text
    // -remove the stop_words 
    strncpy(text_copy, text, MAX_TEXT_LENGTH - 1);
    text_copy[MAX_TEXT_LENGTH - 1] = '\0';
    to_lower(text_copy);

    //tokenize the text
    char *token = strtok(text_copy, " \t\n\r.,;!?\"'");

    //analyze each word
    while(token)
    {
        strcpy(word, token);
        remove_punctuation(word);
    }


}


int main()
{
    return 0;
}