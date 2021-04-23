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
    // If we are making a new root node (tree is currently empty)
    if(t == NULL)
    {
        t = new node(x,NULL, NULL, NULL);
        t->lines1.push_back(line);
        distWord++;
    }
    // If we are looking at an existing node
    else
    {
        // Are we at a leaf?
        // If yes:
        if( t->left == NULL && t->middle == NULL )
        {
            // If leaf only has one key
            if( t->key2 == "" )
            {
                // If word is less than key1, put key1 in key2 instead, then put word in key1
                if( x.compare(t->key1) < 0 )
                {
                    t->key2 = t->key1;
                    t->key1 = x;
                }
                // If word is equal to key1, push back line number
                if( x.compare(t->key1) == 0 )
                {
                    t->lines1.push_back(line);
                }
                // If word is greater than key1, set key2
                if( x.compare(t->key1) > 0 )
                {
                    t->key2 = x;
                }
            }
            // If leaf has two keys, promote!
            else
            {
                promote( t, x );
            }
        }
        // If not, keep going:
        else
        {
            // If node only has one key
            if( t->key2 == "" )
            {
                // If word is less than key1, go left
                if( x.compare(t->key1) < 0 )
                {
                    insertHelper(x, line, t->left, distWord);
                }
                // If word is equal to key1, push back line number
                if( x.compare(t->key1) == 0 )
                {
                    t->lines1.push_back(line);
                }
                // If word is greater than key1, go right
                if( x.compare(t->key1) > 0 )
                {
                    insertHelper(x, line, t->middle, distWord);
                }
            }
            // If node has both keys
            else
            {
                // If word is already in node, push line number to node's lines vector
                if( x.compare(t->key1) == 0 )
                {
                    t->lines1.push_back(line);
                }
                if( x.compare(t->key2) == 0 )
                {
                    t->lines2.push_back(line);
                }

                // If word is less than both keys, go left
                if( x.compare(t->key1) < 0 && x.compare(t->key2) < 0 )
                {
                    insertHelper(x, line, t->left, distWord);
                }
                // If word is in between keys, go mid
                if( x.compare(t->key1) > 0 && x.compare(t->key2) < 0 )
                {
                    insertHelper(x, line, t->middle, distWord);
                }
                // If word is greater than both keys, go right
                if( x.compare(t->key1) > 0 && x.compare(t->key2) > 0 )
                {
                    insertHelper(x, line, t->right, distWord);
                }
            }
        }








        /*
        // If node has both keys filled, go left/mid/right
        if( t->key2 != "" )
        {
            // If word is less than both keys, go left
            if(x.compare(t->key1) < 0 && x.compare(t->key2) < 0)
            {
                insertHelper(x, line, t->left, distWord);
            }
            // If word is in between keys, go mid
            if(x.compare(t->key1) > 0 && x.compare(t->key2) < 0)
            {
                insertHelper(x, line, t->middle, distWord);
            }
            // If word is greater than both keys, go right
            if(x.compare(t->key1) > 0 && x.compare(t->key2) > 0)
            {
                insertHelper(x, line, t->right, distWord);
            }

            // If word is already in node, push line number to node's lines vector
            if(x.compare(t->key1) == 0)
            {
                t->lines1.push_back(line);
            }
            if(x.compare(t->key2) == 0)
            {
                t->lines2.push_back(line);
            }
        }
        // Otherwise, if node has only one key
        else
        {
            // If word is less than key1
            if(x.compare(t->key1) < 0)
            {
                insertHelper(x, line, t->left, distWord);
            }
            // If word is equal to key1
            if(x.compare(t->key1) < 0)
            {
                t->lines1.push_back(line);
            }
            // If word is greater than key1
            if(x.compare(t->key1) > 0)
            {
                insertHelper(x, line, t->middle, distWord);
            }
        }
        */

        /*
        // If node has only one key:
        if( t->key2 == "" )
        {
            // If word is greater than key1, set key2
            if( x.compare(t->key1) > 0 )
            {
                t->key2 = x;
                t->lines2.push_back(line);
            }
            // If word matches key1, push line number to vector lines1
            else if( x.compare(t->key1) == 0 )
                t->lines1.push_back(line);
            // If word is less than key, go left
            else
                insertHelper(x, line, t->left, distWord);
        }

        // If node has both keys:
        else

        {
            // If word is greater than both keys, go right
            if(x.compare(t->key1) > 0 && x.compare(t->key2) > 0)
            {
                insertHelper(x, line, t->right, distWord);
            }
            // If word is greater than key1 but smaller than key2, go mid
            if(x.compare(t->key1) > 0 && x.compare(t->key2) < 0)
            {
                insertHelper(x, line, t->middle, distWord);

                *
                 * key1 = x
                 * t->left --> inserthelper(key1)
                 * t->right --> inserthelper(key2)
                 *
            }
            //If word is already in tree, then add the line the inserted word
            //came from to the node's lines vector
            else if(x.compare(t->key1) == 0)
            {
                t->lines1.push_back(line);
            }
            else if(x.compare(t->key2) == 0)
            {
                t->lines2.push_back(line);
            }
            // If word is less than both keys
            else
            {
                insertHelper(x, line, t->left, distWord);
            }

        }*/
    }
}

