#ifndef USER_REPOSITORY_H
#define USER_REPOSITORY_H

#include <stddef.h>
#include "../database/database.h"
#include "../models/user.h"

int database_add_user(Database *database, const User *user);            // 1 = success, 0 = failure
User *database_get_user(Database *database, size_t index);              //returns pointer to User or NULL id invalid
size_t database_get_user_count(const Database *database);
int database_remove_user(Database *database, uint32_t user_id);
int database_update_user(Database *database, const User *user, uint32_t user_id);

#endif
