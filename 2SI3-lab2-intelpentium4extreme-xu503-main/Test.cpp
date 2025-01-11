#include "objPos.h"
#include "objPosList.h"
#include "objPosArrayList.h"
#include "objPosDLinkedList.h"

#include <cstdlib>
#include <ctime>

#define COUNT 10
#define TOTAL_ASSERT_COUNT 439
#define TOTAL_TEST_CASES 40

#include <iostream>
using namespace std;

// ******************* //
// Turn this true once you are ready to test getNext() and resetReadPos()
bool testGetNextReady = true;
// ******************* //


objPosList *ListUnderTest;
int successCount;
int passCount;

void clearList();
objPos generateRandomPos();
bool assert_equal(int, int);
bool assert_equal(char, char);

// This is the polymorphic list changer
void createNewList()
{
	if(ListUnderTest != NULL) clearList();
	//ListUnderTest = new objPosArrayList();	
	ListUnderTest = new objPosDLinkedList();
}





void testConstructorGetSize() {
	
	bool result = true;

	cout << "TEST: testConstructorGetSize" << endl;
	createNewList();
	int expected = 0;
	int actual = ListUnderTest->getSize();	

	result = result && assert_equal(expected, actual);
	clearList();
	if(result) passCount++;
}

void testConstructorIsEmptyTrue() {
	
	bool result = true;

	cout << "TEST: testConstructorIsEmptyTrue" << endl;
	createNewList();	
	bool expected = true;
	bool actual = ListUnderTest->isEmpty();		

	result = result && assert_equal(expected, actual);
	clearList();
	if(result) passCount++;
}




// INSERT HEAD
// INSERT HEAD
// INSERT HEAD

void testInsertHeadIsEmptyFalse() {
	
	bool result = true;

	cout << "TEST: testInsertHeadIsEmptyFalse" << endl;
	createNewList();
	objPos testPos{};
	ListUnderTest->insertHead(testPos);

	bool expected = false;
	bool actual = ListUnderTest->isEmpty();	
	result = result && assert_equal(expected, actual);
	clearList();
	if(result) passCount++;
}

void testInsertHeadGetSize() {
	
	bool result = true;

	cout << "TEST: testInsertHeadGetSize" << endl;
	createNewList();
	objPos testPos{};
	ListUnderTest->insertHead(testPos);
	ListUnderTest->insertHead(testPos);
	ListUnderTest->insertHead(testPos);
	int expected = 3;
	int actual = ListUnderTest->getSize();	

	result = result && assert_equal(expected, actual);
	clearList();
	if(result) passCount++;
}

void testInsertHeadGetHead() {
	
	bool result = true;

	cout << "TEST: testInsertHeadGetHead" << endl;
	createNewList();
	objPos itemArray[COUNT];
	for(int i = 0; i < COUNT; i++)	
	{
		itemArray[i] = generateRandomPos();
		ListUnderTest->insertHead(itemArray[i]);
	}
	
	objPos expected = itemArray[COUNT-1];
	objPos actual = ListUnderTest->getHead();	

	result = result && assert_equal(expected.getX(), actual.getX());
	result = result && assert_equal(expected.getY(), actual.getY());
	result = result && assert_equal(expected.getNum(), actual.getNum());
	result = result && assert_equal(expected.getPF(), actual.getPF());
	result = result && assert_equal(expected.getSym(), actual.getSym());
	clearList();
	if(result) passCount++;
}

void testInsertHeadGetTail() {
	
	bool result = true;

	cout << "TEST: testInsertHeadGetTail" << endl;
	createNewList();
	objPos itemArray[COUNT];
	for(int i = 0; i < COUNT; i++)	
	{
		itemArray[i] = generateRandomPos();
		ListUnderTest->insertHead(itemArray[i]);
	}
	
	objPos expected = itemArray[0];
	objPos actual = ListUnderTest->getTail();	

	result = result && assert_equal(expected.getX(), actual.getX());
	result = result && assert_equal(expected.getY(), actual.getY());
	result = result && assert_equal(expected.getNum(), actual.getNum());
	result = result && assert_equal(expected.getPF(), actual.getPF());
	result = result && assert_equal(expected.getSym(), actual.getSym());
	clearList();
	if(result) passCount++;
}

void testInsertHeadGetNegTen() {
	
	bool result = true;

	cout << "TEST: testInsertHeadGetNegTen" << endl;
	createNewList();
	objPos itemArray[COUNT];
	for(int i = 0; i < COUNT; i++)	
	{
		itemArray[i] = generateRandomPos();
		ListUnderTest->insertHead(itemArray[i]);
	}
	
	objPos expected = itemArray[COUNT-1];
	objPos actual = ListUnderTest->get(-10);	

	result = result && assert_equal(expected.getX(), actual.getX());
	result = result && assert_equal(expected.getY(), actual.getY());
	result = result && assert_equal(expected.getNum(), actual.getNum());
	result = result && assert_equal(expected.getPF(), actual.getPF());
	result = result && assert_equal(expected.getSym(), actual.getSym());
	clearList();
	if(result) passCount++;
}

void testInsertHeadGetZero() {
	
	bool result = true;

	cout << "TEST: testInsertHeadGetZero" << endl;
	createNewList();
	objPos itemArray[COUNT];
	for(int i = 0; i < COUNT; i++)	
	{
		itemArray[i] = generateRandomPos();
		ListUnderTest->insertHead(itemArray[i]);
	}
	
	objPos expected = itemArray[COUNT-1];
	objPos actual = ListUnderTest->get(0);	

	result = result && assert_equal(expected.getX(), actual.getX());
	result = result && assert_equal(expected.getY(), actual.getY());
	result = result && assert_equal(expected.getNum(), actual.getNum());
	result = result && assert_equal(expected.getPF(), actual.getPF());
	result = result && assert_equal(expected.getSym(), actual.getSym());
	clearList();
	if(result) passCount++;
}

