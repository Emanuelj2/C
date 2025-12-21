#include <SDL2/SDL.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#define WIN_W 800
#define WIN_H 600
#define SPEED 4

typedef struct
{
    int vx;
    int vy;
} Velocity;

typedef struct
{
    int x;
    int y;
    double radius;
    Velocity v;
    Uint32 color;
} Circle;

typedef struct
{
    int x;
    int y;
    int base;
    int height;
    Velocity v;
    Uint32 color;
} Rectangle;

static double clamp(double v, double min, double max)
{
    if (v < min) return min;
    if (v > max) return max;
    return v;
}

void draw_rect(SDL_Surface *surface, Rectangle *r)
{
    SDL_Rect rect = { r->x, r->y, r->base, r->height };
    SDL_FillRect(surface, &rect, r->color);
}

void wrap_circle(Circle *c)
{
    if (c->x > WIN_W + c->radius)  c->x = -c->radius;
    if (c->x < -c->radius)         c->x = WIN_W + c->radius;
    if (c->y > WIN_H + c->radius)  c->y = -c->radius;
    if (c->y < -c->radius)         c->y = WIN_H + c->radius;
}

Circle init_circle(SDL_Surface *surface)
{
    Circle c;
    c.x = WIN_W / 2;
    c.y = WIN_H / 2;
    c.radius = 12;
    c.v.vx = 0;
    c.v.vy = 0;
    c.color = SDL_MapRGB(surface->format, 0, 255, 0);
    return c;
}

Rectangle init_rect(SDL_Surface *surface)
{
    Rectangle r;
    r.x = 200;
    r.y = 200;
    r.base = 100;
    r.height = 60;
    r.v.vx = 0;
    r.v.vy = 0;
    r.color = SDL_MapRGB(surface->format, 255, 255, 255);
    return r;
}

void draw_circle(SDL_Surface *surface, Circle *c)
{
        if (SDL_MUSTLOCK(surface))
        SDL_LockSurface(surface);

    Uint32 *pixels = (Uint32 *)surface->pixels;

    for (int y = -c->radius; y <= c->radius; y++)
    {
        for (int x = -c->radius; x <= c->radius; x++)
        {
            if (x*x + y*y <= c->radius * c->radius)
            {
                int px = c->x + x;
                int py = c->y + y;

                if (px >= 0 && px < WIN_W && py >= 0 && py < WIN_H)
                {
                    pixels[py * surface->w + px] = c->color;
                }
            }
        }
    }

    if (SDL_MUSTLOCK(surface))
        SDL_UnlockSurface(surface);
}

int circle_rect_collision(Circle *c, Rectangle *r)
{
    double closestX = clamp(c->x, r->x, r->x + r->base);
    double closestY = clamp(c->y, r->y, r->y + r->height);

    double dx = c->x - closestX;
    double dy = c->y - closestY;

    return (dx*dx + dy*dy) <= (c->radius * c->radius);
}

void update_rect(Rectangle *r, Circle *c)
{
        if(!circle_rect_collision(c, r))
                return;
        //push rect by circle velovity
        r->x += c->v.vx;
        r->y += c->v.vy;
}


int main(void)
{
    SDL_Init(SDL_INIT_VIDEO);
    srand(time(NULL));

    SDL_Window *window = SDL_CreateWindow(
        "Circle–Rectangle Collision",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        WIN_W, WIN_H,
        0
    );

    SDL_Surface *surface = SDL_GetWindowSurface(window);

    Circle circle = init_circle(surface);
    Rectangle rect = init_rect(surface);

    int running = 1;

    while (running)
    {
        SDL_Event event;

        /* ---- INPUT ---- */
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
                running = 0;
        }

        const Uint8 *keys = SDL_GetKeyboardState(NULL);

        //reset velocity each frame
        circle.v.vx = 0;
        circle.v.vy = 0;

        if (keys[SDL_SCANCODE_UP])    circle.v.vy -= SPEED;
        if (keys[SDL_SCANCODE_DOWN])  circle.v.vy += SPEED;
        if (keys[SDL_SCANCODE_LEFT])  circle.v.vx -= SPEED;
        if (keys[SDL_SCANCODE_RIGHT]) circle.v.vx += SPEED;

        //apply velocity
        circle.x += circle.v.vx;
        circle.y += circle.v.vy;

        wrap_circle(&circle);

        /* ---- COLLISION ---- */
        if (circle_rect_collision(&circle, &rect))
        {
            circle.color = SDL_MapRGB(surface->format, 255, 0, 0);
            update_rect(&rect, &circle);
        }
        else
        {
            circle.color = SDL_MapRGB(surface->format, 0, 255, 0);
        }

        /* ---- RENDER ---- */
        SDL_FillRect(surface, NULL,
            SDL_MapRGB(surface->format, 0, 0, 0));

        draw_circle(surface, &circle);
        draw_rect(surface, &rect);

        SDL_UpdateWindowSurface(window);
        SDL_Delay(16);
    }

    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}