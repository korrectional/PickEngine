#ifndef PICKPHYSICS_H
#define PICKPHYSICS_H


#include <iostream>
#include <SDL2/SDL.h>
#include "glad.h"
#include "UI.h"
//#include "renderer.h"
#include "GameObject.h"
#include "Camera.h"
//#include "input.h"






class PickPhysics
{
public:
    float camCollisions[6];
    void collisionLoop()
    {
        camera.gameObject.updateCollider(false);
        for(int i=0;i<6;i++){camCollisions[i] = camera.gameObject.collisionBox[i];}
        objectArray[0].updateCollider(false);
        objectArray[1].updateCollider(false);
        objectArray[2].updateCollider(false);
        for(int i=0;i<gameObjectCount;i++){
            for(int d=0;d<gameObjectCount;d++){
                if(d==i){
                    continue;
                }
                else if(d<i){
                    continue;
                }

                if(objectArray[i].collisionBox[0]>objectArray[d].collisionBox[1] && objectArray[i].collisionBox[1]<objectArray[d].collisionBox[0]){
                    if(objectArray[i].collisionBox[2]>objectArray[d].collisionBox[3] && objectArray[i].collisionBox[3]<objectArray[d].collisionBox[2]){
                        if(objectArray[i].collisionBox[4]>objectArray[d].collisionBox[5] && objectArray[i].collisionBox[5]<objectArray[d].collisionBox[4]){
                            // WHAT TO DO IF COLLIDING:
                            goBackTransform(i,d, false);
                        }
                    }
                }
                else{
                }
            }
        }

        for(int d=0;d<gameObjectCount;d++){

            if(camCollisions[0]>objectArray[d].collisionBox[1] && camCollisions[1]<objectArray[d].collisionBox[0]){
                if(camCollisions[2]>objectArray[d].collisionBox[3] && camCollisions[3]<objectArray[d].collisionBox[2]){
                    if(camCollisions[4]>objectArray[d].collisionBox[5] && camCollisions[5]<objectArray[d].collisionBox[4]){
                        // WHAT TO DO IF COLLIDING:
                        goBackTransform(0,d, true);
                    }
                }
            }
            else{
            }
        }



    }

    void goBackTransform(int i, int d, bool doit){
        float dist[6];
        float transform[3]{0,0,0};
        if(doit){

            dist[0] = camCollisions[0]-objectArray[d].collisionBox[1];
            dist[1] = objectArray[d].collisionBox[0]-camCollisions[1];
            dist[2] = camCollisions[2]-objectArray[d].collisionBox[3];
            dist[3] = objectArray[d].collisionBox[2]-camCollisions[3];
            dist[4] = camCollisions[4]-objectArray[d].collisionBox[5];
            dist[5] = objectArray[d].collisionBox[4]-camCollisions[5];
        }
        else{
            dist[0] = objectArray[i].collisionBox[0]-objectArray[d].collisionBox[1];
            dist[1] = objectArray[d].collisionBox[0]-objectArray[i].collisionBox[1];
            dist[2] = objectArray[i].collisionBox[2]-objectArray[d].collisionBox[3];
            dist[3] = objectArray[d].collisionBox[2]-objectArray[i].collisionBox[3];
            dist[4] = objectArray[i].collisionBox[4]-objectArray[d].collisionBox[5];
            dist[5] = objectArray[d].collisionBox[4]-objectArray[i].collisionBox[5];
        }

        int min = 0;
        for(int e=1;e<6;e++){
            if(dist[min]>dist[e]){
                min = e;
            }
        }
        int trmod;
        if(min == 0||min == 1){
            trmod = 0;
        }
        if(min == 2||min == 3){
            trmod = 1;
        }
        if(min == 4||min == 5){
            trmod = 2;
        }

        std::cout<<trmod<<" min: "<<min<<"\n";
        if(min % 2 == 0){
            transform[trmod] = -dist[min];
        }
        else{
            transform[trmod] = dist[min];
        }
        
        if(doit){
            camera.gameObject.force(transform);
        }
        else{
            objectArray[i].force(transform);
        }
    }
};




#endif