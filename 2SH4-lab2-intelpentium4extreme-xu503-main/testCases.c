#include <assert.h>
#include <setjmp.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "CuTest.h"
#include "Questions.h"
    

    
    
//=========Question 1==================================
void TestQ1_add(CuTest *tc) {

	int n = 5;
	double input1[5] = {3.60, 4.78, 6.00, 10.00, 0.01};
	double input2[5] = {1.50, 2.00, 3.30, 9.90, 1.00};
	double actual[5];
	double expected [5] = {5.10, 6.78, 9.30, 19.90, 1.01};
	add_vectors(input1,input2,actual,n);
	int i;
	for (i=0; i<n; i++)
		CuAssertDblEquals(tc, expected[i], actual[i],0.009);
}
//new test cases
void TestQ1_add2(CuTest *tc) {

	int n = 5;
	double input1[5] = {3.50, 4.68, 6.00, 10.00, 1.01};
	double input2[5] = {1.60, 2.10, 3.300, 0.01, 1.00};
	double actual[5];
	double expected [5] = {5.10, 6.78, 9.30, 10.01, 2.01};
	add_vectors(input1,input2,actual,n);
	int i;
	for (i=0; i<n; i++)
		CuAssertDblEquals(tc, expected[i], actual[i],0.009);
}
void TestQ1_add3(CuTest *tc) {

	int n = 5;
	double input1[5] = {0, 0, 0, 0, 0};
	double input2[5] = {1.50, 2.00, 3.30, 9.90, 1.00};
	double actual[5];
	double expected [5] = {1.50, 2.00, 3.30, 9.90, 1.00};
	add_vectors(input1,input2,actual,n);
	int i;
	for (i=0; i<n; i++)
		CuAssertDblEquals(tc, expected[i], actual[i],0.009);
}
void TestQ1_add4(CuTest *tc) {

	int n = 5;
	double input1[5] = {10.50, 4.00, 6.00, 10.00, 0.01};
	double input2[5] = {1.50, 2.00, 3.00, 10.00, 1.00};
	double actual[5];
	double expected [5] = {12.00, 6.00, 9.00, 20.00, 1.01};
	add_vectors(input1,input2,actual,n);
	int i;
	for (i=0; i<n; i++)
		CuAssertDblEquals(tc, expected[i], actual[i],0.009);
}


void TestQ1_scalar_prod(CuTest *tc) {

	int n = 5;
	double input1[5] = {5.0, 1.0, 1.00, 1.00, 1.00};
	double input2[5] = {12.0, 1.0, 1.00, 1.00, 1.00};
	double expected=64.00 ;
	double actual = scalar_prod(input1,input2,n);

	CuAssertDblEquals(tc, expected, actual,0.009);
}
// new test cases

void TestQ1_scalar_prod2(CuTest *tc) {

	int n = 5;
	double input1[5] = {0,0,0,0,0};
	double input2[5] = {0,0,0,0,0};
	double expected=0.00 ;
	double actual = scalar_prod(input1,input2,n);

	CuAssertDblEquals(tc, expected, actual,0.009);
}
void TestQ1_scalar_prod3(CuTest *tc) {

	int n = 5;
	double input1[5] = {1.8, 3.4, 10, 10.00, 0.01};
	double input2[5] = {1.50, 2.00,50, 5, 1.00};
	double expected=559.51 ;
	double actual = scalar_prod(input1,input2,n);

	CuAssertDblEquals(tc, expected, actual,0.009);
}
void TestQ1_scalar_prod4(CuTest *tc) {

	int n = 5;
	double input1[5] = {1, 4.78, 6.00, 10.00, 6};
	double input2[5] = {1.50, 2.3, 3.30, 5, 1.00};
	double expected=88.294 ;
	double actual = scalar_prod(input1,input2,n);

	CuAssertDblEquals(tc, expected, actual,0.009);
}

