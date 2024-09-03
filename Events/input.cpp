


#include "input.h"






void Input::ButtonLogic(const SDL_Event& ev, float* location, int funcNum){
    std::cout<<"\n\n"<<lastX<<" y: "<<lastY<<"\n";
    
    if(lastX >= location[0] &&
        lastY >= location[1] &&
        lastX <= location[2] &&
        lastY <= location[3])
    {
        if(funcNum == 0){
            if(playing){
                playing = false;
            }
            else{
                playing = true;
            }
        }
        else if(funcNum == 1){
            std::cout<<"COMING SOON";
        }
        

    }
}





SDL_Event Input::getEvents(){


    // single frame resets

    // events!!!!!!!
    while(SDL_PollEvent(&event)){
        
        ImGui_ImplSDL2_ProcessEvent(&event);

        if(event.type == SDL_QUIT){
            exitProgram = true;
            break;    
        }


        //std::cout<<event.button.x<<"\n"<<event.button.y<<"\n\n";




        if(event.type == SDL_MOUSEBUTTONDOWN){
            
            if(event.button.button == SDL_BUTTON_LEFT){
                lMousePressed = true;
                
            }
            if(event.button.button == SDL_BUTTON_RIGHT){
                rMousePressed = true;
            }
                
        }
        if(event.type == SDL_MOUSEBUTTONUP){
            
            if(event.button.button == SDL_BUTTON_LEFT){
                lMousePressed = false;
            }
            if(event.button.button == SDL_BUTTON_RIGHT){
                rMousePressed = false;
            }
                
        }

        if(!lMousePressed && event.button.y > 0 && event.button.y < 5000 && event.button.y > 0){
            lastX = event.button.x;
            lastY = event.button.y;

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



        
    } 

    
    
    return event;
}



void setPlaying(bool playing_){
playing = playing_;
}



