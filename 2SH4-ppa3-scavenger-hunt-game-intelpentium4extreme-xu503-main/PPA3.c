//===================library_part====/
#include <stdio.h>
#include "MacUILib.h"
#include "myStringLib.h"   // This is your first custom C library
#include "stdlib.h"// [TODO] Import the required library for rand() and srand()
#include "time.h"// [TODO] Import the required library for accessing the current time - for seeding random number generation
//========Library_end================/
//=====Init globle variable==========/
int x,y,frame,move_count,temp,i,j;   //basic init grub data from ppa2
enum FSMMode {UP = 1, LEFT, DOWN, RIGHT, Stop} myFSMMode; 
char input;
// GLOBAL VARIABLES
// ================================
char *main_string = "Mcmaster-ECE"; //used for target strig 
char *strange = NULL; // requirement 

int exitFlag; // Program Exiting Flag
int win; // returning the winnin information
int col; // using for collision detection
struct objPos{              // give the basic information of the object discription.
    int x_pos;
    int y_pos;
    char * direction;
}myobjPos;
struct enemyobjPos{
    int x_pos ;
    int y_pos ;
    char * letter;
};
struct enemyobjPos *egg_cart = NULL; 
//set up a pointer for five structure
// [TODO] Declare Global Pointers as seen needed / instructed in the manual.
// ==============FUNCTION PROTOTYPES==================
// Declare function prototypes here, so that we can organize the function implementation after the main function for code readability.
void Initialize(void);
void GetInput(void);
void RunLogic(void);
void DrawScreen(void);
void LoopDelay(void);
void CleanUp(void);
// [TODO] In PPA3, you will need to implement this function to generate random items on the game board
//        to set the stage for the Scavenger Hunter game.
// list[]       The pointer to the Item Bin
// listSize     The size of the Item Bin (5 by default)
// playerPos    The pointer to the Player Object, read only.
// xRange       The maximum range for x-coordinate generation (probably the x-dimension of the gameboard?)
// yRange       The maximum range for y-coordinate generation (probably the y-dimension of the gameboard?)
// str          The pointer to the start of the Goal String (to choose the random characters from)
void GenerateItems(struct enemyobjPos list[], const int listSize, const struct objPos *playerPos, const int xRange, const int yRange, const char* str);
// big funtion in order to creat 5 differnt oject which have different location and so on.
// MAIN PROGRAM
// ===============================
int main(void)
{
    Initialize(); //supposr where the obj information should be generated and stored 
    while(!exitFlag)  
    {
        GetInput();
        RunLogic();
        DrawScreen();
        LoopDelay();
        if(win) break;
    }
    CleanUp();
}
// INITIALIZATION ROUTINE
// ===============================
void Initialize(void)
{
    MacUILib_init();
    MacUILib_clearScreen();
    // [COPY AND PASTE FROM PPA2] Copy your initialization routine from PPA2 and paste them below
    exitFlag = 0;  // not exiting
    myFSMMode = Stop;
    input = 0;
    myobjPos.x_pos = 10,myobjPos.y_pos = 5;
    win = 0;
    strange = (char*)malloc(13*sizeof(char*));  // strange need to free
    for(i = 0; i < 12 ; i++){
        strange[i] = '?';
    }
    strange[12] = NULL;
    // [TODO] Initialize any global variables as required.
    // [TODO] Allocated heap memory for on-demand variables as required.  Initialize them as required.
    egg_cart = (struct enemyeobjPos*)calloc(5,sizeof(struct enemyobjPos));
    // give the extra space
    // [TODO] Seed the random integer generation function with current time.
    srand(time(NULL));
    // [TODO] Generate the initial random items on the game board at the start of the game.
    GenerateItems(egg_cart, 5 , &myobjPos, 19, 9, main_string);
}

