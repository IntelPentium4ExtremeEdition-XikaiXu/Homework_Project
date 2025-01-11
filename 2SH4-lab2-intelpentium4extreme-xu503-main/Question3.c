#include <stdio.h>
#include <stdlib.h>
#include "Questions.h"


// this is the very first question without hints in the comments.  read the manual to develop your own algorithm

// Read Questions.h to understand the definition of Q3Struct

void efficient(const int source[], struct Q3Struct effVector[], int size)
{
    int location,mem;                 
    mem = 0;
    for (location = 0; location < size ; location++){
        if(source[location] != 0){                               //find the element which have the characteristic which is not zero.
            effVector[mem].val = source[location];
            effVector[mem].pos = location;              
            mem += 1;
        }
    }
}

void reconstruct(int source[], int m, const struct Q3Struct effVector[], int n)
{
    int location_sources,location_eff;                              // fill out the whole array with all zeros            
    for(location_sources = 0; location_sources < m; location_sources++){
        source[location_sources] = 0;
    }
    for(location_eff = 0; location_eff < n; location_eff++){        // find specific element pos to swap the zero and stored the useful data.
        source[effVector[location_eff].pos] = effVector[location_eff].val;
    }
}
