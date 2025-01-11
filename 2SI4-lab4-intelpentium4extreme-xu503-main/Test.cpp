//To Be Modified
#include "objPos.h"
#include "objPosBST.h"

#include <cstdlib>
#include <ctime>

#define SIZE20 20
#define SIZE50 50
#define TOTAL_ASSERT_COUNT 214
#define TOTAL_TEST_CASES 14

#include <iostream>
using namespace std;

objPosBST *TreeUnderTest;
int successCount;
int passCount;

void createNewTrees();
void clearTrees();

// Test cases
objPos data20w98[20];
bool data20w98isInTree[26];
bool data20w98isLeaf[26];
void createData20w98();

objPos data20wo98[20];
bool data20wo98isInTree[26];
bool data20wo98isLeaf[26];
void createData20wo98();

objPos data50w98[50];
bool data50w98isInTree[26];
bool data50w98isLeaf[26];
void createData50w98();

objPos data50wo98[50];
bool data50wo98isInTree[26];
bool data50wo98isLeaf[26];
void createData50wo98();

bool assert_equal(int, int);
bool assert_equal(char, char);
bool assert_equal(bool, bool);

// **** Enable This Flag for Verbose Tree Printout for Debugging **** //
// **** Enable This Flag for Verbose Tree Printout for Debugging **** //
bool verboseMode = true;
// **** Enable This Flag for Verbose Tree Printout for Debugging **** //
// **** Enable This Flag for Verbose Tree Printout for Debugging **** //




//////////////////////////////////////////
//////////////////////////////////////////
////////   CONSTRUCTOR TESTERS   /////////
//////////////////////////////////////////
//////////////////////////////////////////

/// Required Methods:  
//  Constructor, Destructor, deleteTree(), IsEmpty(), IsInTree()

/// Total Assertion Counts: 2

// 1 assertion count
void testConstructorIsEmpty() {
	
	bool result = true;
	cout << "TEST: testConstructorIsEmpty" << endl;

	createNewTrees();
	bool expected = true;
	bool actual = TreeUnderTest->isEmptyTree();	

	result = result & assert_equal(expected, actual);
	clearTrees();
	if(result) passCount++;
}

// 1 assertion count
void testConstructorIsInTreeEmpty() {
	
	bool result = true;
	cout << "TEST: testConstructorIsInTreeEmpty" << endl;

	createNewTrees();
	char testPF = (rand() % 26) + 'a';
	objPos target(0, 0, 0, testPF, 'a');
	bool expected = false;
	bool actual = TreeUnderTest->isInTree(target);	
	
	result = result & assert_equal(expected, actual);
	clearTrees();
	if(result) passCount++;
}



/////////////////////////////////////
/////////////////////////////////////
////////   INSERT TESTERS   /////////
/////////////////////////////////////
/////////////////////////////////////

// Required Methods:
// insert(), isLeaf(), printTree()

// 26 assertion counts  (a - z)
void testInsert20IsLeafCheckPrintTreeCase1() {

	bool result = true;

	cout << "TEST: testInsert20IsLeafCheckPrintTreeCase1" << endl;
	bool expected, actual;
	createNewTrees();

	for(int i = 0; i < SIZE20; i++)
	{
		TreeUnderTest->insert(data20w98[i]);
	}

	if(verboseMode)
	{
		cout << "Tree Under Test:" << endl;
		TreeUnderTest->printTree();			
	}
	
	objPos target(0, 0, 0, 'a', 'a');  // dummy
	for(int i = 0; i < 26; i++)
	{
		target.setPF(i + 'a');
		actual = TreeUnderTest->isLeaf(target);
		expected = data20w98isLeaf[i];

		result = result & assert_equal(expected, actual);
	}
			
	clearTrees();
	if(result) passCount++;
}


// 26 assertion counts  (a - z)
void testInsert20IsLeafCheckPrintTreeCase2() {

	bool result = true;

	cout << "TEST: testInsert20IsLeafCheckPrintTreeCase2" << endl;
	bool expected, actual;
	createNewTrees();

	for(int i = 0; i < SIZE20; i++)
	{
		TreeUnderTest->insert(data20wo98[i]);
	}

	if(verboseMode)
	{
		cout << "Tree Under Test:" << endl;
		TreeUnderTest->printTree();		
	}
	
	objPos target(0, 0, 0, 'a', 'a');  // dummy
	for(int i = 0; i < 26; i++)
	{
		target.setPF(i + 'a');
		actual = TreeUnderTest->isLeaf(target);
		expected = data20wo98isLeaf[i];

		result = result & assert_equal(expected, actual);
	}
			
	clearTrees();
	if(result) passCount++;
}

