#include <stdlib.h>

typedef struct
{
    int id;
    int age;
    char *name;
}Dog;

void get_info(Dog dog)
{
    printf("Dog ID: %d\n", dog.id);
    printf("Dog Age: %d\n", dog.age);
    printf("Dog Name: %s\n", dog.name);
}



int main()
{
    Dog myDog = {1, 3, "Buddy"};
    get_info(myDog);
    return 0;
}
