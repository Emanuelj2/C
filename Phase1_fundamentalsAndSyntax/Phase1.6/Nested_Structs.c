#include <stdlib.h>
#include <stdio.h>

typedef struct
{
    char Name[50];
    int age;
}Person;

typedef struct
{
    Person person;
    char department[50];
    float salary;
}Employee;


int main()
{
    Employee emp = {
    .person = {"Emanuel", 20},
    .department = "Computer Science",
    .salary = 80000
    };

    printf("%s is %d years old\n", emp.person.Name, emp.person.age);

    return 0;
}