#include "objPosDoubleHashing.h"
#include "MacUILib.h"

#include <iostream>
using namespace std;

objPosDoubleHashing::objPosDoubleHashing()
{
    myHashTable = new objPos[TABLE_SIZE];
    // Instantiate the objPos Hash Table of the default size TABLE_SIZE defined in the objPosHashTable abstract class
    tableSize = TABLE_SIZE;
    // Should also initialize tableSize field with the default size TABLE_SIZE
}

objPosDoubleHashing::objPosDoubleHashing(int size)
{
    // Instantiate the objPos Hash Table of the specified size
    myHashTable = new objPos[size];
    // Should also initialize tableSize field with specified size
    tableSize = size;
}

objPosDoubleHashing::~objPosDoubleHashing()
{
    // delete the Hash Table
    delete[] myHashTable;
}

int objPosDoubleHashing::calculateHashing(int prefix, int number) const  // hashing function
{    
    // Implementing the primary hashing function
    int Hashkey1 = 0;
    // Add all the decimal integer digits of the Prefix ASCII char and the Number together
    // For example, given objPos.prefix = 'A' (65) and objPos.number = 98, then...
    //  h(x) = sum of all decimal digits of prefix and number = 6 + 5 + 9 + 8 = 28
    while(prefix > 0){
        Hashkey1 += prefix %10;
        prefix /= 10;
    }
    while(number > 0){
        Hashkey1 += number % 10;
        number /= 10;
    }
    // return the sum as the hashing key.  
    return Hashkey1;     
}

int objPosDoubleHashing::calculateSecondaryHashing(int input) const
{
    int Hashkey2 = 0;
    while(input > 0){
        Hashkey2 += input % 10;
        input /= 10;
    }
    return (5 - (Hashkey2 % 5));
}

