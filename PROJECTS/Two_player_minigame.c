#include <stdio.h>
#include <SDL2/SDL.h>
#include <stdbool.h>

#define WIN_H 800
#define WIN_W 800

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