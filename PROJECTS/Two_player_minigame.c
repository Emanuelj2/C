#include <stdio.h>
#include <SDL2/SDL.h>
#include <stdbool.h>

#define WIN_H 800
#define WIN_W 800
#define SPEED 5
#define MAX_BULLETS 10
#define BULLET_W 2
#define BULLET_H 2
#define HEALTH_BAR_W 100
#define HEALTH_BAR_H 10

typedef enum
{
        OWNER_RED,
        OWNER_BLUE,
}BulletOwner;

typedef struct
{
        SDL_Rect rect;
        int vx;
        int vy;
        bool active;
        BulletOwner owner;
}Bullet;

typedef struct
{
        int current;
        int max;
}Health;

void init_bullets(Bullet bullets[])
{
        for(int i = 0; i < MAX_BULLETS; i++)
        {
                bullet.active = false;
                bullet[i].rect.y = 0;
                bullet[i].rect.x = 0;
                bullet[i].vy = 0;
                bullet[i].vx = 0;
                bullet[i].rect.w = BULLET_W;
                bullet[i].rect.h = BULLET_H;
        }
}

void shoot_bullet(Bullet bullet[], int x, int y, int vx, int vy, BulletOwner owner)
{
        for(int i = 0; i < MAX_BULLETS; i++)
        {
                if(!bullet[i].active)
                {
                        bullet[i].rect.x = x;
                        bullet[i].rect.y = y;
                        bullet[i].rect.vx = vx;
                        bullet[i].rect.vy = vy;
                        bullet[i].rect.active = true;
                        bullet->owner = owner;
                        break;
                }
        }
}

void update_bullet(Bullet bullets[])
{
        for(int i = 0; i < MAX_BULLETS; i++)
        {
                if(bullets[i].active)
                {
                        bullets[i].rect.x += bullets[i].vx;
                        bullets[i].rect.y += bullets[i].vy;

                        if(bullets[i].rect.x < 0 || bullets[i].rect.x > WIN_W ||
                                        bullets[i].rect.y < 0 || bullets[i].rect.y > WIN_H)
                        {
                                bullets[i].active = false;
                        }
                }
        }
}

void draw_bullets(SDL_Surface *surface, Bullet bullets[])
{
        for(int i = 0; i < MAX_BULLETS; i++)
        {
                if(bullets[i].active)
                {
                        SDL_FillRect(surface,
                                        &bullets[i].rect,
                                        SDL_MapRGB(surface->format, 255, 255, 255)
                                    );
                }
        }
}


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

void draw_player_health_bar(SDL_Surface *psurface, int x, int y, SDL_Rect *player, Health *health)
{
        if(health->current < 0)
        {
                health->current = 0;
        }

        float ratio = (float)health->current / health->max;

        SDL_Rect bg = {
                x,              //x position of health bar
                y,              //y position of health bar
                HEALTH_BAR_W,
                HEALTH_BAR_H
        };

        SDL_Rect fg = {
                x,              //x position of health bar
                y,              //y position of health bar
               (int)(HEALTH_BAR_W * ratio),
                HEALTH_BAR_H
        };

        //background (grey)
        SDL_FillRect(psurface, &bg, SDL_MapRGB(psurface->format, 80, 80, 80));

        //foreground (green)
        SDL_FillRect(psurface, &fg, SDL_MapRGB(psurface->format, 0, 255, 0));

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

    //health
    Health health1 = {100, 100};
    Health health2 = {100, 100};


    Bullet bullets[MAX_BULLETS];
    init_bullets(bullets);

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
        if(keys[SDL_SCANCODE_TAB])
        {
                shoot_bullet(bullets, rect1.x + rect1.w / 2, rect1.y + rect1.h / 2, 8, 0, OWNER_RED);
        }
        //blue player
        if(keys[SDL_SCANCODE_UP])       rect2.y -= SPEED;
        if(keys[SDL_SCANCODE_DOWN])     rect2.y += SPEED;
        if(keys[SDL_SCANCODE_LEFT])     rect2.x -= SPEED;
        if(keys[SDL_SCANCODE_RIGHT])    rect2.x += SPEED;
        if(keys[SDL_SCANCODE_SPACE])
        {
                shoot_bullet(bullets, rect2.x + rect2.w/2, rect2.y + rect2.h/2, -8, 0, OWNER_BLUE);
        }
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