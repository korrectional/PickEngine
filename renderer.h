
#ifndef RENDERER_H
#define RENDERER_H

#include "imgui-master/imgui.h"
#include "imgui-master/imgui_impl_sdl2.h"
#include "imgui-master/imgui_impl_opengl3.h"

#include <iostream>
#include <string>
#include <cstring>  // For strcpy and strlen

#include <SDL2/SDL.h>
#include "glad.h"
#include "UI.h"
#include "GameObject.h"
#include "Camera.h"
#include "stb_image_implementation.h"





#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>






void interface();












class renderer{
private:
    const char *vertexShaderSource = "#version 330 core\n"
        "layout (location = 0) in vec3 aPos;\n"
        "layout (location = 1) in vec2 aTexCoord;\n"
        "uniform mat4 model;\n"
        "uniform mat4 view;\n"
        "uniform mat4 projection;\n"
        "uniform mat4 rotation;\n"
        "out vec2 TexCoord;\n"



        "void main()\n"
        "{\n"
        "   gl_Position = projection*view*model*vec4(aPos,1.0f);\n"
        "   TexCoord = aTexCoord;\n"
        "}\0";



    const char* fragmentShaderSource = "#version 330 core\n"
        "out vec4 FragColor;\n"
        "uniform vec4 color;\n"
        "in vec2 TexCoord;\n"
        "uniform sampler2D ourTexture;\n"

        "void main()\n"
        "{\n"
        "   FragColor = vec4(texture(ourTexture, TexCoord))*vec4(color);\n"
        "}\n\0";







    const char *vertexShaderSourceGizmo = "#version 330 core\n"
        "layout (location = 0) in vec3 aPos;\n"
        "uniform mat4 model;\n"
        "uniform mat4 view;\n"
        "uniform mat4 projection;\n"
        "uniform mat4 rotation;\n"



        "void main()\n"
        "{\n"
        "   gl_Position = projection*view*model*vec4(aPos,1.0f);\n"
        "}\0";



    const char* fragmentShaderSourceGizmo = "#version 330 core\n"
        "out vec4 FragColor;\n"
        "uniform vec4 color;\n"

        "void main()\n"
        "{\n"
        "   FragColor = vec4(color);\n"
        "}\n\0";













    const char *vertexShaderSourceUI = "#version 330 core\n"
        "layout (location = 0) in vec3 aPos;\n"
        "uniform mat4 view;\n"

        "void main()\n"
        "{\n"
        "   gl_Position = view*vec4(aPos.x,aPos.y,aPos.z,1.0f);\n"
        "}\0";


    const char* fragmentShaderSourceUI = "#version 330 core\n"
        "out vec4 FragColor;\n"
        "uniform vec4 color;\n"
        "void main()\n"
        "{\n"
        "   FragColor = color;\n"
        "}\n\0";


    // Text

    const char *vertexShaderSourceText = "#version 330 core\n"
        "layout (location = 0) in vec3 aPos;\n"
        "uniform vec2 pos;\n"



        "void main()\n"
        "{\n"
        "   gl_Position = vec4(aPos.x+pos.x,aPos.y+pos.y,aPos.z,1.0f);\n"
        "}\0";




    const char* fragmentShaderSourceText = "#version 330 core\n"
        "out vec4 FragColor;\n"
        "uniform vec4 color;\n"
        "void main()\n"
        "{\n"
        "   FragColor = color;\n"
        "}\n\0";



    int sX;
    int sY;

    GLuint vertexShader;
    GLuint fragmentShader;
    GLuint shaderProgram;
    GLuint vertexShaderGizmo;
    GLuint fragmentShaderGizmo;
    GLuint shaderProgramGizmo;
    GLuint vertexShaderUI;
    GLuint fragmentShaderUI;
    GLuint vertexShaderText;
    GLuint fragmentShaderText;
    GLuint VAO[1000], VBO[1000]; 
    GLuint shaderProgramUI;
    GLuint shaderProgramText;
    GLuint VAOtxt[1000], VBOtxt[1000]; //txt
    GLuint vertexShaderTex;
    GLuint fragmentShaderTex;
    GLuint shaderProgramTex;
    unsigned int texture[10];
    float FOV = 90;


    void createTextures(){
        // TIME TO CREATE TEXTURE OBJECT!!!
        createTexture(0,"../wall.png");
        createTexture(1,"../letuce.png");
        createTexture(2,"../windows.png");

    }



public: /////////////////////////////////////BEGIN///////////////////////////////////////////////////////


