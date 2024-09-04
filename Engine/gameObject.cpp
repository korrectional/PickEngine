


#include <iostream>
#include <string>
#include <cstdlib>  
#include <vector>

#include "gameObject.h"
#include "renderer.h"



void GameObject::create(std::string name_, float transform_[3], float rotation_[4], GLfloat color_[3], bool textured_, int texNum_ , float scale_[3], float* initCollisionBox_,bool collisionsEnabled_, bool isTrigger_)
{
    for(int i=0;i<288;i++){vertices[i] = verticesS[i];};
    gameObjectCount++;
    if(!initCollisionBox_){
        for(int i=0;i<6;i++){initCollisionBox[i] = scaledCollisionBox[i];}
    }
    
    for(int i=0;i<3;i++){transform[i] = transform_[i];}
    for(int i=0;i<4;i++){rotation[i] = rotation_[i];}
    if(scale_ != nullptr){for(int i=0;i<3;i++){scaleValue[i] = scale_[i];}}
    else{for(int i=0;i<3;i++){scaleValue[i] = 1.0f;}}
    for(int i=0;i<3;i++){color[i] = color_[i];}
    for(int i=0;i<6;i=i+2){
        collisionBox[i] = transform[i/2]+initCollisionBox[i];
        collisionBox[i+1] = transform[i/2]+initCollisionBox[i+1];
    }
    textured = textured_;
    texNum = texNum_;
    collisionsEnabled = collisionsEnabled_;
    isTrigger = isTrigger_;

    name = checkForNames(name_);;

    updateCollider(true);
}


void GameObject::createCamera()
{
    initCollisionBox[0] = 0.3;
    initCollisionBox[1] = -0.3;
    initCollisionBox[2] = 0.5;
    initCollisionBox[3] = -0.5;
    initCollisionBox[4] = 0.3;
    initCollisionBox[5] = -0.3;
    for(int i=0;i<6;i=i+2){
        collisionBox[i] = transform[i/2]+initCollisionBox[i];
        collisionBox[i+1] = transform[i/2]+initCollisionBox[i+1];
    }
    updateCollider(true);
}


void GameObject::createRenderObject(int pointCount_, GLuint VAO_, GLuint VBO_)
{
    pointCount = pointCount_;
    glBindVertexArray(VAO_);
    glBindBuffer(GL_ARRAY_BUFFER, VBO_);
    glBufferData(GL_ARRAY_BUFFER, pointCount*7, vertices, GL_DYNAMIC_DRAW);
    
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(5 * sizeof(float)));
    glEnableVertexAttribArray(2);
    
}