void TestQ1_norm(CuTest *tc) {

	int n = 5;
	double input1[5] = {3.60, 4.78, 6.00, 10.00, 0.01};
	double expected=13.108 ;
    double actual = norm2(input1,n);

    CuAssertDblEquals(tc, expected, actual,0.009);
}
//new test cases 
void TestQ1_norm2(CuTest *tc) {

	int n = 5;
	double input1[5] = {3.60, 4.78,7.00, 10.00, 0.01};
	double expected=13.594429 ;
    double actual = norm2(input1,n);

    CuAssertDblEquals(tc, expected, actual,0.009);
}
void TestQ1_norm3(CuTest *tc) {

	int n = 5;
	double input1[5] = {3.60, 4.78, 6.00, 11.00, 0.01};
	double expected=13.885550 ;
    double actual = norm2(input1,n);

    CuAssertDblEquals(tc, expected, actual,0.009);
}
void TestQ1_norm4(CuTest *tc) {

	int n = 5;
	double input1[5] = {3.60, 4.78, 6.00, 10.00, 220};
	double expected=220.390128 ;
    double actual = norm2(input1,n);

    CuAssertDblEquals(tc, expected, actual,0.009);
}
//--------------------------------------------------------------------------------
//===========================================================
//=================Question 2================================  

void TestQ2(CuTest *tc) {
	int n = 3;
	int input[3][3] = {{1, 2, 3},{ 5, 8, 9},{ 0, 3, 5}};
	int expected[9]= {1, 2, 5, 3, 8, 0, 9, 3, 5};
	int actual[9];
	diag_scan(input,actual);

	int i;
	for (i=0; i<n*n; i++)
		CuAssertIntEquals(tc, expected[i], actual[i]);
}
// new test cases.
void TestQ22(CuTest *tc) {
	int n = 3;
	int input[3][3] = {{1, 2, 3},{ 6, 8, 9},{ 0, 3, 5}};
	int expected[9]= {1, 2, 6, 3, 8, 0, 9, 3, 5};
	int actual[9];
	diag_scan(input,actual);

	int i;
	for (i=0; i<n*n; i++)
		CuAssertIntEquals(tc, expected[i], actual[i]);
}
void TestQ23(CuTest *tc) {
	int n = 3;
	int input[3][3] = {{1, 2, 3},{ 5, 8, 9},{ 15, 3, 5}};
	int expected[9]= {1, 2, 5, 3, 8, 15, 9, 3, 5};
	int actual[9];
	diag_scan(input,actual);

	int i;
	for (i=0; i<n*n; i++)
		CuAssertIntEquals(tc, expected[i], actual[i]);
}
void TestQ24(CuTest *tc) {
	int n = 3;
	int input[3][3] = {{17, 2, 3},{ 5, 8, 9},{ 0, 3, 5}};
	int expected[9]= {17, 2, 5, 3, 8, 0, 9, 3, 5};
	int actual[9];
	diag_scan(input,actual);

	int i;
	for (i=0; i<n*n; i++)
		CuAssertIntEquals(tc, expected[i], actual[i]);
}
//===========================================================
//=================Question 3================================   
void TestQ3_1(CuTest *tc) {
	int n=8;
	int input[]={0,0,23,0,-7,0,0,48};
	struct Q3Struct actual[8] = {0};
	struct Q3Struct expected[8] = {{23, 2}, {-7, 4}, {48, 7}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}};
	efficient(input,actual,n);
    
	int i;
	for (i=0; i<n; i++){
		CuAssertIntEquals(tc, expected[i].val, actual[i].val);
		CuAssertIntEquals(tc, expected[i].pos, actual[i].pos);
	}
}
// new test cases
void TestQ3_12(CuTest *tc) {
	int n=8;
	int input[]={0,11,23,0,-7,0,0,48};
	struct Q3Struct actual[8] = {0};
	struct Q3Struct expected[8] = {{11, 1},{23, 2}, {-7, 4}, {48, 7},  {0, 0}, {0, 0}, {0, 0}, {0, 0}};
	efficient(input,actual,n);
    
	int i;
	for (i=0; i<n; i++){
		CuAssertIntEquals(tc, expected[i].val, actual[i].val);
		CuAssertIntEquals(tc, expected[i].pos, actual[i].pos);
	}
}
void TestQ3_13(CuTest *tc) {
	int n=8;
	int input[]={0,0,0,0,-7,0,0,48};
	struct Q3Struct actual[8] = {0};
	struct Q3Struct expected[8] = {{-7, 4}, {48, 7}, {0, 0},{0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}};
	efficient(input,actual,n);
    
	int i;
	for (i=0; i<n; i++){
		CuAssertIntEquals(tc, expected[i].val, actual[i].val);
		CuAssertIntEquals(tc, expected[i].pos, actual[i].pos);
	}
}
void TestQ3_14(CuTest *tc) {
	int n=8;
	int input[]={0,0,0,0,0,0,0,1};
	struct Q3Struct actual[8] = {0};
	struct Q3Struct expected[8] = {{1, 7}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}};
	efficient(input,actual,n);
    
	int i;
	for (i=0; i<n; i++){
		CuAssertIntEquals(tc, expected[i].val, actual[i].val);
		CuAssertIntEquals(tc, expected[i].pos, actual[i].pos);
	}
}
void TestQ3_zeros(CuTest *tc) {
	int n=8;
	int input[]={0,0,0,0,0,0,0,0};
	struct Q3Struct actual[8] = {0};
	struct Q3Struct expected[8] = {0};
	efficient(input,actual,n);
    
	int i;
	for (i=0; i<n; i++){
		CuAssertIntEquals(tc, expected[i].val, actual[i].val);
		CuAssertIntEquals(tc, expected[i].pos, actual[i].pos);
	}
}

