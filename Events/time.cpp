
#include "time.h"


void Time::tick(){
    ticks = SDL_GetTicks();
    delta = ticks - lastTicks;
    lastTicks = ticks;
}

int Time::returnTick(){
    ticks = SDL_GetTicks();
    return ticks - lastTicks;
}

