#ifndef CAMERA_H
#define CAMERA_H


#include <iostream>
#include "glad.h"
#include "GameObject.h"
#include "PickPhysics.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>



class Camera
{
private:
    float omX=0, omY=0;
    float olXweid = 0;
    float camZ = 3;
    float dmX;
    float dmY;
    int mX, mY;
    float i = 0;    
    float transform[3] = {0,0,3.0f};float rotation[3] = {3.14,4.6,0};
    float sX, sY;
    float dirR[2];
    float distanceY;
    glm::vec3 direction;

    glm::vec3 cameraPos;
    glm::vec3 cameraFront;
    glm::vec3 cameraUp;
    glm::mat4 view_;
    float y2val;

    


public:
    GameObject gameObject;
    bool mouseCommand = true;

    void initialize(bool mouseCommand_, float sX_, float sY_)
    {
        sX=sX_;sY=sY_;
        mouseCommand = mouseCommand_;
        for(int i=0;i<3;i++){gameObject.transform[i] = transform[i];}
        for(int i=0;i<3;i++){gameObject.rotation[i] = rotation[i];}
        
    }


    glm::mat4 camera()
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


    void force(float velocity[3]) // for directional movement
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


    void calculateDirR() // for directional movement
    {
        dirR[0] = cos(gameObject.rotation[1]-1.5);
        dirR[1] = sin(gameObject.rotation[1]-1.5);
    }

    void calculateDir() // for directional movement
    {
        dirR[0] = cos(gameObject.rotation[1]);
        dirR[1] = sin(gameObject.rotation[1]);
    }

    void processRotInput() // X rotation (up n'down)
    {
        float rot = gameObject.rotation[0];
        if(rot>4.71){
            gameObject.rotation[0] = 4.71;
        }
        else if(rot<1.57){
            gameObject.rotation[0] = 1.57;
        }
    }


    void defaultCameraCommandLoop(bool upPressed, bool downPressed, bool leftPressed, bool rightPressed, float sensX, float sensY){
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


    

    

};

Camera camera;


#endif