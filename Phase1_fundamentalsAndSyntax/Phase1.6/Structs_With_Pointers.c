#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct 
{
    char *name;
    int *grades;
    int num_grades;
}Student;


Student create_student(const char *name, int *grades, int num_grades)
{
    Student s;
    s.name = (char*)malloc(strlen(name) + 1);
    strcpy(s.name, name);
    s.grades = (int*)malloc(num_grades * sizeof(int));

    for(int i = 0; i < num_grades; i++)
    {
        s.grades[i] = grades[i];
    }
    s.num_grades = num_grades;
    return s;
}

void free_student(Student *s )
{
    free(s->name);
    free(s->grades);
    s->name = NULL;
    s->grades = NULL;
}


int main()
{
    // Example data
    int grades[] = {90, 85, 88};
    int num_grades = 3;

    // Create a student using your function
    Student s1 = create_student("Emanuel", grades, num_grades);

    // Print student info
    printf("Name: %s\n", s1.name);
    printf("Grades: ");
    for (int i = 0; i < s1.num_grades; i++) {
        printf("%d ", s1.grades[i]);
    }
    printf("\n");

    // Free dynamically allocated memory
    free_student(&s1);

    return 0;

    return 0;
}