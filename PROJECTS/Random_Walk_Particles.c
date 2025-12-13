#include <SDL2/SDL.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#define WIN_W 800
#define WIN_H 800
#define MAX_SPEED 2

typedef struct
{
        int vx;
        int vy;
}Velocity;

typedef struct
{
        int x;
        int y;
        Velocity v;
        Uint32 color;
}Particle;

//random velocity
Velocity random_velocity(void)
{
        Velocity v;
        v.vx = (rand() % (2 * MAX_SPEED + 1)) - MAX_SPEED;
        v.vy = (rand() % (2 * MAX_SPEED + 1)) - MAX_SPEED;
        return v;
}

//initialize particle
void init_particles(Particle *p, int count)
{
        for(int i =0; i < count; i++)
        {
                p[i].x = rand() % WIN_W;
                p[i].y = rand() % WIN_H;
                p[i].v = random_velocity();
                p[i].color = rand();
        }
}

//move particle and handel wall collision
void update_particle(Particle *p)
{
        p->x += p->v.vx;
        p->y += p->v.vy;

        if(p->x <= 0 || p->x >= WIN_W)
        {
                p->v.vx *= -1; //opposite direction
        }
        if(p->y <= 0 || p->y >= WIN_H)
        {
                p->v.vy *= -1;
        }
}


//draw the particle
void draw_particle(SDL_Surface *surface, Particle *p)
{
        SDL_Rect rect = {p->x, p->y, 2, 2};
        SDL_FillRect(surface, &rect, p->color);
}


int main(int argc, char** argv)
{
        int count = (argc == 2)? atoi(argv[1]) : 50;

        srand(time(NULL));


        SDL_Window *window = SDL_CreateWindow("partical simulation",
                        SDL_WINDOWPOS_CENTERED,
                        SDL_WINDOWPOS_CENTERED,
                        WIN_W,
                        WIN_H,
                        0);
        SDL_Surface *surface = SDL_GetWindowSurface(window);

        Particle *particles = malloc(sizeof(Particle) * count);
        init_particles(particles, count);

        int running = 1;

        while(running)
        {
                SDL_Event event;
                while(SDL_PollEvent(&event))
                {
                        if(event.type == SDL_QUIT)
                        {
                                running = 0;
                        }
                }
                for(int i = 0; i < count;i++)
                {
                        update_particle(&particles[i]);
                        draw_particle(surface, &particles[i]);
                }
                SDL_UpdateWindowSurface(window);
                SDL_Delay(16); //60 fps

        }
        free(particles);

        SDL_DestroyWindow(window);
        SDL_Quit();
        return 0;
}