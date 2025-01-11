#include <assert.h>
#include <setjmp.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "CuTest.h"
#include "Questions.h"
    

    
//=========Question 1==================================
    void TestQ1_for(CuTest *tc) {

        int actual = Q1_for(3);
        int expected = 166833;
        CuAssertIntEquals(tc, expected, actual);

        actual = Q1_for(11);
        expected = 45045;
        CuAssertIntEquals(tc, expected, actual);

        actual = Q1_for(37);
        expected = 13986;
        CuAssertIntEquals(tc, expected, actual);

        actual = Q1_for(10); //new test_case 1
        expected = 50500;
        CuAssertIntEquals(tc, expected, actual);   

        actual = Q1_for(20); //new test_case 2
        expected = 25500;
        CuAssertIntEquals(tc, expected, actual);

        actual = Q1_for(88); //new test_case 3
        expected = 5808;
        CuAssertIntEquals(tc, expected, actual);               
    }

    void TestQ1_while(CuTest *tc) {

        int actual = Q1_while(3);
        int expected = 166833;
        CuAssertIntEquals(tc, expected, actual);

        actual = Q1_while(11);
        expected = 45045;
        CuAssertIntEquals(tc, expected, actual);

        actual = Q1_while(37);
        expected = 13986;
        CuAssertIntEquals(tc, expected, actual);

        actual = Q1_for(10); //new test_case 1
        expected = 50500;
        CuAssertIntEquals(tc, expected, actual);

        actual = Q1_for(20); //new test_case 2
        expected = 25500;
        CuAssertIntEquals(tc, expected, actual);

        actual = Q1_for(88); //new test_case 3
        expected = 5808;
        CuAssertIntEquals(tc, expected, actual);        
    }
    void TestQ1_do(CuTest *tc) {

        int actual = Q1_dowhile(3);
        int expected = 166833;
        CuAssertIntEquals(tc, expected, actual);

        actual = Q1_dowhile(11);
        expected = 45045;
        CuAssertIntEquals(tc, expected, actual);

        actual = Q1_dowhile(37);
        expected = 13986;
        CuAssertIntEquals(tc, expected, actual);

        actual = Q1_for(10); //new test_case 1
        expected = 50500;
        CuAssertIntEquals(tc, expected, actual);

        actual = Q1_for(20); //new test_case 2
        expected = 25500;
        CuAssertIntEquals(tc, expected, actual);

        actual = Q1_for(88); //new test_case 3
        expected = 5808;
        CuAssertIntEquals(tc, expected, actual);       
    }


//===========================================================
//=================Question 2================================
    void TestQ2(CuTest *tc) {
        
        float threshold = 3.7;
	    float input = -10.1;
        int actual = Q2_FPN(input, threshold);
        int expected = -999;
        CuAssertIntEquals(tc, expected, actual);

        input = -6.2;
        actual = Q2_FPN(input, threshold);
        expected = 0;
        CuAssertIntEquals(tc, expected, actual);

        input = -2.4;
        actual = Q2_FPN(input, threshold);
        expected = 1;
        CuAssertIntEquals(tc, expected, actual);

        input = 1.8;
        actual = Q2_FPN(input, threshold);
        expected = 2;
        CuAssertIntEquals(tc, expected, actual);

        input = 4.9;
        actual = Q2_FPN(input, threshold);
        expected = 3;
        CuAssertIntEquals(tc, expected, actual);

        input = 91.1;
        actual = Q2_FPN(input, threshold);
        expected = -999;
        CuAssertIntEquals(tc, expected, actual);
        // additonal test cases 1
        input = 88.1;
        actual = Q2_FPN(input, threshold);
        expected = -999;
        CuAssertIntEquals(tc, expected, actual);
        // additonal test cases 2
        input = 90.1;
        actual = Q2_FPN(input, threshold);
        expected = -999;
        CuAssertIntEquals(tc, expected, actual);
        // additonal test cases 3
        input = 88.8;
        actual = Q2_FPN(input, threshold);
        expected = -999;
        CuAssertIntEquals(tc, expected, actual);
    }   




