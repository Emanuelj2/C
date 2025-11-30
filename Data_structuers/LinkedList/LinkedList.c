#include "LinkedList.h"
#include <stdlib.h>
#include <stdio.h>

Node* create_node(int value)
{
    //allocate the memory
    Node* node = (Node*)malloc(sizeof(Node));

    //check if allocation faild
    if(!node)
    {
        printf("memory allocation fail\n");
        exit(1);
    }

    node->data = value;
    node->next = NULL;
    return node;
}

void insert_head(Node** head, int value)
{
    //step1: create the node with the value
    Node* node = create_node(value);
    node->next = *head;
    *head = node;
}

void insert_tail(Node** head, int value)
{
    Node* node = create_node(value);
    Node* curr  = *head; //used for iterating the linked list

    //if there is no node in the list
    if(*head == NULL)
    {
        *head = node;
        return;
    }

    while(curr->next) //while there is a node ahead of the current node
    {
        curr = node->next;
    }
    curr->next = node;
}

void insert_at(Node** head, int index, int value)
{
    Node *node = create_node(value);

    if(index == 0)
    {
        node->next = *head;
        *head = node;
        return;
    }

    Node *curr = *head;
    for(int i = 0; i < index - 1; i++)
    {
        if(curr == NULL || curr->next == NULL)
        {
            free(node); //free the allocated node
            return;
        }
        curr = curr->next;
    }
    node->next = curr->next;
    curr->next = node;
}

//delet operations
void delete_value(Node** head, int value)
{
    Node* curr = *head; //used for iterating
    Node* prev = NULL;

    while (curr)
    {
        if(curr->data == value)
        {
            if(prev == NULL)
            {
                *head = curr->next;
                free(curr);
                return;
            }
            else
            {
                prev->next = curr->next;
                free(curr);
                return;
            }
        }
        prev = curr;
        curr = curr->next;
    }
}
void delete_at(Node** head, int index);


//search fiunction
int search(Node* head, int value)
{
    Node *curr = head;
    while(curr)
    {
        if(curr->data == value)
        {
            return 1;
        }
        curr = curr->next;
    }
    return 0;
}

void reverse(Node** head);

void print_list(Node* head)
{
    while(head)
    {
        printf("%d -> ", head->data);
        head = head->next;
    }
    printf("NULL\n");
}

void free_list(Node** head)
{
   Node *curr = *head;
   while(curr)
   {
    Node* next = curr->next;
    free(curr);
    curr = next;
   } 
   *head = NULL;
}