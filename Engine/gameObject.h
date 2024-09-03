#ifndef GAMEOBJECT
#define GAMEOBJECT


#include <iostream>
#include <string>
#include <cstdlib>  
#include <vector>
#include "../third-party/glad/glad.h"
#include "../Tools/objProcessor.h"
#include "../assets/defaultCubeArray.h"



bool playing;

int gameObjectCount = 0;
int UIObjectCount = 0;




class GameObject
{
private:
    GLuint VAO;
    //int VAOnum;
    int pointCount;
    int viewLoc;
    glm::mat4 model;
    glm::mat4 view;
    int modelLoc;
    int colorLoc;
    int locVAO;
    int locVBO;

public:    
    std::string name;
    bool textured;
    GLfloat color[3] = {0,0,0};
    int reflectivness = 16;

    float transform[3] = {0,0,0};
    float rotation[4] = {0,0.1,0,0};
    float scaleValue[3] = {1,1,1};
    int texNum;
    GLfloat vertices[288];

    bool collisionsEnabled = true;
    bool isTrigger = false;
    bool enabled = true;

    float initCollisionBox[6] = {
        0.5,-0.5,//x
        0.5,-0.5,//y
        0.5,-0.5//z
    };
    float scaledCollisionBox[6] = {
        0.5,-0.5,//x
        0.5,-0.5,//y
        0.5,-0.5//z
    };
    float collisionBox[6] = {
        0.5,-0.5,//x
        0.5,-0.5,//y
        0.5,-0.5 //z
    };
    



    
    void create(std::string name_, float transform_[3], float rotation_[4], GLfloat color_[3], bool textured_, int texNum_ , float scale_[3] = nullptr, float* initCollisionBox_ = nullptr ,bool collisionsEnabled_=true, bool isTrigger = false);


    void createCamera();

    
    void createRenderObject(int pointCount_, GLuint VAO_, GLuint VBO_);


    void createGizmoRenderObject(int pointCount_, GLuint VAO_, GLuint VBO_);





    void renderObject(GLuint shader, unsigned int* texture, GLuint VAO_, glm::mat4 view_);


    void renderGizmoObject(GLuint shader, GLuint VAO_, glm::mat4 view_);






    void updateCollider(bool except);
    void updateColliderScale();

    
    bool alreadyCollided = false;





    
    
    
    void onCollision(int objectNumber, int targetNumber);
    
    
    
    
    
    
    
    
    // TRANSFORM EDITS!!!!!!
    void transformPos(float transform_[3]);

    void force(float velocity[3]);

    void force3(float velocity1,float velocity2,float velocity3);

    void rotationPos(float rotation_[4]);

    void rotate(float rotate[4]);

    void setColor(GLfloat color_[4]);

    void scale(float scale[3]);

    void scale3(float x,float y,float z);

    
















    
    

};

std::vector<GameObject> objectArray(1000);





void disableAll();

void deleteObject(int objectNumber);

void deleteAll();

int find(std::string objectName);








#endif