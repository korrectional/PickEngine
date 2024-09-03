#ifndef SAVEDATA_H
#define SAVEDATA_H

#include "../third-party/imgui-master/imgui.h"
#include "../third-party/imgui-master/imgui_impl_sdl2.h"
#include "../third-party/imgui-master/imgui_impl_opengl3.h"

#include <iostream>
#include <string>
#include <fstream>
#include <string>

#include <SDL2/SDL.h>
#include "../third-party/glad/glad.h"
#include "../Engine/gameObject.h"
#include "../Engine/camera.h"
#include "../Events/time.h"
#include "../Engine/shader.h"
#include "../Engine/renderer.h"


#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


// temporary variables that will be the parameters for the creation of the new gameObjects
std::string tagC;
float transformC[3];
float rotationC[4];
float scaleValueC[3];
float colorC[3];
int texNumC;
bool texturedC;
bool collisionsEnabledC;
bool isTriggerC;
float scaledCollisionBoxC[6];



void saveData(const std::string& filename);
void loadData(const std::string& filename);













#endif