void testInsertHeadGetOne() {
	
	bool result = true;

	cout << "TEST: testInsertHeadGetOne" << endl;
	createNewList();
	objPos itemArray[COUNT];
	for(int i = 0; i < COUNT; i++)	
	{
		itemArray[i] = generateRandomPos();
		ListUnderTest->insertHead(itemArray[i]);
	}
	
	objPos expected = itemArray[COUNT-2];
	objPos actual = ListUnderTest->get(1);	

	result = result && assert_equal(expected.getX(), actual.getX());
	result = result && assert_equal(expected.getY(), actual.getY());
	result = result && assert_equal(expected.getNum(), actual.getNum());
	result = result && assert_equal(expected.getPF(), actual.getPF());
	result = result && assert_equal(expected.getSym(), actual.getSym());
	clearList();
	if(result) passCount++;
}

void testInsertHeadGetCountN3() {
	
	bool result = true;

	cout << "TEST: testInsertHeadGetCountN3" << endl;
	createNewList();
	objPos itemArray[COUNT];
	for(int i = 0; i < COUNT; i++)	
	{
		itemArray[i] = generateRandomPos();
		ListUnderTest->insertHead(itemArray[i]);
	}
	
	objPos expected = itemArray[2];
	objPos actual = ListUnderTest->get(COUNT-3);	

	result = result && assert_equal(expected.getX(), actual.getX());
	result = result && assert_equal(expected.getY(), actual.getY());
	result = result && assert_equal(expected.getNum(), actual.getNum());
	result = result && assert_equal(expected.getPF(), actual.getPF());
	result = result && assert_equal(expected.getSym(), actual.getSym());
	clearList();
	if(result) passCount++;
}

void testInsertHeadGetCountN1() {
	
	bool result = true;

	cout << "TEST: testInsertHeadGetCountN1" << endl;
	createNewList();
	objPos itemArray[COUNT];
	for(int i = 0; i < COUNT; i++)	
	{
		itemArray[i] = generateRandomPos();
		ListUnderTest->insertHead(itemArray[i]);
	}
	
	objPos expected = itemArray[0];
	objPos actual = ListUnderTest->get(COUNT-1);	

	result = result && assert_equal(expected.getX(), actual.getX());
	result = result && assert_equal(expected.getY(), actual.getY());
	result = result && assert_equal(expected.getNum(), actual.getNum());
	result = result && assert_equal(expected.getPF(), actual.getPF());
	result = result && assert_equal(expected.getSym(), actual.getSym());
	clearList();
	if(result) passCount++;
}

void testInsertHeadGetCountP5() {
	
	bool result = true;

	cout << "TEST: testInsertHeadGetCountP5" << endl;
	createNewList();
	objPos itemArray[COUNT];
	for(int i = 0; i < COUNT; i++)	
	{
		itemArray[i] = generateRandomPos();
		ListUnderTest->insertHead(itemArray[i]);
	}
	
	objPos expected = itemArray[0];
	objPos actual = ListUnderTest->get(COUNT+5);	

	result = result && assert_equal(expected.getX(), actual.getX());
	result = result && assert_equal(expected.getY(), actual.getY());
	result = result && assert_equal(expected.getNum(), actual.getNum());
	result = result && assert_equal(expected.getPF(), actual.getPF());
	result = result && assert_equal(expected.getSym(), actual.getSym());
	clearList();
	if(result) passCount++;
}




// INSERT TAIL
// INSERT TAIL
// INSERT TAIL

void testInsertTailIsEmptyFalse() {

	bool result = true;

	cout << "TEST: testInsertTailIsEmptyFalse" << endl;
	createNewList();
	objPos testPos{};
	ListUnderTest->insertTail(testPos);

	bool expected = false;
	bool actual = ListUnderTest->isEmpty();	

	result = result && assert_equal(expected, actual);
	clearList();
	if(result) passCount++;
}

void testInsertTailGetSize() {
	
	bool result = true;

	cout << "TEST: testInsertTailGetSize" << endl;
	createNewList();
	objPos testPos{};
	ListUnderTest->insertTail(testPos);
	ListUnderTest->insertTail(testPos);
	ListUnderTest->insertTail(testPos);
	int expected = 3;
	int actual = ListUnderTest->getSize();	

	result = result && assert_equal(expected, actual);
	clearList();
	if(result) passCount++;
}

void testInsertTailGetHead() {
	
	bool result = true;

	cout << "TEST: testInsertTailGetHead" << endl;
	createNewList();
	objPos itemArray[COUNT];
	for(int i = 0; i < COUNT; i++)	
	{
		itemArray[i] = generateRandomPos();
		ListUnderTest->insertTail(itemArray[i]);
	}
	
	objPos expected = itemArray[0];
	objPos actual = ListUnderTest->getHead();	

	result = result && assert_equal(expected.getX(), actual.getX());
	result = result && assert_equal(expected.getY(), actual.getY());
	result = result && assert_equal(expected.getNum(), actual.getNum());
	result = result && assert_equal(expected.getPF(), actual.getPF());
	result = result && assert_equal(expected.getSym(), actual.getSym());
	clearList();
	if(result) passCount++;
}

void testInsertTailGetTail() {
	
	bool result = true;

	cout << "TEST: testInsertTailGetTail" << endl;
	createNewList();
	objPos itemArray[COUNT];
	for(int i = 0; i < COUNT; i++)	
	{
		itemArray[i] = generateRandomPos();
		ListUnderTest->insertTail(itemArray[i]);
	}
	
	objPos expected = itemArray[COUNT-1];
	objPos actual = ListUnderTest->getTail();	

	result = result && assert_equal(expected.getX(), actual.getX());
	result = result && assert_equal(expected.getY(), actual.getY());
	result = result && assert_equal(expected.getNum(), actual.getNum());
	result = result && assert_equal(expected.getPF(), actual.getPF());
	result = result && assert_equal(expected.getSym(), actual.getSym());
	clearList();
	if(result) passCount++;
}