//===========================================================
//=================Question 3================================   
    void TestQ3_none(CuTest *tc) {
        int input = 5;
        int expected[100]={0};
        int actual[100]={0};
        int expectedCount = 0;
        int actualCount = Q3(input,actual);
        CuAssertIntEquals(tc, expectedCount, actualCount);
	    
        int i;
        for (i=0;i<100;i++)
          	CuAssertIntEquals(tc, expected[i], actual[i]);
    }

    void TestQ3_10(CuTest *tc) {
        int input = 10;
        int expected[100]={0},actual[100]={0};
        expected[0]= 6;
        int expectedCount=1;
        int actualCount = Q3(input,actual);
        CuAssertIntEquals(tc, expectedCount, actualCount);
	    
        int i;
        for (i=0;i<100;i++)
          	CuAssertIntEquals(tc, expected[i], actual[i]);
    }

    void TestQ3_1000(CuTest *tc) {
        int input = 1000;
        int expected[100]={0};
        int actual[100]={0};
        expected[0]=6;
        expected[1]=28;
        expected[2]=496;
        int expectedCount=3;
        int actualCount = Q3(input,actual);
        CuAssertIntEquals(tc, expectedCount, actualCount);
	
        int i;
        for (i=0;i<100;i++)
        	 CuAssertIntEquals(tc, expected[i], actual[i]);
    }
      
    void TestQ3_10000(CuTest *tc) {
        int input = 10000;
        int expected[100]={0},actual[100]={0};
        expected[0]=6;
        expected[1]=28;
        expected[2]=496;
        expected[3]=8128;
        int expectedCount=4;
        int actualCount = Q3(input,actual);
        CuAssertIntEquals(tc, expectedCount, actualCount);
    
    	int i;
        for (i=0;i<100;i++)
          	CuAssertIntEquals(tc, expected[i], actual[i]);

    }
    
    void TestQ3_neg(CuTest *tc) {
        int input = -1000;
        int expected[100]={0},actual[100]={0};
        int expectedCount=0;
        int actualCount = Q3(input,actual);
        CuAssertIntEquals(tc, expectedCount, actualCount);
	    
        int i;
        for (i=0;i<100;i++)
          	CuAssertIntEquals(tc, expected[i], actual[i]);
    }
    //new test cases:
    void TestQ3_8128(CuTest *tc) {
        int input = 8128;
        int expected[100]={0},actual[100]={0};
        expected[0]=6;
        expected[1]=28;
        expected[2]=496;
        expected[3]=8128;
        int expectedCount=4;
        int actualCount = Q3(input,actual);
        CuAssertIntEquals(tc, expectedCount, actualCount);
    
    	int i;
        for (i=0;i<100;i++)
          	CuAssertIntEquals(tc, expected[i], actual[i]);

    }
        void TestQ3_8127(CuTest *tc) {
        int input = 8127;
        int expected[100]={0},actual[100]={0};
        expected[0]=6;
        expected[1]=28;
        expected[2]=496;
        int expectedCount=3;
        int actualCount = Q3(input,actual);
        CuAssertIntEquals(tc, expectedCount, actualCount);
    
    	int i;
        for (i=0;i<100;i++)
          	CuAssertIntEquals(tc, expected[i], actual[i]);

    }
        void TestQ3_497(CuTest *tc) {
        int input = 497;
        int expected[100]={0},actual[100]={0};
        expected[0]=6;
        expected[1]=28;
        expected[2]=496;
        int expectedCount=3;
        int actualCount = Q3(input,actual);
        CuAssertIntEquals(tc, expectedCount, actualCount);
    
    	int i;
        for (i=0;i<100;i++)
          	CuAssertIntEquals(tc, expected[i], actual[i]);

    }    


