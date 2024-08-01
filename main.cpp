#include <iostream>
#include <SDL2/SDL.h>
#include "glad.h"
#include "glad.c"
#include "UI.h"
#include "renderer.h"
#include "GameObject.h"
#include "Camera.h"


// /#include <glm/glm.hpp>
// /#include <glm/gtc/matrix_transform.hpp>
// /#include <glm/gtc/type_ptr.hpp>

float sayHi();





//                Create shader code 
// set vars
UI ui;
renderer render;


int main()
{
    





    // INITIALIZATION
    render.initializeRenderer();
    render.initializeText();
    camera.initialize();
    
    SDL_Event event;


    int visionMode = 0;
    float transform[3]
    {
        0.0f,0.0f,-3.0f
    };
    float rotation[4]
    {
        30.0f,1.0f,1.0f,0.0f
    };
    float rotate = 0;

    
    
    // Object positions
    float transform_[3] = {0,0,-6.0f};
    cubeObject.transformPos(transform_);

    float transform__[3] = {0.4,0.5,-3.0f};
    cubeObject1.transformPos(transform__);

    float rotation_[4] = {30.0f,0,1.0f,0};
    cubeObject.rotationPos(rotation_);

    float rotation__[4] = {30.0f,0,1.0f,0};
    cubeObject1.rotationPos(rotation__);

    float transform___[3] = {0,0,0};
    buttonObject.transformPos(transform___);

    texObject1.transformPos(transform___);


        
        
    float rotation___[4] = {5.0f,1.0f,0,0};
    cubeObject.rotate(rotation___);

    float rotation____[4] = {10.0f,0.7f,0,0};
    cubeObject1.rotate(rotation____);


    GLfloat green[4] = {0,1.0f,0,1.0f};
    cubeObject.setColor(green);

    GLfloat yellow[4] = {1.0f,1.0f,0,1.0f};
    cubeObject1.setColor(yellow);

    GLfloat grey[4] = {0.5f,0.5f,0.5f,0.5f};
    buttonObject.setColor(grey);
    texObject1.setColor(grey);




    //keys:
    bool wPressed = false;
    bool sPressed = false;
    bool aPressed = false;
    bool dPressed = false;

    bool kPressed = false;
    bool lPressed = false;

    float camZ = 3;

    float exit = false;
    while (1)
	{


        // events!!!!!!!
        while(SDL_PollEvent(&event)){
            if(event.type == SDL_QUIT){
                exit = true;
                break;    
            }
            if(event.type == SDL_KEYDOWN){
                if(event.key.keysym.sym == SDLK_ESCAPE){
                    exit = true;
                    break;
                }
                if(event.key.keysym.sym == SDLK_p){
                    visionMode ++;
                    if(visionMode > 1){
                        visionMode = 0;
                    }
                }
                if(event.key.keysym.sym == SDLK_w){
                    wPressed = true; 
                }
                if(event.key.keysym.sym == SDLK_s){
                    sPressed = true;
                }
                if(event.key.keysym.sym == SDLK_a){ 
                    aPressed = true; 
                }
                if(event.key.keysym.sym == SDLK_d){
                    dPressed = true;
                }

                if(event.key.keysym.sym == SDLK_k){ 
                    kPressed = true; 
                }
                if(event.key.keysym.sym == SDLK_l){
                    lPressed = true;
                }
            
            }
            else if(event.type = SDL_KEYUP)
            {
                
                if(event.key.keysym.sym == SDLK_w){ 
                    wPressed = false; 
                }
                if(event.key.keysym.sym == SDLK_s){
                    sPressed = false;
                }
                if(event.key.keysym.sym == SDLK_a){ 
                    aPressed = false; 
                }
                if(event.key.keysym.sym == SDLK_d){
                    dPressed = false;
                }

                if(event.key.keysym.sym == SDLK_k){ 
                    kPressed = false; 
                }
                if(event.key.keysym.sym == SDLK_l){
                    lPressed = false;
                }

            }
            float buttonPos[] = {0.0f,0.0f,62.0f,25.0f};
            if(event.type == SDL_MOUSEBUTTONDOWN){
                float* velocity = new float[3];
                if(event.button.button == SDL_BUTTON_LEFT){
                    
                    float* velocity = ui.ButtonLogic(event, 1.0f,buttonPos);

                    for(int i=0;i<3;i++){
                        transform[i] = transform[i] + velocity[i];
                    }

                }    
                if(event.button.button == SDL_BUTTON_RIGHT){
                    float* velocity = ui.ButtonLogic(event, -1.0f, buttonPos);

                    for(int i=0;i<3;i++){
                        transform[i] = transform[i] + velocity[i];
                    }

                } 



                // PLAYER SCRIPT FROM NOW ON!   

            }

            
        }
        if(exit){
            break;
        }

        //check for keys 
        if(wPressed == true){
            float transform____[3]={0,0,-0.1f};
            camera.force(transform____);
        }
        if(sPressed == true){
            float transform____[3]={0,0,0.1f};
            camera.force(transform____);
        }
        if(aPressed == true){
            float transform____[3]={-0.1f,0,0};
            camera.force(transform____);
        }
        if(dPressed == true){
            float transform____[3]={0.1f,0,0};
            camera.force(transform____);
        }

        if(lPressed == true){
            float rotate____[3]={0.0f,0.05f,0};
            camera.gameObject.rotate(rotate____);
        }
        if(kPressed == true){
            float rotate____[3]={0.0f,-0.05f,0};
            camera.gameObject.rotate(rotate____);
        }
        
        
        //Object positions
        float transform__[3] = {-0.001,0,-0.005f};
        cubeObject1.force(transform__);

        float rotation_[4] = {3.0f,0,0,0};
        cubeObject.rotate(rotation_);

        float rotation__[4] = {5.0f,0,0,0};
        cubeObject1.rotate(rotation__);








        render.renderLoop(visionMode);
        SDL_Delay(17);
	}

    SDL_DestroyWindow(render.window);
    SDL_Quit();



  


    
    

    

    
    return 0;
}