// 26 assertion counts  (a - z)
void testInsert50IsLeafCheckPrintTreeCase1() {

	bool result = true;

	cout << "TEST: testInsert50IsLeafCheckPrintTreeCase1" << endl;
	bool expected, actual;
	createNewTrees();

	for(int i = 0; i < SIZE50; i++)
	{
		TreeUnderTest->insert(data50w98[i]);
	}

	if(verboseMode)
	{
		cout << "Tree Under Test:" << endl;
		TreeUnderTest->printTree();		
	}
	
	objPos target(0, 0, 0, 'a', 'a');  // dummy
	for(int i = 0; i < 26; i++)
	{
		target.setPF(i + 'a');
		actual = TreeUnderTest->isLeaf(target);
		expected = data50w98isLeaf[i];

		result = result & assert_equal(expected, actual);
	}
			
	clearTrees();
	if(result) passCount++;
}

// 26 assertion counts  (a - z)
void testInsert50IsLeafCheckPrintTreeCase2() {

	bool result = true;

	cout << "TEST: testInsert50IsLeafCheckPrintTreeCase2" << endl;
	bool expected, actual;
	createNewTrees();

	for(int i = 0; i < SIZE50; i++)
	{
		TreeUnderTest->insert(data50wo98[i]);
	}
	
	if(verboseMode)
	{
		cout << "Tree Under Test:" << endl;
		TreeUnderTest->printTree();		
	}

	objPos target(0, 0, 0, 'a', 'a');  // dummy
	for(int i = 0; i < 26; i++)
	{
		target.setPF(i + 'a');
		actual = TreeUnderTest->isLeaf(target);
		expected = data50wo98isLeaf[i];

		result = result & assert_equal(expected, actual);
	}
			
	clearTrees();
	if(result) passCount++;
}



/////////////////////////////////////
/////////////////////////////////////
////////   REMOVE TESTERS   /////////
/////////////////////////////////////
/////////////////////////////////////

// Required Methods:
// remove(), isInTree()

// 26 assertion counts  (a - z)
#define REMOVECOUNT1 3
void testInsert20Remove3IsInTreeCheckPrintTreeCase1() {

	bool result = true;

	cout << "TEST: testInsert20Remove3IsInTreeCheckPrintTreeCase1" << endl;
	bool expected, actual;
	createNewTrees();

	for(int i = 0; i < SIZE20; i++)
	{
		TreeUnderTest->insert(data20w98[i]);
	}

	if(verboseMode)
	{
		cout << "Tree Under Test:" << endl;
		TreeUnderTest->printTree();			
	}

	objPos target(0, 0, 0, 'a', 'a');  // dummy
	int targetChar[REMOVECOUNT1];
	for(int i = 0; i < REMOVECOUNT1; i++)
	{
		targetChar[i] = rand() % 26;
		data20w98isInTree[targetChar[i]] = false;
		target.setPF(targetChar[i] + 'a');
		TreeUnderTest->remove(target);
	}
	
	for(int i = 0; i < 26; i++)
	{
		target.setPF(i + 'a');
		actual = TreeUnderTest->isInTree(target);
		expected = data20w98isInTree[i];

		result = result & assert_equal(expected, actual);
	}
			
	clearTrees();
	if(result) passCount++;
}


// 26 assertion counts  (a - z)
#define REMOVECOUNT2 5
void testInsert20Remove5IsInTreeCheckPrintTreeCase2() {

	bool result = true;

	cout << "TEST: testInsert20Remove5IsInTreeCheckPrintTreeCase2" << endl;
	bool expected, actual;
	createNewTrees();

	for(int i = 0; i < SIZE20; i++)
	{
		TreeUnderTest->insert(data20wo98[i]);
	}

	if(verboseMode)
	{
		cout << "Tree Under Test:" << endl;
		TreeUnderTest->printTree();			
	}

	objPos target(0, 0, 0, 'a', 'a');  // dummy
	int targetChar[REMOVECOUNT2];
	for(int i = 0; i < REMOVECOUNT2; i++)
	{
		targetChar[i] = rand() % 26;
		data20wo98isInTree[targetChar[i]] = false;
		target.setPF(targetChar[i] + 'a');
		TreeUnderTest->remove(target);
	}
	
	for(int i = 0; i < 26; i++)
	{
		target.setPF(i + 'a');
		actual = TreeUnderTest->isInTree(target);
		expected = data20wo98isInTree[i];

		result = result & assert_equal(expected, actual);
	}
			
	clearTrees();
	if(result) passCount++;
}


