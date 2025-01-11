#include <stdio.h>
#include <stdlib.h>

#include <math.h>
#include "Questions.h"



void add_vectors(double vector1[],double vector2[],double vector3[],int size)
{
    /*vector3 should store the sum of vector1 and vector2. 
	You may assume that all three arrays have the size equal to the input parameter "size"
	*/
	//write your code below
	int i;//give a int element for for loop
	for(i = 0; i <= size - 1;i++){        // from array position 0 all the way to position size - 1.
		vector3[i] = vector1[i] + vector2[i];
	}
}

double scalar_prod(double vector1[],double vector2[],int size)
{
	// this is the variable holding the scalar product of the two vectors
    double prod=0;
	//write your code below to calculate the prod value
	int j;
	for(j = 0; j <= size - 1;j++){
		prod += vector1[j]*vector2[j];  //each cycle = summision of the element.
	}
	// return the result
    return prod;
}

double norm2(double vector1[], int size)
{
	//this is the variable holding the L2 norm of the passed vector
    double L2 = 0; // need to init the content of L2.
	    
	//write your code here
	// you should call function scalar_prod().
	int k;
	for(k = 0; k<= size - 1 ;k++){   
		L2 += pow(vector1[k],2);    //Let L2 first storage the integration of the ints.
	}
	//finally, return the L2 norm
	if(L2 >= 0){           //useless but protect from garbage data, only needs when l2 is large than double float size caused mem leak and tern to negative.
		L2 = sqrt(L2);
	}
    return L2;
}
