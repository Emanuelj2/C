#include "user_repository.h"
#include <stdlib.h>


int database_add_user(Database *database, const User *user)
{
        if(database->user_count >= database->user_capacity)
        {
                size_t new_capacity = database->user_capacity * 2;

                User **new_users = realloc(database->users, sizeof(User *) * new_capacity);

                if(new_users == NULL)
                {
                        return 0;
                }

                database->users = new_users;
                database->user_capacity = new_capacity;
        }

        User *new_user = malloc(sizeof(User));
        if(new_user == NULL)
        {
                return 0;
        }
        *new_user = *user;

        database->users[database->user_count] = new_user;
        database->user_count++;

        return 1;
}


User *database_get_user(Database *database, size_t index)
{
        if(index >= database->user_count)
        {
                return NULL;
        }

        return database->users[index];
}

size_t database_get_user_count(const Database *database)
{
        return database->user_count;
}


int database_remove_user(Database *database, uint32_t user_id)
{

       size_t index = 0;
       while(index < database->user_count)
       {
               if(database->users[index]->id == user_id)
               {
                       break;
               }
               index++;
       }

       if(index == database->user_count)
       {
               return 0;
       }

       //shift users after the remove user to the left
       for(size_t i = index; i < database->user_count - 1; i++)
       {
               database->users[i] = database->users[i + 1];
       }

       database->user_count--;

       return 1;
}

int database_update_user(Database *database, const User *user, uint32_t user_id)
{
        for(size_t i = 0; i < database->user_count; i++)
        {
                if(database->users[i]->id == user_id)
                {
                        uint32_t original_id = database->users[i]->id;
                        *database->users[i] = *user;
                        database->users[i]->id = original_id;
                        return 1;
                }
        }

        return 0;
}

