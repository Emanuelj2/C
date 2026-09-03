#ifndef USER_H
#define USER_H

#include <stdint.h>

typedef struct
{
	uint32_t id;
	char first_name		[50];
	char middle_name	[50];
	char last_name		[50];
	char username		[50];
	char password 		[50];
	int32_t age;
	int32_t permissions;
}User;


void user_create(User *user);

void user_set_first_name(User *user, const char *first_name);
void user_set_middle_name(User *user, const char *middle_name);
void user_set_last_name(User *user, const char *last_name);
void user_set_username(User *user, const char *username);
void user_set_password(User *user, const char *password);
void user_set_age(User *user, int32_t age);

const char *user_get_first_name(const User *user);
const char *user_get_middle_name(const User *user);
const char *user_get_last_name(const User *user);
const char *user_get_username(const User *user);
const char *user_get_password(const User *user);
const char *user_get_full_name(const User *user);
int32_t user_get_age(const User *user);
uint32_t user_get_id(const User *user);
#endif
