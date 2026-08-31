#include <stdio.h>
#include <raylib.h>
#include <stdlib.h>

#define WIDTH 500
#define HEIGHT 500

#define MAX_POINTS 10
#define GRID_SPACING 20
#define GRAPH_TOP 100

void draw_grid()
{
	for(int32_t x = 0; x <= WIDTH; x += GRID_SPACING)
	{
		DrawLine(x, GRAPH_TOP, x, HEIGHT, WHITE);
	}

	for(int32_t y = GRAPH_TOP; y <= HEIGHT; y += GRID_SPACING)
	{
		DrawLine(0, y, WIDTH, y, WHITE);
	}
}
void draw_point()
{
	int32_t max_x_index = WIDTH / GRID_SPACING;
        int32_t max_y_index = (HEIGHT - GRAPH_TOP) / GRID_SPACING;

        int32_t x_index = rand() % (max_x_index + 1);
        int32_t y_index = rand() % (max_y_index + 1);

        int32_t x = x_index * GRID_SPACING;
        int32_t y = GRAPH_TOP + y_index * GRID_SPACING;

        DrawCircle(x, y, 5, RED);
}

void draw_points(int32_t n)
{
	for(int32_t i = 0; i < n; i++)
	{
		draw_point();
	}
}

bool draw_button(int32_t x_pos, int32_t y_pos, const char* text)
{
	Rectangle button = {x_pos, y_pos, 160, 60};
	
	bool mouse_over = CheckCollisionPointRec(GetMousePosition(), button);

	if(mouse_over)
		DrawRectangleRec(button, DARKGRAY);
	else
		DrawRectangleRec(button, GRAY);

	DrawText(text, x_pos + 20, y_pos + 20, 20, WHITE);

	return mouse_over && IsMouseButtonPressed(MOUSE_BUTTON_LEFT);
}

int main(void)
{
	InitWindow(WIDTH, HEIGHT, "Linear Regression");
	SetTargetFPS(60);

	draw_grid();
	while(!WindowShouldClose())
	{
		BeginDrawing(); 
			
			if(draw_button(20, 20, "Regenerate"))
			{
				draw_points(MAX_POINTS);
				TraceLog(LOG_INFO, "button clicked : generated 10 random data points");
			}
			
		EndDrawing();

	}

	CloseWindow();

	return 0;
}
