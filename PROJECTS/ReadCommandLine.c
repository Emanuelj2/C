#include <stdio.h>
#include <string.h>

/*
 * argc is the integer count
 * argv is the vector 
 * My name is Emanuel
 *
*/

int main(int argc, char **argv)
{
	char command[100];

	while(1)
	{
		printf("> ");
		
		fgets(command, sizeof(command), stdin);

		command[strcspn(command, "\n")] = '\0';

		if(strcmp(command, "hello") == 0)
		{
			puts("hi");
		}
		else if(strcmp(command, "q") == 0)
		{
			puts("quiting");
			break;
		}	
		else
		{
			puts("unknown");
		}
	}
	return 0;
}
