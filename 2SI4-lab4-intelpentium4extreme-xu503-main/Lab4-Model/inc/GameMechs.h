#ifndef GAMEMECHS_H
#define GAMEMECHS_H

#include "Player.h"

#define WIN_SCORE 1000
#define WIN_SPECIAL_THRES 90
#define MAX_PLAYER_COUNT 4

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
        int winner;              // Allow winner to be identified
        
        void setLoseFlag();
        void setInitBoard();
        bool checkInput();

    public:
        GameMechs();
        ~GameMechs();

        int getBoardSizeX() const;
        int getBoardSizeY() const;
        int getWinScore() const;
        int getWinnerID() const;
        int getSpecialThreshold() const;
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
        void setWinner(Player* playerRef);
};

#endif