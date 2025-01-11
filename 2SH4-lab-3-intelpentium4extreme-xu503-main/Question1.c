#include <stdio.h>
#include <stdlib.h>
#include "Questions.h"

int my_strlen(const char * const str1)
{
	// Returns the length of the string - the number of characters, but IGNORING the terminating NULL character
	int length = 0;
	while(str1[length] != '\0'){
		length += 1;
	}
	return (length);
}

int my_strcmp(const char * const str1, const char * const str2)
{
	// Return 0 if the two strings are not identical.  Return 1 otherwise.
	int pos1;
	int pos2;
	// Criteria 1: Check their lenghts.  If not the same length, not equal
	for(pos1 = 0; str1[pos1] !='\0'; pos1++);
	for(pos2 = 0; str2[pos2] !='\0'; pos2++);
	if(pos1 != pos2){
		return 0;
	}
	pos1 = 0;
	// Criteria 2: Check their contents char-by-char.  If mismatch found, not equal
	while(str1[pos1] != '\0'){
		if(str1[pos1] != str2[pos1]){
			return 0;
		}
		pos1++;
	}
	// if passing the two criteria, strings equal
	return 1;
}


int my_strcmpOrder(const char * const str1, const char * const str2)
{
	/*compare_str alphabetically compares two strings.
    	If str2 is alphabetically  smaller than str1 (comes before str1),
    	the function returns a 1, else if str1 is smaller than str2, the
    	function returns a 0.*/
	// if two strings are completely identical in order, return -1.
	int pos = 0;
	while(str1[pos] != '\0' || str2[pos] != '\0'){
		if(str1[pos] != str2[pos]){
			if(str1[pos] > str2[pos]){
				return 1;
			}
			else{
				return 0;
			}
			
		}
		pos += 1;
	}

	return -1;
	// We are NOT looking for any custom alphabetical order - just use the integer values of ASCII characte
}


char *my_strcat(const char * const str1, const char * const str2){

	/* this is the pointer holding the string to return */
	char* z;
	/*write your implementation here*/
	int len_str1 = 0,len_str2 = 0,i,j;
	len_str1 = my_strlen(str1);
	len_str2 = my_strlen(str2);
	z = (char *)malloc((len_str1 + len_str2 + 1)*sizeof(char)); // space for '/0'
	for(i = 0; i < len_str1; i++){
		z[i] = (char)str1[i];
	}
	// i overthrough one akkod
	for(j = 0; j < len_str2; j++){
		z[i+j] = (char)str2[j];
	}
	z[(len_str1 + len_str2)] = 0;   // 注意tmd z【寻址位】和分配地址数量差一，看半天没找出来
	/* finally, return the string*/
	return z;
	// IMPORTANT!!  Where did the newly allocated memory being released?
	free(z);	
	// THINK ABOUT MEMORY MANAGEMENT
}