// INPUT COLLECTION ROUTINE
// ===============================
void GetInput(void)
{
    // Asynchronous Input - non blocking character read-in
    if(MacUILib_hasChar()){
        input = MacUILib_getChar();
    }
    // [COPY AND PASTE FROM PPA2] Copy your input collection routine from PPA2 and paste them below
    // [TODO] Though optional for PPA3, you may insert any additional logic for input processing.  
}
// MAIN LOGIC ROUTINE
// ===============================
void RunLogic(void)
{
    if(input == ' '){
        exitFlag = 1;
    }
    if(input == 'h'){
        win = 1; // just for testing the win function
    }
    //WASD to the corresponding change in player object movement direction
    if(input != 0){
        if((input == 'W' || input == 'w') && myFSMMode != 3){
            myFSMMode = UP;
        }        
        else if((input == 'A' || input == 'a') && myFSMMode != 4){
            myFSMMode = LEFT;
        }
        else if((input == 'S' || input == 's') && myFSMMode != 1){
            myFSMMode = DOWN;
        }
        else if((input == 'D' || input == 'd') && myFSMMode != 2){
            myFSMMode = RIGHT;
        }
        else if(input == 'T' || input == 't'){
            myFSMMode = Stop;
        }
    }// the control table using FSM
    switch(myFSMMode){
        case LEFT:
            myobjPos.x_pos -= 1;
            if(myobjPos.x_pos == 0){
                myobjPos.x_pos = 18;
            }
            myobjPos.direction = "Left";
            move_count++;
            break;
        case RIGHT:
            myobjPos.x_pos += 1; 
            if(myobjPos.x_pos == 19){
                myobjPos.x_pos = 1;
            }
            myobjPos.direction = "Right";
            move_count++;
            break;
        case DOWN:
            myobjPos.y_pos += 1;
            if(myobjPos.y_pos == 9){
                myobjPos.y_pos = 1;
            }
            myobjPos.direction = "Down";
            move_count++;
            break;
        case UP:
            myobjPos.y_pos -=1;
            if(myobjPos.y_pos == 0){
                myobjPos.y_pos = 8;
            }
            myobjPos.direction = "Up";
            move_count++;
            break;
        case Stop:
            myobjPos.direction = "Stop";
            break;
    }// The operation of the myobject
    for(i = 0; i < 5; i++){
        if(myobjPos.x_pos == egg_cart[i].x_pos && myobjPos.y_pos == egg_cart[i].y_pos){
            for(j = 0; j < 13;j++){
                if(main_string[j] == egg_cart[i].letter){
                    strange[j] = main_string[j];
                }
            }
            if(my_strcmp(main_string,strange)){
                win = 1;
                exitFlag = 1;
                break;
            }
            else{
                GenerateItems(egg_cart, 5 , &myobjPos, 19, 9, main_string);
            }
            break;
        }
    }//partial collisoon detection 
    // [TODO]   Implement the Object Collision logic here
    //
    //      Simple Collision Algorithm
    //      1. Go through all items on board and check their (x,y) against the player object x and y.
    //      2. If a match is found, use the ASCII symbol of the collided character, and 
    //         find all the occurrences of this ASCII symbol in the Goal String
    //      3. For every occurrence, reveal its ASCII character at the corresponding location in the
    //         Collected String
    //      4. Then, determine whether the game winning condition is met.
    // [TODO]   Implement Game Winning Check logic here
    //
    //      Game Winning Check Algorithm
    //      1. Check if the contents of the Collected String exactly matches that of the Goal String.
    //         YOU MUST USE YOUR OWN my_strcmp() function from Lab 3.
    //      2. If matched, end the game.
    //      3. Otherwise, discard the current items on the game board, and 
    //         generate a new set of random items on the board.  Game continues.
    frame += 1; // used for detecting the main logic part is running properly.
}

// DRAW ROUTINE
// ===============================
void DrawScreen(void)
{
    MacUILib_clearScreen();
    // [COPY AND PASTE FROM PPA2] Copy your draw logic routine from PPA2 and paste them below
    for (y = 0; y < 10; y++){
        for (x = 0; x < 20 ; x++){
            if(y == 0 || y == 9){
                MacUILib_printf("#");
            }
            else if((y != 0 && y != 9)&&(x == 0 || x == 19)){
                MacUILib_printf("#");
            }
            else if(x == myobjPos.x_pos && y == myobjPos.y_pos){
                MacUILib_printf("@");
            }
            else if(x == egg_cart[0].x_pos && y == egg_cart[0].y_pos){
                MacUILib_printf("%c",egg_cart[0].letter);
            }
            else if(x == egg_cart[1].x_pos && y == egg_cart[1].y_pos){
                MacUILib_printf("%c",egg_cart[1].letter);
            }
            else if(x == egg_cart[2].x_pos && y == egg_cart[2].y_pos){
                MacUILib_printf("%c",egg_cart[2].letter);
            }
            else if(x == egg_cart[3].x_pos && y == egg_cart[3].y_pos){
                MacUILib_printf("%c",egg_cart[3].letter);
            }
            else if(x == egg_cart[4].x_pos && y == egg_cart[4].y_pos){
                MacUILib_printf("%c",egg_cart[4].letter);
            }          
            else{
                MacUILib_printf(" ");
            }

        }
        MacUILib_printf("\n");
    }

    //dash board print structure 
    MacUILib_printf("Mystery String:");
    for(i = 0; i < 13; i++){
        MacUILib_printf("%c",strange[i]); // select to using the string operation;
    }
    MacUILib_printf("\n");
    MacUILib_printf("current obj location is %d,%d\n",myobjPos.x_pos,myobjPos.y_pos);
    MacUILib_printf("current player direction is %s\n",myobjPos.direction);
    MacUILib_printf("total frames are %d\n", frame);       
    MacUILib_printf("total moves are %d\n", move_count);    
}

