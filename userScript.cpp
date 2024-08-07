#include <iostream>
#include <SDL2/SDL.h>
#include "glad.h"
#include "UI.h"
#include "renderer.h"
#include "GameObject.h"
#include "Camera.h"
#include "input.h"

void Boot(){

    
}







void Loop(){
    float transform__[3] = {0,0.01f,0};
    objectArray[0].force(transform__);

    float transform___[3] = {0,0,0.01};
    objectArray[1].force(transform___);

    
    
    




    



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


    //float rotation___[4] = {2.0,0.7,0.4,0.2};
    //objectArray[0].rotate(rotation___);
    //float rotation____[4] = {3.0,0.3,0.5,0};
    //objectArray[1].rotate(rotation____);
}