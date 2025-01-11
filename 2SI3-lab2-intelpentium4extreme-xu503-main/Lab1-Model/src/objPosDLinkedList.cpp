#include "objPosDLinkedList.h"
#include <iostream>
using namespace std;

// Develop the objPos Doubly Linked List here.  
// Use the Test cases Test.cpp to complete the Test-Driven Development

objPosDLinkedList::objPosDLinkedList()
{
    listHead = new DNode();  //create a real stuff linked with the element 
    listTail = new DNode();

    listHead->next = listTail;//cnnected the back and frone
    listTail->prev = listHead; 

    persistHead = listHead; //reader on the empty 0 pision
    
    listSize = 0; 
    
}

objPosDLinkedList::~objPosDLinkedList()
{   
    while(listHead->next != listTail){
        DNode* recyclebin = listHead->next;
        listHead->next = recyclebin->next;
        delete recyclebin;
    }
    
    delete listTail;
    delete listHead;

}

int objPosDLinkedList::getSize()
{  
    return listSize;
  
}

bool objPosDLinkedList::isEmpty()
{
    return !listSize;
}

void objPosDLinkedList::insertHead(const objPos &thisPos)
{
    DNode *newhead = new DNode();    
    newhead->data = thisPos;

 
    newhead->next = listHead->next;
    newhead->prev = listHead;  

    newhead->prev->next = newhead;    
    newhead->next->prev = newhead;
        
    listSize++;
}

void objPosDLinkedList::insertTail(const objPos &thisPos)
{
    DNode *newtail = new DNode();
    newtail->data = thisPos;

    newtail->next = listTail; //setup the back of the data type 
    newtail->prev = listTail->prev;

    newtail->prev->next = newtail; //back and forward build the connection
    newtail->next->prev = newtail;

    listSize++;
}

void objPosDLinkedList::insert(const objPos &thisPos, int index)
{
    
    if(listSize == 0 || index - 1 > listSize || index < 0){ //process of inserting different elements 
        if(index <= 0){
            objPosDLinkedList::insertHead(thisPos);
            return;
        }
        else{
            objPosDLinkedList::insertTail(thisPos);
            return;
        }
    }
    
    DNode *newnode = new DNode();
    newnode->data = thisPos;

    int counter = 0;
    resetReadPos();
    //persistHead = listHead->next;//set the reader to the front 
    while(counter < index){
        persistHead = persistHead->next;
        counter++;
    }
    //when target head reached the specificed position! 

    newnode->prev = persistHead;
    newnode->next = persistHead->next;

    persistHead->next = newnode;
    persistHead->next->next->prev = newnode; //let the shawdow told the truth

    listSize++;
    
}

objPos objPosDLinkedList::getHead() const
{
    return listHead->next->data;
}

objPos objPosDLinkedList::getTail() const
{
    return listTail->prev->data;
}

objPos objPosDLinkedList::get(int index) const
{
    
    if(index >listSize-1){
        return objPosDLinkedList::getTail();
    }
    if(index<0){
        return objPosDLinkedList::getHead();
    }
    
    DNode *Tempreader = listHead->next;
    int counter = index;

    while(counter > 0){
        Tempreader = Tempreader->next;
        counter--;
    }

    return Tempreader->data;
  
    
}

objPos objPosDLinkedList::getNext()
{
    if(persistHead->next == listTail){
        resetReadPos();
        return objPos(-99,0,0,0,0);
    }
    persistHead = persistHead->next;

    return persistHead->data;
}

void objPosDLinkedList::resetReadPos()
{
    persistHead = listHead;
}

void objPosDLinkedList::set(const objPos &thisPos, int index)
{
    if(index>=listSize-1) 
    {
        listTail->prev->data = thisPos;
        return;
    }
    else if(index<=0)
    {
        listHead->next->data = thisPos;
        return;
    } 

    resetReadPos();
    persistHead = listHead->next; //1st node

    int counter = index;
    while(counter > 0){
        persistHead = persistHead->next;
        counter--;
    }

    persistHead->data = thisPos;
    
}


objPos objPosDLinkedList::removeHead()
{
    
    if(isEmpty()){
        return objPos(-99,0,0,0,0);
    }
    objPos data;
    DNode *garbage = listHead->next;

    data = garbage->data;

    listHead->next->next->prev = listHead;
    //the second pard's prev point to listhead
    listHead->next = listHead->next->next;
    //listhead's next point to seconds' object 
    listSize--;

    delete garbage;
    return data;
    
}

objPos objPosDLinkedList::removeTail()
{
    
    if(isEmpty()){
        return objPos(-99,0,0,0,0);
    }
    objPos data;
    DNode *garbage = listTail->prev;
    data = garbage->data;
    listTail->prev->prev->next = listTail;

    listTail->prev = listTail->prev->prev;

    listSize--;

    delete garbage;
    return data;
    

}

objPos objPosDLinkedList::remove(int index)
{
    
    if(isEmpty()){
        return objPos(-99,0,0,0,0);
    }
    if(index>=listSize-1){
        return removeTail();
    }
    if(index<=0){
        return removeHead();
    } 
    resetReadPos();
    persistHead = persistHead->next; //set to 1st
    int counter = index;
    DNode* garbage;
    objPos data;
    while(counter > 0){
        persistHead = persistHead->next;
        counter--;
    }

    garbage = persistHead;

    persistHead->prev->next = persistHead->next;
    persistHead->next->prev = persistHead->prev;

    data = garbage->data;
    delete garbage;

    listSize--;
    return data;
    
}


void objPosDLinkedList::printList() const
{
    
    DNode *Tempreader;
    Tempreader = listHead;
    cout<< "[";
    objPos PrintBuffer;
    while(Tempreader != listTail){
        Tempreader = Tempreader->next;  
        PrintBuffer = Tempreader->data;      
        PrintBuffer.printObjPos();
    }
    cout<<"]"<<endl;
    
}


