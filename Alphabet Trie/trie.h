#pragma once

#include <iostream>
#include <exception>
#include <vector>

using namespace std;

class TrieNode
{
    public:
        //Function: Default constructor for TrieNode
        //Inputs: None
        //Returns: None
        TrieNode();

        //Function: Deconstructor for TrieNode, deletes all children before
        //          deleting itself
        //Inputs: None
        //Returns: None
        ~TrieNode();

        //Member data for TrieNode
        TrieNode* childNodes[26]; //Array of pointers to child nodes
        bool isEnd;               //True if node specifies end of word
};

class Trie
{
    public:
        //Function: Default constructor for Trie
        //Inputs: None
        //Returns: None
        Trie();

        //Function: Deconstructor for Trie
        //Inputs: None
        //Returns: None
        ~Trie();

        //Function: Inserts string into the trie
        //Inputs: str (string) - string to be added to trie
        //Returns: bool - returns true if successfully inserted, false if string
        //         is already in trie
        bool insert(string str);

        //Function: Returns the number of nodes in the trie
        //Inputs: None
        //Returns: int - number of nodes in the trie
        int count();

        //Function: Returns the number of words in the trie
        //Inputs: None
        //Returns: int - number of words in the trie
        int getSize();

        //Function: Returns true if string is in trie
        //Inputs: str (string) - string to be searched for
        //Returns: bool - returns true if string is in trie, false if not
        bool find(string str);

        //Function: Returns the number of words in the trie matching a given prefix
        //Inputs: str (string) - prefix to be searched for
        //Returns: int - number of strings in trie with given prefix
        int completeCount(string str);

        //Function: Returns a vector of strings that begin with a given prefix
        //Inputs: str (string) - prefix to be searched for
        //Returns: vector<string> - vector of strings that begin with a given prefix
        vector<string> complete(string str);

    private:
        //Member data for Trie
        TrieNode* rootNode;     //Pointer to the root node
        int numWords;           //Number of words in the trie
        int numNodes;           //Number of nodes in the trie

        //Function: Helper function for completeCount(), recursively traverses trie
        //Inputs: node (TrieNode*) - pointer to node
        //Returns: int - number of strings beginning with prefix str
        int completeCountHelper(TrieNode* node);

        //Function: Helper function for compltee(), recursively traverses trie, adding
        //          words to vector
        //Inputs: node (TrieNode*) - pointer to node to be checked
        //        vec (vector<string>&) - reference to vector to add words to
        //        str (string) - current string of at node
        //Returns: None
        void completeHelper(TrieNode* node, vector<string>& vec, string str);
};