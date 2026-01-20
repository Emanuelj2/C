#ifndef INSTRUMENTS_H
#define INSTRUMENTS_H

#include <SDL2/SDL.h>
#include "Aircraft.h"

class Instruments {
public:
    Instruments(SDL_Renderer* renderer);
    
    void drawAttitude(double pitch);
    void drawAltitude(double altitude);
    void drawSpeed(double airspeed);
    
private:
    SDL_Renderer* renderer;
};

#endif 
