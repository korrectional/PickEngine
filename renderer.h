
#ifndef RENDERER_H
#define RENDERER_H


#include <iostream>
#include <SDL2/SDL.h>
#include "glad.h"
#include "UI.h"
#include "GameObject.h"
#include "Camera.h"
#include "stb_image_implementation.h"


#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>





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

    SDL_Renderer* renderer;
    SDL_GLContext glcontext;
    GLuint vertexShader;
    GLuint fragmentShader;
    GLuint shaderProgram;
    GLuint vertexShaderUI;
    GLuint fragmentShaderUI;
    GLuint vertexShaderText;
    GLuint fragmentShaderText;
    GLuint VAO[1000], VBO[1000]; 
    GLuint shaderProgramUI;
    GLuint shaderProgramText;
    GLuint VAOtxt[1], VBOtxt[1]; //txt
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
        window = SDL_CreateWindow("Line",SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, sX, sY, SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL);
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



        
        GLfloat vertices[] = {
            -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
             0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
             0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
             0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
            -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
            -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

            -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
             0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
             0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
             0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
            -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
            -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

            -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
            -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
            -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
            -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
            -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
            -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

             0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
             0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
             0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
             0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
             0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
             0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

            -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
             0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
             0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
             0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
            -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
            -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

            -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
             0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
             0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
             0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
            -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
            -0.5f,  0.5f, -0.5f,  0.0f, 1.0f

        };

        GLfloat button[] = {
            -1.0f , 1.0f, 0.0f,
            -1.0f , 0.9f, 0.0f,
            -0.75f , 1.0f, 0.0f,  //  125 x, 50 ys
            -1.0f , 0.9f, 0.0f,
            -0.75f , 1.0f, 0.0f,
            -0.75f , 0.9f, 0.0f
        };




                
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











        float transform[3] = {
            0.0f,0.0f,-3.0f
        };


        float rotation[4] = {
            0.0f,0.0f,0.0f,0.0f
        }; // rotation[0] is degrees

        GLfloat red[4] = {
            0.5f,0.5f,0.5f,0.5f
        }; 
        

        // Scene Objects
        for(int i=0;i<gameObjectCount;i++){
            objectArray[i].createRenderObject(vertices, 36*5, VAO[i],VBO[i]);
        }
        // UI
        UIObjectArray[0].createButtonObject("button1", transform, rotation, red, button,6*3,VAO[gameObjectCount],VBO[gameObjectCount], false);

        


        // Bind both the VBO and VAO to 0 so that we don't accidentally modify the VAO and VBO we created
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);

        



        // One-time UI settings
        glUseProgram(shaderProgramUI);  
        int colorUILoc = glGetUniformLocation(shaderProgramUI, "color");
        glUniform4f(colorUILoc, 0.5f, 0.5f, 0.5f, 0.5f);

        

        

        float rotate;
        rotate = 0.0;

        int visionMode;
        visionMode = 0;

        


        setFOV();


        
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
        


        glGenVertexArrays(1, VAOtxt);
        glGenBuffers(1, VBOtxt);
        //glGenBuffers(1, &EBO);


        // First
        glBindVertexArray(VAOtxt[0]);
        glBindBuffer(GL_ARRAY_BUFFER, VBOtxt[0]);
        glBufferData(GL_ARRAY_BUFFER, sizeof(block), block, GL_STATIC_DRAW);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);



        // Bind both the VBO and VAO to 0 so that we don't accidentally modify the VAO and VBO we created
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);


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
    void setFOV(){
        // set FOV
        projection = glm::perspective(glm::radians(FOV), float(sX) / float(sY), 0.1f, 100.0f);
        projectionLoc = glGetUniformLocation(shaderProgram, "projection");


        glm::mat4 view = glm::mat4(1.0f);
        view = glm::translate(view, glm::vec3(0,0,-3.0f)); 
        int viewLoc = glGetUniformLocation(shaderProgram, "view");
        glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));

        
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
    void renderLoop(int visionMode)
    {
        
        glm::mat4 view = camera.camera();




        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);





        glUseProgram(shaderProgram);
        glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projection));






        
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

        for(int i=0;i<gameObjectCount;i++){
            objectArray[i].renderObject(shaderProgram, texture, VAO[i],view);
        }
        
        glDisable(GL_DEPTH_TEST);  


        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);


        UIObjectArray[0].renderButtonObject(shaderProgramUI, VAO[gameObjectCount]);
        


        

        // Text
        const char text2render[12] = "PICK ENGINE";
        ui.RenderText(shaderProgramText, VAOtxt[0], text2render,sizeof(text2render), 0.01,0.01, 1.0f);

        

        
        SDL_GL_SwapWindow(window);
    }





};




renderer render;






#endif