    SDL_Window* window;
    SDL_Renderer* renderer;
    SDL_GLContext glcontext;
    bool showCollisionGizmo = false;





    // set vars
    UI ui;





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
        glClearColor(0.4f,0.6f,1.0f,1.0f);
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





        // Creating shader program
        vertexShader = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
        glCompileShader(vertexShader);

            
        int  success;
        char infoLog[512];
        glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
        if(!success)
        {
            glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
            std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
        }



        fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
        glCompileShader(fragmentShader);

        shaderProgram = glCreateProgram();
        glAttachShader(shaderProgram, vertexShader);
        glAttachShader(shaderProgram, fragmentShader);
        glLinkProgram(shaderProgram);

        glDeleteShader(vertexShader);
        glDeleteShader(fragmentShader);







        // Gizmo
        vertexShaderGizmo = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(vertexShaderGizmo, 1, &vertexShaderSourceGizmo, NULL);
        glCompileShader(vertexShaderGizmo);

            

        glGetShaderiv(vertexShaderGizmo, GL_COMPILE_STATUS, &success);
        if(!success)
        {
            glGetShaderInfoLog(vertexShaderGizmo, 512, NULL, infoLog);
            std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
        }



        fragmentShaderGizmo = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(fragmentShaderGizmo, 1, &fragmentShaderSourceGizmo, NULL);
        glCompileShader(fragmentShaderGizmo);

        shaderProgramGizmo = glCreateProgram();
        glAttachShader(shaderProgramGizmo, vertexShaderGizmo);
        glAttachShader(shaderProgramGizmo, fragmentShaderGizmo);
        glLinkProgram(shaderProgramGizmo);

        glDeleteShader(vertexShaderGizmo);
        glDeleteShader(fragmentShaderGizmo);




    //  UI SHADER

        vertexShaderUI = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(vertexShaderUI, 1, &vertexShaderSourceUI, NULL);
        glCompileShader(vertexShaderUI);

        fragmentShaderUI = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(fragmentShaderUI, 1, &fragmentShaderSourceUI, NULL);
        glCompileShader(fragmentShaderUI);

        shaderProgramUI = glCreateProgram();
        glAttachShader(shaderProgramUI, vertexShaderUI);
        glAttachShader(shaderProgramUI, fragmentShaderUI);
        glLinkProgram(shaderProgramUI);

        glDeleteShader(vertexShaderUI);
        glDeleteShader(fragmentShaderUI);






        int pixelLoc = glGetUniformLocation(shaderProgramUI, "color");
        glUniform4f(pixelLoc, 0.5f,0.5f,0.5f,1);

    // UI SHADER DONE



        





                
       // float texCoords[] = {                       // TEXTURES!!!!!
       //     -1.0f, 1.0f, 0.0f,   0.0f, 1.0f,
       //     -1.0f, 0.9f, 0.0f,   1.0f, 1.0f,
       //     -0.75f, 1.0f, 0.0f,   0.0f, 0.0f,
       //     -1.0f, 0.9f, 0.0f,   1.0f, 1.0f,
       //     -0.75f, 1.0f, 0.0f,   0.0f, 0.0f,
       //     -0.75f, 0.9f, 0.0f,   1.0f, 0.0f
       // };

       

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



        



        



        // One-time UI settings
        glUseProgram(shaderProgramUI);  
        int colorUILoc = glGetUniformLocation(shaderProgramUI, "color");
        glUniform4f(colorUILoc, 0.5f, 0.5f, 0.5f, 0.5f);

        

        

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
        // UI
        //for(int i=0;i<UIObjectCount;i++){
        //    UIObjectArray[i].createRenderUI(button,VAO[gameObjectCount+i+1],VBO[gameObjectCount+i+1]);
        //}

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

    void initializeText()
    {
// shader start
        vertexShaderText = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(vertexShaderText, 1, &vertexShaderSourceText, NULL);
        glCompileShader(vertexShaderText);

            
        int  successUI;
        char infoLogUI[512];
        glGetShaderiv(vertexShaderText, GL_COMPILE_STATUS, &successUI);
        if(!successUI)
        {
            glGetShaderInfoLog(vertexShaderText, 512, NULL, infoLogUI);
            std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLogUI << std::endl;
        }



        fragmentShaderText = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(fragmentShaderText, 1, &fragmentShaderSourceText, NULL);
        glCompileShader(fragmentShaderText);

        shaderProgramText = glCreateProgram();
        glAttachShader(shaderProgramText, vertexShaderText);
        glAttachShader(shaderProgramText, fragmentShaderText);
        glLinkProgram(shaderProgramText);

        glDeleteShader(vertexShaderText);
        glDeleteShader(fragmentShaderText);
// shader done


        GLfloat block[] = {
            -1, 1, 0,
            -0.99, 1, 0,
            -1, 0.99, 0,
            -0.99, 1, 0,
            -1, 0.99, 0,
            -0.99, 0.99, 0
        };
        


        


        // Text settings
        glUseProgram(shaderProgramText);
        int pixelLoc = glGetUniformLocation(shaderProgramText, "color");
        glUniform4f(pixelLoc, 1,1,1,1);

        glUseProgram(shaderProgramText);
        int posLoc = glGetUniformLocation(shaderProgramText, "pos");
        glUniform2f(posLoc,0,0);


        
    };


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
    
