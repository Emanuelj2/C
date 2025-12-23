#include <stdio.h>
#include <SDL2/SDL.h>
#include <stdbool.h>

#define WIN_H 800
#define WIN_W 800
#define SPEED 5

//rect stops at the window edges
void clamp_player(SDL_Rect *r)
{
        if(r->x < 0) r->x = 0;
        if(r->y < 0) r->y = 0;

        if(r->x + r->w > WIN_W) r->x = WIN_W - r->w;
        if(r->y + r->h > WIN_H) r->y = WIN_H - r->h;
}
//collision detection
bool check_collision(SDL_Rect *rect1, SDL_Rect *rect2)
{
        return SDL_HasIntersection(rect1, rect2);
}

int main()
{
    SDL_Window *pwindow = SDL_CreateWindow(
        "two_players",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        WIN_W,
        WIN_H,
        0
    );

    SDL_Surface *psurface = SDL_GetWindowSurface(pwindow);

    // create the rect
    SDL_Rect rect1 = {50, 50, 20, 20};
    SDL_Rect rect2 = {750, 750, 20, 20};

    bool running = true;
    while(running)
    {
        SDL_Event event;
        while(SDL_PollEvent(&event))
        {
            if(event.type == SDL_QUIT)
                running = false;
        }

        int old_x1 = rect1.x;
        int old_y1 = rect1.y;
        int old_y2 = rect2.y;
        int old_x2 = rect2.x;
        
        const Uint8 *keys = SDL_GetKeyboardState(NULL);
        //red player
        if(keys[SDL_SCANCODE_W])        rect1.y -= SPEED;
        if(keys[SDL_SCANCODE_S])        rect1.y += SPEED;
        if(keys[SDL_SCANCODE_A])        rect1.x -= SPEED;
        if(keys[SDL_SCANCODE_D])        rect1.x += SPEED;
        //blue player
        if(keys[SDL_SCANCODE_UP])       rect2.y -= SPEED;
        if(keys[SDL_SCANCODE_DOWN])     rect2.y += SPEED;
        if(keys[SDL_SCANCODE_LEFT])     rect2.x -= SPEED;
        if(keys[SDL_SCANCODE_RIGHT])    rect2.x += SPEED;

        clamp_player(&rect1);
        clamp_player(&rect2);

        if(check_collision(&rect1, &rect2))
        {
                rect1.x = old_x1;
                rect1.y = old_y1;
                rect2.x = old_x2;
                rect2.y = old_y2;
        }


        // Draw background black
        SDL_FillRect(psurface, NULL, SDL_MapRGB(psurface->format, 0, 0, 0));

        // Draw rectangle red
        SDL_FillRect(psurface, &rect1, SDL_MapRGB(psurface->format, 255, 0, 0));
        //Draw rectangle blue
        SDL_FillRect(psurface, &rect2, SDL_MapRGB(psurface->format, 0, 0, 255));

        // Update window
        SDL_UpdateWindowSurface(pwindow);

        SDL_Delay(16);
    }

    SDL_DestroyWindow(pwindow);
    SDL_Quit();

    return 0;
}