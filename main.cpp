#include <iostream>
#include <SDL2/SDL.h>
#include "glad.h"
#include "glad.c"
#include "UI.h"
#include "renderer.h"
#include "GameObject.h"
#include "Camera.h"
#include "input.h"
#include "userScript.cpp"


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
    




    gameObjectCreation();
    // INITIALIZATION
    camera.initialize(false);
    render.initializeRenderer();
    render.initializeText();
    
    
    Input input;




    Boot();


    while (1)
	{
        input.getEvents();
        if(exitProgram){
            break;
        }



        
        Loop();




        render.renderLoop(visionMode);
        SDL_Delay(17);
	}

    SDL_DestroyWindow(render.window);
    SDL_Quit();



  


    
    

    

    
    return 0;
}