// 26 assertion counts  (a - z)
#define REMOVECOUNT3 8
void testInsert50Remove8IsInTreeCheckPrintTreeCase1() {

	bool result = true;

	cout << "TEST: testInsert50Remove8IsInTreeCheckPrintTreeCase1" << endl;
	bool expected, actual;
	createNewTrees();

	for(int i = 0; i < SIZE50; i++)
	{
		TreeUnderTest->insert(data50w98[i]);
	}

	if(verboseMode)
	{
		cout << "Tree Under Test:" << endl;
		TreeUnderTest->printTree();			
	}

	objPos target(0, 0, 0, 'a', 'a');  // dummy
	int targetChar[REMOVECOUNT3];
	for(int i = 0; i < REMOVECOUNT3; i++)
	{
		targetChar[i] = rand() % 26;
		data50w98isInTree[targetChar[i]] = false;
		target.setPF(targetChar[i] + 'a');
		TreeUnderTest->remove(target);
	}
	
	for(int i = 0; i < 26; i++)
	{
		target.setPF(i + 'a');
		actual = TreeUnderTest->isInTree(target);
		expected = data50w98isInTree[i];

		result = result & assert_equal(expected, actual);
	}
			
	clearTrees();
	if(result) passCount++;
}

// 26 assertion counts  (a - z)
#define REMOVECOUNT4 10
void testInsert50Remove10IsInTreeCheckPrintTreeCase2() {

	bool result = true;

	cout << "TEST: testInsert50Remove10IsInTreeCheckPrintTreeCase2" << endl;
	bool expected, actual;
	createNewTrees();

	for(int i = 0; i < SIZE50; i++)
	{
		TreeUnderTest->insert(data50wo98[i]);
	}

	if(verboseMode)
	{
		cout << "Tree Under Test:" << endl;
		TreeUnderTest->printTree();			
	}

	objPos target(0, 0, 0, 'a', 'a');  // dummy
	int targetChar[REMOVECOUNT4];
	for(int i = 0; i < REMOVECOUNT4; i++)
	{
		targetChar[i] = rand() % 26;
		data50wo98isInTree[targetChar[i]] = false;
		target.setPF(targetChar[i] + 'a');
		TreeUnderTest->remove(target);
	}
	
	for(int i = 0; i < 26; i++)
	{
		target.setPF(i + 'a');
		actual = TreeUnderTest->isInTree(target);
		expected = data50wo98isInTree[i];

		result = result & assert_equal(expected, actual);
	}
			
	clearTrees();
	if(result) passCount++;
}



///////////////////////////////////////////
///////////////////////////////////////////
////////   FIND GREATER TESTERS   /////////
///////////////////////////////////////////
///////////////////////////////////////////

// Required Methods:
// findGreater()

#define THRESHOLD 98  // DO NOT CHANGE!!

// 1 assertion call
void testInsert20w98FindGreaterCheckPrintTree() {

	bool result = true;

	cout << "TEST: testInsert20w98FindGreaterCheckPrintTree" << endl;
	bool expected, actual;
	createNewTrees();
	createData20w98();  // resetting remove modification

	for(int i = 0; i < SIZE20; i++)
	{
		TreeUnderTest->insert(data20w98[i]);
	}

	if(verboseMode)
	{
		cout << "Tree Under Test:" << endl;
		TreeUnderTest->printTree();			
	}

	actual = TreeUnderTest->findGreater(THRESHOLD);
	expected = true;

	result = result & assert_equal(expected, actual);
				
	clearTrees();
	if(result) passCount++;
}

// 1 assertion call
void testInsert20wo98FindGreaterCheckPrintTree() {

	bool result = true;

	cout << "TEST: testInsert20wo98FindGreaterCheckPrintTree" << endl;
	bool expected, actual;
	createNewTrees();
	createData20wo98();  // resetting remove modification

	for(int i = 0; i < SIZE20; i++)
	{
		TreeUnderTest->insert(data20wo98[i]);
	}

	if(verboseMode)
	{
		cout << "Tree Under Test:" << endl;
		TreeUnderTest->printTree();			
	}

	actual = TreeUnderTest->findGreater(THRESHOLD);
	expected = false;

	result = result & assert_equal(expected, actual);
				
	clearTrees();
	if(result) passCount++;
}

