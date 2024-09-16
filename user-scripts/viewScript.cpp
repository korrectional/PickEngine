#include <iostream>
#include <SDL2/SDL.h>
#include "../third-party/glad/glad.h"
#include "../Engine/renderer.h"
#include "../Engine/gameObject.h"
#include "../Engine/camera.h"
#include "../Events/input.h"







void viewBoot(){
    // Object positions

}



int lMousePressedFrames;
void viewConLoop(){
    






    float playButtonLoc[4] = {
        0,0,
        65,25
    };
    float soonButtonLoc[4] = {
        435,0,
        500,25
    };




    // no-hold
    if(lMousePressed){
        lMousePressedFrames++;
        if(lMousePressedFrames == 1){
            //input.ButtonLogic(input.event, playButtonLoc, 0);
            //input.ButtonLogic(input.event, soonButtonLoc, 1);
        }
    }
    else{
        lMousePressedFrames = 0;
    }
}

float speed = 0.2f;

void viewLoop(){



    // cam control
    camera.defaultCameraCommandLoop(upPressed,downPressed,leftPressed,rightPressed, 0.9, 0.9);
    if(wPressed == true){
        float transform____[3]={0,0,-0.1f*speed};
        camera.force(transform____);
    }
    if(sPressed == true){
        float transform____[3]={0,0,0.1f*speed};
        camera.force(transform____);
    }
    if(aPressed == true){
        float transform____[3]={-0.1f*speed,0,0};
        camera.force(transform____);
    }
    if(dPressed == true){
        float transform____[3]={0.1f*speed,0,0};
        camera.force(transform____);
    }
    if(spPressed == true){
        float transform____[3]={0,0.1f*speed,0};
        camera.force(transform____);
    }
    if(shPressed == true){
        float transform____[3]={0,-0.1f*speed,0};
        camera.force(transform____);
    }
}