void TestQ3_combined(CuTest *tc) {
	int n=8;
	int input[]={0,0,23,0,-7,0,0,48};
	struct Q3Struct int_result[8] = {0};
	int expected[8] = {0,0,23,0,-7,0,0,48};
	int actual[8] = {0};
	efficient(input,int_result,n);
	reconstruct(actual, 8, int_result, 3);

	int i;
	for (i=0; i<n; i++){
		CuAssertIntEquals(tc, expected[i], actual[i]);
	}
}
// new test cases 
void TestQ3_combined2(CuTest *tc) {
	int n=8;
	int input[]={0,0,0,0,-7,0,0,48};
	struct Q3Struct int_result[8] = {0};
	int expected[8] = {0,0,0,0,-7,0,0,48};
	int actual[8] = {0};
	efficient(input,int_result,n);
	reconstruct(actual, 8, int_result, 2);

	int i;
	for (i=0; i<n; i++){
		CuAssertIntEquals(tc, expected[i], actual[i]);
	}
}


void TestQ3_combined3(CuTest *tc) {
	int n=8;
	int input[]={0,0,0,0,0,0,0,0};
	struct Q3Struct int_result[8] = {0};
	int expected[8] = {0,0,0,0,0,0,0,0};
	int actual[8] = {0};
	efficient(input,int_result,n);
	reconstruct(actual, 8, int_result, 0);

	int i;
	for (i=0; i<n; i++){
		CuAssertIntEquals(tc, expected[i], actual[i]);
	}
}

void TestQ3_combined4(CuTest *tc) {
	int n=8;
	int input[]={5,0,23,0,-7,0,0,48};
	struct Q3Struct int_result[8] = {0};
	int expected[8] = {5,0,23,0,-7,0,0,48};
	int actual[8] = {0};
	efficient(input,int_result,n);
	reconstruct(actual, 8, int_result, 4);

	int i;
	for (i=0; i<n; i++){
		CuAssertIntEquals(tc, expected[i], actual[i]);
	}
}
//===========================================================
//=================Question 4================================   
void TestQ4_BubbleSort_1(CuTest *tc) 
{
	int n=6;
	struct Q4Struct input[]={{10, 'c'}, {2, 'B'}, {-5, 'k'}, {12, 'z'}, {77, 'a'}, {-42, '?'}};	
	struct Q4Struct expected[]={{-42, '?'}, {-5, 'k'}, {2, 'B'}, {10, 'c'}, {12, 'z'}, {77, 'a'}};		
	
	sortDatabyBubble(input, n);
	
	int i;
	for (i=0; i<n; i++)
	{
		CuAssertIntEquals(tc, expected[i].intData, input[i].intData);
		CuAssertIntEquals(tc, expected[i].charData, input[i].charData);
	}
}

