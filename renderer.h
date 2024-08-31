
#ifndef RENDERER_H
#define RENDERER_H

#include "imgui-master/imgui.h"
#include "imgui-master/imgui_impl_sdl2.h"
#include "imgui-master/imgui_impl_opengl3.h"

#include <iostream>
#include <string>

#include <SDL2/SDL.h>
#include "glad/glad.h"
#include "gameObject.h"
#include "camera.h"
#include "stb/stb_image.h"
#include "time.h"
#include "light.h"
#include "shader.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>



bool playing;



void interface();




Shader mainShader;
Shader gizmoShader;
Shader sunShader;







class renderer{
private:












    // Text







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









    void initializeRenderer(float sX_, float sY_)
    {
        sX=sX_;sY=sY_;

        // INITIALIZATION
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION,4);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION,0);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_COMPATIBILITY);
        SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER,1);
        SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE,16);

        SDL_Init(SDL_INIT_VIDEO);
        window = SDL_CreateWindow("PickEngine",SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, sX, sY, SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL);
        renderer = SDL_CreateRenderer(window, -1, 0); 
        glcontext = SDL_GL_CreateContext(window);

        //SDL_VIDEODRIVER=x11;
        if(camera.mouseCommand == true){
            SDL_SetWindowMouseGrab(window,SDL_TRUE);
            SDL_ShowCursor(SDL_DISABLE);
        }
        
        gladLoadGL();
        
        //102, 153, 255
        //glClearColor(0.4f,0.6f,1.0f,1.0f);
        glClearColor(0.0f,0.0f,0.0f,0.0f);
        glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
        SDL_GL_SwapWindow(window);
        glViewport(0,0,sX,sY);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        createTextures();



        mainShader.ShaderInitialize("/home/david/Desktop/PickEngine/shaders/mainShader.vs","/home/david/Desktop/PickEngine/shaders/mainShader.fs");
        gizmoShader.ShaderInitialize("/home/david/Desktop/PickEngine/shaders/gizmoShader.vs","/home/david/Desktop/PickEngine/shaders/gizmoShader.fs");
        sunShader.ShaderInitialize("/home/david/Desktop/PickEngine/shaders/sunShader.vs","/home/david/Desktop/PickEngine/shaders/sunShader.fs");



        
        



       

        // VAO and VBO!!!
        glGenVertexArrays(1000, VAO);
        glGenBuffers(1000, VBO);
                // Bind both the VBO and VAO to 0 so that we don't accidentally modify the VAO and VBO we created
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);



        glGenVertexArrays(1000, VAOtxt);
        glGenBuffers(1000, VBOtxt);
                // Bind both the VBO and VAO to 0 so that we don't accidentally modify the VAO and VBO we created
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);








        float transform[3] = {
            0.0f,0.0f,-3.0f
        };


        float rotation[4] = {
            0.0f,0.0f,0.0f,0.0f
        }; // rotation[0] is degrees





        

        // Scene Objects
        objectRenderSet();



        



        




        

        

        float rotate;
        rotate = 0.0;

        int visionMode;
        visionMode = 0;

        


        setFOV();
        imGuiSetup();


        //ImGui::Begin("Window", NULL);
        //ImGui::Text("hihi");
        //ImGui::End();

    }


    void objectRenderSet(){
        for(int i=0;i<gameObjectCount;i++){
            objectArray[i].createRenderObject(36*5, VAO[i],VBO[i]);
            objectArray[i].createGizmoRenderObject(36*5, VAOtxt[i],VBOtxt[i]);
        }


    }

    
    void imGuiSetup(){
        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        ImGuiIO& io = ImGui::GetIO(); (void)io;
        io.WantCaptureKeyboard = true;
        ImGui::StyleColorsDark();
        ImGui_ImplSDL2_InitForOpenGL(window, glcontext);
        ImGui_ImplOpenGL3_Init();



    }
    
    
    
    
    
    //////////////////////////////////////////////////////////////////////////////////////////////////////
    //////////////////////////////////////////////////////////////////////////////////////////////////////



    void createTexture(int texNum, const char* texPath){
        glGenTextures(1, &texture[texNum]);
        glBindTexture(GL_TEXTURE_2D, texture[texNum]); // all upcoming GL_TEXTURE_2D operations now have effect on this texture object
        // set the texture wrapping parameters
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// set texture wrapping to GL_REPEAT (default wrapping method)
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        // set texture filtering parameters
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        // load image, create texture and generate mipmaps
        int width, height, nrChannels;
        unsigned char *data = stbi_load(texPath, &width, &height, &nrChannels, 0);
        if (data)
        {
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
            glGenerateMipmap(GL_TEXTURE_2D);
        }
        else
        {
            std::cout << "Failed to load texture" << std::endl;
        }
        stbi_image_free(data);
    }


    glm::mat4 projection;
    int projectionLoc;
    int projectionLocGizmo;
    int projectionLocSun;
    
    void setFOV(){
        // set FOV
        glUseProgram(mainShader.ID);
        projection = glm::perspective(glm::radians(FOV), float(sX) / float(sY), 0.1f, 100.0f);
        projectionLoc = glGetUniformLocation(mainShader.ID, "projection");


        glm::mat4 view = glm::mat4(1.0f);
        view = glm::translate(view, glm::vec3(0,0,-3.0f)); 
        int viewLoc = glGetUniformLocation(mainShader.ID, "view");
        glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));



        glUseProgram(gizmoShader.ID);
        glUniformMatrix4fv(glGetUniformLocation(gizmoShader.ID, "view"), 1, GL_FALSE, glm::value_ptr(view));
        projectionLocGizmo = glGetUniformLocation(gizmoShader.ID, "projection");

        glUseProgram(sunShader.ID);
        glUniformMatrix4fv(glGetUniformLocation(sunShader.ID, "view"), 1, GL_FALSE, glm::value_ptr(view));
        projectionLocSun = glGetUniformLocation(sunShader.ID, "projection");




        

        
    }
    bool boola = true;
    float lightPosition[3] = {10.0f,10.0f,10.0f};
    //////////////////////////////////////////////////////////////////////////////////////////////////////
    //////////////////////////////////////////////////////////////////////////////////////////////////////
    //////////////////////////////////////////////////////////////////////////////////////////////////////
    //////////////////////////////////////////////////////////////////////////////////////////////////////
    /////////////////////////////////////////////loop/////////////////////////////////////////////////////
    //////////////////////////////////////////////////////////////////////////////////////////////////////
    //////////////////////////////////////////////////////////////////////////////////////////////////////
    //////////////////////////////////////////////////////////////////////////////////////////////////////
    //////////////////////////////////////////////////////////////////////////////////////////////////////
    void renderLoop(int visionMode)
    {
        glUseProgram(mainShader.ID);
        float color[3] = {1.0f,1.0f,1.0f};
        mainShader.setVec3("lightColor", color);
        
        lightPosition[0] = objectArray[0].transform[0];
        lightPosition[1] = objectArray[0].transform[1];
        lightPosition[2] = objectArray[0].transform[2];
        
        mainShader.setVec3("lightPos", lightPosition);










        
        glm::mat4 view = camera.camera();




        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);



        glUseProgram(mainShader.ID);
        glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projection));

        glUseProgram(gizmoShader.ID);
        glUniformMatrix4fv(projectionLocGizmo, 1, GL_FALSE, glm::value_ptr(projection));

        glUseProgram(sunShader.ID);
        glUniformMatrix4fv(projectionLocSun, 1, GL_FALSE, glm::value_ptr(projection));






        
        if(visionMode == 0){   // Let me see them polygons!!!!
            glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); 
        }
        else if(visionMode == 1){
            glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        }
        else if(visionMode == 2){ // currently disabled
            glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);
        }
        //////////////////////////////////////////////////DRAWDRAW/////////////////////////////
        
        glEnable(GL_DEPTH_TEST);  // Scene
        glUseProgram(sunShader.ID);
        objectArray[0].renderObject(sunShader.ID, 0, VAO[0],view);
        
        for(int i=1;i<gameObjectCount;i++){
            objectArray[i].renderObject(mainShader.ID, texture, VAO[i],view);
        }



        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        glDisable(GL_DEPTH_TEST);  

        if(showCollisionGizmo){


            for(int i=0;i<gameObjectCount;i++){
                objectArray[i].renderGizmoObject(gizmoShader.ID, VAOtxt[i],view);
            }
        }
        


        



        // ImGui

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplSDL2_NewFrame();
        ImGui::NewFrame();

        interface();

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        


            

        

        SDL_GL_SwapWindow(window);


    }





};




