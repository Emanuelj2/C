#include "stdio.h"
#include "raylib.h"

//window parameters
#define WIN_W 800
#define WIN_H 500

//font size
#define NORMAL_TEXT 20 

//make a node


int main(void)
{
	InitWindow(WIN_W, WIN_H, "Nodes");

	SetTargetFPS(60);
	
	while(!WindowShouldClose())
	{
		//update variables here

		//draw here
		BeginDrawing();
			DrawText("hello world", WIN_W/2, WIN_H/2, NORMAL_TEXT, RED);
		EndDrawing();
	}

	CloseWindow();
	
	return 0;
}
