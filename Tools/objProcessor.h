#ifndef ObjPross
#define ObjPross


#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>


#include <SDL2/SDL.h>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


std::vector<std::vector<float>> models;

bool done = false;


struct Vertex{
    glm::vec3 vertices;
    glm::vec3 normal;
    glm::vec2 texCoords;
};

std::vector<float> loadModel(std::string path = "/home/david/Desktop/PickEngine/assets/cube.obj")
{
    if(path == "")
    {
        path = "/home/david/Desktop/PickEngine/assets/cube.obj";
    }
    Assimp::Importer import;
    const aiScene *scene = import.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs);	
	
    if(!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) 
    {
        std::cerr << "ERROR::ASSIMP::" << import.GetErrorString() << std::endl;
        std::exit(EXIT_FAILURE);
    }
    
    Vertex output;
    std::vector<float> model;

    for(int i = 0; i < scene->mMeshes[0]->mNumVertices; i++)
    {
        model.push_back(scene->mMeshes[0]->mVertices[i].x);
        model.push_back(scene->mMeshes[0]->mVertices[i].y);
        model.push_back(scene->mMeshes[0]->mVertices[i].z);

        model.push_back(scene->mMeshes[0]->mTextureCoords[0][i].x);
        model.push_back(scene->mMeshes[0]->mTextureCoords[0][i].y);
        
        model.push_back(scene->mMeshes[0]->mNormals[i].x);
        model.push_back(scene->mMeshes[0]->mNormals[i].y);
        model.push_back(scene->mMeshes[0]->mNormals[i].z);
    }



    if(!done){//0.063671
        std::cout<<scene->mMeshes[0]->mNumVertices<<"\n";
        std::cout<<model.size()<<"\n";

        for(int i = 0; i < scene->mMeshes[0]->mNumVertices*8; i=i+8)
        {
            
            std::cout<<model[i]<<" ";
            std::cout<<model[i+1]<<" ";
            std::cout<<model[i+2]<<" ";

            std::cout<<model[i+3]<<" ";
            std::cout<<model[i+4]<<" ";

            std::cout<<model[i+5]<<" ";
            std::cout<<model[i+6]<<" ";
            std::cout<<model[i+7]<<"\n";
        }
        done = true;

    }
    
    return model;
}  

void addModels()
{
    //models.push_back(verticesS);
    models.push_back(loadModel());
}












#endif