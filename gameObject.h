#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H


#include <iostream>
#include <string>
#include "glad/glad.h"
#include "objProcessor.h"
//#include "renderer.h"



bool playing;

int gameObjectCount = 0;
int UIObjectCount = 0;

GLfloat verticesS[] = {
-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,   0.0f,  0.0f, -1.0f,
 0.5f, -0.5f, -0.5f,  1.0f, 0.0f,   0.0f,  0.0f, -1.0f, 
 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,   0.0f,  0.0f, -1.0f, 
 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,   0.0f,  0.0f, -1.0f, 
-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,   0.0f,  0.0f, -1.0f, 
-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,   0.0f,  0.0f, -1.0f, 
  
-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,   0.0f,  0.0f, 1.0f,
 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,   0.0f,  0.0f, 1.0f,
 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,   0.0f,  0.0f, 1.0f,
 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,   0.0f,  0.0f, 1.0f,
-0.5f,  0.5f,  0.5f,  0.0f, 1.0f,   0.0f,  0.0f, 1.0f,
-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,   0.0f,  0.0f, 1.0f,
  
-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,  -1.0f,  0.0f,  0.0f,
-0.5f,  0.5f, -0.5f,  1.0f, 1.0f,  -1.0f,  0.0f,  0.0f,
-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,  -1.0f,  0.0f,  0.0f,
-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,  -1.0f,  0.0f,  0.0f,
-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,  -1.0f,  0.0f,  0.0f,
-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,  -1.0f,  0.0f,  0.0f,
  
 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,   1.0f,  0.0f,  0.0f,
 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,   1.0f,  0.0f,  0.0f,
 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,   1.0f,  0.0f,  0.0f,
 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,   1.0f,  0.0f,  0.0f,
 0.5f, -0.5f,  0.5f,  0.0f, 0.0f,   1.0f,  0.0f,  0.0f,
 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,   1.0f,  0.0f,  0.0f,
  
-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,   0.0f, -1.0f,  0.0f,
 0.5f, -0.5f, -0.5f,  1.0f, 1.0f,   0.0f, -1.0f,  0.0f,
 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,   0.0f, -1.0f,  0.0f,
 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,   0.0f, -1.0f,  0.0f,
-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,   0.0f, -1.0f,  0.0f,
-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,   0.0f, -1.0f,  0.0f,
  
-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,   0.0f,  1.0f,  0.0f,
 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,   0.0f,  1.0f,  0.0f,
 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,   0.0f,  1.0f,  0.0f,
 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,   0.0f,  1.0f,  0.0f,
-0.5f,  0.5f,  0.5f,  0.0f, 0.0f,   0.0f,  1.0f,  0.0f,
-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,   0.0f,  1.0f,  0.0f




};






GLfloat button[] = {
-1.0f , 1.0f, 0.0f,
-1.0f , 0.9f, 0.0f,
-0.75f , 1.0f, 0.0f,  //  125 x, 50 ys
-1.0f , 0.9f, 0.0f,
-0.75f , 1.0f, 0.0f,
-0.75f , 0.9f, 0.0f
};



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
    GLfloat gizmoVertices[180] = {
-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
 0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
-0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
-0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
 0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
 0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
-0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
-0.5f,  0.5f, -0.5f,  0.0f, 1.0f

    };

