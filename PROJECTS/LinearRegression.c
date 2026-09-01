#include <stdio.h>
#include <raylib.h>
#include <stdint.h>
#include <stdlib.h>
#include <time.h>

#define WIDTH 500
#define HEIGHT 500

#define MAX_POINTS 10
#define GRID_SPACING 20
#define GRAPH_TOP 100


typedef struct Point
{
	int32_t x;
	int32_t y;
}Point;

Point points[MAX_POINTS];
int32_t point_count = 0;

void draw_grid()
{
	for(int32_t x = 0; x <= WIDTH; x += GRID_SPACING)
	{
		DrawLine(x, GRAPH_TOP, x, HEIGHT, GRAY);
	}

	for(int32_t y = GRAPH_TOP; y <= HEIGHT; y += GRID_SPACING)
	{
		DrawLine(0, y, WIDTH, y, GRAY);
	}
}

void draw_points(int32_t n)
{
	int32_t max_x_index = WIDTH / GRID_SPACING;
        int32_t max_y_index = (HEIGHT - GRAPH_TOP) / GRID_SPACING;
	int32_t total = (max_x_index + 1) * (max_y_index + 1);

	Point all_points[total];
	int32_t idx = 0;
	for(int32_t x_i = 0; x_i <= max_x_index; x_i++)
	{
		for(int32_t y_i = 0; y_i <= max_y_index; y_i++)
		{
			all_points[idx].x = x_i * GRID_SPACING;
                        all_points[idx].y = GRAPH_TOP + y_i * GRID_SPACING;
                        idx++;
		}
	}

	for(int32_t i = 0; i < n; i++)
        {
                int32_t j = i + rand() % (total - i);
                Point tmp = all_points[i];
                all_points[i] = all_points[j];
                all_points[j] = tmp;
        }

	point_count = 0;
	for(int32_t i = 0; i < n; i++)
	{
		points[point_count] = all_points[i];
		point_count++;
	}
}

void to_graph_space(Vector2 *graph_points, int32_t max_y_index)
{
	for(int32_t i = 0; i < point_count; i++)
	{
		graph_points[i].x = points[i].x / (float)GRID_SPACING;
		graph_points[i].y = (float)max_y_index - (points[i].y - GRAPH_TOP) / (float)GRID_SPACING;
	}
}

/* linear regression formula: Y =  B_0 + (B_1 * X)
 * Y = dependent variable (outcome)
 * X = independent variable (predictor)
 * B_0 = the y intercept
 * B_1 = slope of the regression line (coefficient for X)
 * e = error term (residuals)
 */

void linear_regression(Vector2 *pts, float *b_0, float *b_1, float *r_squared)
{
	float x_sum = 0;
	float y_sum = 0;

	for(int32_t i = 0; i < point_count; i++)
	{
		x_sum += pts[i].x;
		y_sum += pts[i].y;
	}


	float x_mean = x_sum/point_count;
	float y_mean = y_sum/point_count;

	float numerator = 0;
	float denominator = 0;
	float syy = 0;

	for(int32_t i = 0; i < point_count; i++)
	{
		float dx = pts[i].x - x_mean;
		float dy = pts[i].y - y_mean;
		numerator += dx * dy;
		denominator += dx * dx;
		syy += dy * dy;
	}

	*b_1 = numerator/denominator;
	*b_0 = y_mean - (*b_1) * x_mean;
	*r_squared = (numerator * numerator) / (denominator * syy);
}

void draw_regression_line(float b_0, float b_1, int32_t max_y_index)
{
	float x0_graph = 0.0f;
	float x1_graph = WIDTH / (float)GRID_SPACING;
	float y0_graph = b_0 + b_1 * x0_graph;
	float y1_graph = b_0 + b_1 * x1_graph;

	int32_t y_start = (int32_t)(GRAPH_TOP + (max_y_index - y0_graph) * GRID_SPACING);
	int32_t y_end = (int32_t)(GRAPH_TOP + (max_y_index - y1_graph) * GRID_SPACING);
	DrawLine(0, y_start, WIDTH, y_end, GREEN);
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
	srand((uint32_t)time(NULL));

	float b_0 = 0;
	float b_1 = 0;
	float r_squared = 0;

	bool has_line = false;

	//draw_grid();
	while(!WindowShouldClose())
	{
		BeginDrawing();

	       		ClearBackground(BLACK);	
			draw_grid();
			
			int32_t max_y_index = (HEIGHT - GRAPH_TOP) / GRID_SPACING;

			Vector2 mouse = GetMousePosition();

			for(int32_t i = 0; i < point_count; i++)
			{
        			DrawCircle(points[i].x, points[i].y, 5, RED);

        			if(CheckCollisionPointCircle(mouse, (Vector2){points[i].x, points[i].y}, 8))
        			{
                			int32_t col = points[i].x / GRID_SPACING;
                			int32_t row_from_top = (points[i].y - GRAPH_TOP) / GRID_SPACING;
                			int32_t row_from_bottom = max_y_index - row_from_top;

                			char label[32];
                			snprintf(label, sizeof(label), "(%d, %d)", col, row_from_bottom);

                			int32_t font_size = 14;
                			int32_t text_width = MeasureText(label, font_size);
                			int32_t box_x = points[i].x + 10;
                			int32_t box_y = points[i].y - 10;
                			int32_t padding = 4;

                			DrawRectangle(box_x - padding, box_y - padding, text_width + padding * 2, font_size + padding * 2, LIGHTGRAY);
                			DrawText(label, box_x, box_y, font_size, BLACK);
        			}
			}

			for(int32_t i = 0; i < point_count; i++)
			{
				DrawCircle(points[i].x, points[i].y, 5, RED);
			}
			if(has_line)
			{
				draw_regression_line(b_0, b_1, max_y_index);
				char eq_lable[64];
				char r2_lable[32];
				snprintf(eq_lable, sizeof(eq_lable), "y = %.2fx + %.2f", b_1, b_0);
				snprintf(r2_lable, sizeof(r2_lable), "R^2 = %.3f", r_squared);
				
				DrawText(eq_lable, 200, 30, 20, WHITE);
				DrawText(r2_lable, 200, 55, 20, WHITE);
			}

			if(draw_button(20, 20, "Generate"))
			{
				draw_points(MAX_POINTS);
				Vector2 graph_points[MAX_POINTS];
				to_graph_space(graph_points, max_y_index); 
				linear_regression(graph_points, &b_0, &b_1, &r_squared);
				has_line = true;
				TraceLog(LOG_INFO, "button clicked : generated 10 random data points");
			}
			
		EndDrawing();

	}

	return 0;
}
