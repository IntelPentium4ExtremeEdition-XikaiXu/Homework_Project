#include "objPosQuadHashing.h"

#include <iostream>
using namespace std;

objPosQuadHashing::objPosQuadHashing()
{
    // Instantiate the objPos Hash Table of the default size TABLE_SIZE defined in the objPosHashTable abstract class
    myHashTable = new objPos[TABLE_SIZE];
    // Should also initialize tableSize field with the default size TABLE_SIZE
    tableSize = TABLE_SIZE;
}

objPosQuadHashing::objPosQuadHashing(int size)
{
    // Instantiate the objPos Hash Table of the specified size
    myHashTable = new objPos[size];
    // Should also initialize tableSize field with specified size
    tableSize = size;
}

objPosQuadHashing::~objPosQuadHashing()
{
    // delete the Hash Table
    delete[] myHashTable;
}

int objPosQuadHashing::calculateHashing(int prefix, int number) const  // hashing function
{    
    // Implementing the primary hashing function
    int Hashkey = 0;
    // Add all the decimal integer digits of the Prefix ASCII char and the Number together
    // For example, given objPos.prefix = 'A' (65) and objPos.number = 98, then...
    //  h(x) = sum of all decimal digits of prefix and number = 6 + 5 + 9 + 8 = 28
    while(prefix > 0) {
        Hashkey += prefix %10;
        prefix /= 10;
    }
    while(number > 0) {
        Hashkey += number % 10;
        number /= 10;
    }
    // return the sum as the hashing key.  
    return Hashkey;     
}

bool objPosQuadHashing::insert(const objPos &thisPos)
{
    //  1. Calculate the initial hashing key using calculateHashing() private helper function (i.e. the h1(x))
    int hashIndex = calculateHashing(thisPos.getPF(),thisPos.getNum()); //h(x)
    int finalIndex = hashIndex; //the og key
    long int probeCount = 1;

    //  2. Check symbol field to see whether the indexed slot is empty
    //      If yes, insert data, set symbol to 'v', then return true (indicating successful insertion)
    //      Otherwise, proceed to collision resolution
    if(myHashTable[hashIndex].getPF() == 0) {
        myHashTable[hashIndex] = thisPos;
        myHashTable[hashIndex].setSym('v');
        return true;
    }

    //  3. Collision resolution strategy - Quadratic Hashing
    //      h(x) = (h1(x) + i^2) mod tableSize  (i is the probing count)
    while(myHashTable[finalIndex].getSym() == 'v' && myHashTable[finalIndex].getPF() == thisPos.getPF() && !(myHashTable[finalIndex].getNum() == thisPos.getNum())) {
        if(probeCount > MAX_PROBING_COUNT) {
            return false;
        }
        finalIndex = (hashIndex + probeCount * probeCount) % tableSize;
        probeCount++; 
    }

    //  4. For every newly calculated key using quadratic probing, check for empty slot for insertion
    //      If empty slot is found, insert data, set symbol to 'v', then return true (indicating successful insertion)
    //      If element is already inserted, return false (indicating failed insertion)
    //      If probing count exceeds MAX_PROBING_COUNT defined in objPosHash.h, return false
    //          (too many probing attempts, may lead to integer overflow)
    if(myHashTable[finalIndex].getSym() == 'v') {
        return false;
    }   
    else {
        myHashTable[finalIndex] = thisPos;
        myHashTable[finalIndex].setSym('v');
        return true;
    }
}

