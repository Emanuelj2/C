#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#define MAX_TASKS 50


static int id_tracker = 1;
static int task_count = 0;

typedef struct
{
	int id;
	char title[100];
	bool compleat;
}Task;

Task tasks[MAX_TASKS];

void create_task(void);
void print_task(void);
void compleate_task(int id);
void delete_task(int id);

int  main(void)
{
	bool running = true;

	do
	{
		puts("1. Create Task");
		puts("2. List Task");
		puts("3. Compleate Task");
		puts("4. Delete Task");
		puts("5. Exit");
		int input;

		if(scanf("%d", &input) != 1)
		{
			puts("invalid input, enter a number.");

			while(getchar() != '\n')
			{
				//clear invalid input
			}
			continue;
		}
		
		switch(input)
		{
			case 1:
				puts("creating a task...");
				create_task();
				break;
			case 2:
				puts("Listing tasks...");
				print_task();
				break;
			case 3:
				puts("Compleating a task...");
				break;
			case 4:
				puts("Deleting a task...");
				break;
			case 5:
				puts("Exiting...");
				running = false;
				break;
			default:
				puts("Invalid input...");
		}

	}while(running);

	return 0;
}


void create_task(void)
{
	if(task_count >= MAX_TASKS)
	{
		puts("task list is full");
		return;
	}
	char input[100];
	puts("what do you want to name your task...");
	scanf(" %99[^\n]", input);
	
	if(strlen(input) > sizeof(tasks[task_count].title))
	{
		puts("the title is too long");
		return;
	}

	tasks[task_count].id = id_tracker;
	strcpy(tasks[task_count].title, input);
	tasks[task_count].compleat = false;
	
	task_count++;
	id_tracker++;
	puts("task created successfully");
}
void print_task(void)
{
	int number_of_elements = sizeof(tasks) / sizeof(tasks[0]);
	printf("number of tasks: %d\n", number_of_elements);
}
void compleate_task(int id)
{
}
void delete_task(int id)
{
}
