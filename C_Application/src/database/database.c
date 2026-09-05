#include "database.h"

#include <stdlib.h>


#define INITIAL_CAPACITY 5

int database_init(Database *database)
{
	database->users = malloc(sizeof(User) * INITIAL_CAPACITY);

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
	free(database->users);

	database->users = NULL;
	database->user_count = 0;
	database->user_capacity = 0;
}


//users table
int database_add_user(Database *database, const User *user)
{
	if(database->user_count >= database->user_capacity)
	{
		size_t new_capacity = database->user_capacity * 2;

		User *new_users = realloc(database->users, sizeof(User) * new_capacity);

		if(new_users == NULL)
		{
			return 0;
		}

		database->users = new_users;
		database->user_capacity = new_capacity;
	}

	database->users[database->count] = *user;

	database->user_count++;

	return 1;
}

User *database_get_user(Database *database, size_t index)
{
	if(index >= database->user_count)
	{
		return NULL;
	}
	
	return &database->users[index];	
}

size_t database_get_user_count(const Database *database)
{
	return database->user_count;
}

int database_remove_user(Database *database, size_t index, uint32_t user_id)
{
	size_t index = 0; 
	//TODO : 
}

int database_update_user(Database *database, size_t index, const User *user, uint32_t user_id)
{
	if(index >= database->user_count)
	{
		return 0;
	}
	database->users[index] = *user;

	return 1;
}
