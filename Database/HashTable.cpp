#include "HashTable.h"
#include "hashfunction.h"

using namespace std;

//Function: Default constructor for HashTable
//Inputs: None
//Returns: None
HashTable::HashTable()
{
    //HashTable starts with 0 slots filled
    slotsFilled = 0;

    //Initalize slots as empty and probe keys as their respective integers
    for (size_t i = 0; i < MAXHASH; i++)
    {
        slots[i] = Slot();
        probeKeys[i] = i;
    }

    //Shuffle probe keys for pseudo random probing
    for (size_t i = 1; i < MAXHASH; i++)
    {
        //For each probe key, pick a random probe key to swap with
        int temp, rand;
        rand = std::rand() % (MAXHASH - 1) + 1;

        temp = probeKeys[i];
        probeKeys[i] = probeKeys[rand];
        probeKeys[rand] = temp;
    }
}


//Function: Attempts to insert specified key/index pair while counting collisions
//Inputs: key (int) - key to be added
//        index (int) - index to be added
//        collisions (int&) - number of collisions while adding
//Returns: Returns true if successfully added, otherwise returns false
bool HashTable::insert(int key, int index, int& collisions)
{
    unsigned int hash = jsHash(key) % MAXHASH;
    Slot* currentSlot;
    collisions = 0;

    //Return false if key is already in table
    if (find(key, index))
    {
        return false;
    }

    //Use pseudo random probing to fill slots
    for (size_t i = 0; i < MAXHASH; i++)
    {
        currentSlot = &slots[(hash + probeKeys[i]) % MAXHASH];

        //Fill slot if not normal
        if (!currentSlot->isNormal())
        {
            slots[hash + probeKeys[i]] = Slot(key, index);
            slotsFilled++;
            return true;
        }
        else
            collisions++;
    }

    return false;
}


//Function: Attempts to remove specified key
//Inputs: key (int) - key to be removed
//Returns: Returns true if key is successfully removed, otherwise returns false
bool HashTable::remove(int key)
{
    unsigned int hash = jsHash(key) % MAXHASH;
    Slot* currentSlot;

    //Use pseudo random keys to probe slots
    for (size_t i = 0; i < MAXHASH; i++)
    {
        currentSlot = &slots[hash + probeKeys[i]];

        //If slot has been empty since start, return false
        if (currentSlot->isEmptySinceStart())
        {
            return false;
        }
        //If slot is filled and the keys match, return true
        else if (currentSlot->isNormal() && currentSlot->getKey() == key)
        {
            currentSlot->kill();
            slotsFilled--;
            return true;
        }
    }

    return false;
}


//Function: Searches for specified key
//Inputs: key (int) - key to search for
//        index (int&) - reference of index stored with key
//Returns: True if key is present, otherwise returns false
bool HashTable::find(int key, int& index)
{
    unsigned int hash = jsHash(key) % MAXHASH;
    Slot* currentSlot;

    //Use pseudo random keys to probe slots
    for (size_t i = 0; i < MAXHASH; i++)
    {
        currentSlot = &slots[hash + probeKeys[i]];

        //If slot has been empty since start, return false
        if (currentSlot->isEmptySinceStart())
        {
            return false;
        }
        //If slot is filled and the keys match, return true
        else if (currentSlot->isNormal() && currentSlot->getKey() == key)
        {
            index = currentSlot->getIndex();
            return true;
        }
    }

    return false;
}


//Function: Replaces index of specified key with new index
//Inputs: key (int) - key to search for
//        newIndex (int) - key that index will be replaced with
//Returns: True if key is present, otherwise returns false
bool HashTable::replaceIndex(int key, int newIndex)
{
    int collisions;

    //If key is removed, insert new key
    if (remove(key))
    {
        insert(key, newIndex, collisions);
        return true;
    }
    
    return false;
}

//Function: Returns a copy of the Slot at a given index
//Inputs: index (int) - index of specified Slot
//Returns: Copy of Slot at given index
Slot HashTable::getSlot(int index)
{
    return slots[index];
}

//Function: Returns the current load factor
//Inputs: None
//Returns: None
float HashTable::alpha()
{
    float alpha;

    alpha = (float) slotsFilled / (float) MAXHASH;

    return alpha;
}


//Function: Prints contents of HashTable to specified ostream
//Inputs: os (ostream&) - ostream to print to
//        me (HashTable&) - hashtable to be printed
//Returns: Inputted ostream
ostream& operator<<(ostream& os, const HashTable& me)
{
    cout << "HashTable contents:" << endl;

    //For each slot, print if normal
    for (size_t i = 0; i < MAXHASH; i++)
    {
        if (me.slots[i].isNormal())
        {
            os << "HashTable Slot " << i << ": " << me.slots[i] << endl;
        }
    }
    
    //Spacing
    os << endl;

    return os;
}