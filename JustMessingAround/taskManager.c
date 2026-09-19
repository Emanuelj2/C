#include <stdio.h>
#include <stdbool.h>



typedef struct
{
	int id;
	char title[100];
	bool compleat;
}Task;


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
		scanf("%d", &input);
		
		switch(input)
		{
			case 1:
				puts("creating a task...");
				break;
			case 2:
				puts("Listing tasks...");
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
