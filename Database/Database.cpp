#include "Database.h"

//Function: Default constructor for Database
//Inputs: None
//Returns: None
Database::Database()
{
    recordStore = vector<Record>();
    indexTable = HashTable();
}


//Function: Inserts a new record into the database
//Inputs: newRecord (Record&) - record to be inserted
//        collisions (int) - number of collisions when attempting to insert
//Returns: Returns true if successfully inserted, other returns false
bool Database::insert(const Record& newRecord, int& collisions)
{
    int index;
    int uid = newRecord.getUID();

    //Check to make sure the UID is not already in the HashTable.
    if (indexTable.find(uid, index))
    {
        return false;
    }
    //If not, insert the Record into the recordStore, and
    //Insert the UID and the slot the Record occupies in the recordStore into the HashTable.
    else
    {
        index = recordStore.size();
        recordStore.push_back(newRecord);
        indexTable.insert(uid, index, collisions);
        return true;
    }
}


//Function: Removes a record with the given key if it exists in the database
//Inputs: key (int) - key to be searched for
//Returns: Returns true if successfully removed, otherwise false
bool Database::remove(int key)
{
    int index;

    //Attempt to find index of 
    if (indexTable.find(key, index))
    {
        //If the record is the last in the record store, remove from database
        if (recordStore.size() - 1 == index)
        {
            recordStore.pop_back();
            indexTable.remove(key);

            return true;
        }
        //If the record is not last in the record store, place the last record in
        //the record store in the removed record's former spot and replace index
        else
        {
            Record lastRecord = recordStore.back();
            recordStore.pop_back();
            recordStore.at(index) = lastRecord;

            indexTable.replaceIndex(lastRecord.getUID(), index);
            indexTable.remove(key);

            return true;
        }
    }

    return false;
}


//Function: Attempts to find specified uid within the database
//Inputs: uid (int) - id to be searched for
//        foundRecord (Record&) - a copy of the record found
//Returns: Returns true if record with given uid is found in the database
bool Database::find(int uid, Record& foundRecord)
{
    int index;

    if (indexTable.find(uid, index))
    {
        foundRecord = recordStore[index];
        return true;
    }

    return false;
}


//Function: Returns the current load factor of the database's hash table
//Inputs: None
//Returns: Returns the current load factor (float)
float Database::alpha()
{
    return indexTable.alpha();
}


//Function: Prints all the information in the database
//Inputs: os (ostream&) - output stream to be printed to
//        db (Database&) - database to be printed
//Returns: Returns the ostream passed in
ostream& operator<<(ostream& os, Database& db)
{
    os << "Database contents:" << endl;

    //Loop through HashTable
    for (size_t i = 0; i < MAXHASH; i++)
    {
        Slot slot = db.indexTable.getSlot(i);

        //If slot is normal, print info
        if (slot.isNormal())
        {
            os << "HashTable Slot: " << i;
            os << ", recordStore slot " << slot.getIndex();
            os << " -- " << db.recordStore[slot.getIndex()] << endl;
        }
    }
    
    os << endl;
    return os;
}