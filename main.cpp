#include <iostream>
#include <SDL2/SDL.h>
#include "glad/glad.h"
#include "glad/glad.c"
#include "renderer.h"
#include "gameObject.h"
#include "camera.h"
#include "input.h"
#include "pickPhysics.h"
#include "userScript.cpp"
#include "viewScript.cpp"
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include "objProcessor.h"
#include "time.h"
#include "userInterface.h"




// /#include <glm/glm.hpp>
// /#include <glm/gtc/matrix_transform.hpp>
// /#include <glm/gtc/type_ptr.hpp>






//                Create shader code 
// set vars
//renderer render; in renderer.h
PickPhysics physics;


int main()
{
    

    //ObjPross::ProcessOBJ("/home/david/Desktop/PickEngine/Humanoid.obj");


    gameObjectCreation();
    // INITIALIZATION
    camera.initialize(false, 500, 500);
    render.initializeRenderer(500, 500);
    
    
    //Input input;




    //Boot();
    viewBoot();

    int gameRunDelta;

    while (1)
	{
        timeClock.tick();

        input.getEvents();
        if(exitProgram){
            break;
        }



        if(playing){
            Loop();
            viewConLoop();


            physics.collisionLoop();
        }
        else{
            viewConLoop();
            viewLoop();
        }



        render.renderLoop(visionMode);
        UI::renderUserInterface();
        SDL_GL_SwapWindow(render.window); // render loop


        gameRunDelta = timeClock.returnTick();
        
        if(gameRunDelta < 17){
            SDL_Delay(17 - gameRunDelta);
        }
	}





    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplSDL2_Shutdown();
    ImGui::DestroyContext();


    SDL_DestroyWindow(render.window);
    SDL_Quit();



  


    
    

    

    
    return 0;
}









