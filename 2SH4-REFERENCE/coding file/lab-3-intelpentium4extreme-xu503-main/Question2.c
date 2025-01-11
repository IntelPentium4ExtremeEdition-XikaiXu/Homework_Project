#include <stdio.h>
#include <stdlib.h>
#include "Questions.h"




char **read_words(const char *input_filename, int *nPtr){
	
    char **word_list; 
    int i,j;
    char* Temp[114];
    int count_x = 0;
    int pos;     
    /*write your implementation here*/
    FILE* myFile;
    // !!READ C FILE HANDLING INSTRUCTIONS BEFORE PROCEEDING!! //
    // Step 1:  Open file "input_filename" in ASCII read mode
    myFile = fopen(input_filename , "r");
    // Step 2:  Read the first line of the text file as an integer into nPtr
    fscanf(myFile, "%ls", nPtr);
    //          This is the number of valid lines in the text file containing words to be sorted
    if(*nPtr == 0 && *nPtr == 1){
        return NULL;
    }
    else if(*nPtr == NULL);
    // Step 3:  Allocate an array of nPtr number of char pointer under word_list

    word_list = (char **)malloc(*nPtr * sizeof(char *)); // creat 6 empty table to fit 6 char pointers
    
    
    for(i = 0; i < *nPtr; i++){
        fscanf("myFile", "%s", "Temp");
        pos = 0;
        while(Temp[pos] != NULL){
            count_x += 1;
        }
        word_list[i] = (char *)malloc(count_x * sizeof(char*)); // creat 1st order info of the  directed information.
        for (j = 0 ; j < count_x; j++){
            word_list[i][j] = Temp[j];
        }
        count_x = 0; // reset the count 0;
    }//find the mount of space i need to deal with

    // Step 4:  Allocate an array of characters for each word under word_list; 

    //          Read each line from the input file and save it in the allocated array.  
    // Step 5:  Close the file handle
    fclose(input_filename);
    // Step 6:  (for debugging purpose) Print out the contents in the string array
    //          This is for your own confirmation.  Remove this printing code before submission.
    
    return word_list;
}

void swap(char **str1, char **str2)
{    
	/*this is a helper function that you can implement and use to facilitate your development*/
    
    // Hint: str1 and str2 are not just double pointers - they are single pointers passed-by-reference
    //       Therefore, you should treat *str1 and *str2 as changeable addresses of the start of their
    //       respective strings.

    // Hint 2: Swapping two strings in an array of strings is as easy as swapping the starting addresses
    //         of the two target strings to be swapped.  Review Lecture Contents!
    

    // by using pointers operation; we can find the mem_location differ, swap two mem location
    int Temp; // give a double pointer but with no mem slot 
            // init - last 
    Temp = str1 - str2; //giving the distance of the init memory location;
    str1 = str1 - Temp;
    str2 = str2 + Temp;  // swap the init driection of the mem slot 
}

void delete_wordlist(char **word_list, int size)
{
    /*This is a helper function that you MUST IMPLEMENT and CALL at the end of every test case*/
    /*THINK ABOUT WHY!!!*/
    int i;
    for(i = 0; i < size; i++){
        free(word_list[i]);
    }
    // implement your table deletion code here //
   
    // Hint: Review how to deallocate 2D array on heap.  word_list is a 2D array of chars on heap.
    
}

void sort_words_Bubble(char **words, int size)
{   
	/*write your implementation here*/
    char **str1;
    char **str2;
    swap(**str1, **str2);
    // !!IMPLEMENT SWAP() BEFORE ATTEMPTING THIS FUNCTION!! //

    // By this time you should be able to implement bubble sort with your eyes closed ;)
    int i,j;
    for(i = 0; i < size - 1 ; i++){
        size = sizeof(words[i])/sizeof(char*);
        for(j = 0; j < size; j++){
            if(words[i][j] > words[i+1][j]){
                swap(words[i][j], words[i+1][j]);
                break;
            }
        }
    }
    // Hint: Use your own my_strcmpOrder to compare the ASCII size of the two strings, and
    //       use the returned result as the sorting reference.  

    // Hint: Use swap() if string swapping is required

    
}



void sort_words_Selection(char **words, int size){

    // This implementation of string-sorting function using Selection Sort contains 2 semantic bugs

    // Fix the code, and document how you've found the bugs using GNU debugger.
    // Take screenshots of the debugger output at the instance where you've determined every bug.

    // You will be tested again at the cross exam.

    // If you forgot how Selection Sort works, review Lab 2 document.

    int i, j;    
    int min, minIndex;
    
    for(i = 0; i < size; i++)
    {
        minIndex = i;

        for(j = i + 1; j < size; j++)
        {
            if(my_strcmpOrder(words[i], words[j]) == 1)
            {
                minIndex = j;
            }                        
        }
       
        if(minIndex != j)
        {
            swap(&words[i], &words[minIndex]);
        }

    }
    
}

