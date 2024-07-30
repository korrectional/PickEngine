    
#ifndef TEXSET_H
#define TEXSET_H

#include <iostream>
#include "glad.h"
#include "stb_image.h"
    
    
    
void textureSetup(GLfloat vertexShaderTex, const char* vertexShaderSourceTexture, GLfloat fragmentShaderTex, const char* fragmentShaderSourceTexture, GLfloat shaderProgramTex, GLuint texture){
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    vertexShaderTex = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShaderTex, 1, &vertexShaderSourceTexture, NULL);
    glCompileShader(vertexShaderTex);

         
     

    fragmentShaderTex = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShaderTex, 1, &fragmentShaderSourceTexture, NULL);
    glCompileShader(fragmentShaderTex);
    int  successTex;
    char infoLogUITex[512];
    glGetShaderiv(fragmentShaderTex, GL_COMPILE_STATUS, &successTex);
    if(!successTex)
    {
        glGetShaderInfoLog(fragmentShaderTex, 512, NULL, infoLogUITex);
        std::cout << "ERROR::SHAADER::VERTEX::COMPILATION_FAILED\n" << infoLogUITex << std::endl;
    }
    shaderProgramTex = glCreateProgram();
    glAttachShader(shaderProgramTex, vertexShaderTex);
    glAttachShader(shaderProgramTex, fragmentShaderTex);
    glLinkProgram(shaderProgramTex);
    glDeleteShader(vertexShaderTex);
    glDeleteShader(fragmentShaderTex); // texShader
    glBindTexture(GL_TEXTURE_2D, texture);

  
      // TIME TO CREATE TEXTURE OBJECT!!!
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture); // all upcoming GL_TEXTURE_2D operations now have effect on this texture object
    // set the texture wrapping parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// set texture wrapping to GL_REPEAT (default wrapping method)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    // set texture filtering parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    // load image, create texture and generate mipmaps
    int width, height, nrChannels;
    // The FileSystem::getPath(...) is part of the GitHub repository so we can find files on any IDE/platform; replace it with your own image path.
    unsigned char *data = stbi_load("/home/david/Desktop/PickEngine/wall.png", &width, &height, &nrChannels, 0);
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

#endif