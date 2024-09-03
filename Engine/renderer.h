
#ifndef RENDERER_H
#define RENDERER_H

#include "../third-party/imgui-master/imgui.h"
#include "../third-party/imgui-master/imgui_impl_sdl2.h"
#include "../third-party/imgui-master/imgui_impl_opengl3.h"

#include <iostream>
#include <string>

#include <SDL2/SDL.h>
#include "../third-party/glad/glad.h"
#include "gameObject.h"
#include "camera.h"
#include "../third-party/stb/stb_image.h"
#include "time.h"
#include "shader.h"




#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>










Shader mainShader;
Shader gizmoShader;
Shader sunShader;







class Renderer{
private:



    int sX;
    int sY;

    GLuint VAO[1000], VBO[1000]; 
    GLuint VAOtxt[1000], VBOtxt[1000]; //gizmos
    unsigned int texture[100];
    float FOV = 90;


    void createTextures(){
        // TIME TO CREATE TEXTURE OBJECT!!!
        createTexture(0,"../assets/wall.png");
        createTexture(1,"../assets/letuce.png");
        createTexture(2,"../assets/windows.png");

    }



public: /////////////////////////////////////BEGIN///////////////////////////////////////////////////////


    SDL_Window* window;
    SDL_Renderer* renderer;
    SDL_GLContext glcontext;
    bool showCollisionGizmo = false;









    void initializeRenderer(float sX_, float sY_);


    void objectRenderSet();
    void sayHey();

    
    void imGuiSetup();
    
    
    
    
    

    void createTexture(int texNum, const char* texPath);


    glm::mat4 projection;
    int projectionLoc;
    int projectionLocGizmo;
    int projectionLocSun;
    
    void setFOV();
    bool boola = true;
    float lightPosition[3] = {10.0f,10.0f,10.0f};

    void renderLoop(int visionMode);



};




Renderer render;












#endif