#include <iostream>
#include <SDL2/SDL.h>
#include "glad.h"
#include "UI.h"
#include "renderer.h"
#include "GameObject.h"
#include "Camera.h"
#include "input.h"

//#include "main.cpp"


void gameObjectCreation(){
    float transform[3] = {0.0f,0.0f,-3.0f};
    float rotation[4] = {0.0f,0.1f,0.0f,0.0f};
    GLfloat red[4] = {1.0f,1.0f,0.0f,1.0f}; 
    
    GLfloat orange[4] = {0.0f,0.2f,1.0f,0.7f};
    

    objectArray[gameObjectCount].create("CUBE1", transform, rotation, red, true, 0, nullptr, false);
    objectArray[gameObjectCount].create("CUBE2", transform, rotation, red, true, 1, nullptr, false);
    objectArray[gameObjectCount].create("CUBE3", transform, rotation, red, true, 0, nullptr, false); 
    objectArray[gameObjectCount].create("CUBE4", transform, rotation, red, true, 2, nullptr, false); 

    //objectArray[gameObjectCount].create("CUBE5", transform, rotation, red, true, 2, nullptr, false); 
    //objectArray[gameObjectCount].create("CUBE6", transform, rotation, red, true, 2, nullptr, false); 
    

    float transform_[3] = {0,0,1};
    objectArray[1].transformPos(transform_);
    transform_[0] = 0.2;
    transform_[1] = 0.3;
    transform_[2] = 2.7;
    objectArray[2].transformPos(transform_);
    transform_[2] = 8;
    objectArray[3].transformPos(transform_);
    

    
    GLfloat green[4] = {0,1.0f,0,1.0f};
    objectArray[0].setColor(green);
    objectArray[3].setColor(orange);
    GLfloat yellow[4] = {0,1.0f,0,1.0f};
    objectArray[1].setColor(yellow);







    GLfloat apricot[4] = {
        0.5f,0.5f,0.5f,0.5f
    }; 





}




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


void viewLoop(){




    // cam control
    camera.defaultCameraCommandLoop(upPressed,downPressed,leftPressed,rightPressed, 0.9, 0.9);
    if(wPressed == true){
        float transform____[3]={0,0,-0.1f};
        camera.force(transform____);
    }
    if(sPressed == true){
        float transform____[3]={0,0,0.1f};
        camera.force(transform____);
    }
    if(aPressed == true){
        float transform____[3]={-0.1f,0,0};
        camera.force(transform____);
    }
    if(dPressed == true){
        float transform____[3]={0.1f,0,0};
        camera.force(transform____);
    }
    if(spPressed == true){
        float transform____[3]={0,0.1f,0};
        camera.force(transform____);
    }
    if(shPressed == true){
        float transform____[3]={0,-0.1f,0};
        camera.force(transform____);
    }
}