bool objPosQuadHashing::remove(const objPos &thisPos)  // lazy delete 
{
    //  1. Calculate the initial hashing key using calculateHashing() private helper function (i.e. the h1(x))
    int hashIndex = calculateHashing(thisPos.getPF(),thisPos.getNum()); //h(x)
    int finalIndex = hashIndex; //the og key
    long int probeCount = 1;

    //  2. Check symbol field to see whether the indexed slot is empty
    //      If yes, insert data, set symbol to 'v', then return true (indicating successful insertion)
    //      Otherwise, proceed to collision resolution
    if(myHashTable[hashIndex].getPF() == 0) {
        myHashTable[hashIndex] = thisPos;
        myHashTable[hashIndex].setSym('v');
        return true;
    }

    //  3. Collision resolution strategy - Quadratic Hashing
    //      h(x) = (h1(x) + i^2) mod tableSize  (i is the probing count)
    while(myHashTable[finalIndex].getSym() == 'v' && myHashTable[finalIndex].getPF() == thisPos.getPF() && !(myHashTable[finalIndex].getNum() == thisPos.getNum())) {
        if(probeCount > MAX_PROBING_COUNT) {
            return false;
        }
        finalIndex = (hashIndex + probeCount * probeCount) % tableSize;
        probeCount++;
    }

    //  4. For every newly calculated key using quadratic probing, check for data matching (identical prefix and number)
    //      If match found, perform lazy delete by setting symbol to 0, then return true (indicating successful removal)
    //      If empty slot encountered, the probing chain reaches the end, hence return false (indicating failed removal)
    //      If probing count exceeds MAX_PROBING_COUNT defined in objPosHash.h, return false
    //          (too many probing attempts, may lead to integer overflow)

    if(!(myHashTable[finalIndex].getSym() != 'v') && !(myHashTable[finalIndex].getPF() == 0)){
        myHashTable[finalIndex].setSym('0');
        return true;
    }
    else{
        return false;
    }
}

bool objPosQuadHashing::isInTable(const objPos &thisPos) const
{
    //  1. Calculate the initial hashing key using calculateHashing() private helper function (i.e. the h1(x))
    int hashIndex = calculateHashing(thisPos.getPF(),thisPos.getNum()); //h(x)
    int finalIndex = hashIndex; //the og key
    long int probeCount = 1;

    //  2. Check symbol field to see whether the indexed slot is empty
    //      If yes, insert data, set symbol to 'v', then return true (indicating successful insertion)
    //      Otherwise, proceed to collision resolution
    if(myHashTable[hashIndex].getNum() == thisPos.getNum() && myHashTable[hashIndex].getPF() == thisPos.getPF()) {
        if(myHashTable[finalIndex].getSym() == 'v') {
            return true;
        }
        else {
            return false;
        }
    }
    //  3. Collision resolution strategy - Quadratic Hashing
    //      h(x) = (h1(x) + i^2) mod tableSize  (i is the probing count)
    while(myHashTable[finalIndex].getSym() == 'v' && myHashTable[finalIndex].getPF() == thisPos.getPF() && !(myHashTable[finalIndex].getNum() == thisPos.getNum())) {
        if(probeCount > MAX_PROBING_COUNT) {
            return false;
        }
        finalIndex = (hashIndex + probeCount*probeCount) % tableSize;
        probeCount++;
    }

    //  4. For every newly calculated key using quadratic probing, check for data matching (identical prefix and number)
     //      If matched, further chech whether symbol != 0 (data not deleted yet)
    //          If yes, return true (indicating successfully found)
    //          Otherwise, return false (indicating failed to find)
    //      If probing count exceeds MAX_PROBING_COUNT defined in objPosHash.h, return false
    //          (too many probing attempts, may lead to integer overflow)

    if(!(myHashTable[finalIndex].getPF() == 0) && myHashTable[finalIndex].getSym() == 'v') {
        return true;
    }   
    else {
        return false;
    }
}

double objPosQuadHashing::getLambda() const
{
    // Calculate the Load Factor of the Hash Table
    // Check lecture code for examples
    int n = 0;
    for(int i = 0; i < tableSize; i++){
        if(myHashTable[i].getSym() == 'v') {
            n++;
        }
    }
    return ((double)n / tableSize);
}

void objPosQuadHashing::printMe() const
{
    for(int i = 0; i < tableSize; i++) {
        printf("[%d] %d %d ", i, myHashTable[i].getPF(), myHashTable[i].getNum());
        char symbol = myHashTable[i].getSym();
        if(symbol == 'v') {
        printf("v ");
        } 
        else {
            printf(" ");
        }
        printf("\n");
    }
}