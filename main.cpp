#include <iostream>
#include <SDL2/SDL.h>
#include "glad.h"
#include "glad.c"
#include "UI.h"
#include "renderer.h"
#include "GameObject.h"
#include "Camera.h"
#include "input.h"
#include "PickPhysics.h"
#include "userScript.cpp"





// /#include <glm/glm.hpp>
// /#include <glm/gtc/matrix_transform.hpp>
// /#include <glm/gtc/type_ptr.hpp>






//                Create shader code 
// set vars
UI ui;
//renderer render; in renderer.h
PickPhysics physics;


int main()
{
    




    gameObjectCreation();
    // INITIALIZATION
    camera.initialize(false, 500, 500);
    render.initializeRenderer(500, 500);
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



        physics.collisionLoop();
        render.renderLoop(visionMode);
        SDL_Delay(17);
	}

    SDL_DestroyWindow(render.window);
    SDL_Quit();



  


    
    

    

    
    return 0;
}