// 1 assertion call
void testInsert50w98FindGreaterCheckPrintTree() {

	bool result = true;

	cout << "TEST: testInsert50w98FindGreaterCheckPrintTree" << endl;
	bool expected, actual;
	createNewTrees();
	createData50w98();  // resetting remove modification

	for(int i = 0; i < SIZE50; i++)
	{
		TreeUnderTest->insert(data50w98[i]);
	}

	if(verboseMode)
	{
		cout << "Tree Under Test:" << endl;
		TreeUnderTest->printTree();			
	}

	actual = TreeUnderTest->findGreater(THRESHOLD);
	expected = true;

	result = result & assert_equal(expected, actual);
				
	clearTrees();
	if(result) passCount++;
}


// 1 assertion call
void testInsert50wo98FindGreaterCheckPrintTree() {

	bool result = true;

	cout << "TEST: testInsert50wo98FindGreaterCheckPrintTree" << endl;
	bool expected, actual;
	createNewTrees();
	createData50wo98();  // resetting remove modification

	for(int i = 0; i < SIZE50; i++)
	{
		TreeUnderTest->insert(data50wo98[i]);
	}

	if(verboseMode)
	{
		cout << "Tree Under Test:" << endl;
		TreeUnderTest->printTree();			
	}

	actual = TreeUnderTest->findGreater(THRESHOLD);
	expected = false;

	result = result & assert_equal(expected, actual);
				
	clearTrees();
	if(result) passCount++;
}



////////////////////////////////////////////////
////////////////////////////////////////////////
/////////////   Main Test Suite   //////////////
////////////////////////////////////////////////
////////////////////////////////////////////////


