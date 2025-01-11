#include "objPos.h"
#include "objPosQuadHashing.h"
#include "objPosDoubleHashing.h"

#include <cstdlib>
#include <ctime>

#define COUNT 37				// 36 is a better number, but not prime
#define LARGE_COUNT 111			// 
#define TOTAL_ASSERT_COUNT 604
#define TOTAL_TEST_CASES 12
#define TOLERANCE_RANGE 0.005   // +/- 0.5%

#include <iostream>
using namespace std;

objPosHashTable *HTableUnderTest;
int successCount;
int passCount;

void createQuadHashingTable(int);
void createDoubleHashingTable(int);
void deleteHashingTable();
objPos generateRandomPos();
char generateRandomChar();

bool assert_equal(int, int);
bool assert_equal(char, char);
bool assert_equal(bool, bool);
bool assert_equal(double, double);

// **** Enable This Flag for Verbose Hash Table Printout for Debugging **** //
// **** Enable This Flag for Verbose Hash Table Printout for Debugging **** //
bool verboseMode = true;
// **** Enable This Flag for Verbose Hash Table Printout for Debugging **** //
// **** Enable This Flag for Verbose Hash Table Printout for Debugging **** //





////////////////////////////////////////////////
////////////////////////////////////////////////
////////   QUADRATIC HASHING TESTERS   /////////
////////////////////////////////////////////////
////////////////////////////////////////////////

// Part I - Constructor
// Required Method - Constructor (both), Destructor, getLambda

void testQHConstructorGetLambdaSmall() {
	
	bool result = true;

	cout << "TEST: testQHConstructorGetLambdaSmall" << endl;
	createQuadHashingTable(COUNT);
	double expected = 0.0;
	double actual = HTableUnderTest->getLambda();	

	result = result & assert_equal(expected, actual);
	deleteHashingTable();
	if(result) passCount++;
}

void testQHConstructorGetLambdaLarge() {
	
	bool result = true;

	cout << "TEST: testQHConstructorGetLambdaLarge" << endl;
	createQuadHashingTable(LARGE_COUNT);
	double expected = 0.0;
	double actual = HTableUnderTest->getLambda();	

	result = result & assert_equal(expected, actual);
	deleteHashingTable();
	if(result) passCount++;
}

// Part II - Insertion
// Required Method - insert, isInTable, printMe

void testQHInsertPrintSmall() {
	
	bool result = true;

	cout << "TEST: testQHInsertPrintSmall" << endl;
	objPos itemArray[COUNT];
	bool itemInserted[COUNT];
	bool expected, actual;	

	createQuadHashingTable(COUNT);

	for(int i = 0; i < COUNT; i++)
	{
		itemArray[i] = generateRandomPos();
		if(HTableUnderTest->isInTable(itemArray[i]))
			itemInserted[i] = true;
		else
			itemInserted[i] = HTableUnderTest->insert(itemArray[i]);
	}
	
	if(verboseMode) HTableUnderTest->printMe();
	
	for(int i = 0; i < COUNT; i++)
	{
		expected = itemInserted[i];
		actual = HTableUnderTest->isInTable(itemArray[i]);
		result = result & assert_equal(expected, actual);
	}
	
	deleteHashingTable();
	if(result) passCount++;
}

void testQHInsertPrintLarge() {
	
	bool result = true;

	cout << "TEST: testQHInsertPrintLarge" << endl;
	objPos itemArray[LARGE_COUNT];
	bool itemInserted[LARGE_COUNT];
	bool expected, actual;	

	createQuadHashingTable(LARGE_COUNT);

	for(int i = 0; i < LARGE_COUNT; i++)
	{
		itemArray[i] = generateRandomPos();
		if(HTableUnderTest->isInTable(itemArray[i]))
			itemInserted[i] = true;
		else
			itemInserted[i] = HTableUnderTest->insert(itemArray[i]);
	}
	
	if(verboseMode) HTableUnderTest->printMe();
	
	for(int i = 0; i < LARGE_COUNT; i++)
	{
		expected = itemInserted[i];
		actual = HTableUnderTest->isInTable(itemArray[i]);
		result = result & assert_equal(expected, actual);
	}
	
	deleteHashingTable();
	if(result) passCount++;
}


// Part II - Removal
// Required Method - remove, getLambda, isInTable, printMe

