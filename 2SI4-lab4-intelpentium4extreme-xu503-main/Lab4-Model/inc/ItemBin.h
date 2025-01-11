#ifndef ITEMBIN_H
#define ITEMBIN_H

#include "objPos.h"
#include "objPosList.h"
#include "GameMechs.h"
#include "Player.h"
#include "objPosStack.h"

#define STACK_SIZE 100

class GameMechs;
class Player;
class objPosStack;

class ItemBin
{
    private:
        // Lab 3 - Stack
        // Generate 100 items, with pre-determined ranges of PF's and Nums
        //  So we can prep random food collections beforehand

        objPosStack *myStack;
        objPos myDrawItem;
                
        //objPos* myItem;     
                            
        GameMechs* gmRef;
        char** boardRef;

        void undrawItem();
        void DigitToChar(char result[]); // pass by ref

    public:
        ItemBin(GameMechs* gm);
        ~ItemBin();

        void drawItem();
        void generateItem();
        objPos getItem();
        
};

#endif