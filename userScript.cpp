#include <iostream>
#include <SDL2/SDL.h>
#include "glad.h"
#include "UI.h"
#include "renderer.h"
#include "GameObject.h"
#include "Camera.h"
#include "input.h"


void gameObjectCreation(){
    float transform[3] = {0.0f,0.0f,-3.0f};
    float rotation[4] = {0.0f,0.1f,0.0f,0.0f}; // rotation[0] is degrees
    GLfloat red[4] = {1.0f,1.0f,0.0f,1.0f}; 
    

    // Scene Objects
    objectArray[0].create("cube1", transform, rotation, red, true, false);
    objectArray[1].create("cube1", transform, rotation, red, true, false);
    objectArray[2].create("cube1", transform, rotation, red, true, false);
    //for(int i=2;i<100;i++){
    //    objectArray[i].create("cube1", transform, rotation, red, 36*5, true);
    //}
    float transform_[3] = {0,0,1};
    objectArray[1].transformPos(transform_);
    transform_[0] = 0.2;
    transform_[1] = 0.3;
    transform_[2] = 2.7;
    objectArray[2].transformPos(transform_);
    

    
    GLfloat green[4] = {0,1.0f,0,1.0f};
    objectArray[0].setColor(green);
    GLfloat grey[4] = {0.5f,0.5f,0.5f,0.5f};
    UIObjectArray[0].setColor(grey);


    //for(int i=0;i<100;i++){
    //    float transform_[3] = {0,0+cos(float(i)),-6.0f-float(i)};
    //    objectArray[i].transformPos(transform_);
    //}
    // /float transform__[3] = {0.4,0.5,-3.0f};
    //objectArray[1].transformPos(transform__);

}




void Boot(){
    // Object positions
    float transform___[3] = {0,0,0};
    UIObjectArray[0].transformPos(transform___);

    
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