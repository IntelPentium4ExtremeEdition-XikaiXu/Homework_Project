#include "Questions.h"
int Q1_for(int num){
	int sum = 0;
	int i;
	// calculate your sum below..this has to use for loop
	// for loop is depends on i value, with limitation of 1000.
	for(i = 1;i <= 1000;i++){  
		if(i % num ==0){
		sum += i;
		}
		else{
		}
	}
	// here, we return the calcualted sum:
	return sum;
}
int Q1_while(int num){
	int sum = 0;
	// calculate your sum below..this has to use while loop
	int j = 1;
	// while loop is limited by j value 
	while (j <= 1000){
		if(j % num == 0){
		sum += j;
		}
		else{
		}
		j++;
	}
	// here, we return the calcualted sum:
	return sum;
}
int Q1_dowhile(int num){
	int sum = 0;
	// calculate your sum below..this has to use do-while loop
	int k = 1;
	do{
		if(k % num == 0){
		sum += k;
		}
		else{
		}
		k++;
	}
	while(k<1000);
	// do while loop will do the function first o after 1000 times the loop will stop, but the function do first,
	//so the limit is 999.
	// here, we return the calcualted sum:
	return sum;
}

//===============================================================================================
int Q2_FPN(float Q2_input, float Q2_threshold){
	
	int result;
	// Determine which range does Q2_input fall into.  Keep in mind the floating point number range.
	// Assign the correct output to the result.
	// C89 only allows single line compairsion, using && means and logic determination.
	if(-2*Q2_threshold<=Q2_input&&Q2_input<=-1*Q2_threshold){
		result = 0;
	}
	else if(-1*Q2_threshold<=Q2_input&&Q2_input<0){
		result = 1;
	}        
	else if(0<=Q2_input&&Q2_input<Q2_threshold){
		result = 2;
	}  
	else if(Q2_threshold<=Q2_input&&Q2_input<=2*Q2_threshold){
		result = 3;
	}  
	else{
		result = -999;
	}
	// Finally, return the result.
	return result;
}

//===============================================================================================
int Q3(int Q3_input, int perfect[]){

	//counts is the variable that should hold the total number of found perfect numbers
	//you should update it within your code and return it at the end
	int counts = 0;
	int factor = 0;
    int i,j;
	int var_pos = 0;
	for (i = 2; i <= Q3_input; i++){   //as the Q3 input to i , in list to find all of the num between the range
		for (j = 1; j < i; j++){	//from 1 to the element of i, this step to find all the number before i, provide
			if (i % j == 0){		//opportunity to find the factors, by using i%j == 0 means no remiander. 
				factor = factor + j;	// and we need the sum of the factor, so add them together
			}
			else{		
			}
		}
		if (factor == i){				// if the factor addition equals to itself, can be seen as a perfect num
			counts = counts + 1;
			perfect[var_pos] = i;		//write the perfect number in to list
			var_pos = var_pos + 1;		//prepare next location.
		}
		else{
		}
		factor = 0;						// reset the factor addition space to 0, prepare next addition.
	}
		/*
		*perfect is an array that you need to add into it any perfect number you find
		*which means at the end of this function, the perfect[] array should hold all the found perfect numbers in the range
		*you do not need to return perfect because as stated in lectures arrays are already passed by reference. so, modifying them will 
		*autmoatically reflect in the main calling function.
		*/
	return counts;
}

//===============================================================================================
int Q4_Bubble(int array[], int size){
	// This variable tracks the number of passes done on the array to sort the array.
	int passes = 0;
	int i,j,x;

	while (1){
		i = 0;
        for (j = 0;j <= size-2 ;j++){    //located to the last 2 elements
	        if (array[j+1] < array[j]){  // if the next is small than the current, make a memory and swap the location.
                x = array[j];
	            array[j] = array[(j + 1)];
	    	    array[(j + 1)] = x;
				i += 1;                  //counter to terminate the function
	        }
	        else{              
	        } 
        }
		passes +=1;
		if (i == 0){                     // if there is no swap anymore, stop the while loop.
			break;
		}
	}
	// Pseudocode
	// 	1. Given an array and its size, visit every single element in the array up to size-2 (i.e. up to the second last element, omit the last element)
	//  2. For every visited element (current element), check its subsequent element (next element).  
	//     If the next element is smaller, swap the current element and the next element. 
	//  3. Continue until reaching size-2 element.  This is considered One Pass => increment pass count by one.
	//  4. Repeat 1-3 until encountering a pass in which no swapping was done.
	//   -> Sorting Completed.
	// Finally, return the number of passes used to complete the Bubble Sort
	return passes;	
}