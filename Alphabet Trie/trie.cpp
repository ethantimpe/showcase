#include "trie.h"

//Function: Default constructor for TrieNode
//Inputs: None
//Returns: None
TrieNode::TrieNode()
{
    //Set all child nodes to null pointers
    for (size_t i = 0; i < 26; i++)
    {
        childNodes[i] = nullptr;
    }

    isEnd = false;
}

//Function: Deconstructor for TrieNode, deletes all children before
//          deleting itself
//Inputs: None
//Returns: None
TrieNode::~TrieNode()
{
    //Loop through all child nodes, if they aren't null call deconstructor
    for (size_t i = 0; i < 26; i++)
    {
        if (childNodes[i] != nullptr)
            delete childNodes[i];
    }
    
}

//Function: Default constructor for Trie
//Inputs: None
//Returns: None
Trie::Trie()
{
    rootNode = new TrieNode();
    numNodes = 1;
    numWords = 0;
}

//Function: Deconstructor for Trie
//Inputs: None
//Returns: None
Trie::~Trie()
{
    //Deleting root node recursively deletes all children
    if (rootNode != nullptr)
        delete rootNode;
}

//Function: Inserts string into the trie
//Inputs: str (string) - string to be added to trie
//Returns: bool - returns true if successfully inserted, false if string
//         is already in trie
bool Trie::insert(string str)
{
    TrieNode* currentNode = rootNode;

    //Loop through the letters of the string
    for (size_t i = 0; i < str.length(); i++)
    {
        //Determine index of the letter by subtracting ASCII value of 'a'
        int index = str[i] - 'a';

        //If next letter node doesn't exist, create it
        if (currentNode->childNodes[index] == nullptr)
        {
            numNodes++;
            currentNode->childNodes[index] = new TrieNode();
        }
        
        //Move to next node
        currentNode = currentNode->childNodes[index];
    }

    //If end of word already exists, return false
    if (currentNode->isEnd)
    {
        return false;
    }
    //Otherwise, mark as end and return true
    else
    {
        currentNode->isEnd = true;
        numWords++;
        return true;
    }
}

//Function: Returns the number of nodes in the trie
//Inputs: None
//Returns: int - number of nodes in the trie
int Trie::count()
{
    return numNodes;
}

//Function: Returns the number of words in the trie
//Inputs: None
//Returns: int - number of words in the trie
int Trie::getSize()
{
    return numWords;
}

//Function: Returns true if string is in trie
//Inputs: str (string) - string to be searched for
//Returns: bool - returns true if string is in trie, false if not
bool Trie::find(string str)
{
    TrieNode* currentNode = rootNode;

    //Loop through all letters in word
    for (size_t i = 0; i < str.length(); i++)
    {
        //Get index of current letter
        int index = str[i] - 'a';

        //If any letter pointer is null, return false
        if (currentNode->childNodes[index] == nullptr)
        {
            return false;
        }
        //Otherwise, go to next node
        else currentNode = currentNode->childNodes[index];
    }

    //If last node specifies the end of a word, return true
    if (currentNode->isEnd)
    {
        return true;
    }
}

//Function: Returns the number of words in the trie matching a given prefix
//Inputs: str (string) - prefix to be searched for
//Returns: int - number of strings in trie with given prefix
int Trie::completeCount(string str)
{
    TrieNode* currentNode = rootNode;

    for (size_t i = 0; i < str.length(); i++)
    {
        //Get index of current letter
        int index = str[i] - 'a';

        //If any letter pointer is null, return false
        if (currentNode->childNodes[index] == nullptr)
        {
            return 0;
        }
        //Otherwise, go to next node
        else currentNode = currentNode->childNodes[index];
    }
    
    completeCountHelper(currentNode);
}

//Function: Helper function for completeCount(), recursively traverses trie
//Inputs: 
//Returns: int - number of strings beginning with prefix str
int Trie::completeCountHelper(TrieNode* node)
{
    int count = 0;

    //Check all child nodes. If not null, recursively add amount of endWord nodes found
    for (size_t i = 0; i < 26; i++)
    {
        if (node->childNodes[i] != nullptr)
        {
            count += completeCountHelper(node->childNodes[i]);
        }
    }
    
    if (node->isEnd)
        count++;

    return count;
}

//Function: Returns a vector of strings that begin with a given prefix
//Inputs: str (string) - prefix to be searched for
//Returns: vector<string> - vector of strings that begin with a given prefix
vector<string> Trie::complete(string str)
{
    vector<string> vec = {};
    TrieNode* currentNode = rootNode;

    //Loop through letters to get to starting node
    for (size_t i = 0; i < str.length(); i++)
    {
        //Get index of current letter
        int index = str[i] - 'a';

        //If any letter pointer is null, return empty vector
        if (currentNode->childNodes[index] == nullptr)
        {
            return vec;
        }
        //Otherwise, go to next node
        else currentNode = currentNode->childNodes[index];
    }

    //Recursively traverse trie, adding words to vec
    completeHelper(currentNode, vec, str);

    return vec;
}

//Function: Helper function for complete(), recursively traverses trie, adding
//          words to vector
//Inputs: node (TrieNode*) - pointer to node to be checked
//        vec (vector<string>&) - reference to vector to add words to
//        str (string) - current string of at node
//Returns: None
void Trie::completeHelper(TrieNode* node, vector<string>& vec, string str)
{
    //If node is an end node, add string to vector
    if (node->isEnd)
    {
        vec.push_back(str);
    }

    for (size_t i = 0; i < 26; i++)
    {
        if (node->childNodes[i] != nullptr)
        {
            //Get char of existing node and add to str
            char ch = 'a' + i;
            string tempStr = str;
            tempStr += ch;

            completeHelper(node->childNodes[i], vec, tempStr);
        }
    }
}