#ifndef CAMERA_H
#define CAMERA_H


#include <iostream>
#include "glad.h"
#include "GameObject.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>



class Camera
{
public:
    GameObject gameObject;
    float transform[3] = {0,0,3.0f};float rotation[3] = {3.14,4.6,0};
    glm::vec3 direction;
    float dirR[2];
    float distanceY;
    //float rotation[3];
    bool mouseCommand = true;

    void initialize(bool mouseCommand_)
    {
        mouseCommand = mouseCommand_;
        for(int i=0;i<3;i++){gameObject.transform[i] = transform[i];}
        for(int i=0;i<3;i++){gameObject.rotation[i] = rotation[i];}
        
    }


    glm::mat4 camera(float yaw, float pitch)
    {
        yaw = 0;
        pitch = 0;

        glm::vec3 cameraPos   = glm::vec3(gameObject.transform[0],gameObject.transform[1],gameObject.transform[2]);
        glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
        glm::vec3 cameraUp    = glm::vec3(0.0f, 1.0f,  0.0f);

        processRotInput();
        distanceY = fabs(sin(gameObject.rotation[0]+1.57));
        //std::cout<<gameObject.rotation[0]<<"\n"<<distanceY<<"\n";
        
        direction.x = cos(gameObject.rotation[1]) * distanceY; 
        direction.y = sin(gameObject.rotation[0]);// * distanceY;
        direction.z = sin(gameObject.rotation[1]) * distanceY;
        cameraFront = glm::normalize(direction);
        //std::cout<<direction.x<<" "<<direction.y<<" "<<direction.z<<"\n\n\n";

        glm::mat4 view_;
        view_ = glm::lookAt(
        glm::vec3(cameraPos), 
  		glm::vec3(cameraPos + cameraFront), 
  		glm::vec3(cameraUp));

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
        else{
            calculateDir();
            velocity_[0] = direction.x * -velocity[2];
            velocity_[1] = 0;
            velocity_[2] = direction.z * -velocity[2];
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
        if(rot>4.71){   // I think it should be half
            gameObject.rotation[0] = 4.71;
        }
        else if(rot<1.57){
            gameObject.rotation[0] = 1.57;
        }
    }


    

    

};

Camera camera;


#endif