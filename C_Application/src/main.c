#include <stdio.h>

#include "models/user.h"
#include "database/database.h"

int main(void)
{
	Database database;

	if(!database_init(&database))
	{
		puts("Failed to initialize database.");
		return 1;
	}

	User user1;
	User user2;
	User user3;

	user_create(&user1);
	user_create(&user2);
	user_create(&user3);

	user_set_first_name(&user1, "Emanuel");
	user_set_last_name(&user1, "Jose");
	user_set_username(&user1, "Emanuelj2");
	user_set_password(&user1, "password123");
	user_set_age(&user1, 23);

	user_set_first_name(&user2, "Gerardo");
	user_set_last_name(&user2, "Jose");
	user_set_username(&user2, "Gerardoj2");
	user_set_password(&user2, "password123");
	user_set_age(&user2, 20);

	user_set_first_name(&user3, "Jonathan");
	user_set_last_name(&user3, "Jose");
        user_set_username(&user3, "Jonathanj2");
	user_set_password(&user3, "password123");
	user_set_age(&user3, 5);

	//add the user to the db
	database_add_user(&database, &user1);
	database_add_user(&database, &user2);
	database_add_user(&database, &user3);

	printf("Users before deletion:\n\n");
       	for (size_t i = 0; i < database_get_user_count(&database); i++)
       	{
	       	User *user = database_get_user(&database, i);
	       	printf( "ID: %u | Name: %s | Username: %s\n",
			       	user_get_id(user),
			       	user_get_first_name(user),
			       	user_get_username(user) );
       	}


	printf("\nRemoving user with ID 2...\n\n");
       	if (database_remove_user(&database, 2))
       	{ 
		printf("User removed successfully.\n");
       	} 
	else 
	{ 
		printf("User not found.\n"); 
	}
	
	printf("\nUsers after deletion:\n\n");
       	for (size_t i = 0; i < database_get_user_count(&database); i++)
       	{ 
		User *user = database_get_user(&database, i);
	       	printf( "ID: %u | Name: %s | Username: %s\n",
			       	user_get_id(user),
			       	user_get_first_name(user),
			       	user_get_username(user) );
       	}

	database_destroy(&database);
	return 0;
}
