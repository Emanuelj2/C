#include <string.h>
#include <stdio.h>
#include "user.h"

static uint32_t next_user_id = 1;

void user_create(User *user)
{
	user->id                    = next_user_id++;

	user->first_name	[0] = '\0';
	user->last_name		[0] = '\0';
	user->middle_name	[0] = '\0';
	user->username		[0] = '\0';
	user->password		[0] = '\0';

	user->age 		    = 0;
	user->permissions           = 0;
}

void user_set_first_name(User *user, const char *first_name)
{
	strcpy(user->first_name, first_name);
}

void user_set_middle_name(User *user, const char *middle_name)
{
	strcpy(user->middle_name, middle_name);
}

void user_set_last_name(User *user, const char *last_name)
{
	strcpy(user->last_name, last_name);
}

void user_set_username(User *user, const char *username)
{
	strcpy(user->username, username);
}

void user_set_password(User *user, const char *password)
{
	strcpy(user->password, password);
}

void user_set_age(User *user, int32_t age)
{
	user->age = age;
}

const char *user_get_first_name(const User *user)
{
	return user->first_name;
}

const char *user_get_middle_name(const User *user)
{
	return user->middle_name;
}

const char *user_get_last_name(const User *user)
{
	return user->last_name;
}

const char *user_get_username(const User *user)
{
	return user->username;
}

const char *user_get_password(const User *user)
{
	return user->password;
}

const char *user_get_full_name(const User *user)
{
	static char full_name[150];

	if(user->middle_name[0] == '\0')
	{
		snprintf(
                        full_name,
                        sizeof(full_name),
                        "%s %s",
                        user->first_name,
                        user->last_name
                        );
	}
	else
	{
		snprintf(
			full_name,
			sizeof(full_name), 
			"%s %s %s",
			user->first_name,
			user->middle_name,
			user->last_name
			);
	}
	return full_name;
}
int32_t user_get_age(const User *user)
{
	return user->age;
}

uint32_t user_get_id(const User *user)
{
	return user->id;
}