renderer render;






























































// gameobject craeteion
char tagg[] = "nametag";
float transform[3] = {0,0,0};
float rotationdir[3] = {0,0,0};
float rotangle = 1.0f;
float rotation[4] = {0,0,0,0};
float colorRBG[3] = {0,255,0};
float colorPick;
GLfloat color[4] = {0,1.0,0,1.0};
int texnum = 0;





bool showGameObject;
bool showDebugPanel;
float aha = 1.04;
float buffer;
bool startWindowOpen = true;
bool createGameObjectOpen = false;
bool editGameObjectOpen = false;


void interface(){
    

    ImGui::Begin("Menu");

    if(startWindowOpen){

        ImGui::Begin("Startup");

        ImGui::SeparatorText("PickEngine");
        ImGui::Text("This is my game engine");
        ImGui::TextLinkOpenURL("Please star my github project", "https://github.com/korrectional/PickEngine");

        if(ImGui::TreeNode("tips")){
            ImGui::Text("To change vision modes press P");
            ImGui::Text("To move use WASD and the arrow");
            ImGui::Text("keys for camera rotation");
            ImGui::TreePop();
        }

        if(ImGui::Button("Close")){
            startWindowOpen = false;
        }

        ImGui::End();
    }


    ImGui::Checkbox("Play" , &playing);



    if(ImGui::BeginMenu("Items")){
        ImGui::MenuItem("GameObject editor", NULL, &showGameObject);
        ImGui::MenuItem("Debug tools", NULL, &showDebugPanel);

        ImGui::EndMenu();
    }






    //ImGui::CloseCurrentPopup();


    // various screens:
    int selectedGameObject = 0;
    if(showGameObject){
        ImGui::Begin("GameObjects");
    
        for(int i = 0; i < gameObjectCount; i++){
            
            
            if(ImGui::TreeNode(objectArray[i].tag)){


                buffer = objectArray[i].transform[0];
                ImGui::InputFloat("#", &buffer);
                objectArray[i].transform[0] = buffer;
                buffer = objectArray[i].transform[1];
                ImGui::InputFloat("##", &buffer);
                objectArray[i].transform[1] = buffer;
                buffer = objectArray[i].transform[2];
                ImGui::InputFloat("###", &buffer);
                objectArray[i].transform[2] = buffer;


                if(ImGui::Button("Edit GameObject")){
                    selectedGameObject = i;
                    editGameObjectOpen = true;
                }

                
                ImGui::TreePop();
            }

        }

        if(ImGui::Button("Create GameObject")){
            createGameObjectOpen = true;
        }


        ImGui::End();

    }

    // Create GameObject

    if(createGameObjectOpen){
        ImGui::Begin("Create");


        ImGui::InputText("nametag", tagg, sizeof(tagg));
        ImGui::InputFloat3("transform", transform);
        ImGui::InputFloat3("rotation", rotationdir);
        ImGui::InputFloat("angle", &rotangle);
        //ImGui::ColorPicker4("Pick color", &colorPick);
        ImGui::InputFloat3("RGB color", colorRBG);
        color[0] = colorRBG[0]/255;color[1] = colorRBG[1]/255;color[2] = colorRBG[2]/255;
        ImGui::InputInt("texture number", &texnum);




        if(ImGui::Button("Create")){
            char* taggg = new char[strlen(tagg)+1];    
            strcpy(taggg, tagg);
            memset(tagg, '#', sizeof(tagg));
            std::cout<<taggg<<"\n";

            rotation[0] = rotangle;
            rotation[1] = rotationdir[0];
            rotation[2] = rotationdir[1];
            rotation[3] = rotationdir[2];
            if(rotation[1] == 0&&rotation[2] == 0&&rotation[3] == 0){rotation[1] = 1.0;}

            objectArray[gameObjectCount].create(taggg, transform, rotation, color, true, texnum, nullptr, false);
            //std::cout<<taggg<<"\n"<<transform[0]<<"\n"<<transform[1]<<"\n"<<transform[2]<<"\n"<<rotation[0]<<"\n"<<rotation[1]<<"\n"<<rotation[2]<<"\n"<<rotation[3]<<"\n";



            float transform[3] = {0.0f,2.0f,-3.0f};
            float rotation[4] = {0.0f,0.1f,0.0f,0.0f};
            GLfloat red[4] = {1.0f,1.0f,0.0f,1.0f}; 
            //objectArray[gameObjectCount].create("CUBE4", transform, rotation, red, true, 2, nullptr, false); 

            



            render.objectRenderSet();
            createGameObjectOpen = false;
        }



        if(ImGui::Button("Close")){
            createGameObjectOpen = false;
        }
        ImGui::End();

    }


    // show gameobject editor
    float trBuffer[3];
    float anBuffer;
    int texBuffer;

    if(editGameObjectOpen){
        ImGui::Begin("Edit GameObject");


        //ImGui::Text(objectArray[selectedGameObject].tag);
        trBuffer[0] = objectArray[selectedGameObject].transform[0];trBuffer[1] = objectArray[selectedGameObject].transform[1];trBuffer[2] = objectArray[selectedGameObject].transform[2];
        ImGui::InputFloat3("transform", trBuffer);
        objectArray[selectedGameObject].transform[0] = trBuffer[0];objectArray[selectedGameObject].transform[1] = trBuffer[1];objectArray[selectedGameObject].transform[2] = trBuffer[2];
        

        trBuffer[0] = objectArray[selectedGameObject].rotation[1];trBuffer[1] = objectArray[selectedGameObject].rotation[2];trBuffer[2] = objectArray[selectedGameObject].rotation[3];
        ImGui::InputFloat3("rotation", trBuffer);
        objectArray[selectedGameObject].rotation[1] = trBuffer[0];objectArray[selectedGameObject].rotation[2] = trBuffer[1];objectArray[selectedGameObject].rotation[3] = trBuffer[2];

        anBuffer = objectArray[selectedGameObject].rotation[0];
        ImGui::InputFloat("angle", &anBuffer);
        objectArray[selectedGameObject].rotation[0] = anBuffer;

        trBuffer[0] = objectArray[selectedGameObject].color[0];trBuffer[1] = objectArray[selectedGameObject].color[1];trBuffer[2] = objectArray[selectedGameObject].color[2];
        ImGui::InputFloat3("color", trBuffer);
        objectArray[selectedGameObject].color[0] = trBuffer[0];objectArray[selectedGameObject].color[1] = trBuffer[1];objectArray[selectedGameObject].color[2] = trBuffer[2];

        texBuffer = objectArray[selectedGameObject].texNum;
        ImGui::InputInt("texture number", &texBuffer);
        objectArray[selectedGameObject].texNum = texBuffer;

        objectArray[0].collisionBox;



        if(ImGui::Button("Close")){
            editGameObjectOpen = false;
        }
        ImGui::End();
    }


    // show gizmo pannel

    if(showDebugPanel)
    {
        ImGui::Begin("Gizmos");

        int fps = 1000/timeClock.delta;
        ImGui::Text("FPS: %d", fps);
        ImGui::Text("TPS: %d", timeClock.delta);
        ImGui::Checkbox("Colliders", &render.showCollisionGizmo);

        

        ImGui::End();
    }


    ImGui::End();

}








#endif