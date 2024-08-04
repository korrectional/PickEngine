#ifndef PICKPHYSICS_H
#define PICKPHYSICS_H


#include <iostream>
#include <SDL2/SDL.h>
#include "glad.h"
#include "UI.h"
//#include "renderer.h"
#include "GameObject.h"
//#include "Camera.h"
//#include "input.h"






class PickPhysics
{
public:
    void collisionLoop()
    {
        
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
                            goBackTransform(i,d);
                        }
                    }
                }
                else{
                    std::cout<<" "<<"\n";
                }
            }
        }



    }

    void goBackTransform(int i, int d){
        float dist[6];
        float transform[3]{0,0,0};
        dist[0] = objectArray[i].collisionBox[0]-objectArray[d].collisionBox[1];
        dist[1] = objectArray[d].collisionBox[0]-objectArray[i].collisionBox[1];
        dist[2] = objectArray[i].collisionBox[2]-objectArray[d].collisionBox[3];
        dist[3] = objectArray[d].collisionBox[2]-objectArray[i].collisionBox[3];
        dist[4] = objectArray[i].collisionBox[4]-objectArray[d].collisionBox[5];
        dist[5] = objectArray[d].collisionBox[4]-objectArray[i].collisionBox[5];

        int min = 0;
        for(int e=1;e<6;e++){
            if(dist[min]>dist[e]){
                min = e;
            }
        }
        int trmod;
        //std::cout<<max<<"\n";
        if(min == 0||min == 1){
            trmod = 0;
        }
        if(min == 2||min == 3){
            trmod = 1;
        }
        if(min == 4||min == 5){
            trmod = 2;
        }
        transform[trmod] = -dist[min];
        
        objectArray[i].force(transform);
    }
};




#endif