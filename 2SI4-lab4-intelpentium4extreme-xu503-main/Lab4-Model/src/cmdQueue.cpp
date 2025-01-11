#include "cmdQUeue.h"

#include <iostream>
using namespace std;

cmdQueue::cmdQueue()
{
    myQueue = new DLinkedList<char>();
}

cmdQueue::~cmdQueue()
{
    delete myQueue;
}

void cmdQueue::enqueue(char thisCmd)
{
    myQueue->addFirst(thisCmd);
}

char cmdQueue::dequeue()
{
    return myQueue->removeLast();
}

int cmdQueue::getSize()
{
    return myQueue->getSize();
}

void cmdQueue::clearQueue()
{
    myQueue->makeEmpty();
}

void cmdQueue::printMe()
{
    cout << "Command Queue Contains: ";
    myQueue->printList();
    cout << "Command Queue Size: " << myQueue->getSize() << endl;
}