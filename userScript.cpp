#include <iostream>
#include <SDL2/SDL.h>
#include "glad.h"
#include "UI.h"
#include "renderer.h"
#include "GameObject.h"
#include "Camera.h"
#include "input.h"


void gameObjectCreation(){
    float transform[3] = {
        0.0f,0.0f,-3.0f
    };


    float rotation[4] = {
        0.0f,0.0f,0.0f,0.0f
    }; // rotation[0] is degrees

    GLfloat red[4] = {
        1.0f,1.0f,0.0f,1.0f
    }; 
    

    // Scene Objects
    //objectArray[0].create()
    //objectArray[1].create()
    objectArray[0].create("cube1", transform, rotation, red, 36*5, true);
    objectArray[1].create("cube2", transform, rotation, red, 36*5, true);

}




void Boot(){
    // What are the gameObjects!
    //objectArray[0].create();




    float transform[3]{0.0f,0.0f,-3.0f};
    float rotation[4]{30.0f,1.0f,1.0f,0.0f};
    float rotate = 0;

    
    
    // Object positions
    float transform_[3] = {0,0,-6.0f};
    objectArray[0].transformPos(transform_);
    float transform__[3] = {0.4,0.5,-3.0f};
    objectArray[1].transformPos(transform__);
    float rotation_[4] = {30.0f,0,1.0f,0};
    objectArray[0].rotationPos(rotation_);
    float rotation__[4] = {30.0f,0,1.0f,0};
    objectArray[1].rotationPos(rotation__);
    float transform___[3] = {0,0,0};
    UIObjectArray[0].transformPos(transform___);

    //texObject1.transformPos(transform___);


        
    float rotation___[4] = {5.0f,1.0f,0,0};
    objectArray[0].rotate(rotation___);
    float rotation____[4] = {10.0f,0.7f,0,0};
    objectArray[1].rotate(rotation____);
    GLfloat green[4] = {0,1.0f,0,1.0f};
    objectArray[0].setColor(green);
    GLfloat yellow[4] = {1.0f,1.0f,0,1.0f};
    objectArray[1].setColor(yellow);
    GLfloat grey[4] = {0.5f,0.5f,0.5f,0.5f};
    UIObjectArray[0].setColor(grey);
    //texObject1.setColor(grey);


    // set cam
    //float rotate____[3] = {2.5f,2.5f,0};
    //camera.gameObject.rotationPos(rotate____);



    



}
void Loop(){
    float transform__[3] = {0,0.01f,0};
    objectArray[0].force(transform__);


    camera.defaultCameraCommandLoop(upPressed,downPressed,leftPressed,rightPressed);
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


    float rotation___[4] = {2.0,0.7,0.4,0.2};
    objectArray[0].rotate(rotation___);
    float rotation____[4] = {3.0,0.3,0.5,0};
    objectArray[1].rotate(rotation____);
    GLfloat green[4] = {0,1.0f,0,1.0f};
}