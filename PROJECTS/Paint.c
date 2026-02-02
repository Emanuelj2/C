#include "raylib.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define WIN_W 1000
#define WIN_H 1000



//GLOBAL VARIABLES
Color color = BLACK;
int brush_size = 5;
Color silly_color;
float silly_timer = 0.0f;


//function to draw
void Draw()
{
        Vector2 mouse = GetMousePosition();
        DrawCircle(mouse.x, mouse.y, brush_size, color);
}

void BrushSize()
{
        if(IsKeyPressed(KEY_ONE) && brush_size < 15)
        {
                brush_size++;
        }
        if(IsKeyPressed(KEY_TWO) && brush_size > 1)
        {
                brush_size--;
        }

}

void DisplayStats()
{

        //display the bruch size
        DrawText(TextFormat("BrushSize: %d", brush_size),WIN_W -150, WIN_H - 250, 20, BLACK);
        //display the color that is used
        DrawText("Color", WIN_W - 150, WIN_H - 200, 20,color);
        // drawing or erasing
        if(IsKeyPressed(KEY_E))
        {
                DrawText("Erasing", WIN_W - 150, WIN_H - 150, 20, BLACK);
        }
        else
        {
                DrawText("Drawing", WIN_W - 150, WIN_H - 150, 20, BLACK);
        }
}

void SillyColor()
{
        silly_timer += GetFrameTime();

        if(silly_timer >= 2.0f)
        {
        silly_color = (Color)
        {
                GetRandomValue(0, 255),
                GetRandomValue(0, 255),
                GetRandomValue(0, 255),
                255,
        };
        silly_timer = 0.0f;
        }
        Vector2 mouse = GetMousePosition();
        DrawCircle(mouse.x, mouse.y, brush_size, silly_color);
}

int main()
{
        InitWindow(WIN_W, WIN_H, "Canvas");
        SetTargetFPS(120);

        BeginDrawing();
        ClearBackground(WHITE);
        EndDrawing();

        silly_color = (Color){
                GetRandomValue(0, 255),
                GetRandomValue(0, 255),
                GetRandomValue(0, 255),
                255
        };

        while(!WindowShouldClose())
        {
                BeginDrawing();
                DisplayStats();
                BrushSize();
                //if the mouse or pad button is presed draw
                if(IsMouseButtonDown(MOUSE_BUTTON_LEFT))
                {
                        if(IsKeyDown(KEY_S))
                        {
                                SillyColor();
                        }
                        else
                        {
                                Draw();
                        }
                }


                if(IsKeyPressed(KEY_E))
                {
                        color = WHITE;
                }
                if(IsKeyPressed(KEY_D))
                {
                        color = BLACK;
                }
                if(IsKeyPressed(KEY_R))
                {
                        color = RED;
                }
                if(IsKeyPressed(KEY_B))
                {
                        color = BLUE;
                }
                if(IsKeyPressed(KEY_G))
                {
                        color = GREEN;
                }

                EndDrawing();
        }
        printf("program ended\n");
        return 0;
}