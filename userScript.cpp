#include <iostream>
#include <SDL2/SDL.h>
#include "glad/glad.h"
#include "renderer.h"
#include "gameObject.h"
#include "camera.h"
#include "input.h"

void Boot(){

    
}







void Loop(){
    objectArray[0].force3(0,0,-0.005);

    objectArray[1].force3(0,0.01,0);


    objectArray[2].force3(0,0,0.02);

    objectArray[3].force3(0,0,0.03);

    



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









