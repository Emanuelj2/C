#include "raylib.h"
#include <stdlib.h>
#include <stdio.h>

#define WIN_H 800
#define WIN_W 800

#define NUM_CIRCLES 5

typedef struct
{
        int x;
        int y;
        //int z;
        int vx;
        int vy;
        //int vz;
        int r;

}Circle;

Circle circles[NUM_CIRCLES];

void Init_Circles()
{
        for(int i = 0; i < NUM_CIRCLES; i++)
        {
                circles[i].x = GetRandomValue(0, 795);
                circles[i].y = GetRandomValue(0, 795);
                //circles[i].z = GetRamdomValue(0, 1);
                circles[i].vx = 2;
                circles[i].vy = 2;
                //circles[i].vz = 2;
                circles[i].r = 5;
        }
}

void Draw_Circles()
{
        for(int i = 0; i < NUM_CIRCLES; i++)
        {
                DrawCircle(circles[i].x, circles[i].y, circles[i].r, RED);
        }
}
void Draw_Lines()
{
        for(int i = 0; i < NUM_CIRCLES - 1; i++)
        {
                for(int j = i + 1; j < NUM_CIRCLES; j++)
                {
                        //startposx, startposy, endposx, endposy, color
                        DrawLine(circles[i].x + (circles[i].r)/2,
                                        circles[i].y + (circles[i].r)/2,
                                        circles[j].x + (circles[i].r)/2,
                                        circles[j].y + (circles[i].r)/2,
                                        WHITE);
                }
        }
}

int main()
{
        InitWindow(WIN_W, WIN_H, "connecting lines");
        SetTargetFPS(60);

        Init_Circles();

        while(!WindowShouldClose())
        {
                BeginDrawing();
                ClearBackground(BLACK);
                //DrawText("Emanuel", WIN_W/2, WIN_H/2, 20, LIGHTGRAY);
                Draw_Circles();
                Draw_Lines();
                EndDrawing();
        }
        CloseWindow();

        return 0;
}

