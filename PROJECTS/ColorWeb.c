#include "raylib.h"
#include <stdlib.h>
#include <stdio.h>

#define WIN_H 500
#define WIN_W 500

#define NUM_CIRCLES 7
#define SPEED 2
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
                circles[i].x = GetRandomValue(0, WIN_W);
                circles[i].y = GetRandomValue(0, WIN_H);
                //circles[i].z = GetRamdomValue(0, 1);
                circles[i].vx = SPEED;
                circles[i].vy = SPEED;
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
/*
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
*/

//note to self i dont want the color to change every 60 secs
void Draw_Triangles()
{
        for(int i = 0; i < NUM_CIRCLES - 1; i++)
        {
                for(int j = i + 1; j < NUM_CIRCLES; j++)
                {
                        for(int k = j + 1; k < NUM_CIRCLES; k++)
                        {
                                //create the vectors
                                Vector2 position1 =  (Vector2){circles[i].x, circles[i].y};
                                Vector2 position2 =  (Vector2){circles[j].x, circles[j].y};
                                Vector2 position3 =  (Vector2){circles[k].x, circles[k].y};

                                Color randomColor;
                                randomColor.r = GetRandomValue(0, 255);
                                randomColor.g = GetRandomValue(0, 255);
                                randomColor.b = GetRandomValue(0, 255);
                                randomColor.a = 255;
                                //Vector2 v1, Vector2 v2,Vector2 v3, Color color
                                DrawTriangle(position1, position2, position3, randomColor);
                        }
                }
        }
}


void Update_Pos()
{
        for(int i = 0; i < NUM_CIRCLES; i++)
        {
                circles[i].x += circles[i].vx;
                circles[i].y += circles[i].vy;

        }
}

void Wall_Collision()
{

        for(int i = 0; i < NUM_CIRCLES; i++)
        {
                //left and rigth wall
                if(circles[i].x <= 0 || circles[i].x > WIN_W)
                {
                        circles[i].vx *= -1;
                }

                //top and bottom
                if(circles[i].y <= 0 || circles[i].y > WIN_H)
                {
                        circles[i].vy *= -1;
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
                //Draw_Lines();
                Draw_Triangles();
                Wall_Collision();
                Update_Pos();
                EndDrawing();
        }
        CloseWindow();

        return 0;
}

