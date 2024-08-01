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
    float transform[3] = {0,0,3.0f};float rotation[3] = {0,0,0};
    glm::vec3 direction;
    float dirR[2];
    //float rotation[3];

    void initialize()
    {
        for(int i=0;i<3;i++){gameObject.transform[i] = transform[i];}
        for(int i=0;i<3;i++){gameObject.rotation[i] = rotation[i];}
    }


    glm::mat4 camera(float yaw, float pitch)
    {
        yaw = 0;
        pitch = 0;
        //camX = camX + 0.01;
        //camZ = camZ + 0.01;
        //glm::vec3 cameraPos = glm::vec3(0,0,3);
        //glm::vec3 cameraTarget = glm::vec3(0,0,0);
        //glm::vec3 cameraDirection = glm::normalize(cameraPos - cameraTarget);
        //glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f); 
        //glm::vec3 cameraRight = glm::normalize(glm::cross(up, cameraDirection));
        //glm::vec3 cameraUp = glm::cross(cameraDirection, cameraRight);
        glm::vec3 cameraPos   = glm::vec3(gameObject.transform[0],gameObject.transform[1],gameObject.transform[2]);
        glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
        glm::vec3 cameraUp    = glm::vec3(0.0f, 1.0f,  0.0f);

//gameObject.rotation[0];//
//gameObject.rotation[0];//
//gameObject.rotation[2];//
        std::cout<<gameObject.rotation[1]<<"\n";
        
        
        direction.x = cos(gameObject.rotation[1]);// * cos(glm::radians(pitch));
        direction.y = 0.0f;//sin(glm::radians(pitch));
        direction.z = sin(gameObject.rotation[1]);//sin(glm::radians(gameObject.rotation[1]));// * cos(glm::radians(pitch));
        cameraFront = glm::normalize(direction);

        glm::mat4 view_;
        view_ = glm::lookAt(
        glm::vec3(cameraPos), 
  		glm::vec3(cameraPos + cameraFront), 
  		glm::vec3(cameraUp));

        return view_;
    }


    void force(float velocity[3])
    {
        float velocity_[3];
        for(int i=0;i<3;i++){std::cout<<velocity[i]<<"\n";}
        if(velocity[0]!=0){
            std::cout<<"BAD";
            calculateDirR();
            velocity_[0] = dirR[0] * -velocity[0];
            velocity_[1] = 0;
            velocity_[2] = dirR[1] * -velocity[0];
        }
        else{
            velocity_[0] = direction.x * -velocity[2];
            velocity_[1] = 0;
            velocity_[2] = direction.z * -velocity[2];
        }
        for(int i=0;i<3;i++){std::cout<<velocity_[i]<<": "<<velocity[i]<<"\n";}
        gameObject.force(velocity_);
    }


    void calculateDirR()
    {
        dirR[0] = cos(gameObject.rotation[1]-1.5);
        dirR[1] = sin(gameObject.rotation[1]-1.5);
    }


    

    

};

Camera camera;


#endif