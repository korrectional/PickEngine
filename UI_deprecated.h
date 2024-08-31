#pragma once



#include <iostream>
#include "font.h"
#include "glad/glad.h"





bool playing = false;




class UI_deprecated{
public:








    

    void RenderText(GLuint shader, GLuint VAO, char* words, int amountChars,float positionX, float positionY ,float distans, int coords = -1, float transform = -1)
    {   
        if(coords != -1)
        {
            if(transform<0){
                words[0] = '-';
                words[1] = char('0' + int(transform*-1/100));
                words[2] = char('0' + int(transform*-1/10));
                words[3] = char('0' + int(transform*-1)%10);
                words[4] = '.';
                words[5] = char('0' + int(transform*-1*10)%10);
                words[6] = char('0' + int(transform*-1*100)%10);
            }
            else{
                words[0] = char('0' + int(transform/1000));
                words[1] = char('0' + int(transform/100));
                words[2] = char('0' + int(transform/10));
                words[3] = char('0' + int(transform)%10);
                words[4] = '.';
                words[5] = char('0' + int(transform*10)%10);
                words[6] = char('0' + int(transform*100)%10);
            }
        }
        
        
        
        amountChars --;
        int letterInt;
        for(int i=0;i<amountChars;i++){
            letterInt = checkLetters(words[i]);
            if(letterInt == -1){return;}if(letterInt == 0){return;}if(letterInt == 1){continue;}


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



















    int checkLetters(char letter){
        switch (letter) {
            case '\0':
                return 1;
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
            
            case '-':
                return 51;
            case '.':
                return 52;

            case '0':
                return 54;
            case '1':
                return 55;
            case '2':
                return 56;
            case '3':
                return 57;
            case '4':
                return 58;
            case '5':
                return 59;
            case '6':
                return 60;
            case '7':
                return 61;
            case '8':
                return 62;
            case '9':
                return 63;
                

                
            default:
                std::cout<<"NOT APPLIABLE"<<": "<<letter<<"\n";
                return 0;
                break;
        }
    }
};




