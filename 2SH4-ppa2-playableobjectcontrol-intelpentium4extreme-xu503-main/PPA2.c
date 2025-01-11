#include <stdio.h>
#include "MacUILib.h"
// PPA2 GOAL: 
//       Construct the game backbone where the player can control an object 
//       to move freely in the game board area with border wraparound behaviour.
// Watch Briefing Video and Read Lab Manual before starting on the activity!
// PREPROCESSOR CONSTANTS DEFINITION HERE
// GLOBAL VARIABLE DEFINITION HERE
int x,y,total_frames;   //basic init grub data
//--------------------------------------------------------//
int exitFlag; // Program Exiting Flag - old stuff
// For storing the user input - from PPA1
char input; // init the input from the keyboard
enum FSMMode {UP = 1, LEFT, DOWN, RIGHT, Stop} myFSMMode;   // init all the possible probability of the object movement.
enum Speed {Lowest = 1, Low , Medium , High , Highest} myspeed; // possible speed of all the element.
// [TODO] : Define objPos structure here as described in the lab document
//--------------------------------------------------------//
struct objPos{                 // give the basic information of the object discription.
    int x_pos;
    int y_pos;
    char * direction;
}myobjPos;
struct clockspeed{             // give the basic discription of the speed of the game.
    int gamming_speed;
    char * speed_name;
}myclockspeed;
// [TODO] : Define the Direction enumeration here as described in the lab document
//          This will be the key ingredient to construct a simple Finite State Machine
//          For our console game backbone.
// FUNCTION PROTOTYPING DEFINITION HERE
//--------------------------------------------------------//
void Initialize(void);
void GetInput(void);
void RunLogic(void);
void DrawScreen(void);
void LoopDelay(void);
void CleanUp(void);
// You may insert additional helper function prototypes below.
// As a good practice, always insert prototype before main() and implementation after main()
// For ease of code management.
//--------------------------------------------------------//
// MAIN PROGRAM LOOP
// This part should be intuitive by now.
// DO NOT TOUCH
int main(void)
{   
    Initialize(); 
    while(!exitFlag)  
    {
        GetInput();
        RunLogic();
        DrawScreen();
        LoopDelay();
    }
    CleanUp();
}
// INITIALIZATION ROUTINE
/////////////////////////////////////////
void Initialize(void)
{
    MacUILib_clearScreen();
    MacUILib_init();
    exitFlag = 0;  // not exiting
    myFSMMode = Stop;
    input = 0;
    myobjPos.x_pos = 10,myobjPos.y_pos = 5;
    myspeed = Lowest;
    total_frames = 0;
    // [TODO] : Initialize more variables here as seen needed.
    //          PARTICULARLY for the structs!!
}
// INPUT PROCESSING ROUTINE
/////////////////////////////////////////
void GetInput(void)
{
    // [TODO] : Implement Asynchronous Input - non blocking character read-in    
    if(MacUILib_hasChar()){
        input = MacUILib_getChar();
    }
}
// PROGRAM LOGIC ROUTINE
/////////////////////////////////////////
void RunLogic(void)
{
    MacUILib_clearScreen();
    if(input == ' '){
        exitFlag = 1;
    }
    // [TODO] : First, process the input by mapping
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
        else if(input == '1'){
            myspeed = Lowest;
        }
        else if(input == '2'){
            myspeed = Low;
        }
        else if(input == '3'){
            myspeed = Medium;
        }
        else if(input == '4'){
            myspeed = High;
        }
        else if(input == '5'){
            myspeed = Highest;
        }
    }
    switch(myFSMMode){
        case LEFT:
            myobjPos.x_pos -= 1;
            if(myobjPos.x_pos == 0){
                myobjPos.x_pos = 18;
            }
            myobjPos.direction = "Left";
            break;
        case RIGHT:
            myobjPos.x_pos += 1; 
            if(myobjPos.x_pos == 19){
                myobjPos.x_pos = 1;
            }
            myobjPos.direction = "Right";
            break;
        case DOWN:
            myobjPos.y_pos += 1;
            if(myobjPos.y_pos == 9){
                myobjPos.y_pos = 1;
            }
            myobjPos.direction = "Down";
            break;
        case UP:
            myobjPos.y_pos -=1;
            if(myobjPos.y_pos == 0){
                myobjPos.y_pos = 8;
            }
            myobjPos.direction = "Up";
            break;
        case Stop:
            myobjPos.direction = "Stop";
            break;
    }
    switch(myspeed){
        case Lowest:
            myclockspeed.gamming_speed = 400000;
            myclockspeed.speed_name = "SLOW_AS_A_PUPPY_0.4_sec";
            break;
        case Low:
            myclockspeed.gamming_speed = 300000;
            myclockspeed.speed_name = "slow_0.3_sec";
            break;
        case Medium:
            myclockspeed.gamming_speed = 200000;
            myclockspeed.speed_name = "medium_0.2_sec";
            break;
        case High:
            myclockspeed.gamming_speed = 100000;
            myclockspeed.speed_name = "fast_enough_0.1_sec";
            break;
        case Highest:
            myclockspeed.gamming_speed = 50000;
            myclockspeed.speed_name = "BACK_TO_THE_FUTURE!!!_0.05sec";
            break;

    }
    total_frames += 1;
    input = 0;
    // [TODO] : Next, you need to update the player location by 1 unit 
    //          in the direction stored in the program
    // [TODO] : Heed the border wraparound!!!
}
// SCREEN DRAWING ROUTINE
/////////////////////////////////////////
void DrawScreen(void)
{
    for (y = 0; y < 10; y++){
        for (x = 0; x < 20 ; x++){
            if(y == 0 || y == 9){
                MacUILib_printf("#");
            }
            else if((y != 0 && y != 9)&&(x == 0 || x == 19)){
                MacUILib_printf("#");
            }
            else if( x == myobjPos.x_pos && y == myobjPos.y_pos){
                MacUILib_printf("&");
            }
            else{
                MacUILib_printf(" ");
            }
        }
        MacUILib_printf("\n");
    }
    MacUILib_printf("current obj location is %d,%d\n",myobjPos.x_pos,myobjPos.y_pos);
    MacUILib_printf("current gamming speed is %s\n",myclockspeed.speed_name);
    MacUILib_printf("current player direction is %s\n",myobjPos.direction);
    MacUILib_printf("total frames are %d\n", total_frames);
    // [TODO] : Implement the latest drawing logic as described in the lab manual
    //
    //  1. clear the current screen contents

    //  2. Iterate through each character location on the game board
    //     using the nested for-loop row-scanning setup.

    //  3. For every visited character location on the game board
    //          If on border on the game board, print a special character
    //          If at the player object position, print the player symbol
    //          Otherwise, print the space character
    //     Think about how you can format the screen contents to achieve the
    //     same layout as presented in the lab manual

    //  4. Print any debugging messages as seen needed below the game board.
    //     As discussed in class, leave these debugging messages in the program
    //     throughout your dev process, and only remove them when you are ready to release
    //     your code. 
}
// PROGRAM LOOOP DELAYER ROUTINE
/////////////////////////////////////////
void LoopDelay(void)
{
    // Change the delaying constant to vary the movement speed.
    MacUILib_Delay(myclockspeed.gamming_speed);    
}
// PROGRAM CLEANUP ROUTINE
/////////////////////////////////////////
// Recall from PPA1 - this is run only once at the end of the program
// for garbage collection and exit messages.
void CleanUp(void)
{
    MacUILib_uninit();
}