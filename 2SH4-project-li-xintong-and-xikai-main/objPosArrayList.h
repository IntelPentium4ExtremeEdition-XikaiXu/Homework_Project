#ifndef OBJPOS_ARRAYLIST_H
#define OBJPOS_ARRAYLIST_H

#define ARRAY_MAX_CAP 200

#include "objPos.h"

class objPosArrayList
{
    private:
        objPos* aList;
        int sizeList; //snake length mapping
        int sizeArray; //acutal snake body length
        int print_pos;//specific for print element position with same x and y value of the printer

    public:
        objPosArrayList();
        objPosArrayList(int sList,int sArray);//additional constructor
        objPosArrayList(const objPosArrayList &ArrayList); //deep copy constructor

        ~objPosArrayList();

        int getSize();
        
        //snake operation interact with snake 
        void insertHead(objPos thisPos);
        void insertTail(objPos thisPos);
        void removeHead();
        void removeTail();
        
        //snake feature, using for snake 
        void getHeadElement(objPos &returnPos);
        void getTailElement(objPos &returnPos);
        void getElement(objPos &returnPos, int index);

        //food and snake print 
        bool detect_to_print(int x, int y);
        //food and snake print element
        char detect_get_char();
};

#endif