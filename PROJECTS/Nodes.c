#include "raylib.h"
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

//window parameters
#define WIN_W 800
#define WIN_H 500

//font size
#define NORMAL_TEXT 20 

//node radius
#define RADIUS 25

//node spacing
#define NODE_SPACING 75

//starting positions
#define X_POS 100
#define Y_POS 250


static int32_t count = 1;

//make a node
typedef struct Node
{
	int32_t radius;
	int32_t data;
	struct Node* next;
}Node;


Node *create_node(void)
{
	Node *node = malloc(sizeof(Node));

	if(node == NULL)
	{
		return NULL;
	}

	node->radius = RADIUS;
	node->data = count;
	node->next = NULL;
	
	count++;

	return node;
}


void add_node(Node **head)
{
	Node *new_node = create_node();
	
	if(new_node == NULL)
	{
		return;
	}

	if(*head == NULL)
	{
		*head = new_node;
		return;
	}

	Node *current = *head;

	while(current->next != NULL)
	{
		current = current->next;
	}

	current->next = new_node;
}

void free_linked_list(Node *head)
{
	Node *current = head;
	
	while(current != NULL)
	{
		Node *next = current->next;
		free(current);

		current = next;
	}
}

int main(void)
{
	InitWindow(WIN_W, WIN_H, "Nodes (linked list)");

	SetTargetFPS(60);
	
	Node *head = NULL;

	//add node button
	Rectangle add_button = {20, 20, 150, 50};

	while(!WindowShouldClose())
	{
		//update variables here
		
		Vector2 mouse_position = GetMousePosition();
		if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
		{
			if(CheckCollisionPointRec(mouse_position, add_button))
			{
				add_node(&head);
			}
		}
		
		//draw here
		BeginDrawing();
			
			DrawRectangleRec(add_button, BLUE);

			DrawText("Add Node",
				 add_button.x + 25,
				 add_button.y + 15,
				 NORMAL_TEXT,
				 WHITE
				);
			Node *current = head;

        		int x = X_POS;
        		int y = Y_POS;

        		while (current != NULL)
        		{

            			DrawCircle(x, y, current->radius, RED);

            			char data_text[20];

            			sprintf(data_text, "%d", current->data);

            			// Center text inside node
            			int text_width = MeasureText(
                			data_text,
                			NORMAL_TEXT
            			);

            			DrawText(
                			data_text,
                			x - text_width / 2,
                			y - NORMAL_TEXT / 2,
                			NORMAL_TEXT,
                			WHITE
            			);


            			if (current->next != NULL)
            			{
                			DrawLine(
                    				x + current->radius,
                    				y,
                    				x + NODE_SPACING - current->radius,
                    				y,
                    				WHITE
                			);

                			// Draw arrow head
                			DrawTriangle(
                    				(Vector2){
                        				x + NODE_SPACING - current->radius,
                        				y
                    				},

                    				(Vector2){
                        				x + NODE_SPACING - current->radius - 10,
                        				y - 6
                    				},

                    				(Vector2){
                        				x + NODE_SPACING - current->radius - 10,
                        				y + 6
                    				},

                    				WHITE
                				);
            				}


            		// Move to next node position
            		x += NODE_SPACING;

            		// Move to next linked-list node
            		current = current->next;
        		}

		EndDrawing();
	}

	free_linked_list(head);
	CloseWindow();
	
	return 0;
}
