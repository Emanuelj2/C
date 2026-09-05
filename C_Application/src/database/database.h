#ifndef DATABASE_H
#define DATABASE_H

#include <stddef.h>

#include "../models/user.h"

typedef struct
{
	User *users;

	size_t user_count;
	size_t user_capacity;
}Database;


int database_init(Database *database);					// 1 = success, 0 = failure
void database_destroy(Database *database);


//users table
int database_add_user(Database *database, const User *user);		// 1 = success, 0 = failure
User *database_get_user(Database *database, size_t index);		//returns pointer to User or NULL id invalid
size_t database_get_user_count(const Database *database);
int database_remove_user(Database *database, size_t index, uint32_t user_id);
int database_update_user(Database *database, size_t index, const User *user, uint32_t user_id);

#endif
