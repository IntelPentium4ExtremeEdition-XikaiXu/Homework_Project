#include "objPosArrayList.h"
#include<iostream>

using namespace std;

objPosArrayList::objPosArrayList(){
    sizeList = 0;
    sizeArray = ARRAY_MAX_CAP;
    aList = new objPos [ARRAY_MAX_CAP];
}

objPosArrayList::objPosArrayList(int sList,int sArray){
    sizeList = sList;
    sizeArray = sArray;
    aList=new objPos [sizeArray];
}

objPosArrayList::objPosArrayList(const objPosArrayList &ArrayList){
    sizeList=ArrayList.sizeList;
    sizeArray=ArrayList.sizeArray;
    aList=new objPos [ArrayList.sizeArray];
}
objPosArrayList::~objPosArrayList(){
    delete [] aList;
}
int objPosArrayList::getSize(){
    return sizeList; 
}
void objPosArrayList::insertHead(objPos thisPos){  
    if(sizeList==sizeArray)
    {
        return;
    }
    
    for(int i=sizeList; i>0; i--)
    {
        aList[i]=aList[i-1];
    }
    aList[0].x= thisPos.x;
    aList[0].y= thisPos.y;
    aList[0].symbol=thisPos.symbol;
    sizeList++;
    
}
void objPosArrayList::insertTail(objPos thisPos){
    if(sizeList==sizeArray)
    {
        return;
    }
 

    aList[sizeList].x= thisPos.x;
    aList[sizeList].y= thisPos.y;
    aList[sizeList].symbol=thisPos.symbol;
    sizeList++;
}
void objPosArrayList::removeHead(){
    if(sizeList==0)
    {
        return;
    }
    for(int i=1;i<sizeList;i++)
    {
        aList[i-1]=aList[i];
    }
    sizeList--;
}
void objPosArrayList::removeTail(){
    if(sizeList==0)
    {
        return;
    }
    sizeList--;
}
void objPosArrayList::getHeadElement(objPos &returnPos){
    returnPos.symbol=aList[0].symbol;
    returnPos.x=aList[0].x;
    returnPos.y=aList[0].y;
}
void objPosArrayList::getTailElement(objPos &returnPos){
    returnPos.symbol=aList[sizeList-1].symbol;
    returnPos.x=aList[sizeList-1].x;
    returnPos.y=aList[sizeList-1].y;
}
void objPosArrayList::getElement(objPos &returnPos, int index){
    returnPos.symbol=aList[index].symbol;
    returnPos.x=aList[index].x;
    returnPos.y=aList[index].y;
}

bool objPosArrayList::detect_to_print(int x, int y){   //get a bool to make the printing porcess convenient

    for(int z = 0 ; z < sizeList ; z++){   
        if(aList[z].x == x && aList[z].y == y){
            print_pos = z;
            return true;
        }
    }
    return false;
}

char objPosArrayList::detect_get_char(){
    return aList[print_pos].symbol;
}