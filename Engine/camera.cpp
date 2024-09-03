#include <iostream>
#include "camera.h"


void Camera::initialize(bool mouseCommand_, float sX_, float sY_)
{
    gameObject.createCamera();
    sX=sX_;sY=sY_;
    mouseCommand = mouseCommand_;
    for(int i=0;i<3;i++){gameObject.transform[i] = transform[i];}
    for(int i=0;i<3;i++){gameObject.rotation[i] = rotation[i];}   
}



glm::mat4 Camera::camera()
{
    cameraPos   = glm::vec3(gameObject.transform[0],gameObject.transform[1],gameObject.transform[2]);
    cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
    cameraUp    = glm::vec3(0.0f, 1.0f,  0.0f);
    processRotInput();
    distanceY = fabs(sin(gameObject.rotation[0]+1.57));
    
    direction.x = cos(gameObject.rotation[1]) * distanceY; 
    direction.y = sin(gameObject.rotation[0]);// * distanceY;
    direction.z = sin(gameObject.rotation[1]) * distanceY;
    cameraFront = glm::normalize(direction);
    view_;
    view_ = glm::lookAt(
    cameraPos, 
	glm::vec3(cameraPos + cameraFront), 
	cameraUp);
    return view_;
}



void Camera::force(float velocity[3]) // for directional movement
{
    float velocity_[3];
    if(velocity[0]!=0){
        calculateDirR();
        velocity_[0] = dirR[0] * -velocity[0];
        velocity_[1] = 0;
        velocity_[2] = dirR[1] * -velocity[0];
    }
    else if(velocity[1]!=0){
        velocity_[1] = velocity[1];
    }
    else{
        calculateDir();
        velocity_[0] = dirR[0] * -velocity[2];
        velocity_[1] = 0;
        velocity_[2] = dirR[1] * -velocity[2];
    }
    gameObject.force(velocity_);
}


void Camera::calculateDirR()
{
    dirR[0] = cos(gameObject.rotation[1]-1.5);
    dirR[1] = sin(gameObject.rotation[1]-1.5);
}


void Camera::calculateDir() // for directional movement
{
    dirR[0] = cos(gameObject.rotation[1]);
    dirR[1] = sin(gameObject.rotation[1]);
}


void Camera::processRotInput() // X rotation (up n'down)
{
    float rot = gameObject.rotation[0];
    if(rot>4.71){
        gameObject.rotation[0] = 4.71;
    }
    else if(rot<1.57){
        gameObject.rotation[0] = 1.57;
    }
}


void Camera::defaultCameraCommandLoop(bool upPressed, bool downPressed, bool leftPressed, bool rightPressed, float sensX, float sensY){
    if(mouseCommand == true){
        SDL_GetMouseState(&mX, &mY);
        if(olXweid==0){omX=mX;omY=mY;olXweid=1;}
        dmX = (mX-omX)*0.01;
        dmY = (mY-omY);
        omX = mX; omY = mY;
    }
    else{
        dmY = 0;
        dmX = 0;
        if(upPressed){
            dmY = -4*sensY;
        }
        if(downPressed){
            dmY = 4*sensY;
        }
        if(leftPressed){
            dmX = -0.05*sensX;
        }
        if(rightPressed){
            dmX = 0.05*sensX;
        }
    }
    y2val = dmY*3.14/sY;
    float rotate____[3]={y2val,dmX,0};
    gameObject.rotate(rotate____);
}


    

