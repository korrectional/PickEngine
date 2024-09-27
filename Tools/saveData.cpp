

#include "saveData.h"





void saveData(const std::string& filename){
    std::ofstream outFile(filename);
    if (outFile.is_open()) {
        outFile << gameObjectCount<< std::endl;
        for(int i = 1; i<gameObjectCount; i++){
            outFile << objectArray[i].name<< std::endl;
            outFile << objectArray[i].transform[0]<<" " << objectArray[i].transform[1]<<" " << objectArray[i].transform[2]<< std::endl;
            outFile << objectArray[i].rotation[0]<<" " << objectArray[i].rotation[1]<<" " << objectArray[i].rotation[2]<<" " << objectArray[i].rotation[3]<< std::endl;
            outFile << objectArray[i].color[0]<<" " << objectArray[i].color[1]<<" " << objectArray[i].color[2]<< std::endl;
            outFile << objectArray[i].texNum<< std::endl;
            outFile << objectArray[i].textured<< std::endl;
            outFile << objectArray[i].scaleValue[0]<<" " << objectArray[i].scaleValue[1]<<" " << objectArray[i].scaleValue[2]<< std::endl;
            outFile << objectArray[i].collisionsEnabled<< std::endl;
            outFile << objectArray[i].isTrigger<< std::endl;

        }
        outFile.close();
        std::cout << "Data saved successfully." << std::endl;
    }
    else
    {
        std::cerr << "Error opening file for reading!" << std::endl;

    }
}



void loadData(const std::string& filename) 
{
    std::ifstream inFile(filename); 
    std::string line;

    std::string x; std::string y; std::string z; std::string w; std::string v; std::string t;

    if (inFile.is_open()) 
    {
        GAMEOBJECT::deleteAll(); // disable all current objects
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

            std::getline(inFile, line); // scale
            std::istringstream issScale(line);
            issScale >> x >> y >> z;
            scaleValueC[0] = std::stof(x);
            scaleValueC[1] = std::stof(y);
            scaleValueC[2] = std::stof(z);

            std::getline(inFile, line);  // collisionsEnabled
            collisionsEnabledC = std::stoi(line);

            std::getline(inFile, line);  // isTrigger
            isTriggerC = std::stoi(line);



            



            const char* tagB = tagC.c_str();
            // Now that we have the object data, we create it
            objectArray[gameObjectCount].create(tagB, transformC, rotationC, colorC, "", texturedC, texNumC, scaleValueC, nullptr, collisionsEnabledC, isTriggerC);
            objectArray[gameObjectCount].updateColliderScale();
        }

        // at the end, we restart the renderer
        render.objectRenderSet();



        inFile.close();
        std::cout << "Data loaded successfully."<< std::endl;
    } else {
        std::cerr << "Error opening file for reading!" << std::endl;
    }
}