void TestQ4_BubbleSort_2(CuTest *tc) 
{
	int n=8;
	struct Q4Struct input[]={{-23, '='}, {78, ' '}, {11, 'Y'}, {-2, '0'}, {41, '+'}, {0, 'm'}, {55, 'T'}, {-9, 'o'}};	
	struct Q4Struct expected[]={{-23, '='}, {-9, 'o'}, {-2, '0'}, {0, 'm'}, {11, 'Y'}, {41, '+'}, {55, 'T'}, {78, ' '}};		
	
	sortDatabyBubble(input, n);
	
	int i;
	for (i=0; i<n; i++)
	{
		CuAssertIntEquals(tc, expected[i].intData, input[i].intData);
		CuAssertIntEquals(tc, expected[i].charData, input[i].charData);
	}
}
//new test cases
void TestQ4_BubbleSort_3(CuTest *tc) 
{
	int n=8;
	struct Q4Struct input[]={{-21, '='}, {78, ' '}, {11, 'Y'}, {-2, '0'}, {41, '+'}, {1, 'm'}, {55, 'T'}, {-11, 'o'}};	
	struct Q4Struct expected[]={{-21, '='}, {-11, 'o'}, {-2, '0'}, {1, 'm'}, {11, 'Y'}, {41, '+'}, {55, 'T'}, {78, ' '}};		
	
	sortDatabyBubble(input, n);
	
	int i;
	for (i=0; i<n; i++)
	{
		CuAssertIntEquals(tc, expected[i].intData, input[i].intData);
		CuAssertIntEquals(tc, expected[i].charData, input[i].charData);
	}
}
void TestQ4_BubbleSort_4(CuTest *tc) 
{
	int n=8;
	struct Q4Struct input[]={{7, 'h'}, {6, 'g'}, {5, 'f'}, {4, 'e'}, {3, 'd'}, {2, 'c'}, {1, 'b'}, {0, 'a'}};	
	struct Q4Struct expected[]={{0, 'a'}, {1, 'b'}, {2, 'c'}, {3, 'd'}, {4, 'e'}, {5, 'f'}, {6, 'g'}, {7, 'h'}};		
	
	sortDatabyBubble(input, n);
	
	int i;
	for (i=0; i<n; i++)
	{
		CuAssertIntEquals(tc, expected[i].intData, input[i].intData);
		CuAssertIntEquals(tc, expected[i].charData, input[i].charData);
	}
}
void TestQ4_BubbleSort_5(CuTest *tc) 
{
	int n=8;
	struct Q4Struct input[]={{-23, '1'}, {78, '2'}, {11, '3'}, {-2, '4'}, {41, '5'}, {0, '6'}, {55, '7'}, {-9, '8'}};	
	struct Q4Struct expected[]={{-23, '1'}, {-9, '8'}, {-2, '4'}, {0, '6'}, {11, '3'}, {41, '5'}, {55, '7'}, {78, '2'}};		
	
	sortDatabyBubble(input, n);
	
	int i;
	for (i=0; i<n; i++)
	{
		CuAssertIntEquals(tc, expected[i].intData, input[i].intData);
		CuAssertIntEquals(tc, expected[i].charData, input[i].charData);
	}
}

void TestQ4_SelectionSort_1(CuTest *tc) 
{
	int n=6;
	struct Q4Struct input[]={{10, 'c'}, {2, 'B'}, {-5, 'k'}, {12, 'z'}, {77, 'a'}, {-42, '?'}};	
	struct Q4Struct expected[]={{-42, '?'}, {-5, 'k'}, {2, 'B'}, {10, 'c'}, {12, 'z'}, {77, 'a'}};		
	
	sortDatabySelection(input, n);
	
	int i;
	for (i=0; i<n; i++)
	{
		CuAssertIntEquals(tc, expected[i].intData, input[i].intData);
		CuAssertIntEquals(tc, expected[i].charData, input[i].charData);
	}
}

