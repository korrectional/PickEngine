#ifndef SAVEDATA_H
#define SAVEDATA_H

#include "imgui-master/imgui.h"
#include "imgui-master/imgui_impl_sdl2.h"
#include "imgui-master/imgui_impl_opengl3.h"

#include <iostream>
#include <string>
#include <fstream>
#include <string>

#include <SDL2/SDL.h>
#include "glad/glad.h"
#include "gameObject.h"
#include "camera.h"
#include "time.h"
#include "light.h"
#include "shader.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


void saveData(const std::string& filename);
void loadData(const std::string& filename);




void saveData(const std::string& filename){
    std::ofstream outFile(filename);
    if (outFile.is_open()) {
        outFile << gameObjectCount<< std::endl;
        for(int i = 1; i<gameObjectCount; i++){
            outFile << objectArray[i].tag<< std::endl;
            outFile << objectArray[i].transform[0]<<" " << objectArray[i].transform[1]<<" " << objectArray[i].transform[2]<< std::endl;
            outFile << objectArray[i].rotation[0]<<" " << objectArray[i].rotation[1]<<" " << objectArray[i].rotation[2]<<" " << objectArray[i].rotation[3]<< std::endl;
            outFile << objectArray[i].color[0]<<" " << objectArray[i].color[1]<<" " << objectArray[i].color[2]<< std::endl;
            outFile << objectArray[i].texNum<< std::endl;
            outFile << objectArray[i].textured<< std::endl;
        }
        outFile.close();
        std::cout << "Data saved successfully." << std::endl;
    }
    else
    {
        std::cerr << "Error opening file for reading!" << std::endl;

    }
}


// temporary variables that will be the parameters for the creation of the new gameObjects
std::string tagC;
float transformC[3];
float rotationC[4];
float colorC[3];
int texNumC;
bool texturedC;


void loadData(const std::string& filename) 
{
    std::ifstream inFile(filename); 
    std::string line;

    std::string x; std::string y; std::string z; std::string w;

    if (inFile.is_open()) 
    {
        GAMEOBJECT_H::deleteAll(); // disable all current objects
        int gameOC;
        std::getline(inFile, line);
        std::istringstream issGOC(line);
        issGOC >> x;
        gameOC = std::stoi(x);
        for(int i = 0; i < gameOC - 1; i++){

            std::getline(inFile, line); // tag
            tagC = line;

            std::getline(inFile, line); // transform
            std::istringstream iss(line);
            iss >> x >> y >> z;
            transformC[0] = std::stof(x);
            transformC[1] = std::stof(y);
            transformC[2] = std::stof(z);

            std::getline(inFile, line);
            std::istringstream issRot(line); // rotation
            issRot >> x >> y >> z >> w;
            rotationC[0] = std::stof(x);
            rotationC[1] = std::stof(y);
            rotationC[2] = std::stof(z);
            rotationC[3] = std::stof(w);

            std::getline(inFile, line);  //  color
            std::istringstream issCol(line);
            issCol >> x >> y >> z;
            colorC[0] = std::stof(x);
            colorC[1] = std::stof(y);
            colorC[2] = std::stof(z);

            std::getline(inFile, line);  // texture number
            texNumC = std::stoi(line);

            std::getline(inFile, line);  // if object has texture
            texturedC = std::stoi(line);

            const char* tagB = tagC.c_str();
            // Now that we have the object data, we create it
            objectArray[gameObjectCount].create(tagB, transformC, rotationC, colorC, texturedC, texNumC);
        }

        // at the end, we restart the renderer
        render.objectRenderSet();

        for(int s = 0; s <gameObjectCount; s++)
        {
            std::cout<<"Textured: "<<objectArray[s].tag<<"\n";
            
        }


        inFile.close();
        std::cout << "Data loaded successfully."<< std::endl;
    } else {
        std::cerr << "Error opening file for reading!" << std::endl;
    }
}








#endif