void testInsertTailGetNegTen() {
	
	bool result = true;

	cout << "TEST: testInsertTailGetNegTen" << endl;
	createNewList();
	objPos itemArray[COUNT];
	for(int i = 0; i < COUNT; i++)	
	{
		itemArray[i] = generateRandomPos();
		ListUnderTest->insertTail(itemArray[i]);
	}
	
	objPos expected = itemArray[0];
	objPos actual = ListUnderTest->get(-10);	

	result = result && assert_equal(expected.getX(), actual.getX());
	result = result && assert_equal(expected.getY(), actual.getY());
	result = result && assert_equal(expected.getNum(), actual.getNum());
	result = result && assert_equal(expected.getPF(), actual.getPF());
	result = result && assert_equal(expected.getSym(), actual.getSym());
	clearList();
	if(result) passCount++;
}

void testInsertTailGetZero() {
	
	bool result = true;

	cout << "TEST: testInsertTailGetZero" << endl;
	createNewList();
	objPos itemArray[COUNT];
	for(int i = 0; i < COUNT; i++)	
	{
		itemArray[i] = generateRandomPos();
		ListUnderTest->insertTail(itemArray[i]);
	}
	
	objPos expected = itemArray[0];
	objPos actual = ListUnderTest->get(0);	

	result = result && assert_equal(expected.getX(), actual.getX());
	result = result && assert_equal(expected.getY(), actual.getY());
	result = result && assert_equal(expected.getNum(), actual.getNum());
	result = result && assert_equal(expected.getPF(), actual.getPF());
	result = result && assert_equal(expected.getSym(), actual.getSym());
	clearList();
	if(result) passCount++;
}

void testInsertTailGetOne() {
	
	bool result = true;

	cout << "TEST: testInsertTailGetOne" << endl;
	createNewList();
	objPos itemArray[COUNT];
	for(int i = 0; i < COUNT; i++)	
	{
		itemArray[i] = generateRandomPos();
		ListUnderTest->insertTail(itemArray[i]);
	}
	
	objPos expected = itemArray[1];
	objPos actual = ListUnderTest->get(1);	

	result = result && assert_equal(expected.getX(), actual.getX());
	result = result && assert_equal(expected.getY(), actual.getY());
	result = result && assert_equal(expected.getNum(), actual.getNum());
	result = result && assert_equal(expected.getPF(), actual.getPF());
	result = result && assert_equal(expected.getSym(), actual.getSym());
	clearList();
	if(result) passCount++;
}

void testInsertTailGetCountN3() {
	
	bool result = true;

	cout << "TEST: testInsertTailGetCountN3" << endl;
	createNewList();
	objPos itemArray[COUNT];
	for(int i = 0; i < COUNT; i++)	
	{
		itemArray[i] = generateRandomPos();
		ListUnderTest->insertTail(itemArray[i]);
	}
	
	objPos expected = itemArray[COUNT-3];
	objPos actual = ListUnderTest->get(COUNT-3);	

	result = result && assert_equal(expected.getX(), actual.getX());
	result = result && assert_equal(expected.getY(), actual.getY());
	result = result && assert_equal(expected.getNum(), actual.getNum());
	result = result && assert_equal(expected.getPF(), actual.getPF());
	result = result && assert_equal(expected.getSym(), actual.getSym());
	clearList();
	if(result) passCount++;
}

void testInsertTailGetCountN1() {
	
	bool result = true;

	cout << "TEST: testInsertTailGetCountN1" << endl;
	createNewList();
	objPos itemArray[COUNT];
	for(int i = 0; i < COUNT; i++)	
	{
		itemArray[i] = generateRandomPos();
		ListUnderTest->insertTail(itemArray[i]);
	}
	
	objPos expected = itemArray[COUNT-1];
	objPos actual = ListUnderTest->get(COUNT-1);	

	result = result && assert_equal(expected.getX(), actual.getX());
	result = result && assert_equal(expected.getY(), actual.getY());
	result = result && assert_equal(expected.getNum(), actual.getNum());
	result = result && assert_equal(expected.getPF(), actual.getPF());
	result = result && assert_equal(expected.getSym(), actual.getSym());
	clearList();
	if(result) passCount++;
}

void testInsertTailGetCountP5() {
	
	bool result = true;

	cout << "TEST: testInsertTailGetCountP5" << endl;
	createNewList();
	objPos itemArray[COUNT];
	for(int i = 0; i < COUNT; i++)	
	{
		itemArray[i] = generateRandomPos();
		ListUnderTest->insertTail(itemArray[i]);
	}
	
	objPos expected = itemArray[COUNT-1];
	objPos actual = ListUnderTest->get(COUNT+5);	

	result = result && assert_equal(expected.getX(), actual.getX());
	result = result && assert_equal(expected.getY(), actual.getY());
	result = result && assert_equal(expected.getNum(), actual.getNum());
	result = result && assert_equal(expected.getPF(), actual.getPF());
	result = result && assert_equal(expected.getSym(), actual.getSym());
	clearList();
	if(result) passCount++;
}




// INSERT
// INSERT
// INSERT

void testInsertIsEmptyFalse() {

	bool result = true;

	cout << "TEST: testInsertIsEmptyFalse" << endl;
	createNewList();
	objPos testPos{};
	ListUnderTest->insert(testPos, 0);

	bool expected = false;
	bool actual = ListUnderTest->isEmpty();	

	result = result && assert_equal(expected, actual);
	clearList();
	if(result) passCount++;
}

