//Description: Takes a text file supplied by the user
//             and turns it into a word index, implemented
//             through the use of a BST 

#include <iostream>
#include <fstream>
#include "bst.h"
#include "TwoThreeTree.h"
using namespace std;

int main(int argc, char* argv[])
{
	if (argc != 2)
	{
	    cout << "Incorrect input. Correct format: ./<exectuable.out> <inputtext.txt>\n";
	    return 1;
	}

	ifstream input(argv[1]);
    if(!input.is_open())
    {
        cout << "Invalid File Name. Restart Program.\n";
        return 2;
    }

	char ch;
    cout <<"Options: (a) BST, (b) 2-3 Tree, (c) Compare BST and 2-3 Tree, (d) quit\n";
	cin >> ch;

	if( ch == 'a' )
    {
        int choice;
        BST myTree;

        myTree.buildTree(input);
        input.close();
        while(1)
        {
            choice = 0;
            cout << "Options: (1) display index, (2) search, (3) save index, (4) quit\n";
            cin >> choice;

            //Print index
            if(choice == 1)
            {
                myTree.printTree(cout);
            }
            //Search index for a word
            else if(choice == 2)
            {
                myTree.contains();
            }
            //Save index
            else if(choice == 3)
            {
                string outputFile;
                cout << "Enter a filename to save your index to (Suggested: <filename>.txt) : ";
                cin >> outputFile;
                ofstream output(outputFile.c_str());
                myTree.printTree(output);
                output.close();
                cout << "Saved\n";
            }
            //Quit
            else
            {
                break;
            }
        }
    }

    if( ch == 'b' )
    {
        int choice;
        TwoThreeTree myTree;

        myTree.buildTree(input);
        input.close();
        while(1)
        {
            choice = 0;
            cout << "Options: (1) display index, (2) search, (3) save index, (4) quit\n";
            cin >> choice;

            //Print index
            if(choice == 1)
            {
                myTree.printTree(cout);
            }
            //Search index for a word
            else if(choice == 2)
            {
                myTree.contains();
            }
            //Save index
            else if(choice == 3)
            {
                string outputFile;
                cout << "Enter a filename to save your index to (Suggested: <filename>.txt) : ";
                cin >> outputFile;
                ofstream output(outputFile.c_str());
                myTree.printTree(output);
                output.close();
                cout << "Saved\n";
            }
            //Quit
            else
            {
                break;
            }
        }
    }

	return 0;
}
