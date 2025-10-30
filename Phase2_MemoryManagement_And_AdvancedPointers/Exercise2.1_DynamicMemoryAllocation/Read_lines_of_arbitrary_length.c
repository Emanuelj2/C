#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char **data;
    size_t size;
    size_t capacity;
} StringArray;

static StringArray *sa_create(void) {
    StringArray *sa = malloc(sizeof(StringArray));
    if (!sa) return NULL;
    sa->capacity = 4;
    sa->size = 0;
    sa->data = malloc(sa->capacity * sizeof(char *));
    if (!sa->data) {
        free(sa);
        return NULL;
    }
    return sa;
}

static void sa_free(StringArray *sa)
{
    if(!sa) return;
    for(size_t i = 0; i < sa->size; i++)
        free(sa->data[i]);
    free(sa->data);
    free(sa);
}

static int sa_push(StringArray* sa, char *line)
{
    if(!sa) return -1;
    if(sa->size >= sa->capacity)
    {
        size_t newcap = sa->capacity * 2;
        char **temp = realloc(sa->data, newcap * sizeof(char *));
        if(!temp) return -1;
        sa->data = temp;
        sa->capacity = newcap;
    }
    sa->data[sa->size++] = line;
    return 0;
}

static char *read_line_arbitrary(void)
{
    size_t cap = 80;
    size_t len = 0;
    char *buff = malloc(cap);
    if(!buff) return NULL;

    int c;
    while((c = getchar()) != EOF)
    {
        if(len + 1 >= cap)
        {
            size_t newcap = cap * 2;
            char* temp = realloc(buff, newcap);
            if(!temp)
            {
                free(buff);
                return NULL;
            }
            buff = temp;
            cap = newcap;
        }
        buff[len++] = (char)c;
        if(c == '\n') break;
    }
    if(len == 0 && c == EOF)
    {
        free(buff);
        return NULL;
    }
    buff[len] = '\0';
    char *sh = realloc(buff, len + 1);
    if (sh) buff = sh;
    return buff;
}

static StringArray *read_all_lines(void)
{
    StringArray *sa = sa_create();
    if (!sa) return NULL;
    char *ln;
    while ((ln = read_line_arbitrary()) != NULL)
    {
        if (sa_push(sa, ln) != 0)
        {
            free(ln);
            sa_free(sa);
            return NULL;
        }
    }
    return sa;
}

int main(void)
{
    printf("Enter lines (Ctrl+C to end):\n");
    StringArray *lines = read_all_lines();
    if (!lines)
    {
        printf("(no input read or allocation failed)\n");
    }
    else
    {
        printf("\nRead %zu lines:\n", lines->size);
        for (size_t i = 0; i < lines->size; ++i)
        {
            printf("%3zu: %s", i + 1, lines->data[i]);
            if (lines->data[i][strlen(lines->data[i])-1] != '\n') printf("\n");
        }
        sa_free(lines);
    }
    return 0;
}
