#ifndef LINKEDLIST_H
#define LINKEDLIST_H

//make the node structuer
//if we want to refreence the struct the name of the node has to appear before and after
typedef struct Node
{
    int data;
    struct Node *next;
}Node;

Node* create_node(int value);

//implementations
void insert_head(Node** head, int value);
void insert_tail(Node** head, int value);
void insert_at(Node** head, int index, int value);

//delet operations
void delete_value(Node** head, int value);
void delete_at(Node** head, int index);


//search fiunction
int search(Node* head, int value);
void reverse(Node** head);
void print_list(Node* head);
void free_list(Node** head);

#endif