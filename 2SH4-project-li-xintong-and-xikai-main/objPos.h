#ifndef OBJPOS_H
#define OBJPOS_H
using namespace std;
#include<iostream>

class objPos
{
    public:
        int x;
        int y;
        char symbol;

        objPos(); //DECLARE 
        objPos(objPos &o); // copy constructor //require a deep copy
        objPos(int xPos, int yPos, char sym); //alll obj characteristic

        void setObjPos(objPos o);        
        void setObjPos(int xPos, int yPos, char sym);  
        void getObjPos(objPos &returnPos);
        

        char getSymbol();

        //comparson function
        bool isPosEqual(const objPos* refPos);
        char getSymbolIfPosEqual(const objPos* refPos);
};

#endif