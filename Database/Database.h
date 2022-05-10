#pragma once
#include "HashTable.h"
#include <vector>

class Database
{
    public:
        //Function: Default constructor for Database
        //Inputs: None
        //Returns: None
        Database();
        
        //Function: Inserts a new record into the database
        //Inputs: newRecord (Record&) - record to be inserted
        //        collisions (int) - number of collisions when attempting to insert
        //Returns: Returns true if successfully inserted, other returns false
        bool insert(const Record& newRecord, int& collisions);

        //Function: Removes a record with the given key if it exists in the database
        //Inputs: key (int) - key to be searched for
        //Returns: Returns true if successfully removed, otherwise false
        bool remove(int key);

        //Function: Attempts to find specified uid within the database
        //Inputs: uid (int) - id to be searched for
        //        foundRecord (Record&) - a copy of the record found
        //Returns: Returns true if record with given uid is found in the database
        bool find(int uid, Record& foundRecord);

        //Function: Returns the current load factor of the database's hash table
        //Inputs: None
        //Returns: Returns the current load factor (float)
        float alpha();

        //Function: Prints all the information in the database
        //Inputs: os (ostream&) - output stream to be printed to
        //        db (Database&) - database to be printed
        //Returns: Returns the ostream passed in
        friend ostream& operator<<(ostream& os, Database& db);
    private:
        //Member data
        HashTable indexTable;
        vector<Record> recordStore;
};