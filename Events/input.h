    #ifndef INPUT_H
    #define INPUT_H


    #include <iostream>
    #include <SDL2/SDL.h>
    #include "../Engine/gameObject.h"
    #include "../Engine/camera.h"
    #include "../Engine/renderer.h"


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
    bool lMousePressed = false;
    bool rMousePressed = false;
    float exitProgram = false;


    SDL_Event globalEvent;

    class Input
    {
    private:
        Sint32 lastX;
        Sint32 lastY;
    public:
        SDL_Event event;


        void ButtonLogic(const SDL_Event& ev, float* location, int funcNum);


        SDL_Event getEvents();

    };


void setPlaying(bool playing_);

Input input;
#endif