void TwoThreeTree::promote(const string &x, int line, node *& t, int &distWord)
{
    // If node has only one key, set key2
    if( t->key2 == "" )
    {
        // If word is less than key1, put key1 in key2 instead, then put word in key1
        if( x.compare(t->key1) < 0 )
        {
            t->key2 = t->key1;
            t->key1 = x;
        }
        // If word is equal to key1, push back line number
        if( x.compare(t->key1) == 0 )
        {
            t->lines1.push_back(line);
        }
        // If word is greater than key1, set key2
        if( x.compare(t->key1) > 0 )
        {
            t->key2 = x;
        }
    }
    // if node already has key1 and key2 filled
    else if (t->key2 != "")
    {
        node* parent = findParent(t);
        int a,b,c;
        //if the word is the middle value
        if( x.compare(t->key1) > 0 && x.compare(t->key2) < 0)
        {
            //check to see if you are on the left child or the middle child
            //left child
            if()
            {
                //split key1(left) and key2(middle)
                insertHelper(t->key1, line, t->left, distWord);
                insertHelper(t->key2, line, t->middle, distWord);
            }

            //right child
            else if()
            {
                insertHelper(t->key1, line, t->middle, distWord);
                insertHelper(t->key2, line, t->right, distWord);
            }

            //middle child
            else if()
            {

            }
        }
        //if key1 is the middle value
        else if ( x.compare(t->key1) < 0 && t->key1.compare(t->key2) < 0)
        {
            //find parent node & push key1 up to the parent node
            findParent();

            //word is now key1
            t->key1 = x;

            //split key1(left) and key2(middle)
            insertHelper(t->key1, line, t->left, distWord);
            insertHelper(t->key2, line, t->middle, distWord);
        }
        //if key2 is the middle value
        else if ( x.compare(t->key1) > 0 && x.compare(t->key2) > 0)
        {
            //find parent node & push key2 up to the parent node
            findParent();

            //word is now key2
            t->key2 = x;

            //split key1(left) and key2(middle)
            insertHelper(t->key1, line, t->left, distWord);
            insertHelper(t->key2, line, t->middle, distWord);
        }
    }
}

TwoThreeTree::node* TwoThreeTree::findParent(node *& t)
{
    return findParentHelper( root, t );
}

TwoThreeTree::node* TwoThreeTree::findParentHelper(node *& r, node *& t)
{
    if( t != NULL )
    {
        if( r->left != t && r->middle != t && r->right != t )
        {
            node* left = findParentHelper( r->left, t );
            node* mid = findParentHelper( r->middle, t );
            node* right = findParentHelper( r->right, t );

            if( left != NULL )
            {
                return left;
            }
            if( mid != NULL )
            {
                return mid;
            }
            if( right != NULL )
            {
                return right;
            }
        }
        else
        {
            return r;
        }
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
    else if( x.compare(t->key2) > 0 )
        return containsHelper(x, t->right, result);
    // If word is in between key values
    else if( x.compare(t->key1) > 0 && x.compare(t->key2) < 0 )
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