void testInsertGetSize() {
	
	bool result = true;

	cout << "TEST: testInsertGetSize" << endl;
	createNewList();
	objPos testPos{};
	ListUnderTest->insert(testPos, 0);
	ListUnderTest->insert(testPos, -1);
	ListUnderTest->insert(testPos, 10);
	int expected = 3;
	int actual = ListUnderTest->getSize();	

	result = result && assert_equal(expected, actual);
	clearList();
	if(result) passCount++;
}

void testInsertGetHead() {
	
	bool result = true;

	cout << "TEST: testInsertGetHead" << endl;
	createNewList();
	objPos itemArray[COUNT];
	for(int i = 0; i < COUNT; i++)	
	{
		itemArray[i] = generateRandomPos();
		ListUnderTest->insert(itemArray[i], i);
	}
	
	objPos expected = itemArray[0];
	objPos actual = ListUnderTest->getHead();	

	result = result && assert_equal(expected.getX(), actual.getX());
	result = result && assert_equal(expected.getY(), actual.getY());
	result = result && assert_equal(expected.getNum(), actual.getNum());
	result = result && assert_equal(expected.getPF(), actual.getPF());
	result = result && assert_equal(expected.getSym(), actual.getSym());
	clearList();
	if(result) passCount++;
}

void testInsertGetTail() {
	
	bool result = true;

	cout << "TEST: testInsertGetTail" << endl;
	createNewList();
	objPos itemArray[COUNT];
	for(int i = 0; i < COUNT; i++)	
	{
		itemArray[i] = generateRandomPos();
		ListUnderTest->insert(itemArray[i], i);
	}
	
	objPos expected = itemArray[COUNT-1];
	objPos actual = ListUnderTest->getTail();	

	result = result && assert_equal(expected.getX(), actual.getX());
	result = result && assert_equal(expected.getY(), actual.getY());
	result = result && assert_equal(expected.getNum(), actual.getNum());
	result = result && assert_equal(expected.getPF(), actual.getPF());
	result = result && assert_equal(expected.getSym(), actual.getSym());
	clearList();
	if(result) passCount++;
}

void testInsertGetNegTen() {
	
	bool result = true;

	cout << "TEST: testInsertGetNegTen" << endl;
	createNewList();
	objPos itemArray[COUNT];
	for(int i = 0; i < COUNT; i++)	
	{
		itemArray[i] = generateRandomPos();
		ListUnderTest->insert(itemArray[i], i);
	}
	
	objPos expected = itemArray[0];
	objPos actual = ListUnderTest->get(-10);	

	result = result && assert_equal(expected.getX(), actual.getX());
	result = result && assert_equal(expected.getY(), actual.getY());
	result = result && assert_equal(expected.getNum(), actual.getNum());
	result = result && assert_equal(expected.getPF(), actual.getPF());
	result = result && assert_equal(expected.getSym(), actual.getSym());
	clearList();
	if(result) passCount++;
}

void testInsertGetZero() {
	
	bool result = true;

	cout << "TEST: testInsertGetZero" << endl;
	createNewList();
	objPos itemArray[COUNT];
	for(int i = 0; i < COUNT; i++)	
	{
		itemArray[i] = generateRandomPos();
		ListUnderTest->insert(itemArray[i], i);
	}
	
	objPos expected = itemArray[0];
	objPos actual = ListUnderTest->get(0);	

	result = result && assert_equal(expected.getX(), actual.getX());
	result = result && assert_equal(expected.getY(), actual.getY());
	result = result && assert_equal(expected.getNum(), actual.getNum());
	result = result && assert_equal(expected.getPF(), actual.getPF());
	result = result && assert_equal(expected.getSym(), actual.getSym());
	clearList();
	if(result) passCount++;
}

void testInsertGetOne() {
	
	bool result = true;

	cout << "TEST: testInsertGetOne" << endl;
	createNewList();
	objPos itemArray[COUNT];
	for(int i = 0; i < COUNT; i++)	
	{
		itemArray[i] = generateRandomPos();
		ListUnderTest->insert(itemArray[i], i);
	}
	
	objPos expected = itemArray[1];
	objPos actual = ListUnderTest->get(1);	

	result = result && assert_equal(expected.getX(), actual.getX());
	result = result && assert_equal(expected.getY(), actual.getY());
	result = result && assert_equal(expected.getNum(), actual.getNum());
	result = result && assert_equal(expected.getPF(), actual.getPF());
	result = result && assert_equal(expected.getSym(), actual.getSym());
	clearList();
	if(result) passCount++;
}

void testInsertGetCountN3() {
	
	bool result = true;

	cout << "TEST: testInsertGetCountN3" << endl;
	createNewList();
	objPos itemArray[COUNT];
	for(int i = 0; i < COUNT; i++)	
	{
		itemArray[i] = generateRandomPos();
		ListUnderTest->insert(itemArray[i], i);
	}
	
	objPos expected = itemArray[COUNT-3];
	objPos actual = ListUnderTest->get(COUNT-3);	

	result = result && assert_equal(expected.getX(), actual.getX());
	result = result && assert_equal(expected.getY(), actual.getY());
	result = result && assert_equal(expected.getNum(), actual.getNum());
	result = result && assert_equal(expected.getPF(), actual.getPF());
	result = result && assert_equal(expected.getSym(), actual.getSym());
	clearList();
	if(result) passCount++;
}