    void setFOV(){
        // set FOV
        glUseProgram(shaderProgram);
        projection = glm::perspective(glm::radians(FOV), float(sX) / float(sY), 0.1f, 100.0f);
        projectionLoc = glGetUniformLocation(shaderProgram, "projection");


        glm::mat4 view = glm::mat4(1.0f);
        view = glm::translate(view, glm::vec3(0,0,-3.0f)); 
        int viewLoc = glGetUniformLocation(shaderProgram, "view");
        glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));



        glUseProgram(shaderProgramGizmo);
        projectionLocGizmo = glGetUniformLocation(shaderProgramGizmo, "projection");
//
//
        view = glm::mat4(1.0f);
        view = glm::translate(view, glm::vec3(0,0,-3.0f)); 
        viewLoc = glGetUniformLocation(shaderProgramGizmo, "view");
        glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));




        

        
    }
    bool boola = true;
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











        
        glm::mat4 view = camera.camera();




        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);



        glUseProgram(shaderProgram);
        glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projection));

        glUseProgram(shaderProgramGizmo);
        glUniformMatrix4fv(projectionLocGizmo, 1, GL_FALSE, glm::value_ptr(projection));






        
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
        //glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

        for(int i=0;i<gameObjectCount;i++){
            objectArray[i].renderObject(shaderProgram, texture, VAO[i],view);
        }




        if(showCollisionGizmo){

            glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
            glDisable(GL_DEPTH_TEST);  

            for(int i=0;i<gameObjectCount;i++){
                objectArray[i].renderGizmoObject(shaderProgramGizmo, VAOtxt[i],view);
            }
        }
        
        glDisable(GL_DEPTH_TEST);  


        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);


        //for(int i=0;i<UIObjectCount;i++){
        //    UIObjectArray[i].renderUI(shaderProgramUI, VAO[gameObjectCount+i+1]);
        //}


        

        // Text
        //char text2render[12] = "PICK ENGINE";
        //ui.RenderText(shaderProgramText, VAOtxt[0], text2render,sizeof(text2render), 0.01,0.01, 1.0f);
        //char* objectNamae = objectArray[0].tag;
        //std::cout<<objectArray[0].tag<<" namae\n";
        //ui.RenderText(shaderProgramText, VAOtxt[1], objectArray[0].tag,sizeof(objectNamae), 0.01,0.1, 1.0f);
        //char objectName[8];
        //ui.RenderText(shaderProgramText, VAOtxt[1], objectName,sizeof(objectName), 0.01,0.2, 1.0f, 1, objectArray[0].transform[0]);
        //ui.RenderText(shaderProgramText, VAOtxt[1], objectName,sizeof(objectName), 0.01,0.3, 1.0f, 1, objectArray[0].transform[1]);
        //ui.RenderText(shaderProgramText, VAOtxt[1], objectName,sizeof(objectName), 0.01,0.4, 1.0f, 1, objectArray[0].transform[2]);


        



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
bool showGizmoPanel;
float aha = 1.04;
float buffer;
bool startWindowOpen = true;
bool createGameObjectOpen = false;


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
        ImGui::MenuItem("Gizmos", NULL, &showGizmoPanel);

        ImGui::EndMenu();
    }






    //ImGui::CloseCurrentPopup();


    // various screens:

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
            std::cout<<taggg<<"\n"<<transform[0]<<"\n"<<transform[1]<<"\n"<<transform[2]<<"\n"<<rotation[0]<<"\n"<<rotation[1]<<"\n"<<rotation[2]<<"\n"<<rotation[3]<<"\n";



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



    if(showGizmoPanel)
    {
        ImGui::Begin("Gizmos");

        ImGui::Checkbox("Colliders", &render.showCollisionGizmo);

        

        ImGui::End();
    }


    ImGui::End();

}








#endif