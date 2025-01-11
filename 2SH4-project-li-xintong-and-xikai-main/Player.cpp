#include "Player.h"
#include "MacUILib.h"
#include "objPosArrayList.h"
#include "Food.h"
#include "objPos.h"
#include "GameMechs.h"

Player::Player(GameMechs* thisGMRef) //can been seen as the initial construct function //can been seen as the initial construct function
{
    myDir = STOP;
    
    playerPosList = new objPosArrayList();
    
    objPos TEMP;
    TEMP.setObjPos((thisGMRef->getBoardSizeX())/2,(thisGMRef->getBoardSizeY())/2,'*'); //create the snake head to begin at the centre of the board
    playerPosList -> insertHead(TEMP);

    mainGameMechsRef = thisGMRef;

    award = 0;  //score
}

Player::~Player()
{   
    
    // delete any heap members here
    delete playerPosList;
}

void Player::getPlayerPos(objPosArrayList &returnPosList) //the snake head location, always print add very beginning first of the element. 
{
    int a = playerPosList -> getSize();
    for(int i=0; (i < playerPosList -> getSize()); i++)
    {   
        objPos a;
        playerPosList->getElement(a,i);
        returnPosList.insertTail(a);
    }
}

void Player::updatePlayerDir() // CONNECTED WITH THE PLAY FUNCTION FIXED 
{
    char input = mainGameMechsRef -> getInput();
    switch(input)
    {
        case 'W':
        case 'w':
            if(myDir != DOWN && myDir != UP)
                myDir = UP;
            break;
        case 'A':
        case 'a':
            if(myDir != RIGHT && myDir != LEFT)
                myDir = LEFT;
            break;
        case 'S':
        case 's':
            if(myDir != DOWN && myDir != UP)
                myDir = DOWN;
            break;
        case 'D':
        case 'd':
            if(myDir != RIGHT && myDir != LEFT)
                myDir = RIGHT;
            break;
        case 'T':
        case 't':
            myDir = STOP;
            break;
    } 
    mainGameMechsRef -> clearInput();       
}

void Player::movePlayer()  
{
    //myDir from input of analysitic 
    objPos a; //calculate the head position
    playerPosList -> getHeadElement(a);
    //movement for the snake
    //move the snake by add a head and remove a tail
    switch(myDir){
        
        case UP:

            a.y--;
            if(a.y == 0){
                a.y = (mainGameMechsRef -> getBoardSizeY()) - 1;
            }            
            playerPosList -> insertHead(a);
            playerPosList -> removeTail();
            break;
        case DOWN:

            a.y++;
            if(a.y == mainGameMechsRef->getBoardSizeY()){
                a.y = 1;
            }
            playerPosList -> insertHead(a);
            playerPosList -> removeTail();
            break;
        case LEFT:

            a.x--;
            
            if(a.x == 0){
                a.x = (mainGameMechsRef -> getBoardSizeX()) - 1;
            }
            playerPosList -> insertHead(a);
            playerPosList -> removeTail();
            break;
        case RIGHT:
            a.x++;
            
            if(a.x == mainGameMechsRef->getBoardSizeX()){
                a.x = 1;
            }
            playerPosList -> insertHead(a);
            playerPosList -> removeTail();
            break;
    }
   
}

bool Player::checkfoodconsumption(objPosArrayList &food_list){
    objPos playerPOS;    //identify the food is eaten by the snake and control the change of length and score for the snake
    objPos TEMP_FOODPOS;
    playerPosList -> getHeadElement(playerPOS);
    for(int i = 0; i < 5 ; i++){
        food_list.getElement(TEMP_FOODPOS,i);
        //different foods with different effects (normal food and special food)
        if(TEMP_FOODPOS.isPosEqual(&playerPOS)&&TEMP_FOODPOS.symbol >= 123){
            mainGameMechsRef -> scoreup(); 
            mainGameMechsRef -> scoreup(); 
            increasingsnake();
            award = 1;
            return true;
        }
        else if(TEMP_FOODPOS.isPosEqual(&playerPOS)&&TEMP_FOODPOS.symbol >= 61 && TEMP_FOODPOS.symbol < 123){
            mainGameMechsRef -> scoreup();
            increasingsnake();
            award = 2;
            return true;
        }
        else if(TEMP_FOODPOS.isPosEqual(&playerPOS)&&TEMP_FOODPOS.symbol >= 41 && TEMP_FOODPOS.symbol < 61){
            mainGameMechsRef -> scoreup();
            mainGameMechsRef -> scoreup();
            mainGameMechsRef -> scoreup();
            mainGameMechsRef -> scoreup();
            playerPosList ->removeTail();
            award = 3;
            return true;
        }
        else if(TEMP_FOODPOS.isPosEqual(&playerPOS)&&TEMP_FOODPOS.symbol >= 35 && TEMP_FOODPOS.symbol < 41){
            increasingsnake();
            award = 4;
            return true;
        }
        else if(TEMP_FOODPOS.isPosEqual(&playerPOS)&&TEMP_FOODPOS.symbol == 34){
            award = 5;
            for(int i = 0 ; i < 10 ; i++){
                increasingsnake();
                mainGameMechsRef -> scoreup();
            }
            return true;
        }
        else if(TEMP_FOODPOS.isPosEqual(&playerPOS)&&TEMP_FOODPOS.symbol == 33){
            award = 6;
            return true;
            mainGameMechsRef -> setExitTrue();
        }
    }
    award = 0;
    return false;
}

int Player::getaward(){
    return award;
}
void Player::increasingsnake(){
    objPos head;
    playerPosList -> getHeadElement(head);
    playerPosList -> insertHead(head);
}

bool Player::checkselfcollision()  //check the condition of suicide by compare the pos of head with pos with bodies
{
    objPos head;
    objPos body;
    for(int i = 3 ;(i < playerPosList -> getSize()); i++)
    {
        playerPosList -> getHeadElement(head);
        playerPosList -> getElement(body,i);
        if(body.x == head.x && body.y == head.y){
            return true;
        }
    }
    return false;
}