void testInsertGetCountN1() {
	
	bool result = true;

	cout << "TEST: testInsertGetCountN1" << endl;
	createNewList();
	objPos itemArray[COUNT];
	for(int i = 0; i < COUNT; i++)	
	{
		itemArray[i] = generateRandomPos();
		ListUnderTest->insert(itemArray[i], i);
	}
	
	objPos expected = itemArray[COUNT-1];
	objPos actual = ListUnderTest->get(COUNT-1);	

	result = result && assert_equal(expected.getX(), actual.getX());
	result = result && assert_equal(expected.getY(), actual.getY());
	result = result && assert_equal(expected.getNum(), actual.getNum());
	result = result && assert_equal(expected.getPF(), actual.getPF());
	result = result && assert_equal(expected.getSym(), actual.getSym());
	clearList();
	if(result) passCount++;
}

void testInsertGetCountP5() {
	
	bool result = true;

	cout << "TEST: testInsertGetCountP5" << endl;
	createNewList();
	objPos itemArray[COUNT];
	for(int i = 0; i < COUNT; i++)	
	{
		itemArray[i] = generateRandomPos();
		ListUnderTest->insert(itemArray[i], i);
	}
	
	objPos expected = itemArray[COUNT-1];
	objPos actual = ListUnderTest->get(COUNT+5);	

	result = result && assert_equal(expected.getX(), actual.getX());
	result = result && assert_equal(expected.getY(), actual.getY());
	result = result && assert_equal(expected.getNum(), actual.getNum());
	result = result && assert_equal(expected.getPF(), actual.getPF());
	result = result && assert_equal(expected.getSym(), actual.getSym());
	clearList();
	if(result) passCount++;
}



// REMOVE HEAD
// REMOVE TAIL
// REMOVE 

void testRemoveHead() {
	
	bool result = true;

	cout << "TEST: testRemoveHead" << endl;
	createNewList();
	objPos itemArray[COUNT];
	for(int i = 0; i < COUNT; i++)	
	{
		itemArray[i] = generateRandomPos();
		ListUnderTest->insert(itemArray[i], i);
	}	
	
	objPos expected = itemArray[0];
	objPos actual = ListUnderTest->removeHead();	

	result = result && assert_equal(expected.getX(), actual.getX());
	result = result && assert_equal(expected.getY(), actual.getY());
	result = result && assert_equal(expected.getNum(), actual.getNum());
	result = result && assert_equal(expected.getPF(), actual.getPF());
	result = result && assert_equal(expected.getSym(), actual.getSym());

	int actualSize = ListUnderTest->getSize();
	int expectedSize = COUNT - 1;

	result = result && assert_equal(expectedSize, actualSize);

	clearList();
	if(result) passCount++;
}

void testRemoveTail() {
	
	bool result = true;

	cout << "TEST: testRemoveTail" << endl;
	createNewList();
	objPos itemArray[COUNT];
	for(int i = 0; i < COUNT; i++)	
	{
		itemArray[i] = generateRandomPos();
		ListUnderTest->insert(itemArray[i], i);
	}
	
	objPos expected = itemArray[COUNT-1];
	objPos actual = ListUnderTest->removeTail();	

	result = result && assert_equal(expected.getX(), actual.getX());
	result = result && assert_equal(expected.getY(), actual.getY());
	result = result && assert_equal(expected.getNum(), actual.getNum());
	result = result && assert_equal(expected.getPF(), actual.getPF());
	result = result && assert_equal(expected.getSym(), actual.getSym());

	int actualSize = ListUnderTest->getSize();
	int expectedSize = COUNT - 1;

	result = result && assert_equal(expectedSize, actualSize);

	clearList();
	if(result) passCount++;
}

void testRemoveNegTen() {
	
	bool result = true;

	cout << "TEST: testRemoveNegTen" << endl;
	createNewList();
	objPos itemArray[COUNT];
	for(int i = 0; i < COUNT; i++)	
	{
		itemArray[i] = generateRandomPos();
		ListUnderTest->insert(itemArray[i], i);
	}
	
	objPos expected = itemArray[0];
	objPos actual = ListUnderTest->remove(-10);	

	result = result && assert_equal(expected.getX(), actual.getX());
	result = result && assert_equal(expected.getY(), actual.getY());
	result = result && assert_equal(expected.getNum(), actual.getNum());
	result = result && assert_equal(expected.getPF(), actual.getPF());
	result = result && assert_equal(expected.getSym(), actual.getSym());

	int actualSize = ListUnderTest->getSize();
	int expectedSize = COUNT - 1;

	result = result && assert_equal(expectedSize, actualSize);

	clearList();
	if(result) passCount++;
}

void testRemoveZero() {
	
	bool result = true;

	cout << "TEST: testRemoveZero" << endl;
	createNewList();
	objPos itemArray[COUNT];
	for(int i = 0; i < COUNT; i++)	
	{
		itemArray[i] = generateRandomPos();
		ListUnderTest->insert(itemArray[i], i);
	}
	
	objPos expected = itemArray[0];
	objPos actual = ListUnderTest->remove(0);	

	result = result && assert_equal(expected.getX(), actual.getX());
	result = result && assert_equal(expected.getY(), actual.getY());
	result = result && assert_equal(expected.getNum(), actual.getNum());
	result = result && assert_equal(expected.getPF(), actual.getPF());
	result = result && assert_equal(expected.getSym(), actual.getSym());

	int actualSize = ListUnderTest->getSize();
	int expectedSize = COUNT - 1;

	result = result && assert_equal(expectedSize, actualSize);

	clearList();
	if(result) passCount++;
}