#define REMOVAL_COUNT1 10
void testQH10RemoveGetLambdaSmall() {
	
	bool result = true;

	cout << "TEST: testQH10RemoveGetLambdaSmall" << endl;
	objPos itemArray[COUNT];
	bool itemInserted[COUNT];
	int insertedCount = 0;
	double expectedLambda, actualLambda;
	bool expected, actual;	

	createQuadHashingTable(COUNT);

	for(int i = 0; i < COUNT; i++)
	{
		itemArray[i] = generateRandomPos();
		if(HTableUnderTest->isInTable(itemArray[i]))
		{
			itemInserted[i] = true;
		}
		else
		{
			itemInserted[i] = HTableUnderTest->insert(itemArray[i]);
			if(itemInserted[i])	insertedCount++;
		}
	}

	if(verboseMode) 
	{
		cout << endl << endl << "[Before Removal]" << endl;
		HTableUnderTest->printMe();
	}
	
	expectedLambda = (double)insertedCount / COUNT;
	actualLambda = HTableUnderTest->getLambda();	
	bool temp = assert_equal(expectedLambda, actualLambda);
	result = result & temp;
	if(!temp) 
	{
		HTableUnderTest->printMe();
		cout << "Lambda: " << HTableUnderTest -> getLambda();
	}
	

	for(int i = 0, count = REMOVAL_COUNT1; count > 0; i = (i + rand() % 10) % COUNT)
	{
		if(itemInserted[i])
		{
			itemInserted[i] = false;
			if(HTableUnderTest->remove(itemArray[i]))
				insertedCount--;
			count--;			
		}
	}

	for(int i = 0; i < COUNT; i++)
	{
		if(!HTableUnderTest->isInTable(itemArray[i]))
			itemInserted[i] = false;
	}

	if(verboseMode) 
	{
		cout << endl << endl << "[After Removal]" << endl;
		HTableUnderTest->printMe();
	}
	
	for(int i = 0; i < COUNT; i++)
	{
		expected = itemInserted[i];
		actual = HTableUnderTest->isInTable(itemArray[i]);
		result = result & assert_equal(expected, actual);
	}

	expectedLambda = (double)insertedCount / COUNT;
	actualLambda = HTableUnderTest->getLambda();	
	result = result & assert_equal(expectedLambda, actualLambda);
		
	deleteHashingTable();
	if(result) passCount++;
}

#define REMOVAL_COUNT2 20
void testQH20RemoveGetLambdaLarge() {
	
	bool result = true;

	cout << "TEST: testQH20RemoveGetLambdaLarge" << endl;
	objPos itemArray[LARGE_COUNT];
	bool itemInserted[LARGE_COUNT];
	int insertedCount = 0;
	double expectedLambda, actualLambda;
	bool expected, actual;	

	createQuadHashingTable(LARGE_COUNT);

	for(int i = 0; i < LARGE_COUNT; i++)
	{
		itemArray[i] = generateRandomPos();
		if(HTableUnderTest->isInTable(itemArray[i]))
		{
			itemInserted[i] = true;
		}
		else
		{
			itemInserted[i] = HTableUnderTest->insert(itemArray[i]);
			if(itemInserted[i])	insertedCount++;
		}
	}

	if(verboseMode) 
	{
		cout << endl << endl << "[Before Removal]" << endl;
		HTableUnderTest->printMe();
	}
	
	expectedLambda = (double)insertedCount / LARGE_COUNT;
	actualLambda = HTableUnderTest->getLambda();	
	result = result & assert_equal(expectedLambda, actualLambda);
	

	for(int i = 0, count = REMOVAL_COUNT2; count > 0; i = (i + rand() % 10) % LARGE_COUNT)
	{
		if(itemInserted[i])
		{
			itemInserted[i] = false;
			if(HTableUnderTest->remove(itemArray[i]))
				insertedCount--;
			count--;			
		}
	}

	for(int i = 0; i < LARGE_COUNT; i++)
	{
		if(!HTableUnderTest->isInTable(itemArray[i]))
			itemInserted[i] = false;
	}

	if(verboseMode) 
	{
		cout << endl << endl << "[After Removal]" << endl;
		HTableUnderTest->printMe();
	}
	
	for(int i = 0; i < LARGE_COUNT; i++)
	{
		expected = itemInserted[i];
		actual = HTableUnderTest->isInTable(itemArray[i]);
		result = result & assert_equal(expected, actual);
	}

	expectedLambda = (double)insertedCount / LARGE_COUNT;
	actualLambda = HTableUnderTest->getLambda();	
	result = result & assert_equal(expectedLambda, actualLambda);
		
	deleteHashingTable();
	if(result) passCount++;
}



/////////////////////////////////////////////
/////////////////////////////////////////////
////////   DOUBLE PROBING TESTERS   /////////
/////////////////////////////////////////////
/////////////////////////////////////////////

// Part I - Constructor
// Required Method - Constructor (both), Destructor, getLambda

void testDHConstructorGetLambdaSmall() {
	
	bool result = true;

	cout << "TEST: testDHConstructorGetLambdaSmall" << endl;
	createDoubleHashingTable(COUNT);
	double expected = 0.0;
	double actual = HTableUnderTest->getLambda();	

	result = result & assert_equal(expected, actual);
	deleteHashingTable();
	if(result) passCount++;
}

