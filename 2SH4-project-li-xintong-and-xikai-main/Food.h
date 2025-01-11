#ifndef FOOD_H
#define FOOD_H

#include<iostream>
#include "objPos.h"
#include "objPosArrayList.h"
#include "GameMechs.h"
#include "Player.h"


class Food{
    private:
        objPosArrayList* foodBucket; //the list of five food 
        
        objPos tempfood;
        int boundx;
        int boundy;

    public:
        Food(GameMechs* thisgm);//constructor that creates a bucket for 5 food and gives the boundary of food.
        ~Food();
        void generatefood();//create 5 food, make sure that they  are in the correct region and check it whether they are repetitive or not.
        void getFoodbucket(objPosArrayList &Food_list); //return food list 
};
#endif