void testRemoveOne() {
	
	bool result = true;

	cout << "TEST: testRemoveOne" << endl;
	createNewList();
	objPos itemArray[COUNT];
	for(int i = 0; i < COUNT; i++)	
	{
		itemArray[i] = generateRandomPos();
		ListUnderTest->insert(itemArray[i], i);
	}	
	
	objPos expected = itemArray[1];
	objPos actual = ListUnderTest->remove(1);	

	result = result && assert_equal(expected.getX(), actual.getX());
	result = result && assert_equal(expected.getY(), actual.getY());
	result = result && assert_equal(expected.getNum(), actual.getNum());
	result = result && assert_equal(expected.getPF(), actual.getPF());
	result = result && assert_equal(expected.getSym(), actual.getSym());

	int actualSize = ListUnderTest->getSize();
	int expectedSize = COUNT - 1;

	result = result && assert_equal(expectedSize, actualSize);

	clearList();
	if(result) passCount++;
}

void testRemoveCountN3() {
	
	bool result = true;

	cout << "TEST: testRemoveCountN3" << endl;
	createNewList();
	objPos itemArray[COUNT];
	for(int i = 0; i < COUNT; i++)	
	{
		itemArray[i] = generateRandomPos();
		ListUnderTest->insert(itemArray[i], i);
	}
	
	objPos expected = itemArray[COUNT-3];
	objPos actual = ListUnderTest->remove(COUNT-3);	

	result = result && assert_equal(expected.getX(), actual.getX());
	result = result && assert_equal(expected.getY(), actual.getY());
	result = result && assert_equal(expected.getNum(), actual.getNum());
	result = result && assert_equal(expected.getPF(), actual.getPF());
	result = result && assert_equal(expected.getSym(), actual.getSym());

	int actualSize = ListUnderTest->getSize();
	int expectedSize = COUNT - 1;

	result = result && assert_equal(expectedSize, actualSize);

	clearList();
	if(result) passCount++;
}

void testRemoveCountN1() {
	
	bool result = true;

	cout << "TEST: testRemoveCountN1" << endl;
	createNewList();
	objPos itemArray[COUNT];
	for(int i = 0; i < COUNT; i++)	
	{
		itemArray[i] = generateRandomPos();
		ListUnderTest->insert(itemArray[i], i);
	}
	
	objPos expected = itemArray[COUNT-1];
	objPos actual = ListUnderTest->remove(COUNT-1);	

	result = result && assert_equal(expected.getX(), actual.getX());
	result = result && assert_equal(expected.getY(), actual.getY());
	result = result && assert_equal(expected.getNum(), actual.getNum());
	result = result && assert_equal(expected.getPF(), actual.getPF());
	result = result && assert_equal(expected.getSym(), actual.getSym());

	int actualSize = ListUnderTest->getSize();
	int expectedSize = COUNT - 1;

	result = result && assert_equal(expectedSize, actualSize);

	clearList();
	if(result) passCount++;
}

void testRemoveCountP5() {
	
	bool result = true;

	cout << "TEST: testRemoveCountP5" << endl;
	createNewList();
	objPos itemArray[COUNT];
	for(int i = 0; i < COUNT; i++)	
	{
		itemArray[i] = generateRandomPos();
		ListUnderTest->insert(itemArray[i], i);
	}
	
	objPos expected = itemArray[COUNT-1];
	objPos actual = ListUnderTest->remove(COUNT+5);	

	result = result && assert_equal(expected.getX(), actual.getX());
	result = result && assert_equal(expected.getY(), actual.getY());
	result = result && assert_equal(expected.getNum(), actual.getNum());
	result = result && assert_equal(expected.getPF(), actual.getPF());
	result = result && assert_equal(expected.getSym(), actual.getSym());

	int actualSize = ListUnderTest->getSize();
	int expectedSize = COUNT - 1;

	result = result && assert_equal(expectedSize, actualSize);

	clearList();
	if(result) passCount++;
}



// SET
// SET
// SET

void testSetNegTen() {
	
	bool result = true;

	cout << "TEST: testSetNegTen" << endl;
	createNewList();
	objPos itemArray[COUNT];
	for(int i = 0; i < COUNT; i++)	
	{
		itemArray[i] = generateRandomPos();
		ListUnderTest->insert(itemArray[i], i);
	}

	objPos expected = generateRandomPos();	
	ListUnderTest->set(expected, -10);
	objPos actual = ListUnderTest->get(-10);	
	
	result = result && assert_equal(expected.getX(), actual.getX());
	result = result && assert_equal(expected.getY(), actual.getY());
	result = result && assert_equal(expected.getNum(), actual.getNum());
	result = result && assert_equal(expected.getPF(), actual.getPF());
	result = result && assert_equal(expected.getSym(), actual.getSym());
	clearList();
	if(result) passCount++;
}

void testSetZero() {
	
	bool result = true;

	cout << "TEST: testSetZero" << endl;
	createNewList();
	objPos itemArray[COUNT];
	for(int i = 0; i < COUNT; i++)	
	{
		itemArray[i] = generateRandomPos();
		ListUnderTest->insert(itemArray[i], i);
	}
	
	objPos expected = generateRandomPos();
	ListUnderTest->set(expected, 0);
	objPos actual = ListUnderTest->get(0);	

	result = result && assert_equal(expected.getX(), actual.getX());
	result = result && assert_equal(expected.getY(), actual.getY());
	result = result && assert_equal(expected.getNum(), actual.getNum());
	result = result && assert_equal(expected.getPF(), actual.getPF());
	result = result && assert_equal(expected.getSym(), actual.getSym());
	clearList();
	if(result) passCount++;
}

void testSetOne() {
	
	bool result = true;

	cout << "TEST: testSetOne" << endl;
	createNewList();
	objPos itemArray[COUNT];
	for(int i = 0; i < COUNT; i++)	
	{
		itemArray[i] = generateRandomPos();
		ListUnderTest->insert(itemArray[i], i);
	}
	
	objPos expected = generateRandomPos();
	ListUnderTest->set(expected, 1);
	objPos actual = ListUnderTest->get(1);	

	result = result && assert_equal(expected.getX(), actual.getX());
	result = result && assert_equal(expected.getY(), actual.getY());
	result = result && assert_equal(expected.getNum(), actual.getNum());
	result = result && assert_equal(expected.getPF(), actual.getPF());
	result = result && assert_equal(expected.getSym(), actual.getSym());
	clearList();
	if(result) passCount++;
}

