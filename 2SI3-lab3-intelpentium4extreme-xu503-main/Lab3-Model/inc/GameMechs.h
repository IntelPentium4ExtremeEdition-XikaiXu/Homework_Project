#ifndef GAMEMECHS_H
#define GAMEMECHS_H

#include "Player.h"

// Forward Declaration
class Player;

class GameMechs
{
    private:
        char** gameBoard;
        int boardSizeX;
        int boardSizeY;

        bool exitFlag;   
        bool loseFlag;     
        int delayConst;

        char cmd;

        Player** playerList;     // array of player reference
        int playerCount;
        
        void setLoseFlag();
        void setInitBoard();
        bool checkInput();

    public:
        GameMechs();
        ~GameMechs();

        int getBoardSizeX() const;
        int getBoardSizeY() const;
        bool getExitFlag() const;
        bool getLoseFlag() const;
        char getCMD() const;
        char** getBoardRef() const;
        Player** getPlayerListRef() const;
        int getPlayerCount() const;
                
        void processInput();
        void applyDelay();

        void addPlayer(Player* pl);

        void setGameLost();
        void setExitFlag();

};

#endif