#include "database.h"

#include <stdlib.h>


#define INITIAL_CAPACITY 5

int database_init(Database *database)
{
	database->users = malloc(sizeof(User *) * INITIAL_CAPACITY);

	if(database->users == NULL)
	{
		return 0;
	}

	database->user_count = 0;
	database->user_capacity = INITIAL_CAPACITY;

	return 1;
}

void database_destroy(Database *database)
{
	for(size_t i = 0; i < database->user_count; i++)
	{
		free(database->users[i]);
	}

	free(database->users);

	database->users = NULL;
	database->user_count = 0;
	database->user_capacity = 0;
}