void testDHConstructorGetLambdaLarge() {
	
	bool result = true;

	cout << "TEST: testDHConstructorGetLambdaLarge" << endl;
	createDoubleHashingTable(LARGE_COUNT);
	double expected = 0.0;
	double actual = HTableUnderTest->getLambda();	

	result = result & assert_equal(expected, actual);
	deleteHashingTable();
	if(result) passCount++;
}


// Part II - Insertion
// Required Method - insert, isInTable, printMe

void testDHInsertPrintSmall() {
	
	bool result = true;

	cout << "TEST: testDHInsertPrintSmall" << endl;
	objPos itemArray[COUNT];
	bool itemInserted[COUNT];
	bool expected, actual;	

	createDoubleHashingTable(COUNT);

	for(int i = 0; i < COUNT; i++)
	{
		itemArray[i] = generateRandomPos();
		if(HTableUnderTest->isInTable(itemArray[i]))
			itemInserted[i] = true;
		else
			itemInserted[i] = HTableUnderTest->insert(itemArray[i]);
	}
	
	if(verboseMode) HTableUnderTest->printMe();
	
	for(int i = 0; i < COUNT; i++)
	{
		expected = itemInserted[i];
		actual = HTableUnderTest->isInTable(itemArray[i]);
		result = result & assert_equal(expected, actual);
	}
	
	deleteHashingTable();
	if(result) passCount++;
}

void testDHInsertPrintLarge() {
	
	bool result = true;

	cout << "TEST: testDHInsertPrintLarge" << endl;
	objPos itemArray[LARGE_COUNT];
	bool itemInserted[LARGE_COUNT];
	bool expected, actual;	

	createDoubleHashingTable(LARGE_COUNT);

	for(int i = 0; i < LARGE_COUNT; i++)
	{
		itemArray[i] = generateRandomPos();
		if(HTableUnderTest->isInTable(itemArray[i]))
			itemInserted[i] = true;
		else
			itemInserted[i] = HTableUnderTest->insert(itemArray[i]);
	}
	
	if(verboseMode) HTableUnderTest->printMe();
	
	for(int i = 0; i < LARGE_COUNT; i++)
	{
		expected = itemInserted[i];
		actual = HTableUnderTest->isInTable(itemArray[i]);
		result = result & assert_equal(expected, actual);
	}
	
	deleteHashingTable();
	if(result) passCount++;
}


// Part II - Removal
// Required Method - remove, getLambda, isInTable, printMe

#define REMOVAL_COUNT1 10
void testDH10RemoveGetLambdaSmall() {
	
	bool result = true;

	cout << "TEST: testDH10RemoveGetLambdaSmall" << endl;
	objPos itemArray[COUNT];
	bool itemInserted[COUNT];
	int insertedCount = 0;
	double expectedLambda, actualLambda;
	bool expected, actual;	

	createDoubleHashingTable(COUNT);

	for(int i = 0; i < COUNT; i++)
	{
		itemArray[i] = generateRandomPos();
		if(HTableUnderTest->isInTable(itemArray[i]))
		{
			itemInserted[i] = true;
		}
		else
		{
			itemInserted[i] = HTableUnderTest->insert(itemArray[i]);
			if(itemInserted[i])	insertedCount++;
		}
	}

	if(verboseMode) 
	{
		cout << endl << endl << "[Before Removal]" << endl;
		HTableUnderTest->printMe();
	}
	
	expectedLambda = (double)insertedCount / COUNT;
	actualLambda = HTableUnderTest->getLambda();	
	result = result & assert_equal(expectedLambda, actualLambda);
	

	for(int i = 0, count = REMOVAL_COUNT1; count > 0; i = (i + rand() % 10) % COUNT)
	{
		if(itemInserted[i])
		{
			itemInserted[i] = false;
			if(HTableUnderTest->remove(itemArray[i]))
				insertedCount--;
			count--;			
		}
	}

	for(int i = 0; i < COUNT; i++)
	{
		if(!HTableUnderTest->isInTable(itemArray[i]))
			itemInserted[i] = false;
	}

	if(verboseMode) 
	{
		cout << endl << endl << "[After Removal]" << endl;
		HTableUnderTest->printMe();
	}
	
	for(int i = 0; i < COUNT; i++)
	{
		expected = itemInserted[i];
		actual = HTableUnderTest->isInTable(itemArray[i]);
		result = result & assert_equal(expected, actual);
	}

	expectedLambda = (double)insertedCount / COUNT;
	actualLambda = HTableUnderTest->getLambda();	
	result = result & assert_equal(expectedLambda, actualLambda);
		
	deleteHashingTable();
	if(result) passCount++;
}

