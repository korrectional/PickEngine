
#include <iostream>
#include <string>

#include "renderer.h"





void Renderer::initializeRenderer(float sX_, float sY_)
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
    //glClearColor(0.0f,0.0f,0.0f,0.0f);
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
}



void Renderer::objectRenderSet()\
{
    for(int i=0;i<gameObjectCount;i++){
        objectArray[i].createRenderObject(36*5, VAO[i],VBO[i]);
        objectArray[i].createGizmoRenderObject(36*5, VAOtxt[i],VBOtxt[i]);
    }
}

void Renderer::sayHey()
{
    std::cout<<"Hey!\n";
}







    
void Renderer::imGuiSetup(){
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
void Renderer::createTexture(int texNum, const char* texPath){
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


void Renderer::setFOV(){
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
//////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////loop/////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////
void Renderer::renderLoop(int visionMode)
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
    mainShader.setVec3("viewPos", camera.gameObject.transform); 
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
    
    
}




    