void GameObject::createGizmoRenderObject(int pointCount_, GLuint VAO_, GLuint VBO_)
{
    pointCount = pointCount_;
    glBindVertexArray(VAO_);
    glBindBuffer(GL_ARRAY_BUFFER, VBO_);
    glBufferData(GL_ARRAY_BUFFER, pointCount*4, gizmoVertices, GL_DYNAMIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
}













void GameObject::renderObject(GLuint shader, unsigned int* texture, GLuint VAO_, glm::mat4 view_)
{
    if(!enabled){return;}
    glUseProgram(shader);
    if(textured){
        glBindTexture(GL_TEXTURE_2D, texture[texNum]);
    }
    view = glm::mat4(1.0f);
    view = view_ * glm::translate(view, glm::vec3(transform[0],transform[1],transform[2]));
    glUniformMatrix4fv(glGetUniformLocation(shader, "view"), 1, GL_FALSE, glm::value_ptr(view));
    
    model = glm::mat4(1.0f);
    if(rotation[1]==0&&rotation[2]==0&&rotation[3]==0){rotation[1]=0.1;}
    model = glm::rotate(model, glm::radians(rotation[0]), glm::vec3(rotation[1],rotation[2],rotation[3])); 
    glUniformMatrix4fv(glGetUniformLocation(shader, "model"), 1, GL_FALSE, glm::value_ptr(model));

    glm::mat4 scale = glm::mat4(1.0f); 
    scale = glm::scale(scale, glm::vec3(scaleValue[0], scaleValue[1], scaleValue[2]));
    glUniformMatrix4fv(glGetUniformLocation(shader, "scale"), 1, GL_FALSE, glm::value_ptr(scale)); 

    
    glUniform3f(glGetUniformLocation(shader, "color"), color[0],color[1],color[2]); // MAKING COLOR
    glUniform1i(glGetUniformLocation(shader, "reflectivness"), reflectivness); // Set reflectivness
    glBindVertexArray(VAO_);
    glDrawArrays(GL_TRIANGLES, 0, 36); 
}

void GameObject::renderGizmoObject(GLuint shader, GLuint VAO_, glm::mat4 view_)
{
    if(!enabled){return;}
    glUseProgram(shader);
    
    view = glm::mat4(1.0f);
    view = view_ * glm::translate(view, glm::vec3(transform[0],transform[1],transform[2]));
    glUniformMatrix4fv(glGetUniformLocation(shader, "view"), 1, GL_FALSE, glm::value_ptr(view));
    
    model = glm::mat4(1.0f);
    model = glm::rotate(model, glm::radians(0.0f), glm::vec3(1.0f,0.0f,0.0f)); 
    glUniformMatrix4fv(glGetUniformLocation(shader, "model"), 1, GL_FALSE, glm::value_ptr(model));

    glm::mat4 scale = glm::mat4(1.0f); 
    scale = glm::scale(scale, glm::vec3(scaleValue[0], scaleValue[1], scaleValue[2]));
    glUniformMatrix4fv(glGetUniformLocation(shader, "scale"), 1, GL_FALSE, glm::value_ptr(scale)); 
    
    glUniform4f(glGetUniformLocation(shader, "color"), 0.0,1.0,0.0,1.0); // MAKING COLOR
    glBindVertexArray(VAO_);
    glDrawArrays(GL_TRIANGLES, 0, 36); 
}
//////////////////////////////UTILITY//////////////////////////////////////////////////////////
void GameObject::updateCollider(bool except){
    if(!enabled){return;}
    for(int i=0;i<6;i=i+2){
        collisionBox[i] = transform[i/2]+scaledCollisionBox[i];
        collisionBox[i+1] = transform[i/2]+scaledCollisionBox[i+1];
    }
}

void GameObject::updateColliderScale(){
    if(!enabled){return;}
    for(int i=0;i<6;i=i+2){
        scaledCollisionBox[i] = initCollisionBox[i]*scaleValue[i/2];
        scaledCollisionBox[i+1] = initCollisionBox[i+1]*scaleValue[i/2];
    }
}

bool alreadyCollided = false;








    
    //////////////////////////////////USER/UTILITY/////////////////////////////////////////
    
    
    
    
    
void GameObject::onCollision(int objectNumber, int targetNumber){
    if(!enabled){return;}
    if(alreadyCollided){
        return;
    }
    alreadyCollided = true;
    ///////////////////////////////////////////////////////////////////////////////////////////////////////////
    // Here you specify what to do based on the objectNumber
    std::cout<<"Collision: "<<objectNumber;
    if(objectNumber == 1 && targetNumber == 1){
        // if 1, do something
    }
}
    
    
    
    
    
    
    
    
    // PARAMETER EDITS!!!!!!
void GameObject::transformPos(float transform_[3])
{
    for(int i=0;i<3;i++){transform[i] = transform_[i];}
}


void GameObject::force(float velocity[3])
{
    for(int i=0;i<3;i++){transform[i] = transform[i] + velocity[i];}
}


void GameObject::force3(float velocity1,float velocity2,float velocity3)
{
    float velocity[3] = {velocity1,velocity2,velocity3};
    for(int i=0;i<3;i++){transform[i] = transform[i] + velocity[i];}
}


void GameObject::rotationPos(float rotation_[4])
{
    for(int i=0;i<4;i++){rotation[i] = rotation_[i];}
}


void GameObject::rotate(float rotate[4])
{
    for(int i=0;i<4;i++){rotation[i] = rotation[i] + rotate[i];}
}


void GameObject::setColor(GLfloat color_[4])
{
    for(int i=0;i<4;i++){color[i] = color_[i];}
}


void GameObject::scale(float scale[3])
{
    scaleValue[0] =+ scale[0];
    scaleValue[1] =+ scale[1];
    scaleValue[2] =+ scale[2];
}

void GameObject::scale3(float x,float y,float z)
{
    scaleValue[0] =+ x;
    scaleValue[1] =+ y;
    scaleValue[2] =+ z;

}









void disableAll(){
    for(int i = 1; i < gameObjectCount; i++){
        objectArray[i].enabled = false;
    }
}

void deleteObject(int objectNumber)
{
    for(int i = objectNumber; i < gameObjectCount-1; i++){
        objectArray[i] = objectArray[i+1];
    }
    gameObjectCount--;
    return;
}

void deleteAll()
{
    int gameObjectCountBuffer = gameObjectCount;
    for(int i = 1; i<gameObjectCountBuffer;i++)
    {
        deleteObject(i);
    }
}

int find(std::string objectName)
{
    for(int i = 1; i < gameObjectCount; i++)
    {
        if(objectArray[i].name == objectName){
            return i;
        }
    }
    std::cerr<<"\ngameObject.cpp: Cannot find object with name "<<objectName<<std::endl;
    std::exit(EXIT_FAILURE);
}

int tryFind(std::string objectName)
{
    for(int i = 1; i < gameObjectCount; i++)
    {
        if(objectArray[i].name == objectName){
            return i;
        }
    }
    std::cout<<"\ngameObject.cpp: Cannot find object with name "<<objectName<<std::endl;
}


std::string checkForNames(std::string name)
{
    int count = 0;
    std::string nameSave;
    nameSave = name;
    for(int i = 0; i < gameObjectCount; i++)
    {
        if(objectArray[i].name == name)
        {
            count ++;
            name = nameSave + "(" + std::to_string(count) + ")";
            i = 0;
        }
    }
    return name;
}