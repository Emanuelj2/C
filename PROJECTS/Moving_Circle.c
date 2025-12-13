#include <SDL2/SDL.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#define WIN_H  800
#define WIN_W  700
#define PI 3.14

typedef struct
{
        int vx;
        int vy;
}Velocity;

typedef struct
{
        int x;
        int y;
        double radius;
        Velocity v;
        Uint32 color;
}Circle;

Circle init_circle(void)
{
        Circle c;
        c.x = WIN_W/2;
        c.y = WIN_H/2;
        c.radius = 10;
        c.v.vx = (rand() % 10) - 5;
        c.v.vy = (rand() % 10) - 5;
        c.color = SDL_MapRGB(SDL_AllocFormat(SDL_PIXELFORMAT_RGBA8888),
                rand() % 256, rand() % 256, rand() % 256);
        return c;
}

void draw_circle(SDL_Surface *surface, Circle *c)
{
        int cx = c->x;
        int cy = c->y;
        int r = (int)c->radius;

        for(int y = -r; y <= r; y++)
        {
                for(int x = -r; x <= r; x++)
                {
                        if(x * x + y * y <= r*r)
                        {
                                int px = cx + x;
                                int py = cy + y;
                                if(px >= 0 && px < WIN_W && py >= 0 && py < WIN_H)
                                {
                                        Uint32 *pixels = (Uint32*)surface->pixels;
                                        pixels[py * surface->w + px] = c->color;
                                }
                        }
                }

        }

}
//WRAP AROUND
void wrap_circle(Circle *c)
{
        //width
        if(c->x > WIN_W + c->radius)
        {
                c->x = -c->radius;
        }
        if(c->x < -c->radius)
        {
                c->x = WIN_W + c->radius;
        }

        //height
        if(c->y > WIN_H + c->radius)
        {
                c->x = -c->radius;
        }
        if(c->y < -c->radius)
        {
                c->y = WIN_H + c->radius;
        }
}



//CIRCLE MOVEMENT
void move_circle_up(SDL_Surface *surface, SDL_Window *window, Circle *c)
{
        Velocity v = (Velocity) {0, -1};
        for(int i = 0; i < 10; i++)
        {
                c->y += v.vy;
                wrap_circle(c);
                SDL_FillRect(surface, NULL, SDL_MapRGB(surface->format, 0, 0, 0));
                draw_circle(surface, c);
                SDL_UpdateWindowSurface(window);
        }
}
void move_circle_down(SDL_Surface *surface, SDL_Window *window, Circle *c)
{
        Velocity v = (Velocity) {0, 1};
        for(int i = 0; i < 10 ; i++)
        {

                c->y += v.vy;
                wrap_circle(c);
                SDL_FillRect(surface, NULL, SDL_MapRGB(surface->format, 0, 0, 0));
                draw_circle(surface, c);
                SDL_UpdateWindowSurface(window);
        }
}
void move_circle_left(SDL_Surface *surface, SDL_Window *window, Circle *c)
{
        Velocity v = (Velocity) {-1, 0};
        for(int i = 0; i < 10; i++)
        {
                c->x += v.vx;
                wrap_circle(c);
                SDL_FillRect(surface, NULL, SDL_MapRGB(surface->format, 0, 0, 0));
                draw_circle(surface, c);
                SDL_UpdateWindowSurface(window);
        }
}
void move_circle_right(SDL_Surface *surface, SDL_Window *window, Circle *c)
{
        Velocity v = (Velocity) {1, 0};
        for(int i = 0;i < 10; i++)
        {
                c->x += v.vx;
                wrap_circle(c);
                SDL_FillRect(surface, NULL, SDL_MapRGB(surface->format, 0,0,0));
                draw_circle(surface, c);
                SDL_UpdateWindowSurface(window);
        }
}
int main()//CIRCLE MOVEMENT
void move_circle_up(SDL_Surface *surface, SDL_Window *window, Circle *c)
{
        Velocity v = (Velocity) {0, -1};
        for(int i = 0; i < 10; i++)
        {
                c->y += v.vy;
                wrap_circle(&c);
                SDL_FillRect(surface, NULL, SDL_MapRGB(surface->format, 0, 0, 0));
                draw_circle(surface, c);
                SDL_UpdateWindowSurface(window);
        }
}
void move_circle_down(SDL_Surface *surface, SDL_Window *window, Circle *c)
{
        Velocity v = (Velocity) {0, 1};
        for(int i = 0; i < 10 ; i++)
        {

                c->y += v.vy;
                wrap_circle(&c);
                SDL_FillRect(surface, NULL, SDL_MapRGB(surface->format, 0, 0, 0));
                draw_circle(surface, c);
                SDL_UpdateWindowSurface(window);
        }
}
void move_circle_left(SDL_Surface *surface, SDL_Window *window, Circle *c)
{
        Velocity v = (Velocity) {-1, 0};
        for(int i = 0; i < 10; i++)
        {
                c->x += v.vx;
                SDL_FillRect(surface, NULL, SDL_MapRGB(surface->format, 0, 0, 0));
                draw_circle(surface, c);
                SDL_UpdateWindowSurface(window);
        }
}
{
        SDL_Window *window = SDL_CreateWindow("Physics Circle", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                        WIN_H, WIN_W, 0);
        SDL_Surface *surface = SDL_GetWindowSurface(window);

        Circle circle = init_circle();

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

                        if(event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_UP)
                        {
                                move_circle_up(surface, window, &circle);
                        }
                        if(event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_DOWN)
                        {
                                move_circle_down(surface, window, &circle);
                        }
                        if(event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_LEFT)
                        {
                                move_circle_left(surface, window, &circle);
                        }
                        if(event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_RIGHT)
                        {
                                move_circle_right(surface, window, &circle);
                        }

                        draw_circle(surface, &circle);

                        SDL_UpdateWindowSurface(window);
                        SDL_Delay(16); //60 fps
                }
        }
        return 0;
}