#include "MacUILib.h"
#include "GameMechs.h"
#include "ScreenDrawer.h"
#include "Player.h"
#include "ItemBin.h"

#include <iostream>
using namespace std;

int main(int argc, char* argv[])
{
    // DECLARATION (LOCAL, on Stack)
    //////////////////////////////
    GameMechs *myGM;
    ScreenDrawer *myDrawer;
    Player* player1;
    ItemBin* myBin;


    // INITIALIZATION
    //////////////////////////////
    MacUILib_init();                            // Initialilze MacUI Library
    
    myGM = new GameMechs();                     // Create GM instance on the heap        
    myBin = new ItemBin(myGM);                  // Create the item bin on the heap
    player1 = new Player(3, 3, '@', myGM, myBin);      // Create first Player on the heap
    myDrawer = new ScreenDrawer(myGM, player1, myBin); // Create Screen Drawer Module on the heap
    
    myBin->generateItem();
   

    //////////////////////////////
    // PROGRAM LOOP
    //////////////////////////////
    while(myGM->getExitFlag() == false)
    {
        // I. GET INPUT
        myGM->processInput();
       
        // II. RUN LOGIC                 
        player1->movePlayer();   
                      
        // III. DRAW SCREEN  
        myDrawer->Draw();            
        myDrawer->DrawAverageComputationTime(myGM->getAverageTime());        

        // IV. LOOP DELAY
        myGM->applyDelay();
    }



    // CLEANUP
    //////////////////////////////
    myDrawer->DrawEndGame();

    MacUILib_uninit();
    delete myGM;            // Remove GM instance on the heap
    delete myDrawer;
    delete player1;
    delete myBin;

    return 0;
}