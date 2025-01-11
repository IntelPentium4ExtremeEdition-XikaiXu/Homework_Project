#include <stdio.h>
#include <stdlib.h>
#include "Questions.h"




char **read_words(const char *input_filename, int *nPtr){
	
    char **word_list;         
    char temp[20];    //init a sting can temp storage info from
    int i,j,temp_len;
    FILE* myFile;

    myFile = fopen(input_filename,"r");
    if(myFile == NULL){
        printf("Empty file\n");
        return 0;
    }
    fscanf(myFile, "%d", nPtr);
    if(*nPtr == 0){
        printf("No space!!\n");
        return 0;
    }
    word_list=(char**)malloc(*nPtr*sizeof(char*));
    if (word_list == NULL) {
        printf("Allocation fail\n");
        return 0;
    }

    for(i=0 ; i < *nPtr ; i++){ 
        fscanf(myFile, "%s", temp);
        temp_len=my_strlen(temp);
        word_list[i] = (char*)malloc((temp_len+1)*sizeof(char)); // give one extra space for NULL
        for(j = 0;j < temp_len; j++){
            word_list[i][j]=temp[j]; //store the word char
        }
        word_list[i][temp_len]='\0';  //end of the string using null
    }
    // Step 1:  Open file "input_filename" in ASCII read mode
    // Step 2:  Read the first line of the text file as an integer into nPtr
    //          This is the number of valid lines in the text file containing words to be sorted
    // Step 3:  Allocate an array of nPtr number of char pointer under word_list
    // Step 4:  Allocate an array of characters for each word under word_list; 
    //          Read each line from the input file and save it in the allocated array.  
    // Step 5:  Close the file handle
    // Step 6:  (for debugging purpose) Print out the contents in the string array
    //          This is for your own confirmation.  Remove this printing code before submission.
    fclose(myFile); //close the file as protection

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
    char *Temp; // give a single pointer but with no mem slot 
    Temp = *str1; //giving the distance of the init memory location;
    *str1 = *str2;
    *str2 = Temp;

}

void delete_wordlist(char **word_list, int size)
{
    /*This is a helper function that you MUST IMPLEMENT and CALL at the end of every test case*/
    /*THINK ABOUT WHY!!!*/

    // implement your table deletion code here //
   
    // Hint: Review how to deallocate 2D array on heap.  word_list is a 2D array of chars on heap.
    int i=0;
    for(i = 0;i < size; i++){
        free(word_list[i]); //loop though and free the spaces
    }
    free(word_list);
    
}

void sort_words_Bubble(char **words, int size)
{   
	/*write your implementation here*/

    // !!IMPLEMENT SWAP() BEFORE ATTEMPTING THIS FUNCTION!! //

    // By this time you should be able to implement bubble sort with your eyes closed ;)
    // Hint: Use your own my_strcmpOrder to compare the ASCII size of the two strings, and
    //       use the returned result as the sorting reference.  
    // Hint: Use swap() if string swapping is required
    // !!IMPLEMENT SWAP() BEFORE ATTEMPTING THIS FUNCTION!! //

    // By this time you should be able to implement bubble sort with your eyes closed ;)
    int i,ok = 0;
    while(!ok){ //SICK METHOD
        ok = 1; //if no swap interact;auto out of the loop
        for(i = 0; i < size - 1; i++){  
            if(my_strcmpOrder(words[i],words[i+1]) == 1){  // given the i is larger 
                swap(&words[i], &words[i+1]);
                ok = 0; // if swapped occured , push to next
            }
        }
    }
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
            if(my_strcmpOrder(words[minIndex], words[j]) == 1) //wt*? i is the stm large num
            {
                minIndex = j;
            }                        
        }
       
        if(minIndex != i)     //LOL FIND IT 
        {
            swap(&words[i], &words[minIndex]);
        }

    }
}

