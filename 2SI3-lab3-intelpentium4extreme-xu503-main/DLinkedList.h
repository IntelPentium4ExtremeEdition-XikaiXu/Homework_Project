/*
 * DLinkedList.h
 *
 *  Created on: Dec 8, 2022
 *      Author: Scott Chen
 */

#ifndef DLINKEDLIST_H_
#define DLINKEDLIST_H_

// Node Template Class – Supporting Different Data Types
template <typename E>
class DNode   //node part of the storagement system combined with different dataa type with extra dirsction pointer operator 
{
	public:
		E data;
		DNode<E> *next;
		DNode<E> *prev;

		DNode(const E &e, DNode<E> *n, DNode<E> *p)
		{
			data = e;
			next = n;
			prev = p;
		}
};


template <typename E>
class DLinkedList     
{
	private:
		DNode<E> *head;  	// data member
		DNode<E> *tail;  	// data member
		int size;

	public:	// Public Interface
		DLinkedList();		// Constructor
		~DLinkedList();		// Destructor

		int getSize();
		void makeEmpty();    		// Clear the entire list
		void addFirst(const E &e);	// Add Element to Head
		void addLast(const E &e);	// Add Element to Tail
		E removeFirst();			// Remove Element from Head
		E removeLast();				// Remove Element from Tail;
		void remove(const E &e);	// Remove specified value
		void printList();		 	// Output list contents

		// More functionalities can be added to ADT
};

#endif /* DLINKEDLIST_H_ */
