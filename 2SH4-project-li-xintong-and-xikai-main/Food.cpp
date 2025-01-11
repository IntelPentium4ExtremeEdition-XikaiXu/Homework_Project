#include "Food.h"
#include "objPos.h"
#include "objPosArrayList.h"
#include "GameMechs.h"

Food::Food(GameMechs* thisgm){
    foodBucket = new objPosArrayList();
    boundx = thisgm -> getBoardSizeX();
    boundy = thisgm -> getBoardSizeY();
}

Food::~Food(){
    delete foodBucket;
}

void Food::generatefood()
{   
    bool pass = false;
    
    while(!pass){
        
        for(int i = 0; i < 5 ; i++){
            do{
            tempfood.x =rand()%(boundx-2)+1;  //random create the food postion to make sure that they are in the board
            tempfood.y =rand()%(boundy-2)+1;
            tempfood.symbol = (rand()%93) + 33; //do not have ' '
            }
            while(tempfood.x < 2 || tempfood.y < 2); //avoid the food to create at the corner of the board which is easy to suicide for snake to eat
            foodBucket -> insertHead(tempfood); 
        }
        for(int j = 0; j < 4 ; j++){
            objPos reference1;  //to check the food whether they are repetitive or not.
            objPos reference2;
            foodBucket -> getElement(reference1, j);
            for(int k = j; k < 3 ;k++)
            {
                foodBucket -> getElement(reference2, k+1);
                if(reference1.x == reference2.x && reference1.y == reference2.y) //like selection sort comparson
                {
                    pass = false;
                    for(int z = 0; z<5; z++)
                    {
                        foodBucket ->removeHead();
                    }
                }
                else{
                    pass = true;                    
                }
            }
        }
    }
}

void Food::getFoodbucket(objPosArrayList &Food_list){
    int a = foodBucket -> getSize();
    for(int i = 0; i < 5; i++){
        objPos a;
        foodBucket -> getElement(a,i);  //copy the foodbucket into the food list
        Food_list.insertTail(a);
    }
}