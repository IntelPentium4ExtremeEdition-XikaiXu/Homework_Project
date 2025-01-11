#ifndef GAMEMECHS_H
#define GAMEMECHS_H

#include <cstdlib>
#include <time.h>

#include "objPos.h"
#include "objPosArrayList.h"

using namespace std;


class GameMechs
{
    private:
        char input; //stock
        bool exitFlag; //stock
        bool loseflag; //stock
        int score; //stock
        
        int boardSizeX;
        int boardSizeY;

    public:
        GameMechs();
        GameMechs(int boardX, int boardY);

        //exit status 
        void setExitTrue();
        bool getExitFlagStatus();
        
        //loosing 
        bool getloseflagStatus();
        void setloseflagTrue();

        //input part
        void setInput(char this_input);
        char getInput();
        void clearInput();

        //board size
        int getBoardSizeX();
        int getBoardSizeY();

        //score cat
        int getscore();
        void scoreup();
        void scoredown();
};

#endif