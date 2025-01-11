#include <assert.h>
#include <setjmp.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "CuTest.h"
#include "Questions.h"

//=========test 1==================================
	void TestQ1_1(CuTest *tc) {
		
		int input1=2,input2=4,expected=6,actual;
		actual=addFunction(input1,input2);
		CuAssertIntEquals(tc, expected, actual);
	}

//=========test 2==================================
    
	void TestQ1_2(CuTest *tc) {
		
		int input1=0,input2=4,expected=4,actual;
		actual=addFunction(input1,input2);
		CuAssertIntEquals(tc, expected, actual);
	}
    
//=========test 3==================================
    
	void TestQ1_3(CuTest *tc) {
		
		int input1=0,input2=3,expected=3,actual;
		actual=addFunction(input1,input2);
		CuAssertIntEquals(tc, expected, actual);
	}   

//=========test 4==================================
    
	void TestQ1_4(CuTest *tc) {
		
		int input1=5,input2=5,expected=10,actual;
		actual=addFunction(input1,input2);
		CuAssertIntEquals(tc, expected, actual);
	}

//=========test 5==================================
    
	void TestQ1_5(CuTest *tc) {
		
		int input1=4,input2=7,expected=11,actual;
		actual=addFunction(input1,input2);
		CuAssertIntEquals(tc, expected, actual);
	}

//=========test 6==================================
    
	void TestQ1_6(CuTest *tc) {
		
		int input1=115,input2=514,expected=629,actual;
		actual=addFunction(input1,input2);
		CuAssertIntEquals(tc, expected, actual);
	}		

//===========================================================
	CuSuite* Lab0GetSuite() {
		CuSuite* suite = CuSuiteNew();
		SUITE_ADD_TEST(suite, TestQ1_1);
		SUITE_ADD_TEST(suite, TestQ1_2); //如果要加testcase，则需要在这里添加环境。
		SUITE_ADD_TEST(suite, TestQ1_3);								
        SUITE_ADD_TEST(suite, TestQ1_4);
		SUITE_ADD_TEST(suite, TestQ1_5);
		SUITE_ADD_TEST(suite, TestQ1_6);
		return suite;
	}
    
