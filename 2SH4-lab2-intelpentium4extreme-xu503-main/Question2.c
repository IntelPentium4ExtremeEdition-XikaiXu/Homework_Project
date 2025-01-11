#include <stdio.h>
#include <stdlib.h>

#include "Questions.h"

void diag_scan(int mat [][N3], int arr [])
{
    // This is the first programming (scripting) question without any initial setup as hints.
    // This is also the first question requiring you to come up with an algorithm on paper 
    // with mathematical analysis before implementing the code.
    // High Level Hint:
    //  Assume a 3x3 square matrix, look at the SUM of the row and column indices of each element.
    //  You should be able to see a numerical pattern after doing so.
    int cycle,x,y,location,calc_line;
    cycle = 0;x = 0; y = 0; location = 0; calc_line = 0;
    while(calc_line <= N3*2 - 1){   // ready to passing through the crossline of the angle trail
        y = cycle;                  // y-ccordinate of the mat is tje mount of read through the program
        while(x <= cycle){          
            arr [location] = mat [x][y];  
            x++;                  // x + y = cycle, find the elemrnt cross the right up to left down
            y--;                   // X first move to right, then y reduce to move downward
            location++;
        }
        calc_line++;               // ready for next cycle
        if(calc_line < N3 ){        // if the cycle less than the cross exp: mat[][3] =>                
                                                                                        //a  1  b  2   c  3
            cycle++;                                                                    //E  2  F  3   G  2
            x = 0;                                                                      //h  3  i  2   j  1
        }
        else{
            x = calc_line - N3 + 1;   // from the 3 - 1 start find the element, inverse dirction.
        }
    }
}
