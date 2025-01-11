#include "Question1.h"
#include <iostream>
using namespace std;

#define TOTAL_ASSERT_COUNT 1

int successCount;
void assert_equal(int, int);


void testQuestion1() {
	cout << "TEST: testQuestion1" << endl;
	
	int operand1 = 3, operand2 = 4;
	int expected = operand1 + operand2;

	int actual = add(operand1, operand2);

	assert_equal(expected, actual);
}

bool runAllTests(int argc, char const *argv[]) {
	
    testQuestion1();
	
	if(successCount != TOTAL_ASSERT_COUNT) 
		return false;
	else 
		return true;
}

int main(int argc, char const *argv[]) {
    successCount = 0;
	bool successCode = runAllTests(argc, argv);
	if(successCode)	cout << endl << "Passed All Tests" << endl;
	else			cout << "Failed Tests, Check Failure" << endl;	
	cout << "Assertion Score: " << successCount << " / " << TOTAL_ASSERT_COUNT << endl;	

	return successCode? EXIT_SUCCESS : EXIT_FAILURE;
}

void assert_equal(int a, int b)
{
	bool result = (a == b);
	if(result)	
		successCount++;
	else
	{
		cout << "\t[ASSERTION] Expected: " << a << ", but Actual: " << b << endl;		
	}
	//return result;
}
