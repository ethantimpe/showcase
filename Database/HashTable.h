#pragma once
#include "Slot.h"
#include "Record.h"
#include <string>

#define MAXHASH 20

class HashTable
{
    public:
        //Function: Default constructor for HashTable
        //Inputs: None
        //Returns: None
        HashTable();

        //Function: Attempts to insert specified key/index pair while counting collisions
        //Inputs: key (int) - key to be added
        //        index (int) - index to be added
        //        collisions (int&) - number of collisions while adding
        //Returns: Returns true if successfully added, otherwise returns false
        bool insert(int key, int index, int& collisions);

        //Function: Attempts to remove specified key
        //Inputs: key (int) - key to be removed
        //Returns: Returns true if key is successfully removed, otherwise returns false
        bool remove(int key);

        //Function: Searches for specified key
        //Inputs: key (int) - key to search for
        //        index (int&) - reference of index stored with key
        //Returns: True if key is present, otherwise returns false
        bool find(int key, int& index);

        //Function: Replaces index of specified key with new index
        //Inputs: key (int) - key to search for
        //        newIndex (int) - key that index will be replaced with
        //Returns: True if key is present, otherwise returns false
        bool replaceIndex(int key, int newIndex);

        //Function: Returns a copy of the Slot at a given index
        //Inputs: index (int) - index of specified Slot
        //Returns: Copy of Slot at given index
        Slot getSlot(int index);

        //Function: Returns the current load factor
        //Inputs: None
        //Returns: None
        float alpha();

        //Function: Prints contents of HashTable to specified ostream
        //Inputs: os (ostream&) - ostream to print to
        //        me (HashTable&) - hashtable to be printed
        //Returns: Inputted ostream
        friend ostream& operator<<(ostream& os, const HashTable& me);
    private:
        //Member data
        int slotsFilled;
        Slot slots[MAXHASH];
        int probeKeys[MAXHASH];
};