void TestQ4_SelectionSort_2(CuTest *tc) 
{
	int n=8;
	struct Q4Struct input[]={{-21, '='}, {78, ' '}, {11, 'Y'}, {-2, '0'}, {41, '+'}, {1, 'm'}, {55, 'T'}, {-11, 'o'}};	
	struct Q4Struct expected[]={{-21, '='}, {-11, 'o'}, {-2, '0'}, {1, 'm'}, {11, 'Y'}, {41, '+'}, {55, 'T'}, {78, ' '}};			
	
	sortDatabySelection(input, n);
	
	int i;
	for (i=0; i<n; i++)
	{
		CuAssertIntEquals(tc, expected[i].intData, input[i].intData);
		CuAssertIntEquals(tc, expected[i].charData, input[i].charData);
	}
}
// give the result
void TestQ4_SelectionSort_3(CuTest *tc) 
{
	int n=8;
	struct Q4Struct input[]={{-23, '='}, {78, ' '}, {11, 'Y'}, {-2, '0'}, {41, '+'}, {0, 'm'}, {55, 'T'}, {-9, 'o'}};	
	struct Q4Struct expected[]={{-23, '='}, {-9, 'o'}, {-2, '0'}, {0, 'm'}, {11, 'Y'}, {41, '+'}, {55, 'T'}, {78, ' '}};			
	
	sortDatabySelection(input, n);
	
	int i;
	for (i=0; i<n; i++)
	{
		CuAssertIntEquals(tc, expected[i].intData, input[i].intData);
		CuAssertIntEquals(tc, expected[i].charData, input[i].charData);
	}
}
void TestQ4_SelectionSort_4(CuTest *tc) 
{
	int n=8;
	struct Q4Struct input[]={{7, 'h'}, {6, 'g'}, {5, 'f'}, {4, 'e'}, {3, 'd'}, {2, 'c'}, {1, 'b'}, {0, 'a'}};	
	struct Q4Struct expected[]={{0, 'a'}, {1, 'b'}, {2, 'c'}, {3, 'd'}, {4, 'e'}, {5, 'f'}, {6, 'g'}, {7, 'h'}};			
	
	sortDatabySelection(input, n);
	
	int i;
	for (i=0; i<n; i++)
	{
		CuAssertIntEquals(tc, expected[i].intData, input[i].intData);
		CuAssertIntEquals(tc, expected[i].charData, input[i].charData);
	}
}
void TestQ4_SelectionSort_5(CuTest *tc) 
{
	int n=8;
	struct Q4Struct input[]={{0, '0'}, {0, '0'}, {0, '0'}, {0, '0'}, {0, '0'}, {0, '0'}, {0, '0'}, {0, '0'}};	
	struct Q4Struct expected[]={{0, '0'}, {0, '0'}, {0, '0'}, {0, '0'}, {0, '0'}, {0, '0'}, {0, '0'}, {0, '0'}};			
	
	sortDatabySelection(input, n);
	
	int i;
	for (i=0; i<n; i++)
	{
		CuAssertIntEquals(tc, expected[i].intData, input[i].intData);
		CuAssertIntEquals(tc, expected[i].charData, input[i].charData);
	}
}

CuSuite* Lab2GetSuite() {

	CuSuite* suite = CuSuiteNew();

	SUITE_ADD_TEST(suite, TestQ1_add);
	SUITE_ADD_TEST(suite, TestQ1_add2);
	SUITE_ADD_TEST(suite, TestQ1_add3);
	SUITE_ADD_TEST(suite, TestQ1_add4);
	SUITE_ADD_TEST(suite, TestQ1_scalar_prod);
	SUITE_ADD_TEST(suite, TestQ1_scalar_prod2);
	SUITE_ADD_TEST(suite, TestQ1_scalar_prod3);
	SUITE_ADD_TEST(suite, TestQ1_scalar_prod4);
	SUITE_ADD_TEST(suite, TestQ1_norm);
	SUITE_ADD_TEST(suite, TestQ1_norm2);
	SUITE_ADD_TEST(suite, TestQ1_norm3);
	SUITE_ADD_TEST(suite, TestQ1_norm4);

	SUITE_ADD_TEST(suite, TestQ2);
	SUITE_ADD_TEST(suite, TestQ22);
	SUITE_ADD_TEST(suite, TestQ23);
	SUITE_ADD_TEST(suite, TestQ24);

	SUITE_ADD_TEST(suite, TestQ3_1);
	SUITE_ADD_TEST(suite, TestQ3_12);
	SUITE_ADD_TEST(suite, TestQ3_13);
	SUITE_ADD_TEST(suite, TestQ3_14);
	SUITE_ADD_TEST(suite, TestQ3_zeros);
	SUITE_ADD_TEST(suite, TestQ3_combined);
	SUITE_ADD_TEST(suite, TestQ3_combined2);
	SUITE_ADD_TEST(suite, TestQ3_combined3);
	SUITE_ADD_TEST(suite, TestQ3_combined4);

	SUITE_ADD_TEST(suite, TestQ4_BubbleSort_1);
	SUITE_ADD_TEST(suite, TestQ4_BubbleSort_2);
	SUITE_ADD_TEST(suite, TestQ4_BubbleSort_3);
	SUITE_ADD_TEST(suite, TestQ4_BubbleSort_4);
	SUITE_ADD_TEST(suite, TestQ4_BubbleSort_5);
	SUITE_ADD_TEST(suite, TestQ4_SelectionSort_1);
	SUITE_ADD_TEST(suite, TestQ4_SelectionSort_2);
	SUITE_ADD_TEST(suite, TestQ4_SelectionSort_3);
	SUITE_ADD_TEST(suite, TestQ4_SelectionSort_4);
	SUITE_ADD_TEST(suite, TestQ4_SelectionSort_5);
	return suite;
}
    
