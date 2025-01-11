#include "GameMechs.h"
#define DEFAULT_SIZEX 30
#define DEFAULT_SIZEY 15

GameMechs::GameMechs()     //default constructor
{
    input = 0;
    score = 0;
    exitFlag = false;
    loseflag = false;
    boardSizeX = DEFAULT_SIZEX;
    boardSizeY = DEFAULT_SIZEX;
}

GameMechs::GameMechs(int boardX, int boardY)    //additional constructor
{
    input = 0;
    score = 0;
    exitFlag = false;
    loseflag = false;
    boardSizeX = boardX;
    boardSizeY = boardY;
    if(boardX <= 0){
        boardSizeX = DEFAULT_SIZEX;
    }
    if(boardY <= 0){
        boardSizeY = DEFAULT_SIZEY;
    }
}

bool GameMechs::getExitFlagStatus()
{
    return exitFlag;
}

bool GameMechs::getloseflagStatus()
{
    return loseflag = true;
}

char GameMechs::getInput()
{
    return input;
}

void GameMechs::setExitTrue()
{
    exitFlag = true;
}

void GameMechs::setloseflagTrue()
{   
    loseflag = true;
}

void GameMechs::setInput(char this_input)
{
    input = this_input; //deep copy
}

void GameMechs::clearInput()
{
    input ='\0';
}

//board size
int GameMechs::getBoardSizeX()
{
    return boardSizeX;
}
int GameMechs::getBoardSizeY()
{
    return boardSizeY;
}

//score cat
int GameMechs::getscore(){
    return score;
}
void GameMechs::scoreup(){
    score++;
}
void GameMechs::scoredown(){
    score--;
}