#define REMOVAL_COUNT2 20
void testDH20RemoveGetLambdaLarge() {
	
	bool result = true;

	cout << "TEST: testDH20RemoveGetLambdaLarge" << endl;
	objPos itemArray[LARGE_COUNT];
	bool itemInserted[LARGE_COUNT];
	int insertedCount = 0;
	double expectedLambda, actualLambda;
	bool expected, actual;	

	createDoubleHashingTable(LARGE_COUNT);

	for(int i = 0; i < LARGE_COUNT; i++)
	{
		itemArray[i] = generateRandomPos();
		if(HTableUnderTest->isInTable(itemArray[i]))
		{
			itemInserted[i] = true;
		}
		else
		{
			itemInserted[i] = HTableUnderTest->insert(itemArray[i]);
			if(itemInserted[i])	insertedCount++;
		}
	}

	if(verboseMode) 
	{
		cout << endl << endl << "[Before Removal]" << endl;
		HTableUnderTest->printMe();
	}
	
	expectedLambda = (double)insertedCount / LARGE_COUNT;
	actualLambda = HTableUnderTest->getLambda();	
	result = result & assert_equal(expectedLambda, actualLambda);
	

	for(int i = 0, count = REMOVAL_COUNT2; count > 0; i = (i + rand() % 10) % LARGE_COUNT)
	{
		if(itemInserted[i])
		{
			itemInserted[i] = false;
			if(HTableUnderTest->remove(itemArray[i]))
				insertedCount--;
			count--;			
		}
	}

	for(int i = 0; i < LARGE_COUNT; i++)
	{
		if(!HTableUnderTest->isInTable(itemArray[i]))
			itemInserted[i] = false;
	}

	if(verboseMode) 
	{
		cout << endl << endl << "[After Removal]" << endl;
		HTableUnderTest->printMe();
	}
	
	for(int i = 0; i < LARGE_COUNT; i++)
	{
		expected = itemInserted[i];
		actual = HTableUnderTest->isInTable(itemArray[i]);
		result = result & assert_equal(expected, actual);
	}

	expectedLambda = (double)insertedCount / LARGE_COUNT;
	actualLambda = HTableUnderTest->getLambda();	
	result = result & assert_equal(expectedLambda, actualLambda);
		
	deleteHashingTable();
	if(result) passCount++;
}



bool runAllTests(int argc, char const *argv[]) {
	
	// objPosStack Testers
	cout << "[QUADRATIC PROBING HASH TABLE TESTER STARTED]" << endl;
    testQHConstructorGetLambdaSmall();
	testQHConstructorGetLambdaLarge();
	testQHInsertPrintSmall();
	testQHInsertPrintLarge();
	testQH10RemoveGetLambdaSmall();
	testQH20RemoveGetLambdaLarge();
	cout << "[QUADRATIC PROBING HASH TABLE TESTER ENDED]" << endl << endl;
	
	cout << "[DOUBLE HASHING HASH TABLE TESTER STARTED]" << endl;
	testDHConstructorGetLambdaSmall();
	testDHConstructorGetLambdaLarge();
	testDHInsertPrintSmall();
	testDHInsertPrintLarge();
	testDH10RemoveGetLambdaSmall();
	testDH20RemoveGetLambdaLarge();
	cout << "[DOUBLE HASHING HASH TABLE TESTER ENDED]" << endl;


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

void createQuadHashingTable(int size)
{
	deleteHashingTable();
	HTableUnderTest = new objPosQuadHashing(size);
}

void createDoubleHashingTable(int size)
{
	deleteHashingTable();
	HTableUnderTest = new objPosDoubleHashing(size);
}

void deleteHashingTable()
{
	if(HTableUnderTest != NULL)
	{
		delete HTableUnderTest;
		HTableUnderTest = NULL;
	}
	
}


objPos generateRandomPos()
{
	objPos temp;

	temp.setX(rand() % 100);
	temp.setY(rand() % 100);
	temp.setNum(rand() % 100);
	temp.setPF(rand() % 26 + 'A');
	temp.setSym(0);

	return temp;
}

char generateRandomChar()
{
	char candidate;

	if(rand() % 2 == 0)	candidate = rand() % 26 + 'a';
	else				candidate = rand() % 26 + 'A';

	return candidate;
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

bool assert_equal(bool a, bool b)
{
	bool result = (a == b);
	if(result)	
		successCount++;
	else
	{
		if(a)
			cout << "\t\t[ASSERTION] Expected: TRUE, but Actual: FALSE" << endl;		
		else
			cout << "\t\t[ASSERTION] Expected: FALSE, but Actual: TRUE" << endl;		
	}
	return result;
}

bool assert_equal(double a, double b)
{
	bool result = ((a <= (b+TOLERANCE_RANGE)) && (a >= (b-TOLERANCE_RANGE)));
	if(result)	
		successCount++;
	else
		cout << "\t\tExpected: " << a << ", but Actual: " << b << endl;		
	
	return result;
}