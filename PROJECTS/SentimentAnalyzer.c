#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_TEXT_LENGTH 1000
#define MAX_WORD_LENGTH 50
#define MAX_WORDS 200

static const char *positive_words[] = {
    "good", "great", "excellent", "amazing", "wonderful", "fantastic",
    "love", "happy", "joy", "beautiful", "best", "perfect", "awesome",
    "brilliant", "outstanding", "superb", "delightful", "pleasant",
    "positive", "nice", "enjoyed", "recommend", "satisfied", "impressive"
};
static const char *negative_words[] = {
    "bad", "terrible", "awful", "horrible", "worst", "hate", "poor",
    "disappointing", "sad", "angry", "negative", "disgusting", "annoying",
    "useless", "waste", "boring", "dull", "mediocre", "inferior", "pathetic",
    "unpleasant", "frustrating", "disappointing", "regret"
};

static const char *stop_words[] = {
    "the", "a", "an", "and", "or", "but", "in", "on", "at", "to", "for",
    "of", "with", "by", "from", "as", "is", "was", "are", "were", "been",
    "be", "have", "has", "had", "do", "does", "did", "will", "would",
    "could", "should", "may", "might", "must", "can", "this", "that",
    "these", "those", "i", "you", "he", "she", "it", "we", "they"
};

//count of the words in the dictionary
const int positive_count = sizeof(positive_words) / sizeof(positive_words[0]);
const int negative_count = sizeof(negative_words) / sizeof(negative_words[0]);
const int stop_word_count = sizeof(stop_words) / sizeof(stop_words[0]);


//convert string to lower case
void to_lower(char *str)
{
    for(int i = 0; str[i]; i++)
    {
        str[i] = tolower(str[i]);
    }
}

//function to remove punctuation
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

//create the struct for the sentiment score
typedef struct {
    int positive_score;
    int negative_score;
    int neutral_score;
    int total_words;
    int stop_words_removed;
    float sentiment_ratio;
    char sentiment[20]; 
} SentimentResult;


SentimentResult analyze_sentiment(const char* text)
{
    SentimentResult result = {0, 0, 0, 0, 0, 0.0, ""};
    char text_copy[MAX_TEXT_LENGTH];
    char word[MAX_WORD_LENGTH];

    //preprocessing
    // -copy the text
    strncpy(text_copy, text, MAX_TEXT_LENGTH - 1);
    text_copy[MAX_TEXT_LENGTH - 1] = '\0';
    to_lower(text_copy);

    //tokenize the text
    char *token = strtok(text_copy, " \t\n\r.,;!?\"'");

    //analyze each word
    while(token != NULL)
    {
        strcpy(word, token);
        remove_punctuation(word);

        result.total_words++;

        //skip the stop words
        if(is_stop_word(word))
        {
            result.stop_words_removed++;
            token = strtok(NULL, " \t\n\r.,;!?\"'");
            continue;
        }

        if(is_positive(word))
        {
            result.positive_score++;
        }
        else if(is_negative(word))
        {
            result.negative_score++;
        }

        token = strtok(NULL, " \t\n\r.,;!?\"'");
    }

    int total = result.positive_score + result.negative_score;

    if(total == 0)
    {
        strcpy(result.sentiment, "Neutral");
        result.sentiment_ratio = 0.0;
    }
    else
    {
        result.sentiment_ratio = (float)(result.positive_score - result.negative_score) / total;

        if(result.positive_score > result.negative_score)
        {
            strcpy(result.sentiment, "Positive");
        }
        else if(result.negative_score > result.positive_score)
        {
            strcpy(result.sentiment, "Negative");
        }
        else
        {
            strcpy(result.sentiment, "Neutral");
        }
    }

    return result;
}

//print the results
void print_sentiment(const SentimentResult *result)
{
    printf("Total words analyzed: %d\n", result->total_words);
    printf("Stop words removed: %d\n", result->stop_words_removed);
    printf("Positive words found: %d\n", result->positive_score);
    printf("Negative words found: %d\n", result->negative_score);
    printf("Overall sentiment: %s\n", result->sentiment);

    if(result->positive_score + result->negative_score > 0)
    {
        printf("Sentiment Score: %.2f\n", result->sentiment_ratio);
    }

}

//func to read text for file
char* read_file(const char *filename)
{

    //open the file to read it
    FILE *fp = fopen(filename, "r");
    if(fp == NULL)
    {
        printf("Error: could not open file '%s'\n", filename);
        return NULL;
    }

    //allocate memory for the text
    char *text = (char*)malloc(MAX_TEXT_LENGTH * sizeof(char));
    if(text == NULL)
    {
        printf("Memory allocation fail\n");
        fclose(fp);
        return NULL;
    }

    //read the file context
    size_t bytes_read = fread(text, sizeof(char), MAX_TEXT_LENGTH -1, fp);
    text[bytes_read] = '\0';

    //close the file
    fclose(fp);
    return text;
}

//func to analyze the file
void analyze_file(const char *filename)
{
    char *text = read_file(filename);
    if(text == NULL)
    {
        return;
    }

    SentimentResult result = analyze_sentiment(text);
    print_sentiment(&result);

    //free the allocated memory
    free(text);
}


int main()
{
    char text[MAX_TEXT_LENGTH];
    char filename[256];
    int choice;

    printf("---Sentiment Analysis Project---\n");

    while(1)
    {
        printf("\n--- MENU ---\n");
        printf("1. Analyze text input\n");
        printf("2. Analyze text file\n");
        printf("3. View word dictionaries\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        
        if (scanf("%d", &choice) != 1) {
            printf("Invalid input. Please enter a number.\n");
            while (getchar() != '\n'); // Clear input buffer
            continue;
    }
    getchar(); // Consume newline

    switch (choice) {
            case 1:
                printf("\nEnter text to analyze (max %d characters):\n", MAX_TEXT_LENGTH - 1);
                fgets(text, MAX_TEXT_LENGTH, stdin);
                
                // Remove trailing newline
                text[strcspn(text, "\n")] = 0;
                
                if (strlen(text) > 0) {
                    SentimentResult result = analyze_sentiment(text);
                    print_sentiment(&result);
                } else {
                    printf("No text entered.\n");
                }
                break;
                
            case 2:
                printf("\nEnter filename (e.g., input.txt): ");
                fgets(filename, sizeof(filename), stdin);
                filename[strcspn(filename, "\n")] = 0; // Remove newline
                
                if (strlen(filename) > 0) {
                    analyze_file(filename);
                } else {
                    printf("No filename entered.\n");
                }
                break;
                
            case 3:
                printf("\n=== POSITIVE WORDS (%d total) ===\n", positive_count);
                for (int i = 0; i < positive_count; i++) {
                    printf("%-15s", positive_words[i]);
                    if ((i + 1) % 5 == 0) printf("\n");
                }
                printf("\n\n=== NEGATIVE WORDS (%d total) ===\n", negative_count);
                for (int i = 0; i < negative_count; i++) {
                    printf("%-15s", negative_words[i]);
                    if ((i + 1) % 5 == 0) printf("\n");
                }
                printf("\n\n=== STOP WORDS (%d total) ===\n", stop_word_count);
                for (int i = 0; i < stop_word_count; i++) {
                    printf("%-15s", stop_words[i]);
                    if ((i + 1) % 5 == 0) printf("\n");
                }
                printf("\n");
                break;
                
            case 4:
                printf("Thank you for using Sentiment Analysis Program!\n");
                return 0;
                
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }
    return 0;
}