public:    
    std::string tag;
    bool textured;
    float vertices[6]; 
    GLfloat color[3] = {0,0,0};

    float transform[3] = {0,0,0};
    float rotation[4] = {0,0.1,0,0};
    bool staticCollider;
    int texNum;

    bool enabled = true;

    float initCollisionBox[6] = {
        0.5,-0.5,//x
        0.5,-0.5,//y
        0.5,-0.5//z
    };
    float defInitCollisionBox[6] = {
        0.5,-0.5,//x
        0.5,-0.5,//y
        0.5,-0.5//z
    };
    float collisionBox[6] = {
        0.5,-0.5,//x
        0.5,-0.5,//y
        0.5,-0.5 //z
    };
    

    
    void create(std::string tag_, float transform_[3], float rotation_[4], GLfloat color_[3], bool textured_, int texNum_ ,float* initCollisionBox_ = nullptr ,bool staticCollider_=false)
    {


        //render.createTexture(3,texPath);
        gameObjectCount++;
        if(!initCollisionBox_){
            for(int i=0;i<6;i++){initCollisionBox[i] = defInitCollisionBox[i];}
        }
        
        for(int i=0;i<3;i++){transform[i] = transform_[i];}
        for(int i=0;i<4;i++){rotation[i] = rotation_[i];}
        for(int i=0;i<3;i++){color[i] = color_[i];}

        for(int i=0;i<6;i=i+2){
            collisionBox[i] = transform[i/2]+initCollisionBox[i];
            collisionBox[i+1] = transform[i/2]+initCollisionBox[i+1];
        }



        textured = textured_;
        texNum = texNum_;
        tag = tag_;
        staticCollider = staticCollider_;
        //if(textured){
        //    texture
        //}
        updateCollider(true);
    }




    void createCamera()
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

        staticCollider = false;

        updateCollider(true);
    }



    
    void createRenderObject(int pointCount_, GLuint VAO_, GLuint VBO_)
    {
        pointCount = pointCount_;
        glBindVertexArray(VAO_);
        glBindBuffer(GL_ARRAY_BUFFER, VBO_);
        glBufferData(GL_ARRAY_BUFFER, pointCount*7, verticesS, GL_DYNAMIC_DRAW);
        

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(5 * sizeof(float)));
        glEnableVertexAttribArray(2);
        


    }


    void createGizmoRenderObject(int pointCount_, GLuint VAO_, GLuint VBO_)
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














    void renderObject(GLuint shader, unsigned int* texture, GLuint VAO_, glm::mat4 view_)
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
        model = glm::rotate(model, glm::radians(rotation[0]), glm::vec3(rotation[1],rotation[2],rotation[3])); 
        glUniformMatrix4fv(glGetUniformLocation(shader, "model"), 1, GL_FALSE, glm::value_ptr(model));

        
        glUniform3f(glGetUniformLocation(shader, "color"), color[0],color[1],color[2]); // MAKING COLOR


        glBindVertexArray(VAO_);
        glDrawArrays(GL_TRIANGLES, 0, 36); 
    }
    


    void renderGizmoObject(GLuint shader, GLuint VAO_, glm::mat4 view_)
    {
        if(!enabled){return;}

        glUseProgram(shader);
        


        view = glm::mat4(1.0f);
        view = view_ * glm::translate(view, glm::vec3(transform[0],transform[1],transform[2]));
        glUniformMatrix4fv(glGetUniformLocation(shader, "view"), 1, GL_FALSE, glm::value_ptr(view));
        
        model = glm::mat4(1.0f);
        model = glm::rotate(model, glm::radians(0.0f), glm::vec3(1.0f,0.0f,0.0f)); 
        glUniformMatrix4fv(glGetUniformLocation(shader, "model"), 1, GL_FALSE, glm::value_ptr(model));

        
        glUniform4f(glGetUniformLocation(shader, "color"), 0.0,1.0,0.0,1.0); // MAKING COLOR


        glBindVertexArray(VAO_);
        glDrawArrays(GL_TRIANGLES, 0, 36); 
    }
























    //////////////////////////////UTILITY//////////////////////////////////////////////////////////
    void updateCollider(bool except){
        if(!enabled){return;}
        if(!staticCollider||except){
            for(int i=0;i<6;i=i+2){
                collisionBox[i] = transform[i/2]+initCollisionBox[i];
                collisionBox[i+1] = transform[i/2]+initCollisionBox[i+1];
            }
        }

        
    }

    
    bool alreadyCollided = false;











    //void updateCollisionGizmo(){
    //    gizmoVertices[0] = initCollisionBox[1];
    //    gizmoVertices[5] = initCollisionBox[0];
    //    gizmoVertices[10] = initCollisionBox[0];
    //    gizmoVertices[15] = initCollisionBox[0];
    //    gizmoVertices[20] = initCollisionBox[1];
    //    gizmoVertices[25] = initCollisionBox[1];
    //    gizmoVertices[30] = initCollisionBox[1];
    //    gizmoVertices[35] = initCollisionBox[0];
    //    gizmoVertices[40] = initCollisionBox[0];
    //    gizmoVertices[45] = initCollisionBox[0];
    //    gizmoVertices[50] = initCollisionBox[1];
    //    gizmoVertices[55] = initCollisionBox[1];
    //    gizmoVertices[60] = initCollisionBox[1];
    //    gizmoVertices[65] = initCollisionBox[1];
    //    gizmoVertices[70] = initCollisionBox[1];
    //    gizmoVertices[75] = initCollisionBox[1];
    //    gizmoVertices[80] = initCollisionBox[1];
    //    gizmoVertices[85] = initCollisionBox[1];
    //    gizmoVertices[90] = initCollisionBox[0];
    //    gizmoVertices[95] = initCollisionBox[0];
    //    gizmoVertices[100] = initCollisionBox[0];
    //    gizmoVertices[105] = initCollisionBox[0];
    //    gizmoVertices[110] = initCollisionBox[0];
    //    gizmoVertices[115] = initCollisionBox[0];
    //    gizmoVertices[120] = initCollisionBox[1];
    //    gizmoVertices[125] = initCollisionBox[0];
    //    gizmoVertices[130] = initCollisionBox[0];
    //    gizmoVertices[135] = initCollisionBox[0];
    //    gizmoVertices[140] = initCollisionBox[1];
    //    gizmoVertices[145] = initCollisionBox[1];
    //    gizmoVertices[150] = initCollisionBox[1];
    //    gizmoVertices[155] = initCollisionBox[0];
    //    gizmoVertices[160] = initCollisionBox[0];
    //    gizmoVertices[165] = initCollisionBox[0];
    //    gizmoVertices[170] = initCollisionBox[1];
    //    gizmoVertices[175] = initCollisionBox[1];
