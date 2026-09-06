#ifndef DATABASE_H
#define DATABASE_H

#include <stddef.h>

#include "../models/user.h"

typedef struct
{
	User **users;

	size_t user_count;
	size_t user_capacity;
}Database;


int database_init(Database *database);					// 1 = success, 0 = failure
void database_destroy(Database *database);

#endif