bool runAllTests(int argc, char const *argv[]) {
	
	// objPosBST Testers
	cout << "[CREATE TEST DATA]" << endl;
	createData20w98();
	createData20wo98();
	createData50w98();
	createData50wo98();

	cout << "[TREE TESTER STARTED]" << endl;
    testConstructorIsEmpty();  //1
	testConstructorIsInTreeEmpty();  //1
	
	testInsert20IsLeafCheckPrintTreeCase1();  // 20 w 98	// 26
	testInsert20IsLeafCheckPrintTreeCase2();  // 20 wo 98	// 26
	testInsert50IsLeafCheckPrintTreeCase1();  // 50 w 98	// 26
	testInsert50IsLeafCheckPrintTreeCase2();  // 50 wo 98	// 26

	testInsert20Remove3IsInTreeCheckPrintTreeCase1();  // 20 w 98	// 26
	testInsert20Remove5IsInTreeCheckPrintTreeCase2();  // 20 wo 98	// 26
	testInsert50Remove8IsInTreeCheckPrintTreeCase1();  // 50 w 98	// 26
	testInsert50Remove10IsInTreeCheckPrintTreeCase2(); // 50 wo 98	// 26
	
	testInsert20w98FindGreaterCheckPrintTree();   // 20 w 98	// 1
	testInsert20wo98FindGreaterCheckPrintTree();  // 20 wo 98	// 1
	testInsert50w98FindGreaterCheckPrintTree();   // 50 w 98	// 1
	testInsert50wo98FindGreaterCheckPrintTree();  // 50 wo 98	// 1

	cout << "[TREE TESTER ENDED]" << endl << endl;

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

void clearTrees()
{
	delete TreeUnderTest;
	TreeUnderTest = NULL;	
}

void createNewTrees()
{
	if(TreeUnderTest != NULL) clearTrees();
	TreeUnderTest = new objPosBST();
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



void createData20w98()
{
    data20w98[0] = objPos(42,78,27,'o','X');
    data20w98[1] = objPos(7,67,4,'m','C');
    data20w98[2] = objPos(10,44,38,'n','I');
    data20w98[3] = objPos(59,29,28,'t','L');
    data20w98[4] = objPos(48,91,19,'z','W');
    data20w98[5] = objPos(86,90,3,'k','H');
    data20w98[6] = objPos(89,59,46,'j','K');
    data20w98[7] = objPos(60,60,18,'w','U');
    data20w98[8] = objPos(46,72,10,'e','D');
    data20w98[9] = objPos(77,48,22,'z','Q');
    data20w98[10] = objPos(18,57,10,'s','P');
    data20w98[11] = objPos(61,82,35,'p','Y');
    data20w98[12] = objPos(25,53,15,'f','M');
    data20w98[13] = objPos(65,12,16,'t','U');
    data20w98[14] = objPos(73,63,29,'l','U');
    data20w98[15] = objPos(41,96,43,'x','L');
    data20w98[16] = objPos(20,45,13,'o','P');
    data20w98[17] = objPos(95,77,11,'k','O');
    data20w98[18] = objPos(24,30,49,'t','C');
    data20w98[19] = objPos(68,15,39,'t','S');

    data20w98isInTree[0] = false;    // a
    data20w98isInTree[1] = false;    // b
    data20w98isInTree[2] = false;    // c
    data20w98isInTree[3] = false;    // d
    data20w98isInTree[4] = true;    // e
    data20w98isInTree[5] = true;    // f
    data20w98isInTree[6] = false;    // g
    data20w98isInTree[7] = false;    // h
    data20w98isInTree[8] = false;    // i
    data20w98isInTree[9] = true;    // j
    data20w98isInTree[10] = true;    // k
    data20w98isInTree[11] = true;    // l
    data20w98isInTree[12] = true;    // m
    data20w98isInTree[13] = true;    // n
    data20w98isInTree[14] = true;    // o
    data20w98isInTree[15] = true;    // p
    data20w98isInTree[16] = false;    // q
    data20w98isInTree[17] = false;    // r
    data20w98isInTree[18] = true;    // s
    data20w98isInTree[19] = true;    // t
    data20w98isInTree[20] = false;    // u
    data20w98isInTree[21] = false;    // v
    data20w98isInTree[22] = true;    // w
    data20w98isInTree[23] = true;    // x
    data20w98isInTree[24] = false;    // y
    data20w98isInTree[25] = true;    // z

    data20w98isLeaf[0] = false;    // a
    data20w98isLeaf[1] = false;    // b
    data20w98isLeaf[2] = false;    // c
    data20w98isLeaf[3] = false;    // d
    data20w98isLeaf[4] = false;    // e
    data20w98isLeaf[5] = true;    // f
    data20w98isLeaf[6] = false;    // g
    data20w98isLeaf[7] = false;    // h
    data20w98isLeaf[8] = false;    // i
    data20w98isLeaf[9] = false;    // j
    data20w98isLeaf[10] = false;    // k
    data20w98isLeaf[11] = true;    // l
    data20w98isLeaf[12] = false;    // m
    data20w98isLeaf[13] = true;    // n
    data20w98isLeaf[14] = false;    // o
    data20w98isLeaf[15] = true;    // p
    data20w98isLeaf[16] = false;    // q
    data20w98isLeaf[17] = false;    // r
    data20w98isLeaf[18] = false;    // s
    data20w98isLeaf[19] = false;    // t
    data20w98isLeaf[20] = false;    // u
    data20w98isLeaf[21] = false;    // v
    data20w98isLeaf[22] = false;    // w
    data20w98isLeaf[23] = true;    // x
    data20w98isLeaf[24] = false;    // y
    data20w98isLeaf[25] = false;    // z
}

void createData20wo98()
{
    data20wo98[0] = objPos(65,39,38,'g','W');
    data20wo98[1] = objPos(0,26,24,'m','M');
    data20wo98[2] = objPos(76,83,19,'p','Q');
    data20wo98[3] = objPos(65,41,40,'q','W');
    data20wo98[4] = objPos(40,83,26,'b','W');
    data20wo98[5] = objPos(76,68,1,'w','J');
    data20wo98[6] = objPos(56,92,18,'a','C');
    data20wo98[7] = objPos(61,38,16,'q','S');
    data20wo98[8] = objPos(16,0,1,'g','Q');
    data20wo98[9] = objPos(51,64,8,'w','R');
    data20wo98[10] = objPos(15,82,12,'h','H');
    data20wo98[11] = objPos(3,19,3,'g','P');
    data20wo98[12] = objPos(88,23,16,'h','D');
    data20wo98[13] = objPos(71,75,5,'q','S');
    data20wo98[14] = objPos(30,48,31,'k','I');
    data20wo98[15] = objPos(45,95,7,'y','T');
    data20wo98[16] = objPos(95,92,16,'r','Y');
    data20wo98[17] = objPos(65,36,0,'g','A');
    data20wo98[18] = objPos(64,88,47,'j','Y');
    data20wo98[19] = objPos(22,26,22,'v','U');
    
    data20wo98isInTree[0] = true;    // a
    data20wo98isInTree[1] = true;    // b
    data20wo98isInTree[2] = false;    // c
    data20wo98isInTree[3] = false;    // d
    data20wo98isInTree[4] = false;    // e
    data20wo98isInTree[5] = false;    // f
    data20wo98isInTree[6] = true;    // g
    data20wo98isInTree[7] = true;    // h
    data20wo98isInTree[8] = false;    // i
    data20wo98isInTree[9] = true;    // j
    data20wo98isInTree[10] = true;    // k
    data20wo98isInTree[11] = false;    // l
    data20wo98isInTree[12] = true;    // m
    data20wo98isInTree[13] = false;    // n
    data20wo98isInTree[14] = false;    // o
    data20wo98isInTree[15] = true;    // p
    data20wo98isInTree[16] = true;    // q
    data20wo98isInTree[17] = true;    // r
    data20wo98isInTree[18] = false;    // s
    data20wo98isInTree[19] = false;    // t
    data20wo98isInTree[20] = false;    // u
    data20wo98isInTree[21] = true;    // v
    data20wo98isInTree[22] = true;    // w
    data20wo98isInTree[23] = false;    // x
    data20wo98isInTree[24] = true;    // y
    data20wo98isInTree[25] = false;    // z

    data20wo98isLeaf[0] = true;    // a
    data20wo98isLeaf[1] = false;    // b
    data20wo98isLeaf[2] = false;    // c
    data20wo98isLeaf[3] = false;    // d
    data20wo98isLeaf[4] = false;    // e
    data20wo98isLeaf[5] = false;    // f
    data20wo98isLeaf[6] = false;    // g
    data20wo98isLeaf[7] = false;    // h
    data20wo98isLeaf[8] = false;    // i
    data20wo98isLeaf[9] = true;    // j
    data20wo98isLeaf[10] = false;    // k
    data20wo98isLeaf[11] = false;    // l
    data20wo98isLeaf[12] = false;    // m
    data20wo98isLeaf[13] = false;    // n
    data20wo98isLeaf[14] = false;    // o
    data20wo98isLeaf[15] = false;    // p
    data20wo98isLeaf[16] = false;    // q
    data20wo98isLeaf[17] = false;    // r
    data20wo98isLeaf[18] = false;    // s
    data20wo98isLeaf[19] = false;    // t
    data20wo98isLeaf[20] = false;    // u
    data20wo98isLeaf[21] = true;    // v
    data20wo98isLeaf[22] = false;    // w
    data20wo98isLeaf[23] = false;    // x
    data20wo98isLeaf[24] = true;    // y
    data20wo98isLeaf[25] = false;    // z
}

void createData50w98()
{
    data50w98[0] = objPos(53,87,6,'i','W');
    data50w98[1] = objPos(8,14,4,'t','S');
    data50w98[2] = objPos(32,34,8,'i','R');
    data50w98[3] = objPos(50,72,19,'t','L');
    data50w98[4] = objPos(31,85,32,'b','J');
    data50w98[5] = objPos(30,94,26,'t','S');
    data50w98[6] = objPos(78,5,15,'v','Y');
    data50w98[7] = objPos(52,57,12,'t','K');
    data50w98[8] = objPos(88,49,2,'r','U');
    data50w98[9] = objPos(32,60,3,'z','J');
    data50w98[10] = objPos(88,53,32,'z','L');
    data50w98[11] = objPos(54,70,34,'i','X');
    data50w98[12] = objPos(37,31,27,'w','G');
    data50w98[13] = objPos(17,62,10,'r','X');
    data50w98[14] = objPos(19,43,23,'d','K');
    data50w98[15] = objPos(1,59,37,'w','R');
    data50w98[16] = objPos(23,52,32,'p','M');
    data50w98[17] = objPos(84,27,39,'y','F');
    data50w98[18] = objPos(7,16,37,'z','Q');
    data50w98[19] = objPos(55,57,2,'x','G');
    data50w98[20] = objPos(64,20,34,'l','Z');
    data50w98[21] = objPos(17,27,7,'i','E');
    data50w98[22] = objPos(68,52,13,'l','A');
    data50w98[23] = objPos(47,35,16,'k','Q');
    data50w98[24] = objPos(60,60,10,'y','B');
    data50w98[25] = objPos(7,43,16,'u','T');
    data50w98[26] = objPos(23,80,20,'c','V');
    data50w98[27] = objPos(59,70,30,'n','X');
    data50w98[28] = objPos(5,44,25,'i','L');
    data50w98[29] = objPos(32,47,39,'j','K');
    data50w98[30] = objPos(83,16,20,'m','I');
    data50w98[31] = objPos(45,21,0,'t','Q');
    data50w98[32] = objPos(11,1,36,'h','S');
    data50w98[33] = objPos(26,96,5,'c','L');
    data50w98[34] = objPos(1,59,10,'s','T');
    data50w98[35] = objPos(21,13,4,'n','L');
    data50w98[36] = objPos(53,90,7,'l','U');
    data50w98[37] = objPos(52,79,30,'j','K');
    data50w98[38] = objPos(12,0,30,'l','J');
    data50w98[39] = objPos(95,70,23,'e','O');
    data50w98[40] = objPos(1,88,17,'d','Z');
    data50w98[41] = objPos(5,23,20,'x','R');
    data50w98[42] = objPos(10,18,26,'i','U');
    data50w98[43] = objPos(12,91,21,'v','H');
    data50w98[44] = objPos(8,92,9,'g','X');
    data50w98[45] = objPos(75,41,27,'w','X');
    data50w98[46] = objPos(76,70,22,'i','W');
    data50w98[47] = objPos(91,27,16,'r','H');
    data50w98[48] = objPos(69,61,23,'w','E');
    data50w98[49] = objPos(59,13,21,'d','K');
    
    data50w98isInTree[0] = false;    // a
    data50w98isInTree[1] = true;    // b
    data50w98isInTree[2] = true;    // c
    data50w98isInTree[3] = true;    // d
    data50w98isInTree[4] = true;    // e
    data50w98isInTree[5] = false;    // f
    data50w98isInTree[6] = true;    // g
    data50w98isInTree[7] = true;    // h
    data50w98isInTree[8] = true;    // i
    data50w98isInTree[9] = true;    // j
    data50w98isInTree[10] = true;    // k
    data50w98isInTree[11] = true;    // l
    data50w98isInTree[12] = true;    // m
    data50w98isInTree[13] = true;    // n
    data50w98isInTree[14] = false;    // o
    data50w98isInTree[15] = true;    // p
    data50w98isInTree[16] = false;    // q
    data50w98isInTree[17] = true;    // r
    data50w98isInTree[18] = true;    // s
    data50w98isInTree[19] = true;    // t
    data50w98isInTree[20] = true;    // u
    data50w98isInTree[21] = true;    // v
    data50w98isInTree[22] = true;    // w
    data50w98isInTree[23] = true;    // x
    data50w98isInTree[24] = true;    // y
    data50w98isInTree[25] = true;    // z

    data50w98isLeaf[0] = false;    // a
    data50w98isLeaf[1] = false;    // b
    data50w98isLeaf[2] = true;    // c
    data50w98isLeaf[3] = false;    // d
    data50w98isLeaf[4] = false;    // e
    data50w98isLeaf[5] = false;    // f
    data50w98isLeaf[6] = true;    // g
    data50w98isLeaf[7] = false;    // h
    data50w98isLeaf[8] = false;    // i
    data50w98isLeaf[9] = true;    // j
    data50w98isLeaf[10] = false;    // k
    data50w98isLeaf[11] = false;    // l
    data50w98isLeaf[12] = true;    // m
    data50w98isLeaf[13] = false;    // n
    data50w98isLeaf[14] = false;    // o
    data50w98isLeaf[15] = false;    // p
    data50w98isLeaf[16] = false;    // q
    data50w98isLeaf[17] = false;    // r
    data50w98isLeaf[18] = true;    // s
    data50w98isLeaf[19] = false;    // t
    data50w98isLeaf[20] = true;    // u
    data50w98isLeaf[21] = false;    // v
    data50w98isLeaf[22] = false;    // w
    data50w98isLeaf[23] = true;    // x
    data50w98isLeaf[24] = false;    // y
    data50w98isLeaf[25] = false;    // z
}

void createData50wo98()
{
    data50wo98[0] = objPos(84,92,10,'s','V');
    data50wo98[1] = objPos(62,22,16,'i','T');
    data50wo98[2] = objPos(31,61,5,'m','P');
    data50wo98[3] = objPos(70,5,10,'u','F');
    data50wo98[4] = objPos(32,87,20,'k','W');
    data50wo98[5] = objPos(72,73,32,'l','B');
    data50wo98[6] = objPos(69,86,38,'o','S');
    data50wo98[7] = objPos(23,43,26,'x','I');
    data50wo98[8] = objPos(73,54,33,'y','U');
    data50wo98[9] = objPos(83,49,0,'c','W');
    data50wo98[10] = objPos(32,70,6,'p','Z');
    data50wo98[11] = objPos(62,68,36,'i','G');
    data50wo98[12] = objPos(9,73,25,'p','J');
    data50wo98[13] = objPos(67,36,12,'p','C');
    data50wo98[14] = objPos(14,82,8,'c','S');
    data50wo98[15] = objPos(35,19,15,'a','S');
    data50wo98[16] = objPos(93,73,2,'t','T');
    data50wo98[17] = objPos(58,21,35,'u','U');
    data50wo98[18] = objPos(96,40,22,'x','K');
    data50wo98[19] = objPos(65,10,35,'f','K');
    data50wo98[20] = objPos(95,35,20,'f','S');
    data50wo98[21] = objPos(39,90,6,'h','D');
    data50wo98[22] = objPos(53,58,16,'i','W');
    data50wo98[23] = objPos(46,59,26,'w','V');
    data50wo98[24] = objPos(99,97,32,'b','W');
    data50wo98[25] = objPos(19,76,18,'q','P');
    data50wo98[26] = objPos(25,12,29,'q','M');
    data50wo98[27] = objPos(88,80,0,'h','X');
    data50wo98[28] = objPos(28,33,28,'c','C');
    data50wo98[29] = objPos(15,76,15,'l','U');
    data50wo98[30] = objPos(26,53,0,'d','F');
    data50wo98[31] = objPos(75,66,16,'b','P');
    data50wo98[32] = objPos(60,61,9,'v','J');
    data50wo98[33] = objPos(93,46,25,'y','Y');
    data50wo98[34] = objPos(92,95,13,'y','D');
    data50wo98[35] = objPos(59,46,16,'g','K');
    data50wo98[36] = objPos(38,63,1,'j','E');
    data50wo98[37] = objPos(47,79,22,'y','M');
    data50wo98[38] = objPos(15,26,6,'e','H');
    data50wo98[39] = objPos(32,52,7,'i','G');
    data50wo98[40] = objPos(99,5,10,'z','N');
    data50wo98[41] = objPos(25,66,17,'z','Z');
    data50wo98[42] = objPos(22,10,9,'t','L');
    data50wo98[43] = objPos(39,88,38,'v','V');
    data50wo98[44] = objPos(79,60,24,'v','X');
    data50wo98[45] = objPos(49,23,6,'r','N');
    data50wo98[46] = objPos(81,79,28,'b','Z');
    data50wo98[47] = objPos(87,98,12,'f','B');
    data50wo98[48] = objPos(2,13,2,'a','B');
    data50wo98[49] = objPos(1,4,22,'z','E');
        
    data50wo98isInTree[0] = true;    // a
    data50wo98isInTree[1] = true;    // b
    data50wo98isInTree[2] = true;    // c
    data50wo98isInTree[3] = true;    // d
    data50wo98isInTree[4] = true;    // e
    data50wo98isInTree[5] = true;    // f
    data50wo98isInTree[6] = true;    // g
    data50wo98isInTree[7] = true;    // h
    data50wo98isInTree[8] = true;    // i
    data50wo98isInTree[9] = true;    // j
    data50wo98isInTree[10] = true;    // k
    data50wo98isInTree[11] = true;    // l
    data50wo98isInTree[12] = true;    // m
    data50wo98isInTree[13] = false;    // n
    data50wo98isInTree[14] = true;    // o
    data50wo98isInTree[15] = true;    // p
    data50wo98isInTree[16] = true;    // q
    data50wo98isInTree[17] = true;    // r
    data50wo98isInTree[18] = true;    // s
    data50wo98isInTree[19] = true;    // t
    data50wo98isInTree[20] = true;    // u
    data50wo98isInTree[21] = true;    // v
    data50wo98isInTree[22] = true;    // w
    data50wo98isInTree[23] = true;    // x
    data50wo98isInTree[24] = true;    // y
    data50wo98isInTree[25] = true;    // z

    data50wo98isLeaf[0] = false;    // a
    data50wo98isLeaf[1] = true;    // b
    data50wo98isLeaf[2] = false;    // c
    data50wo98isLeaf[3] = false;    // d
    data50wo98isLeaf[4] = true;    // e
    data50wo98isLeaf[5] = false;    // f
    data50wo98isLeaf[6] = true;    // g
    data50wo98isLeaf[7] = false;    // h
    data50wo98isLeaf[8] = false;    // i
    data50wo98isLeaf[9] = true;    // j
    data50wo98isLeaf[10] = false;    // k
    data50wo98isLeaf[11] = true;    // l
    data50wo98isLeaf[12] = false;    // m
    data50wo98isLeaf[13] = false;    // n
    data50wo98isLeaf[14] = false;    // o
    data50wo98isLeaf[15] = false;    // p
    data50wo98isLeaf[16] = false;    // q
    data50wo98isLeaf[17] = true;    // r
    data50wo98isLeaf[18] = false;    // s
    data50wo98isLeaf[19] = true;    // t
    data50wo98isLeaf[20] = false;    // u
    data50wo98isLeaf[21] = true;    // v
    data50wo98isLeaf[22] = false;    // w
    data50wo98isLeaf[23] = false;    // x
    data50wo98isLeaf[24] = false;    // y
    data50wo98isLeaf[25] = true;    // z
}