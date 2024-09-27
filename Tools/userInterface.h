
#ifndef UI
#define UI

#include "../third-party/imgui-master/imgui.h"
#include "../third-party/imgui-master/imgui_impl_sdl2.h"
#include "../third-party/imgui-master/imgui_impl_opengl3.h"

#include <iostream>
#include <string>


#include "../Engine/gameObject.h"
#include "../Engine/camera.h"
#include "../Events/time.h"
#include "../Engine/shader.h"
#include "../Engine/renderer.h"
#include "saveData.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

void userInterface();








// gameobject creation
char tagg[] = "nametag";
float transform[3] = {0,0,0};
float rotationdir[3] = {0,0,0};
float rotangle = 1.0f;
float rotation[4] = {0,0,0,0};
float colorRBG[3] = {0,255,0};
float colorPick;
GLfloat color[4] = {0,1.0,0,1.0};
int texnum = 0;
char fileName[16] = {"filename"}; 
char fileNameSave[16] = {"filename"}; 
char modelFile[64] = {"model filepath"}; 





bool showGameObject;
bool showDebugPanel;
float aha = 1.04;
float buffer;
bool startWindowOpen = true;
bool createGameObjectOpen = false;
bool editGameObjectOpen = false;
bool saveProjectOpen = false;
int selectedGameObject = 0;


void renderUserInterface(){
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplSDL2_NewFrame();
    ImGui::NewFrame();

    userInterface();

    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void userInterface(){
    

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
        ImGui::MenuItem("Save/Load", NULL, &saveProjectOpen);

        ImGui::EndMenu();
    }






    //ImGui::CloseCurrentPopup();


    // various screens:
    
    if(showGameObject){
        ImGui::Begin("GameObjects");
    
        for(int i = 0; i < gameObjectCount; i++){


            if(ImGui::Button(objectArray[i].name.c_str())){
                selectedGameObject = i;
                editGameObjectOpen = true;
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
        ImGui::InputText("model", modelFile, sizeof(modelFile));




        if(ImGui::Button("Create")){
            char* taggg = new char[strlen(tagg)+1];    
            strcpy(taggg, tagg);
            memset(tagg, '#', sizeof(tagg));

            rotation[0] = rotangle;
            rotation[1] = rotationdir[0];
            rotation[2] = rotationdir[1];
            rotation[3] = rotationdir[2];
            if(rotation[1] == 0&&rotation[2] == 0&&rotation[3] == 0){rotation[1] = 1.0;}

            objectArray[gameObjectCount].create(taggg, transform, rotation, color, modelFile, true, texnum, nullptr);



            float transform[3] = {0.0f,2.0f,-3.0f};
            float rotation[4] = {0.0f,0.1f,0.0f,0.0f};
            GLfloat red[4] = {1.0f,1.0f,0.0f,1.0f}; 

            



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
        ImGui::Text("%s",objectArray[selectedGameObject].name.c_str());

        bool buffer = objectArray[selectedGameObject].enabled;
        ImGui::Checkbox("Enabled", &buffer);
        objectArray[selectedGameObject].enabled = buffer;

        trBuffer[0] = objectArray[selectedGameObject].transform[0];trBuffer[1] = objectArray[selectedGameObject].transform[1];trBuffer[2] = objectArray[selectedGameObject].transform[2];
        ImGui::InputFloat3("position", trBuffer);
        objectArray[selectedGameObject].transform[0] = trBuffer[0];objectArray[selectedGameObject].transform[1] = trBuffer[1];objectArray[selectedGameObject].transform[2] = trBuffer[2];
        

        trBuffer[0] = objectArray[selectedGameObject].rotation[1];trBuffer[1] = objectArray[selectedGameObject].rotation[2];trBuffer[2] = objectArray[selectedGameObject].rotation[3];
        ImGui::InputFloat3("rotation", trBuffer);
        objectArray[selectedGameObject].rotation[1] = trBuffer[0];objectArray[selectedGameObject].rotation[2] = trBuffer[1];objectArray[selectedGameObject].rotation[3] = trBuffer[2];

        anBuffer = objectArray[selectedGameObject].rotation[0];
        ImGui::InputFloat("angle", &anBuffer);
        objectArray[selectedGameObject].rotation[0] = anBuffer;

        trBuffer[0] = objectArray[selectedGameObject].scaleValue[0];trBuffer[1] = objectArray[selectedGameObject].scaleValue[1];trBuffer[2] = objectArray[selectedGameObject].scaleValue[2];
        ImGui::InputFloat3("scale", trBuffer);
        objectArray[selectedGameObject].scaleValue[0] = trBuffer[0];objectArray[selectedGameObject].scaleValue[1] = trBuffer[1];objectArray[selectedGameObject].scaleValue[2] = trBuffer[2];


        trBuffer[0] = objectArray[selectedGameObject].color[0];trBuffer[1] = objectArray[selectedGameObject].color[1];trBuffer[2] = objectArray[selectedGameObject].color[2];
        ImGui::InputFloat3("color", trBuffer);
        objectArray[selectedGameObject].color[0] = trBuffer[0];objectArray[selectedGameObject].color[1] = trBuffer[1];objectArray[selectedGameObject].color[2] = trBuffer[2];

        texBuffer = objectArray[selectedGameObject].texNum;
        ImGui::InputInt("texture number", &texBuffer);
        objectArray[selectedGameObject].texNum = texBuffer;


        ImGui::Checkbox("Collsion enabled", &objectArray[selectedGameObject].collisionsEnabled);
        ImGui::Checkbox("isTrigger", &objectArray[selectedGameObject].isTrigger);


        

        objectArray[selectedGameObject].updateColliderScale();
        

        if(ImGui::Button("Delete")){
            GAMEOBJECT::deleteObject(selectedGameObject);

        }

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






    
    if(saveProjectOpen){
        ImGui::Begin("Save");
    
        
        ImGui::Text("Save project");
        ImGui::InputText("##", fileName, sizeof(fileName));
        if(ImGui::Button("Save")){
            saveData(fileName);
        }



        ImGui::Text("Load project");
        ImGui::InputText("####", fileNameSave, sizeof(fileNameSave));
        if(ImGui::Button("Load")){
            loadData(fileNameSave);
        }




        if(ImGui::Button("Close")){
            saveProjectOpen = false;
        }


        ImGui::End();

    }





    ImGui::End();

}


























#endif