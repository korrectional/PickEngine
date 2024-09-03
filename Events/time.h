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

    void tick();

    int returnTick();
};

Time timeClock;





#endif