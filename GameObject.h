#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H


#include <iostream>
#include "glad.h"
#include "objProcessor.h"
//#include "renderer.h"




int gameObjectCount = 0;
int UIObjectCount = 0;

GLfloat verticesS[] = {
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
    bool textured;
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
    const char* tag;
    float vertices[6]; 
    GLfloat color[4] = {0,0,0,1.0f};

    float transform[3] = {0,0,0};
    float rotation[4] = {0,0.1,0,0};
    bool staticCollider;
    int texNum;

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
    
    
    
    void create(const char* tag_, float transform_[3], float rotation_[4], GLfloat color_[4], bool textured_, int texNum_ ,float* initCollisionBox_ = nullptr ,bool staticCollider_=false)
    {


        //render.createTexture(3,texPath);
        gameObjectCount++;
        if(!initCollisionBox_){
            for(int i=0;i<6;i++){initCollisionBox[i] = defInitCollisionBox[i];}
        }
        
        for(int i=0;i<3;i++){transform[i] = transform_[i];}
        for(int i=0;i<4;i++){rotation[i] = rotation_[i];}
        for(int i=0;i<4;i++){color[i] = color_[i];}

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
        std::vector<Mesh> customMesh = ObjPross::ProcessOBJ("/home/david/Desktop/PickEngine/Humanoid.obj"); // messing with customs
        GLfloat customVertices[customMesh.size()*5];
        //int wfs = 0;
        for(int i = 0; i < customMesh.size(); i++){
            customVertices[i*5] = customMesh[i].vertex.x ;
            customVertices[i*5+1] = customMesh[i].vertex.y ;
            customVertices[i*5+2] = customMesh[i].vertex.z ;
            customVertices[i*5+3] = customMesh[i].texture.u;
            customVertices[i*5+4] = customMesh[i].texture.v;
            //std::cout << customVertices[i*5] <<" "<< customVertices[i*5+1] <<" "<< customVertices[i*5+2] <<" UV: "<< customVertices[i*5+3] <<" "<< customVertices[i*5+4] << "\n";
        }

        std::vector<Indice> indices = ObjPross::ProcessOBJIndices("/home/david/Desktop/PickEngine/Humanoid.obj"); // messing with customs
        unsigned int customIndices[indices.size()*3];

        for(int i = 0; i < indices.size(); i ++)
        {
            customIndices[i*3] = indices[i].x;
            customIndices[i*3+1] = indices[i].y;
            customIndices[i*3+2] = indices[i].z;
            //std::cout<<customIndices[i*3]<<" "<<customIndices[i*3+1]<<" "<<customIndices[i*3+2]<<"\n";
        }





        //locVAO = VAO_; locVBO = VBO_;
        pointCount = pointCount_;//customMesh.size()*5;
        glBindVertexArray(VAO_);
        glBindBuffer(GL_ARRAY_BUFFER, VBO_);
        glBufferData(GL_ARRAY_BUFFER, pointCount*4, verticesS, GL_DYNAMIC_DRAW);
        
        if(textured = true)
        {
            glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
            glEnableVertexAttribArray(0);
            glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
            glEnableVertexAttribArray(1);
        }
        else
        {
            glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
            glEnableVertexAttribArray(0);
        }
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







    void createUI(char* tag_, float transform_[3], GLfloat color_[4])
    {
        UIObjectCount++;

        for(int i=0;i<3;i++){transform[i] = transform_[i];}
        for(int i=0;i<4;i++){color[i] = color_[i];}

        tag = tag_;
    }

    //void createRenderUI(float vertices_[], GLuint VAO_, GLuint VBO)
    //{
    //    glBindVertexArray(VAO_);
    //    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    //    glBufferData(GL_ARRAY_BUFFER, 6*3*4, vertices_, GL_DYNAMIC_DRAW);
//
    //    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    //    glEnableVertexAttribArray(0);
//
    //}
//
//
//
    //void renderUI(GLuint shader, GLuint VAO_)
    //{
    //    glUseProgram(shader);
//
//
    //    glm::mat4 view = glm::mat4(1.0f);
    //    view = glm::translate(view, glm::vec3(transform[0],transform[1],transform[2]));
    //    int viewLoc = glGetUniformLocation(shader, "view");
    //    glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
    //    
    //    int colorLoc = glGetUniformLocation(shader, "color"); 
    //    glUniform4f(colorLoc, color[0],color[1],color[2],color[3]); // MAKING COLOR
//
//
    //    glBindVertexArray(VAO_);
    //    glDrawArrays(GL_TRIANGLES, 0, 6); 
    //}











    void renderObject(GLuint shader, unsigned int* texture, GLuint VAO_, glm::mat4 view_)
    {
        glUseProgram(shader);
        glBindTexture(GL_TEXTURE_2D, texture[texNum]);


        view = glm::mat4(1.0f);
        view = view_ * glm::translate(view, glm::vec3(transform[0],transform[1],transform[2]));
        viewLoc = glGetUniformLocation(shader, "view");
        glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
        
        model = glm::mat4(1.0f);
        model = glm::rotate(model, glm::radians(rotation[0]), glm::vec3(rotation[1],rotation[2],rotation[3])); 
        modelLoc = glGetUniformLocation(shader, "model");
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

        
        colorLoc = glGetUniformLocation(shader, "color"); 
        glUniform4f(colorLoc, color[0],color[1],color[2],color[3]); // MAKING COLOR


        glBindVertexArray(VAO_);
        glDrawArrays(GL_TRIANGLES, 0, pointCount/3); 
    }


    void renderGizmoObject(GLuint shader, GLuint VAO_, glm::mat4 view_)
    {
        glUseProgram(shader);
        


        view = glm::mat4(1.0f);
        view = view_ * glm::translate(view, glm::vec3(transform[0],transform[1],transform[2]));
        viewLoc = glGetUniformLocation(shader, "view");
        glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
        
        model = glm::mat4(1.0f);
        model = glm::rotate(model, glm::radians(0.0f), glm::vec3(1.0f,0.0f,0.0f)); 
        modelLoc = glGetUniformLocation(shader, "model");
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

        
        colorLoc = glGetUniformLocation(shader, "color"); 
        glUniform4f(colorLoc, 0.0,1.0,0.0,1.0); // MAKING COLOR


        glBindVertexArray(VAO_);
        glDrawArrays(GL_TRIANGLES, 0, pointCount/3); 
    }
























    //////////////////////////////UTILITY//////////////////////////////////////////////////////////
    void updateCollider(bool except){
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
    
    
    
    
    
    void onCollision(int objectNumber){
        if(alreadyCollided){
            return;
        }
        alreadyCollided = true;

        ///////////////////////////////////////////////////////////////////////////////////////////////////////////
        // Here you specify what to do based on the objectNumber
        std::cout<<"COLLLLIISION!!!";
        if(objectNumber == 1){
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



#endif