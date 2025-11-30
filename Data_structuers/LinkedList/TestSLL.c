#include "LinkedList.h"
#include <stdio.h>
#include <stdlib.h>

int main()
{
    Node *head = NULL;
    insert_head(&head, 10);
    insert_head(&head, 20);
    insert_head(&head, 50);
    
    insert_tail(&head, 30);

    insert_at(&head, 2, 123);


    print_list(head);

    free_list(&head);
    return 0;
}