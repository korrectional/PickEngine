#ifndef INPUT_H
#define INPUT_H


#include <iostream>
#include <SDL2/SDL.h>
#include "glad.h"
#include "UI.h"
#include "GameObject.h"
#include "Camera.h"
#include "renderer.h"


#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>





int visionMode = 0;

//keys:
bool wPressed = false;
bool sPressed = false;
bool aPressed = false;
bool dPressed = false;
bool leftPressed = false;
bool rightPressed = false;
bool upPressed = false;
bool downPressed = false;
bool kPressed = false;
bool spPressed = false;
bool shPressed = false;
float exitProgram = false;


class Input
{
public:

    SDL_Event getEvents(){
        SDL_Event event;
        // events!!!!!!!
        while(SDL_PollEvent(&event)){
            if(event.type == SDL_QUIT){
                exitProgram = true;
                break;    
            }
            if(event.type == SDL_KEYDOWN){
                if(event.key.keysym.sym == SDLK_ESCAPE){
                    exitProgram = true;
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

                if(event.key.keysym.sym == SDLK_LEFT){ 
                    leftPressed = true; 
                }
                if(event.key.keysym.sym == SDLK_RIGHT){
                    rightPressed = true;
                }
                if(event.key.keysym.sym == SDLK_UP){ 
                    upPressed = true; 
                }
                if(event.key.keysym.sym == SDLK_DOWN){ 
                    downPressed = true;
                }
                if(event.key.keysym.sym == SDLK_SPACE){ 
                    spPressed = true;
                }
                if(event.key.keysym.sym == SDLK_LSHIFT){ 
                    shPressed = true;
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

                if(event.key.keysym.sym == SDLK_LEFT){ 
                    leftPressed = false; 
                }
                if(event.key.keysym.sym == SDLK_RIGHT){
                    rightPressed = false;
                }
                if(event.key.keysym.sym == SDLK_UP){ 
                    upPressed = false; 
                }
                if(event.key.keysym.sym == SDLK_DOWN){  
                    downPressed = false;
                }
                if(event.key.keysym.sym == SDLK_SPACE){ 
                    spPressed = false;
                }
                if(event.key.keysym.sym == SDLK_LSHIFT){ 
                    shPressed = false;
                }

            }
            float buttonPos[] = {0.0f,0.0f,62.0f,25.0f};
            if(event.type == SDL_MOUSEBUTTONDOWN){
                float* velocity = new float[3];
                if(event.button.button == SDL_BUTTON_LEFT){
                }    
                if(event.button.button == SDL_BUTTON_RIGHT){
                }
            }

            
        } 
        return event;              

    }

};


#endif