#include "ItemBin.h"
#include <ctime>
#include <cstdlib>
#include <iostream>
using namespace std;

ItemBin::ItemBin(GameMechs* gm)
{
    gmRef = gm;
    boardRef = gmRef->getBoardRef();  
    myItem = new objPos(12, 12, 32, 'A', '*');  

    srand(time(NULL));    
}

ItemBin::~ItemBin()
{
    delete myItem;
}

void ItemBin::drawItem()
{
    int x = myItem->getX();    
    int y = myItem->getY();        
    char num[2];  // convert number to displayable chars      
    DigitToChar(num);     

    boardRef[y][x] = myItem->getSym();    
    boardRef[y-1][x-1] = myItem->getPF();    
    boardRef[y-1][x] = num[0];    
    boardRef[y-1][x+1] = num[1];    
}      

void ItemBin::undrawItem()
{
    int x = myItem->getX();   
    int y = myItem->getY();

    boardRef[y][x] = ' ';
    boardRef[y-1][x-1] = ' ';
    boardRef[y-1][x] = ' ';
    boardRef[y-1][x+1] = ' ';
}

void ItemBin::DigitToChar(char result[])
{
    int number = myItem->getNum();     
    result[0] = (number / 10) + '0';      
    result[1] = (number % 10) + '0';    
}    


void ItemBin::generateItem()
{
    // Step 1: Get Player Ref from GameMech for Player pos
    Player** plList = gmRef->getPlayerListRef();          
    objPosList *playerPos = plList[0]->getPlayerPos();    

    //int bitVec[gmRef->getBoardSizeX()][gmRef->getBoardSizeY()]= {0};

    // to prevent stack overflow
    int xsize = gmRef->getBoardSizeX();       
    int ysize = gmRef->getBoardSizeY();       
    int** bitVec = new int*[xsize];           
    for(int i = 0; i < xsize; i++)           
       bitVec[i] = new int[ysize];            


    int playerLength = playerPos->getSize();    

    objPos target;  
    playerPos->resetReadPos();  

    for(int i = 0; i < playerLength; i++) 
    {
        target = playerPos->getNext();  
        bitVec[target.getX()][target.getY()] = 1;          
    }    

    int randCandidateX = 0;
    int randCandidateY = 0;
    int randCandidate = 0;

    
    do
    {
        randCandidateX = rand() % (gmRef->getBoardSizeX() - 4) + 2;
        randCandidateY = rand() % (gmRef->getBoardSizeY() - 4) + 2;
    } while(bitVec[randCandidateX][randCandidateY] != 0); 

    undrawItem();   

    myItem->setX(randCandidateX);
    myItem->setY(randCandidateY);        

    // Prefix Generation
    // PF   [a-z, A-Z]
    randCandidate = rand() % 26 + 'A';  // 26 alpabets          
    if(rand() % 2) randCandidate += 32; // randomly lowercased 
    myItem->setPF((char)randCandidate); 

    // Number Generation
    // Number [00, 99]
    myItem->setNum(rand() % 100);   

    drawItem();

    for(int i = 0; i < xsize; i++)
        delete[] bitVec[i];
    delete[] bitVec;
}


objPos ItemBin::getItem()
{
    objPos temp(myItem->getX(), myItem->getY(), myItem->getNum(), myItem->getPF(), myItem->getSym());
    // constructor     
    return temp;  // copy constructor     
}    
