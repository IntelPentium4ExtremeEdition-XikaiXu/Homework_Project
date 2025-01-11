#include "objPosStack.h"
#include "objPosDLinkedList.h"

#include <ctime>
#include <cstdlib>
#include <iostream>
using namespace std;

// Available Data Members from objPosStack.h (Must Review)
//
//      objPosList* myList
//      
//  This is the polymorphic list pointer to the underlying List data structure to
//   support all Stack functionalities
//
//  You should use objPosDLinkedList as your main design param


objPosStack::objPosStack()
{
    myList = new objPosDLinkedList();
    // Constructor
    // Instantiate myList as objPosDLinkedList.  You may use objPosArrayList for testing purpose only.
}


objPosStack::~objPosStack()
{
    delete myList;
    // Destructor
    // Just delete myList (and all otherheap members, if any)
}


// private helper function
void objPosStack::generateObjects(int count)
{
    
    for(int i = 0; i < count; i++){
        char Prefix = 0;
        while((Prefix > 40 && Prefix < 91)||(Prefix > 60 && Prefix < 123)){
            Prefix = (rand() % 81) + 40;
        }
        // Generate and pushes individual objPos isntances with randomly generated Prefix, Number, and Symbol.
        // The total number of generated instances is capped by input variable **count**.
        int randnum = rand() % 100;
        // 1. Generate Prefix A-Z and a-z.  Alphabetic characters only.
        // 2. Generate Number [0, 99]
        // 3. Leave Symbol as *
        // Push every randomly generately objPos into the Stack.
        objPos temp(randnum,randnum,randnum,Prefix,'*');
        push(temp);
    }

}


// private helper function
int objPosStack::sortByTenScoreBS()
{
    
    // Use BUBBLE SORT to sort all the objPos instances in the Stack in ascending order using teh doigit of 10
    //  of the **number** field of objPos.
    bool NotSorted = true;
    int count = 0;
    while(NotSorted){
        for(int i = 0; i < myList->getSize() - 1; i++){
            if((myList->get(i).getNum()/10) > (myList->get(i+1).getNum()/10)){
                myList->set(myList->get(i+1),i);
                myList->set(myList->get(i),i+1);
                count++;
            }
        }
        if(count == 0){
            NotSorted = false;
        }
        else{
            count = 0;
        }
    }
    // You can use the relevant insertion and removal methods from the objPosDLinkedList interface
    //  to complete the sorting operations.

    // Recommendation - use set() and get() - Think about how

    return 1;
}


void objPosStack::populateRandomElements(int size)
{
    // This function generates the number of randomly generated objPos instances with uninitialized
    //  x-y coordinate on the Stack, then sort them in ascending order using the digit of 10
    //  of the **number** field in objPos instances.

    // Implementation done.  You'd have to implement the following two private helper functions above.
    srand(time(NULL));
    generateObjects(size);
    sortByTenScoreBS();
}



void objPosStack::push(const objPos &thisPos) const
{
    myList->insertHead(thisPos);
    // Push thisPos on to the Stack.
    //  Think about which objPosDLinkedList method can realize this operation.
}

objPos objPosStack::pop()
{   
    objPos temp(-99, 0, 0, 0, 0);
    if(myList->isEmpty()){
        return temp;
    }
    temp = myList->removeHead();
    return temp;
    // Pop the top element of the Stack.
    //  If the Stack is empty, return objPos(-99, 0, 0, 0, 0)
    //  Think about which objPosDLinkedList methods can realize this operation.
}

objPos objPosStack::top()
{
    objPos temp(-99, 0, 0, 0, 0);
    if(myList->isEmpty()){
        return temp;
    }
    temp = myList->getHead();
    return temp;
    // Return the top element of the Stack without removing it
    //  If the Stack is empty, return objPos(-99, 0, 0, 0, 0)
    //  Think about which objPosDLinkedList methods can realize this operation.
}

int objPosStack::size()
{
    return myList->getSize();
    // Return the size of the Stack 
    //  Think about which objPosDLinkedList method can realize this operation.
}

void objPosStack::printMe()
{
    // NOT GRADED
    //  Print the contents of the Stack
    //  Think about which objPosDLinkedList method can partially realize this operation.
    //myList->printList();
    // IMPORTANT: USE THIS METHOD FOR DEBUGGING!!!
}