bool objPosDoubleHashing::insert(const objPos &thisPos)
{
    // Algorithm similar to the one discussed in class
    //  1. Calculate the initial hashing key using calculateHashing() private helper function (i.e. the h1(x))
    int hashIndex = calculateHashing(thisPos.getPF(),thisPos.getNum());
    int finalIndex = hashIndex;
    int probeCount = 1;

    //  2. Check symbol field to see whether the indexed slot is empty
    //      If yes, insert data, set symbol to 'v', then return true (indicating successful insertion)
    //      Otherwise, proceed to collision resolution
    if(myHashTable[finalIndex].getPF() == 0) {
        myHashTable[finalIndex] = thisPos;
        myHashTable[finalIndex].setSym('v');
        return true;
    }

    //  3. Collision resolution strategy - Double Probing
    //      h(x) = (h1(x) + i*h2(x)) mod tableSize  (i is the probing count)
    //      where h2(x) = 5 - (sum of all digits of h1(x)) mod 5)
    while(myHashTable[finalIndex].getSym() == 'v' && !(myHashTable[finalIndex].getNum() == thisPos.getNum()) && myHashTable[finalIndex].getPF() == thisPos.getPF()) {
        if(probeCount > MAX_PROBING_COUNT) {
            return false;
        }
        finalIndex = (hashIndex + probeCount*calculateSecondaryHashing(hashIndex)) % tableSize;
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

bool objPosDoubleHashing::remove(const objPos &thisPos)
{
    // Algorithm similar to the one discussed in class
    //  1. Calculate the initial hashing key using calculateHashing() private helper function (i.e. the h1(x))
    int hashIndex = calculateHashing(thisPos.getPF(),thisPos.getNum());
    int finalIndex = hashIndex;
    int probeCount = 1;

    //  2. Check symbol field to see whether the indexed slot is empty
    //      If yes, insert data, set symbol to 'v', then return true (indicating successful insertion)
    //      Otherwise, proceed to collision resolution
    if(myHashTable[finalIndex].getPF() == 0) {
        myHashTable[finalIndex] = thisPos;
        myHashTable[finalIndex].setSym('v');
        return true;
    }

    //  3. Collision resolution strategy - Double Probing
    //      h(x) = (h1(x) + i*h2(x)) mod tableSize  (i is the probing count)
    //      where h2(x) = 5 - (sum of all digits of h1(x)) mod 5)
    while(myHashTable[finalIndex].getSym() == 'v' && (!(myHashTable[finalIndex].getNum() == thisPos.getNum()) && myHashTable[finalIndex].getPF() == thisPos.getPF())) {
        if(probeCount > MAX_PROBING_COUNT) {
            return false;
        }
        finalIndex = (hashIndex + probeCount*calculateSecondaryHashing(hashIndex)) % tableSize;
        probeCount++;
    }
    //  4. For every newly calculated key using quadratic probing, check for data matching (identical prefix and number)
    //      If match found, perform lazy delete by setting symbol to 0, then return true (indicating successful removal)
    //      If empty slot encountered, the probing chain reaches the end, hence return false (indicating failed removal)
    //      If probing count exceeds MAX_PROBING_COUNT defined in objPosHash.h, return false
    //          (too many probing attempts, may lead to integer overflow)

    if(myHashTable[finalIndex].getPF() == 0) {
        return false;
    }
    else {
        if(myHashTable[finalIndex].getSym() != 'v') {
            return false;
        } 
        else {
            myHashTable[finalIndex].setSym('0');
            return true;
        }
    }
}

bool objPosDoubleHashing::isInTable(const objPos &thisPos) const
{
    // Algorithm similar to the one discussed in class
    //  1. Calculate the initial hashing key using calculateHashing() private helper function (i.e. the h1(x))
    int hashIndex = calculateHashing(thisPos.getPF(),thisPos.getNum());
    int finalIndex = hashIndex;
    int probeCount = 1;

    //  2. Check symbol field to see whether the indexed slot is empty
    //      If yes, insert data, set symbol to 'v', then return true (indicating successful insertion)
    //      Otherwise, proceed to collision resolution
    if(myHashTable[finalIndex].getNum() == thisPos.getNum() && myHashTable[finalIndex].getPF() == thisPos.getPF()) {
        if(myHashTable[finalIndex].getSym() == 'v') {
            return true;
        }
        else {
            return false;
        }
    }

    //  3. Collision resolution strategy - Double Probing
    //      h(x) = (h1(x) + i*h2(x)) mod tableSize  (i is the probing count)
    //      where h2(x) = 5 - (sum of all digits of h1(x)) mod 5)
    while(myHashTable[finalIndex].getSym() == 'v' && (!(myHashTable[finalIndex].getNum() == thisPos.getNum()) && myHashTable[finalIndex].getPF() == thisPos.getPF())) {
        if(probeCount > MAX_PROBING_COUNT) {
            return false;
        }
        finalIndex = (hashIndex + probeCount*calculateSecondaryHashing(hashIndex)) % tableSize;
        probeCount++;
    }
    
    //  4. For every newly calculated key using quadratic probing, check for data matching (identical prefix and number)
    //      If match found, perform lazy delete by setting symbol to 0, then return true (indicating successful removal)
    //      If empty slot encountered, the probing chain reaches the end, hence return false (indicating failed removal)
    //      If probing count exceeds MAX_PROBING_COUNT defined in objPosHash.h, return false
    //          (too many probing attempts, may lead to integer overflow)
    if(myHashTable[finalIndex].getPF() == 0 || myHashTable[finalIndex].getSym() != 'v') {
        return false;
    }
    else {
        return true;
    }
}

double objPosDoubleHashing::getLambda() const
{
    // Calculate the Load Factor of the Hash Table
    // Check lecture code for examples
    int n = 0;
    for(int i = 0; i < tableSize; i++) {
        if(myHashTable[i].getSym() == 'v') {
            n++;
        }  
    }
    return ((double)n / tableSize);
}

void objPosDoubleHashing::printMe() const
{
    MacUILib_printf("[ ");
    for(int i = 0; i < TABLE_SIZE; i++)
    {
        if(myHashTable[i].getSym() != 0)
            MacUILib_printf("%c%d ", myHashTable[i].getPF(), myHashTable[i].getNum());     
    }
    MacUILib_printf("] L=%.2f", getLambda());
}