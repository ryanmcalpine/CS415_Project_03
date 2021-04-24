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


TwoThreeTree::node* insertHelper(const string &x, int line, node *& rt, int &distWord) {
    node* retval;
    if (rt == NULL) // Empty tree: create a leaf node for root
        return new node(x, NULL, NULL, NULL);
    if (rt->left == NULL) // At leaf node: insert here
        return rt.add(new node(x, NULL, NULL, NULL));
    // Add to internal node
    if (x.compare(rt->key1) < 0) { // Insert left
        retval = insertHelper( x, line, rt->left, distWord);
        if (retval == rt->left) return rt;
        else return rt.add(retval);
    }
    else if((rt->key2 == "") || (x.compare(rt->key2) < 0)) {
        retval = insertHelper(x, line, rt->middle, distWord);
        if (retval == rt->middle) return rt;
        else return rt.add(retval);
    }
    else { // Insert right
        retval = insertHelper(x, line, rt->right, distWord);
        if (retval == rt->right) return rt;
        else return rt.add(retval);
    }
}

// Add a new key/value pair to the node. There might be a subtree
// associated with the record being added. This information comes
// in the form of a 2-3 tree node with one key and a (possibly null)
// subtree through the center pointer field.
TwoThreeTree::node* add( const string &x, int line, node *& rt, int &distWord ) {
    node* right;
    node* center;
    node* left;
    if (rt->key2 == "") { // Only one key, add here
        if (rt->key1.compareTo(rt->key1) < 0) {
            rt->key2 = rt->key1;
            center = rt->left; right = rt->middle;
        }
        else {
            rt->key2 = rt->key1; right = center;
            rt->key1 = rt->key1;
            center = rt->middle;
        }
        return rt;
    }
    else if (key1.compareTo(rt->key1) >= 0) { // Add left
        TTNode<Key,E> N1 = new TTNode<Key,E>(lkey, lval, null, null, it, this, null);
        it.setLeftChild(left);
        left = center; center = right; right = null;
        lkey = rkey; lval = rval; rkey = null; rval = null;
        return N1;
    }
    else if (rkey.compareTo(it.lkey()) >= 0) { // Add center
        it.setCenterChild(new TTNode<Key,E>(rkey, rval, null, null, it.cchild(), right, null));
        it.setLeftChild(this);
        rkey = null; rval = null; right = null;
        return it;
    }
    else { // Add right
        TTNode<Key,E> N1 = new TTNode<Key,E>(rkey, rval, null, null, this, it, null);
        it.setLeftChild(right);
        right = null; rkey = null; rval = null;
        return N1;
    }
}



//x is the word to insert, line is the line in the text file
//the word was found at, node is the node of the tree being
//examined, and distWord is incremented if a new word is created
//and used by buildTree
/*void TwoThreeTree::insertHelper(const string &x, int line, node *& t, int &distWord){
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
                promote( x, line, t, distWord );
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

        }
    }
}
*/
void TwoThreeTree::promote(const string &x, int line, node *& t, int &distWord)
{
    // Recursive base case: If node has only one key, set key2
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
    else if( t->key2 != "" )
    {
        // Save the parent of this node
        node* parent = findParent(t);

        // Order node values a < b < c
        string a, b, c = "";
        // If x is least value, set it as 'a'
        if( x.compare(t->key1) < 0 && x.compare(t->key2) < 0 )
        {
            a = x;
            // That only leaves key1 and key2 for b and c
            if( t->key1.compare(t->key2) < 0 )
            {
                b = t->key1;
                c = t->key2;
            }
            else
            {
                b = t->key2;
                c = t->key1;
            }
        }
        // If key1 is least value, set it as 'a'
        if( t->key1.compare(x) < 0 && t->key1.compare(t->key2) < 0 )
        {
            a = t->key1;
            // That only leaves x and key2 for b and c
            if( x.compare(t->key2) < 0 )
            {
                b = x;
                c = t->key2;
            }
            else
            {
                b = t->key2;
                c = x;
            }
        }
        // If key2 is least value, set it as 'a'
        if( t->key2.compare(x) < 0 && t->key2.compare(t->key1) < 0 )
        {
            a = t->key2;
            // That only leaves x and key1 for b and c
            if( x.compare(t->key1) < 0 )
            {
                b = x;
                c = t->key1;
            }
            else
            {
                b = t->key1;
                c = x;
            }
        }

        // If this node has no parent, create one
        if( parent == NULL )
        {
            parent = new node(b, t, NULL, NULL);
            t->key1 = a;
            t->key2 = "";
            insertHelper(c, line, parent->middle, distWord);
        }

        // If the parent of this node has only one key, give it 'b' and split node
        if( parent-> key2 == "" )
        {
            // Give parent 'b':
            // If b is less than key1, put key1 in key2 instead, then put b in key1
            if( b.compare(parent->key1) < 0 )
            {
                parent->key2 = parent->key1;
                parent->key1 = b;
            }
            // If b is greater than key1, set key2
            if( b.compare(parent->key1) > 0 )
            {
                parent->key2 = b;
            }

            // Split node:
            // If we are working with left child
            if( t == parent->left )
            {
                t->key1 = a;
                t->key2 = "";
                insertHelper( c, line, parent->middle, distWord );
            }
            // If we are working with middle child
            if( t == parent->middle )
            {
                t->key1 = a;
                t->key2 = "";
                insertHelper( c, line, parent->right, distWord );
            }
            // Note: a node with only key1 will never have a right child,
            // so a third "if" here to check parent->right is not necessary
        }
        // If the parent of this node has two keys
        else
        {
            node* grandparent = findParent(parent);
            while( grandparent->key2 != "" )
            {
                // If we are at the left child:
                if( t == parent->left )
                {

                }
                // If we are at the middle child:
                if( t == parent->middle )
                {

                }
                // If we are at the right child:
                if( t == parent->right )
                {
                    node *cnode = new node(c, NULL, NULL, NULL);
                    node *bnode = new node(b, t, cnode, NULL);
                    t->key1 = a;
                    t->key2 = "";
                    parent->right = NULL;
                    // promote parent's key2 to parent's parent

                }
            }
        }




        /*
        // Promotion process depends on which child (l/m/r) our node is
        // If we are at the left child:
        if( t == parent->left )
        {
            // Middle value gets promoted // maybe move to end
            promote( b, line, parent, distWord );
            // Least value becomes left child
            // Greatest value becomes middle child
        }
        // If we are at the middle child:
        if ( t == parent-> middle )
        {
            // Middle value gets promoted
            // Least value becomes right child of new left child
            // Greatest value becomes left child of new right child
        }
        // If we are at the right child:
        if( t == parent->right )
        {
            // Middle value gets promoted
            // Least value becomes middle child
            // Greatest value becomes right child
        }






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
         */
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