//
    //}


    
    //////////////////////////////////USER/UTILITY/////////////////////////////////////////
    
    
    
    
    
    void onCollision(int objectNumber, int targetNumber){
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
    
    
    
    
    
    
    
    
    // TRANSFORM EDITS!!!!!!
    void transformPos(float transform_[3])
    {
        for(int i=0;i<3;i++){transform[i] = transform_[i];}
    }

    void force(float velocity[3])
    {
        for(int i=0;i<3;i++){transform[i] = transform[i] + velocity[i];}
    }
    void force3(float velocity1,float velocity2,float velocity3)
    {
        float velocity[3] = {velocity1,velocity2,velocity3};
        for(int i=0;i<3;i++){transform[i] = transform[i] + velocity[i];}
    }



    void rotationPos(float rotation_[4])
    {
        for(int i=0;i<4;i++){rotation[i] = rotation_[i];}
    }

    void rotate(float rotate[4])
    {
        for(int i=0;i<4;i++){rotation[i] = rotation[i] + rotate[i];}
    }

    
    
    void setColor(GLfloat color_[4])
    {
        for(int i=0;i<4;i++){color[i] = color_[i];}
    }

    
















    
    

};

GameObject objectArray[1000];
GameObject UIObjectArray[100];




void deleteObject(int objectNumber)
{
    for(int i = objectNumber; i < gameObjectCount-1; i++){
        objectArray[i] = objectArray[i+1];
    }
    gameObjectCount--;
    return;
}

void disableAll(){
    for(int i = 1; i < gameObjectCount; i++){
        objectArray[i].enabled = false;
    }
}

void deleteAll()
{
    int gameObjectCountBuffer = gameObjectCount;
    for(int i = 1; i<gameObjectCountBuffer;i++)
    {
        deleteObject(i);
    }
}








#endif