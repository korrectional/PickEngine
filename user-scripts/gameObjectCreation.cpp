/*


This is a temporary file for loading the debug world. Its used because its more flexible than save files, since due to updates their formats might
be often changed and therefore prove inconvinient for debug purposes.


*/





#include <iostream>
#include <SDL2/SDL.h>
#include "../third-party/glad/glad.h"
#include "../Engine/gameObject.h"




void gameObjectCreation(){
    float transform[3] = {0.0f,0.0f,-3.0f};
    float transformSun[3] = {10.0f,10.0f,10.0f};
    float rotation[4] = {0.0f,0.1f,0.0f,0.0f};
    GLfloat red[4] = {1.0f,1.0f,0.0f,1.0f}; 
    
    GLfloat orange[4] = {0.0f,0.2f,1.0f,0.7f};
    
    objectArray[gameObjectCount].create("light", transformSun, rotation, red, "", false, 0);
    objectArray[gameObjectCount].create("cube1", transform, rotation, red, "", true, 0);
    objectArray[gameObjectCount].create("cube2", transform, rotation, red, "", true, 1);
    objectArray[gameObjectCount].create("cube3", transform, rotation, red, "", true, 0); 
    objectArray[gameObjectCount].create("cube4", transform, rotation, red, "", true, 2); 

    

    float transform_[3] = {0,0,1};
    objectArray[2].transformPos(transform_);
    transform_[0] = 0.2;
    transform_[1] = 0.3;
    transform_[2] = 2.7;
    objectArray[3].transformPos(transform_);
    transform_[2] = 8;
    objectArray[4].transformPos(transform_);
    

    
    GLfloat green[4] = {0,1.0f,0,1.0f};
    objectArray[1].setColor(green);
    objectArray[4].setColor(orange);
    GLfloat yellow[4] = {0,1.0f,0,1.0f};
    objectArray[2].setColor(yellow);







    GLfloat apricot[4] = {
        0.5f,0.5f,0.5f,0.5f
    }; 





}