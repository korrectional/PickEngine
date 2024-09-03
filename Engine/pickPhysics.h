#ifndef PICKPHYSICS
#define PICKPHYSICS


#include <iostream>
#include <SDL2/SDL.h>
#include "gameObject.h"
#include "camera.h"








float camCollisions[6];
void collisionLoop();
void goBackTransform(int i, int d, bool doit);




#endif