#ifndef CAMERA_H
#define CAMERA_H


#include <iostream>
#include "../third-party/glad/glad.h"
#include "gameObject.h"
//#include "PickPhysics.h"

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

    void initialize(bool mouseCommand_, float sX_, float sY_);


    glm::mat4 camera();

    void force(float velocity[3]);


    void calculateDirR(); 

    void calculateDir();

    void processRotInput();


    void defaultCameraCommandLoop(bool upPressed, bool downPressed, bool leftPressed, bool rightPressed, float sensX, float sensY);


    

    

};

Camera camera;


#endif