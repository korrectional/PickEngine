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



struct Vertex {
    float x, y, z;
};

struct Texture {
    float u, v;
};  

struct Indice {
    unsigned int x, y, z;
};  

struct Mesh {
    Vertex vertex;
    Texture texture;
    //int pointCount;
};


//class Mesh {
//    public:
//        // mesh data
//        vector<Vertex>       vertices;
//        vector<unsigned int> indices;
//        vector<Texture>      textures;
//
//        Mesh(vector<Vertex> vertices, vector<unsigned int> indices, vector<Texture> textures);
//        void Draw(Shader &shader);
//    private:
//        //  render data
//        unsigned int VAO, VBO, EBO;
//
//        void setupMesh();
//};  

std::vector<Indice> ProcessOBJIndices(std::string directory){

    std::string filename = directory;  // Replace with your .obj file name
    std::ifstream objFile(filename);

    std::vector<Indice> bufferIndice;

    if (!objFile.is_open()) {
        std::cerr << "Error opening file: " << filename << std::endl;
        return bufferIndice;
    }

    std::vector<Indice> indices;  
    std::string line;
    while (std::getline(objFile, line)) {

        if (line.rfind("f ", 0) == 0) {


            std::istringstream iss(line.substr(2));  // Create a string stream from the line
            
            std::string xStr, yStr, zStr;
            char delimiter; // To store the slash

            
            std::getline(iss, xStr, '/');
            std::getline(iss, yStr, '/');
            std::getline(iss, zStr, '/');

            unsigned int x = std::stof(xStr); // Convert uStr to float
            unsigned int y = std::stof(yStr); 
            unsigned int z = std::stof(zStr); 

            indices.push_back({x, y, z});


            
            //std::cout<<x<<" "<<y<<" "<<z<<"\n";

            while(zStr.find(' ') != std::string::npos){

                //std::cout<<"some leftover"<<"\n";

                int pos = zStr.find(' ');
                xStr = zStr.substr(pos);
                std::getline(iss, yStr, '/');
                std::getline(iss, zStr, '/');

                x = std::stof(xStr); // Convert uStr to float
                y = std::stof(yStr); 
                z = std::stof(zStr); 

                indices.push_back({x, y, z});
                //std::cout<<x<<" "<<y<<" "<<z<<"\n";
            }
            //vertexLines.push_back(line);  // Add the line to the array
        }
    }

    for(int i = 0; i<indices.size();i++){
        //std::cout<<normals[i].x<<" "<<normals[i].y<<" "<<normals[i].z<<"\n";
    }

    return indices;

}



std::vector<Mesh> ProcessOBJ(std::string directory){
    //Assimp::Importer importer;
    //const aiScene *scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs); 

    std::string filename = directory;  // Replace with your .obj file name
    std::ifstream objFile(filename);

    std::vector<Mesh> bufferMesh;

    if (!objFile.is_open()) {
        std::cerr << "Error opening file: " << filename << std::endl;
        return bufferMesh;
    }

    std::vector<Vertex> vertexes;  // Array to store lines starting with 'v'
    std::vector<Texture> texCoords;  // Array to store lines starting with 'vt'
    std::string line;

    int points = 0;
    int vertices = 0;
    while (std::getline(objFile, line)) {
        // Check if the line starts with 'v' followed by a space
        if (line.rfind("v ", 0) == 0) {


            std::istringstream iss(line);  // Create a string stream from the line
            char v;                        // To store the 'v' character
            float x, y, z;                 // To store the three float values

            // Extract the 'v' character and the three float values
            iss >> v >> x >> y >> z;
            vertices++;
            points = points + 3;
            // Store the vertex in the vector
            vertexes.push_back({x, y, z});

            //vertexLines.push_back(line);  // Add the line to the array
        }


        if (line.rfind("vt ", 0) == 0) {


            std::istringstream iss(line);  // Create a string stream from the line
            std::string vt;                        // To store the 'v' character
            float u, v;                 // To store the three float values

            // Extract the 'v' character and the three float values
            iss >> vt >> u >> v;
            // Store the vertex in the vector
            points = points + 2;
            texCoords.push_back({u, v});

            //vertexLines.push_back(line);  // Add the line to the array
        }


        
    }

    objFile.close();

    std::vector<Mesh> mesh(vertices);

    // Output the lines to verify
    for (int i=0;i<vertices;i++) {
        //mesh[i].pointCount = points;
        mesh[i].vertex.x = vertexes[i].x;
        mesh[i].vertex.y = vertexes[i].y;
        mesh[i].vertex.z = vertexes[i].z;
        mesh[i].texture.u = texCoords[i].u;
        mesh[i].texture.v = texCoords[i].v;
        //std::cout << mesh[i].vertex.x <<" "<< mesh[i].vertex.y <<" "<< mesh[i].vertex.z <<" UV: "<< mesh[i].texture.u <<" "<< mesh[i].texture.v << "\n";
    }

    return mesh;


    //if(!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) 
    //{
    //    cout << "ERROR::ASSIMP::" << import.GetErrorString() << endl;
    //    return;
    //}
    //std::string directory;
    //directory = path.substr(0, path.find_last_of('/'));

    //std::cout<<directory<<"\n";

    //processNode(scene->mRootNode, scene);


}

















#endif