void testSetCountN3() {
	
	bool result = true;

	cout << "TEST: testSetCountN3" << endl;
	createNewList();
	objPos itemArray[COUNT];
	for(int i = 0; i < COUNT; i++)	
	{
		itemArray[i] = generateRandomPos();
		ListUnderTest->insert(itemArray[i], i);
	}
	
	objPos expected = generateRandomPos();
	ListUnderTest->set(expected, COUNT-3);
	objPos actual = ListUnderTest->get(COUNT-3);	

	result = result && assert_equal(expected.getX(), actual.getX());
	result = result && assert_equal(expected.getY(), actual.getY());
	result = result && assert_equal(expected.getNum(), actual.getNum());
	result = result && assert_equal(expected.getPF(), actual.getPF());
	result = result && assert_equal(expected.getSym(), actual.getSym());
	clearList();
	if(result) passCount++;
}

void testSetCountN1() {
	
	bool result = true;

	cout << "TEST: testSetCountN1" << endl;
	createNewList();
	objPos itemArray[COUNT];
	for(int i = 0; i < COUNT; i++)	
	{
		itemArray[i] = generateRandomPos();
		ListUnderTest->insert(itemArray[i], i);
	}
	
	objPos expected = generateRandomPos();
	ListUnderTest->set(expected, COUNT-1);
	objPos actual = ListUnderTest->get(COUNT-1);

	result = result && assert_equal(expected.getX(), actual.getX());
	result = result && assert_equal(expected.getY(), actual.getY());
	result = result && assert_equal(expected.getNum(), actual.getNum());
	result = result && assert_equal(expected.getPF(), actual.getPF());
	result = result && assert_equal(expected.getSym(), actual.getSym());
	clearList();
	if(result) passCount++;
}

void testSetCountP5() {
	
	bool result = true;

	cout << "TEST: testSetCountP5" << endl;
	createNewList();
	objPos itemArray[COUNT];
	for(int i = 0; i < COUNT; i++)	
	{
		itemArray[i] = generateRandomPos();
		ListUnderTest->insert(itemArray[i], i);
	}
	
	objPos expected = generateRandomPos();
	ListUnderTest->set(expected, COUNT+5);
	objPos actual = ListUnderTest->get(COUNT+5);

	result = result && assert_equal(expected.getX(), actual.getX());
	result = result && assert_equal(expected.getY(), actual.getY());
	result = result && assert_equal(expected.getNum(), actual.getNum());
	result = result && assert_equal(expected.getPF(), actual.getPF());
	result = result && assert_equal(expected.getSym(), actual.getSym());
	clearList();
	if(result) passCount++;
}


// GET NEXT and RESET
// GET NEXT and RESET
// GET NEXT and RESET

void testGetNextResetWholeList() {
	
	bool result = true;

	cout << "TEST: testGetNextResetWholeList" << endl;
	createNewList();
	objPos itemArray[COUNT];
	for(int i = 0; i < COUNT; i++)	
	{
		itemArray[i] = generateRandomPos();
		ListUnderTest->insert(itemArray[i], i);
	}
	
	objPos expected, actual;
	ListUnderTest->resetReadPos();
	for(int i = 0; i < ListUnderTest->getSize(); i++)
	{
		expected = itemArray[i];
		actual = ListUnderTest->getNext();

		result = result && assert_equal(expected.getX(), actual.getX());
		result = result && assert_equal(expected.getY(), actual.getY());
		result = result && assert_equal(expected.getNum(), actual.getNum());
		result = result && assert_equal(expected.getPF(), actual.getPF());
		result = result && assert_equal(expected.getSym(), actual.getSym());
	}
	
	clearList();
	if(result) passCount++;
}

void testGetNextResetPos2() {
	
	bool result = true;

	cout << "TEST: testGetNextResetPos2" << endl;
	createNewList();
	objPos itemArray[COUNT];
	for(int i = 0; i < COUNT; i++)	
	{
		itemArray[i] = generateRandomPos();
		ListUnderTest->insert(itemArray[i], i);
	}
	
	objPos expected, actual;
	ListUnderTest->resetReadPos();
	for(int i = 0; i < 2; i++)
	{
		expected = itemArray[i];
		actual = ListUnderTest->getNext();

		result = result && assert_equal(expected.getX(), actual.getX());
		result = result && assert_equal(expected.getY(), actual.getY());
		result = result && assert_equal(expected.getNum(), actual.getNum());
		result = result && assert_equal(expected.getPF(), actual.getPF());
		result = result && assert_equal(expected.getSym(), actual.getSym());
	}

	ListUnderTest->resetReadPos();
	for(int i = 0; i < ListUnderTest->getSize(); i++)
	{
		expected = itemArray[i];
		actual = ListUnderTest->getNext();

		result = result && assert_equal(expected.getX(), actual.getX());
		result = result && assert_equal(expected.getY(), actual.getY());
		result = result && assert_equal(expected.getNum(), actual.getNum());
		result = result && assert_equal(expected.getPF(), actual.getPF());
		result = result && assert_equal(expected.getSym(), actual.getSym());
	}
	
	clearList();
	if(result) passCount++;
}