//===========================================================
//=================Question 4================================ 
    void TestQ4_8(CuTest *tc) {

        int targetArray[8] = {6, 13, 0, -7, 28, 1, 45, -4};
		int inputSize = 8;
        int expectedArray[8] = {-7, -4, 0, 1, 6, 13, 28, 45};
        int expectedPass = 7;
        int actualPass = Q4_Bubble(targetArray, inputSize);        
        CuAssertIntEquals(tc, expectedPass, actualPass);

        int i;
        for (i = 0; i < inputSize; i++)
          	CuAssertIntEquals(tc, expectedArray[i], targetArray[i]);
    } 

    void TestQ4_16(CuTest *tc) {

		int targetArray[16] = {11, 3, -2, 88, 10, 25, 103, 91, -44, 0, 233, -85, 1015, -7, -411, -27};
		int inputSize = 16;
        int expectedArray[16] = {-411, -85, -44, -27, -7, -2, 0, 3, 10, 11, 25, 88, 91, 103, 233, 1015};
        int expectedPass = 15;
        int actualPass = Q4_Bubble(targetArray, inputSize);        
        CuAssertIntEquals(tc, expectedPass, actualPass);

        int i;
        for (i = 0; i < inputSize; i++)
          	CuAssertIntEquals(tc, expectedArray[i], targetArray[i]);
    } 

    void TestQ4_25(CuTest *tc) {

		int targetArray[25] = {889, 12, 69, 7, -25, 25, 353, -1422, -1, -65535, 11, 89, 63, -375, 227, 55, 3688, -324, 71, -6, -31, 88, 477, -5225, -91};
		int inputSize = 25;
        int expectedArray[25] = {-65535, -5225, -1422, -375, -324, -91, -31, -25, -6, -1, 7, 11, 12, 25, 55, 63, 69, 71, 88, 89, 227, 353, 477, 889, 3688};
        int expectedPass = 23;
        int actualPass = Q4_Bubble(targetArray, inputSize);        
        CuAssertIntEquals(tc, expectedPass, actualPass);

        int i;
        for (i = 0; i < inputSize; i++)
            CuAssertIntEquals(tc, expectedArray[i], targetArray[i]);
    } 
    // new test
    void TestQ4_10(CuTest *tc) {

		int targetArray[10] = {9, 8, 7, 6, 5, 4, 3, 2, 1, 0};
		int inputSize = 10;
        int expectedArray[10] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
        int expectedPass = 10;
        int actualPass = Q4_Bubble(targetArray, inputSize);        
        CuAssertIntEquals(tc, expectedPass, actualPass);

        int i;
        for (i = 0; i < inputSize; i++)
            CuAssertIntEquals(tc, expectedArray[i], targetArray[i]);
    } 
  
    CuSuite* Lab1GetSuite() {
        
        CuSuite* suite = CuSuiteNew();

        
        SUITE_ADD_TEST(suite, TestQ1_for);
        SUITE_ADD_TEST(suite, TestQ1_while);
        SUITE_ADD_TEST(suite, TestQ1_do);
        

        SUITE_ADD_TEST(suite, TestQ2);

        
        SUITE_ADD_TEST(suite, TestQ3_none);
        SUITE_ADD_TEST(suite, TestQ3_10);
        SUITE_ADD_TEST(suite, TestQ3_1000);
        SUITE_ADD_TEST(suite, TestQ3_10000);
        SUITE_ADD_TEST(suite, TestQ3_8128);
        SUITE_ADD_TEST(suite, TestQ3_8127);
        SUITE_ADD_TEST(suite, TestQ3_497);        
        SUITE_ADD_TEST(suite, TestQ3_neg);
     
        

        SUITE_ADD_TEST(suite, TestQ4_8);
        SUITE_ADD_TEST(suite, TestQ4_16);
        SUITE_ADD_TEST(suite, TestQ4_25);
        SUITE_ADD_TEST(suite, TestQ4_10);

        return suite;
    }
    
