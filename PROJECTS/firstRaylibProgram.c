#include "raylib.h"

#define NUM_PARTICLES 10

typedef struct
{
        int r;
        int x;
        int y;
        int vx;
        int vy;
}Particle;

Particle particles[NUM_PARTICLES];


//initialize a particle
void initParticles()
{
        for(int i = 0; i < NUM_PARTICLES; i++)
        {
                particles[i].r = 10;
                particles[i].x = GetRandomValue(10, 790);
                particles[i].y = GetRandomValue(10, 590);
                particles[i].vx = 1;
                particles[i].vy = 1;
        }
}

void Draw_Particles()
{
        for(int i = 0; i < NUM_PARTICLES; i++)
        {
                DrawCircle(particles[i].x, particles[i].y, particles[i].r, RED);
        }
        //DrawCircle(Particles[i].x, Particles[i].y, Particles[i].r, RED);
}

void Update_Pos()
{
        for(int i = 0; i < NUM_PARTICLES; i++)
        {
                /*
                if(particles[i].x < 600 )
                {
                        particles[i].x -= particles[i].vx;
                }
                if(particles[i].x > 0)
                {
                        particles[i].x += particles[i].vx;
                }
                */
                particles[i].x += particles[i].vx;

                particles[i].y += particles[i].vy;
        }
}

void Wall_Collision()
{
        for(int i = 0; i < NUM_PARTICLES; i++)
        {
                // Left or right wall
                if(particles[i].x - particles[i].r <= 0 || particles[i].x + particles[i].r >= 800)
                {
                        particles[i].vx *= -1;  // Reverse horizontal velocity
                }

                //top or bottom
                if(particles[i].y - particles[i].r <= 0 || particles[i].y + particles[i].r >= 600)
                {
                        particles[i].vy *= -1; //reverse
                }

        }
}

void Circles_Collision()
{
    for (int i = 0; i < NUM_PARTICLES; i++)
    {
        for (int j = i + 1; j < NUM_PARTICLES; j++)
        {
            Vector2 a = { particles[i].x, particles[i].y };
            Vector2 b = { particles[j].x, particles[j].y };

            if (CheckCollisionCircles(a, particles[i].r,
                                      b, particles[j].r))
            {
                particles[i].vx *= -1;
                particles[i].vy *= -1;
                particles[j].vx *= -1;
                particles[j].vy *= -1;
            }
        }
    }
}

int main() {
    InitWindow(800, 600, "Hello Raylib");
    SetTargetFPS(60);
    initParticles();
    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(BLACK);
        // DrawText("Welcome to raylib!", 190, 200, 20, LIGHTGRAY);
        Update_Pos();
        Wall_Collision();
        Circles_Collision();
        Draw_Particles();
        EndDrawing();
    }

    CloseWindow();
    return 0;
}

//DrawCircle(int centerX, int centerY, float radius, Color color);
