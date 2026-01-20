#include <SDL.h> //initializing shut down functions
#include <SDL2/SDL_image.h> //rendering images and graphics
#include <SDL2/SDL_timer.h> //for using SDL_Delay()
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#define WIN_HEIGHT 800
#define WIN_WIDTH 800
#define SCALE 10
#define AGENT_SIZE 2

typedef struct
{
    int x_start, x_end, y_start, y_end;
}Line;

typedef struct
{
    int vx, vy;
}Velocity;

typedef struct
{
    int x, y;
    Uint32 color;
}Agent;

Velocity get_rand_velocity()
{
        int choice = rand()/(RAND_MAX/4);
        switch(choice) //{x, y}
        {
            case 0: //up
                return (Velocity) {0, -1};
            case 1: //down
                return (Velocity) {0, 1};
            case 2: //left
                return (Velocity) {-1, 0};
            case 3:
                return (Velocity) {1, 0};
        }
        fprintf(stderr, "Impossible random value %d encoutered\n", choice);
        exit(-1);
}

void create_agents(Agent *pagents,int num_of_agents)
{
    for(int i = 0; i < num_of_agents; i++)
    {
        Uint32 color = rand();
        pagents[i] = (Agent) {WIN_WIDTH/2, WIN_HEIGHT/2, color};
    }
}

void move_agent(SDL_Surface *psurface, SDL_Window *win ,Agent *pagent)
{

    Velocity v = get_rand_velocity();
    for(int i = 0; i < SCALE; i++)
    {
        pagent->x += v.vx;
        pagent->y += v.vy;
        SDL_Rect rect = (SDL_Rect) {pagent->x, pagent->y, AGENT_SIZE, AGENT_SIZE};
        SDL_FillRect(psurface, &rect, pagent->color);
        SDL_UpdateWindowSurface(win);
    }
}

int main(int argc, char **argv)
{

    int num_of_agents;
    if(argc == 1)
    {
        num_of_agents = 5;
    }
    else if(argc == 2)
    {
        num_of_agents = atoi(argv[1]);
    }
    else
    {
        printf("Usage: %s <num of agents>\n", argv[0]);
    }



    SDL_Window* win = SDL_CreateWindow("Window", SDL_WINDOWPOS_CENTERED,
                    SDL_WINDOWPOS_CENTERED, WIN_HEIGHT, WIN_WIDTH, 0);
    SDL_Surface *psurface = SDL_GetWindowSurface(win);

    //we can draw something on the serface
    //SDL_Rect rect = (SDL_Rect) {WIN_HEIGHT/2, WIN_WIDTH/2, 2, 2};
    //SDL_FillRect(psurface, &rect, 0xFFFFFF);
    //SDL_UpdateWindowSurface(win);
    Agent *pagents = calloc(num_of_agents, sizeof(Agent));
    //Agent agent0 = (Agent){WIN_HEIGHT/2, WIN_WIDTH/2, 0xFFFFFF};


    //create multiple agents
    create_agents(pagents, num_of_agents);
    int run = 1;


    while(run)
    {
        SDL_Event event;

        while(SDL_PollEvent(&event))
        {
            if(event.type == SDL_QUIT)
            {
                run = 0;
            }
        }

        for(int i = 0; i < num_of_agents; i++)
        {
            move_agent(psurface, win, &pagents[i]);
        }

        //move_agent(psurface, win, &agent0);

        SDL_Delay(20); //20fps
    }
    free(pagents);
    return 0;
}
