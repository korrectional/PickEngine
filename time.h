#ifndef TIME
#define TIME


#include <iostream>
#include <SDL2/SDL.h>


struct Time
{
private:
    int lastTicks;
    int ticks;
public:
    int delta;

    void tick(){
        ticks = SDL_GetTicks();
        delta = ticks - lastTicks;
        lastTicks = ticks;
    }

    int returnTick(){
        ticks = SDL_GetTicks();
        return ticks - lastTicks;
    }
};

Time timeClock;





#endif