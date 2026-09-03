#include <stdio.h>

#include "models/user.h"

int main(void)
{
	User user;
	User user2;
        User user3;
	
	user_create(&user);
	user_create(&user2);
        user_create(&user3);

	user_set_first_name(&user, "Emanuel");
    	user_set_middle_name(&user, "Jose");
    	user_set_last_name(&user, "Doe");
    	user_set_username(&user, "emanuel");
	user_set_password(&user, "password");
    	user_set_age(&user, 25);
	
	user_set_first_name(&user2, "John");
        user_set_middle_name(&user2, "Michael");
        user_set_last_name(&user2, "Smith");
        user_set_username(&user2, "john");
        user_set_password(&user2, "password123");
        user_set_age(&user2, 30);

        user_set_first_name(&user3, "Sarah");
        user_set_middle_name(&user3, "Marie");
        user_set_last_name(&user3, "Johnson");
        user_set_username(&user3, "sarah");
        user_set_password(&user3, "password456");
        user_set_age(&user3, 22);

        printf("ID: %u\n", user.id);
        printf("Name: %s %s %s\n", user.first_name,
                                   user.middle_name,
                                   user.last_name);
        printf("Username: %s\n", user.username);
        printf("Age: %d\n\n", user.age);

   
        printf("ID: %u\n", user2.id);
        printf("Name: %s %s %s\n", user2.first_name,
                                   user2.middle_name,
                                   user2.last_name);
        printf("Username: %s\n", user2.username);
        printf("Age: %d\n\n", user2.age);

	
        printf("ID: %u\n", user3.id);
        printf("Name: %s %s %s\n", user3.first_name,
                                   user3.middle_name,
                                   user3.last_name);
        printf("Username: %s\n", user3.username);
        printf("Age: %d\n", user3.age);

	puts("getters");
	printf("ID: %u\n", user_get_id(&user));
	printf("Name: %s\n", user_get_full_name(&user));
	printf("Username: %s\n", user_get_username(&user));
	printf("Age: %d\n\n", user_get_age(&user));


	printf("ID: %u\n", user_get_id(&user2));
	printf("Name: %s\n", user_get_full_name(&user2));
	printf("Username: %s\n", user_get_username(&user2));
	printf("Age: %d\n\n", user_get_age(&user2));


	printf("ID: %u\n", user_get_id(&user3));
	printf("Name: %s\n", user_get_full_name(&user3));
	printf("Username: %s\n", user_get_username(&user3));
	printf("Age: %d\n", user_get_age(&user3));

	return 0;
}
