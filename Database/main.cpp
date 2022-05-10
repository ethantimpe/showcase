#include "Database.h"
#include <time.h>

using namespace std;

void promptInsert(Database&);
void promptDelete(Database&);
void promptSearch(Database&);

int main()
{
    //Seed random
    srand(time(0));

    Database db = Database();

    //Keep prompting user input until they choose to quit
    while (true)
    {
        string in;

        //Prompt user
        cout << "Would you like to (I)nsert or (D)elete a record, or (S)earch for a record, or (Q)uit?" << endl;
        cout << "Enter action: ";
        cin >> in;

        //Prompt user further or quit depending on user input
        if (in == "I")
        {
            promptInsert(db);
        }
        else if (in == "D")
        {
            promptDelete(db);
        }
        else if (in == "S")
        {
            promptSearch(db);
        }
        else if (in == "Q")
        {
            cout << "Exiting.";
            return 0;
        }
        else
        {
            cout << "Action not recognized." << endl << endl;
        }
    }
}

void promptInsert(Database& db)
{
    //Local variables to store record data
    string firstName, lastName, year;
    int uid, collisions;

    //Prompt user for credentials
    cout << "Last name: ";
    cin >> lastName;
    
    cout << "First name: ";
    cin >> firstName;

    cout << "UID: ";
    cin >> uid;

    cout << "Year: ";
    cin >> year;

    //Create record based on input
    Record record(firstName, lastName, uid, year);
    
    //Attempt to insert record to database
    if (db.insert(record, collisions))
    {
        cout << "Record inserted with " << collisions << " collisions." << endl << endl;
    }
    else
        cout << "Record insertion unsuccessful." << endl << endl;
}

void promptDelete(Database& db)
{
    int uid;

    //Prompt user for UID
    cout << "Enter UID to delete: ";
    cin >> uid;

    //Remove record if present in database
    if (db.remove(uid))
    {
        cout << "Record deleted." << endl << endl;
    }
    else
        cout << "Record not found." << endl << endl;
}

void promptSearch(Database& db)
{
    int uid, collisions;
    Record record;

    //Prompt user for UID
    cout << "Enter UID to search for: ";
    cin >> uid;

    cout << "Searching... ";

    //Return record if present in database
    if (db.find(uid, record))
    {
        cout << "record found." << endl;
        cout << "-----------------------" << endl;
        cout << record << endl;
        cout << "-----------------------" << endl;
    }
    else
        cout << "record not found." << endl << endl;
}