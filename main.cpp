#include <iostream>
#include <SDL2/SDL.h>
#include "third-party/glad/glad.h"
#include "third-party/glad/glad.c"
#include "Engine/renderer.h"
#include "Engine/renderer.cpp"
#include "Engine/shader.h"
#include "Engine/shader.cpp"
#include "Engine/gameObject.h"
#include "Engine/gameObject.cpp"
#include "Engine/camera.h"
#include "Engine/camera.cpp"
#include "Events/input.h"
#include "Events/input.cpp"
#include "Events/time.h"
#include "Events/time.cpp"

#include "Engine/pickPhysics.h"
#include "Engine/pickPhysics.cpp"
#include "Engine/audioPlayer.h"
#include "user-scripts/userScript.cpp"
#include "user-scripts/viewScript.cpp"
#include "user-scripts/gameObjectCreation.cpp"
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include "Tools/objProcessor.h"
#include "Tools/userInterface.h"
#include "Tools/saveData.h"
#include "Tools/saveData.cpp"





 



int main()
{

    //ObjPross::ProcessOBJ("/home/david/Desktop/PickEngine/Humanoid.obj");


    gameObjectCreation();
    // INITIALIZATION
    camera.initialize(false, 500, 500);
    render.initializeRenderer(500, 500);
    
    




    //Boot();
    viewBoot();

    int gameRunDelta;
    AUDIOPLAYER::playSound("/home/david/Desktop/PickEngine/assets/ShinChan-ep6.wav");

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


            PICKPHYSICS::collisionLoop();
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