// DELAY ROUTINE
// ===============================
void LoopDelay(void){
    MacUILib_Delay(100000); // 0.1s delay
}
// TEAR-DOWN ROUTINE
// ===============================
void CleanUp(void)
{   
    free(strange);
    free(egg_cart);
    // [TODO]   To prevent memory leak, free() any allocated heap memory here
    //          Based on the PPA3 requirements, you need to at least deallocate one heap variable here.
    // Insert any additional end-game actions here.
    if(win){
        printf("hahaha you win the game !");
    }
    MacUILib_uninit();
}

// The Item Generation Routine
////////////////////////////////////
void GenerateItems(struct enemyobjPos list[], const int listSize, const struct objPos *playerPos, const int xRange, const int yRange, const char* str)
{
    // This is possibly one of the most conceptually challenging function in all PPAs
    // Once you've mastered this one, you are ready to take on the 2SH4 course project!
    int x,y,i,z,ok,j,W,u,v;
    ok = 0;
    int ep = 0;
    int xp = 0;
    // init we have no random nums.
    // Random Non-Repeating Item Generation Algorithm
    ////////////////////////////////////////////////////
    // Use random number generator function, rand(), to generate a random x-y coordinate and a random choice of character from the Goal String as the ASCII character symbol.
    //      The x and y coordinate range should fall within the xRange and yRange limits, which should be the x- and y-dimension of the board size.
    // This will then be a candidate of the randomly generated Item to be placed on the game board.

    for (i = 0; i < listSize; i++){
        while(!ep){
            x = (rand() % (xRange - 1)) + 1; // random 1-19
            y = (rand() % (yRange - 1)) + 1; // random 1-9
            z = (rand()%(my_strlen(str)-1)); // random 0-11
            for(j = 0; j < listSize; j++){
                if(x == list[j].x_pos && y == list[j].y_pos){
                    break;
                }
                else if(x == playerPos->x_pos && y == playerPos->y_pos){
                    break;
                }
                else if(str[z] == list[j].letter){
                    break;
                }
            } //if x y z have repeated, using while loop to regenerated a new set of x y z;
            if(j == 5){
                ep = 1;
            }
        }
        // add the x y z value after the selection.            
        list[i].x_pos = x;
        list[i].y_pos = y;
        list[i].letter = str[z];
        ep = 0; // reset the while loop
    } // GENERATED INIT ARRAY
    for(u = 2; u < listSize; u++){
        while(!xp){
            W = (rand()% 93) + 33; // random 33-126 --> for bonus
            for(v = 0; v < listSize; v++){ 
                if(W == list[v].letter){
                    break;
                }
            } //if w have repeated, using while loop to regenerated a new set of x y z;
            if(v == 5){
                xp = 1;
            }// 5 of them were not repeated 
        }
        // add the W value after the selection.            
        list[u].letter = W;
        xp = 0; // reset the while loop
    }  
    // In order to make sure this candidate is validated, it needs to meet both criteria below:
    //  1. Its coordinate and symbol has not been previously generated (no repeating item)
    //  2. Its coordinate does not overlap the Player's position
    // Thus, for every generated item candidate, check whether its x-y coordinate and symbol has previously generated.  
    //  Also, check if it overlaps the player position
    //      If yes, discard this candidate and regenerate a new one
    //      If no, this candidate is validated.  Add it to the input list[]
    // There are many efficient ways to do this question
    //  We will take a deep dive into some methods in 2SI.
}
