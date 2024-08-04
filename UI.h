#pragma once
#include <SDL2/SDL.h>
#include <iostream>
#include "font.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>




/*
return 0 = invalid character
return 1 = space


*/





class UI{
public:

    

    void RenderText(GLuint shader, GLuint VAO, const char* words, int amountChars,float positionX, float positionY ,float distans)
    {
        amountChars --;
        int letterInt;
        for(int i=0;i<amountChars;i++){
            letterInt = checkLetters(words[i]);
            if(letterInt == 0){return;}if(letterInt == 1){continue;}


            float distance = float(i)*0.08*distans;

            
            int letter = letterInt     -6; /// THE NUMBER
            const int T[8] = { font8b[letter][0], font8b[letter][1], font8b[letter][2], font8b[letter][3], 
                                font8b[letter][4], font8b[letter][5], font8b[letter][6], font8b[letter][7]};   
            int x,y;
            int set;
            glUseProgram(shader);
            for (x=0; x < 8; x++) {
                for (y=0; y < 8; y++) {
                    set = T[x] & 1 << y;

                    
                    if(set > 0){
                        int posLoc = glGetUniformLocation(shader, "pos");
                        glUniform2f(posLoc,0+(float(y)/100)+distance+positionX,0-(float(x)/100)-positionY);
                        
                        glBindVertexArray(VAO);
                        glDrawArrays(GL_TRIANGLES, 0, 6);

                    }

                    
                    
                }
        }
    }


        

    };





    float* ButtonLogic(const SDL_Event& ev, float change, float* location){
        if(ev.button.x >= location[0] &&
            ev.button.x <= location[2] &&
            ev.button.y >= location[1] &&
            ev.button.y <= location[3])
        {
        
            //position = position + change;  // TRYNA MAKE IT MOVE!!!
            float* velocity = new float[3];
            velocity[0] = 0.0f;
            velocity[1] = 0.0f;
            velocity[2] = change;

            return velocity;


        }
        else{
            float* velocity = new float[3];
            velocity[0] = 0.0f;
            velocity[1] = 0.0f;
            velocity[2] = 0.0f;
//
            return velocity;
        }
        
    };








    int checkLetters(char letter){
        switch (letter) {
            case ' ':
                return 1;
            case 'A':
                return 71;
            case 'B':
                return 72;
            case 'C':
                return 73;
            case 'D':
                return 74;
            case 'E':
                return 75;
            case 'F':
                return 76;
            case 'G':
                return 77;
            case 'H':
                return 78;
            case 'I':
                return 79;
            case 'J':
                return 80;
            case 'K':
                return 81;
            case 'L':
                return 82;
            case 'M':
                return 83;
            case 'N':
                return 84;
            case 'O':
                return 85;
            case 'P':
                return 86;
            case 'Q':
                return 87;
            case 'R':
                return 88;
            case 'S':
                return 89;
            case 'T':
                return 90;
            case 'U':
                return 91;
            case 'V':
                return 92;
            case 'W':
                return 93;
            case 'X':
                return 94;
            case 'Y':
                return 95;
            case 'Z':
                return 96;
            

                

                
            default:
                std::cout<<"NOT APPLIABLE"<<": "<<letter<<"\n";
                return 0;
                break;
        }
    }
};

