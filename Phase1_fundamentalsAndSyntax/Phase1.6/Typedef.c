#include <stdio.h>
#include <stdlib.h>

typedef struct Node
{
    int data;
    struct  Node *next; //must use 'struct Node' for self-reference
    
}Node;

typedef struct
{
    int x;
    int y;

}Point;

int main()
{

    Point p1;
    p1.x = 10;
    p1.y = 200;

    printf("Point coordinate: (%d, %d)\n", p1.x, p1.y);

    Node *node1 = (Node*)malloc(sizeof(Node));
    Node *node2 = (Node*)malloc(sizeof(Node));

    node1->data = 5;
    node2->data = 10;

    node1->next = node2;
    node2->next = NULL;

    printf("Node 1 data: %d\n", node1->data);
    printf("Node 2 data: %d\n", node1->next->data);

    free(node1);
    free(node2);

    return 0;
}