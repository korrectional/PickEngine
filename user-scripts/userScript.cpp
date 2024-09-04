#include <iostream>
#include <SDL2/SDL.h>
#include "../third-party/glad/glad.h"
#include "../Engine/renderer.h"
#include "../Engine/gameObject.h"
#include "../Engine/camera.h"
#include "../Events/input.h"

void Boot(){

    
}







void Loop(){
    objectArray[0].force3(0,0,-0.005);
    objectArray[GAMEOBJECT::tryFind("cube1")].force3(0,0.01,0);
    objectArray[GAMEOBJECT::tryFind("cube2")].force3(0,0,0.02);
    objectArray[GAMEOBJECT::tryFind("cube3")].scale3(1.01,1.01,1.01);

    



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









