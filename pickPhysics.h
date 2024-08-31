#ifndef PICKPHYSICS_H
#define PICKPHYSICS_H


#include <iostream>
#include <SDL2/SDL.h>
#include "gameObject.h"
#include "camera.h"






class PickPhysics
{
public:
    float camCollisions[6];
    void collisionLoop()
    {
        camera.gameObject.updateCollider(false);
        for(int i=0;i<6;i++){camCollisions[i] = camera.gameObject.collisionBox[i];}
        
        for(int i=0;i<gameObjectCount;i++){
            objectArray[i].updateCollider(false);
        }
        for(int i=0;i<gameObjectCount;i++){
            for(int d=0;d<gameObjectCount;d++){
                if(d==i){
                    continue;
                }
                else if(d<i){
                    continue;
                }
                for(int g = 0; g<6; g++){
                    if(objectArray[i].collisionBox[g]>objectArray[d].collisionBox[g+1] && objectArray[i].collisionBox[g+1]<objectArray[d].collisionBox[g]){
                        g++;
                    }else{
                        g = 10;
                    }
                    if(g == 5){
                        objectArray[i].onCollision(i, d);
                        objectArray[d].onCollision(d, i);
                        goBackTransform(i,d, false);
                    }
                }
            }
        }

        for(int d=0;d<gameObjectCount;d++){
            for(int g = 0; g<6; g++){
                    if(camCollisions[g]>objectArray[d].collisionBox[g+1] && camCollisions[g+1]<objectArray[d].collisionBox[g]){
                        g++;
                    }else{
                        g = 10;
                    }
                    if(g == 5){
                        goBackTransform(0,d, true);
                    }
            }
        }
    }





    void goBackTransform(int i, int d, bool doit){
        float dist[6];
        float transform[3]{0,0,0};
        if(doit){

            for(int g=0;g<5;g=g+2){
                dist[g] = camCollisions[g]-objectArray[d].collisionBox[g+1];
                dist[g+1] = objectArray[d].collisionBox[g]-camCollisions[g+1];
            }
        }
        else{
            for(int g=0;g<5;g=g+2){
                dist[g] = objectArray[i].collisionBox[g]-objectArray[d].collisionBox[g+1];
                dist[g+1] = objectArray[d].collisionBox[g]-objectArray[i].collisionBox[g+1];
            }

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