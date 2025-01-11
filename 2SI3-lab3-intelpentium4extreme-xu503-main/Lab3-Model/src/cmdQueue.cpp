#include "cmdQueue.h"

#include <iostream>
using namespace std;

// Available Data Members from objPosStack.h (Must Review)
//
//      DLinkedList<char>* myQueue
//      
//  This is the character-type template Doubly Linked List class to support
//   all the character command Queue operations
//
//  You should also review the DLinkedList<> template class (identical to the lecture examples)


cmdQueue::cmdQueue()
{
    myQueue = new DLinkedList<char>;
    // Constructor
    //  Instantiate myQueue as DLinkedList<char> type to support the queue implementations
}

cmdQueue::~cmdQueue()
{
    myQueue->makeEmpty();
    delete myQueue;
    // Destructor 
    //  Destroy myQueue on the heap (and also for all other heap members, if any)
}

void cmdQueue::enqueue(char thisCmd)
{
    myQueue->addLast(thisCmd);
    // Enqueue thisCmd into the Queue
    //  Think about what underlying DLinkedList method can support this operation
}

char cmdQueue::dequeue()
{
    char temp;
    if(myQueue == NULL){
        return NULL;
    }
    temp = myQueue->removeFirst();
    return temp;
    // Dequeue the oldest character command from the queue and return
    // If no more commands to dequeue, return NULL character ('\0')
    //  Think about what underlying DLinkedList method can support this operation    
}

int cmdQueue::getSize()
{
    return myQueue->getSize();
    // Return the size of the Queue
    //  Think about what underlying DLinkedList method can support this operation
}

void cmdQueue::clearQueue()
{
    myQueue->makeEmpty();
    // Clear all tbe elements in the queue
    //  Think about what underlying DLinkedList method can support this operation
}

void cmdQueue::printMe()
{
    // NOT GRADED
    //  Print the contents of the Queue
    //  Think about which DLinkedList method can partially realize this operation.
    //myQueue->printList();
    // IMPORTANT: USE THIS METHOD FOR DEBUGGING!!!
}