void testGetNextResetPos5() {
	
	bool result = true;

	cout << "TEST: testGetNextResetPos5" << endl;
	createNewList();
	objPos itemArray[COUNT];
	for(int i = 0; i < COUNT; i++)	
	{
		itemArray[i] = generateRandomPos();
		ListUnderTest->insert(itemArray[i], i);
	}
	
	objPos expected, actual;
	ListUnderTest->resetReadPos();
	for(int i = 0; i < 5; i++)
	{
		expected = itemArray[i];
		actual = ListUnderTest->getNext();

		result = result && assert_equal(expected.getX(), actual.getX());
		result = result && assert_equal(expected.getY(), actual.getY());
		result = result && assert_equal(expected.getNum(), actual.getNum());
		result = result && assert_equal(expected.getPF(), actual.getPF());
		result = result && assert_equal(expected.getSym(), actual.getSym());
	}

	ListUnderTest->resetReadPos();
	for(int i = 0; i < ListUnderTest->getSize(); i++)
	{
		expected = itemArray[i];
		actual = ListUnderTest->getNext();

		result = result && assert_equal(expected.getX(), actual.getX());
		result = result && assert_equal(expected.getY(), actual.getY());
		result = result && assert_equal(expected.getNum(), actual.getNum());
		result = result && assert_equal(expected.getPF(), actual.getPF());
		result = result && assert_equal(expected.getSym(), actual.getSym());
	}
	
	clearList();
	if(result) passCount++;
}

void testGetNextResetPos8() {
	
	bool result = true;

	cout << "TEST: testGetNextResetPos8" << endl;
	createNewList();
	objPos itemArray[COUNT];
	for(int i = 0; i < COUNT; i++)	
	{
		itemArray[i] = generateRandomPos();
		ListUnderTest->insert(itemArray[i], i);
	}
	
	objPos expected, actual;
	ListUnderTest->resetReadPos();
	for(int i = 0; i < 8; i++)
	{
		expected = itemArray[i];
		actual = ListUnderTest->getNext();

		result = result && assert_equal(expected.getX(), actual.getX());
		result = result && assert_equal(expected.getY(), actual.getY());
		result = result && assert_equal(expected.getNum(), actual.getNum());
		result = result && assert_equal(expected.getPF(), actual.getPF());
		result = result && assert_equal(expected.getSym(), actual.getSym());
	}

	ListUnderTest->resetReadPos();
	for(int i = 0; i < ListUnderTest->getSize(); i++)
	{
		expected = itemArray[i];
		actual = ListUnderTest->getNext();

		result = result && assert_equal(expected.getX(), actual.getX());
		result = result && assert_equal(expected.getY(), actual.getY());
		result = result && assert_equal(expected.getNum(), actual.getNum());
		result = result && assert_equal(expected.getPF(), actual.getPF());
		result = result && assert_equal(expected.getSym(), actual.getSym());
	}
	
	clearList();
	if(result) passCount++;
}


// add two more test cases for your unit test learning purpose


bool runAllTests(int argc, char const *argv[]) {
	
	
    testConstructorGetSize();
	testConstructorIsEmptyTrue();

	testInsertHeadIsEmptyFalse();
	testInsertHeadGetSize();
	testInsertHeadGetHead();
	testInsertHeadGetTail();
	testInsertHeadGetNegTen();
	testInsertHeadGetZero();
	testInsertHeadGetOne();
	testInsertHeadGetCountN3();
	testInsertHeadGetCountN1();
	testInsertHeadGetCountP5();

	testInsertTailIsEmptyFalse();
	testInsertTailGetSize();
	testInsertTailGetHead();
	testInsertTailGetTail();
	testInsertTailGetNegTen();
	testInsertTailGetZero();
	testInsertTailGetOne();
	testInsertTailGetCountN3();
	testInsertTailGetCountN1();
	testInsertTailGetCountP5();

	testRemoveHead();
	testRemoveTail();
	testRemoveNegTen();
	testRemoveZero();
	testRemoveOne();
	testRemoveCountN3();
	testRemoveCountN1();
	testRemoveCountP5();

	testSetNegTen();
	testSetZero();
	testSetOne();
	testSetCountN3();
	testSetCountN1();
	testSetCountP5();

	if(testGetNextReady)
	{
		testGetNextResetWholeList();
		testGetNextResetPos2();
		testGetNextResetPos5();
		testGetNextResetPos8();
	}
	
	if(successCount != TOTAL_ASSERT_COUNT) 
		return false;
	else 
		return true;
}

int main(int argc, char const *argv[]) {
  	
	srand(time(NULL));
	successCount = 0;
	passCount = 0;
	bool successCode = runAllTests(argc, argv);
	if(successCode)	cout << endl << "Passed All Tests" << endl;
	else			cout << "Failed Tests, Check Failure" << endl;	
	cout << "Assertion Score: " << successCount << " / " << TOTAL_ASSERT_COUNT << endl;	
	cout << "Test Case Score: " << passCount << " / " << TOTAL_TEST_CASES << endl;

	return successCode? EXIT_SUCCESS : EXIT_FAILURE;
}

void clearList()
{
	delete ListUnderTest;
	ListUnderTest = NULL;	
}

objPos generateRandomPos()
{
	objPos temp;

	temp.setX(rand() % 100);
	temp.setY(rand() % 100);
	temp.setNum(rand() % 500);
	temp.setPF(rand() % 26 + 'a');
	temp.setSym(rand() % 26 + 'A');

	return temp;
}


bool assert_equal(int a, int b)
{
	bool result = (a == b);
	if(result)	
		successCount++;
	else
	{
		cout << "\t\t[ASSERTION] Expected: " << a << ", but Actual: " << b << endl;		
	}
	return result;
}

bool assert_equal(char a, char b)
{
	bool result = (a == b);
	if(result)	
		successCount++;
	else
	{
		cout << "\t\tExpected: " << a << ", but Actual: " << b << endl;		
	}
	return result;
}