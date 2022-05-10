#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <stdlib.h>
#include "trie.h"

using namespace std;

int main()
{
    Trie trie;
    string nextWord;
    ifstream infile;

    //Attempt to open file, print error and return if fails
    infile.open("wordlist_windows.txt");
    if (!infile)
    {
        cout << "Couldn't open file." << endl;
        return 1;
    }

    //Loops through all words in the file, adding each to the trie
    while (!infile.eof())
    {
        getline(infile, nextWord);
        
        trie.insert(nextWord);
    }

    cout << trie.getSize() << " words were added to the trie using " << trie.count() << " nodes." << endl << endl;

    //Prompt user input continuously until quit
    while (true)
    {
        string in = "";
        string lastKey = "";
        string in2 = "";
        
        //Prompt user for prefix
        cout << "Please enter a word prefix (or press enter to exit): ";
        cin.clear();
        cin.sync();
        getline(cin, in);

        //Terminate program if enter is pressed
        if (in == "")
        {
            return 0;
        }
        
        //Ask user if want to show completions
        cout << "\nThere are " << trie.completeCount(in) << " completions for the prefix '" << in;
        cout << "'. Show completions? ";
    
        cin >> in2;

        //If yes, print all words with prefix
        if (in2 == "Yes" || in2 == "yes" || in2 == "y")
        {
            cout << endl;
            cout << "Completions" << endl;
            cout << "-----------" << endl;

            vector<string> vec = trie.complete(in);
	        for (vector<string>::iterator it = vec.begin(); it != vec.end(); ++it) 
            {	
		        cout << *it << endl;
	        }
        }
        
        cout << endl;
    }
    
}