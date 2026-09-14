#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct
{
	char first_name[21];
	char last_name[21];
	int age;
}Person;

void set_first_name(Person *person, const char* first_name)
{
	if(strlen(first_name) > sizeof(person->first_name) - 1)
	{

		printf("first name cannot exced 20 characrs\n");
		return;
	}
	strcpy(person->first_name, first_name);
}

void set_last_name(Person *person, const char* last_name)
{
        if(strlen(last_name) > sizeof(person->last_name) - 1)
        {

                printf("last name cannot exced 20 characrs\n");
                return;
        }
        strcpy(person->last_name, last_name);
}

int main(void)
{
	Person p1 = {0};
	Person p2 = {0};

	set_first_name(&p1, "Emanuel");
	set_last_name(&p1, "Jose");
	printf("first name: %s\nlast name: %s\n", p1.first_name, p1.last_name); 

	set_first_name(&p2, "cdosovubslvbulduvbsodbvsoubou");
	set_last_name(&p2, "Jose");
	printf("first name: %s\nlast name: %s\n", p2.first_name, p2.last_name);

	return 0;

}
