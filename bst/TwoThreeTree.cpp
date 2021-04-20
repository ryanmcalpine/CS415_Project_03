//
// Created by Nicholas Keng on 4/17/21.
//

#include "TwoThreeTree.h"
#include "time.h"
#include <iomanip>
#include <sstream>
#include <algorithm>

//Constructor
TwoThreeTree::TwoThreeTree()
{
    root = NULL;
}

//Returns true if there are no nodes in the tree
bool TwoThreeTree::isEmpty()
{
    return root == NULL;
}

//Receives the specified input file and constructs
//the actual tree. Prints a message when finished.
void TwoThreeTree::buildTree(ifstream & input){
    int line = 1, numWords = 0, distWords = 0, treeHeight = 0;
    stringstream tempWord;
    double totalTime, finishTime, startTime = clock();
    while (!input.eof()) {
        string tempLine, tempWord;

        //Read a whole line of text from the file
        getline(input, tempLine);
        for (int i = 0; i < tempLine.length(); i++) {
            //Insert valid chars into tempWord until a delimiter (newline or space) is found
            while (tempLine[i] != ' '&& tempLine[i] != '\n' && i < tempLine.length() ) {
                tempWord.insert(tempWord.end(), tempLine[i]);
                i++;
            }

            //Trim any punctuation off end of word. Will leave things like apostrophes
            //and decimal points
            while(tempWord.length() > 0 && !isalnum(tempWord[tempWord.length() - 1]))
                tempWord.resize(tempWord.size() -1);

            if (tempWord.length() > 0)
            {
                //Once word is formatted,call insert with the word, the line of the input
                //file it came from, the root of our tree, and the distinct word counter
                insertHelper(tempWord, line, root, distWords);
                //Increment our total number of words inserted
                numWords++;
                //Clear out tempWord so we can use it again
                tempWord.clear();
            }

        }
        line++;
    }
    //Do time and height calculation
    finishTime = clock();
    totalTime = (double) (finishTime - startTime)/CLOCKS_PER_SEC;
    treeHeight = findHeight(root);

    //Print output
    cout << setw(40) << std::left;
    cout << "Total number of words: " << numWords<< endl;

    cout << setw(40) << std::left
         << "Total number of distinct words: " << distWords << endl;

    cout << setw(40) << std::left
         <<"Total time spent building index: " << totalTime << endl;

    cout << setw(40) << std::left
         <<"Height of 2-3 Tree is : " << treeHeight << endl;

}

//x is the word to insert, line is the line in the text file
//the word was found at, node is the node of the tree being
//examined, and distWord is incremented if a new word is created
//and used by buildTree
void TwoThreeTree::insertHelper(const string &x, int line, node *& t, int &distWord){
    // If we are making a new node (word is not already in index)
    if(t == NULL)
    {
        t = new node(x,NULL, NULL, NULL);
        t->lines1.push_back(line);
        distWord++;
    }
    // If we are looking at an existing node
    else
    {
        // If node has only one key:
        if( t->key2 == "" )
        {
            // If word is greater than key
            if( x.compare(t->key1) > 0 )
            {
                t->key2 = x;
            }
            // If word matches key1
            else if( x.compare(t->key1) == 0 )
                t->lines1.push_back(line);
            // If word is less than key
            else
                insertHelper(x, line, t->left, distWord);
        }

        // If node has both keys:

        // If word is greater than both keys
        if (x.compare(t->key1) > 0 && x.compare(t->key2) > 0)
            insertHelper(x, line, t->right, distWord);
        // If word is greater than key1 but smaller than key2
        if (x.compare(t->key1) > 0 && x.compare(t->key2) < 0)
            insertHelper(x, line, t->middle, distWord);
        //If word is already in tree, then add the line the inserted word
        //came from the the nodes lines vector
        else if (x.compare(t->key1) == 0)
            t->lines1.push_back(line);
        else if (x.compare(t->key2) == 0)
            t->lines2.push_back(line);
        // If word is less than both keys
        else
            insertHelper(x, line, t->left, distWord);
    }
}

//Used to implement the search function in the main program.
void TwoThreeTree::contains() const
{
    string input;
    node *foundNode = NULL;
    cout << "Search word: ";
    cin >> input;
    if(containsHelper(input, root, foundNode))
    {
        if( input.compare(foundNode->key1) == 0 )
        {
            cout << "Line Numbers: " << foundNode->lines1[0];
            for(int i = 1; i < foundNode->lines1.size(); i++)
                cout << ", " <<foundNode->lines1[i];
            cout << '\n';
        }
        else if( input.compare(foundNode->key2) == 0 )
        {
            cout << "Line Numbers: " << foundNode->lines2[0];
            for(int i = 1; i < foundNode->lines2.size(); i++)
                cout << ", " <<foundNode->lines2[i];
            cout << '\n';
        }
    }
    else
        cout << '\"' << input <<"\" is not in the document\n";
}

//Used by contains() to see if a words is present or not. Will
//give contains() a pointer to the found node so that contains()
//can prints the lines the word was found on.
bool TwoThreeTree::containsHelper(const string & x, node * t, node * &result) const
{
    if( t == NULL )
        return false;
    if( t->key1.compare(x) == 0 || t->key2.compare(x) == 0 )
    {
        result = t;
        return true;
    }
    // If word is greater than key2
    else if( t->key2.compare(x) > 0 )
        return containsHelper(x, t->right, result);
    // If word is in between key values
    else if( t->key1.compare(x) > 0 && t->key2.compare(x) < 0 )
        return containsHelper(x, t->middle, result);
    // If word is less than key1
    else
        return containsHelper(x, t->left, result);
}

//Prints the index to the supplied receiver, either
//cout or the output file
void TwoThreeTree::printTree(ostream & out) const
{
    out << "2-3 Tree Index:\n-------------------------\n";
    printTreeHelper(root, out);
}

//Called by printTree(), does the actual formatted printing
void TwoThreeTree::printTreeHelper(node *t, ostream & out) const
{
    if(t == NULL)
        return;
    else
    {
        printTreeHelper(t->left, out);
        out << setw(30) << std::left;
        out << t->key1 << " " << t->lines1[0];
        for (int i = 1; i < t->lines1.size(); i++)
            out << ", " << t->lines1[i];
        out << endl;

        printTreeHelper(t->middle, out);
        out << setw(30) << std::left;
        if( t-> key2 != "" )
        {
            out << t->key2 << " " << t->lines2[0];
            for(int i = 1; i < t->lines2.size(); i++)
                out << ", " << t->lines2[i];
            out << endl;
        }

        printTreeHelper(t->right, out);
    }
}

//Returns height of tree. If tree has only one node, height is 1
int TwoThreeTree::findHeight(node *t)
{
    if(t == NULL)
        return 0;
    else
    {
        int leftHeight = findHeight(t->left), midHeight = findHeight(t->middle), rightHeight = findHeight(t->right);

        int h = std::max({leftHeight, midHeight, rightHeight});

        return (h+1);
    }
}